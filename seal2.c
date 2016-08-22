#include <stdio.h>
#include <windows.h>
#include "seal2.h"

int seal2_launch(int restrictions, char *command)
{
	PROCESS_INFORMATION my_process;
	HANDLE my_process_handle;
	HANDLE my_job;
	STARTUPINFO my_process_startup;
	
	my_job = CreateJobObject(NULL, NULL);
	if (!my_job)
	{
		error_message();
		return ERR_JOB_CREATION_FAILED;
	}
	
	if (!seal2_job_restrict_exec(my_job))
	{
		error_message();
		return ERR_JOB_RESTRICT_EXEC_FAILED;
	}
	
	if (restrictions & RESTRICT_GUI)
	{
		if (!seal2_job_restrict_gui(my_job))
		{
			error_message();
			return ERR_JOB_RESTRICT_GUI_FAILED;
		}
	}
	
	GetStartupInfo(&my_process_startup);
	if (!CreateProcess(NULL, command, NULL, NULL,
					   FALSE, CREATE_SUSPENDED, NULL, NULL,
					   &my_process_startup, &my_process))
	{
		error_message();
		return ERR_PROCESS_CREATION_FAILED;
	}

	my_process_handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, my_process.dwProcessId);
	if (!my_process_handle)
	{
		error_message();
		return ERR_PROCESS_OPEN_FAILED;
	}
	
	if (!AssignProcessToJobObject(my_job, my_process_handle))
	{
		error_message();
		return ERR_PROCESS_ASSIGN_JOB_FAILED;
	}
	
	ResumeThread(my_process.hThread);
	CloseHandle(my_process_handle);
	return ERR_SUCCESS;
}

int seal2_job_restrict_exec(HANDLE job_handle)
{
	JOBOBJECT_BASIC_LIMIT_INFORMATION job_limits;
	
	job_limits.LimitFlags = JOB_OBJECT_LIMIT_ACTIVE_PROCESS;
	job_limits.ActiveProcessLimit = 0x01; /* Only this one process */
	
	if (!SetInformationJobObject(job_handle,
								 JobObjectBasicLimitInformation,
								 &job_limits,
								 sizeof(JOBOBJECT_BASIC_LIMIT_INFORMATION)))
	{
		return FALSE;
	}
	
	return TRUE;
}

int seal2_job_restrict_gui(HANDLE job_handle)
{
	JOBOBJECT_BASIC_UI_RESTRICTIONS job_ui_rules;
	job_ui_rules.UIRestrictionsClass = 0xFF; /* All possible UI restrictions */

	if (!SetInformationJobObject(job_handle,
								 JobObjectBasicUIRestrictions,
								 &job_ui_rules,
								 sizeof(JOBOBJECT_BASIC_UI_RESTRICTIONS)))
	{
		return FALSE;
	}
	
	return TRUE;
}

void error_message(void)
{
	DWORD err = GetLastError();
	LPSTR buffer = NULL;
	
	/* Usage the ANSI FormatMessageA function so this works with printf etc. */
	FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER |
				   FORMAT_MESSAGE_FROM_SYSTEM |
				   FORMAT_MESSAGE_IGNORE_INSERTS,
				   NULL,
				   err,
				   MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
				   buffer,
				   0, NULL);	

	fprintf(stderr, "%s\n", buffer);
	LocalFree(buffer);
}

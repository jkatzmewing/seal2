#ifndef SEAL2_H
#define SEAL2_H

#define RESTRICT_NONE		0x00000000
#define RESTRICT_GUI		0x00000001
#define RESTRICT_GUI_LIGHT	0x00000002

#define ERR_SUCCESS						 0
#define ERR_JOB_CREATION_FAILED			-1
#define ERR_JOB_RESTRICT_EXEC_FAILED	-2
#define ERR_JOB_RESTRICT_GUI_FAILED		-3
#define ERR_PROCESS_CREATION_FAILED		-4
#define ERR_PROCESS_OPEN_FAILED			-5
#define ERR_PROCESS_ASSIGN_JOB_FAILED	-6

int seal2_launch(int restrictions, char *command);

int seal2_job_restrict_exec(HANDLE job_handle);
int seal2_job_restrict_gui(HANDLE job_handle);

void error_message(void);

#endif /*SEAL2_H*/

# Seal2
A crude process restriction tool for Windows 2000 and later.

## Summary

Seal2 is a port of the original [SEAL](https://github.com/miramor/seal) to ANSI C, which
is more tolerable than C++ to non-programmer types like myself. It can prevent a Windows
program from launching other programs; and also optionally restrict its interaction with
other (graphical) programs, at the cost of disabling copy/paste functionality.

## Caveats

Seal2 by itself is not an adequate defense against modern adversaries. For exploit mitigation,
you want [Microsoft EMET.](https://support.microsoft.com/en-us/kb/2458544)

Seal2 cannot restrict Windows Explorer with default Explorer settings. All Explorer windows
belong to the same process, so there is no "new" Explorer process to effect restrictions on.

Seal2 can't restrict Internet Explorer on newer Windows versions, due to later IE versions
using their own JobObject sandboxes. The same applies for Chrome, and anything else that uses
Win32 native sandboxing mechanisms.

Seal2 working on Windows 2000 and XP is more proof-of-concept than anything else. You should
still limit your legacy Windows OSes to virtual machines without Internet access, at a bare
minimum.

IT security is a bottomless pit, as always.

## Invocation

Seal2 is invoked as follows:

    seal.exe "Path\To\Executable" "Argument1 Argument2 ..."

or just

    seal.exe "Path\To\Executable.exe" ""

if you don't need to give the program any arguments. GUI restrictions are enabled using
the '--gui' option. For instance:

    seal.exe --gui "C:\Windows\Notepad.exe" ""

**Note that passing arguments to the child program might be finicky right now. Seal2
currently handles arguments the Linux way, but Windows might not agree on what
constitutes proper quoting. If in doubt, you should probably forego the command line
arguments.**

## Compiling

Only cross-builds on Linux are currently supported. Building stuff on Windows is painful,
and EXEs built under Debian Jessie (AMD64) have invariably worked fine on my Windows 2000
virtual machines.

The makefile is set for 32-bit cross-builds by default. It should work on any modern Linux
distro with a recent version of MinGW-w64. Just type

    make

64-bit cross-builds also work on Jessie AMD64, though I can't (yet) test them in an actual
64-bit Windows environment. Just substitute the 64-bit MinGW compiler:

    make CC=x86_64-w64-mingw32-gcc

## Implementation

Like the old version, Seal2 uses Win32 JobObjects to prevent process spawning, and also for
the optional GUI restrictions. JobObjects are part of the NT kernel in Windows 2000 and later;
and are supposed to be securely implemented, insofar as anything on Windows can be.

For more information, please see Microsoft's [Win32 API docs on JobObjects.](https://msdn.microsoft.com/en-us/library/windows/desktop/ms684161(v=vs.85).aspx)

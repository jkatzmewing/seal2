# Linux makefile for Linux -> Win32 via MinGW-w64.
# For Win64 or other compilers, specify the needed variables on the
# command line when running make.

CC = i686-w64-mingw32-gcc
CFLAGS = -O2 -Wall -Wextra -pedantic
EXE = seal.exe

all: main.o seal2.o
	$(CC) $(CFLAGS) -o $(EXE) main.o seal2.o

main.o: main.c seal2.h
	$(CC) -c $(CFLAGS) main.c

seal2.o: seal2.c seal2.h
	$(CC) -c $(CFLAGS) seal2.c

clean:
	rm -f $(EXE) *.o

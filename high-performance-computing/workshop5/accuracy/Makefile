#-----------------------------------------------#
#	Makefile for unix systems		#
#    using a GNU C compiler			#
#-----------------------------------------------#
CC=gcc
CFLAGS=-g -Wall -D__USE_FIXED_PROTOTYPES__ -ansi
#
# Compiler flags:
#	-g	-- Enable debugging
#	-Wall	-- Turn on all warnings
#	-D__USE_FIXED_PROTOTYPES__
#		-- Force the compiler to use the correct headers
#	-ansi	-- Don't use GNU extensions.  Stick to ANSI C.

float: float.c
	$(CC) $(CFLAGS) -o float float.c

double: double.c
	$(CC) $(CFLAGS) -o double double.c

clean:
	rm -f float double

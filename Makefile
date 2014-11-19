#------------------------------------------------------------------------
# File:          Makefile
# Author:        
# Created:      
# Last revised:  
#------------------------------------------------------------------------

#------------------------------------------------------------------------
# Use the gcc compiler
CC = gcc
#------------------------------------------------------------------------


all: calendar

# List program components, what they depend on, and how to compile each

calendar:  calendar.o appt-func.o
	$(CC) -o 1 calendar.o appt-func.o

calendar.o:  calendar.c appt.h appt-func.h
	$(CC) -c calendar.c

appt-func.o:  appt-func.c appt-func.h appt.h
	$(CC) -c appt-func.c

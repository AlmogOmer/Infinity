# make clean/all CONFIG=Debug/Release ARCH=linux64/raspi ECHO=0/1

# the parrent dir of "arch" dir
ROOT_DIR = ../../..

#PROJ_SRCS = $(wildcard *.c)
PROJ_SRCS = wd_lib.c  

# list of directories containing header files
PROJ_INC_DIR = ../../../ds/scheduler ../../../ds/uid
# the executable file
PROJ_OUT = libwd.so

# list of ADDITIONAL compiler flags (prepended with "-" sign)
#PROJ_CFLAGS = -Wunused-but-set-variable
PROJ_CFLAGS = 
PROJ_CPPFLAGS =

#PROJ_MACROS = _BSD_SOURCE
PROJ_MACROS =

# additional object files (created by other projects)
PROJ_ADD_OBJS = priority_queue.o heap.o dynamic_vector.o uid.o scheduler.o task.o

# additional libraries
PROJ_LIBS = pthread

# linker flags
PROJ_LDFLAGS =

# list of projects (makefiles) this project depends on
PROJ_DEPENDS  = ../../../ds/scheduler/makefile 

include $(ROOT_DIR)/include/make/Project.mak
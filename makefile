.PHONY: all custom lib

CC=g++
OPT=-g
CFLAGS=-c -Wall -std=c++14
SRCPATH:=src/
SRCS:=$(wildcard $(SRCPATH)*.cpp)
OBJS:=$(SRCS:%.cpp=%.o)

LDFLAGS:=
# include LDFLAGS and LOCAL vaiables
include makefile.flags

INCL=-Isrc -Itest ${LOCAL_OPENCL_I}

# OS dependent variables
RM=
ifeq ($(OS),Windows_NT)
	RM=del
else
	RM=rm
endif

all: test.exe

custom: mtest.exe

lib: liboutput.a

liboutput.a: $(OBJS)
	$(RM) liboutput.a
	ar -qcT liboutput.a $(OBJS)

test.exe: liboutput.a test/test.o
	$(CC) -o test.exe test/test.o liboutput.a $(LDFLAGS) $(OPT)
	
mtest.exe: liboutput.a test/mtest.o
	$(CC) -o mtest.exe test/mtest.o liboutput.a $(LDFLAGS) $(OPT)

%.o: %.cpp
	$(CC) $(CFLAGS) $< -o $@ $(INCL) $(OPT)
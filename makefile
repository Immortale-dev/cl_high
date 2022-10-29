.PHONY: all custom generate_o generate_t

CC=g++
OPT=-g
CFLAGS=-c -Wall -std=c++14
OPENCL_I=-I"C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v11.6\include"
OPENCL_L=-L"C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v11.6\lib\x64"
LDFLAGS:=${OPENCL_I} ${OPENCL_L} -lOpenCL
SRCPATH:=src/
SRCS:=$(wildcard $(SRCPATH)*.cpp)
OBJS:=$(SRCS:%.cpp=%.o)

INCL=-Isrc -Itest

all: generate_o generate_t

generate_o: ${OBJS}

generate_t:
	$(CC) $(CFLAGS) test/test.cpp -o test/test.o $(LDFLAGS) $(INCL) $(OPT)
	$(CC) -o test.exe test/test.o $(OBJS) $(INCL) $(LDFLAGS)

custom: generate_o
	$(CC) $(CFLAGS) test/mtest.cpp -o test/mtest.o $(LDFLAGS) $(INCL) $(OPT)
	$(CC) test/mtest.o $(OBJS) $(INCL) $(LDFLAGS) -o mtest.exe
%.o: %.cpp
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS) $(INCL) $(OPT)
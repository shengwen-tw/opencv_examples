#################################################################
EXECUTABLE=video_capture

#################################################################
#compiler
CC=g++

#################################################################
#include files
CFLAGS=`pkg-config opencv --cflags` `pkg-config opencv --libs`
LDFLAGS:=

#################################################################
#compile all c++ files in dir
SRC=$(wildcard *.cpp)

#################################################################
OUTPUT=./output

all:perspective-correction virtual-billboard

perspective-correction:perspective-correction.cpp
	mkdir -p $(OUTPUT)
	$(CC) $< $(LDFLAGS) $(CFLAGS) -o $@

virtual-billboard:virtual-billboard.cpp
	mkdir -p $(OUTPUT)
	$(CC) $< $(LDFLAGS) $(CFLAGS) -o $@

clean:
	rm -rf $(EXECUTABLE) $(OUTPUT)
#################################################################

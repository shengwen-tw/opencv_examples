#################################################################
EXECUTABLE=opject_tracking

#################################################################
#compiler
CC=g++

#################################################################
#include files
CFLAGS=`pkg-config opencv --cflags` `pkg-config opencv --libs`
LDFLAGS:=

#################################################################
#compile all c++ files in dir
CFLAGS+=-I./
SRC=$(wildcard *.cpp)

#################################################################
OUTPUT=./output

all:$(EXECUTABLE)

$(EXECUTABLE):$(SRC)
	$(CC) $< $(LDFLAGS) $(CFLAGS) -o $@

clean:
	rm -rf $(EXECUTABLE) $(OUTPUT)
#################################################################

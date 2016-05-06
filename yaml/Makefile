#################################################################
EXECUTABLE=yaml

#################################################################
#compiler
CC=g++

#################################################################
#include files
CFLAGS=`pkg-config opencv --cflags` `pkg-config opencv --libs`
CFLAGS+=-lyaml-cpp
LDFLAGS:=

#################################################################
#compile all c++ files in dir
SRC=$(wildcard *.cpp)

#################################################################

all:$(EXECUTABLE)

$(EXECUTABLE):$(SRC)
	$(CC) $< $(LDFLAGS) $(CFLAGS) -o $@

clean:
	rm -rf $(EXECUTABLE)
#################################################################

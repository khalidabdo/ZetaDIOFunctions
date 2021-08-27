#
# Makefile
# Copyright (c) 2018 by Diamond Systems.
#
# Make file to build Demo application
#

APPName = ZetaDIOFunctions
LIB =-L ../Common/ -ldscud-8.3.1 -lm -lpthread
INC =-I ../Common/

SOURCES = Parser.cpp
		

all: $(APPName).o

$(APPName).o:
	g++ -o $(APPName) $(APPName).cpp $(SOURCES) $(INC) $(LIB)
	cp $(APPName) ./Executables

clean:
	rm -f $(APPName).o

#
# Makefile
# Copyright (c) 2018 by Diamond Systems.
#
# Make file to build Demo application
#

APPName = ZetaDIOFunctions
LIB =-L ../Common/ -ldscud-8.3.1 -lm -lpthread
INC =-I ../Common/

all: $(APPName).o

$(APPName).o:
	gcc -o $(APPName) $(APPName).c $(INC) $(LIB)
	cp $(APPName) ./Executables

clean:
	rm -f $(APPName).o

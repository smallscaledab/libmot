.PHONY : clean

UNAME := $(shell uname)
ifeq ($(UNAME), Windows_NT)
	LIB = mot.dll
else
	LIB = mot.so
endif

lib: 
	make -C src
	
tests: lib
	make -C tests

all: lib tests

clean:
	make -C src clean
	make -C tests clean
	rm $(LIB)
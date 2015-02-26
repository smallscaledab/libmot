.PHONY : clean

lib:
	make -C src
	
tests: lib
	make -C tests

all: lib tests

clean:
	make -C src clean
	make -C tests clean
	rm *.dll
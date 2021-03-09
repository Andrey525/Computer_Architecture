
bin/prog: build/main.o lib/libmyTerm.a bin
	gcc build/main.o -L./lib -lmyTerm -o bin/prog

build/main.o: src/main.c src/myTerm.h build
	gcc -Wall -Werror -c src/main.c -o build/main.o 

lib/libmyTerm.a: build/myTerm.o lib
	ar rc lib/libmyTerm.a build/myTerm.o

build/myTerm.o: src/myTerm.c src/myTerm.h build
	gcc -Wall -Werror -c src/myTerm.c -o build/myTerm.o 

build: 
	mkdir build

bin:
	mkdir bin

lib:
	mkdir lib

clean: 
	rm -rf bin build lib *.bin

.PHONY: all clean 
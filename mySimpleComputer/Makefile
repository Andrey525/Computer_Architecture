
bin/prog: build/main.o lib/libmySimpleComputer.a bin
	gcc build/main.o -L./lib -lmySimpleComputer -o bin/prog

build/main.o: src/main.c src/mySimpleComputer.h build
	gcc -Wall -Werror -c src/main.c -o build/main.o 

lib/libmySimpleComputer.a: build/mySimpleComputer.o lib
	ar rc lib/libmySimpleComputer.a build/mySimpleComputer.o

build/mySimpleComputer.o: src/mySimpleComputer.c src/mySimpleComputer.h build
	gcc -Wall -Werror -c src/mySimpleComputer.c -o build/mySimpleComputer.o 

build: 
	mkdir build

bin:
	mkdir bin

lib:
	mkdir lib

clean: 
	rm -rf bin build lib *.bin

.PHONY: all clean 
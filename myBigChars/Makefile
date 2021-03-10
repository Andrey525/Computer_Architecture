
bin/prog: build/main.o lib/libmyBigChars.a bin
	gcc build/main.o -L./lib -lmyBigChars -o bin/prog

build/main.o: src/main.c src/myBigChars.h build
	gcc -Wall -Werror -c src/main.c -o build/main.o 

lib/libmyBigChars.a: build/myBigChars.o lib
	ar rc lib/libmyBigChars.a build/myBigChars.o

build/myBigChars.o: src/myBigChars.c src/myBigChars.h build
	gcc -Wall -Werror -c src/myBigChars.c -o build/myBigChars.o 

build: 
	mkdir build

bin:
	mkdir bin

lib:
	mkdir lib

clean: 
	rm -rf bin build lib *.bin

.PHONY: all clean 
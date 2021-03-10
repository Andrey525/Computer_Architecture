
bin/prog: build/main.o lib/libmyTerm.a lib/libmyBigChars.a bin
	gcc build/main.o -L./lib -lmyTerm -L./lib -lmyBigChars -o bin/prog

build/main.o: src/main.c src/myTerm.h src/myBigChars.h build
	gcc -Wall -Werror -c src/main.c -o build/main.o 

lib/libmyTerm.a: build/myTerm.o lib
	ar rc lib/libmyTerm.a build/myTerm.o

build/myTerm.o: src/myTerm.c src/myTerm.h build
	gcc -Wall -Werror -c src/myTerm.c -o build/myTerm.o 

lib/libmyBigChars.a: build/myBigChars.o build/myTerm.o lib
	ar rc lib/libmyBigChars.a build/myBigChars.o build/myTerm.o

build/myBigChars.o: src/myBigChars.c src/myBigChars.h src/myTerm.h build
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
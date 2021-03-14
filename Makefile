
bin/prog: build/main.o lib/libmySimpleComputer.a lib/libmyTerm.a lib/libmyBigChars.a bin
	gcc build/main.o -L./lib -lmySimpleComputer -L./lib -lmyTerm -L./lib -lmyBigChars -o bin/prog

lib/libmySimpleComputer.a: build/mySimpleComputer.o lib
	ar rc lib/libmySimpleComputer.a build/mySimpleComputer.o

lib/libmyTerm.a: build/myTerm.o lib
	ar rc lib/libmyTerm.a build/myTerm.o

lib/libmyBigChars.a: build/myBigChars.o build/myTerm.o lib
	ar rc lib/libmyBigChars.a build/myBigChars.o build/myTerm.o

build/main.o: src/main.c src/mySimpleComputer.h src/myTerm.h src/myBigChars.h build
	gcc -Wall -Werror -c src/main.c -o build/main.o 

build/mySimpleComputer.o: src/mySimpleComputer.c src/mySimpleComputer.h build
	gcc -Wall -Werror -c src/mySimpleComputer.c -o build/mySimpleComputer.o 

build/myTerm.o: src/myTerm.c src/myTerm.h build
	gcc -Wall -Werror -c src/myTerm.c -o build/myTerm.o

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

bin/prog: build/main.o build/Draw.o build/mysignal.o lib/libmySimpleComputer.a lib/libmyTerm.a lib/libmyBigChars.a lib/libmyReadkey.a bin
	gcc build/main.o build/Draw.o build/mysignal.o -L./lib -lmySimpleComputer -L./lib -lmyTerm -L./lib -lmyBigChars -L./lib -lmyReadkey -lm -o bin/prog

lib/libmySimpleComputer.a: build/mySimpleComputer.o lib
	ar rc lib/libmySimpleComputer.a build/mySimpleComputer.o

lib/libmyTerm.a: build/myTerm.o lib
	ar rc lib/libmyTerm.a build/myTerm.o

lib/libmyBigChars.a: build/myBigChars.o build/myTerm.o lib
	ar rc lib/libmyBigChars.a build/myBigChars.o build/myTerm.o

lib/libmyReadkey.a: build/myReadkey.o lib
	ar rc lib/libmyReadkey.a build/myReadkey.o

build/main.o: src/main.c src/mySimpleComputer.h src/myTerm.h src/myBigChars.h build
	gcc -Wall -Werror -c src/main.c -o build/main.o 

build/mySimpleComputer.o: src/mySimpleComputer.c src/mySimpleComputer.h build
	gcc -Wall -Werror -c src/mySimpleComputer.c -o build/mySimpleComputer.o 

build/myTerm.o: src/myTerm.c src/myTerm.h build
	gcc -Wall -Werror -c src/myTerm.c -o build/myTerm.o

build/myBigChars.o: src/myBigChars.c src/myBigChars.h src/myTerm.h build
	gcc -Wall -Werror -c src/myBigChars.c -o build/myBigChars.o

build/myReadkey.o: src/myReadkey.c src/myReadkey.h build
	gcc -Wall -Werror -c src/myReadkey.c -o build/myReadkey.o

build/Draw.o: src/Draw.c src/myBigChars.h src/myTerm.h src/mySimpleComputer.h src/myReadkey.h build
	gcc -Wall -Werror -c src/Draw.c -o build/Draw.o

build/mysignal.o: src/mysignal.c src/Draw.h src/mysignal.h src/mySimpleComputer.h build
	gcc -Wall -Werror -c src/mysignal.c -o build/mysignal.o

build: 
	mkdir build

bin:
	mkdir bin

lib:
	mkdir lib

clean: 
	rm -rf bin build lib *.bin

.PHONY: all clean 
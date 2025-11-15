o_file_build: main.c src/book.c src/management.c src/user.c
	gcc -c main.c -o bin/main.o
	gcc -c src/book.c -o bin/book.o
	gcc -c src/management.c -o bin/management.o
	gcc -c src/user.c -o bin/user.o

bin_file_build: bin/main.o bin/book.o bin/management.o bin/user.o 
	gcc -o main bin/main.o bin/book.o bin/management.o bin/user.o 

remove: bin/main.o bin/book.o bin/management.o bin/user.o 
	rm main bin/main.o bin/book.o bin/management.o bin/user.o 

all: o_file_build bin_file_build
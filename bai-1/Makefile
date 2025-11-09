o_file_build: main.c src/book.c src/management.c src/user.c
	gcc -c main.c -o main.o
	gcc -c src/book.c -o book.o
	gcc -c src/management.c -o management.o
	gcc -c src/user.c -o user.o

bin_file_build: main.o book.o management.o user.o 
	gcc -o main main.o book.o management.o user.o 

remove: main.o book.o management.o user.o 
	rm main main.o book.o management.o user.o 

all: o_file_build bin_file_build
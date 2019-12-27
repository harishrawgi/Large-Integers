a.out : main.o LargeInt.o utils.o
	gcc main.o LargeInt.o utils.o

main.o: main.c LargeInt.h
	gcc -c main.c

LargeInt.o : LargeInt.c LargeInt.h utils.h
	gcc -c LargeInt.c

utils.o : utils.c utils.h
	gcc -c utils.c

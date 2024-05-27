number=1

all: build
build:
	gcc -g main.c cozi.c -o clasament -lm -Wall
run:
	./clasament Input/test$(number).in testGraf.out testScor.out
clean:
	rm -f clasament r.out
valgrind:
	valgrind --leak-check=full --track-origins=yes ./clasament Input/test$(number).in testGraf.out testScor.out
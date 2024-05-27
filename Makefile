number=2

all: build
build:
	gcc -g main.c cozi.c -o clasament -Wall
run:
	./clasament Input/test$(number).in r.out
clean:
	rm -f clasament r.out
valgrind:
	valgrind --leak-check=full --track-origins=yes ./clasament Input/test$(number).in r.out
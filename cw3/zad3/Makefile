CFLAGS = -Wall
OPT_FLAGS =

all: zad3

zad3: zad3.c
	gcc $(CFLAGS) $(OPT_FLAGS) zad3.c -o zad3

test: zad3
	echo ------------------------
	./zad3 . abcdef
	echo ------------------------
	./zad3 .. abcdef
	echo ------------------------
	./zad3 /root abcdef
	echo ------------------------
	./zad3 .. \#include
	echo ------------------------

clean:
	rm -f zad3
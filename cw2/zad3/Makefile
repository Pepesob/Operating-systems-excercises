CFLAGS = -Wall
OPT_FLAGS =


all: directory

directory: directory.c
	gcc $(CFLAGS) $(OPT_FLAGS) directory.c -o directory

test: directory
	./directory
	wc --bytes *

clean:
	rm -f directory
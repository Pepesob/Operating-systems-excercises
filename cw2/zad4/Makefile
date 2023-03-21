CFLAGS = -Wall
OPT_FLAGS =

all: count

count: count.c
	gcc $(CFLAGS) $(OPT_FLAGS) count.c -o count

test: count
	./count ..
	find ../ | xargs wc --bytes
clean:
	rm -f count
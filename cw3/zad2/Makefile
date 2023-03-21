CFLAGS = -Wall
OPT_FLAGS =

all: zad2

zad2: zad2.c
	gcc $(CFLAGS) $(OPT_FLAGS) zad2.c -o zad2

test: zad2
	./zad2 ../empty_dir
	./zad2 ..
	./zad2 .

clean:
	rm -f zad2
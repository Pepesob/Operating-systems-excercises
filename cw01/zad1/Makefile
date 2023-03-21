CFLAGS = -Wall

all: libw_count.so stat_count.a

stat_count.o: count.c
	gcc $(CFLAGS) -o stat_count.o -c count.c

stat_count.a: stat_count.o
	ar rcs stat_count.a stat_count.o

w_count.o: count.c
	gcc $(CFLAGS) -fPIC -o w_count.o -c count.c

libw_count.so: w_count.o
	gcc $(CFLAGS) -shared w_count.o -o libw_count.so

clean:
	rm -f *.a *.o *.so
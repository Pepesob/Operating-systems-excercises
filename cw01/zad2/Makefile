CFLAGS = -Wall

all: main_stat main_wspoldz main_dynam

main_stat: main.o stat_count.o
	gcc $(CFLAGS) main.o stat_count.o -o main_stat

stat_count.o: count.c
	gcc $(CFLAGS) -o stat_count.o -c count.c

stat_count.a: stat_count.o
	ar rcs stat_count.a stat_count.o

main.o: main.c
	gcc $(CFLAGS) -c main.c

w_count.o: count.c
	gcc $(CFLAGS) -fPIC -o w_count.o -c count.c

libw_count.so: w_count.o
	gcc $(CFLAGS) -shared w_count.o -o libw_count.so

main_wspoldz: main.o libw_count.so
	gcc $(CFLAGS) main.o -L. -lw_count -Wl,-rpath=. -o main_wspoldz

main_dynam: main2.c libw_count.so
	gcc $(CFLAGS) main2.c -o main_dynam -ldl

clean:
	rm *.o *.so *.a
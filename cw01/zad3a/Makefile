CFLAGS = -Wall
OPT_FLAGS = 

all: main_stat main_wspoldz main_dynam

main_stat: main.o stat_count.o
	gcc $(CFLAGS) $(OPT_FLAGS) main.o stat_count.o -o main_stat.exe

stat_count.o: count.c
	gcc $(CFLAGS) $(OPT_FLAGS) -o stat_count.o -c count.c

stat_count.a: stat_count.o
	ar rcs stat_count.a stat_count.o

main.o: main.c
	gcc $(CFLAGS) $(OPT_FLAGS) -c main.c

w_count.o: count.c
	gcc $(CFLAGS) $(OPT_FLAGS) -fPIC -o w_count.o -c count.c

libw_count.so: w_count.o
	gcc $(CFLAGS) $(OPT_FLAGS) -shared w_count.o -o libw_count.so

main_wspoldz: main.o libw_count.so
	gcc $(CFLAGS) $(OPT_FLAGS) main.o -L. -lw_count -Wl,-rpath=. -o main_wspoldz.exe

main_dynam: main2.c libw_count.so
	gcc $(CFLAGS) $(OPT_FLAGS) main2.c -o main_dynam.exe -ldl

clean:
	rm -f *.o *.gch *.a *.so *.exe *.txt

test_stat: main_stat
	./main_stat.exe < test_commands.tst > results_static.txt

test_wspoldz: main_wspoldz
	./main_wspoldz.exe < test_commands.tst > results_shared.txt

test_dynam: main_dynam
	./main_dynam.exe < test_commands.tst > results_dynamic.txt

test: test_stat test_wspoldz test_dynam
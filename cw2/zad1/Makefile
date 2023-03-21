CFLAGS = -Wall
OPT_FLAGS =

all: zamiensys zamienlib

zamiensys: zamiensys.c
	gcc $(CFLAGS) $(OPT_FLAGS) zamiensys.c -o zamiensys

zamienlib: zamienlib.c
	gcc $(CFLAGS) $(OPT_FLAGS) zamienlib.c -o zamienlib

pomiar: zamiensys zamienlib
	./zamiensys c k zamiensys.c result1.txt > pomiar_zad_1.txt
	./zamienlib c k zamiensys.c result2.txt >> pomiar_zad_1.txt

porownaj: zamiensys zamienlib
	./zamiensys c 1 zamiensys.c plik_wyjściowy ; tr c 1 < zamiensys.c > tmp ; diff -s tmp plik_wyjściowy
	./zamienlib c 1 zamiensys.c plik_wyjściowy ; tr c 1 < zamiensys.c > tmp ; diff -s tmp plik_wyjściowy

clean:
	rm -f result1.txt result2.txt tmp zamienlib zamiensys plik_wyjściowy

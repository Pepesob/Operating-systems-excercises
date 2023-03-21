CFLAGS = -Wall
OPT_FLAGS =


all: reverse1 reverse2

reverse1: reverse1.c
	gcc $(CFLAGS) $(OPT_FLAGS) reverse1.c -o reverse1

reverse2: reverse2.c
	gcc $(CFLAGS) $(OPT_FLAGS) reverse2.c -o reverse2

pomiar: reverse1 reverse2
	./reverse1 test_file.txt result1.txt > pomiar_zad_2.txt
	./reverse2 test_file.txt result2.txt >> pomiar_zad_2.txt

test_podwojne_obrocenie1: reverse1
	./reverse1 reverse1 tmp1
	./reverse1 tmp1 tmp2
	diff -s tmp2 reverse1 || true

test_podwojne_obrocenie2: reverse2
	./reverse2 reverse2 tmp1
	./reverse2 tmp1 tmp2
	diff -s tmp2 reverse2 || true

test_tac_rev1: reverse1
	./reverse1 reverse1.c tmp
	tac < reverse1.c | rev > plik_wyjściowy
	diff -s tmp plik_wyjściowy || true

test_tac_rev2: reverse2
	./reverse2 reverse2.c tmp
	tac < reverse2.c | rev > plik_wyjściowy
	diff -s tmp plik_wyjściowy || true

test:
	make test_podwojne_obrocenie1
	make test_podwojne_obrocenie2
	make test_tac_rev1
	make test_tac_rev2
	echo Czasem wyskakują różnice między funkcjami wbudowanymi a moimi, ponieważ nie dodaję znaku końca linii na końcu pliku

clean:
	rm -f reverse1 reverse2 tmp tmp1 tmp2 plik_wyjściowy result1.txt result2.txt



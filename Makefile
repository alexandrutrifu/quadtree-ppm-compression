build:
	gcc -std=c99 -g -o quadtree main.c citirePPM.c alocari.c dezalocari.c constructie_arbore.c functii_c1.c compresie.c decompresie.c
run:
	./quadtree
clean:
	rm quadtree
valgrind:
	valgrind --leak-check=yes --track-origins=yes ./quadtree
/* TRIFU-URZICĂ Alexandru - 315CB */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX_LEN 25

typedef struct { /* matricea de pixeli */
	unsigned int red, green, blue;
} Pixel;

typedef struct nod { /* arborele */
	unsigned int red, green, blue;
	struct nod *unu, *doi, *trei, *patru;
} TNod, *TArb;

/* implementarea cozii */
typedef struct celula {
    TArb nod;
    struct celula *urm;
} TCelula, *TLista;

typedef struct coada {
    TLista inc, sf;
} TCoada;


/* citire .ppm */
void citirePPM(FILE *input, char **type, int *height, int *width, unsigned int *max_value, Pixel ***grid);

/* functii alocare */
Pixel **allocGrid(int height, int width);

/* funcții coadă */
TCoada* initQ();
int popQ(TCoada *coada, TArb *x);
int addQ(TCoada* coada, TArb x);

/* compresie & decompresie */
void compresie(TArb arb, FILE *output);
void evaluare_nod(FILE *input, TArb *arb, TCoada *coada);
TArb arbore_decomp(FILE *input, int *size);
void decompresie(Pixel **grid, TArb arb, unsigned int size, int x, int y);

/* construcție arbore*/
int medie(TArb *arb, Pixel **grid, int x, int y, int size, int factor);
TArb buildNod();
int buildArbore(TArb *arb, Pixel **grid, int size, int x, int y, int factor, int *latura_max);
void frunze(TArb arb, int crt, int *nr_frunze);
int niveluri(TArb arb);

/* dezalocare */
void dezalocGrid(Pixel ***grid, int height);
void distruge(TArb arb);
void DistrArb(TArb *arb);
void dezalocQ(TCoada **coada);
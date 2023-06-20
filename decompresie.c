/* TRIFU-URZICĂ Alexandru - 315CB */

#include "header.h"

/* evaluează tipul fiecărui nod în vederea citirii datelor din fișierul comprimat*/
void evaluare_nod(FILE *input, TArb *arb, TCoada *coada) {

	unsigned char tip;
	*arb = buildNod(); /* creez nodul */
	if (!arb) {
		return;
	}
	
	fread(&tip, sizeof(unsigned char), 1, input); /* evaluez tipul nodului */

	if (tip == 1) { /* nod frunză */

		fread(&((*arb)->red), sizeof(unsigned char), 1, input);
		fread(&((*arb)->green), sizeof(unsigned char), 1, input);
		fread(&((*arb)->blue), sizeof(unsigned char), 1, input);

	} else { /* nod intern*/
		int verif = addQ(coada, *arb);
		if (!verif) {
			return;
		}
	}
}

/* construiește arborele cuaternar pornind de la fișierul comprimat */
TArb arbore_decomp(FILE *input, int *size) {

	fread(size, sizeof(unsigned int), 1, input);

	TArb arb = buildNod();
	if (!arb) {
		return NULL;
	}

	unsigned char tip;

	fread(&tip, sizeof(unsigned char), 1, input); // tipul primului nod

	if (tip == 1) { /* arborele are un singur nod */

		fread(&(arb->red), sizeof(unsigned char), 1, input);
		fread(&(arb->green), sizeof(unsigned char), 1, input);
		fread(&(arb->blue), sizeof(unsigned char), 1, input);

	} else { /* altfel */

		TCoada *coada = initQ();
		int verif = addQ(coada, arb); /* adăugăm rădăcina în coadă */
		if (!verif) {
			return NULL;
		}

		TArb crt = NULL;

		while (coada->inc) { /* reconstruim arborele */
			
			verif = popQ(coada, &crt); /* extragem nodul ai cărui fii trebuie completați */
			if (!verif) {
				return NULL;
			}

			evaluare_nod(input, &(crt->unu), coada);
			evaluare_nod(input, &(crt->doi), coada);
			evaluare_nod(input, &(crt->trei), coada);
			evaluare_nod(input, &(crt->patru), coada);

		}

		dezalocQ(&coada);
	}

	return arb;
}

/* construiește matricea de pixeli pornind de la arborele cuaternar */
void decompresie(Pixel **grid, TArb arb, unsigned int size, int x, int y) {

	if (arb->unu == NULL) { /* dacă nodul e frunză */

		for (int i = x; i < x + size; i++) {

			for (int j = y; j < y + size; j++) {

				grid[i][j].red = arb->red;
				grid[i][j].green = arb->green;
				grid[i][j].blue = arb->blue;

			}

		}

	} else { /* dacă nodul e intern */

		size /= 2; /* parcurgem arborele în adâncime */

		decompresie(grid, arb->unu, size, x, y);
		decompresie(grid, arb->doi, size, x, y + size);
		decompresie(grid, arb->trei, size, x + size, y + size);
		decompresie(grid, arb->patru, size, x + size, y);

	}

}
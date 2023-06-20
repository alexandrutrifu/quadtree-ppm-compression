/* TRIFU-URZICĂ Alexandru - 315CB */

#include "header.h"

/* alocă memorie pentru matricea de pixeli */
Pixel **allocGrid(int height, int width) {

	/* alocarea memoriei pentru matricea de pixeli */
	Pixel **grid = (Pixel**) calloc(height, sizeof(Pixel*));
	
	if (!grid) {
		return NULL;
	}
	
	for (int i = 0; i < height; i++) {
		
		grid[i] = (Pixel*) calloc(width, sizeof(Pixel));
		
		/* eliberarea memoriei în cazul unei alocări nereușite */
		if (!grid[i]) {

			for (int j = 0; j < i; j++) {
				free(grid[j]);
			}
			free(grid);
			return NULL;

		}

	}

	return grid;
}

/* alocă memorie pentru un nod din arborele cuaternar */
TArb buildNod() {

	TArb nod = (TArb) malloc(sizeof(TNod));
	if (!nod) {
		return NULL;
	}
	
	nod->red = nod->green = nod->blue = 0;
	nod->unu = nod->doi = nod->trei = nod->patru = NULL;

	return nod;

}


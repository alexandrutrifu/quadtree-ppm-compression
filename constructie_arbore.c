/* TRIFU-URZICĂ Alexandru - 315CB */

#include "header.h"

/* calculează media culorilor din pătratul de dimensiune size + scorul de similitudine */
int medie(TArb *arb, Pixel **grid, int x, int y, int size, int factor) {

	unsigned long long red = 0, green = 0, blue = 0;

	for (int i = x; i < x + size; i++) { /* calculăm componentele mediei */

		for (int j = y; j < y + size; j++) {

			red += grid[i][j].red;
			green += grid[i][j].green;
			blue += grid[i][j].blue;

		}
	}

	red = (unsigned long long) (red / (size * size));
	green = (unsigned long long) (green / (size * size));
	blue = (unsigned long long) (blue / (size * size));

	unsigned long long similarity = 0;

	for (int i = x; i < x + size; i++) {

		for (int j = y; j < y + size; j++) {

			similarity += (red - grid[i][j].red) * (red - grid[i][j].red); 
			similarity += (green - grid[i][j].green) * (green - grid[i][j].green);
			similarity += (blue - grid[i][j].blue) * (blue - grid[i][j].blue);

		}
	}

	similarity /= (3 * size * size);

	if (similarity <= factor) {
		/* dacă nu e nevoie de divizare, colorăm frunza și returnăm 1 */
		(*arb)->red = red;
		(*arb)->green = green;
		(*arb)->blue = blue;

		return 1; 

	} else {
		/* dacă e nevoie de divizare, nodul rămâne alb și returnăm 0 */
		return 0;
	}
}

/* construiește arborele cuaternar pornind de la matricea de pixeli */
int buildArbore(TArb *arb, Pixel **grid, int size, int x, int y, int factor, int *latura_max) {

	*arb = buildNod();
	if (!arb) {
		return 0;
	}
	
	if (medie(arb, grid, x, y, size, factor)) { /* dacă nodul este frunză */
		
		if ((*latura_max) == 0) { /* dacă nu s-a construit prima frunză */
			*latura_max = size;
		} else {
			if ((*latura_max) < size) { // dacă se găsește ulterior un bloc nedivizat mai mare
				*latura_max = size;
			}
		}

	} else {

		size /= 2;
		buildArbore(&(*arb)->unu, grid, size, x, y, factor, latura_max);
		buildArbore(&(*arb)->doi, grid, size, x, y + size, factor, latura_max);
		buildArbore(&(*arb)->trei, grid, size, x + size, y + size, factor, latura_max);
		buildArbore(&(*arb)->patru, grid, size, x + size, y, factor, latura_max);

	}

	return 1;
}
/* TRIFU-URZICĂ Alexandru - 315CB */

#include "header.h"

int main(int argc, char const *argv[]) {

	if (strcmp(argv[1], "-d") != 0) {
		/* cerințele 1 și 2 - citire fișier .ppm + arbore cuaternar comun */

		/* inițializări */
		FILE *input = fopen(argv[3], "rb");
		char *type;
		int height, width;
		unsigned int max_value;
		Pixel **grid;

		/* citire date din fișier */
		citirePPM(input, &type, &height, &width, &max_value, &grid);
		
		/* construcția arborelui cuaternar */
		TArb arb;
		int latura_max = 0; /* reține latura asociată celei mai mari zone uniforme (prima frunză din arbore) */

		int verif = buildArbore(&arb, grid, height, 0, 0, atoi(argv[2]), &latura_max);
		if (!verif) {
			return 0;
		}
		
		if (strcmp(argv[1], "-c1") == 0) { /* pentru cerința 1 */

			int nr_niveluri = niveluri(arb);
			int nr_frunze = 0, crt = 0;

			frunze(arb, crt, &nr_frunze); /* extrage în nr_frunze numărul de frunze din arbore */

			/* furnizarea rezultatului */
			FILE *output = fopen(argv[4], "wt");
			fprintf(output, "%d\n%d\n%d\n", nr_niveluri, nr_frunze, latura_max);

			fclose(output);

		} else { /* pentru cerința 2 */

			FILE *output = fopen(argv[4], "wb");

			fwrite(&height, sizeof(unsigned int), 1, output);
			compresie(arb, output);

			fclose(output);
		}

		/* dezalocari */
		free(type);
		dezalocGrid(&grid, height);
		DistrArb(&arb);

		fclose(input);

	} else { /* cerința 3 */
		
		FILE *input = fopen(argv[2], "rb");
		FILE *output = fopen(argv[3], "wb");
		unsigned int size = 0;

		TArb arb = arbore_decomp(input, &size); /* reconstruim arborele cuaternar*/

		/* inserăm antetul fișierului .ppm*/
		fprintf(output, "P6\n");
		fprintf(output, "%u %u\n", size, size);
		fprintf(output, "255\n");

		/* construim matricea de pixeli */
		Pixel **grid = allocGrid(size, size);
		if (!grid)
			return 0;
		
		int x = 0, y = 0; /* coordonatele inițiale setate pe primul pixel */

		decompresie(grid, arb, size, x, y);

		/* printăm matricea în fișier */
		for (int i = 0; i < size; i++) {

			for (int j = 0; j < size; j++) {

				fwrite(&(grid[i][j].red), sizeof(unsigned char), 1, output);
				fwrite(&(grid[i][j].green), sizeof(unsigned char), 1, output);
				fwrite(&(grid[i][j].blue), sizeof(unsigned char), 1, output);

			}
		}

		dezalocGrid(&grid, size);
		DistrArb(&arb);

		fclose(input);
		fclose(output);
	}

	return 0;
}
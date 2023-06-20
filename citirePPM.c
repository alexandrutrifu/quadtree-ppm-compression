/* TRIFU-URZICĂ Alexandru - 315CB */

#include "header.h"

void citirePPM(FILE *input, char **type, int *height, int *width, unsigned int *max_value, Pixel ***grid) {

	*type = (char*) malloc(sizeof(char) * MAX_LEN);
	if (!*type) {
		return;
	}

	fscanf(input, "%s", *type); /* tipul fișierului .ppm*/

	/* citirea dimensiunilor matricei de pixeli + max_value */
	fscanf(input, "%d %d", width, height);
	fscanf(input, "%u", max_value);

	char str[MAX_LEN] = {'\0'};
	fgets(str, MAX_LEN, input); /* eliberăm rândul dinaintea matricei */
	
	*grid = allocGrid(*height, *width); /* alocăm matricea de pixeli */
	if (!*grid) {
		return;
	}

	/* citirea matricei de pixeli */
	for (int i = 0; i < *height; i++) {
		
		for (int j = 0; j < *width; j++) {

			fread(&((*grid)[i][j].red), sizeof(unsigned char), 1, input);
			fread(&((*grid)[i][j].green), sizeof(unsigned char), 1, input);
			fread(&((*grid)[i][j].blue), sizeof(unsigned char), 1, input);

		}

	}

}
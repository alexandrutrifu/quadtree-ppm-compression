/* TRIFU-URZICĂ Alexandru - 315CB */

#include "header.h"

/* dezalocă matricea de pixeli */
void dezalocGrid(Pixel ***grid, int height) {

	for (int i = 0; i < height; i++) {
		free((*grid)[i]);
	}
	free(*grid);
	*grid = NULL;

}

void distruge(TArb arb) /* functie auxiliara - distruge toate nodurile */
{
	if (!arb) return;

	distruge(arb->unu); /* distruge subarborele 1 */
	distruge(arb->doi); /* distruge subarborele 2 */
	distruge(arb->trei); /* distruge subarborele 3 */
	distruge(arb->patru); /* distruge subarborele 4 */

	free(arb); /* distruge nodul radacina */
}

void DistrArb(TArb *a) /* distruge toate nodurile arborelui de la adresa a */
{
	if (!(*a)) return; /* arbore deja vid */

	distruge(*a); /* distruge toate nodurile */
	
	*a = NULL; /* arborele este vid */
}

void dezalocQ(TCoada **coada) {

	TLista p, aux;
	p = (*coada)->inc;
	
	while(p) {
		aux = p;
		p = p->urm;
		free(aux);
	}

	free(*coada);
	*coada = NULL;

}
/* TRIFU-URZICĂ Alexandru - 315CB */

#include "header.h"

/* inițializare coadă */
TCoada* initQ() {

    TCoada *c = (TCoada*) malloc(sizeof(TCoada));
    if (!c) {
        return NULL;
    }

    c->inc = NULL;
    c->sf = NULL;

    return c;
}

/* inserare element în coadă */
int addQ(TCoada *coada, TArb x) {

    TLista aux = (TLista) malloc(sizeof(TCelula));
    if (!aux) {
        return 0;
    }

    aux->nod = x;
    aux->urm = NULL;

    if (coada->inc == NULL) {
        coada->inc = aux;
    } else {
        coada->sf->urm = aux;
    }
    coada->sf = aux;

    return 1;
}

/* extragere element din coadă */
int popQ(TCoada *coada, TArb *x) {

    if (coada->inc == NULL) {
        return 0;
    }

    TLista aux;
    aux = coada->inc;

    *x = aux->nod;
    coada->inc = aux->urm;
    if (coada->inc == NULL) {
        coada->sf = NULL;
    }
    free(aux);

    return 1;
}

/* parcurge în lățime arborele cuaternar și completează fișierul comprimat */
void compresie(TArb arb, FILE *output) {

	TCoada *coada = initQ();
    if (!coada) {
        return;
    }

	int verif = addQ(coada, arb); // adăugăm în coadă rădăcina arborelui
    if (!verif) {
        return;
    }

	TArb crt = NULL;

	while (coada->inc) { /* parcurgerea arborelui în lățime */

		verif = popQ(coada, &crt); /* extragem primul nod din coadă */
        if (!verif) {
            return;
        }

		if (crt->unu == NULL) { /* dacă nodul este frunză*/
			
			unsigned char tip = 1;

			fwrite(&tip, sizeof(unsigned char), 1, output);
			fwrite(&(crt->red), sizeof(unsigned char), 1, output);
			fwrite(&(crt->green), sizeof(unsigned char), 1, output);
			fwrite(&(crt->blue), sizeof(unsigned char), 1, output);
			
		} else {
			
			unsigned char tip = 0;

			fwrite(&tip, sizeof(unsigned char), 1, output);

			/* inserăm nodurile-fii în coadă */
			verif = addQ(coada, crt->unu);
            if (!verif) {
                return;
            }

			verif = addQ(coada, crt->doi);
            if (!verif) {
                return;
            }

			verif = addQ(coada, crt->trei);
            if (!verif) {
                return;
            }

			verif = addQ(coada, crt->patru);
            if (!verif) {
                return;
            }
		}
	}

    dezalocQ(&coada); // dezalocăm coada

}
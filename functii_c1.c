/* TRIFU-URZICĂ Alexandru - 315CB */

#include "header.h"

int niveluri(TArb arb) { /* funcție pentru numărul de niveluri */

    int n1, n2, n3, n4;

    if (arb == NULL) {
        return 0;
    }
    
    n1 = niveluri(arb->unu);
	n2 = niveluri(arb->doi);
	n3 = niveluri(arb->trei);
	n4 = niveluri(arb->patru);

	int Max = n1;

	if (Max < n2) Max = n2;
	if (Max < n3) Max = n3;
	if (Max < n4) Max = n4;

    return 1 + Max; 
}

void frunze(TArb arb, int crt, int *nr_frunze) {

	if (arb == NULL) {

		return;
	
	}

	/* dacă nodul este frunză */
	if (!arb->unu && !arb->doi && !arb->trei && !arb->patru) {

		(*nr_frunze)++;
	
	} else {

		frunze(arb->unu, crt + 1, nr_frunze);
		frunze(arb->doi, crt + 1, nr_frunze);
		frunze(arb->trei, crt + 1, nr_frunze);
		frunze(arb->patru, crt + 1, nr_frunze);

	}
}
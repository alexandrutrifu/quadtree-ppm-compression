## Fișierul `main.c`
---

Fișierul <mark>`main.c`</mark> este structurat pe două ramuri, conform celor trei cerințe ale temei (o ramură pentru cerințele -c1 și -c2, respectiv o altă ramură pentru cerința -c3).

## Compresie + Informații arbore:
---
Funcția <mark>`citirePPM()`</mark> (implementată în fișierul `citirePPM.c`) inițializează variabilele ce rețin dimensiunile matricei de pixeli și alocă memorie pentru aceasta din urmă. Pentru construcția matricei se definește tipul de date <mark>`Pixel`</mark>; astfel, unui element `grid[i][j]` îi vor fi asociate cele trei culori aferente codului său RGB.

În urma inițializărilor, se apelează funcția <mark>`buildArbore()`</mark> (implementată în fișierul `constructie_arbore.c`), care construiește un arbore cuaternar pornind de la matricea de pixeli obținută anterior.

### *Descriererea funcției* <mark style = 'background: rgba(247, 156, 118, 0.3)'>`buildArbore()`</mark>:
---
Funcția primește ca parametri următoarele valori:

- o variabilă de tipul `TArb`, în care se va returna, prin efect lateral, arborele cuaternar format;
- matricea de pixeli pe baza căreia se va construi arborele;
- dimensiunea matricei;
- pozițiile x și y de la care vor porni parcurgerile blocurilor de pixeli, pentru fiecare apel recursiv;
- pragul furnizat în vederea calculării scorului de similitudine;
- variabila `latura_max`, în care se va reține dimensiunea celui mai mare bloc de pixeli nedivizat;

La fiecare apel recursiv, se verifică, prin intermediul funcției <mark>`medie()`</mark> (implementată în același fișier `.c`), dacă blocul curent de pixeli trebuie (sau nu) divizat.

*Funcția <mark>`medie()`</mark> parcurge submatricea de pixeli asociată blocului curent și calculează (folosind formulele descrise în cerință) scorul de similitudine al acestuia din urmă. În plus, funcția returnează 1, în cazul în care pătratul de pixeli nu trebuie divizat (avem de a face cu o frunză căreia îi atribuim codul RGB corespunzător), sau 0, altfel*.

În cazul în care trebuie construită o frunză, verificăm dacă e necesară actualizarea valorii din variabila `latura_max`. Altfel, nodul curent este divizat în patru noduri-fii, fiecare dintre aceștia având dimensiunea înjumătățită (pozițiile x, respectiv y sunt de asemenea schimbate).

---

Odată construit arborele, programul abordează separat prima, respectiv cea de-a doua cerință:

1. Pentru prima cerință, se folosesc funcțiile <mark>`niveluri()`</mark> și <mark>`frunze()`</mark> (implementate în fișierul `functii_c1.c`) pentru a determina numărul de niveluri/frunze ale arborelui. La acestea se adaugă valoarea variabilei `lat_max`, calculată anterior.
2. Pentru cea de-a doua cerință, se apelează funcția <mark>`compresie()`</mark> (implementată în fișierul `compresie.c`).

### *Descriererea funcției* <mark style = 'background: rgba(247, 156, 118, 0.3)'>`compresie()`</mark>:
---
Funcția primește ca parametri arborele cuaternar creat, alături de un pointer la fișierul de output; aceasta utilizează o coadă pentru a parcurge în lățime arborele, completând datele de ieșire pe măsură ce tipul nodurilor este evaluat.

La finalul prelucrărilor, sunt realizate dezalocările necesare (funcții implementate în fișierul `dezalocari.c`).

## Decompresie:
---

### <mark style = 'background: rgba(247, 156, 118, 0.3)'>*1. Reconstrucția arborelui cuaternar:*</mark>

Pentru rezolvarea celei de-a treia cerințe, începem prin a reconstrui arborele cuaternar cu ajutorul funcției <mark>`arbore_decomp()`</mark> (implementată în fișierul `decompresie.c`). Aceasta primește ca parametri fișierul de input (care conține datele comprimate) și un pointer la variabila `size`, în care se va returna, prin efect lateral, dimensiunea matricei de pixeli (primul număr din fișierul comprimat).

Inițial, se citește din fișier tipul primului nod din arbore (rădăcina). Pe de o parte, tipul 1 sugerează că avem de a face cu un arbore care are un singur nod, caz în care trebuie citit un singur set de valori RGB. Pe de altă parte, tipul 0 ridică problema unui arbore cu un număr necunoscut de nivele, fiecare dintre acestea solicitând o evaluare ordonată.

Pentru cel din urmă caz, se utilizează o coadă în care introducem treptat nodurile interne ale arborelui, fii acestora fiind analizați apoi individual cu ajutorul funcției <mark>`evaluare_nod()`</mark>.

*Funcția <mark>`evaluare_nod()`</mark> construiește nodul curent, citește din fișier tipul acestuia și abordează cele două cazuri posibile:*

- *pentru tipul 1 (frunză), se continuă citirea din fișier a codului RGB asociat nodului;*
- *pentru tipul 0 (nod neterminal), se adaugă adresa nodului în coada amintită mai sus;*

În acest sens, utilizarea unei cozi permite construcția corectă a arborelui cuaternar, ținându-se cont de ordinea nodurilor de pe fiecare nivel, așa cum este sugerată aceasta în fișierul binar comprimat (se evită, astfel, problema alternanței dintre frunze și noduri interne).

### <mark style = 'background: rgba(247, 156, 118, 0.3)'>*2. Construcția matricei de pixeli:*</mark>

Odată reconstruit arborele cuaternar, poate fi apelată funcția <mark>`decompresie()`</mark> (implementată în fișierul `decompresie.c`). Aceasta primește următorii parametri:

- matricea-rezultat, aceasta având elemente de tip `Pixel`;
- arborele cuaternar generat;
- dimensiunea matricei (`size`);
- pozițiile de parcurgere x și y;

Funcția construiește matricea de pixeli în mod recursiv, după modelul următor:

- pentru fiecare nod intern al arborelui, avem de a face cu o zonă neuniformă a matricei finale; în consecință, înjumătățim dimensiunea blocului curent și tratăm cazurile fiecăreia dintre diviziunile acesteia (corespunzând celor 4 fii ai nodului prelucrat). Pentru fiecare dintre pătratele mai mici, funcția <mark>`decompresie()`</mark> se auto-apelează cu parametrii x și y actualizați conform poziției de început a blocului înaintat spre evaluare;

- pentru fiecare nod terminal al arborelui (frunză), se completează valorile pixelilor din submatricea aferentă zonei în care ne aflăm (aceasta fiind uniformă);

La finalul prelucrărilor, matricea de pixeli este printată în fișierul binar de output și sunt realizate dezalocările necesare (funcții implementate în fișierul `dezalocari.c`).

> ### ***Observație***: 
> Fișierul `header.h` conține definițiile structurilor folosite (coadă, arbore, tipul `Pixel`), alături de antetele tuturor funcțiilor întrebuințate.

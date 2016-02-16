/*
* Auteurs : Simon Paris / Gregory Robin
* 16/03/16
*
* fonctions relatives aux itérations de transfert de chaleur
*/

#include <stdio.h>

#include "matrix.h"


// transmet la chaleur verticalement
void verticale_iter_impair(struct Cell* matrix, int N);

// transmet la chaleur horizontalement
void horizontale_iter_pair(struct Cell* matrix, int N);

// execute une iteration, cad transfert horizontale, verticale, et temperature du centre remit a ca valeur T
void iter(struct Cell* matrix, int n, int N, float T, int nb_iter);

// instancie, initialise la matrice et lance les iterations
void run(int size, float T, int nb_iter, int print);
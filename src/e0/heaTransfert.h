/*
* Author : Simon Paris
* 2016-04-05
*
* fonctions relatives aux iterations de transfert de chaleur
*/
#include <stdio.h>

#include "../matrix.h"

// transmet la chaleur verticalement
void e0_verticale_iter_impair(struct Cell* matrix, int N, int miHeat, int maHeat);

// transmet la chaleur horizontalement
void e0_horizontale_iter_pair(struct Cell* matrix, int N);

// execute une iteration, cad transfert horizontale, verticale, et temperature du centre remit a ca valeur T
void e0_iter(struct Cell* matrix, int n, int N, int nb_iter, int print, int miHeat, int maHeat);

// instancie, initialise la matrice et lance les iterations
void e0_run(int size, int nb_iter, int print);

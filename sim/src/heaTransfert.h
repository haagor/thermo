#include <stdio.h>

#include "matrix.h"


void verticale_iter_impair(struct Cell* matrix, int N);

void horizontale_iter_pair(struct Cell* matrix, int N);

void iter(struct Cell* matrix, int n, int N, float T, int nb_iter);

void run(int size, float T, int nb_iter, int print);
#include <stdio.h>

struct Cell {
	float cell1;
	float cell2;
	int constant;
};

void print_matrix(struct Cell* matrix, int N, int even);

void init_matrix(int n, float T, struct Cell* matrix);

void rinit_matrix(int n, float T, struct Cell* matrix);
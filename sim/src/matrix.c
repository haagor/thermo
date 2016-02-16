#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"


void print_matrix(struct Cell* matrix, int N, int even)
{
	for (int row = 0; row < N; row++)
	{
		printf("\n");
		for (int column = 0; column < N; column++)
		{
			struct Cell* c = matrix + (row * N) + column;
			if (even)
			{
				printf("% 7.2f", c->cell2);
			} else {
				printf("% 7.2f", c->cell1);
			}
		}
	}
}

void init_matrix(int n, float T, struct Cell* matrix)
{
	int N = (1 << n) + 2;						// taille de la matrice	(+2 pour le bord froid)

	// calcul des cellules chauffées
	float heat = 1 << (n - 1);		
	int miHeat = heat - (1 << (n - 4));
	int maHeat = heat + (1 << (n - 4));

	int row, column;
	int hot, cold;
	struct Cell* c;
	for (row = 0; row < N; row++)	//init a retravailler pour heat
	{
		if (row > miHeat && row <= maHeat)
		{
			hot = 1;
		} else {
			hot = 0;
		}
		if (row == 0 || row == N-1)
		{
			cold = 1;
		} else {
			cold = 0;
		}
		for (column = 0; column < N; column++)
		{
			c = matrix + (row * N) + column;
			if (column > miHeat && column <= maHeat && hot)
			{
				c->cell1 = T;
				c->cell2 = T;
				c->constant = 1;
			} 
			else if (column == N - 1 || column == 0 || cold)
			{
				c->cell1 = 0;
				c->cell2 = 0;
				c->constant = 1;
			} else {
				c->cell1 = 0;
				c->cell2 = 0;
				c->constant = 0;
			}
		}
	}
}

void rinit_matrix(int n, float T, struct Cell* matrix)
{
	int N = (1 << n) + 2;						// taille de la matrice	(+2 pour le bord froid)

	// calcul des cellules chauffées
	float heat = 1 << (n - 1);		
	int miHeat = heat - (1 << (n - 4));
	int maHeat = heat + (1 << (n - 4));

	int row, column;
	int hot, cold;
	struct Cell* c;
	for (row = 0; row < N; row++)	//init a retravailler pour heat
	{
		if (row > miHeat && row <= maHeat)
		{
			hot = 1;
		} else {
			hot = 0;
		}
		if (row == 0 || row == N-1)
		{
			cold = 1;
		} else {
			cold = 0;
		}
		for (column = 0; column < N; column++)
		{
			c = matrix + (row * N) + column;
			if (column > miHeat && column <= maHeat && hot)
			{
				c->cell1 = T;
				c->cell2 = T;
				c->constant = 1;
			}
			else if (column == N-1 || column == 0 || cold)
			{
				c->cell1 = 0;
				c->cell2 = 0;
				c->constant = 1;
			}
		}
	}
}
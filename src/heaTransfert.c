/*
* Auteurs : Simon Paris / Gregory Robin
* 19/03/16
*
* fonctions relatives aux itérations de transfert de chaleur
*/

#include <stdio.h>
#include <stdlib.h>

#include "heaTransfert.h"


// transmet la chaleur verticalement
void verticale_iter_impair(struct Cell* matrix, int N)
{
	struct Cell* cUp;
	struct Cell* cDown;
	struct Cell* c;

	for (int row = 0; row < N; row++)
	{

		for (int column = 0; column < N; column++)
		{
			c = matrix + row * N + column;
			cUp = matrix + (row - 1) * N + column;
			cDown = matrix + (row + 1) * N + column;

			if (row == 0)
			{
				c->cell1 = (2 * (c->cell2 / 3)) + (cDown->cell2 / 6);
			}
			else if (row == N - 1)
			{
				c->cell1 = (2 * (c->cell2 / 3)) + (cUp->cell2 / 6);
			} else {
				c->cell1 = (2 * (c->cell2 / 3)) + (cUp->cell2 / 6) + (cDown->cell2 / 6);
			}
		}
	}
}

// transmet la chaleur horizontalement
void horizontale_iter_pair(struct Cell* matrix, int N)
{
	struct Cell* cLeft;
	struct Cell* cRight;
	struct Cell* c;

	for (int row = 0; row < N; row++)
	{

		for (int column = 0; column < N; column++)
		{
			c = matrix + (row * N) + column;
			cLeft = matrix + (row * N) + column - 1;
			cRight = matrix + (row * N) + column + 1;

			if (column == 0)
			{
				c->cell2 = (2 * (c->cell1 / 3)) + (cRight->cell1 / 6);
			}
			else if (column == N - 1)
			{
				c->cell2 = (2 * (c->cell1 / 3)) + (cLeft->cell1 / 6);
			} else {
				c->cell2 = (2 * (c->cell1 / 3)) + (cLeft->cell1 / 6) + (cRight->cell1 / 6);
			}
		}
	}
}

// execute une iteration, cad transfert horizontale, verticale, et temperature du centre remit a ca valeur T
void iter(struct Cell* matrix, int n, int N, float T, int nb_iter, int print)
{
	for (int w = 0; w < nb_iter; w++) // nombre d'itération verticale
	{
		horizontale_iter_pair(matrix, N);
		verticale_iter_impair(matrix, N);

		rinit_matrix(n, T, matrix);
	}
	if (print)
	{
		print_a(matrix, N, n-4);
	}
}

// instancie, initialise la matrice et lance les iterations
void run(int size, float T, int nb_iter, int print)
{
	int n = size + 4;							// [0-9]
	int N = (1 << n) + 2;						// taille de la matrice	(+2 pour le bord froid)
	struct Cell* matrice;						// instant matrice
	matrice = (struct Cell*)malloc(N*N*sizeof(struct Cell));
	if (matrice == 0)
	{
		fprintf(stderr, "core dump\n");
		return;
	}

	init_matrix(n, T, matrice);
	iter(matrice, n, N, T, nb_iter, print);

	free(matrice);
}
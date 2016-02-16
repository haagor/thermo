/*
* Auteurs : Simon Paris / Gregory Robin
* 16/03/16
*
* fonctions relatives aux matrices (initialisation, affichage...)
*/

#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"


// affiche la matrice de l'indice 0 a N, l'argument even sert a specifier la cellule cibler (0 pour cibler la cellule en fin d'iteration)
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

// initialise la matrice a 0 avec une temperature T au centre
void init_matrix(int n, float T, struct Cell* matrix)
{
	int N = (1 << n) + 2;	// taille de la matrice	(+2 pour les bords froid)

	// calcul des cellules chauffees
	float heat = 1 << (n - 1);		
	int miHeat = heat - (1 << (n - 4));
	int maHeat = heat + (1 << (n - 4));

	int row, column;
	int hot, cold;
	struct Cell* c;
	for (row = 0; row < N; row++)
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

// retablit la temperature T au centre de la matrice
void rinit_matrix(int n, float T, struct Cell* matrix)
{
	int N = (1 << n) + 2;	// taille de la matrice	(+2 pour le bord froid)

	// calcul des cellules chauffees
	float heat = 1 << (n - 1);		
	int miHeat = heat - (1 << (n - 4));
	int maHeat = heat + (1 << (n - 4));

	int row, column;
	int hot, cold;
	struct Cell* c;
	for (row = 0; row < N; row++)
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
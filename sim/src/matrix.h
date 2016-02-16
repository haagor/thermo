/*
* Auteurs : Simon Paris / Gregory Robin
* 16/03/16
*
* fonctions relatives aux matrices (initialisation, affichage...)
*/

#include <stdio.h>


struct Cell {
	float cell1;
	float cell2;
	int constant;
};

// affiche la matrice de l'indice 0 a N, l'argument even sert a specifier la cellule cibler (0 pour cibler la cellule en fin d'iteration)
void print_matrix(struct Cell* matrix, int N, int even);

// initialise la matrice a 0 avec une temperature T au centre
void init_matrix(int n, float T, struct Cell* matrix);

// retablit la temperature T au centre de la matrice
void rinit_matrix(int n, float T, struct Cell* matrix);
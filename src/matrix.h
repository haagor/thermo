/*
* Author : Simon Paris
* 2016-04-05
*
* fonctions relatives aux matrices (initialisation, affichage...)
*/

#ifndef MATRIX_H_
#define MATRIX_H_

#include <stdio.h>


struct Cell {
    float cell1;
    float cell2;
};


extern double TEMP_FROID;
extern double TEMP_CHAUD;

// affiche la matrice de l'indice 0 a N, l'argument even sert a specifier la cellule cibler (0 pour cibler la cellule en fin d'iteration)
void print_matrix(struct Cell* matrix, int N, int even);

// affiche la matrice pour satisfaire l'option -a
void print_a(struct Cell* matrix, int N, int s);

// initialise la matrice a 0 avec une temperature T au centre
void init_matrix(int n, struct Cell* matrix);

#endif

/*
* Author : Simon Paris
* 2016-04-05
*
* fonctions relatives aux iterations de transfert de chaleur
*/

#include <stdio.h>
#include <stdlib.h>

#include "heaTransfert.h"


// transmet la chaleur verticalement
void e0_verticale_iter_impair(struct Cell* matrix, int N, int miHeat, int maHeat)
{
    struct Cell* cUp;
    struct Cell* cDown;
    struct Cell* c;
    int hot;

    for (int row = 1; row < N - 1; row++)
    {
        if (row > miHeat && row <= maHeat)
        {
            hot = 1;
        } else {
            hot = 0;
        }
        for (int column = 1; column < N - 1; column++)
        {
            c = matrix + row * N + column;
            if (column > miHeat && column <= maHeat && hot)
            {
                c->cell1 = TEMP_CHAUD;
            } else {
                cUp = matrix + (row - 1) * N + column;
                cDown = matrix + (row + 1) * N + column;

                c->cell1 = (4 * c->cell2 + cUp->cell2 + cDown->cell2) / 6;
            }
        }
    }
}

// transmet la chaleur horizontalement
void e0_horizontale_iter_pair(struct Cell* matrix, int N)
{
    struct Cell* cLeft;
    struct Cell* cRight;
    struct Cell* c;

    for (int row = 1; row < N - 1; row++)
    {

        for (int column = 1; column < N - 1; column++)
        {
            c = matrix + (row * N) + column;
            cLeft = matrix + (row * N) + column - 1;
            cRight = matrix + (row * N) + column + 1;

            c->cell2 = (4 * c->cell1 + cLeft->cell1 + cRight->cell1) / 6;
        }
    }
}

// execute une iteration, cad transfert horizontale, verticale, et temperature du centre remit a ca valeur T
void e0_iter(struct Cell* matrix, int n, int N, int nb_iter, int print, int miHeat, int maHeat)
{
    for (int w = 0; w < nb_iter; w++) // nombre d'iteration verticale
    {
        e0_horizontale_iter_pair(matrix, N);
        e0_verticale_iter_impair(matrix, N, miHeat, maHeat);
    }
    if (print)
    {
        print_a(matrix, N, n-4);
        //print_matrix(matrix, N, 0);printf("\n");
    }
}

// instancie, initialise la matrice et lance les iterations
void e0_run(int size, int nb_iter, int print)
{
    int n = size + 4;							// [0-9]
    int N = (1 << n) + 2;					// taille de la matrice	(+2 pour le bord froid)
    int heat = 1 << (n - 1);
    int miHeat = heat - (1 << (n - 4));
    int maHeat = heat + (1 << (n - 4));
    struct Cell* matrice;						// instant matrice
    matrice = (struct Cell*)malloc(N*N*sizeof(struct Cell));
    if (matrice == 0)
    {
        fprintf(stderr, "core dump\n");
        return;
    }

    init_matrix(n, matrice);
    e0_iter(matrice, n, N, nb_iter, print, miHeat, maHeat);

    free(matrice);
}

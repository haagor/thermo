/*
* Author : Simon Paris
* 2016-03-08
*
* fonctions necessairent pour le calcule de moyenne
*/

#include <stdio.h>
#include <stdlib.h>

#include "utils.h"


// compare 2 doubles
int cmp_double (const void * a, const void * b)
{
    return ( *(double*)a - *(double*)b );
}

// calcule la moyenne d'une list de double en retirant le max et le min
double average(double* list, int n)
{
    qsort(list, n, sizeof(double), cmp_double);
    double res = 0;
    for (int i = 1; i < (n - 1); i++)
    {
        res += list[i];
    }
    res = res / (n - 2);
    return res;
}

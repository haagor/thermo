/*
* Author : Simon Paris
* 2016-03-08
*
* fonctions necessairent pour le calcule de moyenne
*/

#include <stdio.h>


// compare 2 doubles
int cmp_double (const void * a, const void * b);

// calcule la moyenne d'une list de double en retirant le max et le min
double average(double* list, int n);

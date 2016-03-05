/*
* Auteurs : Simon Paris / Gregory Robin
* 16/03/16
*
* fonctions necessairent pour le calcule de moyenn
*/

#include <stdio.h>


// compare 2 doubles
int cmp_double (const void * a, const void * b);

// calcule la moyenne d'une list de double en retirant le max et le min
double average(double* list, int n);
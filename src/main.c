#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int
main()
{

	int T = 36;
	float n = 4;						// [4-9]
	int N = pow(2,n);					// taille de la matrice
	int matrice[N][N];					// init matrice

	// calcul des cellules chauffées
	float heat = pow(2,(n - 1));		
	int miHeat = heat - pow(2,(n-4));
	int maHeat = heat + pow(2,(n-4));

	int row, column;
	int red = 0;
	for (row = 0; row < N; row++)
	{
		if (row >= miHeat && row <= maHeat)
		{
			red = 1;
		} else {
			red = 0;
		}
		printf("\n");
		for (column = 0; column < N; column++)
		{
			if (column >= miHeat && column <= maHeat && red)
			{
				matrice[row][column] = T;
			} else {
				matrice[row][column] = 0;
			}
			printf("%d	", matrice[row][column]);
		}
	}
	printf("\n");
}

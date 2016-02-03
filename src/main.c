#include <stdio.h>
#include <stdlib.h>

int
main()
{
	int n = 4;
	int matrice[n][n]; 

	int row, column;
	for (row = 0; row < n; row++)
	{
		printf("\n");
		for (column = 0; column < n; column++)
		{
			matrice[row][column] = 0;
			printf("%d	", matrice[row][column]);
		}
	}
	printf("\n");
}

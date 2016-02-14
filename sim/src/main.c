#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <getopt.h>
#include <time.h>
#include <sys/resource.h>

// https://www.cs.rutgers.edu/~pxk/416/notes/c-tutorials/getopt.html

struct Cell {
	float cell1;
	float cell2;
	int constant;
};

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

void init_matrix(int n, float T, struct Cell* matrix)
{
	int N = (1 << n) + 2;						// taille de la matrice	(+2 pour le bord froid)

	// calcul des cellules chauffées
	float heat = 1 << (n - 1);		
	int miHeat = heat - (1 << (n - 4));
	int maHeat = heat + (1 << (n - 4));

	int row, column;
	int hot, cold;
	struct Cell* c;
	for (row = 0; row < N; row++)	//init a retravailler pour heat
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

void rinit_matrix(int n, float T, struct Cell* matrix)
{
	int N = (1 << n) + 2;						// taille de la matrice	(+2 pour le bord froid)

	// calcul des cellules chauffées
	float heat = 1 << (n - 1);		
	int miHeat = heat - (1 << (n - 4));
	int maHeat = heat + (1 << (n - 4));

	int row, column;
	int hot, cold;
	struct Cell* c;
	for (row = 0; row < N; row++)	//init a retravailler pour heat
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

void iter(struct Cell* matrix, int n, int N, float T, int nb_iter)
{
	for (int w = 0; w < nb_iter; w++) // nombre d'itération verticale
	{
		horizontale_iter_pair(matrix, N);
		verticale_iter_impair(matrix, N);

		rinit_matrix(n, T, matrix);
	}
}

void run(int size, float T, int nb_iter, int print)
{
	int n = size + 4;							// [0-9]
	int N = (1 << n) + 2;						// taille de la matrice	(+2 pour le bord froid)
	struct Cell matrice[N*N];					// init matrice

	init_matrix(n, T, matrice);
	iter(matrice, n, N, T, nb_iter);
	if (print)
	{
		print_matrix(matrice, N, 0);
		printf("\n -------------------------------");
		printf("\n");
	}
}

int cmp_double (const void * a, const void * b)
{
	return ( *(double*)a - *(double*)b );
}

double average(double* list, int n)
{
	qsort(list, n, sizeof(double), cmp_double);
	double res = 0;
	for (int i = 1; i < (n - 1); i++)
	{
		res += list[i];
	}
	res = res /  (n - 2);
	return res;
}

int debug = 0;

int main(int argc, char *argv[])
{
	extern char *optarg;
	extern int optind;
	static char usage[] = "usage: %s -s sizes -i nb_iter  [-mM]\n";
	int c;
	char* sizes = 0;
	int nb_iter = -1;
	int cpu  = 0;
	int user = 0;
	while ((c = getopt(argc, argv, "s:i:mM")) != -1) {
		switch (c) {
			case 's':
			sizes=optarg;
			debug = 1;
			break;
			case 'i':
			nb_iter=atoi(optarg);
			debug = 1;
			break;
			case 'm':
			cpu = 1;
			break;
			case 'M':
			user = 1;
			break;
		}
	}
	if (sizes == 0) {
		fprintf(stderr, "%s: missing -s option\n", argv[0]);
		fprintf(stderr, usage, argv[0]);
		exit(1);
	}
	if (nb_iter == -1) {
		fprintf(stderr, "%s: missing -i option\n", argv[0]);
		fprintf(stderr, usage, argv[0]);
		exit(1);
	}

	printf("sizes = %s\n", sizes);
	printf("nb_iter = %d\n", nb_iter);
	printf("cpu = %d\n",  cpu);
	printf("user = %d\n", user);

	for (int i = 0; i < strlen(sizes); i++)
	{
		int size = sizes[i] - '0';

		double list_t[10];
		double list_c[10];
		time_t start_t, end_t;
		clock_t start_c, end_c;
		double total_t, total_c;

		int nb_globalIter = 1;
		if (cpu || user)
		{
			nb_globalIter = 10;
		}

		for (int i = 0; i < nb_globalIter; i++)
		{
			start_t = time(NULL);
			start_c = clock();
			run(size, 36, nb_iter, 0);
			end_t = time(NULL);
			end_c = clock();

			total_t = (double)(end_t - start_t);
			total_c = (double)(end_c - start_c) / CLOCKS_PER_SEC;			
			list_t[i] = total_t;
			list_c[i] = total_c;
		}

		total_t = average(list_t, 10);
		total_c = average(list_c, 10);
		printf("Size: %d, total time taken by user: %f\n", size, total_t);
		printf("Size: %d, total time taken by CPU: %f\n", size, total_c);
	}
}
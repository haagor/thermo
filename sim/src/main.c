#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <getopt.h>
#include <time.h>
#include <sys/resource.h>

#include "heaTransfert.h"


// https://www.cs.rutgers.edu/~pxk/416/notes/c-tutorials/getopt.html



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
		switch (c)
		{
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

		if (user == 1)
		{
			total_t = average(list_t, 10);
			printf("Size: %d, total time taken by user: %f\n", size, total_t);
		}
		if (cpu == 1)
		{
			total_c = average(list_c, 10);
			printf("Size: %d, total time taken by CPU: %f\n", size, total_c);
		}

// rapport occupation memoire
		struct rusage ru;
		getrusage(RUSAGE_SELF, &ru);
    	long maxrss = ru.ru_maxrss;
 		printf("RUSAGE :ru_maxrss => %ld [kilobytes], %ld [struct Cell], %d [nb Cell]\n", maxrss, maxrss / sizeof(struct Cell) * 1024, (2 + (1 << (size + 4))) * (2 + (1 << (size + 4))));
	}
}
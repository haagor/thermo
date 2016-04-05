/*
* Author : Simon Paris
* 2016-04-05
*
* fonctions relatives aux itérations de transfert de chaleur
*/

#include <stdio.h>
#define __USE_XOPEN2K 1
#include <pthread.h>

#include "../matrix.h"

// TODO ThreadArgs
struct SubMatrix {
    int x;
    int y;
    int size; // TODO pac
    struct Cell* matrix;
    int N;
    int miHeat;
    int maHeat;
    int nb_iter;
};

// Remplacement des pthread_barrier
struct my_barrier {
    int value;
    int max;
    pthread_mutex_t* mutex;
    pthread_cond_t*  cond;
};
int e2_pthread_barrier_init(struct my_barrier* barrier, int count);
int e2_pthread_barrier_destroy(struct my_barrier* barrier);
int e2_pthread_barrier_wait(struct my_barrier* barrier);

// transmet la chaleur verticalement
void e2_verticale_iter_impair(struct Cell* matrix, int x, int y, int pac,
                              int N, int miHeat, int maHeat);

// transmet la chaleur horizontalement
void e2_horizontale_iter_pair(struct Cell* matrix, int x, int y, int pac, int N);

// execute une iteration, cad transfert horizontale, verticale, et temperature du centre remit a ca valeur T
void e2_iter(struct Cell* matrix, struct SubMatrix* sub_mat,
             int n, int N, int nb_iter, int nb_thread, int print);

void* e2_thread_run(void* args);


void e2_fill_thread_array(pthread_t* threads, struct SubMatrix* thread_args,
                          struct Cell* matrix,
                          int n, int N,
                          int nb_iter, int matrix_size, int t);

void e2_print_array(struct SubMatrix* array, int t);

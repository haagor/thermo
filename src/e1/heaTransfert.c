/*
* Author : Simon Paris
* 2016-03-13
*
* fonctions relatives aux itérations de transfert de chaleur
*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "heaTransfert.h"


pthread_barrier_t* barrierV;
pthread_barrier_t* barrierH;


void e1_fill_thread_array(pthread_t* threads, struct SubMatrix* thread_args,
                          struct Cell* matrix, int n, int N, int nb_iter,
                          int matrix_size, int t)
{
    int rc;
    int sizeDiv = matrix_size / (1 << t);
    int threadIdx = 0;

    // le centre avec temperature T
    int heat = 1 << (n - 1);
    int miHeat = heat - (1 << (n - 4));
    int maHeat = heat + (1 << (n - 4));

    for (int x = 0; x < (1 << t); x++)
    {
        for (int y = 0; y < (1 << t); y++)
        {
            thread_args[threadIdx].x        = x * sizeDiv + 1;
            thread_args[threadIdx].y        = y * sizeDiv + 1;
            thread_args[threadIdx].size     = sizeDiv;
            thread_args[threadIdx].matrix   = matrix;
            thread_args[threadIdx].N        = N;
            thread_args[threadIdx].miHeat   = miHeat;
            thread_args[threadIdx].maHeat   = maHeat;
            thread_args[threadIdx].nb_iter  = nb_iter;

            rc = pthread_create(&threads[threadIdx], 0, e1_thread_run, &thread_args[threadIdx]);
            if (rc != 0) {
                fprintf(stderr, "error: pthread_create, rc: %d\n", rc);
                exit(1);
            }
            threadIdx++;
        }
    }
}

void e1_print_array(struct SubMatrix* array, int t)
{
    for (int i = 0; i < (1 << (t * 2)); i++)
    {
        printf("%d: %d %d %d\n", i, array[i].x, array[i].y, array[i].size);
    }
}

void* e1_thread_run(void* args)
{
    struct SubMatrix* sub_mat = (struct SubMatrix*)args;
    int ret;
    for (int w = 0; w < sub_mat->nb_iter; w++) // nombre d'itération verticale
    {
        e1_horizontale_iter_pair(sub_mat->matrix, sub_mat->x, sub_mat->y, sub_mat->size, sub_mat->N);
        ret = pthread_barrier_wait(barrierV);
        if (ret && ret != PTHREAD_BARRIER_SERIAL_THREAD) {
            fprintf(stderr, "waitG %d %d\n", ret, errno);
            exit(1);
        }

        e1_verticale_iter_impair(sub_mat->matrix, sub_mat->x, sub_mat->y, sub_mat->size,
                                 sub_mat->N,
                                 sub_mat->miHeat, sub_mat->maHeat);
        ret = pthread_barrier_wait(barrierH);
        if (ret && ret != PTHREAD_BARRIER_SERIAL_THREAD) {
            fprintf(stderr, "waitH %d %d\n", ret, errno);
            exit(1);
        }
    }
    pthread_exit(NULL);
    return 0;
}

// transmet la chaleur verticalement
void e1_verticale_iter_impair(struct Cell* matrix, int x, int y, int pac,
                              int N,
                              int miHeat, int maHeat)
{
    struct Cell* cUp;
    struct Cell* cDown;
    struct Cell* c;
    int hot;

    for (int row = y; row < y + pac; row++)
    {
        if (row > miHeat && row <= maHeat)
        {
            hot = 1;
        } else {
            hot = 0;
        }
        for (int column = x; column < x + pac; column++)
        {
            c = matrix + row * N + column;
            if (column > miHeat && column <= maHeat && hot)
            {
                c->cell1 = TEMP_CHAUD;
            } else {
                cUp   = matrix + (row - 1) * N + column;
                cDown = matrix + (row + 1) * N + column;

                c->cell1 = (4 * c->cell2 + cUp->cell2 + cDown->cell2) / 6;
            }
        }
    }
}

// transmet la chaleur horizontalement
void e1_horizontale_iter_pair(struct Cell* matrix, int x, int y, int pac, int N)
{
    struct Cell* cLeft;
    struct Cell* cRight;
    struct Cell* c;

    for (int row = y; row < y + pac; row++)
    {
        for (int column = x; column < x + pac; column++)
        {
            c = matrix + row * N + column;
            cLeft  = matrix + row * N + column - 1;
            cRight = matrix + row * N + column + 1;

            c->cell2 = (4 * c->cell1 + cLeft->cell1 + cRight->cell1) / 6;
        }
    }
}

// execute une iteration, cad transfert horizontale, verticale, et temperature du centre remit a ca valeur T
void e1_iter(struct Cell* matrix, struct SubMatrix* sub_mat,
             int n, int N, int nb_iter, int nb_thread, int print)
{
    int ret;
    for (int w = 0; w < nb_iter; w++) // nombre d'itération verticale
    {
        ret = pthread_barrier_wait(barrierV);
        if (ret && ret != PTHREAD_BARRIER_SERIAL_THREAD) {
            fprintf(stderr, "main waitG %d %d %d\n", ret, errno, w);
            exit(1);
        }

        ret = pthread_barrier_wait(barrierH);
        if (ret && ret != PTHREAD_BARRIER_SERIAL_THREAD) {
            fprintf(stderr, "main waitH %d %d %d\n", ret, errno, w);
            exit(1);
        }

        //print_matrix(matrix, N, 0);printf("\n");
    }
    if (print)
    {
        print_a(matrix, N, n-4);
        //print_matrix(matrix, N, 0);printf("\n");

    }
}

// instancie, initialise la matrice et lance les iterations
void e1_run(int size, int nb_iter, int nb_thread, int print)
{
    int n = size + 4;						  	// [0-9]
    int N = (1 << n) + 2;						// taille de la matrice	(+2 pour le bord froid)
    struct Cell* matrice;						// instant matrice

    struct SubMatrix sub_mat[1 << (nb_thread * 2)];
    pthread_t threads[1 << (nb_thread * 2)];
    barrierV = malloc(sizeof(pthread_barrier_t));
    barrierH = malloc(sizeof(pthread_barrier_t));

    // activer les barrieres avant de lancer les threads
    pthread_barrier_init(barrierV, 0, (1 << (nb_thread * 2)) + 1); // +1 thread main
    pthread_barrier_init(barrierH, 0, (1 << (nb_thread * 2)) + 1); // +1 thread main

    matrice = (struct Cell*)malloc(N*N*sizeof(struct Cell));
    if (matrice == 0)
    {
        fprintf(stderr, "core dump\n");
        return;
    }
    init_matrix(n, matrice);

    //printf("s:%d t:%d\n", size, nb_thread);
    //printf("s:%d t:%d nbCell: %d\n", 1 << (4 + size), 1 << (nb_thread * 2), (1 << (4 + size)) * (1 << (4 + size)));
    e1_fill_thread_array(threads, sub_mat, matrice, n, N, nb_iter, 1 << (4 + size), nb_thread);
    //print_array(sub_mat, nb_thread);

    e1_iter(matrice, sub_mat, n, N, nb_iter, nb_thread, print);
    //print_matrix(matrice, N, 0);printf("\n");

    free(matrice);
    pthread_barrier_destroy(barrierV);
    free(barrierV);
    pthread_barrier_destroy(barrierH);
    free(barrierH);
}

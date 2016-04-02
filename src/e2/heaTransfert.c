/*
* Author : Simon Paris
* 2016-03-13
*
* fonctions relatives aux itérations de transfert de chaleur
*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "heaTransfertInt.h"
#include "heaTransfert.h"

struct my_barrier* barrierG;
struct my_barrier* barrierH;
struct my_barrier* barrierV;

void e2_fill_thread_array(pthread_t* threads, struct SubMatrix* thread_args,
                          struct Cell* matrix, int N, int nb_iter,
                          int matrix_size, int t)
{
    int rc;
    int sizeDiv = matrix_size / (1 << t);
    int threadIdx = 0;
    for (int x = 0; x < (1 << t); x++)
    {
        for (int y = 0; y < (1 << t); y++)
        {
            thread_args[threadIdx].x        = x * sizeDiv + 1;
            thread_args[threadIdx].y        = y * sizeDiv + 1;
            thread_args[threadIdx].size     = sizeDiv;
            thread_args[threadIdx].matrix   = matrix;
            thread_args[threadIdx].N        = N;
            thread_args[threadIdx].nb_iter  = nb_iter;

            rc = pthread_create(&threads[threadIdx], 0, e2_thread_run, &thread_args[threadIdx]);
            if (rc != 0) {
                fprintf(stderr, "error: pthread_create, rc: %d\n", rc);
                exit(1);
            }
            threadIdx++;
        }
    }
}

void e2_print_array(struct SubMatrix* array, int t)
{
    for (int i = 0; i < (1 << (t * 2)); i++)
    {
        printf("%d: %d %d %d\n", i, array[i].x, array[i].y, array[i].size);
    }
}

void* e2_thread_run(void* args)
{
    struct SubMatrix* sub_mat = (struct SubMatrix*)args;
    int ret;
    for (int w = 0; w < sub_mat->nb_iter; w++) // nombre d'itération verticale
    {
        ret = e2_pthread_barrier_wait(barrierG);
        if (ret) {
            fprintf(stderr, "waitG %d %d\n", ret, errno);
            exit(1);
        }

        e2_horizontale_iter_pair(sub_mat->matrix, sub_mat->x, sub_mat->y, sub_mat->size, sub_mat->N);
        ret = e2_pthread_barrier_wait(barrierH);
        if (ret) {
            fprintf(stderr, "waitH %d %d\n", ret, errno);
            exit(1);
        }

        e2_verticale_iter_impair(sub_mat->matrix, sub_mat->x, sub_mat->y, sub_mat->size, sub_mat->N);
        ret = e2_pthread_barrier_wait(barrierV);
        if (ret) {
            fprintf(stderr, "waitV %d %d\n", ret, errno);
            exit(1);
        }
    }
    pthread_exit(NULL);
    return 0;
}

// transmet la chaleur verticalement
void e2_verticale_iter_impair(struct Cell* matrix, int x, int y, int pac, int N)
{
    struct Cell* cUp;
    struct Cell* cDown;
    struct Cell* c;

    for (int row = y; row < y + pac; row++)
    {
        for (int column = x; column < x + pac; column++)
        {
            c     = matrix + row       * N + column;
            cUp   = matrix + (row - 1) * N + column;
            cDown = matrix + (row + 1) * N + column;

            c->cell1 = (4 * c->cell2 + cUp->cell2 + cDown->cell2) / 6;
        }
    }
}

// transmet la chaleur horizontalement
void e2_horizontale_iter_pair(struct Cell* matrix, int x, int y, int pac, int N)
{
    struct Cell* cLeft;
    struct Cell* cRight;
    struct Cell* c;

    for (int row = y; row < y + pac; row++)
    {
        for (int column = x; column < x + pac; column++)
        {
            c      = matrix + row * N + column;
            cLeft  = matrix + row * N + column - 1;
            cRight = matrix + row * N + column + 1;

            c->cell2 = (4 * c->cell1 + cLeft->cell1 + cRight->cell1) / 6;
        }
    }
}

// execute une iteration, cad transfert horizontale, verticale, et temperature du centre remit a ca valeur T
void e2_iter(struct Cell* matrix, struct SubMatrix* sub_mat,
             int n, int N, float T, int nb_iter, int nb_thread, int print)
{
    int ret;
    for (int w = 0; w < nb_iter; w++) // nombre d'itération verticale
    {
        ret = e2_pthread_barrier_wait(barrierG);
        if (ret) {
            fprintf(stderr, "main waitG %d %d %d\n", ret, errno, w);
            exit(1);
        }
        /*ret = e2_pthread_barrier_destroy(barrierG);
        if (ret) {
            fprintf(stderr, "main destroyG %d %d\n", ret, errno);
            exit(1);
        }
        ret = e2_pthread_barrier_init(barrierG, (1 << (nb_thread * 2)) + 1);
        if (ret) {
            fprintf(stderr, "main initG %d %d\n", ret, errno);
            exit(1);
        }
        */

        ret = e2_pthread_barrier_wait(barrierH);
        if (ret) {
            fprintf(stderr, "main waitH %d %d %d\n", ret, errno, w);
            exit(1);
        }
        /*ret = e2_pthread_barrier_destroy(barrierH);
        if (ret) {
            fprintf(stderr, "main destroyH %d %d\n", ret, errno);
            exit(1);
        }
        ret = e2_pthread_barrier_init(barrierH, (1 << (nb_thread * 2)) + 1);
        if (ret) {
            fprintf(stderr, "main initH %d %d\n", ret, errno);
            exit(1);
        }
        */

        ret = e2_pthread_barrier_wait(barrierV);
        if (ret) {
            fprintf(stderr, "main waitV %d %d %d\n", ret, errno, w);
            exit(1);
        }
        /*ret = e2_pthread_barrier_destroy(barrierV);
        if (ret) {
            fprintf(stderr, "main destroyV %d %d\n", ret, errno);
            exit(1);
        }
        ret = e2_pthread_barrier_init(barrierV, (1 << (nb_thread * 2)) + 1);
        if (ret) {
            fprintf(stderr, "main initV %d %d\n", ret, errno);
            exit(1);
        }
        */
        //print_matrix(matrix, N, 0);printf("\n");

        rinit_matrix(n, T, matrix);
    }
    if (print)
    {
        print_a(matrix, N, n-4);
        //print_matrix(matrix, N, 0);printf("\n");

    }
}

// instancie, initialise la matrice et lance les iterations
void e2_run(int size, float T, int nb_iter, int nb_thread, int print)
{
    int n = size + 4;						  	// [0-9]
    int N = (1 << n) + 2;						// taille de la matrice	(+2 pour le bord froid)
    struct Cell* matrice;						// instant matrice

    struct SubMatrix sub_mat[1 << (nb_thread * 2)];
    pthread_t threads[1 << (nb_thread * 2)];

    // activer les barrieres avant de lancer les threads
    barrierG = (struct my_barrier*)malloc(sizeof(struct my_barrier));
    barrierG->mutex = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t));
    barrierG->cond = (pthread_cond_t*)malloc(sizeof(pthread_cond_t));

    barrierH = (struct my_barrier*)malloc(sizeof(struct my_barrier));
    barrierH->mutex = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t));
    barrierH->cond = (pthread_cond_t*)malloc(sizeof(pthread_cond_t));

    barrierV = (struct my_barrier*)malloc(sizeof(struct my_barrier));
    barrierV->mutex = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t));
    barrierV->cond = (pthread_cond_t*)malloc(sizeof(pthread_cond_t));

    e2_pthread_barrier_init(barrierG, (1 << (nb_thread * 2)) + 1); // +1 thread main
    e2_pthread_barrier_init(barrierH, (1 << (nb_thread * 2)) + 1); // +1 thread main
    e2_pthread_barrier_init(barrierV, (1 << (nb_thread * 2)) + 1); // +1 thread main

    matrice = (struct Cell*)malloc(N*N*sizeof(struct Cell));
    if (matrice == 0)
    {
        fprintf(stderr, "core dump\n");
        return;
    }
    init_matrix(n, T, matrice);

    //printf("s:%d t:%d\n", size, nb_thread);
    //printf("s:%d t:%d nbCell: %d\n", 1 << (4 + size), 1 << (nb_thread * 2), (1 << (4 + size)) * (1 << (4 + size)));
    e2_fill_thread_array(threads, sub_mat, matrice, N, nb_iter, 1 << (4 + size), nb_thread);
    //print_array(sub_mat, nb_thread);

    e2_iter(matrice, sub_mat, n, N, T, nb_iter, nb_thread, print);
    //print_matrix(matrice, N, 0);printf("\n");

    free(matrice);
    e2_pthread_barrier_destroy(barrierG);
    e2_pthread_barrier_destroy(barrierH);
    e2_pthread_barrier_destroy(barrierV);
}

int e2_pthread_barrier_init(struct my_barrier* barrier, int count)
{
    //fprintf(stderr, "init %d\n", count);

    int ret = 0;
    ret = pthread_mutex_init(barrier->mutex, 0);
    if (ret) return ret;

    ret = pthread_cond_init(barrier->cond, 0);

    barrier->value = 0;
    barrier->max   = count;

    return ret;
}

int e2_pthread_barrier_destroy(struct my_barrier* barrier)
{
    //fprintf(stderr, "destroy\n");

    int ret = 0;

    ret = pthread_cond_destroy(barrier->cond);
    if (ret) {
        fprintf(stderr, "destroy cond %d %d\n", ret, errno);
        return ret;
    }

    ret = pthread_mutex_destroy(barrier->mutex);
    if (ret) {
        fprintf(stderr, "destroy mutex %d %d %d\n", ret, errno, ret == EBUSY);
        return ret;
    }

    return 0;
}

int e2_pthread_barrier_wait(struct my_barrier* barrier)
{
    //fprintf(stderr, "wait %d\n", barrier->value);

    int ret = 0;
    ret = pthread_mutex_lock(barrier->mutex);
    if (ret) return ret;

    barrier->value++;
    if (barrier->value == barrier->max) {
        barrier->value = 0;
        ret = pthread_cond_broadcast(barrier->cond);
        if (ret) return ret;
        ret = pthread_mutex_unlock(barrier->mutex);
        if (ret) return ret;
        //fprintf(stderr, "release %d\n", barrier->value);
    } else {
        while (0 != barrier->value) {
            ret = pthread_cond_wait(barrier->cond, barrier->mutex);
            if (ret) return ret;
        }
        ret = pthread_mutex_unlock(barrier->mutex);
        if (ret) return ret;
    }
    return ret;
}


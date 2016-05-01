/*
* Author : Simon Paris
* 2016-04-05
*
* main
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <getopt.h>
#include <time.h>
#include <sys/resource.h>

#include "e0/heaTransfert.h"
#include "e1/heaTransfert.h"
#include "e2/heaTransfert.h"
#include "e3/heaTransfert.h"
#include "utils.h"

int debug = 0;
int main(int argc, char *argv[])
{

    // ----- gestion des arguments -----
    extern char *optarg;
    extern int optind;
    static char usage[] = "usage: %s -s sizes -i nb_iter -t nb_thread -e scenarios [-mMa]\n";
    int c;
    char* sizes = 0;
    char* nb_threads = 0;
    char* scenarios = 0;
    int cpu = 0;
    int user = 0;
    int print = 0;
    int nb_iter = -1;
    while ((c = getopt(argc, argv, "s:mMat:i:e:")) != -1) {
        switch (c)
        {
        case 's':
            sizes=optarg;
            debug = 1;
            break;
        case 'm':
            cpu = 1;
            break;
        case 'M':
            user = 1;
            break;
        case 'a':
            print=1;
            break;
        case 'i':
            nb_iter = atoi(optarg);
            debug = 1;
            break;
        case 't':
            nb_threads = optarg;
            break;
        case 'e':
            scenarios = optarg;
            break;
        default:
            fprintf(stderr, "%s: unknown option '%c'\n", argv[0], c);
            fprintf(stderr, usage, argv[0]);
            exit(1);
        }
    }
    if (sizes == 0) {
        fprintf(stderr, "%s: missing -s option\n", argv[0]);
        fprintf(stderr, usage, argv[0]);
        exit(1);
    }
    for (int sizeIdx = 0; sizeIdx < strlen(sizes); sizeIdx++)
    {
        if ('0' > sizes[sizeIdx] || sizes[sizeIdx] > '9')
        {
            fprintf(stderr, "%s: non numeric -s option\n", argv[0]);
            fprintf(stderr, usage, argv[0]);
            exit(1);
        }
    }

    if (nb_threads == 0) {
        fprintf(stderr, "%s: missing -t option\n", argv[0]);
        fprintf(stderr, usage, argv[0]);
        exit(1);
    }
    for (int nb_threadIdx = 0; nb_threadIdx < strlen(nb_threads); nb_threadIdx++)
    {
        if ('0' > nb_threads[nb_threadIdx] || nb_threads[nb_threadIdx] > '9')
        {
            fprintf(stderr, "%s: non numeric -t option\n", argv[0]);
            fprintf(stderr, usage, argv[0]);
            exit(1);
        }
    }

    if (nb_iter == -1) {
        fprintf(stderr, "%s: missing -i option\n", argv[0]);
        fprintf(stderr, usage, argv[0]);
        exit(1);
    }
    if (scenarios == 0) {
        fprintf(stderr, "%s: missing -e option\n", argv[0]);
        fprintf(stderr, usage, argv[0]);
        exit(1);
    }
    for (int scenarioIdx = 0; scenarioIdx < strlen(scenarios); scenarioIdx++)
    {
        if ('0' > scenarios[scenarioIdx] || scenarios[scenarioIdx] > '9')
        {
            fprintf(stderr, "%s: non numeric -e option\n", argv[0]);
            fprintf(stderr, usage, argv[0]);
            exit(1);
        }
    }

    // ----- boucle 'for' pour enchainer les etape (-e 0123) -----
    for (int scenarioIdx = 0; scenarioIdx < strlen(scenarios); scenarioIdx++)
    {
        int scenario = scenarios[scenarioIdx] - '0';
        if (scenario > 3) // TODO faire evoluer pour la suite
        {
            fprintf(stderr, "Scenario trop grand (%d)\n", scenario);
            continue;
        }

        // ----- boucle 'for' pour enchainer les executions (-s 024) -----
        for (int sizeIdx = 0; sizeIdx < strlen(sizes); sizeIdx++)
        {
            int size = sizes[sizeIdx] - '0';

            // ----- boucle 'for' pour -t (-t 012) -----
            for (int threadIdx = 0; threadIdx < strlen(nb_threads); threadIdx++)
            {
                int nb_thread = nb_threads[threadIdx] - '0';
                if (nb_thread > 5)
                {
                    fprintf(stderr, "Trop de threads (%d)\n", nb_thread);
                    continue;
                }

                // controle du nombre de cellule et de threads
                int threadCount = (1 << (2 * nb_thread));
                int cellCount = (1 << (size + 4)) * (1 << (size + 4));
                if (cellCount < threadCount)
                {
                    fprintf(stderr, "Trop de threads (%d) pour la taille donnee (%d)\n", nb_thread, size);
                    continue;
                }

                int localPrint = print;

                // ces 2 lists memorisent le temps cpu et user pour pouvoir calculer la moyenne
                double list_t[10];
                double list_c[10];

                time_t start_t, end_t;
                clock_t start_c, end_c;
                double total_t, total_c;

                int nb_globalIter = 1;
                if (cpu || user) // si il a l'option -m ou -M on execute 10 fois
                {
                    nb_globalIter = 10;
                }

                for (int i = 0; i < nb_globalIter; i++)
                {
                    start_t = time(NULL);
                    start_c = clock();
                    switch (scenario)
                    {
                    case 0:
                        e0_run(size, nb_iter, localPrint);
                        break;
                    case 1:
                        e1_run(size, nb_iter, nb_thread, localPrint);
                        break;
                    case 2:
                        e2_run(size, nb_iter, nb_thread, localPrint);
                        break;
                    case 3:
                        e3_run(size, nb_iter, nb_thread, localPrint);
                        break;
                    default:
                        fprintf(stderr, "Scenario inconnu (%d)\n", scenario);
                        continue;
                    }
                    localPrint = 0;         // il est inutile d'afficher les 10 matrices. On affiche la premiere
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
                    printf("e: %d, s: %d, t: %d, total time taken by user: %f\n", scenario, size, nb_thread, total_t);
                }
                if (cpu == 1)
                {
                    total_c = average(list_c, 10);
                    printf("e: %d, s: %d, t: %d, total time taken by CPU: %f\n", scenario, size, nb_thread, total_c);
                }

/*
                // Rapport: occupation memoire et ecriture dans un fichier pour constituer le rapport
                FILE *f = fopen("./res/res.txt", "a");
                if (f == NULL)
                {
                  printf("Error opening file!\n");
                  exit(1);
                }

                struct rusage ru;
                getrusage(RUSAGE_SELF, &ru);
                long maxrss = ru.ru_maxrss;
                printf("RUSAGE :ru_maxrss => %ld [kilobytes], %ld [struct Cell], %d [nb Cell]\n", maxrss, maxrss / sizeof(struct Cell) * 1024, (2 + (1 << (size + 4))) * (2 + (1 << (size + 4))));

                fprintf(f, "%d , %d , %d , %d , %f|%f - %ld\n", scenario, size, nb_thread, nb_iter, total_t, total_c, maxrss);
                fclose(f);

                if (scenario == 0)
                {
                    break;
                }
*/
            }
        }
    }
}

/*
 * Utilisation de optarg():
 * un programme qui reconnait trois options, a, b et c dont 
 * l'option c attend un argument. 
 */ 

#include <stdio.h>

int ligneMatrice,colonneMatrice;





main(int argc, char *argv[]){
  int c; 
  extern char * optarg; 
  extern int optind, opterr; 
  char * progname = argv[0];

  while ((c = getopt(argc , argv, "abc:")) != -1)
    switch (c) {
    case 's':
      printf("option s");
      break;
    case 'm':
      printf("option m");
      break;
    case 'a':
      printf("option a");
      break;
    case 'i':
      printf("option i");
      break;
    case 'e':
      printf("option e");
      break;
    case 't':
      printf("option t");
      break;
    default :
    printf("Pas d'option par défaut"); 
    break;

    }
  
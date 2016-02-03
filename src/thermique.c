/*
 * Utilisation de optarg():
 * un programme qui reconnait trois options, a, b et c dont 
 * l'option c attend un argument. 
 */ 

#include <stdio.h>
#include <stdlib.h>

int tailleMatrice;
float *Matrice;
extern char * optarg; 
extern int optind, opterr;

//calcul pour trouver la cellule d'une matrice taille*i+j

/*###################################################################
## Récupération des paramètre donnés lors du lancement du programme##
###################################################################*/


void getParameter(int argc, char *argv[]){
  int c,taille; 
  while ((c = getopt(argc , argv, "s:ma:i:e:t:")) != -1){
  switch (c) {
          case 's':
            taille=atoi(optarg);
            if(taille>9){
              printf("l'option s doit avoir une valeur entre 0 et9\n");
              break;
            }
            tailleMatrice=2<<(taille+3);
            break;
          case 'm':
            printf("Avec option mesure du temps d'execution\n");
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
  }
}


/*###################################################################
## Construction de la matrice##
## sera effectué avec un pointeur vers un float.
###################################################################*/

void constructionMatrice(int i){
    Matrice=(float*) malloc(i*i*sizeof(float));
}

void afficheMatrice(){
  int index,i,j;
  for(i=0; i<tailleMatrice;i++){
    for(j=0;j<tailleMatrice;j++){
      index=tailleMatrice*i+j;
      printf("%.2f ",Matrice[index]);
    }
    printf("\n");
  }
}

void libererMem(){
  free(Matrice);
}

int main(int argc, char *argv[]){
  getParameter(argc,argv);
  constructionMatrice(tailleMatrice);
  afficheMatrice();
}
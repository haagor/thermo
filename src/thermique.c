/*
 * Utilisation de optarg():
 * un programme qui reconnait trois options, a, b et c dont 
 * l'option c attend un argument. 
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <math.h>
#include "thermique.h"

#define TEMP_FROID 0
#define TEMP_CHAUD 256



int tailleMatrice,taille;
float *Matrice;
extern char * optarg; 
extern int optind, opterr;

int main(int argc, char *argv[]){
  getParameter(argc,argv);
  constructionMatrice(tailleMatrice);
  zoneChaude();
  afficheMatrice();
  libererMem();
}

//calcul pour trouver la cellule d'une matrice taille*i+j

/*###################################################################
## Récupération des paramètre donnés lors du lancement du programme##
###################################################################*/


void getParameter(int argc, char *argv[]){
  int c; 
  while ((c = getopt(argc , argv, "s:ma:i:e:t:")) != -1){
  switch (c) {
          case 's':
            taille=atoi(optarg)+4;
            if(taille>9){
              printf("ERREUR : La valeur de S doit être comprise entre 0 et 9\n");
              break;
            }
            tailleMatrice=2<<(taille-1);
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
/*###################################################################
## Methode pour afficher le quart sup de la matrice
###################################################################*/

void afficheMatrice(){
  int index;
  printf("\n");
  for(int i=0; i<(tailleMatrice/2);i++){
    for(int j=0;j<(tailleMatrice/2);j++){
      index=tailleMatrice*i+j;
      printf("%.2f ",Matrice[index]);
    }
    printf("\n");
  }
  printf("\n\n");
}

/*###################################################################
## fonction de calcul de la zone interne et insère valeur de TEMP_CHAUD
###################################################################*/
void zoneChaude(){
  int index;
  int centre,interval,zoneDeb, zoneFin;
  centre=(2<<(taille-2));
  if(taille>4){
  interval=(2<<(taille-5));
  }
  else{
    interval=1;
  }
  zoneDeb=centre-interval;
  zoneFin=centre+interval;
   for(int i=zoneDeb; i<zoneFin;i++){
    for(int j=zoneDeb;j<zoneFin;j++){
      index=tailleMatrice*i+j;
      Matrice[index]=TEMP_CHAUD;
    }
  }
}

void libererMem(){
  free(Matrice);
}
//################################################################################################################################



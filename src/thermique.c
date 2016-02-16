#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include "thermique.h"




int tailleMatrice,taille,zoneDeb,zoneFin;
Mat* Matrice;


int main(int argc, char *argv[]){
  getParameter(argc,argv);
  constructionMatrice(tailleMatrice);
  //initiateCold();
  zoneChaude();
  afficheCurrentMatrice();
  calcul();
 // zoneChaude();
  afficheNewMatrice();
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
          if(optarg>0){
                printf("seul l'option itératif est implémenter pour le moment.");
          }
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
    Matrice=(Mat*) malloc(i*i*sizeof(Mat));
}
/*###################################################################
## Methode pour afficher le quart sup de la matrice
###################################################################*/

void afficheCurrentMatrice(){
  int index;
  printf("\n");
  for(int i=0; i<(tailleMatrice);i++){
    for(int j=0;j<(tailleMatrice);j++){
      index=tailleMatrice*i+j;
      printf("%.2f ",Matrice[index].current);
    }
    printf("\n");
  }
  printf("\n\n");
}
void afficheNewMatrice(){
  int index;
  printf("\n");
  for(int i=0; i<(tailleMatrice);i++){
    for(int j=0;j<(tailleMatrice);j++){
      index=tailleMatrice*i+j;
      printf("%.2f ",Matrice[index].new);
    }
    printf("\n");
  }
  printf("\n\n");
}
void calcul(){
  //Calcul de la diffusion horiztontale
  for(int i=0; i<tailleMatrice;i++){
    for(int j=0;j<tailleMatrice;j++){
      if(j==0){
                Matrice[tailleMatrice*i+j].new=(float)TEMP_FROID/6;
      }
      else{
                Matrice[tailleMatrice*i+j].new=(Matrice[tailleMatrice*i+(j-1)].current)/6;
      }
        if(j==tailleMatrice-1){
           Matrice[tailleMatrice*i+j].new+=(float)TEMP_FROID/6;
        }
      else{    
          Matrice[tailleMatrice*i+j].new+=Matrice[tailleMatrice*i+(j+1)].current/6;
        }
    Matrice[tailleMatrice*i+j].new+=(Matrice[tailleMatrice*i+j].current*4)/6;

    }
  }
 /*//Calcul de la diffusion Verticale
for(int i=0; i<tailleMatrice;i++){
    for(int j=0;j<tailleMatrice;j++){
      if(i==0){
                Matrice[tailleMatrice*i+j].current=(float)TEMP_FROID/6;
      }
      else{
                Matrice[tailleMatrice*i+j].current=Matrice[tailleMatrice*(i-1)+j].new/6;
      }
        if(i==tailleMatrice-1){
           Matrice[tailleMatrice*i+j].current+=(float)TEMP_FROID/6;
        }
      else{    
          Matrice[tailleMatrice*i+j].current+=Matrice[tailleMatrice*(i+1)+j].new/6;
        }
    Matrice[tailleMatrice*i+j].current+=(Matrice[tailleMatrice*i+j].new*4)/6;

    }
  }*/
}


/*###################################################################
## fonction de calcul de la zone interne et insère valeur de TEMP_CHAUD
###################################################################*/
void zoneChaude(){
  int index;
  int centre,interval;
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
      Matrice[index].current=TEMP_CHAUD;
    }
  }
}
/*###################################################################
## initialisation de la temperature froide avec la valeur de TEMP_FROID
###################################################################
void initiateCold(){
  int index;
  for(int i=0; i<tailleMatrice;i++){
    for(int j=0;j<tailleMatrice;j++){
      index=tailleMatrice*i+j;
      Matrice[index].current=TEMP_FROID;
    }
  }
}
*/

void libererMem(){
  free(Matrice);
}
//################################################################################################################################



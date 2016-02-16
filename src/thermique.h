/*
 * Utilisation de optarg():
 * un programme qui reconnait trois options, a, b et c dont 
 * l'option c attend un argument. 
 */ 



#define TEMP_FROID 0
#define TEMP_CHAUD 36

typedef struct {
  float current;
  float new;
} Mat;

void getParameter(int argc, char *argv[]);
void constructionMatrice(int i);
void afficheMatrice();
void afficheCurrentMatrice();
void afficheNewMatrice();
void zoneChaude();
void initiateCold();
void libererMem();
void calcul();



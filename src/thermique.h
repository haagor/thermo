/*
 * Utilisation de optarg():
 * un programme qui reconnait trois options, a, b et c dont 
 * l'option c attend un argument. 
 */ 



#define TEMP_FROID 0
#define TEMP_CHAUD 256

void getParameter(int argc, char *argv[]);
void constructionMatrice(int i);
void afficheMatrice();
void zoneChaude();
void libererMem();



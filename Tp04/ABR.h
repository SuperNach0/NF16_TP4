#ifndef ABR_H_INCLUDED
#define ABR_H_INCLUDED


typedef struct T_feuille{
    char mot[20];
    struct T_feuille* pere;
    struct T_feuille* left;
    struct T_feuille* right;
}feuille;

typedef feuille * ABR;

feuille *creerfeuille (char *texte);
void ajoutMot (feuille **racine, char* mot);
feuille* rechercherMot (feuille *racine, char* mot);
feuille* rechercherMin (feuille *racine);
feuille* rechercherMax (feuille *racine);

feuille* rechercherMot2 (feuille **racine, char* mot);

void supprimerMot (feuille **racine, char* mot);

feuille* successeur (feuille *racine);
feuille* predecesseur (feuille *racine);

void afficherArbre (feuille *racine);


void ouvrir (feuille ** racine, FILE * fichier);
void quitter (feuille * racine, FILE * fichier );

void suggestionMots (int k, feuille *dico,char *souschaine);

void print (int k ,feuille *dico, char * souschaine);
void veridico (int k, feuille ** dico, char * souschaine);
void verimot (feuille ** dico);


#endif // ABR_H_INCLUDED

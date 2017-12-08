#ifndef ABR_H_INCLUDED
#define ABR_H_INCLUDED

typedef struct feuille
{
    char mot[20];
    struct feuille* pere;
    struct feuille* left;
    struct feuille* right;
}  feuille;

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

void print (int k ,feuille *dico, char * souschaine, int veri);





#endif // ABR_H_INCLUDED

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
feuille* rechercherMot2 (feuille **racine, char* mot);
void supprimerMot (feuille **racine, char* mot);

void afficherArbre (feuille *racine);
void afficherDec (feuille *racine, int *dec, int length, char* souschaine);

void ouvrir (feuille ** racine, FILE * fichier);
void quitter (feuille * racine, FILE * fichier );

void suggestionMots (int k, feuille *dico,char *souschaine);





#endif // ABR_H_INCLUDED

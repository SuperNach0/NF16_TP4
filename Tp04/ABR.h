#ifndef ABR_H_INCLUDED
#define ABR_H_INCLUDED


typedef struct T_feuille{
    char mot[20];
    struct T_feuille * pere;
    struct T_feuille * left;
    struct T_feuille * right;
}feuille;

typedef feuille *  ABR;

ABR creerfeuille (char *texte);
void ajoutMot (ABR *racine, char* mot);
ABR rechercherMot (ABR racine, char* mot);
ABR rechercherMin (ABR racine);
ABR rechercherMax (ABR racine);

ABR rechercherMot2 (ABR *racine, char* mot);

void supprimerMot (ABR *racine, char* mot);

ABR successeur (ABR racine);
ABR predecesseur (ABR racine);

void afficherArbre (ABR racine);


void ouvrir (ABR * racine, FILE * fichier);
void quitter (ABR  racine, FILE * fichier );

void suggestionMots (int k, ABR dico,char *souschaine);

void print (int k ,ABR dico, char * souschaine);
void veridico (int k, ABR * dico, char * souschaine);
void verimot (ABR * dico);


#endif // ABR_H_INCLUDED

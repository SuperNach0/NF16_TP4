#ifndef AL_H_INCLUDED
#define AL_H_INCLUDED

typedef struct T_cell{
    char c;
    struct T_cell * succ;
    struct T_cell * alt;
}Cellule;

typedef Cellule * Dico;

typedef struct T_mot{
    char c;
    struct T_mot * suivant;
}Mot;
typedef struct T_filtre{
    int (*fonction)(Mot,int);
    int param;
}Filtre;

Dico initDico2(Dico *dico, Mot mot);
Dico prefixeMot(Dico dico, Mot mot);
int rechercheMot2(Mot mot, Dico dico);
Dico ajoutMot2(Mot mot, Dico *dico);
Dico supprimeMot2(Mot mot, Dico dico);

void verimot2(Dico dico);
void veridico2(Dico dico);
void suggestionMot2(int k, Dico dico, Mot souschaine);
void printALFILTRE(Dico dico, Filtre filtre);
void printAL(Dico dico);


// Autres


typedef struct T_liste{
    struct T_liste *suivant;
    char * mot;
}ListeMot;

void writeFileListe(char * nomFichier, ListeMot * liste);
void writeFileAL(char * nomFichier, Dico dico);
void writeFileALrec(FILE * fichier, Dico dico, Mot mot);
void writeMot(Mot mot, FILE * fichier);
ListeMot * loadFileListe(char * nomFichier);
Dico loadFileAL(char * nomFichier);
void printALFILTREveridico(Dico * dico, Filtre filtre);
void printALrecFILTREveridico(Dico dico, Mot mot, Filtre filtre, Dico dico2);
void afficherMotveridico(Mot mot, Dico * dico);
int recsuggestionMot2(int k, Dico dico, Mot * souschaine, Mot mot, int n);
void printALrecFILTRE(Dico dico, Mot mot, Filtre filtre);
int nbLettre(Mot a, int param);
int commencePar(Mot a, int param);

Mot creerMotString(char* string);
void printALrec(Dico dico, Mot mot);
void afficherMot(Mot mot);
void cpMots(Mot *mot1, Mot mot2);
void ajouterLettreMot(Mot *mot, char lettre);
Dico recsupprimeMot2(Mot* mot, Dico dico);
Mot *creerMot(char c, Mot * suiv);
Cellule * creerCellule(char c, Cellule * alt, Cellule * succ);
void viderBuffer(void);

#endif // AL_H_INCLUDED


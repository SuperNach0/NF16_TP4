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
void ajouterfeuille (feuille **racine, char* mot);



#endif // ABR_H_INCLUDED

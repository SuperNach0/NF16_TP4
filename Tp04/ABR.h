#ifndef ABR_H_INCLUDED
#define ABR_H_INCLUDED

<<<<<<< HEAD
<<<<<<< HEAD
=======
typedef struct feuille{
	char* mot;
	struct feuille *father;
	struct feuille *lptr;
	struct feuille *rptr;
} feuille;
=======
typedef struct feuille
{
    char mot[20];
    struct feuille* pere;
    struct feuille* left;
    struct feuille* right;
}  feuille;
>>>>>>> cca1c59bfb42ed7805b969033b302dbb391f713f

typedef feuille * ABR;

feuille *creerfeuille (char *texte);
void ajoutMot (feuille **racine, char* mot);
feuille* rechercherMot (feuille *racine, char* mot);

>>>>>>> bd058210020c39d384109e2c6df6abc7714e1b87


#endif // ABR_H_INCLUDED

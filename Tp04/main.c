#include <stdio.h>
#include <stdlib.h>
#include "tp4.h"
#include "AL.h"
#include "ABR.h"


int main()
{
    feuille* racine = NULL;
    FILE* fichier = NULL;
    fichier = fopen("dicoErwan.txt", "r+");
    if (fichier != NULL){
        ouvrir(&racine,fichier);
    }
     else {
      perror ( fichier ); /* why didn't the file open? */
   }



    printf("okok \n");
    ajoutMot(&racine,"piiiuuuuiiiii");
    ajoutMot(&racine,"zizi");
    supprimerMot(&racine,"g");
    afficherArbre(racine);

    fichier = fopen("dicoErwan.txt", "w+");
    quitter(racine,fichier);
    fclose(fichier);
    return 0;
}

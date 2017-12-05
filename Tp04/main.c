#include <stdio.h>
#include <stdlib.h>
#include "tp4.h"
#include "AL.h"
#include "ABR.h"


int main()
{



    feuille* racine = NULL;



    printf("okok \n");
    ajoutMot(&racine,"f");
    ajoutMot(&racine,"d");
    ajoutMot(&racine,"a");
    ajoutMot(&racine,"b");
    ajoutMot(&racine,"p");
    ajoutMot(&racine,"z");
    ajoutMot(&racine,"q");
    supprimerMot(&racine,"a");
    ajoutMot(&racine,"e");
    ajoutMot(&racine,"o");
    ajoutMot(&racine,"y");
    ajoutMot(&racine,"d");
    ajoutMot(&racine,"c");








    //rechercherMot2(racine,"b");

    printf("\nfin");
    return 0;
}

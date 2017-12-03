#include <stdio.h>
#include <stdlib.h>
#include "tp4.h"
#include "AL.h"
#include "ABR.h"


int main()
{



    feuille* racine = NULL;



    printf("okok \n");
    ajoutMot(&racine,"lalala");
    ajoutMot(&racine,"lalala");
    ajoutMot(&racine,"a");
    ajoutMot(&racine,"b");
    ajoutMot(&racine,"p");
    ajoutMot(&racine,"z");
    ajoutMot(&racine,"q");
    ajoutMot(&racine,"n");
    rechercherMot(racine,"f");

    printf("\nfin");
    return 0;
}

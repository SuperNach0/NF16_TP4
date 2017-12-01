#include <stdio.h>
#include <stdlib.h>
#include "tp4.h"
#include "AL.h"
#include "ABR.h"


int main()
{



    feuille* racine = NULL;



    printf("okok \n");
    ajouterfeuille(&racine,"lalala");
    ajouterfeuille(&racine,"lalala");
    ajouterfeuille(&racine,"a");
    ajouterfeuille(&racine,"b");
    ajouterfeuille(&racine,"p");
    ajouterfeuille(&racine,"z");
    ajouterfeuille(&racine,"q");
    ajouterfeuille(&racine,"n");

    printf("\nfin");
    return 0;
}

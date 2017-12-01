#include <stdio.h>
#include <stdlib.h>
#include "tp4.h"
#include "AL.h"
#include "ABR.h"

Dico initDico2(Dico dico, Mot mot){
    Cellule * iteraCell, * iteraCell2;
    Mot * iteraMot = &mot;
    
    if (iteraMot != NULL){
        iteraCell = (Cellule *) malloc(sizeof(Cellule));
        iteraCell->c = iteraMot->c;
        iteraCell->alt = NULL;
        iteraCell->succ = NULL;
        dico.premier = iteraCell;
        iteraMot = iteraMot->suivant;
        
        while (iteraMot!=NULL){
            iteraCell2 = (Cellule *) malloc(sizeof(Cellule));
            iteraCell2->c = iteraMot->c;
            iteraCell2->alt = NULL;
            iteraCell2->succ = NULL;
            iteraMot = iteraMot->suivant;
            iteraCell->succ = iteraCell2;
            iteraCell = iteraCell2;
        }
        free(iteraCell2); free(iteraCell);
    }
    free(iteraMot);
    return dico;
}

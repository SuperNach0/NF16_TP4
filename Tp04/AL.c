#include <stdio.h>
#include <stdlib.h>
#include "tp4.h"
#include "AL.h"
#include "ABR.h"

Dico initDico2(Dico dico, Mot mot){
    Cellule * iteraCell, * iteraCell2;
    Mot * iteraMot = &mot;
    
    if (iteraMot != NULL){
        // On crée la première cellule, que l'on rattache à dico (premier emplacement)
        iteraCell = (Cellule *) malloc(sizeof(Cellule));
        iteraCell->c = iteraMot->c;
        iteraCell->alt = NULL;
        iteraCell->succ = NULL;
        dico.premier = iteraCell;
        iteraMot = iteraMot->suivant;
    
        // Ensuite on parcours le mot, et pour chaque lettre on crée une cellule, que l'on rattache à la cellule d'avant
        while (iteraMot!=NULL){
            iteraCell2 = (Cellule *) malloc(sizeof(Cellule));
            iteraCell2->c = iteraMot->c;
            iteraCell2->alt = NULL;
            iteraCell2->succ = NULL;
            iteraMot = iteraMot->suivant;
            iteraCell->succ = iteraCell2;
            iteraCell = iteraCell2;
        }
        
        // On fini le mot par un $, que l'on rattache
        iteraCell2 = (Cellule *) malloc(sizeof(Cellule));
        iteraCell2->c = '$';
        iteraCell2->alt = NULL;
        iteraCell2->succ = NULL;
        iteraMot = iteraMot->suivant;
        iteraCell->succ = iteraCell2;
        
        free(iteraCell2); free(iteraCell);
    }
    free(iteraMot);
    return dico;
}

Dico prefixeMot(Dico dico, Mot mot){
    int b = 1;
    Mot * monMot = &mot;
    Cellule * iteraCell = dico.premier;
    Dico prefixe;
    
    while (b){
        while ((iteraCell->c < monMot->c)||(iteraCell==NULL)){// On cherche la lettre alternative correspondant à la lettre du mot
            iteraCell = iteraCell->alt ;
        }
        if(iteraCell->c == monMot->c){// Si c'est égal on passe à la lettre suivante
            prefixe.premier = iteraCell;
            iteraCell = iteraCell->succ;
            if((monMot=monMot->suivant)==NULL){b=0;}
        }
        else{//Sinon on arrête, on a trouvé le prefixe
            b=0;
            free(iteraCell); free(monMot);
        }
    }
    return prefixe;
}

int rechercheMot2(Mot mot, Dico dico){
    Dico d = prefixeMot(dico, mot);
    if (d.premier->succ->c == '$'){
        return 1;
    }
    return 0;
}

Dico ajoutMot2(Mot mot, Dico dico){
    
}

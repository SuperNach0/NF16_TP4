#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tp4.h"
#include "ABR.h"

DicoABR initDico () {
 return NULL;
}



feuille * atacherfeuille (feuille * pere,char * mot) {
    feuille * new = malloc(sizeof *new);
    if (new != NULL){
        new->father = pere;
        new->mot = mot;
        new->lptr= NULL;
        new->rptr= NULL;
        return new;
    }
    else {
    printf("error création feuille MALLOC \n");
    return NULL;

    }
}


DicoABR  ajoutMot (DicoABR arbre,char * mot) {
    if (arbre==NULL){
        arbre = atacherfeuille(NULL,mot);
        printf("mot inséré\n");
    }
    else{
        printf("dazda");
    }
    return arbre;
}

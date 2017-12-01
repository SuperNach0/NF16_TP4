#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tp4.h"
#include "ABR.h"




feuille *creerfeuille (char *texte){
     feuille *nouv  = malloc(sizeof *nouv);
    if(nouv != NULL){

        strcpy(nouv->mot,texte);
        nouv->pere=NULL;
        nouv->left = NULL;
        nouv->right = NULL;
        return nouv;
    }
    else{
        printf("error malloc feuille\n");
        exit(1);
    }
}


void ajouterfeuille (feuille** racine, char* mot){
    if (*racine == NULL){
        printf("arbrevide \n");
        *racine = creerfeuille(mot);
        printf("insere premier \n");

    }
    else {
        printf("PAS VIDE\n");

        int gauche =0;
        feuille* it = *racine;
        feuille* pred = NULL;

        while (it!=NULL){

            if (strcmp(it->mot,mot)==0){printf("mot deja dans l'arbre \n"); return racine;}
            else if (strcmp(mot,it->mot)>0){
                printf("%s est plus grand que %s \n",mot,it->mot);
                pred = it;
                it = it->right;
                gauche =0;
            }
            else if (strcmp(mot,it->mot)<0){
                printf("%s est plus petit que %s \n",mot,it->mot);
                pred = it;
                it = it->left;
                gauche =1;
                }
        }
        if (gauche == 1){
            pred->left = creerfeuille(mot);
            pred->left->pere=pred;
            printf("insere a gauche de %s \n",pred->mot);
        }
        else{
           pred->right = creerfeuille(mot);
           pred->right->pere=pred;
           printf("insere a droite de %s\n",pred->mot);
        }
    }



}

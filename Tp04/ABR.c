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


void ajoutMot (feuille** racine, char* mot){
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

            if (strcmp(it->mot,mot)==0){printf("mot deja dans l'arbre \n"); return (void)0;}
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

feuille* rechercherMot (feuille *racine, char* mot){
     if (racine == NULL){
        printf("mot introuvable retourne NULL \n");
        return NULL;
    }
    else {
        if (strcmp(racine->mot,mot)==0){
             printf("mot trouve \n");
             return racine;
        }
        else if (strcmp(racine->mot,mot)<0){
            return rechercherMot(racine->right,mot);
        }
        else return rechercherMot(racine->left,mot);

    }

}

feuille* rechercherMin (feuille *racine){
    if (racine == NULL){
        printf("arbre vide\n");
        return NULL;
    }
    if (racine->left)
        rechercherMin(racine->left);
    else {
        printf("min de l'arbre : %s \n", racine->mot);
        return racine;

    }
}

feuille* rechercherMot2 (feuille **racine, char* mot){

    if (*racine == NULL){
        printf("arbre vide retourne NULL \n");
        return NULL;
    }

    else {
        feuille *it = *racine;
        while (it != NULL){
            if (strcmp(it->mot,mot)==0){
                printf("mot trouve\n");
                return it;
            }
            else if (strcmp(it->mot,mot)<0)
                it= it->right;
            else it=it->left;
        }
        printf("mot pas trouve NUll ret \n");
        return NULL;
    }
}

void supprimerMot (feuille **racine, char* mot){
    feuille * todelete =rechercherMot2(racine,mot);
    if (todelete == NULL){
        printf("supression : mot introuvable\n");
        return (void)0;
    }
    else {
       if(todelete->right && todelete->left){/// fils gauche et droit
        feuille* temp = rechercherMin(todelete->right);
        if (temp==todelete->right){
            todelete->right=temp->right;
            strcpy(todelete->mot,temp->mot);
            free(temp);
            printf("supression : il avait 2 fils\n");
            return (void)0;
        }
        else{
            strcpy(todelete->mot,temp->mot);
            temp->pere->left=temp->right;
            free(temp);
            printf("supression : il avait 2 fils\n");
            return (void)0;
        }
       }
       else {
            feuille * temp = todelete;
            if (todelete->right==NULL)
                todelete=todelete->left;
            else if (todelete->left==NULL)
                todelete=todelete->right;
            free(temp);
            printf("supression : il avait 1 fils\n");
            return (void)0;
       }


    }
}

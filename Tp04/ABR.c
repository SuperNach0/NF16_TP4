#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tp4.h"
#include "ABR.h"




feuille *creerfeuille (char *texte)
{
    feuille *nouv  = malloc(sizeof *nouv);
    if(nouv != NULL)
    {

        strcpy(nouv->mot,texte);
        nouv->pere=NULL;
        nouv->left = NULL;
        nouv->right = NULL;
        return nouv;
    }
    else
    {
        printf("error malloc feuille\n");
        exit(1);
    }
}


void ajoutMot (feuille** racine, char* mot)
{
    if (*racine == NULL)
    {
        printf("arbrevide \n");
        *racine = creerfeuille(mot);
        printf("insere premier \n");

    }
    else
    {
        //  printf("PAS VIDE\n");

        int gauche =0;
        feuille* it = *racine;
        feuille* pred = NULL;

        while (it!=NULL)
        {

            if (strcmp(it->mot,mot)==0)
            {
                printf("mot deja dans l'arbre \n");
                return (void)0;
            }
            else if (strcmp(mot,it->mot)>0)
            {
                // printf("%s est plus grand que %s \n",mot,it->mot);
                pred = it;
                it = it->right;
                gauche =0;
            }
            else if (strcmp(mot,it->mot)<0)
            {
                // printf("%s est plus petit que %s \n",mot,it->mot);
                pred = it;
                it = it->left;
                gauche =1;
            }
        }
        if (gauche == 1)
        {
            pred->left = creerfeuille(mot);
            pred->left->pere=pred;
            printf("%s insere a gauche de %s \n",mot,pred->mot);
        }
        else
        {
            pred->right = creerfeuille(mot);
            pred->right->pere=pred;
            printf("%s insere a droite de %s\n",mot,pred->mot);
        }
    }
}

feuille* rechercherMot (feuille *racine, char* mot)
{
    if (racine == NULL)
    {
        printf("mot introuvable retourne NULL \n");
        return NULL;
    }
    else
    {
        if (strcmp(racine->mot,mot)==0)
        {
            printf("mot trouve \n");
            return racine;
        }
        else if (strcmp(racine->mot,mot)<0)
        {
            return rechercherMot(racine->right,mot);
        }
        else return rechercherMot(racine->left,mot);

    }

}



feuille* rechercherMin (feuille *racine)
{
    if (racine == NULL)
    {
        //  printf("arbre vide\n");
        return NULL;
    }
    if (racine->left)
        return rechercherMin(racine->left);
    else
    {
        /// printf("min de l'arbre : %s \n", racine->mot);
        return racine;
    }
}


feuille* rechercherMax (feuille *racine)
{
    if (racine == NULL)
    {
        //  printf("arbre vide\n");
        return NULL;
    }
    if (racine->right)
        return rechercherMax(racine->right);
    else
    {
        /// printf("min de l'arbre : %s \n", racine->mot);
        return racine;
    }
}


feuille* rechercherMot2 (feuille **racine, char* mot)
{

    if (*racine == NULL)
    {
        printf("arbre vide retourne NULL \n");
        return NULL;
    }

    else
    {
        feuille *it = *racine;
        while (it != NULL)
        {
            if (strcmp(it->mot,mot)==0)
            {
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

void supprimerMot (feuille **racine, char* mot)
{
    feuille * todelete =rechercherMot2(racine,mot);
    if (todelete == NULL)
    {
        printf("supression : mot introuvable\n");
        return (void)0;
    }
    else
    {
        if(todelete->right && todelete->left) /// fils gauche et droit
        {
            feuille* temp = rechercherMin(todelete->right);
            if (temp==todelete->right)
            {
                todelete->right=temp->right;
                strcpy(todelete->mot,temp->mot);
                free(temp);
                ///   printf("supression : il avait 2 fils\n");
                return (void)0;
            }
            else
            {
                strcpy(todelete->mot,temp->mot);
                temp->pere->left=temp->right;
                free(temp);
                ///     printf("supression : il avait 2 fils\n");
                return (void)0;
            }
        }
        else
        {
            feuille * temp = todelete;
            if (todelete->right==NULL)
            {
                if (todelete->left==NULL) ///il n'a pas de fils
                {
                    ///      printf("il avait 0 fils \n");
                    if (todelete->pere->right==todelete) ///c'était un fils gauche ou droit ?
                    {
                        todelete->pere->right=NULL;
                    }
                    else
                        todelete->pere->left=NULL;
                    free(todelete);
                    return;
                }
                else /// il a un fils gauche
                {
                    if (todelete->pere->right==todelete)
                    {
                        todelete->pere->right=todelete->left;
                    }
                    else
                        todelete->pere->left=todelete->left;
                    ///  printf("supression : il avait 1 fils gauche \n");
                    free(todelete);
                    return;

                }

            }
            else ///il a un fils droit
            {
                if (todelete->pere->right==todelete)
                {
                    todelete->pere->right=todelete->right;
                }
                else
                    todelete->pere->left=todelete->right;
                ///   printf("supression : il avait 1 fils droit \n");
                free(todelete);
                return;

            }


            return (void)0;
        }
    }
}

void afficherArbre (feuille *racine)
{
    if (!racine) return ;
    if (racine->left) afficherArbre(racine->left);
    printf("%s\n",racine->mot);
    if (racine->right) afficherArbre(racine->right);

}


void ouvrir (feuille ** racine, FILE * fichier)
{
    char line [ 128 ];
    while ( fgets ( line, sizeof line, fichier ) != NULL )  //read a line
    {
        line[strlen(line)-1]='\0';///on elève le \n
        ajoutMot(racine,line);
    }
    return;
}

void quitter (feuille * racine, FILE * fichier )
{
    while (racine!=NULL)
    {
        fprintf(fichier,"%s\n",racine->mot);
        quitter(racine->left,fichier);
        quitter(racine->right,fichier);
        free(racine);
        return;
    }

}


feuille* successeur (feuille *racine)
{
    if (racine->right)
    {
        return rechercherMin(racine->right);
    }
    feuille *pere = racine->pere;
    while ((racine!=NULL)&& racine==pere->right)
    {
        racine = pere;
        pere=pere->pere;
    }
    return pere;
}

feuille* predecesseur (feuille *racine)
{
    if (racine->left)
    {
        return rechercherMax(racine->left);
    }
    feuille *pere = racine->pere;
    while ((racine!=NULL)&& racine==pere->left)
    {
        racine = pere;
        pere=pere->pere;
    }
    return pere;
}




void suggestionMots (int k, feuille *dico,char *souschaine)
{
    if (k<0)
    {
        afficherArbre(dico);
        return;
    }
    int i;
    if (k==0)
    {
        printf("fin des suggestion\n");
        return;
    }
    int lengthmax;
/// on va parcourir l'arbre pour trouver la sous chaine avec aussi un pred dans le cas ou elle exitste pas.
    if (dico==NULL)
    {
        printf("dico vide \n");
        return;
    }
    feuille *temp = dico;
    feuille *leplusproche =dico;
    for (i=1; i<=strlen(souschaine); i++)
    {
        while (temp!=NULL)
        {

            if (strncmp(souschaine,temp->mot,i)==0)
            {
                leplusproche=temp;
                lengthmax = i;
                printf("%s\n",leplusproche->mot);
                break;
            }
            else if(strncmp(souschaine,temp->mot,i)<0)
                temp=temp->left;
            else if (strncmp(souschaine,temp->mot,i)>0)
                temp=temp->right;
        }
    }
    if ((leplusproche==dico)&&(strncmp(souschaine,leplusproche->mot,1)!=0))
    {
        printf("pas de correspondance meme pour la premiere lettre \n");
        return;
    }
    // printf("suggestion : %s\n  sa longueur de sous chaine %d\n",leplusproche->mot,lengthmax);
    ///ICI on a la première occurence de la sous chaine (la plus grade trouvée)
    /// il faut chercher dans son sous arbre GAUCHE si il n'y a pas mieux !!
    temp=leplusproche;
    while(temp!=NULL)
    {
        if (strncmp(temp->mot,souschaine,lengthmax)==0) ///c'est plus petit et a aussi la sous chaine
        {
            leplusproche=temp;
        }
        temp=temp->left;
    }

    // afficherArbre(leplusproche->left);
    printf("\n");
    printf(" \n%s\n",leplusproche->mot);///c'est lui le plus proche !
    k--;
    if (k==0)
    {
        printf("fin des suggestion\n");
        return;
    }
    feuille * suc = successeur(leplusproche);
    while ((k!=0)&&(strncmp(suc->mot,souschaine,lengthmax)==0))
    {
        printf("%s\n",suc->mot);
        suc=successeur(suc);
        k--;
    }


    printf("fin des suggestion\n");
    return;
}


void print (int k,feuille *dico, char * souschaine)
{
    int lengthmax;
    feuille *temp = dico;
    feuille *leplusproche =dico;
    while ((leplusproche!=NULL)&& (strncmp(leplusproche->mot,souschaine,strlen(souschaine))!=0) )
    {

        if (strcmp(leplusproche->mot,souschaine)<0)
        {
            temp=leplusproche;
            leplusproche=leplusproche->right;
        }

        else if (strcmp(leplusproche->mot,souschaine)>0)
        {
            temp=leplusproche;
            leplusproche=leplusproche->left;

        }
    }
    //printf("\nhihi\n");

    if (leplusproche==NULL)
    {
        leplusproche=successeur(temp);
    }
    feuille *max =rechercherMax(dico);
    printf("voici les mots les plus proches :\n");
    while ((leplusproche!=NULL)&&(k!=0))
    {
        printf("%s\n",leplusproche->mot);
        k--;
        if (leplusproche==max) return;
        leplusproche=successeur(leplusproche);
    }
    return;

}

void veridico (int k, feuille ** dico, char * souschaine)
{
    int lengthmax;
    feuille* temp = *dico;
    feuille* leplusproche = *dico;
    while ((leplusproche!=NULL)&& (strncmp(leplusproche->mot,souschaine,strlen(souschaine))!=0) )
    {

        if (strcmp(leplusproche->mot,souschaine)<0)
        {
            temp=leplusproche;
            leplusproche=leplusproche->right;
        }

        else if (strcmp(leplusproche->mot,souschaine)>0)
        {
            temp=leplusproche;
            leplusproche=leplusproche->left;

        }
    }
    if (leplusproche==NULL)
    {
        leplusproche=successeur(temp);
    }

    feuille *max =rechercherMax(dico);

    while ((leplusproche!=NULL)&&(k!=0))
    {
        int choix;
        printf("%s\n",leplusproche->mot);
        printf("que voulez vous faire avec ce mot ? \n");
        printf("1- corriger ce mot\n2- supprimer ce mot\n3- valider ce mot  \n4- quitter la fonction\n");
        scanf("%d",&choix);
        switch (choix)
        {
        case 1 :
        {
            printf("corrigez le mot : \n");
            char nouveau[30];
            scanf("%s",&nouveau);
            temp= predecesseur(leplusproche);
            supprimerMot(dico,leplusproche->mot);
            ajoutMot(dico,nouveau);
            leplusproche=temp;
            break;
        }
        case 2 :
        {
            temp= predecesseur(leplusproche);
            supprimerMot(dico,leplusproche->mot);
            leplusproche=temp;
            break;
        }
        case 3 :
        {
            break;
        }
        case 4 :
        {
            return;
        }

        }
        k--;
        if (leplusproche==max) return;
        leplusproche=successeur(leplusproche);
    }
    return;


}

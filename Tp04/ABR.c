#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "tp4.h"
#include "ABR.h"




ABR creerfeuille (char *texte)
{
    ABR nouv  = malloc(sizeof *nouv);
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

feuille* rechercherMot (ABR racine, char* mot)
{
    if (racine == NULL)
    {
        //  printf("mot introuvable retourne NULL \n");
        return NULL;
    }
    else
    {
        if (strcmp(racine->mot,mot)==0)
        {
            //printf("mot trouve \n");
            return racine;
        }
        else if (strcmp(racine->mot,mot)<0)
        {
            return rechercherMot(racine->right,mot);
        }
        else return rechercherMot(racine->left,mot);

    }

}



feuille* rechercherMin (ABR racine)
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


feuille* rechercherMax (ABR racine)
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


feuille* rechercherMot2 (ABR *racine, char* mot)
{

    if (*racine == NULL)
    {
        //  printf("arbre vide retourne NULL \n");
        return NULL;
    }

    else
    {
        ABR it = *racine;
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
        //  printf("mot pas trouve NUll ret \n");
        return NULL;
    }
}

void supprimerMot (ABR *racine, char* mot)
{
    feuille* todelete =rechercherMot(*racine,mot);
    printf("%s\n", todelete->mot);
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
                temp->right->pere=todelete;
                strcpy(todelete->mot,temp->mot);
                free(temp);
                /// printf("supression : il avait 2 fils\n");
                return (void)0;
            }
            else
            {
                strcpy(todelete->mot,temp->mot);
                temp->pere->left=temp->right;
                temp->right->pere=temp->pere;
                free(temp);
                ///     printf("supression : il avait 2 fils\n");
                return (void)0;
            }
        }
        else
        {
            ABR  temp = todelete;
            if (todelete->right==NULL)
            {
                if (todelete->left==NULL) ///il n'a pas de fils
                {
                    //  printf("il avait 0 fils \n");
                    if (todelete->pere->right==todelete) ///c'était un fils gauche ou droit ?
                    {
                        printf("cetait un fils droit\n");
                        todelete->pere->right=NULL;

                    }
                    else
                    {
                        //    printf("cetait un fils gauche\n");
                        todelete->pere->left=NULL;
                        //printf("ici\n");
                    }

                    free(todelete);

                    printf("ici\n");
                    return;
                }
                else /// il a un fils gauche
                {
                    printf("supression : il avait 1 fils gauche :%s\n",todelete->left->mot);
                    if (todelete->pere->right==todelete)
                    {
                        printf("c'etait un fdroit\n");

                        todelete->pere->right=todelete->left;
                        todelete->left->pere=todelete->pere;

                    }
                    else
                    {
                        todelete->pere->left=todelete->left;
                        todelete->left->pere=todelete->pere;
                    }
                    printf("avant free\n");
                    printf("%s\n",todelete->mot);
                    free(todelete);
                    todelete=NULL;///au cas ou
                    return;

                }

            }
            else ///il a un fils droit
            {
                if (todelete->pere->right==todelete)
                {
                    todelete->pere->right=todelete->right;
                    todelete->right->pere=todelete->pere;
                }
                else
                    todelete->pere->left=todelete->right;
                todelete->right->pere=todelete->pere;
                ///   printf("supression : il avait 1 fils droit \n");
                free(todelete);
                todelete=NULL;///au cas ou
                return;

            }


            return (void)0;
        }
    }
}

void afficherArbre (ABR racine)
{
    if (!racine) return ;
    if (racine->left) afficherArbre(racine->left);
    printf("%s\n",racine->mot);
    if (racine->right) afficherArbre(racine->right);

}


void ouvrir (ABR * racine, FILE * fichier)
{
    char line [ 128 ];
    while ( fgets ( line, sizeof line, fichier ) != NULL )  //read a line
    {
        line[strlen(line)-1]='\0';///on elève le \n
        ajoutMot(racine,line);
    }
    return;
}

void quitter (ABR  racine, FILE * fichier )
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


feuille* successeur (ABR racine)
{
    if (racine->right)
    {
        return rechercherMin(racine->right);
    }
    ABR pere = racine->pere;
    while ((racine!=NULL)&& racine==pere->right)
    {
        racine = pere;
        pere=pere->pere;
    }
    return pere;
}

feuille* predecesseur (ABR racine)
{
    if (racine->left)
    {
        return rechercherMax(racine->left);
    }
    ABR pere = racine->pere;
    while ((racine!=NULL)&& racine==pere->left)
    {
        racine = pere;
        pere=pere->pere;
    }
    return pere;
}




void suggestionMots (int k, ABR dico,char *souschaine)
{
    ABR  sauvegarde [20];
    int Lmax [20];
    int j=0;
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
    ABR temp = dico;
    ABR leplusproche =dico;
    for (i=1; i<=strlen(souschaine); i++)
    {
        while (temp!=NULL)
        {


            if (strncmp(souschaine,temp->mot,i)==0)
            {
                leplusproche=temp;
                sauvegarde[j]=leplusproche;
                Lmax [j] = i;
                j++;
                lengthmax = i;
                //printf("%s\n",leplusproche->mot);
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
    int z=0;
    for (i=j-1; i>=0; i--)
    {
        temp=sauvegarde[i];
        lengthmax=Lmax[i];

        if (strcmp(temp,souschaine)!=0){
        while(strncmp(predecesseur(temp),temp,lengthmax)==0)
        {
            temp=predecesseur(temp);
        }
        leplusproche=temp;
        }
        if (k<1)
        {
            printf("fin des suggestion\n");
            return;
        }





        ABR  suc = leplusproche;
        while ((k!=0)&&(strncmp(suc->mot,souschaine,lengthmax)==0))
        {
            if (z>0){
            if (strncmp(suc->mot,souschaine,lengthmax+1)!=0)
            {
                printf("%s\n",suc->mot);
                k--;
            }
            }
            else{
                printf("%s\n",suc->mot);
                k--;
            }
            suc=successeur(suc);

        }
        z++;
    }


    printf("fin des suggestion\n");
    return;
}


void print (int k,ABR dico, char * souschaine)
{
    int lengthmax;
    ABR temp = dico;
    ABR leplusproche =dico;
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
    if (leplusproche!=NULL){
    temp=leplusproche;
    if (strcmp(temp,souschaine)!=0){
        while(strncmp(predecesseur(temp),temp,strlen(souschaine))==0)
        {
            temp=predecesseur(temp);
        }
        }
    }
    leplusproche=temp;
    //printf("\nhihi\n");

    if (leplusproche==NULL)
    {
        if (strcmp(souschaine,temp->mot)<0)
            leplusproche=temp;
        else
            leplusproche=successeur(temp);
    }

    ABR max =rechercherMax(dico);
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

void veridico (int k, ABR * dico, char * souschaine)
{
    int lengthmax;
    feuille* temp = *dico;
    feuille* leplusproche = *dico;
    ABR max =rechercherMax(*dico);
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
            if (leplusproche==max)
            {
                supprimerMot(dico,leplusproche->mot);
                return;
            }
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

void verimot (ABR * dico)
{
    FILE *fichier2 =NULL;

    fichier2 = fopen("file.txt", "r+");
    if (fichier2 != NULL)
    {

        feuille* abr2 = NULL;
        char ligne [ 128 ];
        int choix = 9;
        while ( fgets ( ligne, sizeof ligne, fichier2 ) != NULL )  //read a line
        {
            ligne[strlen(ligne)-1]='\0';///on elève le \n
            printf("\n\nmot lu dans le fichier : %s\n",ligne);
            ABR temp =rechercherMot(*dico,ligne);
            if (temp != NULL)
            {
                printf("ce mot est deja present dans le dictionnaire, on passe au suivant. \n");
                ajoutMot(&abr2,ligne);
            }
            else
            {
                printf("ce mot n'existe pas dans le dico, que voulez vous faire ? \n");
                printf("1 - remplacer ce mot dans le fichier \n");
                printf("2 - ajouter ce mot dans le dictionnaire\n");
                scanf("%d",&choix);
                if (choix == 2)
                {
                    ajoutMot(dico,ligne);
                    ajoutMot(&abr2,ligne);
                }
                else if (choix ==1)
                {
                    char newmot[30];
                    printf("\n\n");
                    printf("\nvoici des suggestions : \n");
                    suggestionMots(4,*dico,ligne);
                    printf("\nremplacez le mot : \n");
                    scanf("%s",&newmot);
                    ajoutMot(&abr2,newmot);
                }

            }
        }
        fclose(fichier2);
        fichier2 = fopen("file.txt", "w+");
        if (fichier2 != NULL)
        {
            printf("ici\n");
            quitter(abr2,fichier2);
            sleep(2);
        }
        else
        {
            perror ( fichier2 ); /* why didn't the file open? */
        }
        fclose(fichier2);

        }

}

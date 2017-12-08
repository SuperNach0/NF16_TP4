#include <stdio.h>
#include <stdlib.h>
#include "tp4.h"
#include "AL.h"
#include "ABR.h"


int main()
{
    int i;
    int j = 99 ;
    int k;
    char  chaine[50];
    printf("bonjour, quelle structure voulez vous utiliser ?\n - Arbre binaire de recherche -> 0\n -Arbre lexico graphique ? ->1\n");
    scanf("%d",&i);

    if  (i==0)
    {
        printf("vous avez choisi ABR : chargement du dictionnaire ...\n");
        feuille* racine = NULL;
        FILE* fichier = NULL;
        fichier = fopen("dicoErwan.txt", "r+");
        if (fichier != NULL)
        {
            ouvrir(&racine,fichier);
            fclose(fichier);
        }
        else
        {
            perror ( fichier ); /* why didn't the file open? */
        }
        printf("\n\n\n\n\n CHARGEMENT DU DICO TERMINE \n");
        while (j!= 5)
        {
            printf("#######################################\n");
            printf("########## MENU DES ABR ###############\n");
            printf("#######################################\n\n");
            printf("que voulez vous faire ? \n");
            printf("1-> print\n2-> verimot\n3 ->veridico\n5 -> quitter\n");
            scanf("%d",&j);
            switch (j)
            {
            case 1 :
            {
                printf("combien de mots afficher (-1 = tous) ?\n");
                scanf("%d",&k);
                printf(" a partir de quel mot afficher?\n");
                scanf("%s",&chaine);
                print(k,racine,chaine,0);
                break;
            }
            case 2 :
            {
                break;
            }

            case 3 :
            {
                printf("combien de mots corriger (-1 = tous) ?\n");
                scanf("%d",&k);
                printf(" a partir de quel mot afficher?\n");
                scanf("%s",&chaine);
                print(k,racine,chaine,1);
                break;
            }

            }


        }




        fichier = fopen("dicoErwan.txt", "w+");
        quitter(racine,fichier);
        fclose(fichier);
    }
    return 0;
}

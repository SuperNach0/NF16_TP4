#include <stdio.h>
#include <stdlib.h>
#include "tp4.h"
#include "AL.h"
#include "ABR.h"


int main()
{
    feuille* racine = NULL;
    FILE* fichier = NULL;
    FILE* fichier2 = NULL;
    int i;
    int j = 99 ;
    int k;
    char chaine[50];
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
            print(k,racine,chaine);
            break;
        }
        case 2 :
        {
            fichier2 = fopen("file.txt", "w+");
            if (fichier2 != NULL)
            {
                verimot(&racine,fichier2);
                fclose(fichier2);
            }
            else
            {
                perror ( fichier2 ); /* why didn't the file open? */
            }


            break;
        }

        case 3 :
        {
            printf("combien de mots corriger (-1 = tous) ?\n");
            scanf("%d",&k);
            printf(" a partir de quel mot afficher?\n");
            scanf("%s",&chaine);
            veridico(k,&racine,chaine);
            break;
        }

        }
    }
    fichier = fopen("dicoErwan.txt", "w+");
    if (fichier != NULL)
    {
        quitter(racine,fichier);
    }
    else
    {
        perror ( fichier ); /* why didn't the file open? */
    }


    fclose(fichier);


// Partie Bastien
// fctionTest();
//return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "tp4.h"
#include "AL.h"
#include "ABR.h"


int main() {

    int choixStruct = 0;
    printf("bonjour, quel type de structure voulez-vous utiliser ? \n1-ABR \n2-AL \n");
    scanf("%d",&choixStruct);


    if (choixStruct==1)
    {

        ABR     racine = NULL;
        FILE* fichier = NULL;
        FILE* fichier2 = NULL;
        int i;
        int j = 99 ;
        int k;
        char chaine[50];
        fichier = fopen("dicoErwan.txt", "r+");
        if (fichier != NULL) {
            ouvrir(&racine,fichier);
            fclose(fichier);
        } else {
            perror ( fichier ); /* why didn't the file open? */
        }

       /// suggestionMots(20,racine,"poulpe");
        while (j!= 5) {
            printf("#######################################\n");
            printf("########## MENU DES ABR  ###############\n");
            printf("#######################################\n\n");
            printf("que voulez vous faire ? \n");
            printf("1-> print\n2-> verimot\n3 ->veridico\n5 -> quitter\n");
            scanf("%d",&j);
            switch (j) {
            case 1 : {
                printf("combien de mots afficher (-1 = tous) ?\n");
                scanf("%d",&k);
                printf(" a partir de quel mot afficher?\n");
                scanf("%s",&chaine);
                print(k,racine,chaine);
                break;
            }
            case 2 : {

                verimot(&racine);


                break;
            }

            case 3 : {
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
        if (fichier != NULL) {
            quitter(racine,fichier);
            sleep(5);
        } else {
            perror ( fichier ); /* why didn't the file open? */
        }
        fclose(fichier);
    }

    else if (choixStruct==2){
        ///%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%שששש
        ///PARTIE BASTIEN !!!!!!

        // Variables
        Dico notreDico;
        int bool;
        int rep;
        char rep2;
        Filtre notreFiltre;

        // Code
        printf("############################\n");
        printf("###########- AL -###########\n");
        printf("############################\n");

        notreDico = loadFileAL("dicoErwan.txt");
        bool = 1;
        do{
            printf("\n\n\n\n");
            printf("Que voulez vous faire ?\n");
            printf("1 - Print\n");
            printf("2 - Verimot\n");
            printf("3 - Veridico\n");
            printf("4 - Quitter\n");
            printf("\n");
            printf("Choix : \n");
            viderBuffer();
            scanf("%d",&rep);

            switch (rep) {
                case 1:
                    printf("##### CHOIX: PRINT\n");
                    printf("\n");
                    printf("Comment voulez vous afficher le dictionnaire ?\n");
                    printf("1 - Les mots commencant par ...\n");
                    printf("2 - Les mots comportant maximum ... lettres\n");
                    printf("3 - Tout afficher\n");
                    printf("\n");
                    printf("Choix : \n");
                    viderBuffer();
                    scanf("%d",&rep);
                    switch (rep) {
                        case 1:
                            notreFiltre.fonction = commencePar;
                            printf("Lettre par laquelle les mots doivent commencer : ");
                            viderBuffer();
                            scanf("%c",&rep2);
                            notreFiltre.param = rep2;
                            printf("\n");
                            printALFILTRE(notreDico, notreFiltre);
                            break;
                        case 2:
                            notreFiltre.fonction = nbLettre;
                            printf("Nombre de lettres maximum : ");
                            viderBuffer();
                            scanf("%d",&rep);
                            notreFiltre.param = rep;
                            printf("\n");
                            printALFILTRE(notreDico, notreFiltre);
                            break;
                        case 3:
                            printAL(notreDico);
                            break;
                        default:
                            printf("Je n'ai pas compris votre choix..\n");
                            break;
                    }

                    break;
                case 2:
                    verimot2(notreDico);
                    break;
                case 3:
                    veridico2(&notreDico);
                    break;
                case 4:
                    bool = 0;
                    break;
                default:
                    break;
            }

        }while(bool);

    }





// Partie Bastien
// fctionTest();
    return 0;
}


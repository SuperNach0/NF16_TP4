#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tp4.h"
#include "AL.h"
#include "ABR.h"


void viderBuffer()
{
    int c = 0;
    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }
}

Cellule * creerCellule(char c, Cellule * alt, Cellule * succ){
    // On alloue la mémoire puis on assigne les différentes valeurs, puis on renvoie un pointeur sur la cellule
    Cellule * newCell;
    if((newCell = (Cellule *) malloc(sizeof(Cellule))) == NULL){
        printf("[creerCellule : ERROR] Malloc FAIL");
    }
    newCell->c = c;
    newCell->alt = alt;
    newCell->succ = succ;
//    printf("[creerCellule : Information] : Cellule cree\n");
    return newCell;
}
Mot *creerMot(char c, Mot * suiv){ // Crée un nouveau mot: test: OK
    //On alloue la mémoire, puis on assigne les différentes valeurs, puis on renvoie un pointeur sur le début du mot
    Mot * newMot;
    if((newMot = (Mot *)malloc(sizeof(Mot))) == NULL){
        printf("[creerMot : ERROR] Malloc FAIL");
    }
    newMot->c = c;
    newMot->suivant = suiv;
//    printf("[creerMot : Information] : Mot cree\n");
    return newMot;
}

Dico initDico2(Dico *dico, Mot mot){
    Cellule * iteraCell;
    Mot * iteraMot = &mot;
    
    if (iteraMot != NULL){
        // On crée la première cellule, que l'on rattache à dico (premier emplacement)
        iteraCell = creerCellule(iteraMot->c, NULL, NULL);
        *dico = iteraCell;
        iteraMot = iteraMot->suivant;
    
        // Ensuite on parcours le mot, et pour chaque lettre on crée une cellule, que l'on rattache à la cellule d'avant
        while (iteraMot!=NULL){
            printf("[initDico2 : Information] : Ajout de la lettre %c\n", iteraMot->c);
            iteraCell->succ = creerCellule(iteraMot->c, NULL, NULL);
            iteraCell = iteraCell->succ;
            iteraMot = iteraMot->suivant;
        }
        
        // On fini le mot par un $, que l'on rattache
        iteraCell->succ = creerCellule('$', NULL, NULL);
        printf("[initDico2 : Information] : Dictionnaire initialise avec le mot passé en paramètre \n");
    }
    
    return *dico;
}
// Renvoie un pointeur sur la cellule qui correspond à la lettre tq
// La partie strictement après la lettre n'est pas dans le dico
// La partie
Dico prefixeMot(Dico dico, Mot mot){
    // VARIABLES
    int b = 1; // Notre boolean
    Mot * monMot = &mot;
    Dico iteraCell = dico;
    Dico prefixe = NULL;
    // FIN VARIABLES
    
    while (b){
        while ((iteraCell!=NULL)&&(iteraCell->c < monMot->c)){// On cherche la lettre alternative correspondant à la lettre du mot
            iteraCell = iteraCell->alt ;
        }

        if((iteraCell!=NULL)&&(iteraCell->c == monMot->c)){// Si c'est égal on passe à la lettre suivante
            prefixe = iteraCell; //On stocke la cellule en tant de début du nouveau dico
            iteraCell = iteraCell->succ;
            if((monMot=monMot->suivant)==NULL){
                printf("[prefixeMot : Information] : Prefixe trouve (mot entier) !\n");
                b=0;
            } // Si la prochaine lettre dans le mot est NULL on arrête
        }
        else{//Sinon on arrête, on a trouvé le prefixe (lettre trouvée différente)
                printf("[prefixeMot : Information] : Prefixe trouve (plus correspondances) !\n");
            b=0;
        }
    }
    return prefixe;
}

// Recherche le mot passé en paramètre dans le dictionnaire passé en paramètre et renvoie
// 0 Si le mot n'est pas dans le dictionnaire
// 1 Si le mot est dans le dictionnaire
int rechercheMot2(Mot mot, Dico dico){
    // VARIABLES
    int b = 1; // Notre boolean
    Mot * monMot = &mot;
    Dico iteraCell = dico;
    Dico prefixe = NULL;
    // FIN VARIABLES
    
    while (b){
        while ((iteraCell!=NULL)&&(iteraCell->c < monMot->c)){// On cherche la lettre alternative correspondant à la lettre du mot
            iteraCell = iteraCell->alt ;
        }
        
        if((iteraCell!=NULL)&&(iteraCell->c == monMot->c)){// Si c'est égal on passe à la lettre suivante
            prefixe = iteraCell; //On stocke la cellule en tant de début du nouveau dico
            iteraCell = iteraCell->succ;
            if((monMot=monMot->suivant)==NULL){
                printf("[prefixeMot : Information] : Prefixe trouve (mot entier) !\n");
                b=0;
            } // Si la prochaine lettre dans le mot est NULL on arrête
        }
        else{//Sinon on arrête, on a trouvé le prefixe (lettre trouvée différente)
            printf("[prefixeMot : Information] : Prefixe trouve (plus correspondances) !\n");
            b=0;
        }
    }
    
    if ((prefixe!=NULL)&&(prefixe->succ->c == '$')&&(monMot==NULL)){
        printf("[rechercheMot2 : Information] : Mot trouve !\n");
        return 1;
    }
    printf("[rechercheMot2 : Information] : Mot non trouve !\n");
    return 0;
}

// Ajoute le mot passé en paramètre au dictionnaire pointé en paramètre
Dico ajoutMot2(Mot mot, Dico *dico){
    if(rechercheMot2(mot,*dico)){
        printf("[ajoutMot2 : Information] : Ce mot est deja dans le dictionnaire, dictionnaire inchange renvoye\n");
        return *dico;
    }
    else if(dico == NULL){
        printf("[ajoutMot2 : Information] : Dictionnaire vide, on l'initialise avec le mot passe en parametre\n");
        return initDico2(dico, mot);
    }
    else{
        // VARIABLES //
        Mot *monMot = &mot;
        Cellule * iteraCell, *prefixe;
        iteraCell = (*dico);
        prefixe = NULL;
        // FIN VARIABLES//
        
        if ((*dico)->c > monMot->c){
            // On insère en racine
            (*dico) = creerCellule(monMot->c, (*dico), NULL);
            monMot = monMot->suivant;
            iteraCell = *dico;
            while (monMot != NULL) {
                iteraCell->succ = creerCellule(monMot->c, NULL, NULL);
                iteraCell = iteraCell->succ;
                monMot = monMot->suivant;
            }
            iteraCell->succ = creerCellule('$', NULL, NULL);
        }else{
            int b = 1; //Notre boolean
            while(b){
                // Sinon on parcours l'arbre à la recherche du prefixe:
                if(iteraCell->c < monMot->c){
                    // On teste la première case
                    while ((iteraCell->alt!=NULL)&&(iteraCell->alt->c < monMot->c)){
                        iteraCell = iteraCell->alt ;
                    }
                }
                if(iteraCell->alt!=NULL){
                    if(iteraCell->alt->c == monMot->c){
                        // On a trouvé la cellule appartenant au mot
                        // Reste à savoir si on continue ou si on s'arrête
                        if(monMot->suivant != NULL){
                            monMot=monMot->suivant;
                            iteraCell=iteraCell->alt;
                            prefixe=iteraCell;
                            iteraCell=iteraCell->succ;
                        }
                        else{
                            iteraCell->alt->succ = creerCellule('$', iteraCell->alt->succ, NULL);
                            b=0;
                        }
                    }
                    else if(iteraCell->c == monMot->c){
                        // On a trouvé la cellule appartenant au mot
                        // Reste à savoir si on continue ou si on s'arrête
                        if(monMot->suivant != NULL){
                            monMot=monMot->suivant;
                            prefixe=iteraCell;
                            iteraCell=iteraCell->succ;
                        }
                        else{
                            iteraCell->succ = creerCellule('$', iteraCell->succ, NULL);
                            b=0;
                        }
                    }
                    else{
                        // On a trouvé un iteraCell->alt->c > monMot->c, donc
                        if(prefixe == NULL){
                            iteraCell->alt = creerCellule(monMot->c, iteraCell->alt, NULL);
                            iteraCell = iteraCell->alt;
                        }
                        else if((prefixe->succ == iteraCell)&&(prefixe->succ->c > monMot->c)){
                            prefixe->succ = creerCellule(monMot->c, prefixe->succ, NULL);
                            iteraCell = prefixe->succ;
                        }
                        else{
                            iteraCell->alt = creerCellule(monMot->c, iteraCell->alt, NULL);
                            iteraCell = iteraCell->alt;
                        }
                        // On fini la completion du mot
                        monMot = monMot->suivant;
                        while (monMot != NULL) {
                            iteraCell->succ = creerCellule(monMot->c, NULL, NULL);
                            iteraCell = iteraCell->succ;
                            monMot = monMot->suivant;
                        }
                        iteraCell->succ = creerCellule('$', NULL, NULL);
                        b=0;
                    }
                }
                else
                {
                   if(iteraCell->c == monMot->c){
                        // On a trouvé la cellule appartenant au mot
                        // Reste à savoir si on continue ou si on s'arrête
                        if(monMot->suivant != NULL){
                            monMot=monMot->suivant;
                            prefixe=iteraCell;
                            iteraCell=iteraCell->succ;
                        }
                        else{
                            iteraCell->succ = creerCellule('$', iteraCell->succ, NULL);
                            b=0;
                        }
                    }
                    else if(prefixe == NULL){
                        iteraCell->alt = creerCellule(monMot->c, iteraCell->alt, NULL);
                        iteraCell = iteraCell->alt;
                        monMot = monMot->suivant;
                        while (monMot != NULL) {
                            iteraCell->succ = creerCellule(monMot->c, NULL, NULL);
                            iteraCell = iteraCell->succ;
                            monMot = monMot->suivant;
                        }
                        iteraCell->succ = creerCellule('$', NULL, NULL);
                        b=0;
                    }
                    else if(prefixe->succ->c > monMot->c){
                        prefixe->succ = creerCellule(monMot->c, prefixe->succ, NULL);
                        iteraCell = prefixe->succ;
                        monMot = monMot->suivant;
                        while (monMot != NULL) {
                            iteraCell->succ = creerCellule(monMot->c, NULL, NULL);
                            iteraCell = iteraCell->succ;
                            monMot = monMot->suivant;
                        }
                        iteraCell->succ = creerCellule('$', NULL, NULL);
                        b=0;
                    }
                    else{
                        iteraCell->alt = creerCellule(monMot->c, iteraCell->alt, NULL);
                        iteraCell = iteraCell->alt;
                        monMot = monMot->suivant;
                        while (monMot != NULL) {
                            iteraCell->succ = creerCellule(monMot->c, NULL, NULL);
                            iteraCell = iteraCell->succ;
                            monMot = monMot->suivant;
                        }
                        iteraCell->succ = creerCellule('$', NULL, NULL);
                        b=0;
                    }
                    
                }
            }
        }
    }
    return *dico;
}

// Partie recursive de la fonction d'avant
Dico recsupprimeMot2(Mot* mot, Dico dico){
    Dico it = dico;
    Dico prec = NULL;
    if(it->c == '$'){
        if(it->alt != NULL){
            return it->alt;
        }
        return NULL;
    }
    
    while (it->c != mot->c){
        prec = it;
        it = it->alt;
    }
        
    Dico suiv = recsupprimeMot2(mot->suivant, it->succ);
    if(suiv == NULL){
        free(it->succ);
        if(prec != NULL) prec->alt = it->alt;
        return it->alt;
    }
    it->succ = suiv;
    return it;
}

// Supprime le mot passé en paramètre du dictionnaire passé en paramètre
Dico supprimeMot2(Mot mot, Dico dico){
    
    if(rechercheMot2(mot, dico)){
       dico = recsupprimeMot2(&mot,dico);
    }
    else{
        printf("[supprimeMot2 : Information] : Ce mot n'est pas dans le dictionnaire, dictionnaire renvoyé sans modifications\n");
    }
    return dico;
}

// Ajoute la lettre au mot
void ajouterLettreMot(Mot *mot, char lettre){ // AJOUTER UNE LETTRE: TEST OK
    if(mot->c == '$'){ /// On considère '$' comme la lettre NULL
       mot->c = lettre;
    }
    else{
        Mot *temp = mot; // On utilise un pointeur sur le premier elem du mot pour le parcourir
        while(temp->suivant != NULL){
            temp=temp->suivant;
        }
        // Ici temp->suivant = NULL
        //Donc on crée un nouveau mot
       temp->suivant = creerMot(lettre, NULL);
    }
}

// Copie le 2nd mot dans le 1er (les deux pointeurs restent différents).
void cpMots(Mot *mot1, Mot mot2){ // Copie le mot2 dans le mot 1: TEST OK
    Mot *iterator2 = &mot2;
    Mot *iterator1 = mot1;
    (*iterator1).c = '$';
    (*iterator1).suivant = NULL;
    while (iterator2 != NULL){
        iterator1->c = iterator2->c;
        if(iterator2->suivant != NULL){
            iterator1->suivant = creerMot(iterator2->c, NULL);
            iterator1 = iterator1->suivant;
        }
        iterator2=iterator2->suivant;
    }
    iterator1->suivant = NULL;
}

// printf le mot passé en paramètre
void afficherMot(Mot mot){ // Affiche un mot: TEST OK
    Mot *iterator = &mot;
    while (iterator != NULL){
        printf("%c",iterator->c);
        iterator=iterator->suivant;
    }
}


// Partie recursive de la fonction suivante
void printALrec(Dico dico, Mot mot){
    Dico iterator = dico;
    while (iterator != NULL){
        if(iterator->c == '$'){
            printf("\n");
            afficherMot(mot);
        }
        else{
        Mot new;
//        printf("Lettre: %c \n", iterator->c);
        cpMots(&new, mot);
        ajouterLettreMot(&new, iterator->c);
        printALrec(iterator->succ, new);
        }
        iterator=iterator->alt;
    }
}

// Affiche tous les mots d'un AL
void printAL(Dico dico){ // affiche tous les mots du dico: TEST OK
    Mot new = *creerMot('$', NULL);
    printALrec(dico, new);
}

// Retourne un mot à partir d'un String
Mot creerMotString(char* string){ // Transforme un string en mot: TEST OK
    Mot new = *creerMot(string[0], NULL);
    int i = 1;
    while (string[i] != '\0'){
        ajouterLettreMot(&new, string[i]);
        i++;
    }
    return new;
}


// PRINT + FONCTIONS
/// Constructeurs de tests

/// Fonctions
int commencePar(Mot a, int param){
    if(a.c == param){
        return 1;
    }
    return 0;
}

int nbLettre(Mot a, int param){
    int i = 0;
    Mot * b = &a;
    while ((i<=param)&&(b != NULL)){
        b = b->suivant;
        i++;
    }
    if(i<=param)
    {return 1;}
    return 0;
        
}


/// Fonction print
void printALrecFILTRE(Dico dico, Mot mot, Filtre filtre){
    Dico iterator = dico;
    while (iterator != NULL){
        if(iterator->c == '$'){
            if((*filtre.fonction)(mot,filtre.param)){
                afficherMot(mot);
            }
        }
        else{
            Mot new;
            //        printf("Lettre: %c \n", iterator->c);
            cpMots(&new, mot);
            ajouterLettreMot(&new, iterator->c);
            printALrecFILTRE(iterator->succ, new, filtre);
        }
        iterator=iterator->alt;
    }
}

void printALFILTRE(Dico dico, Filtre filtre){ // affiche tous les mots du dico: TEST OK
    Mot new = *creerMot('$', NULL);
    printALrecFILTRE(dico, new, filtre);
}

// Fait une suggestion de k mots à partir du mot entré et
int recsuggestionMot2(int k, Dico dico, Mot * souschaine, Mot mot, int n){
    int i = 0;
    Mot new;
    Dico iterator = dico;
    
    if(souschaine != NULL){
        while ((iterator != NULL)&&(iterator->c != souschaine->c)){
            iterator=iterator->alt;
        }
        if(iterator != NULL){
            cpMots(&new, mot);
            ajouterLettreMot(&new, iterator->c);
            i = i + recsuggestionMot2(k, iterator->succ, souschaine->suivant, new, i);
        }
    }
    
    iterator = dico;

        while ((iterator != NULL)&&((i+n)<k)){
                if(iterator->c == '$'){
                    afficherMot(mot);
                    printf("\n");
                    i = i+1;
                }
                else if ((souschaine==NULL)||((souschaine != NULL)&&(iterator->c != souschaine->c))){
                    cpMots(&new, mot);
                    ajouterLettreMot(&new, iterator->c);
                    i = i + recsuggestionMot2(k, iterator->succ, NULL, new, i+n);
                }
            
        iterator=iterator->alt;
    }
    return i;
    
}

// Affiche tous les mots d'un AL
void suggestionMot2(int k, Dico dico, Mot souschaine){ // affiche tous les mots du dico: TEST OK
    Mot new = *creerMot('$', NULL);
    recsuggestionMot2(k,dico, &souschaine, new, 0);
}
// FIN PRINT + FONCTIONS

void afficherMotveridico(Mot mot, Dico * dico){
    printf("\n MOT : ");
    Mot *iterator = &mot;
    while (iterator != NULL){
        printf("%c",iterator->c);
        iterator=iterator->suivant;
    }
    printf("\nQue voulez vous faire ?\n");
    printf("1-Correction\n2-Suppression\n3-Ignorer\n");
    
    int rep;
    int boole;
    char nouveau[30];
    printf("\nChoix :");scanf("%d",&rep);
    printf("\n");
    do{
        boole = 0;
    switch (rep) {
        case 1:
            printf("Rentrez le mot corrigé (max. 30 lettres) : ");
            viderBuffer();
            scanf("%s", nouveau);
            (*dico) = supprimeMot2(mot,*dico);
            (*dico) = ajoutMot2(creerMotString(nouveau), dico);
            printf("\nMOT CORRIGE !");
            break;
        case 2:
            supprimeMot2(mot,*dico);
            printf("\nMOT SUPPRIME !");
            break;
        case 3:
            break;
        default:
            boole = 1;
            break;
    }
    }while(boole);
}

void printALrecFILTREveridico(Dico dico, Mot mot, Filtre filtre, Dico dico2){
    Dico iterator = dico;
    while (iterator != NULL){
        if(iterator->c == '$'){
            iterator=iterator->alt;
            if((*filtre.fonction)(mot,filtre.param)){
                afficherMotveridico(mot, &dico2);
            }
        }
        else{
            Mot new;
            //        printf("Lettre: %c \n", iterator->c);
            cpMots(&new, mot);
            ajouterLettreMot(&new, iterator->c);
            printALrecFILTREveridico(iterator->succ, new, filtre, dico2);
            iterator=iterator->alt;
        }
        
    }
}

void printALFILTREveridico(Dico * dico, Filtre filtre){ // affiche tous les mots du dico: TEST OK
    Mot new = *creerMot('$', NULL);
    printALrecFILTREveridico(*dico, new, filtre, *dico);
}
void veridico2(Dico dico){
    Filtre filtre;
    Mot new = *creerMot('$', NULL);
    
    printf("\n############################");
    printf("\n####### - VERIDICO - #######");
    printf("\n############################");
    printf("\n\n");
    printf(" -- MENU --\n");
    printf(" QUEL FILTRE APPLIQUER AU DICTIONNAIRE ?\n");
    printf("1- Mots qui commencent par la lettre .. \n");
    printf("2- Mots qui comportent moins de N lettres \n");
    printf("3- Quitter VERIDICO \n");
    printf("\n");
    printf("Choix : ");
    
    int rep, nb;
    int boole;
    char lettre;
    scanf("%d",&rep);
    
    do{
        boole = 0;
        switch (rep) {
            case 1:
                printf("Lettre par laquelle les mots doivent commencer : ");
                viderBuffer();
                scanf("%c", &lettre);
                filtre.fonction = commencePar;
                filtre.param = lettre;
                printf("\n");
                printALrecFILTREveridico(dico, new, filtre, dico);
                break;
            case 2:
                printf("Nombre de lettre que doivent avoir les mots au maximum : ");
                viderBuffer();
                scanf("%d", &nb);
                filtre.fonction = nbLettre;
                filtre.param = nb;
                printf("\n");
                printALrecFILTREveridico(dico, new, filtre, dico);
                break;
            case 3:
                break;
            default:
                boole = 1;
                break;
        }
    }while(boole);
    
    
}


void fctionTest(){
    
    
    
    
    
    
    Dico leDico;
    leDico = initDico2(&leDico, creerMotString("Bonjour"));
    leDico = ajoutMot2(creerMotString("Bonjor"), &leDico);
    leDico = ajoutMot2(creerMotString("Bonjar"), &leDico);
    leDico = ajoutMot2(creerMotString("Bonjir"), &leDico);
    leDico = ajoutMot2(creerMotString("Bonjior"), &leDico);
    leDico = ajoutMot2(creerMotString("Bonjazzzr"), &leDico);
    leDico = ajoutMot2(creerMotString("Boncar"), &leDico);
    leDico = ajoutMot2(creerMotString("Bonzar"), &leDico);
    leDico = ajoutMot2(creerMotString("Es"), &leDico);
    leDico = ajoutMot2(creerMotString("EE"), &leDico);
    veridico2(leDico);
//    printf("suppression\n");
//    leDico = supprimeMot2(creerMotString("EE"), leDico);
//    printf("FIN\n");
//    leDico = ajoutMot2(creerMotString("YOUU"), &leDico);
  printAL(leDico);
////
//
//
//
//    //On fait des tests:
//    const char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
//    Dico ledico = NULL;
//    int nbmots = 2000;
//    Mot tableauMots[2000];
//    int i,j,k,indice;
//
//    srand((int)time(NULL));
//
//    //On essaie de créer un mot:
//    printf("\n############################\n");
//    printf("[ESSAI 0] On essaie de créer les mots\n");
//    for(i=0;i<nbmots;i++){
//        tableauMots[i] = *creerMot('$', NULL);
//    }
//    printf("[ESSAI 0] Reussi !\n");
//    printf("############################\n");
//    printf("\n############################\n");
////    printf("[ESSAI 1] On essaie d'ajouter une lettre à un mot\n");
////    ajouterLettreMot(&tableauMots[0], 'C');
////    printf("[ESSAI 1] Reussi !\n");
////    printf("############################\n");
////    printf("\n############################\n");
////    printf("[ESSAI 2] On essaie d'afficher cette lettre");
////    afficherMot(tableauMots[0]);
////    printf("[ESSAI 2] Reussi !\n");
////    printf("############################\n");
//    printf("\n############################\n");
//    printf("[ESSAI 3] On essaie de créer plein de mots\n");
//    for(i=0;i<nbmots;i++){
//       k=rand() % (10) + 1;
//        for(j=0;j<k;j++){
//            indice = rand() % (25 + 1);
//            ajouterLettreMot(&tableauMots[i], alphabet[indice]) ;
//            printf(" - [ESSAI 3] Essai mot num %d : lettre %d \n",i,j);
//        }
//        afficherMot(tableauMots[i]);
//    }
//    printf("[ESSAI 3] Reussi !\n");
//    printf("\n############################\n");
//    printf("[ESSAI 4] On essaie d'initialiser le dico avec le mot : ");
//    afficherMot(tableauMots[0]);
//    initDico2(&ledico, tableauMots[0]);
//    printf("[ESSAI 4] Reussi !\n");
//    printf("############################\n");
////    printf("\n############################\n");
////    printf("[ESSAI 5] On essaie d'afficher le Dico\n");
////    printAL(ledico);
////    printf("[ESSAI 5] Reussi !\n");
////    printf("############################\n");
//    printf("\n############################\n");
//    printf("[ESSAI 6] On essaie de remplir le Dico\n");
//    for(i=0;i<nbmots;i++){
//        ledico = ajoutMot2(tableauMots[i], &ledico);
//    }
//    int g = 1;
//    printALFILTRE(ledico, nbMots);
//
//    if(g==0){printf("Fail\n");}
//    else{printf("OUII\n");}
//
//    printf("[ESSAI 6] Reussi !\n");
//    printf("############################\n");
////    printf("\n############################\n");
////    printf("[ESSAI 6] On essaie de trouver le prefixe d'un mot'");
////    Dico prefixe = prefixeMot(ledico, tableauMots[0]);
////    afficherTousLesMots(prefixe);
////    printf("[ESSAI 6] Reussi !\n");
////    printf("############################\n");
////
//
//    //on crée nbmots mots
//    //on les ajoute dans l'arbre
//
//
////    afficherTousLesMots(ledico);
}












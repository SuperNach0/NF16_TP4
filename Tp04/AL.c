#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tp4.h"
#include "AL.h"
#include "ABR.h"

int GLOB_aborterVeridico;

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
            iteraCell->succ = creerCellule(iteraMot->c, NULL, NULL);
            iteraCell = iteraCell->succ;
            iteraMot = iteraMot->suivant;
        }

        // On fini le mot par un $, que l'on rattache
        iteraCell->succ = creerCellule('$', NULL, NULL);
        printf("[initDico2 : Information] : Dictionnaire initialise ! \n");
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
                printf("[prefixeMot : Information] : Prefixe trouve !\n");
                b=0;
            } // Si la prochaine lettre dans le mot est NULL on arrête
        }
        else{//Sinon on arrête, on a trouvé le prefixe (lettre trouvée différente)
                printf("[prefixeMot : Information] : Prefixe trouve !\n");
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
                printf("[prefixeMot : Information] : Prefixe trouve  !\n");
                b=0;
            } // Si la prochaine lettre dans le mot est NULL on arrête
        }
        else{//Sinon on arrête, on a trouvé le prefixe (lettre trouvée différente)
            printf("[prefixeMot : Information] : Prefixe trouve!\n");
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
    if(dico == NULL){
        printf("[ajoutMot2 : Information] : Dictionnaire vide, on l'initialise avec le mot passe en parametre\n");
        return initDico2(dico, mot);
    }
    else if(rechercheMot2(mot,*dico)){
        printf("[ajoutMot2 : Information] : Ce mot est deja dans le dictionnaire, dictionnaire inchange renvoye\n");
        return *dico;
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

// Partie recursive de la fonction suivant (supprimeMot2)
Dico recsupprimeMot2(Mot* mot, Dico dico){
    Dico it = dico;
    Dico prec = NULL;
    // Si on trouve le mot (on trouve un $ est on est à la fin du mot)
    // On envoie l'alternative de $ (une case ou NULL)
    if((it->c == '$')&&(mot == NULL)){
            return it->alt;
    }

    // Sinon on trouve la bonne alternative, celle qui correspond à la lettre
    while (it->c != mot->c){
        prec = it;
        it = it->alt;
    }

    // Et on va chercher la lettre suivante
    Dico suiv = recsupprimeMot2(mot->suivant, it->succ);

    // Si la lettre suivante est NULL (et donc qu'on a supprimé tout ce qu'il y a après).
    if(suiv == NULL){
        free(it->succ);// on libère l'espace mémoire
        if(prec != NULL){ // Si notre lettre n'est pas la "racine" des alternatives,
            prec->alt = it->alt; // On raccroche le précédent au suivant, pour assurer la continuité
        }
        else{
            return it->alt; // Sinon on renvoie l'alt (on est en haut des alternatives)
        }
    }else{
        // La lettre suivant n'est pas nulle, donc on raccroche la lettre renvoyée
        it->succ = suiv;
    }
    return dico;// Et on retourne le dico (toutes les alternatives depuis le début).
}

// Supprime le mot passé en paramètre du dictionnaire passé en paramètre
Dico supprimeMot2(Mot mot, Dico dico){

    if(rechercheMot2(mot, dico)){ // On ne supprime que les mots qui sont présents dans le dico
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
                printf("\n");
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
        // La souschaine n'est pas nulle, on cherche un caractère commun
        while ((iterator != NULL)&&(iterator->c != souschaine->c)){
            iterator=iterator->alt;
        }
        
        //Si on a trouvé un caractere commun
        if(iterator != NULL){
            cpMots(&new, mot); // On crée une copie du mot
            ajouterLettreMot(&new, iterator->c); // On ajoute ce caractère à ce nouveau mot
            i = i + recsuggestionMot2(k, iterator->succ, souschaine->suivant, new, i);// et on mets à jour le compteur de suggestions, en rappellant la fonction
        }
    }

    iterator = dico;
        // On se retrouve ici lorsqu'on a parcouru tous les mots suivants ou qu'on a pas trouvé de lettre commun
        // dans les deux cas, tant qu'on a pas atteint la fin des alternatives ou que le nombre de suggestions n'est pas atteint, on affiche tous les mots de toutes les alt en commençant par la 1ère (la racine des alt).
        while ((iterator != NULL)&&((i+n)<k)){
                if(iterator->c == '$'){ // Si c'est un mot on l'affiche
                    afficherMot(mot);
                    printf(", ");
                    i = i+1;
                }
                else if ((souschaine==NULL)||((souschaine != NULL)&&(iterator->c != souschaine->c))){ // Sinon si la fin du mot est atteint ou que
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

void afficherMotveridico(char* monMot, Dico * dico){
    // Fonction qui, pour un mot donné présent dans le dictionnaire, propose plusieurs choix à l'utilisateur
    printf("\n MOT : ");
    Mot mot = creerMotString(monMot);
    Mot *iterator = &mot;
    while (iterator != NULL){
        printf("%c",iterator->c);
        iterator=iterator->suivant;
    }
    printf("\nQue voulez vous faire ?\n");
    printf("1-Correction\n2-Suppression\n3-Ignorer\n4-Quitter\n");

    int rep;
    int boole;
    char nouveau[30];
    
    do{
        
        printf("\nChoix :");
        viderBuffer();
        scanf("%d",&rep);
        printf("\n");
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
            (*dico) = supprimeMot2(mot,*dico);
            printf("\nMOT SUPPRIME !");
            break;
        case 3:
            break;
        case 4:
            GLOB_aborterVeridico = 1;
            boole = 0;
            break;
        default:
            boole = 1;
            break;
    }
    }while(boole);
}

// Fonction qui ajoute une mot à la liste passée en paramètre
void ajouterMotListe(Mot mot, ListeMot *liste){
    Mot *it = &mot;
    int i =0;
    // On compte le nombre de letttre
    while (it != NULL){
        i++;
        it = it->suivant;
    }
    it = &mot;
    // On crée un tableau de char avec le bon nombre de lettres
    char * monMot = (char*)malloc(sizeof(char)*i);
    i=0;
    while (it != NULL){
        monMot[i] = it->c;
        it = it->suivant;
        i++;
    }
    // Si c'est le premier mot, on lui donne une valeur
    if(liste->mot == NULL){
        liste->mot = monMot;
    }else{//Sinon on l'ajoute à la suite
        ListeMot *maListe = (ListeMot*)malloc(sizeof(ListeMot));
        maListe->mot = monMot;
        maListe->suivant = NULL;
        ListeMot *itt = liste;
        while(itt->suivant != NULL){//On trouve le dernier mot avant de l'ajouter
            itt=itt->suivant;
        }
        itt->suivant = maListe;
    }
}

// Crée une liste qui contient tous les mots du dictionnaire
void listeAllMotsinDico(Dico *dico, Mot mot, Filtre filtre, Dico *dico2, ListeMot **liste){
    ListeMot *newliste = *liste;
    
    Dico iterator = *dico;
    while (iterator != NULL){
        if(iterator->c == '$'){
            iterator=iterator->alt;
            if((*filtre.fonction)(mot,filtre.param)){ // Si le mot satisfait les conditions de la fonction passée en paramètre, on l'ajoute à la liste
                ajouterMotListe(mot, newliste);
                (*liste) = newliste;
            }
        }
        else{
            Mot new;
            //        printf("Lettre: %c \n", iterator->c);
            cpMots(&new, mot);
            ajouterLettreMot(&new, iterator->c);
            listeAllMotsinDico(&iterator->succ, new, filtre, dico2, liste);
            iterator=iterator->alt;
        }
    }
}

// Procédure qui fait la liste de tous les mots du dico, et pour chaque mot dans la liste, demande à l'utilisateur ce qu'il veut faire
void supprVeridico(Dico *dico, Filtre filtre){
    Mot new = *creerMot('$', NULL);
    ListeMot *liste = (ListeMot*)malloc(sizeof(ListeMot));
    liste->mot=NULL;
    liste->suivant=NULL;
    listeAllMotsinDico(dico, new, filtre, dico, &liste);
    
    ListeMot * it = liste;
    ListeMot * itt;
    while ((it  != NULL)&&(GLOB_aborterVeridico==0)){ // tant qu'on a pas fini la liste & qu'on ne nous demande pas d'aborter la procédure, on demande à l'utilisateur d'effectuer une action pour chaque mot présent dans la liste.
        afficherMotveridico(it->mot, dico);
        itt = it;
        it = it->suivant;
        free(itt); // On fait attention à ne pas laisser la liste dans la mémoire
    }
}
void veridico2(Dico * dico){
    // Fonction qui affiche & demande à l'utilisateur ce qu'il veut faire.
    GLOB_aborterVeridico = 0;
    Filtre filtre;
    GLOB_aborterVeridico = 0;
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
                supprVeridico(dico, filtre);
                break;
            case 2:
                printf("Nombre de lettre que doivent avoir les mots au maximum : ");
                viderBuffer();
                scanf("%d", &nb);
                filtre.fonction = nbLettre;
                filtre.param = nb;
                printf("\n");
                supprVeridico(dico, filtre);
                break;
            case 3:
                break;
            default:
                boole = 1;
                break;
        }
    }while(boole);


}
// Fonction qui charge tous les mots d'un fichier (dont le nom est passé en param) dans un AL
Dico loadFileAL(char * nomFichier){
    FILE * fichier = fopen(nomFichier, "r");
    Dico dico = NULL;
    char currentCar = 0;
    Mot * currentMot = creerMot('$', NULL);
    if(fichier != NULL){
        do{
            currentCar = fgetc(fichier);
            if(((currentCar == '\n' )||(currentCar == EOF)||(currentCar == '\r'))&&(currentMot->c != '$')){
                if(dico != NULL){
                    dico = ajoutMot2(*currentMot, &dico);
                    currentMot = creerMot('$', NULL);
                }
                else{
                    dico = initDico2(&dico, *currentMot);
                    currentMot = creerMot('$', NULL);
                }
            }
            else if ((currentCar != '\n' )&&(currentCar != EOF)&&(currentCar != '\r')){
                    ajouterLettreMot(currentMot, currentCar);
                
            }
        }while(currentCar != EOF);
        fclose(fichier);
    }
    else{
        printf("[loadFileAL : ERREUR] : Impossible d'ouvrir le fichier '%s' \n",nomFichier);
    }

    return dico;
}
//Fonction qui renvoie une liste contenant tous les mots d'un fichier
ListeMot * loadFileListe(char * nomFichier){
    FILE * fichier = fopen(nomFichier, "r");
    ListeMot * dico = (ListeMot*)malloc(sizeof(ListeMot));
    dico->mot = NULL;
    dico->suivant = NULL;
    
    ListeMot * iter = dico;
    
    char currentCar = 0;
    char * currentMot = (char*) malloc(sizeof(char)*50);
    int i = 0;
    if(fichier != NULL){
        do{
            currentCar = fgetc(fichier);
            if(((currentCar == '\n' )||(currentCar == EOF)||(currentCar == '\r'))&&(i != 0)){
                    currentMot[i] = 0;
                    iter->mot = currentMot;
                    currentMot = malloc(sizeof(char)*100);
                    iter->suivant =(ListeMot*)malloc(sizeof(ListeMot));
                    iter = iter->suivant;
                    iter->mot = NULL;
                    iter->suivant = NULL;
                    i=0;
            }
            else if ((currentCar != '\n' )&&(currentCar != EOF)&&(currentCar != '\r')&&(currentCar != '\0')){
                currentMot[i] = currentCar;
                i++;
            }
        }while(currentCar != EOF);
    }
    else{
        printf("[loadFileListe : ERREUR] : Impossible d'ouvrir le fichier '%s' \n",nomFichier);
    }
    
    return dico;
}
// On écrit un mot dans le fichier passé en paramètre (le fichier doit être ouvert au préalable).
void writeMot(Mot mot, FILE * fichier){
    Mot * it = &mot;
    while(it!=NULL){
        fputc(it->c, fichier);
        it=it->suivant;
    }
    fputc('\n', fichier);
}
// On écrit le dictionnaire dans le fichier passé en paramètre, récursivement
void writeFileALrec(FILE * fichier, Dico dico, Mot mot){
    Dico iterator = dico;
    while (iterator != NULL){
        if(iterator->c == '$'){
            writeMot(mot, fichier);
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
// Fonction à appeller pour écrire le dictionnaire dans le fichier dont le nom est passé en paramètre
void writeFileAL(char * nomFichier, Dico dico){
    // On écrase le fichier
    FILE * fichier = fopen(nomFichier, "w+");
    if(fichier != NULL){
        Mot new = *creerMot('$', NULL);
        writeFileALrec(fichier, dico, new);
        fclose(fichier);
    }
}

// fonction qui écrit la liste dans le fichier passé en paramètre
void writeFileListe(char * nomFichier, ListeMot * liste){
    FILE * fichier = fopen(nomFichier, "w+");
    ListeMot * it = liste;
    int i;
    while (it->mot != NULL) {
        i=0;
        while (it->mot[i] != '\0'){
            fputc(it->mot[i], fichier);
            i++;
        }
        fputc('\n',fichier);
        it=it->suivant;
    }
    
    fclose(fichier);
}

//Fonction verimot
void verimot2(Dico dico){
    printf("\n############################");
    printf("\n####### - VERIMOT - ########");
    printf("\n############################");
    printf("\n\n");
    printf("[verimot2 : Information] : Chargement du fichier 'file.txt' \n");
    ListeMot * file = loadFileListe("file.txt");
    ListeMot * it = file;
    Mot mot;
    printf("[verimot2 : Information] : Fin de chargement du fichier 'file.txt' \n");
    printf("[verimot2 : Information] : Début traitement des mots du fichier \n");
    char * nouveau = malloc(sizeof(char)*31);
    while(it->mot != NULL){
        mot = creerMotString(it->mot);
        if(rechercheMot2(mot, dico)==0){
            int rep;
            int boole;
            
            do{
                printf("\nMot : %s",it->mot);
                printf("\n Que souhaitez vous faire ?\n");
                printf("1-Remplacer dans le fichier \n2-Ajouter dans le dictionnaire\n");
                
                
                printf("\nChoix :");
                scanf("%d",&rep);
                printf("\n");
                boole = 0;
                switch (rep) {
                    case 1:
                        printf("Proposition de modification :\n ");
                        suggestionMot2(4, dico, mot);
                        printf("\n");
                        printf("Rentrez le mot corrigé (max. 30 lettres) : ");
                        viderBuffer();
                        scanf("%s", nouveau);
                        it->mot = nouveau;
                        nouveau = malloc(sizeof(char)*31);
                        printf("\nMOT CORRIGE !\n");
                        break;
                    case 2:
                        dico = ajoutMot2(mot, &dico);
                        printf("\nMOT AJOUTE AU DICO!");
                        printf("\n");
                        printf("\n");
                        break;
                    default:
                        boole = 1;
                        break;
                }
            }while(boole);
            
        }
        it=it->suivant;
    }
    
    printf("[verimot2 : Information] : Fin de traitement des mots du fichier \n");
    printf("[verimot2 : Information] : Debut reecriture du fichier \n");
    writeFileListe("file.txt",file);
    printf("[verimot2 : Information] : Fin reecriture du fichier \n");
}

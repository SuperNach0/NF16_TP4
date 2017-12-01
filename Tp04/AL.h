#ifndef AL_H_INCLUDED
#define AL_H_INCLUDED

typedef struct T_cell{
    char c;
    struct T_cell * succ;
    struct T_cell * alt;
}Cellule;

typedef struct T_dico{
    Cellule * premier;
}Dico;

typedef struct T_mot{
    char c;
    struct T_mot * suivant;
}Mot;


Dico initDico2(Dico dico, Mot mot);
Dico prefixeMot(Dico dico, Mot mot);
int rechercheMot2(Mot mot, Dico dico);
Dico ajoutMot2(Mot mot, Dico dico);
Dico supprimeMot2(Mot mot, Dico dico);
#endif // AL_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NB 27

typedef struct lettre* ptr_tableau;
typedef struct lettre{char caractere; ptr_tableau suivant; int fin_mot;}Lettre;
typedef Lettre alphabet[NB];

void ajout_caractere(char, Lettre*);

int ajout_mot(Lettre*, char*, int);

int presence_mot(Lettre*, char*, int, int);

void ajout_dico(Lettre*, char*);

void conversion_mot(char*);

void correction_texte(Lettre*, char*);

void lib_memoire(Lettre* l);



#include "projet.h"

int main(int argc, char* argv[]){

    /**********Creation du tableau de base et initialisation**********/
    Lettre* tableau = malloc(27*sizeof(Lettre));
    for(int j=0;j<NB;j++)
        tableau[j].suivant=NULL;
    
    /**********Ajout du dictionaire**********/
    ajout_dico(tableau,argv[1]);

   
    /**********Test correction texte**********/
    correction_texte(tableau,argv[2]);
    
    /*********liberation memoire********/
    
    lib_memoire(tableau);
}

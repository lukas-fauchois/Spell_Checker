#include "projet.h"



/**********Fonction pour ajouter un nouveau caractere**********/

void ajout_caractere(char avoile, Lettre* l){
    l->caractere=avoile;                                                    // on enregistre le nouveau caractere et on fait pointer le pointeur associé vers un nouveau tableau de structure
    ptr_tableau tab = malloc(NB*sizeof(Lettre));
    l->suivant=tab;
    for(int j=0;j<NB;j++)
        tab[j].suivant=NULL;

}


/**********Fonction pour ajouter un nouveau mot**********/

int ajout_mot(Lettre* l, char* tab, int lettre_numero){
    int i; 
    i=tab[lettre_numero]-97;                                                  //on converti la lettre en son equivalent pour l'indice
                                                                    
    
    if(tab[lettre_numero]=='\0'){                                             //on regarde si c'est pas la fin du mot
        return 1;
    }
    
    else if ((l+i)->caractere!=tab[lettre_numero]){                           //on prend le pointeur du debut de tableau et on y ajoute l'indice cherché puis on regarde le caractere pointé
        if(tab[lettre_numero]==39){                                           //on test si c'est une apostrophe
            if(tab[(lettre_numero)+1]=='\0') (l+26)->fin_mot=1;               //on test si le prochain caractere du tableau est le caractere de fin pour mettre fin_mot à 1 ou non
            ajout_caractere(tab[lettre_numero],l+26);                         
            (lettre_numero)++;
            return ajout_mot((l+26)->suivant,tab,lettre_numero);
        }
            
        else{   

            if(tab[(lettre_numero)+1]=='\0') (l+i)->fin_mot=1;                //on test si le prochain caractere du tableau est le caractere de fin pour mettre fin_mot à 1 ou non
            ajout_caractere(tab[lettre_numero],l+i);                         
            (lettre_numero)++;
            return ajout_mot((l+i)->suivant,tab,lettre_numero);
        }
    }
    else{
        if(tab[(lettre_numero)+1]=='\0') (l+i)->fin_mot=1;                    //on test si le prochain caractere du tableau est le caractere de fin pour mettre fin_mot à 1 ou non
        (lettre_numero)++;
        return ajout_mot((l+i)->suivant,tab,lettre_numero);
    }
}


/**********Fonction pour ajouter le dictionnaire**********/

void ajout_dico(Lettre* l, char* arg){
    int ind=0;                                                               // indice qui sert a parcourir le mot                                                                                                                    
    char tab[30];
    FILE* fr;
    fr=fopen(arg,"r");
    while(!feof(fr)){
        fscanf(fr,"%s",tab);
        conversion_mot(tab);
        ajout_mot(l,tab,ind);
        
    }
    fclose(fr);
}


/**********Fonction pour tester si un mot est bien présent dans le dico**********/

int presence_mot(Lettre* l, char* tab, int indice, int fmot){
    
    int i;
    if (tab[indice]=='\0'){
        if (fmot==1) {indice=0; fmot=0; return 1;}                          //si on est arrivé au bout du mot recherché on quitte la fonction et on retourne 1 pour trouvé  
        else return 0;
    }
    
    
    else if(l==NULL) {indice=0; return 0;}                                    //si la lettre ne pointe sur aucune autre lettre alors que le mot n'est pas fini on retourne 0
    
    else{                                                                      //dans ce else on cherche a savoir a quel indice du tableau de structure chercher
        if(tab[indice]<97 && tab[indice]>39)
            i=tab[indice]-38;
          
        
        else if(tab[indice]>=97)
            i=tab[indice]-97;
         
        
        else if(tab[indice]==39)
            i=25;
    
        
        if(tab[indice]==(l+i)->caractere){                                    //si on trouve le caractere recherché on relance la fonction en passant a la prochaine lettre du mot
            fmot=0;
            if((l+i)->fin_mot==1) fmot=1;                                     //on regarde si a cet emplacement là il y a un mot fini     
            (indice)++;
            return presence_mot((l+i)->suivant,tab,indice,fmot);
        }
        else {indice=0; return 0;}                                            //sinon le mot n'est pas enregistré
    }
}


/**********Fonction pour convertir tous les mots en minuscules**********/

void conversion_mot(char* mot){                                               //si le mot est une majuscule on le convertie minuscule
    int i=0;
    while(mot[i]!='\0'){
        if(mot[i]>64 && mot[i]<91)
            mot[i]+=32;
        i++;
    }
}


/**********Fonction pour detecter les erreurs dans un texte**********/

void correction_texte(Lettre* l,char* arg){
    FILE* fr;
    fr=fopen(arg,"r");                                                        //on ouvre le fichier .txt a lire
    int indice, fin_mot;
    int compteur_erreur=0;                                                    //compteur pour le nombre d'erreurs et pour dimensionner les mallocs
    char tab[30];
    char* stockage_erreur=malloc(sizeof(tab));                                //malloc qui va servir a stocker les mots avec une erreurs
    while(!feof(fr)){
        indice=0; fin_mot=0;
        fscanf(fr,"%s",tab);
        
        int test=0;
        while(tab[test+1]!='\0'){                                           //boucle qui sert a ne pas considerer comme erreur les , . : " etc...
                test++;
                if(tab[test] == 33 || tab[test] == 44 || tab[test] == 45 || tab[test] == 46 || tab[test] == 58 || tab[test] == 59 || tab[test] == 63){
                    tab[test] = '\0';
                    test=0;
                }
        }
        
        conversion_mot(tab);                                                  //chaque nouveau mot est converti en minuscule
        if(presence_mot(l,tab,indice,fin_mot)==0){                            //on regarde si le mot existe ou pas
            strcpy(stockage_erreur+(30*compteur_erreur),tab);
            compteur_erreur++;
            stockage_erreur=realloc(stockage_erreur,(compteur_erreur+1)*sizeof(tab));  //s'il existe pas on detecte une erreur et on enregistre le mot tout en aggrandissant la taille du stockage
        }
    }
    /**********Affichage*************/
    printf("\nDans le texte il y a %d erreur(s)\n",compteur_erreur);
    if(compteur_erreur!=0){
        printf("Les erreurs sont les suivantes : ");
        for(int i=0;i<compteur_erreur;i++){
            printf("\n");
            printf("%s",stockage_erreur+(30*i));                                  //on affiche les errreurs
        }
    }
    free(stockage_erreur);
    fclose(fr);
}

/**********Fonction pour liberer la memoire**********/

void lib_memoire(Lettre* l){
    for(int i=0; i<NB; i++){
        if(l[i].suivant!=NULL){
            lib_memoire(l[i].suivant);
        }
    }
    
    free(l);
}

            
            
        
        
    
    
/* A savoir : un pointeur de structure pointe sur la premiere valeur de la structure, si on incrémente le pointeur de 1 on aura acces à la seconde valeur de la structure
 * Ainsi si on on fait un tableau de structure, le premier pointeur renvoie sur la premiere valeur de la premiere structure et le pointeur + 1 renverra par exemple vers la premiere valeur de la seconde *structure du tableau
 */

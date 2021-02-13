#include "projet.h"



/**********Fonction pour ajouter un nouveau caractere**********/

void ajout_caractere(char avoile, Lettre* l){
    l->caractere=avoile;                                                     // on enregistre le nouveau caractere et on fait pointer le pointeur associe vers un nouveau tableau de structure
    ptr_tableau tab= malloc(NB*sizeof(Lettre));
    l->suivant=tab;
    for(int j=0;j<NB;j++)
        tab[j].suivant=NULL;

}


/**********Fonction pour ajouter un nouveau mot**********/

int ajout_mot(Lettre* l, char* tab, int lettre_numero){
    int i; 
    i=tab[lettre_numero]-97;                                                  //on converti la lettre en son equivalent pour l'indice
                                                                    
    
    if(tab[lettre_numero]=='\0'){                                             //on regarde si c'est pas la fin du mot
        lettre_numero=1;  
        return 1;
    }
    
    else if ((l+i)->caractere!=tab[lettre_numero]){                           //on prend le pointeur du debut de tableau et on y ajoute l'indice cherche puis on regarde le caractere pointe
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
            printf("\n");
            /*for (int x=0; x<27;x++){
                printf(" %c",(l+x)->caractere);
            }*/
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
    char tab[20];
    FILE* fr;
    fr=fopen(arg,"r");
    while(!feof(fr)){
        fscanf(fr,"%s",tab);
        conversion_mot(tab);
        ajout_mot(l,tab,ind);
        
    }
    fclose(fr);
}


/**********Fonction pour tester si un mot est bien present dans le dico**********/

int presence_mot(Lettre* l, char* tab, int indice, int fmot){
    
    int i;
    if (tab[indice]=='\0'){
        if (fmot==1) {indice=0; fmot=0; return 1;}                          //si on est arrive au bout du mot recherche on quitte la fonction et on retourne 1 pour trouve  
        else return 0;
    }
    
    
    else if(l==NULL) {indice=0; return 0;}                                    //si la lettre ne pointe sur aucune autre lettre alors que le mot n'est pas fini on retourne 0
    
    else{                                                                     //dans ce else on cherche a savoir a quel indice du tableau de structure chercher 
        if(tab[indice]>=97)
            i=tab[indice]-97;
         
        
        else if(tab[indice]==39)
            i=26;
    
        
        if(tab[indice]==(l+i)->caractere){                                    //si on trouve le caractere recherche on relance la fonction en passant a la prochaine lettre du mot
            fmot=0;
            if((l+i)->fin_mot==1) fmot=1;                                     //on regarde si a cet emplacement là il y a un mot fini     
            (indice)++;
            return presence_mot((l+i)->suivant,tab,indice,fmot);
        }
        else {indice=0; return 0;}                                            //sinon le mot n'est pas enregistre
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

gchar* correction_texte(Lettre* l,char* arg, int nb_cara_buff){
    
    int indice, fin_mot;
    int compteur_erreur=0;                                                    //compteur pour le nombre d'erreurs et pour dimensionner les mallocs
    int nb_cara_liste=0;                                                      //indice pour le nombre de cara dans la liste
    int indice_texte = 0;                                                     //indice qui sert a parcourir le texte a corrige
    int indice_new_tab;                                                       //indice qui sert a creer le tableau qui stock le mot a tester
    char tab[30];                                                             //sert a stocker le mot a tester
    char buffer[nb_cara_buff+1];
    for(int i=0;i<nb_cara_buff;i++)
        buffer[i]=arg[i];
    buffer[nb_cara_buff]='\0';                                               //pour placer un caractere de fin de chaine car gtk_buffer n'en a pas
    
    
    struct cell liste_erreur;
    liste_erreur.suivant=NULL;
    struct cell* ptr_liste=&liste_erreur;
    struct cell** ptr_liste_parcours=&ptr_liste;
    
    
    while(buffer[indice_texte]!='\0' && buffer[indice_texte+1]!='\0'){        //la deuxieme condition sert au cas ou l'utilisateur fait entre ou espace a la fin de la saisie

        
        indice=0; fin_mot=0; indice_new_tab=0;
        
        while(buffer[indice_texte]!=' ' && buffer[indice_texte]!='\n' && buffer[indice_texte]!='\0' && buffer[indice_texte]!='.' && buffer[indice_texte]!=',' && buffer[indice_texte]!=':' && buffer[indice_texte]!= '"' && buffer[indice_texte]!= '!' && buffer[indice_texte]!= '?' && buffer[indice_texte]!= '(' && buffer[indice_texte]!= ')' &&  buffer[indice_texte]!=';' && buffer[indice_texte]!='-'){     
            tab[indice_new_tab]=buffer[indice_texte];
            indice_new_tab++;
            indice_texte++;
        }  
       
        
        tab[indice_new_tab]='\0';                                             //on met un caractere de fin pour la fonction presence mot
        indice_texte++;
        conversion_mot(tab);
        
        if(tab[0]!='\0'){
            if(presence_mot(l,tab,indice,fin_mot)==0){
                    tab[indice_new_tab]='\n';
                    compteur_erreur++;
                
                    
                    for(int i=0;i<=indice_new_tab;i++){
                        ajout_tete(ptr_liste_parcours,tab[i]);
                        ptr_liste_parcours=&((*ptr_liste_parcours)->suivant);
                        nb_cara_liste++;
                    }
            }
                    
                
        }
        
      if (buffer[indice_texte-1]=='\0') break;
      
    }
    
    char stock_erreur[nb_cara_liste+1];
    for (int i=0;i<nb_cara_liste;i++){
        stock_erreur[i]=ptr_liste->val;
        ptr_liste=ptr_liste->suivant;
    }
    stock_erreur[nb_cara_liste]='\0';
        
    if(compteur_erreur == 0) return g_strdup_printf("Il y a 0 erreurs");
    else return g_strdup_printf("/!\\  Il y a %d erreur(s)  /!\\  \n\n%s",compteur_erreur,stock_erreur);   //fonction qui sert a recuperer ce qu'aurait envoyer un printf 
}


/**********Fonction pour supprimer la memoire**********/

void lib_memoire(Lettre* l){
    
    for(int i=0; i<27; i++){
        if(l[i].suivant!=NULL)
            lib_memoire(l[i].suivant);
    }
    
    free(l);
}

/**********Fonction concernant la gestion de liste**********/

void ajout_tete(struct cell** l, char val){
    ptr_cellule new=malloc(sizeof(struct cell));
    new->suivant=*l;
    *l=new;
    new->val=val;
}

void suppression_tete(struct cell** l){
    ptr_cellule stock=malloc(sizeof(struct cell));
    stock=*l;
    *l=(*l)->suivant;
    free(stock);
}

void supprimer_liste(struct cell** l){
    while(*l!=NULL){
        suppression_tete(l);
    }
    free(*l); 
}

            
            
        
        
    
    
/* A savoir : un pointeur de structure pointe sur la premiere valeur de la structure, si on incremente le pointeur de 1 on aura acces à la seconde valeur de la structure
 * Ainsi si on on fait un tableau de structure, le premier pointeur renvoie sur la premiere valeur de la premiere structure et le pointeur + 1 renverra par exemple vers la premiere valeur de la seconde *structure du tableau
 */

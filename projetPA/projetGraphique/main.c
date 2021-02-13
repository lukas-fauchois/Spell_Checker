#include "projet.h"




int main (int argc, char **argv){
    
    
/**********Creation du tableau de base et initialisation**********/
Lettre* tableau = malloc(27*sizeof(Lettre));
for(int j=0;j<NB;j++)
    tableau[j].suivant=NULL;

ajout_dico(tableau, argv[1]);

Test T;                                 //structure qui sert a passer plusieurs parametre a une fonction G_CALLBACK
T.p_texte = NULL;
T.dico = tableau;
Test* pointeur_test=&T;


GtkWidget *p_window = NULL;
GtkWidget *p_main_box = NULL;
GtkWidget *p_button = NULL;
GtkWidget *p_button_texte = NULL;
GtkWidget *p_button_test = NULL;
GtkWidget *p_button_box = NULL;
GtkWidget *p_scrolled_window = NULL;


/* Initialisation de GTK+ */
gtk_init (&argc, &argv);

/* Creation de la fenetre principale de notre application */
p_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
//gtk_window_maximize (GTK_WINDOW (p_window));
gtk_window_set_default_size(GTK_WINDOW(p_window),800,900);
gtk_window_set_title (GTK_WINDOW (p_window), "Detecteur de fautes par Evan et Lukas");
g_signal_connect (G_OBJECT (p_window), "destroy", G_CALLBACK (cb_quit), tableau);

/* Creation du conteneur principal */
p_main_box = gtk_vbox_new (FALSE, 0);
gtk_container_add (GTK_CONTAINER (p_window), p_main_box);

/* Creation du la fenetre a deffilement */

p_scrolled_window = gtk_scrolled_window_new(NULL, NULL);
gtk_box_pack_start(GTK_BOX(p_main_box), p_scrolled_window,TRUE,TRUE,0);

/* Creation du texte */

T.p_texte = gtk_text_view_new();
gtk_container_add(GTK_CONTAINER(p_scrolled_window), T.p_texte);

/* Creation du bouton "Quitter" */

p_button = gtk_button_new_from_stock (GTK_STOCK_QUIT);
g_signal_connect (G_OBJECT (p_button), "clicked", G_CALLBACK (cb_quit), tableau);


/* Creation du bouton "Ouvrir" */

p_button_texte = gtk_button_new_from_stock (GTK_STOCK_OPEN);
g_signal_connect (G_OBJECT (p_button_texte), "clicked", G_CALLBACK (cb_open2), T.p_texte);

/* Creation du boutton test */

p_button_test = gtk_button_new_from_stock (GTK_STOCK_FIND);
g_signal_connect (G_OBJECT (p_button_test),"clicked", G_CALLBACK (cb_test), pointeur_test);


/* Creation de la boite a bouton */

p_button_box = gtk_hbutton_box_new();
gtk_box_pack_start (GTK_BOX(p_main_box),p_button_box,FALSE,FALSE,0);
gtk_box_pack_start (GTK_BOX(p_button_box),p_button,FALSE,FALSE,0);
gtk_box_pack_start (GTK_BOX(p_button_box),p_button_test,FALSE,FALSE,0);
gtk_box_pack_start (GTK_BOX(p_button_box),p_button_texte,FALSE,FALSE,0);

/* Affichage de la fenetre principale */
gtk_widget_show_all (p_window);

/* Lancement de la boucle principale */
gtk_main ();


return EXIT_SUCCESS;
}

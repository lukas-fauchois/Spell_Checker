#include "projet.h"
#define DEFAULT_FILE "main.c"


void cb_quit (GtkWidget *p_widget, gpointer user_data){
lib_memoire(user_data);
gtk_main_quit();

/* Parametres inutilises */
(void)p_widget;
}



static void open_file (const gchar *file_name, GtkTextView *p_text_view){
    
  GtkTextBuffer *p_text_buffer = NULL;
  p_text_buffer=gtk_text_view_get_buffer(p_text_view);
  
   g_return_if_fail (file_name && p_text_view);{
    
    gchar *contents = NULL;

    if (g_file_get_contents (file_name, &contents, NULL, NULL)){
        /* Copie de contents dans le GtkTextView */

    }
    else{
        printf("Impossible d'ouvrir le fichier %s\n", file_name);
    }
  
  GtkTextIter iter;
  gtk_text_buffer_get_iter_at_line (p_text_buffer, &iter, 0);
  gtk_text_buffer_insert (p_text_buffer, &iter, contents, -1);

 
  }
}

/* Version ou on ne peut pas choisir le fichier */

/*void cb_open(GtkWidget *p_widget, gpointer user_data){

    open_file(DEFAULT_FILE, GTK_TEXT_VIEW(user_data));
    (void)p_widget;

}*/

/* Version où on peut choisir le fichier */

void cb_open2(GtkWidget *p_widget, gpointer user_data){
    
    GtkWidget *p_dialog = NULL;

    p_dialog = gtk_file_chooser_dialog_new ("Ouvrir un fichier", NULL,
                                            GTK_FILE_CHOOSER_ACTION_OPEN,
                                            GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
                                            GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT,
                                            NULL);
    
    if (gtk_dialog_run (GTK_DIALOG (p_dialog)) == GTK_RESPONSE_ACCEPT){
        gchar *file_name = NULL;
        file_name = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (p_dialog));
        open_file (file_name, GTK_TEXT_VIEW (user_data));
        g_free (file_name), file_name = NULL;
    }
}


/* Fonction pour recuperer le contenu du textView et le verifier puis afficher les erreurs */

void cb_test(GtkWidget *p_widget, Test* t){
    
    gchar* buffer;                                                             //tableau pour recuperer le contenu du buffer
    gchar* resultat;                                                           //variable pour stocker les erreurs
    gchar* resultat_converti;
    gint nombre_cara_buffer=0;
    
    GtkTextIter start;                                                         //variable pour stocker a partir de quelle valeur de debut on veut lire le buffer
    GtkTextIter end;                                                           //même chose mais pour la fin
    
    GtkTextBuffer *p_text_buffer = NULL;                                       //on cree un pointeur pour recuperer le buffer
    p_text_buffer=gtk_text_view_get_buffer(GTK_TEXT_VIEW(t->p_texte));         //on recupere le buffer du texte
    gtk_text_buffer_get_start_iter(p_text_buffer,&start);                      //on regarde la taille du buffer
    gtk_text_buffer_get_end_iter(p_text_buffer,&end);                   
    buffer=gtk_text_buffer_get_text(p_text_buffer,&start, &end,FALSE);         //on recupere le contenu du buffer dans un tableau
    nombre_cara_buffer= gtk_text_buffer_get_char_count(p_text_buffer);
    //printf("nombre_cara_buffer : %d \n",nombre_cara_buffer);
    //printf("buffer : %s \n",buffer);
    
    resultat = correction_texte(t->dico,buffer,nombre_cara_buffer);                               //on test les erreurs du texte
    g_free(buffer);                                                            //on libere
    
    GtkWidget *window = NULL;
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);                             //Creation de la fenetre pour les erreurs
    gtk_window_set_default_size(GTK_WINDOW(window),500,700);
    gtk_window_set_title (GTK_WINDOW (window), "Resultat de la recherche");
    g_signal_connect (G_OBJECT (window), "destroy", G_CALLBACK (cb_close_window), window);
    
    GtkWidget *scrolled_window = NULL;                                         //ajout de la barre de deffilement
    scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER(window), scrolled_window);
    
    
    GtkWidget *label = NULL;                                                   //ajout de la zone de texte 
    resultat_converti = g_locale_to_utf8(resultat, -1, NULL, NULL, NULL);
    g_free(resultat);
    
    label = gtk_label_new(resultat_converti);
    g_free(resultat_converti);
    
    
    gtk_container_add(GTK_CONTAINER(scrolled_window), label);

    gtk_widget_show_all (window);
    
}

void cb_close_window (GtkWidget *p_widget, gpointer user_data){
    gtk_widget_destroy(user_data);
}
    


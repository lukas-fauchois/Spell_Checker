#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include <glib.h>
#include <glib/gprintf.h>
#define NB 27


typedef struct lettre* ptr_tableau;
typedef struct lettre{char caractere; ptr_tableau suivant; int fin_mot}Lettre;

typedef struct{GtkWidget *p_texte; Lettre* dico}Test;

void ajout_caractere(char, Lettre*);

int ajout_mot(Lettre*, char*, int);

int presence_mot(Lettre*, char*, int, int);

void ajout_dico(Lettre*, char*);

void conversion_mot(char*);

gchar* correction_texte(Lettre*, char*);

void cb_quit (GtkWidget *p_widget, gpointer user_data);

//void cb_open(GtkWidget *p_widget, gpointer user_data);

void cb_open2 (GtkWidget *p_widget, gpointer user_data);

void cb_test (GtkWidget *p_widget, Test*);

void cb_close_window (GtkWidget *p_widget, gpointer user_data);

void lib_memoire(Lettre*);


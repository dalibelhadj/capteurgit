#ifndef FONCTION_H_
#define FONCTION_H_
#include <gtk/gtk.h>

struct capteur{
    char id[20];
    char marque[20];
    char date[11];
    char type[20];
    char etage[10];
    int valeur;
};typedef struct capteur Capteur;

void ajout(char nom_fich[], Capteur c);
Capteur recherche(char nom_fich[],char id[]);
void supprimer(char nom_fich[],char id[]);
void modif(char nom_fich[],Capteur c);
void defectueux(char nom_fich[]);
void affiche(GtkWidget *liste,char nom_fich[]);
 #endif

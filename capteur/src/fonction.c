#include <stdio.h> 
#include <string.h> 
#include "fonction.h"

#include <errno.h>
#include <stdlib.h>
#include <stdbool.h>
#include "callbacks.h"
#include <gtk/gtk.h>

void ajout(char nom_fich[], Capteur c)
{FILE *f=NULL;
f=fopen(nom_fich,"a");
if(f!=NULL)
 {
  fprintf(f,"%s %s %s %s %s %d \n",c.id,c.marque,c.date,c.type,c.etage,c.valeur); 
  fclose(f);
 }
}

Capteur recherche(char nom_fich[],char id[])
{FILE *f=NULL;
Capteur c1;
f=fopen(nom_fich,"r");
if(f!=NULL)
{
   while(fscanf(f,"%s %s %s %s %s %d \n",c1.id,c1.marque,c1.date,c1.type,c1.etage,&c1.valeur)!=EOF)
      if(strcmp(c1.id,id)==0)
         {fclose(f);
          return(c1);}
}
}

void supprimer(char nom_fich[],char id[])
{FILE *f=NULL;
FILE *f2=NULL;
Capteur c1;

f=fopen(nom_fich,"r");
f2=fopen("capteur2.txt","w");
if(f!=NULL)
  while(fscanf(f,"%s %s %s %s %s %d \n",c1.id,c1.marque,c1.date,c1.type,c1.etage,&c1.valeur)!=EOF)
      if(strcmp(c1.id,id)!=0)
         fprintf(f2,"%s %s %s %s %s %d \n",c1.id,c1.marque,c1.date,c1.type,c1.etage,c1.valeur);
fclose(f);
fclose(f2);
remove(nom_fich); 
rename("capteur2.txt",nom_fich);
}

void modif(char nom_fich[],Capteur c)
{FILE *f=NULL;
FILE *f2=NULL;
Capteur c1;

f=fopen(nom_fich,"r");
f2=fopen("capteur2.txt","w");
if(f!=NULL)
  {while(fscanf(f,"%s %s %s %s %s %d \n",c1.id,c1.marque,c1.date,c1.type,c1.etage,&c1.valeur)!=EOF)
      if(strcmp(c1.id,c.id)==0)
         fprintf(f2,"%s %s %s %s %s %d \n",c.id,c.marque,c.date,c.type,c.etage,c.valeur); 
      else
         fprintf(f2,"%s %s %s %s %s %d \n",c1.id,c1.marque,c1.date,c1.type,c1.etage,c1.valeur);
   fclose(f);
   fclose(f2);
   remove(nom_fich); 
   rename("capteur2.txt",nom_fich);
   }
}


enum{ 
ID,
MARQUE,
DATE,
TYPE,
ETAGE,
VALEUR,
COLUMNS
};

void affiche(GtkWidget *liste,char nom_fich[])
{Capteur c1;
GtkCellRenderer *renderer;
GtkTreeViewColumn *column;
GtkTreeIter iter;
GtkListStore *store;
char ch1[10];
FILE *f;

store=gtk_tree_view_get_model(liste);
if(store==NULL)
{
	renderer=gtk_cell_renderer_text_new();
	column=gtk_tree_view_column_new_with_attributes("Identifiant",renderer,"text",ID,NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
	gtk_tree_view_column_set_expand(column,TRUE);
	
	renderer=gtk_cell_renderer_text_new();
	column=gtk_tree_view_column_new_with_attributes("Marque",renderer,"text",MARQUE,NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
	gtk_tree_view_column_set_expand(column,TRUE);

	renderer=gtk_cell_renderer_text_new();
	column=gtk_tree_view_column_new_with_attributes("Date",renderer,"text",DATE,NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
	gtk_tree_view_column_set_resizable(column,TRUE);
	gtk_tree_view_column_set_expand(column,TRUE);

	renderer=gtk_cell_renderer_text_new();
	column=gtk_tree_view_column_new_with_attributes("Type",renderer,"text",TYPE,NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
	gtk_tree_view_column_set_expand(column,TRUE);

	renderer=gtk_cell_renderer_text_new();
	column=gtk_tree_view_column_new_with_attributes("Etage",renderer,"text",ETAGE,NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
	gtk_tree_view_column_set_expand(column,TRUE);

	renderer=gtk_cell_renderer_text_new();
	column=gtk_tree_view_column_new_with_attributes("Valeur",renderer,"text",VALEUR,NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
	gtk_tree_view_column_set_expand(column,TRUE);

}

store=gtk_list_store_new(COLUMNS,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING);
f=fopen(nom_fich,"r");
if(f==NULL){return;}
else
 { f = fopen(nom_fich,"a+");
		while(fscanf(f,"%s %s %s %s %s %d \n",c1.id,c1.marque,c1.date,c1.type,c1.etage,&c1.valeur)!=EOF)
	{sprintf(ch1,"%d",c1.valeur);
	
	gtk_list_store_append(store,&iter);
	gtk_list_store_set(store,&iter,ID,c1.id,MARQUE,c1.marque,DATE,c1.date,TYPE,c1.type,ETAGE,
	c1.etage,VALEUR,ch1,-1);
	}
	fclose(f);
	gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
	g_object_unref(store);
 }
}


void defectueux(char nom_fich[])
{FILE *f=NULL;
FILE *f2=NULL;
Capteur c1;

f=fopen(nom_fich,"r");
f2=fopen("defectueux.txt","w");
if(f!=NULL)
  {while(fscanf(f,"%s %s %s %s %s %d \n",c1.id,c1.marque,c1.date,c1.type,c1.etage,&c1.valeur)!=EOF)
      {if(strcmp(c1.type,"Température")==0)
	   if(c1.valeur<10 || c1.valeur>30)
             fprintf(f2,"%s %s %s %s %s %d \n",c1.id,c1.marque,c1.date,c1.type,c1.etage,c1.valeur); 
 	if(strcmp(c1.type,"Humidité")==0)
          if(c1.valeur<40 || c1.valeur>90)
             fprintf(f2,"%s %s %s %s %s %d \n",c1.id,c1.marque,c1.date,c1.type,c1.etage,c1.valeur); 
 
 	if(strcmp(c1.type,"Débit_d'eau")==0)
          if(c1.valeur<0 || c1.valeur>30)
             fprintf(f2,"%s %s %s %s %s %d \n",c1.id,c1.marque,c1.date,c1.type,c1.etage,c1.valeur); 
      }
   }
   fclose(f);
   fclose(f2);
}
/*______________________________________________________________________________________________*/

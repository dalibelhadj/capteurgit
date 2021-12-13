#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include "fonction.h"
int x=0;
Capteur c;

void
on_ajouter_clicked                     (GtkWidget       *button,
                                        gpointer         user_data)
{GtkWidget *windowajout,*windowacc;

windowacc=lookup_widget(button,"acceuil");
gtk_widget_destroy(windowacc);

windowajout=create_ajout();
gtk_widget_show(windowajout);

}


void
on_capteur_defectueux_clicked          (GtkWidget      *button,
                                        gpointer         user_data)
{GtkWidget *windowacc,*treeview;

windowacc=lookup_widget(button,"acceuil");
gtk_widget_destroy(windowacc);

windowacc=lookup_widget(button,"acceuil");
windowacc=create_acceuil();
gtk_widget_show(windowacc);

defectueux("capteur.txt");
treeview = lookup_widget (windowacc, "treeview1");
affiche(treeview,"defectueux.txt");
}


void
on_quitter_clicked                     (GtkWidget       *button,
                                        gpointer         user_data)
{GtkWidget *windowacc;

windowacc=lookup_widget(button,"acceuil");
gtk_widget_destroy(windowacc);

}


void
on_actualiser_clicked                  (GtkWidget       *button,
                                        gpointer         user_data)
{GtkWidget *windowacc,*treeview;

windowacc=lookup_widget(button,"acceuil");
gtk_widget_destroy(windowacc);

windowacc=lookup_widget(button,"acceuil");
windowacc=create_acceuil();
gtk_widget_show(windowacc);

treeview = lookup_widget (windowacc, "treeview1");
affiche(treeview,"capteur.txt");
}


void
on_supprimer_clicked                   (GtkWidget       *button,
                                        gpointer         user_data)
{GtkWidget *windowsup,*windowacc;

windowacc=lookup_widget(button,"acceuil");
gtk_widget_destroy(windowacc);

windowsup=create_supprimer();
gtk_widget_show(windowsup);

}


void
on_Modifier_clicked                    (GtkWidget       *button,
                                        gpointer         user_data)
{GtkWidget *windowmodif,*windowacc;

windowacc=lookup_widget(button,"acceuil");
gtk_widget_destroy(windowacc);

windowmodif=create_modif();
gtk_widget_show(windowmodif);

}


void
on_back1_clicked                       (GtkWidget      *button,
                                        gpointer         user_data)
{GtkWidget *windowacc, *windowajout;

windowajout=lookup_widget(button,"ajout");
gtk_widget_destroy(windowajout);

windowacc=create_acceuil();
gtk_widget_show(windowacc);
}


void
on_back2_clicked                       (GtkWidget       *button,
                                        gpointer         user_data)
{GtkWidget *windowacc, *windowsup;

windowsup=lookup_widget(button,"supprimer");
gtk_widget_destroy(windowsup);

windowacc=create_acceuil();
gtk_widget_show(windowacc);

}

void
on_back3_clicked                       (GtkWidget       *button,
                                        gpointer         user_data)
{GtkWidget *windowacc, *windowmodif;

windowmodif=lookup_widget(button,"modif");
gtk_widget_destroy(windowmodif);

windowacc=create_acceuil();
gtk_widget_show(windowacc);

}


void
on_ajout_clicked                       (GtkWidget       *button,
                                        gpointer         user_data)
{ GtkWidget* input,*windowajout,*windowacc;
 Capteur c;
 GtkWidget *j,*m,*a,*type;
 GtkWidget *val;
char ch1[5],ch2[5],ch3[5];

FILE *f=NULL;
 input = lookup_widget(button, "entry3") ; 
 strcpy(c.id,gtk_entry_get_text(GTK_ENTRY(input))); 
 input = lookup_widget(button, "entry10") ; 
 strcpy(c.marque,gtk_entry_get_text(GTK_ENTRY(input)));  


if(x==1)       strcpy(c.etage,"1er");
else if(x==2)  strcpy(c.etage,"2eme");
else if(x==3)  strcpy(c.etage,"3eme");
else if(x==4)  strcpy(c.etage,"4eme");
else if(x==5)  strcpy(c.etage,"5eme");


val=lookup_widget(button,"spinbutton1"); 

c.valeur=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(val));


j=lookup_widget(button, "combobox1") ; 
strcpy(ch1,gtk_combo_box_get_active_text(GTK_COMBO_BOX(j)));
m=lookup_widget(button, "combobox2") ; 
strcpy(ch2,gtk_combo_box_get_active_text(GTK_COMBO_BOX(m)));
a=lookup_widget(button, "combobox3") ; 
strcpy(ch3,gtk_combo_box_get_active_text(GTK_COMBO_BOX(a)));
sprintf(c.date,"%s/%s/%s",ch1,ch2,ch3);
type=lookup_widget(button, "combobox7") ; 
strcpy(c.type,gtk_combo_box_get_active_text(GTK_COMBO_BOX(type)));

ajout("capteur.txt",c);
windowajout=lookup_widget(button,"ajout");
gtk_widget_destroy(windowajout);

windowacc=lookup_widget(button,"acceuil");
windowacc=create_acceuil();
gtk_widget_show(windowacc);

}



void
on_chercher_clicked                    (GtkWidget       *button,
                                        gpointer         user_data)
{GtkWidget* input,*output;
Capteur c2;
  char id[20],ch1[6];

 input = lookup_widget(button,"entry2") ; 
 strcpy(id,gtk_entry_get_text(GTK_ENTRY(input))); 

c2=recherche("capteur.txt",id);


if(strcmp(c2.id,id)==0)
{
output=lookup_widget(button,"entry5");
gtk_entry_set_text(GTK_ENTRY(output),c2.marque);


output=lookup_widget(button,"label29");
gtk_label_set_text(GTK_LABEL(output),c2.date);

output=lookup_widget(button,"label27");
gtk_label_set_text(GTK_LABEL(output),c2.etage);

output=lookup_widget(button,"label1");
gtk_label_set_text(GTK_LABEL(output),c2.type);

output=lookup_widget(button,"label2");
sprintf(ch1,"%d",c2.valeur);
gtk_label_set_text(GTK_LABEL(output),ch1);


output=lookup_widget(button,"label24");
gtk_label_set_text(GTK_LABEL(output),"Capteur existe");
}
else
{output=lookup_widget(button,"label24");
gtk_label_set_text(GTK_LABEL(output),"Capteur n'existe pas!!");}

}


void
on_modif_clicked                       (GtkWidget       *button,
                                        gpointer         user_data)
{GtkWidget* input,*windowmodif,*windowacc;
Capteur c1;
 GtkWidget *j,*m,*a,*type;
 GtkWidget *val;
char ch1[3],ch2[3],ch3[5];

 input = lookup_widget(button, "entry2") ; 
 strcpy(c1.id,gtk_entry_get_text(GTK_ENTRY(input))); 
 input = lookup_widget(button, "entry5") ; 
 strcpy(c1.marque,gtk_entry_get_text(GTK_ENTRY(input)));   


if(x==6)       strcpy(c1.etage,"1er");
else if(x==7)  strcpy(c1.etage,"2eme");
else if(x==8)  strcpy(c1.etage,"3eme");
else if(x==9)  strcpy(c1.etage,"4eme");
else if(x==10)  strcpy(c1.etage,"5eme");


val=lookup_widget(button,"spinbutton2"); 

c1.valeur=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(val));


j=lookup_widget(button, "combobox4") ; 
strcpy(ch1,gtk_combo_box_get_active_text(GTK_COMBO_BOX(j)));
m=lookup_widget(button,"combobox5") ; 
strcpy(ch2,gtk_combo_box_get_active_text(GTK_COMBO_BOX(m)));
a=lookup_widget(button, "combobox6") ; 
strcpy(ch3,gtk_combo_box_get_active_text(GTK_COMBO_BOX(a)));
sprintf(c1.date,"%s/%s/%s",ch1,ch2,ch3);
type=lookup_widget(button, "combobox8") ; 
strcpy(c1.type,gtk_combo_box_get_active_text(GTK_COMBO_BOX(type)));

modif("capteur.txt",c1);
windowmodif=lookup_widget(button,"modif");
gtk_widget_destroy(windowmodif);

windowacc=lookup_widget(button,"acceuil");
windowacc=create_acceuil();
gtk_widget_show(windowacc);

}


void
on_sup_clicked                         (GtkWidget       *button,
                                        gpointer         user_data)
{GtkWidget* input,*windowsup,*windowacc;
  char id[20];

 input = lookup_widget(button, "entry1") ;
 
 strcpy(id,gtk_entry_get_text(GTK_ENTRY(input))); 
 supprimer("capteur.txt",id);

windowsup=lookup_widget(button,"supprimer");
gtk_widget_destroy(windowsup);

windowacc=lookup_widget(button,"acceuil");
windowacc=create_acceuil();
gtk_widget_show(windowacc);

}


void
on_radiobutton1_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{if(gtk_toggle_button_get_active (GTK_RADIO_BUTTON(togglebutton)))
    x=1;

}


void
on_radiobutton2_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{if(gtk_toggle_button_get_active (GTK_RADIO_BUTTON(togglebutton)))
    x=2;
}


void
on_radiobutton3_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{if(gtk_toggle_button_get_active (GTK_RADIO_BUTTON(togglebutton)))
    x=3;
}


void
on_radiobutton4_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{if(gtk_toggle_button_get_active (GTK_RADIO_BUTTON(togglebutton)))
    x=4;
}


void
on_radiobutton5_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{if(gtk_toggle_button_get_active (GTK_RADIO_BUTTON(togglebutton)))
    x=5;
}


void
on_radiobutton6_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{if(gtk_toggle_button_get_active (GTK_RADIO_BUTTON(togglebutton)))
    x=6;

}


void
on_radiobutton7_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{if(gtk_toggle_button_get_active (GTK_RADIO_BUTTON(togglebutton)))
    x=7;

}


void
on_radiobutton8_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{if(gtk_toggle_button_get_active (GTK_RADIO_BUTTON(togglebutton)))
    x=8;

}


void
on_radiobutton9_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{if(gtk_toggle_button_get_active (GTK_RADIO_BUTTON(togglebutton)))
    x=9;

}


void
on_radiobutton10_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{if(gtk_toggle_button_get_active (GTK_RADIO_BUTTON(togglebutton)))
    x=10;

}




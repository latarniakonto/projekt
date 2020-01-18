#include "standing_controller.h"
//do h

void Enter_Callback_Name( GtkWidget *widget,gpointer entry)
{
  struct stand* wsk=entry;
  const gchar *entry_text;
  entry_text = gtk_entry_get_text (GTK_ENTRY (wsk->textentry[0]));
  strcpy(wsk->nazwa,entry_text);
  printf ("Entry contents: %s\n", entry_text);
}
void Enter_Callback_Value( GtkWidget *widget,gpointer entry)
{
  struct stand* wsk=entry;
  const gchar* entry_text;
  entry_text = gtk_entry_get_text (GTK_ENTRY (wsk->textentry[1]));
  strcpy(wsk->value,entry_text);
  printf ("Entry contents: %s\n", entry_text);
}
struct stand  Make_New_Stand()
{
    struct stand new;
    new.textentry[0]=gtk_entry_new();
    new.textentry[1]=gtk_entry_new();
    gtk_entry_set_max_length(GTK_ENTRY(new.textentry[0]),30);
    gtk_entry_set_max_length(GTK_ENTRY(new.textentry[1]),30);
    g_signal_connect (new.textentry[0], "activate",G_CALLBACK (Enter_Callback_Name),&new);
    g_signal_connect (new.textentry[1], "activate",G_CALLBACK (Enter_Callback_Value),&new);
    gtk_editable_select_region (GTK_EDITABLE (new.textentry[0]),0, gtk_entry_get_text_length(GTK_ENTRY(new.textentry[0])));
    gtk_editable_select_region (GTK_EDITABLE (new.textentry[1]),0, gtk_entry_get_text_length(GTK_ENTRY(new.textentry[1])));
    gtk_widget_show(new.textentry[0]);
    gtk_widget_show(new.textentry[1]);
    return new;
}
void Add(struct list* list,struct stand new_stand)
{
    if(list==NULL)
    {
        struct list* new_list=(struct list*)calloc(1,sizeof(struct list));
        new_list->stand=new_stand;
        new_list->next=NULL;
        list=new_list;
    }else
    {
        while(list->next!=NULL)
        {
            list=list->next;
        }
        struct list* new_list=(struct list*)calloc(1,sizeof(struct list));
        new_list->stand=new_stand;
        new_list->next=NULL;
    }
}

#include "standing_controller.h"
//do h


void Enter_Callback_Name( GtkWidget *widget,gpointer entry)
{
  struct stand* wsk=entry;
  const gchar *entry_text;
  entry_text = gtk_entry_get_text (GTK_ENTRY (wsk->textentry[0]));
  strcpy(wsk->name,entry_text);
  printf ("Entry contents: %s\n", entry_text);
}
void Enter_Callback_Value( GtkWidget *widget,gpointer entry)
{
  struct stand* wsk=entry;
  const gchar* entry_text;
  entry_text = gtk_entry_get_text (GTK_ENTRY (wsk->textentry[1]));
  strcpy(wsk->name,entry_text);
  printf ("Entry contents: %s\n", entry_text);
}
void Enter_Callback_Month( GtkWidget *widget,gpointer entry)
{
  struct month* wsk=entry;
  const gchar* entry_text;
  entry_text = gtk_entry_get_text (GTK_ENTRY (wsk->textentry));
  strcpy(wsk->name,entry_text);
  printf ("Entry contents: %s\n", entry_text);
}
int Current_Row(struct month* months)
{
    struct month* wsk=months;
    while(wsk->next!=NULL)
    {
        wsk=wsk->next;
    }
    struct list* lwsk=wsk->list;
    while(lwsk->next!=NULL)
    {
        lwsk=lwsk->next;
    }
    return lwsk->number;
}
struct stand*  Make_New_Stand()
{
    struct stand* new_stand=(struct stand*)calloc(1,sizeof(struct stand));
    new_stand->textentry[0]=gtk_entry_new();
    new_stand->textentry[1]=gtk_entry_new();
    gtk_entry_set_max_length(GTK_ENTRY(new_stand->textentry[0]),30);
    gtk_entry_set_max_length(GTK_ENTRY(new_stand->textentry[1]),30);
    g_signal_connect (new_stand->textentry[0], "activate",G_CALLBACK (Enter_Callback_Name),new_stand);
    g_signal_connect (new_stand->textentry[1], "activate",G_CALLBACK (Enter_Callback_Value),new_stand);
    gtk_editable_select_region (GTK_EDITABLE (new_stand->textentry[0]),0, gtk_entry_get_text_length(GTK_ENTRY(new_stand->textentry[0])));
    gtk_editable_select_region (GTK_EDITABLE (new_stand->textentry[1]),0, gtk_entry_get_text_length(GTK_ENTRY(new_stand->textentry[1])));
    return new_stand;
}
struct month* Make_New_Month(struct month* months,GtkWidget* grid)
{
    struct month* new_month=(struct month*)calloc(1,sizeof(struct month));
    struct list* new_list=(struct list*)calloc(1,sizeof(struct list));
    new_month->textentry=gtk_entry_new();
    gtk_entry_set_max_length(GTK_ENTRY(new_month->textentry),30);
    g_signal_connect (new_month->textentry, "activate",G_CALLBACK (Enter_Callback_Month),new_month);
    gtk_grid_attach(GTK_GRID(grid),new_month->textentry,1,Current_Row(months),1,1);
    gtk_editable_select_region (GTK_EDITABLE (new_month->textentry),0, gtk_entry_get_text_length(GTK_ENTRY(new_month->textentry)));
    struct month* wsk=months;
    while(wsk->next!=NULL)
    {
        wsk=wsk->next;
    }
    wsk->list->number++;
    new_list=wsk->list;
    new_month->list=new_list;
    new_month->next=NULL;
    new_month->number=0;
    for(int i=0;i<wsk->number;i++)
    {
        struct stand* new_stand=Make_New_Stand();
        gtk_grid_attach(GTK_GRID(grid),new_stand->textentry[0],1,new_month->list->number,1,1);
        gtk_grid_attach(GTK_GRID(grid),new_stand->textentry[1],2,new_month->list->number,1,1);
        gtk_widget_show(new_stand->textentry[0]);
        gtk_widget_show(new_stand->textentry[1]);
        Add(new_month,new_stand);
    }
    return new_month;
}
void Add(struct month* months,struct stand* new_stand)
{
    struct month* wsk=months;
    while(wsk->next!=NULL)
    {
        wsk=wsk->next;
    }
    struct list* lwsk=wsk->list;
    while(lwsk->next!=NULL)
    {
        lwsk=lwsk->next;
    }
    struct list* new_list=(struct list*)calloc(1,sizeof(struct list));
    new_list->stand=new_stand;
    new_list->next=NULL;
    new_list->number=lwsk->number+1;
    lwsk->next=new_list;
    wsk->number++;
}
void Add_To_Months(struct month* months, struct month* month)
{
    if(months==NULL)
    {
        months=month;
        return;
    }
    struct month* wsk=months;
    while(wsk->next!=NULL)
    {
        wsk=wsk->next;
    }
    wsk->next=month;

}

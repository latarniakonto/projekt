#include "standing_controller.h"
#include <stdlib.h>

struct list* list;
int Current_Row(struct list* list)
{
    struct list* wsk=list;
    while(wsk->next!=NULL)
    {
        wsk=wsk->next;
    }
    return wsk->number;
}
void Add_Text_Entry(GtkWidget* grid)
{
    struct stand* new=Make_New_Stand();
    gtk_grid_attach(GTK_GRID(grid),new->textentry[0],1,Current_Row(list),1,1);
    gtk_grid_attach(GTK_GRID(grid),new->textentry[1],2,Current_Row(list),1,1);
    gtk_widget_show(new->textentry[0]);
    gtk_widget_show(new->textentry[1]);
    Add(list,new);
}
void On_Clicked_Button1(GtkWidget* widget,GtkWidget* grid)
{
    Add_Text_Entry(grid);
}

void Make_Buttons(GtkWidget* grid)
{
    GtkWidget* button1;
    GtkWidget* button2;
    button1=gtk_button_new_with_label("Add new standing");
    button2=gtk_button_new_with_label("Add new month");
    gtk_grid_attach(GTK_GRID(grid),button1,0,0,1,1);
    gtk_grid_attach(GTK_GRID(grid),button2,0,1,1,1);
    g_signal_connect(button1,"clicked",G_CALLBACK(On_Clicked_Button1),grid);

}
void Make_Window()
{
    GtkWidget* window;
    GtkWidget* grid;
    grid=gtk_grid_new();
    window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window),"Expensometer");
    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 450);
    g_signal_connect(G_OBJECT(window),"destroy",G_CALLBACK(gtk_main_quit),NULL);
    
    Make_Buttons(grid);
    
    gtk_container_add(GTK_CONTAINER(window),grid);
    gtk_widget_show_all(window);
}

int main(int argc,char* argv[])
{
    list=(struct list*)calloc(1,sizeof(struct list));
    list->next=NULL;
    list->number=0;
    gtk_init(&argc,&argv);
    Make_Window();
    gtk_main();
    return 0;
}

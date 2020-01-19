#include "standing_controller.h"
#include <stdlib.h>

struct list* list;
void Add_Text_Entry(GtkWidget* window)
{
    GtkWidget* grid;
    grid=gtk_grid_new();
    struct stand* new=Make_New_Stand();
    Add(list,new);
    gtk_grid_attach(GTK_GRID(grid),new->textentry[0],0,0,1,1);
    gtk_grid_attach(GTK_GRID(grid),new->textentry[1],1,0,1,1);
    gtk_container_add(GTK_CONTAINER(window),grid);
    gtk_widget_show(new->textentry[0]);
    gtk_widget_show(new->textentry[1]);
    gtk_widget_show(grid);
}
void Make_Window()
{
    GtkWidget* window;
    window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window),"Expensometer");
    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 450);
    g_signal_connect(G_OBJECT(window),"destroy",G_CALLBACK(gtk_main_quit),NULL);
    Add_Text_Entry(window);
    gtk_widget_show(window);
}

int main(int argc,char* argv[])
{
    gtk_init(&argc,&argv);
    Make_Window();
    gtk_main();
    return 0;
}

#include "standing_controller.h"
#include "file_controller.h"

struct month* months;
void Add_Text_Entry(GtkWidget* grid)
{
    struct stand* new_stand=Make_New_Stand();
    gtk_grid_attach(GTK_GRID(grid),new_stand->textentry[0],1,Current_Row(months),1,1);
    gtk_grid_attach(GTK_GRID(grid),new_stand->textentry[1],2,Current_Row(months),1,1);
    gtk_widget_show(new_stand->textentry[0]);
    gtk_widget_show(new_stand->textentry[1]);
    Add(months,new_stand);
}
void Add_New_Month(GtkWidget* grid)
{
    Make_New_Month(months,grid);
}
void On_Clicked_Button1(GtkWidget* widget,GtkWidget* grid)
{
    if(Current_Row(months)!=0)Add_Text_Entry(grid);
}
void On_Clicked_Button2(GtkWidget* widget,GtkWidget* grid)
{
    if(Current_Row(months)==0||months->next->number>=1)Add_New_Month(grid);
}
void Close_App(GtkWidget* widget)
{
    Write_To_File(months->next);
    gtk_main_quit();
}
void Open_App(GtkWidget* grid)
{
    Activate(months->next,grid);
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
    g_signal_connect(button2,"clicked",G_CALLBACK(On_Clicked_Button2),grid);
}
void Make_Window()
{
    GtkWidget* window;
    GtkWidget* scrolled_window;
    GtkWidget* grid;
    grid=gtk_grid_new();
    scrolled_window=gtk_scrolled_window_new(NULL,NULL);
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window),GTK_POLICY_AUTOMATIC, GTK_POLICY_ALWAYS);
    window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window),"Expensometer");
    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 450);
    g_signal_connect(G_OBJECT(window),"destroy",G_CALLBACK(Close_App),NULL);
    
    Open_App(grid);
    Make_Buttons(grid);
    
    gtk_container_add(GTK_CONTAINER(scrolled_window),grid);
    gtk_container_add(GTK_CONTAINER(window),scrolled_window);
    gtk_widget_show_all(window);
}
int main(int argc,char* argv[])
{
    months=Write_From_File();
    gtk_init(&argc,&argv);
    Make_Window();
    gtk_main();
    return 0;
}

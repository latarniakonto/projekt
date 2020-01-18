#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>

static void enter_callback( GtkWidget *widget,GtkWidget *entry )
{
  const gchar *entry_text;
  entry_text = gtk_entry_get_text (GTK_ENTRY (entry));
  printf ("Entry contents: %s\n", entry_text);
}
void EntryTextBox(GtkWidget* window)
{
    GtkWidget* entry;
    GtkWidget* box;
    gint tmp_pos;
    box=gtk_box_new(FALSE,0);
    gtk_container_add(GTK_CONTAINER(window),box);
    gtk_widget_show(box);
    entry = gtk_entry_new ();
    gtk_entry_set_max_length (GTK_ENTRY (entry), 50);
    g_signal_connect (entry, "activate",G_CALLBACK (enter_callback),entry);
    gtk_entry_set_text (GTK_ENTRY (entry), "hello");
    tmp_pos = gtk_entry_get_text_length(GTK_ENTRY(entry));
    gtk_editable_insert_text (GTK_EDITABLE (entry), " world", -1, &tmp_pos);
    gtk_editable_select_region (GTK_EDITABLE (entry),0, gtk_entry_get_text_length(GTK_ENTRY(entry)));
    gtk_box_pack_start (GTK_BOX (box), entry, TRUE, TRUE, 0);
    gtk_widget_show (entry);
}
void MakeWindow()
{
    GtkWidget* window;
    window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window),"Expensometer");
    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 450);
    g_signal_connect(G_OBJECT(window),"destroy",G_CALLBACK(gtk_main_quit),NULL);
    EntryTextBox(window);
    gtk_widget_show(window);
}

int main(int argc,char* argv[])
{
   
    gtk_init(&argc,&argv);
    MakeWindow();
    gtk_main();
    return 0;
}

#ifndef STANDING_CONTROLLER

#define STANDING_CONTROLLER
#include <stdio.h>
#include <string.h>
#include <gtk/gtk.h>

struct stand
{
    char nazwa[256];
    char value[256];
    GtkWidget* textentry[2];
};
struct list
{
    struct stand stand;
    struct list* next;
};
void Enter_Callback_Name( GtkWidget*,gpointer);
void Enter_Callback_Value( GtkWidget*,gpointer);
struct stand  Make_New_Stand();
void Add(struct list*,struct stand);
#endif
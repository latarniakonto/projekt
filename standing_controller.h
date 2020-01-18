#ifndef STANDING_CONTROLLER

#define STANDING_CONTROLLER
#include <stdio.h>
#include <string.h>
#include <gtk/gtk.h>

struct stand
{
    char* nazwa;
    char* value;
    GtkWidget* textentry[2];
};
struct list
{
    struct stand stand;
    struct list* next;
};
void Enter_Callback_Name( GtkWidget*,GtkWidget*);
void Enter_Callback_Value( GtkWidget*,GtkWidget*);
struct stand  Make_New_Stand();
void Add(struct list*,struct stand);
#endif
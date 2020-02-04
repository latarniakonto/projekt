#ifndef STANDING_CONTROLLER

#define STANDING_CONTROLLER
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <gtk/gtk.h>


struct stand
{
    char name[256];
    char value[256];
    GtkWidget* textentry[2];
};
struct list
{
    int number;
    struct stand* stand;
    struct list* next;
};
struct month
{
    char name[256];
    int  number;
    GtkWidget* textentry;
    struct list* list;
    struct month* next;
};
void Enter_Callback_Name( GtkWidget*,gpointer);
void Enter_Callback_Value( GtkWidget*,gpointer);
void Enter_Callback_Month( GtkWidget*,gpointer);
int Current_Row(struct month*);
struct stand*  Make_New_Stand();
void Make_New_Month(struct month*,GtkWidget*);
void Add(struct month*,struct stand*);
void Activate(struct month*,GtkWidget*);
bool Is_Good_Entry(const gchar*);
bool Convert_Formula(const gchar*,gchar[]);
#endif
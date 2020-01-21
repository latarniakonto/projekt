#ifndef STANDING_CONTROLLER

#define STANDING_CONTROLLER
#include <stdio.h>
#include <string.h>
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
int Current_Row(struct month*);
void Enter_Callback_Name( GtkWidget*,gpointer);
void Enter_Callback_Value( GtkWidget*,gpointer);
struct stand*  Make_New_Stand();
struct month* Make_New_Month(struct month*,GtkWidget*);
void Add(struct month*,struct stand*);
void Add_To_Months(struct month*,struct month*);
#endif
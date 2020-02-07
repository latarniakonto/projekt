#include "file_controller.h"


void Write_To_File(struct month* months)
{
    if(months==NULL)return;
    FILE* ofile=fopen("dane.txt","w");
    if(ofile==NULL)return;
    struct month* wsk=months;
    while(wsk!=NULL)
    {
        fprintf(ofile,"%s\n","Month");
        fprintf(ofile,"%s\n",wsk->name);//nazwa miesiąca
        fprintf(ofile,"%d\n",wsk->number);//liczba wierszy w miesiącu
        struct list* lwsk=wsk->list;
        if(lwsk->next!=NULL)
        {
            while(lwsk!=NULL)
            {
                if(lwsk->stand!=NULL)
                {
                    fprintf(ofile,"%d ",lwsk->number);//numer wiersza w GTK_GRID do którego są przypisane name i value
                    fprintf(ofile,"%s ",lwsk->stand->name);//nazwa kategorii wydatków
                    fprintf(ofile,"%s ",lwsk->stand->value);//formuła =10.51+10
                    fprintf(ofile,"\n");
                }
                lwsk=lwsk->next;
            }

        }
        wsk=wsk->next;
    }
    fclose(ofile);
}
struct month* Write_From_File()
{
    FILE* ofile=fopen("dane.txt","r");
    struct month* months=(struct month*)calloc(1,sizeof(struct month));
    struct list* list=(struct list*)calloc(1,sizeof(struct list));
    list->stand=NULL;
    list->next=NULL;
    list->number=0;
    months->list=list;
    months->next=NULL;
    months->name[0]='\0';
    months->number=0;
    if(ofile==NULL)
    {
        return months;
    }
    char data[256];
    while(fscanf(ofile,"%s",data)==1)
    {
        if(strcmp(data,"Month")==0)
        {
            struct month* new_month=(struct month*)calloc(1,sizeof(struct month));
            struct list* empty=(struct list*)calloc(1,sizeof(struct list));
            empty->stand=NULL;
            empty->next=NULL;
            empty->number=0;
            fscanf(ofile,"%s",new_month->name);//nazwa miesiąca
            fscanf(ofile,"%d",&new_month->number);//liczba wierszy w miesiącu
            new_month->list=empty;
            new_month->next=NULL;
            if(new_month->number==0)new_month->list->number=1;
            for(int i=0;i<new_month->number;i++)
            {
                struct list* new_list=(struct list*)calloc(1,sizeof(struct list));
                struct stand* new_standing=(struct stand*)calloc(1,sizeof(struct stand));
                fscanf(ofile,"%d",&new_list->number);//number wiersza w GTK_GRID, do którego przypisany jest name i value
                fscanf(ofile,"%s",new_standing->name);// nazwa kategorii wydatków
                fscanf(ofile,"%s",new_standing->value);// formuła =10.51+10
                new_list->stand=new_standing;
                new_list->next=NULL;
                Add_To_List(new_month,new_list);
            }
            Add_To_Months(months,new_month);
        }   
    }
    return months;
}
void Add_To_List(struct month* months, struct list* new)
{
    if(months==NULL)return;
    struct month* wsk=months;
    while(wsk->next!=NULL)
    {
        wsk=wsk->next;
    }
    struct list* lwsk=wsk->list;
    while(lwsk->next!=NULL)lwsk=lwsk->next;
    lwsk->next=new;
}
void Add_To_Months(struct month* months, struct month* new)
{
    if(months==NULL)return;
    struct month* wsk=months;
    while(wsk->next!=NULL)wsk=wsk->next;
    wsk->next=new;
}
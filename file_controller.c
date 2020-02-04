#include "file_controller.h"


void Write_To_File(struct month* months)
{
    if(months==NULL)return;//chcialbym wiedziec ile jest month i ile jest standings
    FILE* ofile=fopen("dane.txt","w");
    if(ofile==NULL)return;
    struct month* wsk=months;
    while(wsk!=NULL)
    {
        fprintf(ofile,"%s\n","Month");
        fprintf(ofile,"%s\n",wsk->name);
        fprintf(ofile,"%d\n",wsk->number);
        struct list* lwsk=wsk->list;
        if(lwsk->next!=NULL)
        {
            while(lwsk!=NULL)
            {
                if(lwsk->stand!=NULL)
                {
                    fprintf(ofile,"%d ",lwsk->number);
                    fprintf(ofile,"%s ",lwsk->stand->name);
                    fprintf(ofile,"%s ",lwsk->stand->value);
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
    if(ofile==NULL)return NULL;
    struct month* months=(struct month*)calloc(1,sizeof(struct month));
    struct list* list=(struct list*)calloc(1,sizeof(struct list));
    list->stand=NULL;
    list->next=NULL;
    list->number=0;
    months->list=list;
    months->next=NULL;
    months->name[0]='\0';
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
            fscanf(ofile,"%s",new_month->name);
            fscanf(ofile,"%d",&new_month->number);
            new_month->list=empty;
            new_month->next=NULL;
            if(new_month->number==0)new_month->list->number=1;
            for(int i=0;i<new_month->number;i++)
            {
                struct list* new_list=(struct list*)calloc(1,sizeof(struct list));
                struct stand* new_standing=(struct stand*)calloc(1,sizeof(struct stand));
                fscanf(ofile,"%d",&new_list->number);
                fscanf(ofile,"%s",new_standing->name);
                fscanf(ofile,"%s",new_standing->value);
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
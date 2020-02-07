#include "standing_controller.h"
//do h


void Enter_Callback_Name( GtkWidget *widget,gpointer entry)
{
  struct stand* wsk=entry;
  const gchar *entry_text;
  entry_text = gtk_entry_get_text (GTK_ENTRY (wsk->textentry[0]));
  if(entry_text[0]!='\0')
  {
    if(Is_Good_Entry(entry_text))
    {
      strcpy(wsk->name,entry_text);
    }else
    {
      char empty[256]="";
      gtk_entry_set_text(GTK_ENTRY(wsk->textentry[0]),empty);
      strcpy(wsk->name,"EMPTY");
    }
  }else
  {
    strcpy(wsk->name,"EMPTY");
  }
  printf ("Entry contents: %s\n", entry_text);
}
void Enter_Callback_Value( GtkWidget* widget,gpointer entry)
{
  struct stand* wsk=entry;
  const gchar* entry_text;
  entry_text = gtk_entry_get_text (GTK_ENTRY (wsk->textentry[1]));
  if(strcmp(wsk->value,"EMPTY")!=0)//Gdy już jest jakaś formuła zapisana w tym GTK_ENTRY. Możemy ją modyfikować, usunąć
  {
    if(entry_text[0]=='\0')
    {
      strcpy(wsk->value,"EMPTY");
      return;
    }
    if(Is_Good_Entry(entry_text))//Czy tekst zgadza się z konwenansami autora
    {
      gchar edit[256];
      bool t=Convert_Formula(wsk->value,edit);
      if(strcmp(edit,entry_text)==0)//Wciśnięcie ENTER, gdy wyświetlał się wynik formuły wyświetli formułę
      {
        gtk_entry_set_text(GTK_ENTRY(wsk->textentry[1]),wsk->value);
      }else if(strcmp(wsk->value,entry_text)==0)//Wciśnięcie ENTER, gdy wyświetlała się formuła wyświetli wynik formuły
      {
        gtk_entry_set_text(GTK_ENTRY(wsk->textentry[1]),edit);
      }else//Gdy edytujemy formułe
      {
        t=Convert_Formula(entry_text,edit);
        if(t)
        {
          gchar remember[256];
          strcpy(remember,entry_text);
          gtk_entry_set_text(GTK_ENTRY(wsk->textentry[1]),edit);
          strcpy(wsk->value,remember);
        }else//Gdy napiszemy coś co nie zgadza się z konewnansami formuł wyświetlimy starą formułe i z edytowania nic nie wyjdzie
        {
          t=Convert_Formula(wsk->value,edit);
          if(t)gtk_entry_set_text(GTK_ENTRY(wsk->textentry[1]),edit);
        }
      }
    }else
    {
      gchar empty[256]="";
      gtk_entry_set_text(GTK_ENTRY(wsk->textentry[1]),empty);
      strcpy(wsk->value,"EMPTY");
    }
  }else//Gdy nie było żadnej formuły W GTK_ENTRY
  {
    if(entry_text[0]!='\0')
    {
      if(Is_Good_Entry(entry_text))
      {
        gchar edit[256];
        gchar remember[256];
        strcpy(remember,entry_text);
        bool t=Convert_Formula(entry_text,edit);
        if(t)
        {
          gtk_entry_set_text (GTK_ENTRY (wsk->textentry[1]),edit);
          strcpy(wsk->value,remember);
        }else//Gdy formuła nie zgadza się z konwenansami formuł oprożniamy GTK_ENTRY
        {
          gchar empty[256]="";
          gtk_entry_set_text(GTK_ENTRY(wsk->textentry[1]),empty);
          strcpy(wsk->value,"EMPTY");
        }
      }else//Gdy formuła nie zgadza się z konwenansami Is_Good_Entry opróżniamy GTK_ENTRY
      {
        gchar empty[256]="";
        gtk_entry_set_text (GTK_ENTRY (wsk->textentry[1]),empty);
        strcpy(wsk->value,"EMPTY");  
      }
    }else
    {
      strcpy(wsk->value,"EMPTY");
    }  
  }
  printf ("Entry contents: %s\n", entry_text);
}
void Enter_Callback_Month( GtkWidget *widget,gpointer entry)
{
  struct month* wsk=entry;
  const gchar* entry_text;
  entry_text = gtk_entry_get_text (GTK_ENTRY (wsk->textentry[0]));
  if(entry_text[0]!='\0')
  {
    if(Is_Good_Entry(entry_text))
    {
      strcpy(wsk->name,entry_text);
    }else
    {
      char empty[256]="";
      gtk_entry_set_text(GTK_ENTRY(wsk->textentry[0]),empty);
      strcpy(wsk->name,"EMPTY");
    }
  }else
  {
    strcpy(wsk->name,"EMPTY");
  }
  printf ("Entry contents: %s\n", entry_text);
}
int Current_Row(struct month* months)
{
    struct month* wsk=months;
    while(wsk->next!=NULL)
    {
        wsk=wsk->next;
    }
    struct list* lwsk=wsk->list;
    while(lwsk->next!=NULL)
    {
        lwsk=lwsk->next;
    }
    return lwsk->number;
}
struct stand*  Make_New_Stand()
{
    struct stand* new_stand=(struct stand*)calloc(1,sizeof(struct stand));
    new_stand->textentry[0]=gtk_entry_new();
    new_stand->textentry[1]=gtk_entry_new();
    strcpy(new_stand->name,"EMPTY");
    strcpy(new_stand->value,"EMPTY");
    gtk_entry_set_max_length(GTK_ENTRY(new_stand->textentry[0]),30);
    gtk_entry_set_max_length(GTK_ENTRY(new_stand->textentry[1]),120);
    g_signal_connect (new_stand->textentry[0], "activate",G_CALLBACK (Enter_Callback_Name),new_stand);
    g_signal_connect (new_stand->textentry[1], "activate",G_CALLBACK (Enter_Callback_Value),new_stand);
    gtk_editable_select_region (GTK_EDITABLE (new_stand->textentry[0]),0, gtk_entry_get_text_length(GTK_ENTRY(new_stand->textentry[0])));
    gtk_editable_select_region (GTK_EDITABLE (new_stand->textentry[1]),0, gtk_entry_get_text_length(GTK_ENTRY(new_stand->textentry[1])));
    gtk_widget_show(new_stand->textentry[0]);
    gtk_widget_show(new_stand->textentry[1]);
    return new_stand;
}
void Make_New_Month(struct month* months,GtkWidget* grid)
{
    struct month* new_month=(struct month*)calloc(1,sizeof(struct month));
    struct list* new_list=(struct list*)calloc(1,sizeof(struct list));
    new_month->textentry[0]=gtk_entry_new();
    new_month->textentry[1]=gtk_entry_new();
    bool z=false;
    if(months->next!=NULL)//GTK_ENTRY z sumą z poprzedniego miesiąca możemy dodać tylko wtedy, gdy już jakiś miesiąć był wcześniej dodany
    {
      z=true;
      gtk_entry_set_max_length(GTK_ENTRY(new_month->textentry[1]),30);
      gtk_grid_attach(GTK_GRID(grid),new_month->textentry[1],2,Current_Row(months),1,1);
      gtk_entry_set_max_length(GTK_ENTRY(new_month->textentry[1]),30);
      gchar merge[256];
      Gluestick(months,merge);
      gchar edit[256];
      bool t=Convert_Formula(merge,edit);
      if(t)
      {
        gtk_entry_set_text(GTK_ENTRY(new_month->textentry[1]),edit);
        gtk_widget_show(new_month->textentry[1]);
      }

    }
    gtk_entry_set_max_length(GTK_ENTRY(new_month->textentry[0]),30);
    if(!z)//Inaczej rozmieszczone będą na GTK_GRID GTK_ENTRIES w zależności od tego czy pojawi się GTK_ENTRY z sumą z poprzedniego miesiąca
    {
      gtk_grid_attach(GTK_GRID(grid),new_month->textentry[0],1,Current_Row(months),1,1);
    }else
    {
      gtk_grid_attach(GTK_GRID(grid),new_month->textentry[0],1,Current_Row(months)+1,1,1);
    }
    g_signal_connect(new_month->textentry[0],"activate",G_CALLBACK(Enter_Callback_Month),new_month);
    gtk_widget_show(new_month->textentry[0]);
    struct month* wsk=months;
    while(wsk->next!=NULL)
    {
        wsk=wsk->next;
    }
    struct list* lwsk=wsk->list;
    while(lwsk->next!=NULL)
    {
        lwsk=lwsk->next;
    }
    new_list->stand=NULL;
    new_list->next=NULL;
    if(!z)new_list->number=lwsk->number+1;
    else new_list->number=lwsk->number+2;
    new_month->list=new_list;
    new_month->next=NULL;
    new_month->number=0;
    strcpy(new_month->name,"EMPTY");
    for(int i=0;i<wsk->number;i++)//Dodajemy do nowego miesiąca tyle wierszy ile było w poprzednim miesiącu 
    {
        struct stand* new_stand=Make_New_Stand();
        gtk_grid_attach(GTK_GRID(grid),new_stand->textentry[0],1,Current_Row(new_month),1,1);
        gtk_grid_attach(GTK_GRID(grid),new_stand->textentry[1],2,Current_Row(new_month),1,1);
        gtk_widget_show(new_stand->textentry[0]);
        gtk_widget_show(new_stand->textentry[1]);
        Add(new_month,new_stand);
    }
    if(months->next!=NULL)//Przepisujemy nazwy kategorii wydatków z poprzedniego miesiąca do nowego miesiąca
    {
      struct list* lwsk1=wsk->list;
      struct list* mlwsk=new_month->list;
      lwsk1=lwsk1->next;
      mlwsk=mlwsk->next;
      while(lwsk1!=NULL)
      {
        strcpy(mlwsk->stand->name,lwsk1->stand->name);
        if(strcmp(mlwsk->stand->name,"EMPTY")!=0)
        {
          gtk_entry_set_text(GTK_ENTRY(mlwsk->stand->textentry[0]),mlwsk->stand->name);
        }
        lwsk1=lwsk1->next;
        mlwsk=mlwsk->next;
      }
    }
    wsk->next=new_month;
}
void Add(struct month* months,struct stand* new_stand)
{
    struct month* wsk=months;
    while(wsk->next!=NULL)
    {
        wsk=wsk->next;
    }
    wsk->number++;
    struct list* lwsk=wsk->list;
    while(lwsk->next!=NULL)
    {
        lwsk=lwsk->next;
    }
    struct list* new_list=(struct list*)calloc(1,sizeof(struct list));
    new_list->stand=new_stand;
    new_list->next=NULL;
    new_list->number=lwsk->number+1;
    lwsk->next=new_list;
}
void Activate(struct month* months,GtkWidget* grid)
{
    struct month* wsk=months;
    int i=0;
    while(wsk!=NULL)
    {
        wsk->textentry[0]=gtk_entry_new();
        gtk_entry_set_max_length(GTK_ENTRY(wsk->textentry[0]),30);
        g_signal_connect (wsk->textentry[0], "activate",G_CALLBACK (Enter_Callback_Month),wsk);
        gtk_editable_select_region (GTK_EDITABLE (wsk->textentry[0]),0, gtk_entry_get_text_length(GTK_ENTRY(wsk->textentry[0])));
        if(strcmp(wsk->name,"EMPTY")!=0)
        {
            gtk_entry_set_text(GTK_ENTRY(wsk->textentry[0]),wsk->name);
        }
        gtk_grid_attach(GTK_GRID(grid),wsk->textentry[0],1,i,1,1);
        gtk_widget_show(wsk->textentry[0]);
        i++;
        struct list* lwsk=wsk->list;
        lwsk=lwsk->next;
        gchar editing[256];
        editing[0]='=';
        editing[1]='\0';
        while(lwsk!=NULL)
        {
            struct stand* swsk=lwsk->stand;
            swsk->textentry[0]=gtk_entry_new();
            swsk->textentry[1]=gtk_entry_new();
            gtk_entry_set_max_length(GTK_ENTRY(swsk->textentry[0]),30);
            gtk_entry_set_max_length(GTK_ENTRY(swsk->textentry[1]),120);
            g_signal_connect (swsk->textentry[0], "activate",G_CALLBACK (Enter_Callback_Name),swsk);
            g_signal_connect (swsk->textentry[1], "activate",G_CALLBACK (Enter_Callback_Value),swsk);
            gtk_editable_select_region (GTK_EDITABLE (swsk->textentry[0]),0, gtk_entry_get_text_length(GTK_ENTRY(swsk->textentry[0])));
            gtk_editable_select_region (GTK_EDITABLE (swsk->textentry[1]),0, gtk_entry_get_text_length(GTK_ENTRY(swsk->textentry[1])));
            if(strcmp(swsk->name,"EMPTY")!=0)
            {
                gtk_entry_set_text(GTK_ENTRY(swsk->textentry[0]),swsk->name);
            }
            if(strcmp(swsk->value,"EMPTY")!=0)
            {
                gchar edit[256];
                bool t=Convert_Formula(swsk->value,edit);
                if(!t)
                {
                  gchar empty[256]="";
                  gtk_entry_set_text(GTK_ENTRY(swsk->textentry[1]),empty);
                  strcpy(swsk->value,"EMPTY");
                }else
                {
                  strcat(editing,edit);
                  int size=strlen(editing);
                  editing[size]='+';
                  editing[size+1]='\0';
                  gtk_entry_set_text (GTK_ENTRY (swsk->textentry[1]),edit);
                }
            }
            gtk_grid_attach(GTK_GRID(grid),swsk->textentry[0],1,i,1,1);
            gtk_grid_attach(GTK_GRID(grid),swsk->textentry[1],2,i,1,1);
            gtk_widget_show(swsk->textentry[0]);
            gtk_widget_show(swsk->textentry[1]);

            i++;
            lwsk=lwsk->next;
        }
        if(editing[1]=='\0')
        {
          editing[1]='0';
          editing[2]='\0';
        }
        gchar edit[256];
        bool t=Convert_Formula(editing,edit);
        if(t&&wsk->next!=NULL)//Robi to co Gluestick() tylko trochę inaczej i dla funkcji Activate()
        {
          wsk->textentry[1]=gtk_entry_new();
          gtk_entry_set_max_length(GTK_ENTRY(wsk->textentry[1]),30);
          gtk_entry_set_text(GTK_ENTRY(wsk->textentry[1]),edit);
          gtk_grid_attach(GTK_GRID(grid),wsk->textentry[1],2,i,1,1);
          gtk_widget_show(wsk->textentry[1]);
          i++;
        }

        wsk=wsk->next;
        
    }
}
bool Is_Good_Entry(const gchar* text)
{
  const gchar* wsk=text;
  while(*wsk!='\0')
  {
    if(*wsk!=43&&*wsk!=45&&*wsk!=46&&*wsk!=61&&(*wsk<48||*wsk>57)&&(*wsk<65||*wsk>90)&&(*wsk<97||*wsk>122))return false;
    wsk++;
  }
  return true;
}
bool Convert_Formula(const gchar* formula,gchar editing[])
{
  const gchar* wsk=formula;
  if(*wsk!='=')
  {
    return false;
  }
  wsk++;
  double sum=0.;
  int operators=1;
  double i=0;
  double d=0.;
  bool t=true;
  bool r=false;
  bool add=true;
  while(*wsk!='\0')//Dodajemy sumy częściowe formuły, tak aby uzyskać sume całej formuły
  {
    if(operators==1)
    {
      if(*wsk=='+'||*wsk=='-'||*wsk=='.')
      {
        return false;
      }else
      {
        operators=0;
        t=false;
      }
    }
    if(operators==0)
    {
      if(!t)
      {
        if(*wsk=='+')
        {
          if(add)
          {
            sum+=i;
          }else
          {
            sum-=i;
          }
          operators=1;
          add=true;
          i=0.;
        }else if(*wsk=='-')
        {
          if(add)
          {
            sum+=i;
            i=0.;
          }else
          {
            sum-=i;
            i=0.;
          }
          operators=1;
          add=false;
        }else if(*wsk=='.')
        {
          t=true;
        }else
        {
          i*=10.;
          i+=(*wsk-'0'); 
        }
      }else
      {
        if(*wsk=='.')
        {
          return false;
        }
        if(*wsk=='+')
        {
          operators=1;
          if(d<10.)
          {
            if(r)
            {
              d/=100.;
              r=false;
            }
            else d/=10.;
          }else 
          {
            d/=100.;
          }

          if(add)
          {
            sum+=i;
            sum+=d;
          }else
          {
            sum-=i;
            sum-=d;
          }
          i=0.;
          d=0.;
          add=true;
        }else if(*wsk=='-')
        {
          operators=1;
         
          if(d<10.)
          {
            if(r)
            {
              d/=100.;
              r=false;
            }else d/=10.;
          }else
          {
            d/=100.;
          }
          
          if(add)
          {
            sum+=i;
            sum+=d;
          }else
          {
            sum-=i;
            sum-=d;
          }
          i=0.;
          d=0.;
          add=false;
        }else
        {
          d*=10.;
          if(d==0.&&(*wsk)=='0')
          {
            r=true;
          }
          d+=(*wsk-'0');
        }
      }
    }
    wsk++;
  }
  if(add)
  {
    if(d<10.)
    {
      if(r)
      {
        d/=100.;
        r=false;
      } 
      else d/=10.;
    }else 
    {
      d/=100.;
    }
  
    sum+=i;
    sum+=d;
  }else
  {
    if(d<10.)
    {
      if(r)
      {
        d/=100.;
        r=false;
      }
      else d/=10.;
    }else 
    {
      d/=100.;
    }
    
    sum-=i;
    sum-=d;
  }
  //Od tego momentu przerabiamy część całkowitą sumy i część ułamkową sumy na stringa
  sum+=0.001;
  int ipart=floor(sum);
  int fpart=floor((sum-ipart)*100.);
  char ipartc[256];
  char fpartc[256];
  int j=0;
  int k=0;
  int z=0;
  if(ipart==0)
  {
    ipartc[0]='0';
    j++;
  }
  while(ipart>0)
  {
    ipartc[j]=ipart%10+'0';
    j++;
    ipart/=10;
  }

  if(fpart!=0)
  {
    for(int p=j-1;p>=0;p--)
    {
      editing[z]=ipartc[p];
      z++;
    }
    editing[z]='.';
    z++;
    if(sum-floor(sum)<0.1)
    {
      editing[z]='0';
      z++;
    }
    while(fpart>0)
    {
      fpartc[k]=fpart%10+'0';
      k++;
      fpart/=10;
    }
    for(int p=k-1;p>=0;p--)
    {
      editing[z]=fpartc[p];
      z++;
    }
    editing[z]='\0';
  }else
  {
    for(int p=j-1;p>=0;p--)
    {
      editing[z]=ipartc[p];
      z++;
    }
    editing[z]='\0';
  }
  return true;
}
void Gluestick(struct month* months,gchar editing[])
{
  struct month* wsk=months;
  while(wsk->next!=NULL)
  {
    wsk=wsk->next;
  }
  editing[0]='=';
  editing[1]='\0';
  struct list* lwsk=wsk->list;
  lwsk=lwsk->next;
  while(lwsk!=NULL)
  {
    if(strcmp(lwsk->stand->value,"EMPTY")!=0)
    {
      gchar edit[256];
      bool t=Convert_Formula(lwsk->stand->value,edit);
      if(t)
      {
        strcat(editing,edit);
        int size=strlen(editing);
        editing[size]='+';
        editing[size+1]='\0';
      }
    }
    lwsk=lwsk->next;
  }
  if(editing[1]=='\0')
  {
    editing[1]='0';
    editing[2]='\0';
  }
}
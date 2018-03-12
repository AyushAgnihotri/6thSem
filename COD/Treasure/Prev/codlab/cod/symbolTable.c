#include<stdio.h>
#include<string.h>
#include<fcntl.h> /*file operations*/
#include<ctype.h>/* isdigit() and isalpha() */

struct symbol
{
char type[6];
char name[10];
char value[5];
int size;
int addr;
};



struct symbol s[20];
int address=1000;

/*inserting a declaration statement symbols*/
int insert(char sta[30],int x)
{
int flag;
char *tok;
char type[6]="";
char value[10]="";
int size=0;

x++;
tok=strtok(sta," ,+=;\n");
while(tok!=NULL)
{
if(strcmp(tok,"int")==0)               /*if the data type is int*/
{
strcpy(type,"int");
strcpy(value,"0");
size=2;
}
else if(strcmp(tok,"float")==0)        /*if the datatype is float*/
{
strcpy(type,"float");
strcpy(value,"0.0");
size=4;
}
else if(strcmp(tok,"char")==0)        /*if the datatype is char*/
{
strcpy(type,"char");
strcpy(value,"");
size=1;
}
else if(isalpha(tok[0]))             /*if the symbol is identified*/
{
flag=0;
if(search(tok,x-1)<0)                /*searching for any duplicates*/
{
strcpy(s[x].name,tok);
strcpy(s[x].type,type);
strcpy(s[x].value,value);
s[x].size=size;
s[x].addr=address;
address=s[x].addr+s[x].size;
x++;
flag=1;                             /*flagging if no duplicate of the       symbol found*/
}
else
printf("\nDUPLICATE OF %s SYMBOL FOUND",tok);
}
else if(isdigit(tok[0])&&flag==1)              /* if the value for symbol is identified*/
{
x--;
strcpy(s[x].value,tok);
x++;
}
tok=strtok(NULL," ,+=;\n");
}
return x-1;
}



/*searching for a symbol*/
int search(char sym[20],int len)
{
int i;
for(i=0;i<=len;i++)
{
if(strcmp(s[i].name,sym)==0)
return i;
}
return -1;
}





/*creating the symbol table*/
int create(char file[20])
{
int fd;                     /*file descriptor*/
int i=0,j,k=0;
char buffer[200]="";        /*buffer storage*/
char *tok,*sta;
char stat[20][20];       /*statements array storage*/
char type[6];            /*used to set the type of symbols in each declaration statement*/
char value[10];
int size;
int flag;                /*to be flagged whenever a declarative statement is found*/


/*reading the file*/
fd=open(file,O_RDONLY);
read(fd,buffer,200);
printf("\nTHE FILE CONTENTS ARE:\n%s",buffer);



/*splitting the program into statements*/
sta=strtok(buffer,"()}{\n");
while(sta!=NULL)
{
strcpy(stat[i],sta);
i++;
sta=strtok(NULL,"()}{\n");
}


/*checking for the symbols in each statement*/
for(j=0;j<=i;j++)
{
flag=0;
tok=strtok(stat[j]," ,+=;");
while(tok!=NULL)
{
if(strcmp(tok,"int")==0)               /*if the data type is int*/
{
strcpy(type,"int");
strcpy(value,"0");
size=2;
flag=1;
}
else if(strcmp(tok,"float")==0)        /*if the datatype is float*/
{
strcpy(type,"float");
strcpy(value,"0.0");
size=4;
flag=1;
}
else if(strcmp(tok,"char")==0)        /*if the datatype is char*/
{
strcpy(type,"char");
strcpy(value,"");
size=1;
flag=1;
}
else if(isalpha(tok[0])&&flag==1)             /*if the symbol is identified*/
{
strcpy(s[k].name,tok);
strcpy(s[k].type,type);
strcpy(s[k].value,value);
s[k].size=size;
s[k].addr=address;
address=s[k].addr+size;
k++;
}
else if(isdigit(tok[0])&&flag==1)              /* if the value for symbol is identified*/
{
k--;
strcpy(s[k].value,tok);
k++;
}
else break;
tok=strtok(NULL," ,+=;");
}
}
return k-1;
}


/*displaying the symbol table*/
void display(int len)
{
int i;
printf("\nNAME\tSIZE\tTYPE\tADDRESS\tVALUE");
for(i=0;i<=len;i++)
{
printf("\n%s\t%d\t%s\t%d\t%s",s[i].name,s[i].size,s[i].type,s[i].addr,s[i].value);
}
printf("\n");
}


int main()
{
char file[20];               /*file name*/
int num=0;
int n,i;                     /*no of symbols created in symbol table*/
int choice,x;
char sym[20];
char decl[30];
char *tok;
char sta;
printf("\n***************************************SYMBOL TABLE*************************************");
/*file operation*/
printf("\nENTER THE FILE PATH CONTAINING THE PROGRAM: ");
scanf("%s",file);
num=create(file);
while(1)
{
printf("\nTHE SYMBOL TABLE IS CREATED");
printf("\nMENU\n1.SEARCH\n2.DISPLAY\n3.INSERT\n4.MODIFY\n5.DELETE\n6.EXIT");
printf("\nENTER YOUR CHOICE ");
scanf("%d",&choice);
fflush(stdin);
switch(choice)
{
case 1: printf("\nENTER THE SYMBOL TO BE SEARCHED FOR ");
       scanf("%s",sym);
       x=search(sym,num);
       if(x==-1)
       printf("\nSORRY!SEARCH RETURNED NO RESULT");
       else
       {
       printf("\nNAME\tSIZE\tTYPE\tADDRESS\tVALUE");
       printf("\n%s\t%d\t%s\t%d\t%s",s[x].name,s[x].size,s[x].type,s[x].addr,s[x].value);
       printf("\n");
       }
       break;

case 2: display(num); break;


case 3:   
    printf("\nENTER A DECLARATION STATEMENT ");
    scanf("\n%[^\n]",decl);
        num=insert(decl,num);
        printf("\nTHE SYMBOLS OF THE STATEMENT ARE INSERTED INTO THE SYMBOL TABLE");
    display(num);
       break;

case 4: printf("\nENTER THE SYMBOL TO BE MODIFIED ");
    scanf("%s",sym);
    x=search(sym,num);
    if(x==-1)
    printf("\nSORRY THE SYMBOL IS NO FOUND IN THE SYMBOL TABLE");
    else
    {
    printf("\nNAME\tSIZE\tTYPE\tADDRESS\tVALUE");
     printf("\n%s\t%d\t%s\t%d\t%s",s[x].name,s[x].size,s[x].type,s[x].addr,s[x].value);
        printf("\n");
    printf("\nENTER THE NEW VALUE FOR THE SYMBOL ");
    scanf("%s",s[x].value);
    }
    printf("\nTHE SYMBOL HAS BEEN MODIFIED");
    display(num);
    break;

case 5: printf("\nENTER THE SYMBOL TO BE DELETED ");
    scanf("%s",sym);
    x=search(sym,num);
    if(x==-1)
    printf("\nSORRY THE SYMBOL IS NO FOUND IN THE SYMBOL TABLE");
    else
    {
    printf("\nNAME\tSIZE\tTYPE\tADDRESS\tVALUE");
     printf("\n%s\t%d\t%s\t%d\t%s",s[x].name,s[x].size,s[x].type,s[x].addr,s[x].value);
        printf("\n");
    for(i=x;i<=num;i++)
    {
    s[x]=s[x+1];
    }
    printf("\nTHE SYMBOL HAS BEEN DELETED");
    num--;
    display(num);
    }
    break;

case 6: break;
}
}
return 0;
}

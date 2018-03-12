#include<bits/stdc++.h>
using namespace std;
char a[100][100];
int col;
void findFirst(char,char);
void findFollow(char,char);
void folTabOperation(char,char);
void firTabOperation(char,char);
int nnn;
struct firTab
{
    int n;
    char firT[50];
};
struct folTab
{
    int n;
    char folT[50];
};
struct folTab follow[50];
struct firTab first[50];
int main()
{
    freopen("input.txt", "r", stdin);
    int i,j,c=0,cnt=0;
    char ip;
    scanf("%d", &nnn);
    char b[nnn];
    cout << "Production Rules are-\n"; 
    for(i=0;i<nnn;i++)
    {
    scanf("%s",&a[i]);  
    printf("%s\n",&a[i]);  
    }
    for(i=0;i<nnn;i++)
    {   c=0;
    for(j=0;j<i+1;j++)
    {
        if(a[i][0] == b[j])
        {
            c=1;    
            break;
        }    
        }
    if(c !=1)
    {
      b[cnt] = a[i][0];
      cnt++;
    }               

    }

    for(i=0;i<cnt;i++)
    {   col=1;
    first[i].firT[0] = b[i];
    first[i].n=0;
    findFirst(b[i],i);
    }
    for(i=0;i<cnt;i++)
    {
    col=1;
    follow[i].folT[0] = b[i];
    follow[i].n=0;
    findFollow(b[i],i);
     }
     cout << endl;
     cout << "First set is-\n";
   for(i=0;i<cnt;i++)
   {
    for(j=0;j<=first[i].n;j++)
    {
            if(j==0)
            {
                printf("First(%c) : {",first[i].firT[j]);
            }
            else
            {   
                printf(" %c,",first[i].firT[j]);
            }
    }
    printf(" } ");
    printf("\n");
    } 
     printf("\n");
     cout << "Follow set is-\n";
   for(i=0;i<cnt;i++)
   {
    for(j=0;j<=follow[i].n;j++)
    {
            if(j==0)
            {
                printf("Follow(%c) : {",follow[i].folT[j]);
            }
            else
            {   
                printf(" %c,",follow[i].folT[j]);
            }
    }
    printf(" } ");

    printf("\n");
    } 

}
void findFirst(char ip,char pos)
{
    int i;
    for(i=0;i<nnn;i++)
    {
        if(ip == a[i][0])
        {
            if(isupper(a[i][3]))
            {
                findFirst(a[i][3],pos);
            }
            else
        {

        first[pos].firT[col]=a[i][3];
        first[pos].n++;
        col++;
            }
        }
    }
}
void findFollow(char ip,char row)
{   int i,j;
    if(row==0 && col==1)
    {
        follow[row].folT[col]= '$';
        col++;
        follow[row].n++;
    }
    for(i=0;i<nnn;i++)
    {
        for(j=3;j<nnn-1;j++)
        {
            if(a[i][j] == ip)
            {
                if(a[i][j+1] == '\0')
                {
                    if(a[i][j] != a[i][0])
                    {
                        folTabOperation(a[i][0],row);
                    }
                }
                else if(isupper(a[i][j+1]))
                {   if(a[i][j+1] != a[i][0])
                    {
                        firTabOperation(a[i][j+1],row);                                     

                }
                }
                else
                {
                    follow[row].folT[col] = a[i][j+1];  
                    col++;
                    follow[row].n++;            


                }   
            }
        }
    }   
}
void folTabOperation(char ip,char row)
{   int i,j;
    for(i=0;i<nnn-3;i++)
    {
        if(ip == follow[i].folT[0])
        {
            for(j=1;j<=follow[i].n;j++)
            {
                follow[row].folT[col] = follow[i].folT[j];
                col++;
                follow[row].n++;
            }
        }
    }   
}
void firTabOperation(char ip,char row)
{   
    int i,j;
    for(i=0;i<5;i++)
    {
        if(ip == first[i].firT[0])
        {
            for(j=1;j<=first[i].n;j++)
            {
                if(first[i].firT[j] != '0')
                {
                    follow[row].folT[col] = first[i].firT[j];
                    follow[row].n++;
                    col++;                  
                }
                else
                {
                    folTabOperation(ip,row);
                }
            }
        }
    }
}

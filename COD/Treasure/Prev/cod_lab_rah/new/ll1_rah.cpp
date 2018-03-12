#include <stdio.h>
#include <ctype.h>
#include <iostream>
#include <string>
#include <string.h>

using namespace std;

//productions
char pro[10][10];

//first and follow is stored
string firstt[10];
string followw[10];

//First
struct arr1
{
	int n;//holds the number of elements in the struct
	char firT[50];//holds the elements
};

//Follow
struct arr2
{
	int n;//holds the number of elements
	char folT[50];//holds the elements
};

struct arr2 follow[50];
struct arr1 first[50];
int n;
int col;
void findFirst(char,char);
void findFollow(char,char);
void folTabOperation(char,char);
void firTabOperation(char,char);

char nt[10],ter[10],res[10][10][10],temp[10];
int noter=0,nont=0,i,j,k,flag=0,count[10][10],l,m,row,column,index;

int main()
{
	int i,j,c=0,cnt=0;
	char ip;
	char b[100]; 
	
	for(i=0;i<10;i++) {
		for(j=0;j<10;j++) {

			count[i][j]=NULL;

			for(k=0;k<10;k++){
				res[i][j][k]=NULL;
			}
		}
	}
	
	cout << "Enter no of production\n";
	scanf("%d", &n); 
	printf("\nFIRST AND FOLLOW SET \n\nenter productions in format A->B+T\n");
	for(i=0;i<n;i++)
	{
		scanf("%s",pro[i]);  
	}

	//counting number of non-terminals
	for(i=0;i<n;i++) {
		flag=0;
		for(j=0;j<nont;j++) {
       		if(nt[j]==pro[i][0])
			{
				flag=1;
			}
		}
		if(flag==0)
		{
			nt[nont]=pro[i][0];
			nont++;
		}
	}
	cnt=0;
	cnt=nont;
	
	//finding the first of elements
	for(i=0;i<cnt;i++)
	{   
		col=1;
		first[i].firT[0] = nt[i];
		first[i].n=0;
		findFirst(nt[i],i);
	}

	//finding the follow terms
	for(i=0;i<cnt;i++)
	{
		col=1;
		follow[i].folT[0] = nt[i];
		follow[i].n=0;
		findFollow(nt[i],i);
	}
	printf("\n");


	int p=0;
	//print the first elements found in the process
	for(i=0;i<cnt;i++)
	{
		for(j=0;j<=first[i].n;j++)
		{
			if(j==0)
			{
				//printf("First Set = (%c) : {",first[i].firT[j]);
			}
			else
			
			{ 
				//Storing first of non-terminal in firstt[p]
				char ch;
			  	ch = first[i].firT[j];
				firstt[p].push_back(ch);
			}
		}
		cout<<firstt[p]<<'\n';
		p++;
	}   
	printf("\n");
	
	p = 0;
	
	for(i=0;i<cnt;i++)
	{
		for(j=0;j<=follow[i].n;j++)
		{
			if(j==0)
			{
				//printf("Follow Set of (%c) = {",follow[i].folT[j]);
			}
			else
			{   
				//Storing follow in followw[p]
				char ch1 = follow[i].folT[j];
				followw[p].push_back(ch1);
			}
		}
	p++;	
	}
	for(i=0;i<cnt;i++)
		cout<<followw[i]<<'\n';
	printf("\n");
	//LL(1) parsing
	
	for(i=0;i<nont;i++)
	{
		flag=0;
		for(j=0;j<firstt[i].size();j++)
		{
			for(k=0;k<noter;k++)
			{
				if(ter[k] == firstt[i][j])
				{
					flag = 1;
				}
			}
			if(flag == 0)
			{
				if(firstt[i][j] != '0')
				{
					ter[noter] = firstt[i][j];
					noter++;
				}
			}
		}
	}
	for(i=0;i<nont;i++)
	{
		flag=0;
		for(j=0;j<followw[i].size();j++)
		{
			for(k=0;k<noter;k++)
			{
				if(ter[k]==followw[i][j])
				{
					flag=1;
				}
			}
			if(flag==0)
			{
				ter[noter]=followw[i][j];
				noter++;
			}
		}
	}
	for(i=0;i<nont;i++)
	{
		for(j=0;j<firstt[i].size();j++)
		{
			flag=0;
			if(firstt[i][j]=='0')
			{
				column=i;
				for(m=0;m<followw[column].size();m++)
				{
					for(l=0;l<noter;l++)
    				{
    					if(ter[l]==followw[column][m])
    					{
    						row=l;
    					}
    				}
    				temp[0]=nt[column];
    				temp[1]='-' ;
    				temp[2]='>';
    				temp[3]='#';
    				temp[4]='\0';
    				printf("temp %s",temp);
    				strcpy(res[column][row],temp);
    				count[column][row]+=1;
    				for(k=0;k<10;k++){
    					temp[k]=NULL;        }
    			}

			}
    		else{
    			for(l=0;l<noter;l++)
    			{
    				if(ter[l]==firstt[i][j])
    				{
    					row=l;
    				}
    			}
    			for(k=0;k<n;k++){
    				if(nt[i]==pro[k][0])
    				{
    					column=i;
    					if((pro[k][3]==firstt[i][j])&&(pro[k][0]==nt[column]))
    					{
    						strcpy(res[column][row],pro[k]);
    						count[column][row]+=1;
    					}
    					else
    					{
    						if((isupper(pro[k][3]))&&(pro[k][0]==nt[column]))
    						{
    							flag=0;
    							for(m=0;m<nont;m++)
    							{
    								if(nt[m]==pro[k][3]){index=m;flag=1;}
    							}
    							if(flag==1){
    								for(m=0;m<firstt[index].size();m++)
    								{
										if(firstt[i][j]==firstt[index][m])
    									{										
											strcpy(res[column][row],pro[k]);
        									count[column][row]+=1;
										}
    								}
    							}
   							 }
						}
					}
				}
			}
		}
	}
	printf("LL1 Table\n\n");
	flag=0;
	for(i=0;i<noter;i++)
	{
		printf("\t%c",ter[i]);
	}
	for(j=0;j<nont;j++)
	{
		printf("\n\n%c",nt[j]);
		for(k=0;k<noter;k++)
		{
			printf("\t%s",res[j][k]);
			if(count[j][k]>1){flag=1;}
		}
	}
	if(flag==1){printf("\nThe given grammar is not LL1");}
	else{printf("\nThe given grammar is LL1");}
//getch();
}

	//


void findFirst(char ip,char pos)
{
	int i;
       //check the entire rows
	for(i=0;i<n;i++)
	{
		//if the first word matches
		if(ip == pro[i][0])
		{
			//if it is a non terminal find its first
			if(isupper(pro[i][3]))
			{
				findFirst(pro[i][3],pos);
			}
			// if non terminal add that part 
			else
			{
				first[pos].firT[col]=pro[i][3];
				firstt[pos][col] = first[pos].firT[col];
				first[pos].n++;
				col++;
			}
		}
	}
}

void findFollow(char ip,char row)
{   
	int i,j;
	//for the first production always '$' will be the follow
	if(row==0 && col==1)
	{
		follow[row].folT[col]= '$';
		col++;
		follow[row].n++;
	}
	//check all the productions
	for(i=0;i<n;i++)
	{
		//check if it is in the RHS part
		for(j=3;j<n;j++)
		{
			//if we find the char is same as the ip
			if(pro[i][j] == ip)
			{
				//if we reach the end then 
				if(pro[i][j+1] == '\0')
				{
					//check if the production lhs and ip are same or not 
					if(pro[i][j] != pro[i][0])
					{
						folTabOperation(pro[i][0],row);
					}

				}
				//id the next term of the ip is non-terminal then its first will be the follow of ip
				else if(isupper(pro[i][j+1]))
				{   
					if(pro[i][j+1] != pro[i][0])
					{
						firTabOperation(pro[i][j+1],row);                                     
					}

				}
				//if the next term is a terminal then the follow will be that terminal itself
				else
				{
					follow[row].folT[col] = pro[i][j+1];  
					col++;
					follow[row].n++;         
				}   
			}
		}
	}   

}

//this function just adds the elemts of follow of rhs to it if the ip is the last elemt of the production
void folTabOperation(char ip,char row)
{   
	int i,j;
	//for the elements in the table
	for(i=0;i<5;i++)
	{
		//if we found the element whos follow is the requireds follow we just attach it here
		if(ip == follow[i].folT[0])
		{
			//all the elemts of the elements 	
			for(j=1;j<=follow[i].n;j++)
			{
				follow[row].folT[col] = follow[i].folT[j];
				col++;
				follow[row].n++;
			}
		}
	}   

}

//this function adds the elements of the first of the next non terminal of the ip
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

/*
   input productions 
   
   E->TA
   A->+TA
   A->0
   T->FB
   B->*FB
   B->0
   F->(E)
   F->#

 */








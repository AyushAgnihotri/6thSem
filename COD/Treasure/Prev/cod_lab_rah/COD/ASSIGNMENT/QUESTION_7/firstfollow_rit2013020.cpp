#include<stdio.h>
#include<ctype.h>
#include <iostream>

using namespace std;

char a[100][100];

//epsilon represented by 0

//THIS STRUCTURE FOR HOLDING THE FIRST OF THE PRODUCTION 
struct arr1
{
	int n;//holds the number of elements in the struct
	char firT[50];//holds the elements
};

//THIS STRUCTURE FOR HOLDING THE FOLLOW OF THE PRODUCTION
struct arr2
{
	int n;//holds the number of elements
	char folT[50];//holds the elements
};

//50 SUCH ELEMENTS
struct arr2 follow[50];
//50 SUCH ELEMENTS
struct arr1 first[50];
//SOME GLOBAL VARIALES DECLARATION
int n;//NUMBER OF PRODUCTION
int col;
//THE FUNCTONS USED IN THE PROGRAM
//TO FIND THE FIRST
void findFirst(char,char);
//TO FIND THE FOLLOW
void findFollow(char,char);
//TO FIND THE 
void folTabOperation(char,char);
void firTabOperation(char,char);


int main()
{
	int i,j,c=0,cnt=0;
	char ip;
	char b[100]; 

	//FOR STORING THE NUMBER OF PRODUCTIONS
	cout << "Enter no of production\n";
	scanf("%d", &n); 
	printf("\nFIRST AND FOLLOW SET \n\nenter productions in format A->B+T\n");

	//SCAN THE PRODUCTIONS
	for(i=0;i<n;i++)
	{
		scanf("%s",a[i]);  
	}

	//THIS COUNTS THE NUMBER OF NON-TERMINALS	
	for(i=0;i<n;i++)
	{   
		c=0;
		for(j=0;j <= i;j++)
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
	printf("\n");
	//printf("%d",cnt);

	//finding the first of elements
	for(i=0;i<cnt;i++)
	{   
		col=1;
		first[i].firT[0] = b[i];
		first[i].n=0;
		findFirst(b[i],i);
	}

	//finding the follow terms
	for(i=0;i<cnt;i++)
	{
		col=1;
		follow[i].folT[0] = b[i];
		follow[i].n=0;
		findFollow(b[i],i);
	}
	printf("\n");


	//print the first elements found in the process
	for(i=0;i<cnt;i++)
	{
		for(j=0;j<=first[i].n;j++)
		{
			if(j==0)
			{
				printf("First Set = (%c) : {",first[i].firT[j]);
			}
			else
			{   
				printf("%c,",first[i].firT[j]);
			}
		}
		printf("} ");
		printf("\n");
	}   
	printf("\n");
 
        //print the follow elements found in the process
	for(i=0;i<cnt;i++)
	{
		for(j=0;j<=follow[i].n;j++)
		{
			if(j==0)
			{
				printf("Follow Set of (%c) = {",follow[i].folT[j]);
			}
			else
			{   
				printf("%c,",follow[i].folT[j]);
			}
		}
		printf("} ");
		printf("\n");
	} 

}

//find the first of the element
void findFirst(char ip,char pos)
{
	int i;
       //check the entire rows
	for(i=0;i<n;i++)
	{
		//if the first word matches
		if(ip == a[i][0])
		{
			//if it is a non terminal find its first
			if(isupper(a[i][3]))
			{
				findFirst(a[i][3],pos);
			}
			// if non terminal add that part 
			else
			{
				first[pos].firT[col]=a[i][3];
				first[pos].n++;
				col++;
			}
		}
	}
}

//find the follow of the elment
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
			if(a[i][j] == ip)
			{
				//if we reach the end then 
				if(a[i][j+1] == '\0')
				{
					//check if the production lhs and ip are same or not 
					if(a[i][j] != a[i][0])
					{
						folTabOperation(a[i][0],row);
					}

				}
				//id the next term of the ip is non-terminal then its first will be the follow of ip
				else if(isupper(a[i][j+1]))
				{   
					if(a[i][j+1] != a[i][0])
					{
						firTabOperation(a[i][j+1],row);                                     
					}

				}
				//if the next term is a terminal then the follow will be that terminal itself
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







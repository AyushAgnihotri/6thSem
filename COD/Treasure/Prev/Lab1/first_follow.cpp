#include<bits/stdc++.h>
#define MX 100
using namespace std;
char a[MX][MX];

// Structure for first table
struct firTab
{
    int n;
    char firT[MX];
};

// structure for follow table
struct folTab
{
    int n;
    char folT[MX];
};

// struct variables
struct folTab follow[MX];
struct firTab first[MX];

int col;
void findFirst(char,char);
void findFollow(char,char);
void folTabOperation(char,char);
void firTabOperation(char,char);
int n;

// function for finding the first
void findFirst(char ip,char pos)
{
    int i;
    for(i = 0; i < n; i++) {
    	//checks whether the first element is Non_Terminal
        if(ip == a[i][0]) {
            if(isupper(a[i][3])){
                findFirst(a[i][3],pos);
            }	
            else
        {
		//assigns the first to the row
        first[pos].firT[col] = a[i][3];
        first[pos].n++;
        col++;
            }
        }
    }
}

//function for finding the follow
void findFollow(char ip,char row) {   
	int i,j;
    
    //assignning the value $ for the first production as $ is always there for start symbol
	if(row == 0 && col == 1)
    {
        follow[row].folT[col]= '$';
        col++;
        follow[row].n++;
    }
    
    for(i=0;i<n;i++) {
    	
        for(j=3;j<n;j++) {
        	
            if(a[i][j] == ip) {
            	//if the element is present at the end the follow should be the follow of RHS
                if(a[i][j+1] == '\0') {
                    if(a[i][j] != a[i][0]) {                    	
                        folTabOperation(a[i][0],row);
                    }
                }
                //if the element is a NON_TERMINAL then follow will be the First of the next elements 
                else if(isupper(a[i][j+1])) {   
					if(a[i][j+1] != a[i][0]) {
                        firTabOperation(a[i][j+1],row);                                     
                	}
                }
                //if all the above conditions fail then the follow will be immediate element present 
                else {
                    follow[row].folT[col] = a[i][j+1];  
                    col++;
                    follow[row].n++;            


                }   
            }
        }
    }   
}

//function for calculating the follow when the element occured during the operation in FindFollow fuction
void folTabOperation(char ip,char row) {   
	int i,j;
	
    for(i = 0; i < 5; i++) {
        if(ip == follow[i].folT[0]) {
            for(j = 1; j <= follow[i].n; j++) {
                follow[row].folT[col] = follow[i].folT[j];
                col++;
                follow[row].n++;
            }
        }
    }   
}

//function for calculating the First when the element occured during the operation in FindFollow fuction
void firTabOperation(char ip,char row) {   
    int i,j;
        
    for(i = 0; i < 5; i++) {
        if(ip == first[i].firT[0]) {
		    for(j = 1; j <= first[i].n; j++) {
                if(first[i].firT[j] != '0') {
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
int main() {
    int i, j, c = 0, cnt = 0;
    char ip;
    char b[MX]; 

  //freopen("inp.txt","r",stdin);
  freopen("in3.txt","r",stdin);

//input the number of productions
    cin>>n;

//input the productions
    for(i = 0; i < n; i++){ 	
    	scanf("%s", a[i]);  
    }
    
//couting the no of non-terminals in the production rules
    for(i = 0; i < n; i++) {
		c=0;
		
		for(j = 0; j < i + 1; j++) { 
		    if(a[i][0] == b[j]) { 
             	c=1;    
            	break;
        	}
        }
        
    	if(c != 1) {
      		b[cnt] = a[i][0];
      		cnt++;
    	}               
    }
     printf("\n");

//finding the first elements
    for(i = 0; i < cnt; i++){   
		col = 1;
    	first[i].firT[0] = b[i];
    	first[i].n=0;
    	findFirst(b[i],i);
    }

//finding the follow elements
    for(i = 0; i < cnt; i++) {   
    	col=1;
    	follow[i].folT[0] = b[i];
    	follow[i].n=0;
    	findFollow(b[i],i);
     }
      printf("\n");
     
//printing the first elements
   for(i = 0; i < cnt; i++) {
    	for(j = 0; j <= first[i].n; j++) {
            if(j == 0) {
                printf("First(%c) = {", first[i].firT[j]);
            }
            else
            {   
                printf(" %c", first[i].firT[j]);
            }
    }
    	printf(" } ");
    	printf("\n");
	} 
     printf("\n");

//printing the follow elements
   for(i = 0; i < cnt; i++) {
    	for(j = 0; j <= follow[i].n; j++) {
            if(j==0) {
                printf("Follow(%c) = {", follow[i].folT[j]);
            }
            else
            {   
                printf(" %c", follow[i].folT[j]);
            }
    	}
    	printf(" } ");
    	printf("\n");
    }
    
    return 0;
}

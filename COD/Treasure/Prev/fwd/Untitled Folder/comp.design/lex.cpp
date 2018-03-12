#include<cstdio>
#include<cstring>
#include<iostream>
#include<string>
#include<cstdlib>
#include<ctype.h>
using namespace std;

FILE *fp;
//FILE *ft;
int numflag = 0, a, f = 0;
char punc[] = { ',', ';', ':', '\'', '\"', '(', ')', '{', '}', '<<', '>>', '@', '~', '\\' };
char ar_op[] = { '+', '-', '*', '/' };
char *comp_op[] = { "<", ">", "=", "==", "<=", ">=", "!=" };
char *for_spec[] = { "*n", "*d", "a" };
char *key[] = { "sart","procedure","stop","end","if","else","for","swt","case","dflt","cont","none","read","write","epow","npow","sqrt","cls" };

char *dt[] = { "num","dnum","alp","neg","pos" };

char predirect[3][14] = { "open", "funct", "val" };

char header[1][10] = { "lib_file" };

void skip();
void analyze();
int punct(char);
int isop(char);
void check(char[]);
char c, ch, sop;
int fop = 0;
//char char_cnst[]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
//const string lower("abcdefghijklmnopqrstuvwxyz");
//char num_cnst[]={'0','1','2','3','4','5','6','7','8','9'};

int main()

{
	
		fp = fopen("hello.cpp", "r");
		if (fp == NULL)
			printf("\nCannot open the file");

//		else

			//ft = fopen("tokens.txt", "w");

			//	if (ft == NULL)

			//	printf("\nCannot open file");

			//printf("\nCannot open the file");

		string s;
		while (getline(cin, s)) {
			analyze();
		}

		//printf("End of file");

		fclose(fp);
	
		//fclose(ft);
	
//		getch();
		return 0;
}

void analyze()

{
	
		char token[10000];
	
		int j = 0;
	
		while (!feof(fp))
		{
			getc(fp);
		
			if (c == '~')
			{
					skip();
			
			}
		
			else if (c == ' ')
				while ((c = getc(fp)) != '"');
		
			else if (isalpha)
			{
			
			if (numflag == 1)
			{
				
					token[j] = '\0';
				
					check(token);
				
					numflag = 0;
				
					j = 0;
				
					f = 0;
				
			}
			
			else
			{
				
					token[j] = c;
					j++;
				
			}
			
			if (f == 0)
				f = 1;
			
		}
		
		else if (isalnum)
		
		{
			
			if (numflag == 0)
				
				numflag = 1;
			
				token[j] = c;
			
				j++;
			
		}
		
		else
		
		{
			if (punct)
				
			{
				
				if (numflag == 1)
					
				{
					
						token[j] = '\0';
					
						check(token);
					
						numflag = 0;
					
				}
				
				if (f == 1)	
				{
						token[j] = '\0';
						numflag = 0;
						check(token);
				}
				
					j = 0;
					f = 0;
					printf("\n delimiters \t%c", c);
				
			}
		
			else if (isop)
			
			{
				
				if (numflag == 1)
					
				{
						token[j] = '\0';
						check(token);
						numflag = 0;
					
						j = 0;
					
						f = 0;
					
				}
				
				if (f == 1)
					
				{
					
						token[j] = '\0';
					
						j = 0;
					
						f = 0;
					
						numflag = 0;
					
						check(token);
					
				}
				
				if (fop == 1)
					
				{
					
						fop = 0;
					
						printf("\n operator \t %c%c", c, sop);
					
				}
				
				else
				
				printf("\n operator \t%c", c);
				
			}
			
			else if (c == '.')
			
			{
				
					token[j] = c;
		
					j++;
			}
			
		}
	}
	
}

int punct(char c)

{
	
		int i;
	
	for (i = 0; i<14; i++)
		
	{
		
		if (c == punc[i])
			
			return 1;
		
	}
	
		return 0;
	
}

int isop(char c)

{
	
		int i, j;
	
		char ch;
	
	for (i = 0; i<7; i++)
		
	{
		
		if (c == ar_op[i])
			
		{
			
				ch = getc(fp);
			
			for (j = 0; j<6; j++)
				
			{
				
				if (ch == ar_op[j])
					
				{
					
						fop = 1;
					
						sop = ch;
					
						return 1;
					
				}
				
			}
			
				ungetc(ch, fp);
			
				return 1;
			
		}
		
	}
	
		return 0;
	
}

void check(char t[])

{
	
		int i;
	
	if (numflag == 1)
		
	{
		
			printf("\n number \t\t%s", t);
		
			return;
		
	}
	
	for (i = 0; i<2; i++)
		
	{
		
		if (strcmp(t, predirect[i]) == 0)
			
		{
	
				printf("\n preprocessor directive %s", t);
			
				return;
			
		}
		
	}
	
	for (i = 0; i<6; i++)
		
	{
		
			a = strcmp(t, header[i]);
		
		if (a == 0)
			
		{
				printf("\n header file \t%s", t);
			
				return;
			
		}
		
	}
	
	for (i = 0; i<21; i++)
		
	{
	
		if (strcmp(key[i], t) == 0)
			
		{
			
				printf("\n keyword \t\t%s", key[i]);
			
				return;
			
		}
		
	}
	
		printf("\n identifier \t%s", t);
	
}



void skip()

{
	while (f == 0)
	{
		ch = getc(fp);
		
		if (ch == '~')
			f = 1;
		
	}
	
		f = 0;
	
}

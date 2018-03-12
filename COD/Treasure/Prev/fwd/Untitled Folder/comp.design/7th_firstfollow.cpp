#include<stdio.h>
#include<ctype.h>
#define mx 100
char a[mx][mx];
int size_pro;

struct firTab
{
	int n;
	char firT[100];
};

struct folTab
{
	int n;
	char folT[100];
};
struct folTab follow[100];
struct firTab first[100];

int col;
void findFirst(char, char);
void findFollow(char, char);
void folTabOperation(char, char);
void firTabOperation(char, char);

int main()
{
	
	printf("\nFIRST AND FOLLOW SETS\n\n");
	int i, j, c = 0, cnt = 0;
	char ip;
	char b[100];
	
	printf("number of production rules\n");
	scanf("%d", &size_pro);

	printf("\nFIRST AND FOLLOW SET \n\nenter productions in format A->B+T and 0 for null\n");
	for (i = 0; i<size_pro; i++)
	{
		scanf("%s", a[i]);
	}

	for (i = 0; i<size_pro; i++)
	{
		c = 0;
		for (j = 0; j<i + 1; j++)
		{
			if (a[i][0] == b[j])
			{
				c = 1;
				break;
			}
		}
		if (c != 1)
		{
			b[cnt] = a[i][0];
			cnt++;
		}

	}
	printf("\n");

	for (i = 0; i<cnt; i++)
	{
		col = 1;
		first[i].firT[0] = b[i];
		first[i].n = 0;
		findFirst(b[i], i);
	}
	for (i = 0; i<cnt; i++)
	{
		col = 1;
		follow[i].folT[0] = b[i];
		follow[i].n = 0;
		findFollow(b[i], i);
	}

	printf("\n");
	for (i = 0; i<cnt; i++)
	{
		for (j = 0; j <= first[i].n; j++)
		{
			if (j == 0)
			{
				printf("First(%c) : {", first[i].firT[j]);
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
	for (i = 0; i<cnt; i++)
	{
		for (j = 0; j <= follow[i].n; j++)
		{
			if (j == 0)
			{
				printf("Follow(%c) : {", follow[i].folT[j]);
			}
			else
			{
				printf(" %c", follow[i].folT[j]);
			}
		}
		printf(" } ");

		printf("\n");
	}

}
void findFirst(char ip, char pos)
{
	int i;
	for (i = 0; i<size_pro; i++)
	{
		if (ip == a[i][0])
		{
			if (isupper(a[i][3]))
			{
				findFirst(a[i][3], pos);
			}
			else
			{

				first[pos].firT[col] = a[i][3];
				first[pos].n++;
				col++;
			}
		}
	}
}
void findFollow(char ip, char row)
{
	int i, j;
	if (row == 0 && col == 1)
	{
		follow[row].folT[col] = '$';
		col++;
		follow[row].n++;
	}
	for (i = 0; i<size_pro; i++)
	{
		for (j = 3; j<size_pro-1; j++)
		{
			if (a[i][j] == ip)
			{
				if (a[i][j + 1] == '\0')
				{
					if (a[i][j] != a[i][0])
					{
						folTabOperation(a[i][0], row);
					}
				}
				else if (isupper(a[i][j + 1]))
				{
					if (a[i][j + 1] != a[i][0])
					{
						firTabOperation(a[i][j + 1], row);

					}
				}
				else
				{
					follow[row].folT[col] = a[i][j + 1];
					col++;
					follow[row].n++;


				}
			}
		}
	}
}
void folTabOperation(char ip, char row)
{
	int i, j;
	for (i = 0; i<5; i++)
	{
		if (ip == follow[i].folT[0])
		{
			for (j = 1; j <= follow[i].n; j++)
			{
				follow[row].folT[col] = follow[i].folT[j];
				col++;
				follow[row].n++;
			}
		}
	}
}
void firTabOperation(char ip, char row)
{
	int i, j;
	for (i = 0; i<5; i++)
	{
		if (ip == first[i].firT[0])
		{
			for (j = 1; j <= first[i].n; j++)
			{
				if (first[i].firT[j] != '0')
				{
					follow[row].folT[col] = first[i].firT[j];
					follow[row].n++;
					col++;
				}
				else
				{
					folTabOperation(ip, row);
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
--------
S -> ABC
A -> df | epsilon
B -> f | epsilon
C -> g | epsilon
*/

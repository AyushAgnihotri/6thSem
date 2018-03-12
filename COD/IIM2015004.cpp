#include<bits/stdc++.h>
#include<fcntl.h> 
#include<unistd.h>

struct symbol
{
	char tp[60], nm[100], val[50];
	int size,addr;
} s[2000];

int  addrs=1000;

int generate(char file[200])
{
	char bf[20000]="", *tok, *sta, stat[200][200], tp[60], val[100];
	int fd, i=0, j, k=0, size, flag;
	fd = open(file,O_RDONLY);
	read(fd,bf,20000);
	sta=strtok(bf,"()}{\n");
	while(sta != NULL) {
		strcpy(stat[i], sta);
		i++;
		sta=strtok(NULL,"()}{\n");
	}

	for(j = 0 ; j <= i; j++) {
		flag=0;
		tok=strtok(stat[j]," ,+=;");
		while(tok!=NULL) {
			if( strcmp( tok, "int" ) == 0 ) {
				flag = 1;
				size = 2;
				strcpy( val, "0" );
				strcpy( tp, "int" );
			}
			else if(strcmp(tok,"float")==0) {
				flag=1;
				size=4;
				strcpy( val , "0.0" );
				strcpy( tp , "float" );
			}
			else if( strcmp( tok , "char" ) == 0 ) {
				flag=1;
				size=1;
				strcpy( val, "" );
				strcpy( tp , "char" );
			}
			else if( isalpha(tok[0]) && flag == 1 ) {
				strcpy(s[k]. val, val);
				strcpy(s[k].tp,tp);
				strcpy(s[k]. nm,tok);
				s[k].addr= addrs;
				s[k].size=size;
				addrs=s[k].addr+size;
				k++;
			}
			else if( isdigit( tok[0] ) && flag == 1 ) {
				k--;
				strcpy( s[k].val , tok );
				k++;
			}
			else break;
			tok=strtok(NULL," ,+=;");
		}
	}
	return k-1;
}

int main(int argc, char* argv[])
{
	int len=0, n, i;
	char sym[200], decl[300];

	len=generate(argv[1]);
	printf("NAME\t\tSIZE\t\tTYPE\t\tADDRESS\t\tVALUE\n");
	for(i = 0; i <= len; i++) {
		if(strlen(s[i].nm) > 7)
			printf("%s\t%d\t\t%s\t\t%d\t\t%s\n",s[i].nm, s[i].size, s[i].tp, s[i].addr, s[i].val);
		else
			printf("%s\t\t%d\t\t%s\t\t%d\t\t%s\n",s[i].nm, s[i].size, s[i].tp, s[i].addr, s[i].val);
	}
	printf("\n");
	return 0;
}

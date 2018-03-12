#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#define INF 10
int size = 0;
struct SymbTab* Insert(int, char[100], unsigned);
void Display();
struct SymbTab* Delete(char, unsigned);
int Search(char lab[]);
struct SymbTab* Modify(char, int, unsigned);
unsigned hash(char s[100]);

struct SymbTab {
	int addr;
	char name[100];
	struct SymbTab *next;
};

struct SymbTab * table[5005];

unsigned hash(char s[100]) {
	unsigned hval = 0;
	int i;
	for (i = 0; s[i] != '\0'; i++) {
		hval += s[i];
	}
	printf("%u\n", hval);
	hval %= INF;
	return hval;
}
int Search(char s[100]) {
	int i, j;
	int hval = hash(s);
	struct SymbTab *p;
	p = table[hval];
	while (p != NULL) {
		char name[100];
		for (i = 0; (*p).name[i] != '\0'; i++) {
			name[i] = (*p).name[i];
		}
		name[i] = '\0';
		if (strcmp(name, s) == 0)
			return 1;
		p = p->next;
	}
	return 0;
}
struct SymbTab* Insert(int addr, char s[100], unsigned h) {
	int i;
	struct SymbTab *p, *temp, *head;
	temp = (struct SymbTab*)malloc(sizeof(struct SymbTab));
	for (i = 0; s[i] != '\0'; i++) {
		(*temp).name[i] = s[i];
	}
	(*temp).name[i] = '\0';
	(*temp).addr = addr;
	temp->next = NULL;
	p = table[h];
	head = p;
	int present = Search(s);
	if (present) {
		printf("already present\n");
		return head;
	}
	printf("***----%s\t%d\n", s, h);
	
	printf("yes\n");
	if (p == NULL) {
		p = temp;
		return p;
	}
	else {
		while (p->next != NULL) {
			p = p->next;
		}
		p->next = temp;
	}
	return head;
}
struct SymbTab* Modify(char name[100], int addr, unsigned h) {
	struct SymbTab *p, *head;
	p = table[h];
	int present = Search(name);
	if (present == 0) {
		printf("Not Present\n");
		return p;
	}
	head = p;
	while (p != NULL) {
		if (strcmp(name, (*p).name) == 0) {
			(*p).addr = addr;
			return head;
		}
		p = p->next;
	}
	return head;
}
struct SymbTab* Delete(char name[100], unsigned h) {
	struct SymbTab *p, *head;
	p = table[h];
	int present = Search(name);
	if (present == 0) {
		printf("Not Present\n");
		return p;
	}
	head = p;
	if (strcmp(name, (*p).name) == 0) {
		p = p->next;
		return p;
	}
	while (p->next != NULL) {
		printf("+++  %s\n", ((*(p->next)).name));
		if (strcmp(name, ((*(p->next)).name)) == 0) {
			p->next = p->next->next;
			return head;
		}
		p = p->next;
	}
	printf("Label deleted\n");
	return head;
}
void Display() {
	int i;
	struct SymbTab *p;
	printf("hash\tlabel\taddress\n");
	for (i = 0; i < 100; i++) {
		p = table[i];
		while (p != NULL) {
			printf("%d\t%s\t%d\n", i, (*p).name, (*p).addr);
			p = p->next;
		}
	}
}
int main() {
	int op;
	int i, present;
	for (i = 0; i < INF; i++) {
		table[i] = NULL;
	}
	do
	{
		char name[100];
		int addr;
		unsigned h;
		printf("\n\tSYMBOL TABLE IMPLEMENTATION\n");
		printf("\n\t1.INSERT\n\t2.DISPLAY\n\t3.DELETE\n\t4.SEARCH\n\t5.MODIFY\n\t6.END\n");
		printf("\n\tEnter your option : ");
		scanf("%d", &op);
		switch (op)
		{
		case 1:
			printf("Enter label and address\n");
			scanf("%s%d", name, &addr);
			h = hash(name);
			table[h] = Insert(addr, name, h);
			if (table[h] == NULL)
				printf("no\n");
			break;
		case 2:
			Display();
			break;
		case 3:
			printf("Enter label to be deleted\n");
			scanf("%s", name);
			h = hash(name);
			table[h] = Delete(name, h);
			break;
		case 4:
			printf("Enter the label to be searched : \n");
			scanf("%s", name);
			present = Search(name);
			printf("Search Result:\n");
			if (present == 1)
				printf("The label is present in the symbol table\n");
			else
				printf("The label is not present in the symbol table\n");
			break;
		case 5:
			printf("enter label to be modified and modified address\n");
			scanf("%s%d", name, &addr);
			h = hash(name);
			table[h] = Modify(name, addr, h);
			break;
		case 6:
			exit(0);
		}
	} while (op<6);
}
#include<bits/stdc++.h>
using namespace std;
#define op_n 8
#define del_n 8
#define keyword_n 8
int isdig( char);
int isalpha(char);
int is_op(char);
int is_del(char);
int is_keyword( char);
int is_ident(char);
void check_string(string );
void lexical(string );

char op[8] = { '+', '-', '*', '/', '=', '<', '>', '%' };
char delmitor[8] = { '}', '{', ';', '(', ')', '[', ']', ',' };
string keyword[] = { "int", "void", "main", "char", "printf", "scanf", "float", "double" };
string tokens[10000], keyword_arr[10000], identifier_arr[10000], operators[10000], delemeters[10000], constant[10000], literal[10000];
int token_n , keys , iden, oper , delem , con , lit;



void lexical(string str) {
	int itr = 0;
	string temp;
	while (itr < str.size()) {
		

		if (is_ident(str[itr])) {
			temp = "";
			while (is_ident(str[itr])) {
				temp += str[itr];
				itr++;
			}
			check_string(temp);
		}


		else if (is_op(str[itr])) {
			temp = "";
			while (is_op(str[itr])) {
				temp += str[itr];
				itr++;
			}
			cout << "(operators , " <<  temp << ")"<<endl<<endl;
			operators[oper++] = temp;
		}

	
		else if (is_del(str[itr])) {
			temp = "";
			while (is_del(str[itr])) {
				cout << "(delimeters , " <<  str[itr] << ")"<<endl<<endl;
				delemeters[delem++] = str[itr];
				temp += str[itr];
				itr++;
			}
		}

	
		else if (str[itr] == '"') {
			temp = "";
			int j = itr + 1;
			while (j < str.size() && str[j] != '"') {
				temp += str[j];
				j++;
			}
			cout << "(literals , " <<  temp << ")"<<endl<<endl;
			literal[lit++] = temp;
			itr = j + 1;
		}
		else
			itr++;
	}
}
int isdig(char c) {
	int charctr = c - '0';
	if (charctr >= 0 && charctr <= 9)
		return 1;
	return 0;
}

int isalpha(char c) {
	if (c >= 'a' && c <= 'z')
		return 1;
	if (c >= 'A' && c <= 'Z')
		return 1;
	return 0;
}
int is_op(char c) {
	int itr;
	for (itr = 0; itr < op_n; itr++) {
		if (c == op[itr])
			return 1;
	}
	return 0;
}

int is_del(char c) {
	int itr;
	for (itr = 0; itr < del_n; itr++) {
		if (c == delmitor[itr])
			return 1;
	}
	return 0;
}

int is_keyword(string str) {
	int itr;
	for (itr = 0; itr < keyword_n; itr++) {
		if (str == keyword[itr])
			return 1;
	}
	return 0;
}

int is_ident(char c) {
	if (isalpha(c) || isdigit(c) || c == '_' || c == '.')
		return 1;
	return 0;
}

void check_string(string str) {
	if (is_keyword(str)) {
		cout << "(KEYWORD , " <<  str << ")"<<endl<<endl;
		keyword_arr[keys++] = str;
		return;
	}
	if (isdig(str[0])) {
		cout << "( LITERAL , " << str << ")"<<endl<<endl;
		literal[lit++] = str;
		return;
	}
	cout << "(IDENTIFIER ,  " <<  str << ")"<<endl << endl;
	identifier_arr[iden++] = str;
}
int main() {
	string str;
	char c;
	cout << "TOKENISATION " << endl<<endl;

	freopen("data.txt", "r", stdin); 
	while (getline(cin, str)) {
		int itr = 0;
		if (str[itr] == '/' && str[itr + 1] == '*') {
			while (str[itr] !='/' && str[itr-1] != '*') {
				continue;
				itr++;
			}
		}
		if (str[itr] != '#' && (str[itr] != '/' && str[itr] != '/')) {
			lexical(str);
			str = "";
		}
	}
	return 0;
}

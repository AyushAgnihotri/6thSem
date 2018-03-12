#include <bits/stdc++.h>
using namespace std;

char op[9] = { '+', '-', '*', '/', '=', '<', '>', '%', '&'};
char del[8] = { '}', '{', ';', '(', ')', '[', ']', ',' };
string keyword[] = { "int", "void", "main", "char", "printf", "scanf", "float", "auto", "return", "break", "continue", "short", "unsigned", "signed", "long", "double", "void", "while", "for", "do", "if", "goto", "static", "sizeof", "malloc", "struct", "switch", "case", "default", "else"};

string tokens[1005];
int token_n = 0;
string keyword_arr[1005];
int keys = 0;
string identifier_arr[1005];
int iden = 0;
string operators[1005];
int oper = 0;
string delimiters[1005];
int delem = 0;
string constant[1005];
int con = 0;
string literal[1005];
int lit = 0;

int isdig(char c) {
	int p = c - '0';
	if (p >= 0 && p <= 9) {
		return 1;
	}
	return 0;
}

int isalpha(char c) {
	if (c >= 'a' && c <= 'z') {
		return 1;
	}
	if (c >= 'A' && c <= 'Z') {
		return 1;
	}
	return 0;
}

int is_op(char c) {
	int i;
	for (i = 0; i < (sizeof(op)/sizeof(op[0])); i++) {
		if (c == op[i]) {
			return 1;
		}
	}
	return 0;
}

int is_del(char c) {
	int i;
	for (i = 0; i < (sizeof(del)/sizeof(del[0])); i++) {
		if (c == del[i]) {
			return 1;
		}
	}
	return 0;
}

int is_keyword(string s) {
	int i;
	for (i = 0; i < (sizeof(keyword)/sizeof(keyword[0])); i++) {
		if (s == keyword[i]) {
			return 1;
		}
	}
	return 0;
}

int is_identifier(char c) {
	if (isalpha(c) || isdigit(c) || c == '_' || c == '.') {
		return 1;
	}
	return 0;
}

void check(string s) {
	if (is_keyword(s)) {
		cout << "keyword = " << s << endl;
		keyword_arr[keys++] = s;
		return;
	}
	if (isdig(s[0])) {
		cout << "literal = " << s << endl;
		literal[lit++] = s;
		return;
	}
	cout << "identifier = " << s << endl;
	identifier_arr[iden++] = s;
}

void lex_analyzer(string s) {
	int i = 0;
	string temp;
	while (i < s.size()) {

		//identifier
		if (is_identifier(s[i])) {
			temp = "";
			while (is_identifier(s[i])) {
				temp += s[i];
				i++;
			}
			check(temp);
		}

		//operators
		else if (is_op(s[i])) {
			temp = "";
			while (is_op(s[i])) {
				temp += s[i];
				i++;
			}
			cout << "operators = " << temp << endl;
			operators[oper++] = temp;
		}

		//delimiters
		else if (is_del(s[i])) {
			while (is_del(s[i])) {
				cout << "delimiters = " << s[i] << endl;
				delimiters[delem++] = s[i];
				i++;
			}
		}

		//literals
		else if (s[i] == '"') {
			temp = "";
			int j = i + 1;
			while (j < s.size() && s[j] != '"') {
				temp += s[j];
				j++;
			}
			cout << "literals = " << temp << endl;
			literal[lit++] = temp;
			i = j + 1;
		}

		else {
			i++;
		}
	}
}

int main() {
	string s;
	char c;
	freopen("input.c", "r", stdin);

	while (getline(cin, s)) {
		if (s[0] == '#') {
			continue;
		}
		lex_analyzer(s);
		s = "";
	}

	return 0;
}
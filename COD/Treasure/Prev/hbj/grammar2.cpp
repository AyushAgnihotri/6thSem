#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <map>
#include <cstring>
#include <cstdio>
#define var_size 7
#define ter_size 6
using namespace std;
string var[] = { "P", "C", "F", "X", "Y", "I", "J" };
string ter[] = { "class", "identifier", "public", "final", "extends", "implements" };
string s[105];
string path[105];
int p_l;
vector<string> prod[105];
int len;

map<string, int> m;
string to_string(string t[105], int l) {
	string p;
	int i;
	for (i = 0; i < l; i++) {
		p += " " + t[i];
	}
	return p;
}
int is_var(string t) {
	int i;
	for (i = 0; i < var_size; i++) {
		if (var[i] == t)
			return 1;
	}
	return 0;
}
int is_ter(string t) {
	int i;
	for (i = 0; i < ter_size; i++) {
		if (ter[i] == t)
			return 1;
	}
	return 0;
}
int is_equal(string t[105], int l) {
	int i, f = 0;
	if (l == len) {
		for (i = 0; i < l; i++) {
			if (s[i] != t[i]) {
				return 0;
			}
		}
		return 1;
	}
	return 0;
}
void store(string rep[], string t[105], int l) {
	int i;
	for (i = 0; i < l; i++) {
		rep[i] = t[i];
	}
}
void restore(string rep[], string t[105], int l) {
	int i;
	for (i = 0; i < l; i++) {
		t[i] = rep[i];
	}
}
int words_in_string(string new_s) {
	int i, c = 0;
	for (i = 0; i < new_s.size(); i++) {
		if (new_s[i] == ' ')
			c++;
	}
	return c + 1;
}
int change_n_shift(string t[105], int l, string new_s, int q) {
	int i, k = 0;
	int r = 0;
	string p[105];
	string temp;
	int words = words_in_string(new_s);
	if (words == 1 && new_s == "epsilon") {
		for (i = q; i < l - 1; i++) {
			t[i] = t[i + 1];
		}
		return l - 1;
	}
	r = 0;
	k = 0;
	for (i = q + 1; i < l; i++) {
		p[k++] = t[i];
		r++;
	}
	k = q;
	for (i = 0; i < new_s.size(); i++) {
		if (new_s[i] == ' ') {
			t[k++] = temp;
			temp = "";
		}
		else {
			temp += new_s[i];
		}
	}
	t[k++] = temp;
	for (i = 0; i < r; i++) {
		t[k++] = p[i];
	}
	return k;
}
void disp(string t[105], int l) {
	int i;
	for (i = 0; i < l; i++) {
		cout << t[i] << " ";
	}
	cout << endl;
}
int count_terminal(string t[105], int l) {
	int i, c = 0;
	for (i = 0; i < l; i++) {
		if (is_ter(t[i]))
			c++;
	}
	return c;
}
void show(int path_len) {
	int i;
	for (i = 0; i <= path_len; i++)
		cout << "=> " << path[i] << endl;
}
void func(string t[105], int l, int path_ll) {
	int i, j, k;
	//disp(t, l);
	//cout << "len = " << l << endl;
	if (is_equal(t, l)) {
		string tem = to_string(t, l);
		path[path_ll] = tem;
		show(path_ll);
		exit(0);
		return;
	}
	int c = count_terminal(t, l);
	if (c > len)
		return;
	string tem = to_string(t, l);
	path[path_ll] = tem;
	for (i = 0; i < l; i++) {
		if (is_var(t[i])) {
			k = m[t[i]];
			//cout << "->" << k << " " << t[i] << endl;
			for (j = 0; j < prod[k].size(); j++) {
				string rep[105];
				int old = l;
				store(rep, t, l);
				l = change_n_shift(t, l, prod[k][j], i);
				func(t, l, path_ll+1);
				restore(rep, t, old);
				l = old;
			}
		}
	}
}
int main() {
	string str, p;
	string q[105];
	q[0] = "P";
	q[1] = "F";
	q[2] = "class";
	q[3] = "identifier";
	q[4] = "X";
	q[5] = "Y";
	int i, j;
	len = 0;
	prod[0].push_back("public");
	prod[0].push_back("epsilon");
	prod[1].push_back("final");
	prod[1].push_back("epsilon");
	prod[2].push_back("extends identifier");
	prod[2].push_back("epsilon");
	prod[3].push_back("implements I");
	prod[3].push_back("epsilon");
	prod[4].push_back("identifier J");
	prod[5].push_back(", I");
	prod[5].push_back("epsilon");

	m["P"] = 0;
	m["F"] = 1;
	m["X"] = 2;
	m["Y"] = 3;
	m["I"] = 4;
	m["J"] = 5;

	getline(cin, str);
	for (i = 0; i < str.size(); i++) {
		if (str[i] == ' ') {
			s[len++] = p;
			p = "";
		}
		else
			p = p + str[i];
	}
	s[len++] = p;
	for (i = 0; i < len; i++) {
		if (!is_ter(s[i])) {
			s[i] = "identifier";
		}
	//	cout << s[i] << " ";
	}
	//cout << endl;
	p_l = 0;
	cout << "C ";
	func(q, 6, 0);
}
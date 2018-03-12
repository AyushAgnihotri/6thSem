#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <map>
#include <cstring>
#include <cstdio>
#include <queue>
#define var_size 3
#define ter_size 11
using namespace std;
map<string, int> vis;
string var[] = { "<opt-default>", "<case-list>", "<one-case>" };
string ter[] = { "switch", "(", "expr", ")", "{", "}", "default:", "statement:", "char-const-value:", "case", "break;" };
string s[105];
string path[105];
int p_l;
vector<string> prod[105];
int len;

map<string, int> m;
string to_string(string t[105], int l) {
	string p;
	int i;
	for (i = 0; i < l-1; i++) {
		p += t[i]+ " ";
	}
	p += t[l - 1];
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
	if (words == 1 && new_s == "empty") {
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
int count_var(string t[105], int l) {
	int i, c = 0;
	for (i = 0; i < l; i++) {
		if (is_var(t[i]))
			c++;
	}
	return c;
}
void show(int path_len) {
	int i;
	for (i = 0; i <= path_len; i++)
		cout << "=> " << path[i] << endl;
}
string test;

int to_string_array(string str, string t[105]) {
	int i;
	int l = 0;
	string temp;
	for (i = 0; i < str.size(); i++) {
		if (str[i] == ' ') {
			t[l++] = temp;
			temp = "";
		}
		else
			temp += str[i];
	}
	t[l++] = temp;
	return l;
}
void show2(vector <string> p) {
	int i;
	for (i = 0; i < p.size(); i++) {
		cout << "=> " << p[i] << endl;
	}
}
void func_bfs(string str) {
	int l;
	int i, j, k;
	queue <string> q;
	queue<vector<string>>v;
	vector<string>p;
	p.push_back(str);

	q.push(str);
	v.push(p);

	while (!q.empty()) {
		str = q.front();
		q.pop();
		p = v.front();
		v.pop();
		string t[105];
		l = to_string_array(str, t);

		
		if (is_equal(t, l)) {
			show2(p);
			exit(0);
			return;
		}

		int c = count_terminal(t, l);
		if (c > len)
			continue;

		if (vis[str])
			continue;
		vis[str] = 1;

		for (i = 0; i < l; i++) {
			if (is_var(t[i])) {
				k = m[t[i]];
				p.push_back("\0");
				for (j = 0; j < prod[k].size(); j++) {
					string rep[105];
					store(rep, t, l);
					int new_l = change_n_shift(rep, l, prod[k][j], i);
					string temp = "";
					temp = to_string(rep, new_l);
					p[p.size() - 1] = temp;
					q.push(temp);
					v.push(p);
				}
			}
		}
	}
}
int main() {

	string str, p;
	string q[105];

	q[0] = "switch";
	q[1] = "(";
	q[2] = "expr";
	q[3] = ")";
	q[4] = "{";
	q[5] = "<case-list>";
	q[6] = "<opt-default>";
	q[7] = "<case-list>";
	q[8] = "}";



	int i, j;
	len = 0;

	prod[0].push_back("empty");
	prod[0].push_back("default: statement;");
	prod[1].push_back("empty");
	prod[1].push_back("<one-case> <case-list>");
	prod[2].push_back("case char-const-value: statement; break;");

	m["<opt-default>"] = 0;
	m["<case-list>"] = 1;
	m["<one-case>"] = 2;

	//	freopen("1.txt","r",stdin)
	p_l = 0;
	s[0] = "switch";
	s[1] = "(";
	s[2] = "expr";
	s[3] = ")";
	s[4] = "{";
	s[5] = "case";
	s[6] = "char-const-value:";
	s[7] = "statement;";
	s[8] = "break;";
	s[9] = "case";
	s[10] = "char-const-value:";
	s[11] = "statement;";
	s[12] = "break;";
	s[13] = "default:";
	s[14] = "statement;";
	s[15] = "}";

	cout << "<switch> ";
	len = 16;
//	func(q, 9, 0);
	func_bfs("switch ( expr ) { <case-list> <opt-default> <case-list> }");
	return 0;
}

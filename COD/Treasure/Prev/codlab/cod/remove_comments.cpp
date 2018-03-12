#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <cstdio>
#include <cstring>
#define op_n 8
#define del_n 8
#define keyword_n 7
using namespace std;

int main() {
	string s;
	int i, f, g;
	char c;
	freopen("hello_world.cpp", "r", stdin);
	freopen("input_comments_removed.cpp", "w", stdout);
	g = 0;
	while (getline(cin, s)) {
		i = 0;
		f = 0;
		while (i < s.size()) {
			if (g == 0 && s[i] == '/' && (i + 1) < s.size() && s[i + 1] == '/') {
				i += 2;
				break;
			}
			if (g == 0 && s[i] == '/' && (i + 1) < s.size() && s[i + 1] == '*') {
				g = 1;
				i++;
			}
			else if (g == 1 && s[i] == '*' && (i + 1) < s.size() && s[i + 1] == '/') {
				g = 0;
				i++;
			}
			else if (g == 1) {
				i++;
				continue;
			}
			else {
				cout << s[i];
				if (s[i] != ' ')
					f = 1;
			}
			i++;
		}
		if (f)
			cout << endl;
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}
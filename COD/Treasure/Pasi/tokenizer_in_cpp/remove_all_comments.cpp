#include <bits/stdc++.h>
using namespace std;

int main() {
	string s;
	int i, f1, f2;
	freopen("inp.txt", "r", stdin);
	freopen("input.c", "w", stdout);
	f1 = 0;
	while (getline(cin, s)) {
		i = 0;
		f2 = 0;
		while (i < s.size()) {
			if (f1 == 0 && s[i] == '/' && (i + 1) < s.size() && s[i + 1] == '/') {
				i += 2;
				break;
			}

			if (f1 == 0 && s[i] == '/' && (i + 1) < s.size() && s[i + 1] == '*') {
				f1 = 1;
				i++;
			} else if (f1 == 1 && s[i] == '*' && (i + 1) < s.size() && s[i + 1] == '/') {
				f1 = 0;
				i++;
			} else if (f1 == 1) {
				i++;
				continue;
			} else {
				cout << s[i];
				if (s[i] != ' ') {
					f2 = 1;
				}
			}
			i++;
		}
		if (f2) {
			cout << endl;
		}
	}

	fclose(stdin);
	fclose(stdout);

	return 0;
}
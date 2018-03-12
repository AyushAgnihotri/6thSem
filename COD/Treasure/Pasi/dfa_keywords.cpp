#include <bits/stdc++.h>
using namespace std;

string keywords[] = {"int", "float", "double", "inline", "for", "if", "alignas", "alignof", "and", "asm", "auto", "bitand", "bitor", "bool", "break", "case", "catch", "char", "class", "compl", "concept", "const", "constexpr", "decltype", "default", "delete", "and_eq"};
int dfa[100005][300];
bool final[100005];

void create_dfa()
{
	int i, j, l, x, y, size;
	size = sizeof(keywords)/sizeof(keywords[0]);

	x = 0;
	for (i = 0; i < size; i++) {
		y = 0;
		l = keywords[i].length();
		for (j = 0; j < l; j++) {
			if (dfa[y][keywords[i][j]] == -1) {
				dfa[y][keywords[i][j]] = x+1;
				x++;
				y = x;
			} else {
				y = dfa[y][keywords[i][j]];
			}

			if (j == l-1) {
				final[y] = true;
			}
		}
	}
}

int main()
{
	int i, state, f, next_state;
	string s;
	memset(dfa, -1, sizeof(dfa));
	memset(final, false, sizeof(final));

	create_dfa();

	while (1) {
		f = 0;
		state = 0;

		cin >> s;

		for (i = 0; i < s.length(); i++) {
			next_state = dfa[state][s[i]];
			if (next_state == -1) {
				f = 1;
				break;
			}
			state = next_state;
		}

		if (!final[state]) {
			f = 1;
		}

		if (f == 1) {
			cout << "Not Keyword\n";
		} else {
			cout << "Keyword\n";
		}
	}

	return 0;
}
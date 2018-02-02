#include <bits/stdc++.h>
using namespace std;

string keywords[] = {"int", "float", "double", "inline", "for", "if"};
int dfa[100005][30];
bool final[100005];

void create_dfa()
{
	int i, j, l, x, y, size;
	size = sizeof(keywords)/sizeof(keywords[0]);

	x = 0;
	for (i = 0; i < size; i++) {
		l = keywords[i].length();
		for (j = 0; j < l; j++) {
			if (j == 0) {
				if (dfa[0][keywords[i][j]-97] == -1) {
					dfa[0][keywords[i][j]-97] = x+1;
					x++;
					y = x;
				} else {
					y = dfa[0][keywords[i][j]-97];
				}
			} else {
				if (dfa[y][keywords[i][j]-97] == -1) {
					dfa[y][keywords[i][j]-97] = x+1;
					x++;
					y = x;
				} else {
					y = dfa[y][keywords[i][j]-97];
				}
			}

			if (j == l-1) {
				final[x] = true;
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
			next_state = dfa[state][s[i]-97];
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
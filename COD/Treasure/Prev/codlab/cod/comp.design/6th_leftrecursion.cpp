#include<cstdio>
#include<iostream>
#include<vector>
#include<cstring>
#include<string>
#include<cstdlib>
using namespace std;

int main()
{
	//freopen("input2.txt", "r", stdin);
	int pr, i, j, k, l, n, m;
	scanf("%d", &pr);
	string a;
	char tt = 'A';
	vector<pair<string, vector<string> > > v;
	for (i = 0; i < pr; i++) {
		cin >> a;
		string b, c, d, temp;
		pair<string, vector<string> > vv;
		b = "";
		vector<string> te;
		for (j = 0; j < a.length(); j++) {
			if (a[j] == '-') {
				temp = b;
				te.push_back(temp);
				b = "";
				j++;
			}
			else if (a[j] == '|') {
				te.push_back(b);
				b = "";
			}
			else {
				b = b + a[j];
			}
		}
		te.push_back(b);
		for (j = 1; j < te.size(); j++) {
			if (te[0][0] == te[1][0]) {
				cout << te[0][0] << "->" << te[2][0] << tt << endl;
				cout << tt << "->";
				for (int ii = 1; ii < te[1].length(); ii++) {
					cout << te[1][ii];
				}
				cout << endl;
				tt++;
				break;
			}
			else {
				cout << a << endl;
				break;
			}
		}
	}
}

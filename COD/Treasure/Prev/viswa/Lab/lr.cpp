#include<bits/stdc++.h>
using namespace std;

#define ll long long int
#define FL(i,a,b) for(ll i=a;i<b;i++)
#define FOR(i,n) for(ll i=0;i<n;i++)
#define SORTF(x) sort(x.begin(),x.end(),func);
#define SORT(x) sort(x.begin(),x.end())
#define pb(x) push_back(x)
#define SET(v, val) memset(v, val, sizeof(v)) ;
#define RSORT(v) { SORT(v) ; REVERSE(v) ; }
#define ALL(v) v.begin(),v.end()
#define REVERSE(v) { reverse(ALL(v)) ; }
#define UNIQUE(v) unique((v).begin(), (v).end())
#define RUNIQUE(v) { SORT(v) ; (v).resize(UNIQUE(v) - (v).begin()) ; }
#define fill(x,n) memset(x,n,sizeof(x))
#define S(n) scanf("%lld",&n)

int main()
{
	freopen("input2.txt", "r", stdin);
	int pr, i, j, k, l, n, m;
//	cout << "Given Grammar\n";
	scanf("%d", &pr);
	string a;
	char tt = 'A';
	vector<pair<string, vector<string> > > v;
	cout << "Grammar After Left Recursion\n";
	for (i = 0; i < pr; i++) {
		cin >> a;
	//	cout << "\t\ta\n";
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
			} else if (a[j] == '|') {
				te.push_back(b);
				b = "";
			} else {
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
				cout << tt ;
				if(j % 2 != 0) {
					cout << "|{";
				}
				cout << endl;
				tt++;
				break;
			} else {
				cout << a << endl; 
				break;
			}
		}
	} 
	return 0;
}

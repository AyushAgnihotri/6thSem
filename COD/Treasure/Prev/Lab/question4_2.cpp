#include <bits/stdc++.h>
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

ll modulo(ll a,ll b) {
	ll c = 1e9 + 7;
    long long x=1,y=a;
    while(b > 0){
        if(b%2 == 1){
            x=(x*y)%c;
        }
        y = (y*y)%c;
        b /= 2;
    }
    return x%c;
}

map<string, ll> map1;
vector<string> ans;

ll solve(string s) {
//	cout << s << "\n";
	if(s.size() == 1|| s[0] == 'S') {
		return 1;
	}
	ll j;
	for(ll i = 0;i <s.size();i++) {
		if(i + 2 < s.size()) {
			string s1;
			s1 = s[i] ;
			s1 = s1 + s[i + 1];
			s1 =s1 +  s[i + 2];
			
			if(map1[s1] == 1) {
				
				string temp;
				for(j = 0;j < i;j++) {
					temp =temp + s[j];
				}
				temp= temp + 'S';
				for(j = i + 3;j < s.size();j++) {
					temp =temp + s[j];
				}
			//	cout << temp << "\n";
				if(solve(temp) == 1) {
					ans.pb(temp);
				//	cout << temp << "\n";
					return 1;
				}
			}
		}
		if(i + 1 < s.size()) {
			string s1;
			s1 = s[i];
			s1 = s1 +s[i + 1] ;
			if(map1[s1] ==1) {
				
				string temp;
				for(j = 0;j < i;j++) {
					temp =temp + s[j];
				}
				temp = temp + 'S';
			//	cout << temp << "\n";
				for(j = i + 2;j < s.size();j++) {
					temp =temp +  s[j];
				}
				if(solve(temp) == 1) {
				//	cout << temp << "\n";
					ans.pb(temp);
					return 1;
				}
			}
		}
	}
	return 0;
}

int main() {
	map1["SS"] = 1;
	map1["(S)"] = 1;
	map1["()"] = 1;
	string s;
	cin >> s;
	solve(s);
	for(ll i = ans.size() - 1;i >= 0;i--) {
		cout << ans[i] << "\n";
	}
}




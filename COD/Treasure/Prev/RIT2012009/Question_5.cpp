

#include <bits/stdc++.h>
using namespace std;

#define ll long long int
#define FL(i,a,b) for(i=a;i<b;i++)
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
#define MAX 100
#define for(i,a,b) for(i=a;i<b; i++)
 
string grammar[MAX][MAX]; 
string dpr[MAX];
int p,np;       

/*Functions are Declared Here*/
inline string string_concatenation( string a, string b);   
inline void break_grammar(string a);    
inline int left_chomsky(string a);  
inline int right_chomsky(string a);  
inline string search_production(string p); 
inline string generat_combination(string a, string b);  
 
/* input pattern 
	S
	7
	S->EF|AF|EB|AB
	G->AY|BY|a|b
	Y->AY|BY|a|b
	E->AG
	F->BG
	A->a
	B->b
	abaaba
*/
 
int main()
{
    int i,pt,j,l,k;
    string a,str,r,pr,start;
    cout<<"\nEnter the start Variable(for e.g S) ";
    cin >> start;
    cout<<"\nTotal Number of productions ";
    cin >> np;
    cout << "Please Enter Grammar in CNF Form(S->AB or S->a)\n";
    for(i,0,np)
    {
        cin >> a;
        pt=a.find("->");
        grammar[i][0] = a.substr(0,pt);
        if (left_chomsky(grammar[i][0]) == 0)
        {
            cout<<"\nGiven grammar is not in Chomsky Normal Form\n";
            abort();
        }
        a = a.substr(pt+2, a.length());
        break_grammar(a);
        for(j,0,p)
        {
            grammar[i][j+1]=dpr[j];
            if (right_chomsky(dpr[j]) == 0)
            {
                cout<<"\nGiven grammar is not in Chomsky Normal Form\n";
                abort();
            }
        }
    }
    string matrix[MAX][MAX],st;
    cout<<"\nInput the test string(for e.g abaaba)-> ";
    cin >> str;
    for(i,0,str.length())       //Assigns values to principal diagonal of matrix
    {
        r="";
        st = "";
        st+=str[i];
        for(j,0,np)
        {
            k=1;
            while(grammar[j][k] != "")
            {
                if(grammar[j][k] == st)
                {
                    r=string_concatenation(r,grammar[j][0]);
                }
                k++;
            }
        }
        matrix[i][i]=r;
    }
    int ii,kk;
    for(k,1,str.length())       //Assigns values to upper half of the matrix
    {
        for(j,k,str.length())
        {
            r="";
            for(l,j-k,j)
            {
                pr = generat_combination(matrix[j-k][l],matrix[l+1][j]);
                r = string_concatenation(r,pr);
            }
            matrix[j-k][j] = r;
        }
    }
 
    for(i,0,str.length())   //Prints the matrix
    {
        k=0;
        l=str.length()-i-1;
        for(j,l,str.length())
        {
        	if(matrix[k][j] == "") {
        		cout <<setw(6)<< "- ";
        		k++;
        	}
        	else
            	cout<<setw(5)<<matrix[k++][j]<<" ";
        }
        cout<<endl;
    }
             
    int f=0;
    for(i,0,start.length())
        if(matrix[0][str.length()-1].find(start[i]) <= matrix[0][str.length()-1].length())   //Checks if last element of first row contains a Start variable
        {
            cout<<"Given grammar generates the given test string\n";
            return 0;
        }
    cout<<"Given grammar do not generate the given test string\n";
    return 0;
}

inline string string_concatenation( string a, string b)   //string_concatenationenates unique non-terminals
{
    int i;
    string r=a;
    for(i,0,b.length())
        if(r.find(b[i]) > r.length())
            r+=b[i];
    return (r);
}
 
inline void break_grammar(string a)    //seperates right hand side of entered grammarmar
{
    int i;
    p=0;
    while(a.length())
    {
        i=a.find("|");
        if(i>a.length())
        {
            dpr[p++] = a;
            a="";
        }
        else
        {
            dpr[p++] = a.substr(0,i);
            a=a.substr(i+1,a.length());
        }
    }
}
 
inline int left_chomsky(string a)   //checks if LHS of entered grammarmar is in CNF
{
    if(a.length()==1 && a[0]>='A' && a[0]<='Z')
        return 1;
    return 0;
}
 
inline int right_chomsky(string a)   //checks if RHS of grammarmar is in CNF
{
    if (a.length() == 1 && a[0]>='a' && a[0] <='z')
        return 1;
    if (a.length()==2 && a[0]>='A' && a[0]<='Z' && a[1]>='A' && a[1]<='Z' )
        return 1;
    if(a.length() == 1 &&( a[0] == '(' || a[0] == ')')) {
    	return 1;
    }
    return 0;
}
 
inline string search_production(string p) //returns a string_concatenationenated string of variables which can produce string p
{
    int j,k;
    string r="";
    for(j,0,np)
    {
        k=1;
        while(grammar[j][k] != "")
        {
            if(grammar[j][k] == p)
            {
                r=string_concatenation(r,grammar[j][0]);
            }
            k++;
        }
    }   
    return r;
}
 
inline string generat_combination(string a, string b)  //creates every combination of variables from a and b . For eg: BA * AB = {BA, BB, AA, BB}
{
    int i,j;
    string pri=a,re="";
    for(i,0,a.length())
        for(j,0,b.length())
        {
            pri="";
            pri=pri+a[i]+b[j];
            re=re+search_production(pri);     //searches if the generated productions can be created or not
        }       
    
    return re;
}
 

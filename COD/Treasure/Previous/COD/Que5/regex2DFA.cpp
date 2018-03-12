#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define pi acos(-1.0)
#define ff first
#define LL long long
#define ss second
#define rep(i,n) for(i = 0; i < n; i++)
#define REP(i,n) for(i=n;i>=0;i--)
#define FOR(i,a,b) for(int i = a; i <= b; i++)
#define ROF(i,a,b) for(int i = a; i >= b; i--)
#define re return
#define QI queue<int>
#define SI stack<int>
#define pii pair <int,int>
#define MAX
#define MOD
#define INF 1<<30
#define SZ(x) ((int) (x).size())
#define ALL(x) (x).begin(), (x).end()
#define sqr(x) ((x) * (x))
#define memo(a,b) memset((a),(b),sizeof(a))
#define G() getchar()
#define MAX3(a,b,c) max(a,max(b,c))

double const EPS=3e-8;

using namespace std;


int numRegEx;
int leaf; // count number of Alphabet + '#' ;
string inpstring;
set<int>followPos[505];
map < char , int > Highrank;
map < int , char > who ;
map < set<int> , bool > visit;
int deg[550];
int symbolTable[130][200];
struct Node
{
	Node *LeftChild , *RightChild ;
	char data ;
	set <int> firstPos , lastPos ;
	bool nullable ;
	Node()
	{   
		LeftChild = NULL ;
		RightChild = NULL;
		data = '\0';
		firstPos.clear();
		lastPos.clear();
	}
};
Node *root , *head ;
bool isAlphabet(char x)
{
	if ( (x >='A' && x<='Z') || (x >='a' && x<='z')) return 1;
	else return 0;
}
bool isOperator(char x){
	return ( x == '*' || x == '+' || x == '.');
}
// Follow Position Calculation
set<int> setUnion(set<int >a,set<int >b){
	set<int>c;
	c.insert( a.begin() , a.end() );
	c.insert( b.begin() , b.end() );
	return c;
}
// Clean all previous Data
void CLEAN()
{
	int i , j ;
	rep(i,450)
	{
		followPos[i].clear();
		deg[i] = 0 ;
	}
	leaf = 0 ;
	delete(root);
	visit.clear();
	who.clear();
}

string Inputstring(string str)
{

	string st = "" ;
	st += str[0];
	for ( int i = 1 ; i < str.size() ; i++)
	{
		if( ( isalpha( str[i] ) || str[i]=='(')&& isalpha(str[i-1]))  {
			st += '.' ,  st += str[i];
		}
		else if( str[i-1]=='*' && (str[i]=='(' || isAlphabet(str[i])))
		{
			st += '.';
			st += str[i] ;

		}

		else st += str[i];
	}
	cout<<"str " << st << endl;
	return st;
}
string infixtopostfix(string str)
{
	stack<char>st;
	int len = str.length() , i;
	string postfix = "";
	Highrank['|'] = 0 ;
	Highrank['.'] = 1 ;
	Highrank['*'] = 2 ;

	Highrank['('] = -1; // lowest
	rep(i,len){
		// cout<<str[i];
		if( isAlphabet(str[i]) || str[i]=='*') postfix += str[i];
		else if(str[i] == '(') st.push(str[i]);
		else if(str[i]==')'){
			while(!st.empty() && st.top()!='('){
				char ch = st.top();
				st.pop();
				postfix += ch;
				cout<<ch<<endl;
			}
			if(!st.empty())
				st.pop();
		}
		else if( st.empty() || Highrank[str[i]] > Highrank[st.top()]) st.push(str[i]);
		else if(!st.empty() && Highrank[st.top()] >= Highrank[str[i]]){
			while(!st.empty() && (Highrank[st.top()] >= Highrank[str[i]]) )
			{
				postfix += st.top();
				st.pop();
			}
			st.push(str[i]);

		}
		else
		{
			printf("There is an error in input string\n");
		}

	}
	while(!st.empty()){
		char ch = st.top();
		if(ch!='(')
			postfix += ch;
		st.pop();
	}
	postfix += "#.";
	cout<<"After Converting into Postfix ::: " << postfix << endl;
	return postfix;
}
void Syntex_Tree(string PostFix)
{
	int i , sz = PostFix.size();
	set <int> :: iterator it;
	stack <Node*> stk;
	rep(i,sz)
	{
		head = new Node();
		head->data = PostFix[i];
		if( isAlphabet(PostFix[i]) || PostFix[i] == '#')
		{
			head->LeftChild = NULL;
			head->RightChild = NULL;
			stk.push(head);
		}
		else
		{
			// for . , | , +
			if(stk.size()>=2) {
				head->RightChild = stk.top();
				stk.pop();
				head->LeftChild = stk.top();
				stk.pop();
			}
			else if(stk.size()==1)
			{
				head->LeftChild = stk.top();
				head->RightChild = NULL;
				stk.pop();
			}
			stk.push(head);

		}

	}
	root = stk.top();
}
int cnt = 0 ;
void firstlastPosCal(Node *N)
{   if(N == NULL ) return ;
	//  cnt++;
	//  cout<<cnt<<" "<<N->data<<endl;
	set <int> :: iterator it1 , it2 ;
	if(N->LeftChild != NULL) firstlastPosCal(N->LeftChild);
	// printf("come\n");
	if(N->RightChild != NULL ) firstlastPosCal(N->RightChild);
	// printf("go\n");
	if((N->data == '+' || N->data == '|') && N->LeftChild != NULL )
	{  // printf(" now + , | \n");
		N->nullable = N->LeftChild->nullable || N->RightChild->nullable;
		N->firstPos = setUnion(N->LeftChild->firstPos,N->RightChild->firstPos);
		N->lastPos = setUnion(N->RightChild->lastPos,N->RightChild->lastPos);
	}
	else if ( ( N->data == '.' ) && ( N->LeftChild != NULL && N->RightChild != NULL ))
	{   // printf(" now '.' \n");
		N->nullable = N->LeftChild->nullable && N->RightChild->nullable;
		if(N->LeftChild->nullable)
			N->firstPos = setUnion(N->LeftChild->firstPos,N->RightChild->firstPos);
		else
			N->firstPos = N->LeftChild->firstPos ;
		if(N->RightChild->nullable)
			N->lastPos = setUnion(N->LeftChild->lastPos,N->RightChild->lastPos);
		else
			N->lastPos = N->RightChild->lastPos;
		// Follow Position calculation
		for ( it1 = N->LeftChild->lastPos.begin();it1!=N->LeftChild->lastPos.end();it1++)
		{
			for ( it2 = N->RightChild->firstPos.begin(); it2 != N->RightChild->firstPos.end();it2++)
			{
				followPos[*it1].insert(*it2);
			}
		}
	}
	else if( ( N->data == '*' ) && (N->LeftChild != NULL  ))
	{
		// printf(" now '*' \n");
		N->nullable = true;
		N->firstPos = N->LeftChild->firstPos;
		N->lastPos = N->LeftChild->lastPos;
		for ( it1 = N->LeftChild->lastPos.begin();it1!=N->LeftChild->lastPos.end();it1++)
		{
			for ( it2 = N->LeftChild->firstPos.begin(); it2 != N->LeftChild->firstPos.end();it2++)
			{
				followPos[*it1].insert(*it2);
			}
		}

	}
	else
	{
		N->nullable = false;
		leaf++;
		N->firstPos.insert(leaf);
		N->lastPos.insert(leaf);
		who[leaf]  = N->data;
		symbolTable[N->data][deg[N->data]++] = leaf ;
	
	}


}
void printSymbolTable()
{
	int i , j;
	printf("\n\n\t Symbol table\n\n");
	printf("     symbol      position\n_______________________________\n");
	for ( i = 'a' ; i <='z' ; i++ )
	{
		if(deg[i])
		{   printf("\t%c\t",(char)i);
			for ( j = 0 ; j < deg[i] ; j++ )
			{
				printf(" %d",symbolTable[i][j]);
			}
			printf("\n_______________________________\n");
		}
	}
}
void printFollowTable()
{
	printf("\n\n\t FollowPos Table\n\n");
	printf("\tNode      Followpos\n");
	set <int> :: iterator it;
	for(it = root->firstPos.begin() ; it != root->firstPos.end();it++)
	{
		followPos[1].insert(*it);
	}
	int i ;
	for ( i = 1 ; i <= 200 ; i++ )
	{
		if (followPos[i].size())
		{
			printf("\t%d\t ",i);
			for ( it = followPos[i].begin() ; it != followPos[i].end() ; it++ )
			{
				cout <<" "<<(*it);
			}
			printf("\n");
		}
	}
}
void DFD()
{
	printf("\n\n\t\t DFA Construction");

	int i , j ;
	printf("\n______________________________________________________________\n");
	printf("\t  Node ");
	set <int> u , v ,add , x;
	vector <int> sym;
	for ( i = 'a' ; i <='z' ; i++ ) if(deg[i]) { printf("\t\t  %c ",i); sym.pb(i);}
	printf("\n______________________________________________________________\n");
	queue < set<int> > q;

	set <int> :: iterator it;
	q.push(root->firstPos);
	visit[root->firstPos] = true ;
	bool space = true;
	while(!q.empty())
	{
		u = q.front();
		q.pop();
		map < int , bool > freq;
		printf("\t");
		for ( it = u.begin() ; it!=u.end() ; it++ )
		{
			cout<<" "<<(*it);
			freq[(*it)] = true;
		}
		if(space)
			printf("\t");
		space = false;
		rep(i,sym.size())
		{
			vector <int > a;
			for ( j = 0 ; j < deg[sym[i]] ; j++ )
			{
				if(freq[symbolTable[sym[i]][j]])
				{
					a.pb(symbolTable[sym[i]][j]);
				}
			}
			x.clear();
			for ( j = 0 ; j < a.size() ; j++ )
			{
				x = setUnion(x,followPos[a[j]]);
			}
			if(x.size())
			{   printf("\t");
				for ( it = x.begin() ; it != x.end() ; it++ )
				{
					cout <<(*it)<<" ";
				}
				if(visit[x]==false)
				{
					q.push(x);
					visit[x] = true;
				}
			}
			else
			{
				printf("\tno");
			}
		}
		printf("\n");


	}
}
int main() {
	int i  , cs ;
	printf("Number of Regular Expression :: ");
	cin >> numRegEx;
	rep(cs,numRegEx) {
		CLEAN();
		cout << " Enter string : " ;
		cin >> inpstring;
		cout << "Given string : " << inpstring << endl;
		string infix = Inputstring(inpstring);
		cout << infix << endl;
		string postfix = infixtopostfix(infix);
		// creating syntext tree
		Syntex_Tree(postfix);
		// follow position calculation
		firstlastPosCal(root);
		printFollowTable();
		//printSymbolTable();
		DFD();
	}
	return 0;
}


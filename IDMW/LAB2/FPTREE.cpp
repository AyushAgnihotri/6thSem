#include <bits/stdc++.h>
using namespace std;
#define inf 100000007

void printset( set<int>  st)
{
	set<int> ::iterator  x;
	printf("{");
	int cnt=1;
	for (x=st.begin();x!=st.end();x++)
	{
		printf("%d",*x);
		if(!(cnt==(st.size())) ) {
			printf(",");
			cnt++;
		}
	}
	printf("}");
}

struct node
{
	map < int,node* > nxt;
	node* prev;
	int val,cntr;
	node()
	{
		prev = NULL;
		val = -inf;
		cntr = 1;
	}
	node(int v,node *par)
	{
		prev = par;
		val = v;
		cntr = 1;
	}
	node(int v,node *par,int inc)
	{
		prev = par;
		val = v;
		cntr = inc;
	}
};


class tree
{
	public:
		node head;
		map<int,vector<node*> >  info;
		node* curb;
		tree()
		{
			head = node();
			curb = &head;
		}
		void add(int x)
		{
			if ((curb->nxt).find(x)==(curb->nxt).end())
			{
				node *temp = new node(x,curb);
				curb->nxt[x] = temp;
				curb = temp;
				info[x].push_back(temp);
			}
			else
			{
				node *temp = (curb->nxt)[x];
				temp->cntr = temp->cntr + 1;
				curb = temp;
			}
		}
		void add_c(int x,int inc)
		{
			if ((curb->nxt).find(x)==(curb->nxt).end())
			{
				node *temp = new node(x,curb,inc);
				curb->nxt[x] = temp;
				curb = temp;
				info[x].push_back(temp);
			}
			else
			{
				node *temp = (curb->nxt)[x];
				temp->cntr = temp->cntr + inc;
				curb = temp;
			}
		}
		void reset()
		{
			curb = &head;
		}
};

void printfma( map<int, map< set<int> ,int> >  x)
{
	map<int, map< set<int> ,int> > ::iterator  it;
	for (it=x.begin();it!=x.end();it++)
	{
		 map< set<int> ,int>  y = x[it->first];
		map< set<int> ,int> ::iterator  it1;
		for (it1=y.begin();it1!=y.end();it1++)
		{
			printset(it1->first);
			cout <<" --> ";
			cout <<(it1->second)<<"\n";
		}
	}
}
map<int, map< set<int> ,int> >  L;
map<int,int>  guide;

bool cmp(const int &x,const int &y)
{
	return guide[x]>guide[y];
}

void tdataprint(map<int,vector<node*> >  x)
{
	map<int,vector<node*> > ::iterator  it;
	for (it=x.begin();it!=x.end();it++)
	{
		cout <<it->first<<"		---		";
		for (int j=0;j<x[it->first].size();j++)
		{
			cout <<x[it->first][j]->cntr<<" "; 
		}
		cout <<"\n";
	}
}
int numsup = -1;


void fpgrowth(tree st, set<int>  init)
{
	map<int,vector<node*> > ::iterator  it;
	map<int,vector<node*> >  inx = st.info;
	for (it=inx.begin();it!=inx.end();it++)
	{
		 set<int>  init1 = init;
		init1.insert(it->first);
		int cur = it->first;
		vector<node*>  X = (st.info)[cur];
		int sum = 0;
		for (int j=0;j<X.size();j++)
		{
			sum += X[j]->cntr;
		}
		(L[init1.size()])[init1] = sum;
		 vector< vector<int> >  T1;
		vector<int> counts;
		tree st1 = tree();
		 map<int,int>  guide1;
		for (int j=0;j<X.size();j++)
		{
			T1.push_back(vector<int>());
			stack<int> st;
			node* temp = X[j]->prev;
			while((temp->val)!= -inf)
			{
				st.push(temp->val);
				temp = temp->prev;
			}
			while(!st.empty())
			{
				T1[T1.size()-1].push_back(st.top());
				int num = st.top();
				if (guide1.find(num)==guide1.end())
				{
					guide1[num] = X[j]->cntr;
				}
				else
				{
					guide1[num] = guide1[num] + X[j]->cntr;
				}
				st.pop();
			}
			counts.push_back(X[j]->cntr);
		}
		for (int j=0;j<T1.size();j++)
		{
			st1.reset();
			for (int k=0;k<T1[j].size();k++)
			{
				if(guide1[T1[j][k]]>=numsup)
				{
					st1.add_c(T1[j][k],counts[j]);
				}
			}
		}
		fpgrowth(st1,init1);
	}
}
int main(int argc, char * argv[])
{
	double minsup ,minconf;
	cout<<"Enter minimum support and confidence in decimal vals in percentage:"<<endl;
	cin >> minsup >> minconf;
	minsup	= minsup/100;
	minconf = minconf/100;
	 vector< vector<int> >  T;
	ifstream fp;
	fp.open(argv[1],ifstream::in);
	string line;
	int mx=0,mmx=0;
	while(getline(fp,line))
	{
		mx++;
		T.push_back(vector<int>());
		stringstream sin;
		sin << line;
		int num;
		while(sin >>num)
		{
			T[T.size()-1].push_back(num);
			if (guide.find(num)==guide.end())
			{
				guide[num] = 1;
			}
			else
			{
				guide[num] = guide[num] + 1;
			}
			mmx=max(mmx,num);
		}
	}
	/*for(int i=1;i<=mmx;i++) {
		cout<<i<<" "<<guide[i]<<endl;
	}*/
	
	numsup = (round)((double)T.size()*minsup);
	cout<<"Minimum Support is :"<<numsup<<endl;

	for (int j=0;j<T.size();j++)
	{
		sort(T[j].begin(),T[j].end(),cmp);
	}
	


	tree st = tree();
	for (int j=0;j<T.size();j++)
	{
		st.reset();
		for (int k=0;k<T[j].size();k++)
		{
			if(guide[T[j][k]]>=numsup)
			{
				st.add(T[j][k]);
			}
		}
	}
	 set<int>  init =  set<int> ();
	fpgrowth(st,init);
	printfma(L);
	printf("\t\tGenerated Rules\n");
	map<int, map< set<int> ,int> > ::iterator  itl;
	for (itl=L.begin();itl!=L.end();itl++)
	{
		int j = itl->first;
		map< set<int> ,int> ::iterator  it;
		for (it=L[j].begin();it!=L[j].end();it++)
		{
			int n = (it->first).size();
			int numconf = (round)((double)(L[n][it->first])/minconf);
			unsigned int N = (1<<n);
			for (int k=1;k<n;k++)
			{
				unsigned int v = 1;
				for (int l=0;l<k-1;l++)
				{
					v<<=1;
					v|=1;
				}
				while(v<N)
				{
					 set<int>  final;
					set<int> ::iterator  st = (it->first).begin();
					unsigned int vt = v;
					while(vt!=0)
					{
						if (vt&1)
						{
							final.insert(*st);
						}
						vt>>=1;
						++st;
					}
					unsigned int w;
					unsigned int t = v | (v - 1);
					w = (t + 1) | (((~t & -~t) - 1) >> (__builtin_ctz(v) + 1));
					v = w;
					if (L[k][final]<=numconf)
					{
						 set<int>  i1;
						set_difference((it->first).begin(),(it->first).end(),final.begin(),final.end(),inserter(i1,i1.end()));
						printset(final);cout <<"-->";printset(i1);cout<<"  C:"<<(double)(L[n][it->first])/L[k][final]<<"\n";
					}
				}
			}
		}
	}
	return 0;
}

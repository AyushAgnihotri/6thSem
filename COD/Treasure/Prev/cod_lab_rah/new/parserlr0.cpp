#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n;
	int graph[100][100];
	memset(graph,0,sizeof(graph));
	string g[100][100];
	//memset(graph,0,sizeof(graph));
	vector<string> v;
	stack<char> order;
	set<char> ter,nonter;
	set<char>::iterator it;
	map<char,vector<string> > closure;
	map<char,vector<string> > ::iterator p;
	set<vector<pair<string,int> > > state;
	map<int,vector<pair<string,int> > > index;
	map<vector<pair<string,int> > ,int> get_i;
	map<int,vector<pair<string,int> > >::iterator q;
	nonter.insert('Z');
	vector<string> y,m,r;
	string s,t;
	cout<<"enter the number of productions"<<endl;
	cin>>n;
	order.push('Z');
	ter.insert('$');
	map<char,int> mp;
	map<char,int>::iterator ij;
	cout<<"enter the productions"<<endl;
	for(int i=0;i<n;i++)
	{
		cin>>s;
		if(nonter.find(s[0])==nonter.end())
		{
			order.push(s[0]);
		}
		y=closure[s[0]];
		y.push_back(s);
		closure[s[0]]=y;
		nonter.insert(s[0]);
		for(int j=3;j<s.size();j++)
		{
			if(s[j]>=65&&s[j]<=90)
			{
				if(nonter.find(s[j])==nonter.end())
				order.push(s[j]);
				nonter.insert(s[j]);
			}
			else
			{
				ter.insert(s[j]);
			}
		}
		//add augmented production before adding the first production
		if(i==0)
		{
			t="Z->";
			t+=s[0];
			t+="$";
			//take closure of Z which is intially empty
			y=closure['Z'];
			//add the production
			y.push_back(t);
			closure['Z']=y;
		//	nonter.insert(s[0]);
			v.push_back(t);
		}
		v.push_back(s);
	}
	cout<<endl;
	int c=0;
	//mark the terminals and nonterminals with their indexes just to print
	for(it=ter.begin();it!=ter.end();it++)
	{
		mp[*it]=c;
		c++;
	}
	for(it=nonter.begin();it!=nonter.end();it++)
	{
		mp[*it]=c;
		c++;
	}
	cout<<endl;
	char ch;
	while(!order.empty())
	{
		ch=order.top();
		y=closure[ch];
		order.pop();
		//to store the closure to make changes in it
		m=y;
		//not directly in y since y.size() is taken in loop
		//take all productions in closure one by one
		for(int j=0;j<y.size();j++)
		{
			//to remove recursive calculation of closure
			if(y[j][3]!=ch)
			{
				//store closure of non-terminal in production
				if(y[j][3]>='A'&&y[j][3]<='Z')
				{
					r=closure[y[j][3]];
					for(int k=0;k<r.size();k++)
					{
						m.push_back(r[k]);
					}
				}
				//update closure
				closure[ch]=m;
			}
		}
	}
	int i=1;
	vector<pair<string,int> > f,new_s,mn;
	pair<string,int> rule;
	y=closure['Z'];
	//f is ging to be 1st state
	//initially dot at index 3
	for(int j=0;j<y.size();j++)
	{
		f.push_back(make_pair(y[j],3));
	}
	vector<int> final;
	int x=1,b;
	//inserted in set of state so dat no duplicates
	state.insert(f);
	//both ways index to state and vice versa
	index[i]=f;
	get_i[f]=i;
	while(true)
	{
		//according to bfs if no more states available then break else find further states
		if(index.find(i)!=index.end())
		{
			f=index[i];
		}
		else
		{
			break;
		}
		//check all rules using dot
		for(int g=0;g<f.size();g++)
		{
			rule=f[g];
			//if . location==size 
			if(rule.second==rule.first.size())
			{
				continue;
			}
			else
			{
				//make a new state with all previous productions transitioning on the same particular character with previous state productions to be included 
				ch=rule.first[rule.second];
				for(int u=0;u<f.size();u++)
				{
					if(f[u].first[f[u].second]==ch)
					{
						new_s.push_back(make_pair(f[u].first,f[u].second+1));
					}
				}
				mn=new_s;
				int kl;
				for(int l=0;l<new_s.size();l++)
				{
					//compare not the end
					if(new_s[l].second!=new_s[l].first.size())
					{
						//just next nonterminal after the dot
						kl=new_s[l].first[new_s[l].second];
						if(kl>='A'&&kl<='Z')
						{
							y=closure[kl];
							//To avoid adding repititive production like for E->.T
							//T->.i already added
							//dont add T->.i else add 
							for(int w=0;w<y.size();w++)
							{
								int a;
								for(a=0;a<new_s.size();a++)
								{
									if(y[w]==new_s[a].first&&new_s[a].second==3)
									{
										break;
									}
								}
								if(a==new_s.size())
								{
									mn.push_back(make_pair(y[w],3));
								}
							}
						}
					}
				}
				new_s=mn;
				cout<<ch<<endl;
				//if no similar state exists then give an index and store that particular state given indexing and mark in graph
				if(state.find(new_s)==state.end())
				{
					state.insert(new_s);
					x++;
					get_i[new_s]=x;
					index[x]=new_s;
					int o=mp[ch];
					graph[i][o]=x;
					cout<<x<<endl;
					for(int l=0;l<new_s.size();l++)
					cout<<new_s[l].first<<"\n";
				cout<<"\n";
				}
				else
				{
					b=get_i[new_s];
					cout<<b<<"\n";
					int o=mp[ch];
					graph[i][o]=b;	
				}
		}
		new_s.clear();
	}
	i++;
}
	//cout<<x<<endl;
	cout<<"  ";
	for(ij=mp.begin();ij!=mp.end();ij++)
	{
		cout<<ij->first<<"  ";
	}
	cout<<"\n";
	for(int l=1;l<=x;l++)
	{
		cout<<l<<" ";
		int c=0;
		for(ij=mp.begin();ij!=mp.end();ij++)
		{
			if(graph[l][ij->second]!=0)
			{
				c++;
			}
	//		cout<<graph[l][ij->second]<<" ";
		}
		for(ij=mp.begin();ij!=mp.end();ij++)
		{
			g[l][ij->second]="";
			if(l==2&&ij->first=='$')
			{
				cout<<"A  ";
				g[l][ij->second]="A";
			}
			else if(l==2&&(ij->first<65||ij->first>90))
			{
				cout<<"E  ";
				g[l][ij->second]="E";
			}
			else if(c==0&&(ij->first<65||ij->first>90))
			{
				cout<<"R";
				g[l][ij->second]="R";
				for(int aa=0;aa<v.size();aa++)
				{
					if(v[aa]==index[l][0].first)
					{
						cout<<aa<<" ";
						

						stringstream convert; // stringstream used for the conversion

						convert << aa;//add the value of Number to the characters in the stream

						g[l][ij->second]+=convert.str();
						break;
					}
				}
			}
	   		else if(c!=0&&graph[l][ij->second]&&(ij->first<65||ij->first>90))
			{
				cout<<"S"<<graph[l][ij->second]<<" ";
				g[l][ij->second]="S";
				stringstream convert; // stringstream used for the conversion

				convert << graph[l][ij->second];//add the value of Number to the characters in the stream

				g[l][ij->second]+=convert.str();
			}
			else if(c!=0&&graph[l][ij->second]&&(ij->first>=65&&ij->first<=90))
			{
				cout<<graph[l][ij->second]<<" ";
				stringstream convert; // stringstream used for the conversion

				convert << graph[l][ij->second];//add the value of Number to the characters in the stream

				g[l][ij->second]+=convert.str();
			}
			else
			{
				cout<<"-  ";
				g[l][ij->second]="-";
			}
		//	cout<<l<<" "<<ij->second<<" "<<g[l][ij->second]<<"\n";
		}
		cout<<endl;
	}
	string a;
	cout<<"Enter the string\n";
	cin>>a;
	stack<int> stk;
	stk.push(1);
	for(int tt=0;;)
	{
		printf("%d\n",stk.top());
		cout<<g[stk.top()][mp[a[tt]]]<<"\n";
		if(mp.find(a[tt])!=mp.end()&&g[stk.top()][mp[a[tt]]]!="-")
		{
			if(g[stk.top()][mp[a[tt]]]=="A")
			{
				printf("Accepted\n");
				break;
			}
			else if(g[stk.top()][mp[a[tt]]]=="E")
			{
				printf("Error\n");
				break;
			}
			else if(g[stk.top()][mp[a[tt]]][0]=='S')
			{
				string rr=g[stk.top()][mp[a[tt]]].substr(1);
				stk.push(mp[a[tt]]);
				stringstream ss(rr);
				int x;
				ss >> x;
				stk.push(x);
				tt++;
			}
			else if(g[stk.top()][mp[a[tt]]][0]=='R')
			{
				string rr=g[stk.top()][mp[a[tt]]].substr(1);
				stringstream ss(rr);
				int x;
				ss >> x;
				int dd=v[x].size()-3;
				dd=2*dd;
				while(dd--)
				{
					stk.pop();
				}
				int yy=stk.top();
				tt--;
				stk.push(mp[v[x][0]]);
				rr=g[yy][mp[v[x][0]]];
				stringstream sst(rr);
				sst >> x;
				stk.push(x);
				tt++;
			}
		}
		else
		{
			printf("Error\n");
			break;
		}
	}
return 0;
}

#include<bits/stdc++.h>
using namespace std;
char a[100][100];
int col;

struct firTab
{
	int n;
	char firT[5];
};

struct firTab first[5];

struct folTab {
	int n;
	char folT[5];
};
struct folTab follow[5];
void findFirst(char ,char);
void findFollow(char ,char);
void firTabOperation(char ,char);
void folTabOperation(char ,char);
void lr0();
int m,cnt=0;
int main()
{
	freopen("slr1input.txt","r",stdin);
	scanf("%d",&m);
	int i,j,c=0;
	char ip;
	char b[m];
	
	cout<<"Given Grammar\n";
	for(i=0;i<m;i++) {
		scanf("%s",&a[i]);
		cout<<a[i]<<"\n";
	}
	
	for(i=0;i<m;i++) {
		c=0;
		for(j=0;j<i+1;j++)
		{
			if(a[i][0]==b[j])
			{
				c=1;
				break;
			}
		}
		if(c!=1)
		{
			b[cnt]=a[i][0];
			cnt++;
		}
	}
	
	printf("\n");
	
	for(i=0;i<cnt;i++) {
		col=1;
		first[i].firT[0]=b[i];
		first[i].n=0;
		findFirst(b[i],i);
	}
	
	for(i=0;i<cnt;i++) {
		col=1;
		follow[i].folT[0]=b[i];
		follow[i].n=0;
		findFollow(b[i],i);
	}
	printf("\n");
    cout << "----------------------------------FIRST OF ALL----------------------------\n";
    
	for(i=0;i<cnt;i++) {
    	for(j=0;j<=first[i].n;j++)
    	{
        	if(j==0)
            {
                printf("First(%c) : {",first[i].firT[j]);
            }
            else
            {   
                printf(" %c",first[i].firT[j]);
            }
    	}
    printf(" } ");
    printf("\n");
    } 
    printf("\n");
    cout << "----------------------------------FOLLOW OF ALL----------------------------\n";
    
	for(i=0;i<cnt;i++) {
    	for(j=0;j<=follow[i].n;j++) {
            if(j==0) {
                printf("Follow(%c) : {",follow[i].folT[j]);
            }
            else {   
                printf(" %c",follow[i].folT[j]);
            }
    	}
    printf(" } ");
    printf("\n");
    }
    lr0();
	return 0; 
}
void findFirst(char ip,char pos)
{
	int i;
	for(i=0;i<m;i++)
	{
		if(ip==a[i][0])
		{
			if(isupper(a[i][3]))
			{
				findFirst(a[i][3],pos);
			}
			else
			{
				first[pos].firT[col]=a[i][3];
				first[pos].n++;
				col++;
			}
		}
	}
}
void findFollow(char ip,char row)
{
	int i,j;
	if(row==0&&col==1)
	{
		follow[row].folT[col]='$';
		col++;
		follow[row].n++;
	}
	for(i=0;i<m;i++)
	{
		for(j=3;j<7;j++)
		{
			if(a[i][j]==ip)
			{
				if(a[i][j+1]=='\0')
				{
					if(a[i][j]!=a[i][0])
					{
						folTabOperation(a[i][0],row);
					}
				}
				else if(isupper(a[i][j+1]))
				{
					if(a[i][j+1]!=a[i][0])
					{
						firTabOperation(a[i][j+1],row);
					}
				}
				else
				{
					follow[row].folT[col]=a[i][j+1];
					col++;
					follow[row].n++;
				}
			}
		}
	}
}
void folTabOperation(char ip,char row)
{
	int i,j;
	for(i=0;i<cnt;i++)
	{
		if(ip==follow[i].folT[0])
		{
			for(j=1;j<=follow[i].n;j++)
			{
				follow[row].folT[col]=follow[i].folT[j];
				col++;
				follow[row].n++;
			}
		}
	}
}
void firTabOperation(char ip,char row)
{
	int i,j;
	for(i=0;i<cnt;i++)
	{
		if(ip==first[i].firT[0])
		{
			for(j=1;j<=first[i].n;j++)
			{
				if(first[i].firT[j]!='0')
				{
					follow[row].folT[col]=first[i].firT[j];
					follow[row].n++;
					col++;
				}
				else
				{
					folTabOperation(ip,row);
				}
			}
		}
	}
}
void lr0()
{
	int n;
	int graph[100][100];
	memset(graph,0,sizeof(graph));
	string g[100][100];
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
	FILE *ptr=fopen("slr1input.txt","r+");
	cout<<"enter the number of productions"<<endl;
	fscanf(ptr,"%d",&n);
	cout<<n<<"\n";
	order.push('Z');
	ter.insert('$');
	map<char,int> mp;
	map<char,int>::iterator ij;
	cout<<"enter the productions"<<endl;
	char a[100];
	for(int i=0;i<n;i++)
	{
		fscanf(ptr,"%s",&a);
		s=string(a);
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
		if(i==0)
		{
			t="Z->";
			t+=s[0];
			t+="$";
			y=closure['Z'];
			y.push_back(t);
			closure['Z']=y;
			nonter.insert(s[0]);
			v.push_back(t);
		}
		v.push_back(s);
	}
	cout<<endl;
	int c=0;
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
		m=y;
		for(int j=0;j<y.size();j++)
		{
			if(y[j][3]!=ch)
			{
				if(y[j][3]>='A'&&y[j][3]<='Z')
				{
					r=closure[y[j][3]];
					for(int k=0;k<r.size();k++)
					{
						m.push_back(r[k]);
					}
				}
				closure[ch]=m;
			}
		}
	}
	int i=1;
	vector<pair<string,int> > f,new_s,mn;
	pair<string,int> rule;
	y=closure['Z'];
	for(int j=0;j<y.size();j++)
	{
		f.push_back(make_pair(y[j],3));
	}
	vector<int> final;
	int x=1,b;
	state.insert(f);
	index[i]=f;
	get_i[f]=i;
	while(true)
	{
		if(index.find(i)!=index.end())
		{
			f=index[i];
		}
		else
		{
			break;
		}
		for(int g=0;g<f.size();g++)
		{
			rule=f[g];
			if(rule.second==rule.first.size())
			{
				continue;
			}
			else
			{
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
					if(new_s[l].second!=new_s[l].first.size())
					{
						kl=new_s[l].first[new_s[l].second];
						if(kl>='A'&&kl<='Z')
						{
							y=closure[kl];
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
	//	cout<<graph[l][ij->second]<<" ";
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
				int f=0,f1=0;
				for(int aaa=0;aaa<cnt;aaa++)
				{
					if(follow[aaa].folT[0]==index[l][0].first[0])
					{
						f=aaa;
						break;
					}
				}
		//	cout<<f<<" "<<follow[f].folT[0]<<"\n";
				for(int as=0;as<=follow[f].n;as++)
				{
			//	cout<<follow[f].folT[as]<<"\n";
				if((ij->first==follow[f].folT[as]))
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
					f1=1;
					break;
				}
			}
			if(f1==0)
			{
				cout<<"-  ";
				g[l][ij->second]="-";
				
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
	}
	cout<<endl;
}
	string at;
	cout<<"Enter the string\n";
	cin>>at;
	stack<int> stk;
	stk.push(1);
	for(int tt=0;;)
	{
		printf("%d\n",stk.top());
		cout<<g[stk.top()][mp[at[tt]]]<<"\n";
		if(mp.find(at[tt])!=mp.end()&&g[stk.top()][mp[at[tt]]]!="-")
		{
			if(g[stk.top()][mp[at[tt]]]=="A")
			{
				printf("Accepted\n");
				break;
			}
			else if(g[stk.top()][mp[at[tt]]]=="E")
			{
				printf("Error\n");
				break;
			}
			else if(g[stk.top()][mp[at[tt]]][0]=='S')
			{
				string rr=g[stk.top()][mp[at[tt]]].substr(1);
				stk.push(mp[at[tt]]);
				stringstream ss(rr);
				int x;
				ss >> x;
				stk.push(x);
				tt++;
			}
			else if(g[stk.top()][mp[at[tt]]][0]=='R')
			{
				string rr=g[stk.top()][mp[at[tt]]].substr(1);
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
	fclose(ptr);
}

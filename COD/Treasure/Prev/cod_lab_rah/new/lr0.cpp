#include<bits/stdc++.h>
using namespace std;

int main()
{
	int n;
	char graph[100][100];
	int table[100][100];
	memset(table,0,sizeof(table));
	memset(graph,'-',sizeof(graph));
	vector<string>v;
	set<char>ter,nonter;
	stack<char>order;
	set<char>::iterator it;
	map<char,vector<string> > closure;
	map<char,vector<string> >::iterator p;
	map<int,vector<pair<string,int> > >index;
	map<vector<pair<string,int> >,int >get_i;
	map<int,vector<pair<string,int> > >::iterator q;
	nonter.insert('Z');
	string s,t;
	vector<string>y,r,m;
	set<vector<pair<string,int> > > state;
	cout<<"enter the number of productions"<<endl;
	cin>>n;
	order.push('Z');
	ter.insert('$');
	map<char,int>mp;
	map<int,char>mp1;
	map<int,char>::iterator ik;
	map<char,int>::iterator ij;
	cout<<"enter the productions"<<endl;
	for(int i=0;i<n;i++){
		cin>>s;
		if(nonter.find(s[0])==nonter.end()){
			//cout<<s<<endl;
					order.push(s[0]);
		}
		y = closure[s[0]];
		y.push_back(s);
		closure[s[0]] = y;
		nonter.insert(s[0]);
		for(int j=3;j<s.size();j++){
			if(s[j]>=65&&s[j]<=90){
				if(nonter.find(s[j])==nonter.end()){
			//cout<<s<<endl;
					order.push(s[j]);
		}
				nonter.insert(s[j]);
				
			}
			else{
				ter.insert(s[j]);
			}
		}
		if(i==0){
			t = "Z->";
			t+= s[0];
			t+="$";
			y = closure['Z'];
			y.push_back(t);
		closure['Z'] = y;
		nonter.insert(s[0]);
			
			v.push_back(t);
		}
		
		v.push_back(s);
	}
	cout<<endl;
	int c =0;
	for(it=ter.begin();it!=ter.end();it++){
		//cout<<*it<<" ";
		mp[*it] = c;
		mp1[c] = *it;
		c++;
	}
	for(it=nonter.begin();it!=nonter.end();it++){
		//cout<<*it<<" ";
		mp[*it] = c;
		mp1[c]=*it;
		c++;
	}
	/*for(ij=mp.begin();ij!=mp.end();ij++){
		cout<<ij->first<<" "<<ij->second<<endl;
	}*/
	cout<<endl;
	char ch;
	while(!order.empty()){
		
		ch = order.top();
	//	cout<<ch<<endl;
		y = closure[ch];
		order.pop();
		m = y;
		for(int j = 0;j<y.size();j++){
			//cout<<y[j][3]<<endl;
			if(y[j][3]!=ch){
			
			if(y[j][3]>='A'&&y[j][3]<='Z'){
				r = closure[y[j][3]];
				for(int k=0;k<r.size();k++){
					m.push_back(r[k]);
				}
			}
			closure[ch] = m;
		}
		}
		//cout<<endl;
	}
	/*for(p=closure.begin();p!=closure.end();p++){
		cout<<p->first<<endl;
		y = p->second;
		for(int i=0;i<y.size();i++){
			cout<<y[i]<<endl;
		}
		cout<<endl;
	}*/
	int i=1;
	vector<pair<string,int> >f,new_s,mn;
	pair<string,int>rule;
	y = closure['Z'];
	for(int j=0;j<y.size();j++){
		f.push_back(make_pair(y[j],3));
	}
	vector<int>final;
	int x =1,b;
	state.insert(f);
	index[i] = f;
	get_i[f] = i;
	while(true){
		if(index.find(i)!=index.end())
		f = index[i];
		else
		break;
		
		for(int g=0;g<f.size();g++){
			rule = f[g];
			//cout<<rule.first<<endl;
			if(rule.second==rule.first.size()){
				
				continue;
			}
			else{
				ch = rule.first[rule.second];
				for(int u=0;u<f.size();u++){
					//cout<<f[u].first<<endl;
					if(f[u].first[f[u].second]==ch){
						new_s.push_back(make_pair(f[u].first,f[u].second+1));
					}
				}
				mn = new_s;
				int kl;
				for(int l=0;l<new_s.size();l++){
					if(new_s[l].second!=new_s[l].first.size()){
						//cout<<" hi " <<new_s[l].first<<endl;
						kl = new_s[l].first[new_s[l].second];
						if(kl>='A'&&kl<='Z'){
							y = closure[kl];
							for(int w=0;w<y.size();w++){
								int a;
								for(a=0;a<new_s.size();a++){
									if(y[w]==new_s[a].first&&new_s[a].second==3){
										break;
									}
								}
								if(a==new_s.size()){
									mn.push_back(make_pair(y[w],3));
								}
							}	
						}
				}
				}
				new_s = mn;
				cout<<ch<<endl;
				if(state.find(new_s)==state.end()){
					state.insert(new_s);
					x++;
					index[x] = new_s;
					get_i[new_s] = x;
					int o = mp[ch];
					graph[i][x] = ch;
					table[i][o] = x;
				//cout<<x<<endl;
					for(int l=0;l<new_s.size();l++){
					cout<<new_s[l].first<<endl;
				}	
				cout<<endl;
				}
				else{
					
					b = get_i[new_s];
					//cout<<"hello " <<b<<endl;
					int o = mp[ch];
					table[i][o] = b;
					graph[i][b] = ch;
				}
			}
			new_s.clear();
		}
		i++;
	}
	
	for(int l=1;l<=x;l++){
		//cout<<l<<" ";
			for(int w=1;w<=x;w++){
				cout<<graph[l][w]<<" ";		
			}
			cout<<endl;
	}
	cout<<"\tTABLE"<<endl;
	cout<<"  ";
	for(ik=mp1.begin();ik!=mp1.end();ik++){
		cout<<ik->second<<" ";
	}
	cout<<endl;
	for(int l=1;l<=x;l++){
		cout<<l<<" ";
		int w=0,sf;
		for( w=0;w<ter.size();w++){
			if(table[l][w]!=0){
				break;
			}
		}
		//if(w!=ter.size()){
			for( sf=0;sf<mp.size();sf++){
			cout<<table[l][sf]<<" ";
		}	
		
		cout<<endl;
	}
	return 0;
}

#include <bits/stdc++.h>
using namespace std;
vector<int> v,v1;
string s[1000];
set<int> st[1000],ST,all[1000];
set<int> :: iterator it;
int total=0,x=0;
int freq[1000];
map<set<int>,float> mp;

int sToi( string s)
{
	stringstream stm(s);
    int x = 0;
    stm >> x;
    return x;
}

void combinationUtil(int arr[], int data[], int start, int end,int index, int r)
{
	if (index == r)
    {
        for (int j=0; j<r; j++)
            all[x].insert(data[j]);
        x++;
        return;
    }
    for (int i=start; i<=end && end-i+1 >= r-index; i++)
    {
        data[index] = arr[i];
        combinationUtil(arr, data, i+1, end, index+1, r);
    }
}

void allCombination(int arr[], int n, int r)
{
    int data[r];
    combinationUtil(arr, data, 0, n-1, 0, r);
}


int main(int argc,char* argv[])
{

	int arr[100];
	int i,j,k;
	int inp;
	FILE *fp;
    char buf[1000];
    fp =fopen(argv[5],"r");
    if(!fp)
    	inp=-1;
    else
	    while(fgets(buf,1000, fp)!=NULL){
	       	//printf("%s",buf);
	       	string str(buf);
	       	s[total] = str;
	       	//cout<<str<<endl;
	       	total++;
	    }
	fclose(fp);
	float subs=total*atof(argv[2]),conf=total*atof(argv[4]);
	if(inp==-1) {
		printf("Error reading file");
	}
	for(i=0;i<total;i++){
		//cout<<s[i]<<endl;
		st[i].clear();
		istringstream iss(s[i]);
		string subs;
	   	iss >> subs;
		while (iss)
    	{
    		freq[sToi(subs)]++;
	    	st[i].insert(sToi(subs));
    		ST.insert(sToi(subs));
    		iss >> subs;
    	} 
	}
	
	for(it=ST.begin();it!=ST.end();it++) {
		all[x].insert(*it);
		arr[x]=*it;
		x++;
	}
	for(i=2;i<=total;i++) {
		allCombination(arr, ST.size(), i);
	}
	int sz=x;
	bool flag=0;
	for(k=0;k<total;k++) {
		for(i=0;i<sz;i++) {
			flag=0;
			for(it=all[i].begin();it!=all[i].end();it++) {
				if(st[k].find(*it)==st[k].end()) {
					flag=1;
				}		
			}
			if(!flag) {
				if(mp.find(all[i])!=mp.end())
					mp[all[i]]++;
				else 
					mp.insert(make_pair(all[i],1));
			}
		}
	}
	int mx=0;
	for(i=0;i<sz;i++) {
		if(mp[all[i]]>subs) { 
			v.push_back(i);
			mx=max(mx,(int)all[i].size());
		}
	}
	for(i=0;i<v.size();i++) {
		if(all[v[i]].size()==mx) { 
			v1.push_back(v[i]);
			for(it=all[v[i]].begin();it!=all[v[i]].end();it++) {
				cout<<*it<<" ";
			}
			cout<<"\t\t\t"<<mp[all[v[i]]]<<endl;
		}
	}
	v.clear();
	int arra[mx];
	set<int> r1,r2,l;
	for(i=0;i<v1.size();i++) {
		k=0;
		for(it=all[v1[i]].begin();it!=all[v1[i]].end();it++) {
			arr[k]=*it;
			k++;
		}
		
	}

return 0;
}

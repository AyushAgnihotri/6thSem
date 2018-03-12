#include<bits/stdc++.h>
using namespace std;
#define SIZE 10001

struct hash {
	set<string> v;
	int idx;
};
struct find_attr {
	string type;
	int hash_value;
	bool flag;
};
struct hash hash_table[SIZE];
map < int ,string > attribute;
set<string> :: iterator st_it;
void print()
{
	int i,j,k,l;
	for(i=0;i<=1000;i++) {
		if(hash_table[i].idx==1) {
			cout<<"DATA TYPE : "<<attribute[i]<<endl;
			for(st_it=hash_table[i].v.begin();st_it!=hash_table[i].v.end();++st_it)
			cout<<*st_it<<" , ";
			cout<<endl<<endl;
		}
	}
}
int hash_idx (string s)
{
	int i,j,l=s.size();
	int sum=0;
	for(i=0;i<l;i++) {
		sum += s[i];
	}
	return sum%SIZE;
} 
void insert(string type, string name)
{
	int idx,i,j,k;
	idx = hash_idx(type);
	hash_table[idx].v.insert(name);
//	for(st_it=hash_table[idx].v.begin();st_it!=hash_table[idx].v.end();++st_it)
//	cout<<*st_it<<" ";
//	cout<<endl<<endl;
	if(hash_table[idx].idx==0) 
	{ 
	hash_table[idx].idx=1;
	attribute[idx]=type;
    }
}

struct find_attr find(string name)
{
	int i,j,k,l,f=0;
	struct find_attr node;
	node.flag=false;
	for(i=0;i<=1000;i++) {
		if(hash_table[i].idx==1) {
		//	cout<<"pp"<<endl;
				if(hash_table[i].v.find(name)!=hash_table[i].v.end() ){
					//cout<<"ppppp"<<endl;
					node.hash_value=i;
					node.type =attribute[i];
					node.flag=true;
					return node;
					break;
				}
				
				}
		}
	
	return node;
	
}
void del(string name)
{
	struct find_attr node;
	node = find(name);
	if(node.flag==false)
	cout<<"NOT EXIST"<<endl;
	else {
		for(int i=0;i<=1000;i++) {
		if(hash_table[i].idx==1) {
			if(hash_table[i].v.find(name)!=hash_table[i].v.end())
			hash_table[i].v.erase(hash_table[i].v.find(name));
		}
	}
		
	}
}
int main()
{
	int i,j,kdx;
	printf("1.\tINSERT\n2.\tCHECK\n3.\tPRINT_TABLE\n4.\tDELETE\n");
	cin>>kdx;
	string type,name;
	for(i=0;i<=1000;i++)
	hash_table[i].idx=0;

	while(kdx!=5) 
	{
		if(kdx==1)
		{
			struct find_attr node;
			cin>>type>>name;
			node = find(name);
			if(node.flag==true) {
			cout<<"	VARIABLE ALREADY EXIST "<<endl;
			if(node.type==type)
			cout<<"SAME TYPE"<<endl;
			else {
				cout<<"CONFLICTING TYPE"<<endl;
				cout<<"Hash_vale:  "<<node.hash_value<<" "<<"VARIABLE:  "<<name<<" "<<"TYPE:  "<<node.type<<endl<<endl;
			}
			} else {
				insert(type,name);
				cout<<"Done"<<endl;
			}
	}
		 else if (kdx==2) {
			cin>>name;
			struct find_attr node;
			node = find(name);
			if(node.flag==true) {
				cout<<"	VARIABLE FOUND "<<endl;
				cout<<"Hash_vale:  "<<node.hash_value<<" "<<"VARIABLE:  "<<name<<" "<<"TYPE:  "<<node.type<<endl<<endl;
			
		} else {
			cout<<"NOT FOUND"<<endl;
		}
	} else if(kdx==3)
	{
		print();
	}
	else if(kdx==4)
	{
		cin>>name;
		del(name);
	}
			printf("1.\tINSERT\n2.\tCHECK\n3.\tPRINT_TABLE\n4.\tDELETE\n");
			cin>>kdx;
	}
	return 0;
}

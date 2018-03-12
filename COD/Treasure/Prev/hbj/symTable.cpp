#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cstdlib>
#include<vector>
#include<map>
#include<set>
#define tb_size 101
using namespace std;

struct hash_table {
	
	string symbl;
	set<string> v;
	int idx;
	
};

struct hash_table hash[tb_size];


int hash_function(string name)
{

	int sum=0;

	for(int i=0; i<name.size(); i++) {

		int ch = name[i];
	//	sum += ch;
		sum += ((i<<7)*ch);
	}
	
	int i = sum%tb_size;
	return i;
}

void hash_display()
{
	cout<<"TABLE_INDEX"<< "\t"<<"SYMBOL" << "\t" << "DATA TYPES" <<endl;
	for(int i=0 ; i<tb_size; i++) {

		if(hash[i].idx==1) {
			int p = hash_function(hash[i].symbl);
			cout<<p<<"\t\t"<<hash[i].symbl<<"\t";
			set<string>:: iterator it;
			
			cout<<"(";
			for(it=hash[i].v.begin(); it!=hash[i].v.end(); ++it) {

				cout<<*it<<", ";
			}
			cout<<")"<<endl;
		}
	}
}

bool hash_search(string type, string sym)
{

	int p = hash_function(sym);
	

	if(hash[p].idx==0) {
		return false;
	} else if (type!="") {
		if(hash[p].v.find(type) != hash[p].v.end()) {
			return true;
		}
		else {
			return false;
		}
		
	}  else {
		cout<<"SYMBOL" << sym<< " found at " << p <<endl;
		set<string> :: iterator it;
		for(it=hash[p].v.begin(); it!=hash[p].v.end(); ++it) {
			cout<< *it <<", ";
			
		}
		cout<<endl;
		return true;	
	}

	
}
		

void hash_insert(string type, string sym)
{
	int p = hash_function(sym);
	cout<<p<<endl;

	if(hash[p].idx==0) {
		cout<<"pp"<<endl;
		hash[p].symbl = sym;
		hash[p].v.insert(type);
		hash[p].idx=1;
	} else {
		cout<<"pp2"<<endl;
		if(hash_search(type, sym)) {
			
			cout<<"SYmbol " << sym << " already exists "<<"in "<<p<<endl;
		} else {
			hash[p].v.insert(type);
		}
	}
		
}

void hash_delete(string sym)
{

	int p = hash_function(sym);
	
	hash[p].idx= 0;

	hash[p].v.clear();
	hash[p].symbl.clear();
}

int main()
{

	string type, symbol;
	int idx;
	int c;
	bool vr;
	for(int i=0; i<101; i++) {
		hash[i].idx=0;
	}
	while(1){
	printf("1. Insert\n 2. Search\n 3. Delete\n 4. Display\n");

	cin>>c;
	switch(c) {

		case 1: cin>>type>>symbol;
			//int p = hash_function(symbol);
			hash_insert(type, symbol);
			continue;
		case 2: cin>>symbol;
			vr = hash_search("", symbol);
			if(!vr) {
				cout<<"symbol not found\n";
			}
			continue;
			
		case 3: cin>>symbol;
			hash_delete(symbol);
			continue;
		
		case 4: hash_display();
			continue;
		
		default : break;
	}
	}

	return 0;
}
							

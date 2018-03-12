#include<cstdio>
#include<iostream>
#include<cstring>
#include<cstdlib>
#include<string>
#include<vector>
#include<map>
#include<set>
#define tb_size 31
using namespace std;

map<string, string> mp;
map<int , string> indxfile;
vector<string> v;

string data_types[4]  = {"int", "char", "float", "double"};


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
		sum += (((i+1)<<7)*ch);
	}
	
	int i = sum%tb_size;
	return i;
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
	

	if(hash[p].idx==0) {
	
		hash[p].symbl = sym;
		hash[p].v.insert(type);
		hash[p].idx=1;
	} else {
	
		if(hash_search(type, sym)) {
			
			cout << sym << " " << "- multiple declaration" << endl;
		} else {
			hash[p].v.insert(type);
		}
	}
		
}


int main()
{

	string str;

	freopen("1.c", "r", stdin);


	int i=0;
	
	while(getline(cin, str)) {

		
		indxfile[i] = str;
		
		i++;
	}

	string tmp = indxfile[2];

	string s1="", s2="";
	int k;
	

	for(int j=0; j<tmp.size(); j++) {
		
		if(tmp[j]>='a' && tmp[j]<='z') {
			s1 += tmp[j];		
		}
				

	}
	

	string ks1="";

	int f = 0;

	for(int i=0; i<s1.size(); i++) {

		ks1 += s1[i];
		k=i;
		
		for(int i=0; i<4; i++) {
			
			if(ks1 == data_types[i]) {

				f=1;
				break;
			}


		}
		if(f) {
			break;
		}
	}

	s2 += s1[k+1];

	string tmp1 = indxfile[4];

	string s11="", s21="";
	int k1;
	

	for(int j=0; j<tmp1.size(); j++) {
		
		if(tmp1[j]>='a' && tmp1[j]<='z') {
			s11 += tmp1[j];		
		}
				

	}
	

	string ks11="";

	int f1 = 0;

	for(int i=0; i<s11.size(); i++) {

		ks11 += s11[i];
		k1=i;
		
		for(int i=0; i<4; i++) {
			
			if(ks11 == data_types[i]) {

				f1=1;
				break;
			}


		}
		if(f1) {
			break;
		}
	}

	s21 += s11[k+1];

	
	string symbol = s2;
	string type = ks1;

	int p1 = hash_function(symbol);
	
	hash_insert(type, symbol);

	string symbol1 = s21;
	string type1 = ks11;
	
	hash_insert(type1, symbol1);

	string name1 = "n";

	bool r = hash_search("", name1);
	if(!r) {

		cout<< name1 << " " << "- undeclared"<<endl;
	}
	
	return 0;
}

#include<bits/stdc++.h>
#define MAX 50
using namespace std;
 
string gram[MAX][MAX];  
string dpr[MAX];
int p,np,mx,mn;       
 
string joined( string s1, string s2)  
{
    int i,j,k;
    string res;
	res = s1;
    for(i=0; i<s2.length();i++)
        if(res.find(s2[i]) > res.length())
            res+=s2[i];
    return (res);
}
 
void break_gram(string a) {
    
	int i, k, l;
    p = 0;
    
    while(a.length()) {
        i=a.find("|");
        
        if(i > a.length()) {
            dpr[p++] = a;
            a="";
        } else {
            dpr[p++] = a.substr(0,i);
            a=a.substr(i+1,a.length());
        }
    }
}
 
inline int lchomsky(string a) {
	//checking if the length is 1 and the letter found belongs to non-terminal
    if(a.length()==1 && a[0]>='A' && a[0]<='Z')
        return 1;
    return 0;
}
 
int rchomsky(string a) {
	
	int len = a.length();
	char fr = a[0];
    
	if (len == 1 && fr>='a' && fr <='z')
    	return 1;
    
	if (len==2 && fr>='A' && fr<='Z' && fr>='A' && fr<='Z' )
    	return 1;
    
	if(len==1 && ( fr=='('  ||fr==')' ))
    	return 1;
    
	return 0;
}
 
string search_prod(string p) {
    int j,k;
    string r="";
    for(j=0;j<np;j++)
    {
        k=1;
        while(gram[j][k] != "")
        {
            if(gram[j][k] == p)
            {
                r=joined(r,gram[j][0]);
            }
            k++;
        }
    }   
    return r;
}
 
string gen_comb(string a, string b) {
    int i,j;
    string pri=a,re="";
    for(i=0;i<a.length();i++)
        for(j=0;j<b.length();j++)
        {
            pri="";
            pri=pri+a[i]+b[j];
            re=re+search_prod(pri);    
        }       
    return re;
}
 
int main() {
    int i,pt,j,l,k;
    string a,str,r,pr,start;
 
   // cout<<"\n START ";
   // cin >> start;
    cout<<"\n Enter no of productions: ";
   // input no of productions
	cin >> np;
 
 // taking input of productions
    for(i = 0; i < np; i++) {
        cin >> a;
        
        //finding the symbol so as to tak the first part and check for correctness 
        pt = a.find("->");
        gram[i][0] = a.substr(0,pt);
        
        //if the returned answer is 0 then it is not in chomsky form
        if (lchomsky(gram[i][0]) == 0) {
            cout<<"\n not in CNF";
            abort();
        }
        
        //taking the substring after the symbol ->
        a = a.substr(pt+2, a.length());
        break_gram(a);
        
        for(j=0;j<p;j++) {
            gram[i][j+1]=dpr[j];
            if (rchomsky(dpr[j]) == 0)
            {
                cout<<"\n not in CNF";
                abort();
            }
        }
    }
    string matrix[MAX][MAX],st;
    cout<<"\n ENTER INPUT STRING : ";
    cin >> str;
    
    for(i = 0; i < str.length(); i++) {
        r = "";
        st = "";
        st += str[i];
        
        for(j = 0; j < np; j++) {
            k = 1;
            while(gram[j][k] != "") {
                if(gram[j][k] == st) {
                    r=joined(r,gram[j][0]);
                }
                k++;
            }
        }
        
        matrix[i][i]=r;
    }
    int ii,kk;
    for(k=1;k<str.length();k++)       
    {
        for(j=k;j<str.length();j++)
        {
            r="";
            for(l=j-k;l<j;l++)
            {
                pr = gen_comb(matrix[j-k][l],matrix[l+1][j]);
                r = joined(r,pr);
            }
            matrix[j-k][j] = r;
        }
    }
 
    for(i=0;i<str.length();i++)   
    {
        k=0;
        l=str.length()-i-1;
        for(j=l;j<str.length();j++)
        {
            cout<<setw(5)<<matrix[k++][j]<<"  ";
        }
        cout<<endl;
    }
             
    int f=0;
    for(i=0;i<start.length();i++)
        if(matrix[0][str.length()-1].find(start[i]) <= matrix[0][str.length()-1].length())   //Checks if last element of first row contains a Start variable
        {
            cout<<"successful\n";
            return 0;
        }
    cout<<"no success\n";
    return 0;
}

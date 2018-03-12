#include<bits/stdc++.h>

using namespace std;

int main()
{
	vector<string>ans;
    int a,i,j;
    string str;
    cin>>str;
    while(str.length()-1){
    	bool temp = true;
        for(i=0;i<str.length();i++)
        {
            if(str[i]=='('&&str[i+1]==')')
            {
                str[i] ='S';
                j = i;
                for(int k=i;k<str.length()-1;k++)
                {
                    str[k+1] = str[k+2];
                }
                str = str.substr(0,str.length()-1);
                temp = false;
                break;
            }
            else if(str[i]=='(' && str[i+1]=='S'&&str[i+2]==')')
            {
                str[i] = 'S';
                 for(int k=i;k<str.length()-1;k++)
                {
                    str[k+1] = str[k+3];
                }
                str = str.substr(0,str.length()-2);
                temp = false;
                break;
            }
            else if(str[i]=='S' && str[i+1]=='S')
            {
                for(int k=i;k<str.length()-1;k++)
                {
                    str[k+1] = str[k+2];
                }
                str = str.substr(0,str.length()-1);
                temp = false;
                break;
            }

        }
        //cout<<str<<endl;
        if(temp) break;
		ans.push_back(str);
    }
    if(str.length()-1){
    cout<<"\nNO"<<endl;
    }
    else
    {
        cout<<"\nYES\n"<<endl;
        for(i = 0;i<ans.size() ;i++) cout<<ans[i]<<endl;
    }
    return 0;
}

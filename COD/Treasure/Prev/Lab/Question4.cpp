#include<bits/stdc++.h>

using namespace std;

int main()
{
    int a,i,j;
    string str;
    cin>>str;
    while(str.length()-1){
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
                break;
            }
            else if(str[i]=='S' && str[i+1]=='S')
            {
                for(int k=i;k<str.length()-1;k++)
                {
                    str[k+1] = str[k+2];
                }
                str = str.substr(0,str.length()-1);
                break;
            }

        }
        cout<<str<<endl;

    }
    if(str.length()-1){
    cout<<"NO"<<endl;
    }
    else
    {
        cout<<"YES"<<endl;
    }
    return 0;
}

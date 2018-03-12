#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cstdlib>
#include<vector>
using namespace std;
int main()
{

	cout << "REMOVING LEFT RECURSION\n\n";

	freopen("input2.txt", "r", stdin);

	int no_of_prod, i, j, k, l, n, m;
	scanf("%d", &no_of_prod);
	
	cout << endl;

	string pr_rules;

	char term = 'A';


	vector<pair<string, vector<string> > > v;


	//cout << "Enter production rules\n" << endl;
	
	for (i = 0; i < no_of_prod; i++) {
		cin >> pr_rules;
		string str1, c, d, temp;
		pair<string, vector<string> > vv;
		str1 = "";
		vector<string> left_vect;
		for (j = 0; j < pr_rules.length(); j++) {
			if (pr_rules[j] == '-') {
				temp = str1;
				left_vect.push_back(temp);
				str1 = "";
				j++;
			}
			else if (pr_rules[j] == '|') {
				left_vect.push_back(str1);
				str1 = "";
			}
			else {
				str1 = str1 + pr_rules[j];
			}
		}


		left_vect.push_back(str1);

		for (j = 1; j < left_vect.size(); j++) {
			if (left_vect[0][0] == left_vect[1][0]) {
				
				cout << left_vect[0][0] << "->" << left_vect[2][0] << term << endl;
				cout << term << "->";

				for (int itr = 1; itr < left_vect[1].length(); itr++) {
					cout << left_vect[1][itr];
				}

				cout << term << "|0";
				cout << endl;
				term++;
				break;
			}
			else {
				cout << pr_rules << endl;
				break;
			}
		}
	}
	cout << endl;
	return 0;
}
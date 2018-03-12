#include<iostream>  
#include<cstring>
#include<algorithm>
#include<string>
#include<iomanip>
#define MAX 100

using namespace std;

string arr[MAX][MAX];
string productns[MAX];
int p, np;

string concat(string a, string b)
{
	int i;
	string r = a;
	for (i = 0; i<b.length(); i++)
	if (r.find(b[i]) > r.length())
		r += b[i];
	return (r);
}

void deconc(string a)
{
	int i;
	p = 0;

	while (a.length())
	{
		i = a.find(" | ");
		if (i>a.length())
		{
			productns[p++] = a;
			a = "";
		}
		else
		{
			productns[p++] = a.substr(0, i);
			a = a.substr(i + 1, a.length());
		}
	}
}

int leftvalidity(string a)
{
	if (a.length() == 1 && a[0] >= 'A' && a[0] <= 'Z')
		return 1;
	return 0;
}

int rightvalidity(string a)
{
	if (a.length() == 1 && a[0] >= 'a' && a[0] <= 'z' || a[0] == '(' || a[0] == ')')
		return 1;
	if (a.length() == 2 && a[0] >= 'A' && a[0] <= 'Z' && a[1] >= 'A' && a[1] <= 'Z' || a[0] == '(' || a[0] == ')' || a[1] == '(' || a[1] == ')')
		return 1;
	return 0;
}

string search_productions(string p)
{
	int j, k;
	string r = "";
	for (j = 0; j < np; j++)
	{
		k = 1;
		while (arr[j][k] != "")
		{
			if (arr[j][k] == p)
			{
				r = concat(r, arr[j][0]);

			}

			k++;
		}
	}
	return r;
}

string combinations(string a, string b)
{
	int i, j;
	string pri = a, re = "";
	for (i = 0; i < a.length(); i++)
	for (j = 0; j < b.length(); j++)
	{
		pri = "";
		pri = pri + a[i] + b[j];

		re = re + search_productions(pri);
	}
	return re;
}

int main()
{
	int i, pt, j, l, k;
	string a, str, r, pr, start;
	int a1, a2;
	
	cout << "\n start variable" << endl;
	cin >> start;
	cout << "\n number of productions" << endl;
	cin >> np;

	for (i = 0; i < np; i++)
	{
		cin >> a;
		pt = a.find("->");
		arr[i][0] = a.substr(0, pt);
		a1 = leftvalidity(arr[i][0]);
		if (!a1)
			cout << "\nGrammar not in Chomsky Form\n";

		a = a.substr(pt + 2, a.length());
		deconc(a);

		for (j = 0; j < p; j++)
		{
			arr[i][j + 1] = productns[j];
			a2 = rightvalidity(productns[j]);
			if (!a2)
				cout << "\nGrammar not in Chomsky Form\n";

		}
	}
	string grid[MAX][MAX], st;
	if (a1 && a2) {
		cout << "\nEnter string to be checked : ";
		cin >> str;

		for (i = 0; i < str.length(); i++)
		{
			r = "";
			st = "";
			st += str[i];

			for (j = 0; j < np; j++)
			{
				k = 1;
				while (arr[j][k] != "")
				{
					if (arr[j][k] == st)
					{
						r = concat(r, arr[j][0]);
					}
					k++;
				}
			}
			grid[i][i] = r;
		}

		int ii, kk;
		for (k = 1; k < str.length(); k++)
		{
			for (j = k; j < str.length(); j++)
			{
				r = "";
				for (l = j - k; l < j; l++)
				{
					pr = combinations(grid[j - k][l], grid[l + 1][j]);
					r = concat(r, pr);
				}
				grid[j - k][j] = r;
			}
		}

		cout << "\ngrid Generated : -" << endl;

		int k1, l1;
		for (i = 0; i < str.length(); i++)
		{
			k1 = 0;
			l1 = str.length() - i - 1;
			for (j = l1; j < str.length(); j++)
				cout << setw(5) << grid[k1++][j] << " ";

			cout << endl;
		}

		int f = 0;
		for (i = 0; i < start.length(); i++)
		if (grid[0][str.length() - 1].find(start[i]) <= grid[0][str.length() - 1].length())
		{
			cout << " \nvalid String \n";
			return 0;
		}

		cout << "\ninvalid string\n";
	}
	return 0;
}
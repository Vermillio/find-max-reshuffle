#define min(a, b) a < b ? a : b
#include "FindReshuffle.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void T_Find::demo()
{
	string s1, s2;
	cout << "Enter first string: ";
	cin >> s1;
	cout << "Enter second string: ";
	cin >> s2;
	cout << FindReshuffle(s1, s2) << endl;
}

string T_Find::FindReshuffle(string s1, string s2)
{
	bool ** M = new bool*[(int)s1.length()];
	for (int i = 0; i < s1.length(); ++i)
		M[i] = new bool[(int)s2.length()];

	string s;
	string s_max;

	for (int i = 0; i < s1.length(); i++)
		for (int j = 0; j < s2.length(); j++)
			if (s1[i] == s2[j])
				M[i][j] = 1;
			else M[i][j] = 0;

	//MATRIX OUTPUT
	//for (int i = 0; i < s1.length(); i++)
	//{
	//	for (int j = 0; j < s2.length(); j++)
	//		cout << M[i][j] << " ";
	//	cout << endl;
	//}

	int sz = min(s1.length(), s2.length());

	vector<bool> used1, used2;

	while (sz > 1)
	{
		used1.resize(sz);
		used2.resize(sz);
		for (int i = 0; i <= s1.length() - sz; ++i)
			for (int j = 0; j <= s2.length() - sz; ++j)
			{
				for (int k = 0; k < sz; ++k)
				{
					used1[k] = false;
					used2[k] = false;
				}

				bool valid = true;
				for (int k = i; k < i + sz; ++k)
				{
					for (int l = j; l < j + sz; ++l)
					{
						if (M[k][l])
							if (used1[k - i] || used2[l - j])
								valid = false;
							else {
								used1[k-i] = true;
								used2[l-j] = true;
							}
							if (!valid)
								break;
					}
					if (!valid)
						break;
				}

				for (int i = 0; i < sz; ++i)
					if (!used1[i] || !used2[i])
					{
						valid = false;
						break;
					}

				if (valid)
					return string(s1.begin() + i, s1.begin() + i + sz);
			}
		--sz;
	}


	return s_max;

}

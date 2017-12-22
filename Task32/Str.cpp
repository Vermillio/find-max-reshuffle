#define MAX_LEN 100

#include "Str.h"
#include <string>
#include <list>
#include <algorithm>


using namespace std;


void T_Str::indexSort(vector<int> &index, string::iterator sbegin, string::iterator send)
{
	for (int i = 0; i < index.size(); i++)
		for (int j = 0; j < index.size(); j++)
		{
			if (i <= j && *(sbegin + index[i]) > *(sbegin + index[j]) || i >= j && *(sbegin + index[i]) < *(sbegin + index[j]))
			{
				swap(index[i], index[j]);
			}
		}
}

pair<borders, borders> T_Str::RunFindSubstr(string::iterator b1, string::iterator e1, string::iterator b2, string::iterator e2)
{
	begin_s1 = b1, end_s1 = e1, begin_s2 = b2, end_s2 = e2;

	for (int i = 0; begin_s1 + i != end_s1; i++)
	{
		pointers1.push_back(i);
		is_shared_1[i] = 0;
	}
	for (int i = 0; begin_s2 + i != end_s2; i++)
	{
		pointers2.push_back(i);
		is_shared_2[i] = 0;
	}
	indexSort(pointers1, begin_s1, end_s1);
	indexSort(pointers2, begin_s2, end_s2);
	//InitUtility();
	MarkSymbolsOccuredInBoth();
	stack1 = MakeBordersList(begin_s1, end_s1, is_shared_1);
	stack2 = MakeBordersList(begin_s2, end_s2, is_shared_2);
	

	return DoFindSubstr();
}

string T_Str::FindSubstr(string s1, string s2)
{
	pair<borders, borders> res = RunFindSubstr(s1.begin(), s1.end(), s2.begin(), s2.end());
	string substr = "";
	for (auto i = s1.begin() + res.first.l; i != s1.begin() + res.first.r; i++)
	{
		substr += *i +'\0';
	}
	return substr;
}

void T_Str::demo()
{
	string s1, s2;
	cout << "Enter first string: ";
	cin >> s1;
	cout << "Enter second string: ";
	cin >> s2;
	cout << FindSubstr(s1, s2) << endl;
}


void T_Str::MarkSymbolsOccuredInBoth()
{
	int i = 0, j = 0;
	while (i < pointers1.size() && j < pointers2.size())
	{
		if (*(begin_s1 + pointers1[i]) == *(begin_s2 + pointers2[j]))
		{
			while (i+1 < pointers1.size())
			{
				if (*(begin_s1 + pointers1[i]) != *(begin_s1 + pointers1[i + 1]))
					break;
				is_shared_1[pointers1[i]] = 1;
				i++;
			}
			is_shared_1[pointers1[i]] = 1;
			while (1+j < pointers2.size())
			{
				if (*(begin_s2 + pointers2[j]) != *(begin_s2 + pointers2[j + 1]))
					break;
				is_shared_2[pointers2[j]] = 1;
				j++;
			}
			is_shared_2[pointers2[j]] = 1;
		}
		if (i < pointers1.size() &&
			(	(j < pointers2.size() && *(begin_s1 + pointers1[i]) < *(begin_s2 + pointers2[j]))	||	j >=sizeof(pointers2)	)
			)
			++i;
		else
			++j;
	}
}

list<borders> T_Str::MakeBordersList(string::iterator begin, string::iterator end, array<bool, MAX_LEN> arr)
{
	list<borders> res;
	int cur_l, cur_r;
	for (int i = 0; begin + i != end; i++)
	{
		if (arr[i])
		{
			cur_l = i;
			while (begin + i != end && arr[i + 1] == true)
			{
				i++;
			};
			cur_r = i + 1;
			insert_byLenDesc(res, cur_l, cur_r);
		}
	}
	return res;
}

void T_Str::insert_byLenDesc(list<borders> &p, int l, int r)
{
	list<borders>::iterator it = p.begin();
	while (it != p.end() && r - l < it->getLen())
	{
		it++;
	}
	p.emplace(it, borders({ l, r }));
}


pair<borders, borders> T_Str::DoFindSubstr()
{
	if (stack1.size() == stack2.size() == 1)
	{
		if (	stack1.begin()->getLen() == stack2.begin()->getLen()	)
			return pair<borders, borders>(*stack1.begin(), *stack2.begin());
	}

	pair<borders, borders> res({ 0, 0 }, { 0, 0 }); // границы искомой подстроки в первой и второй строках
	list<borders>::iterator it1 = stack1.begin(), it2 = stack2.begin();
	//int cur_len = (*it1).getLen() + (*it2).getLen(); // ?

	/*if (it1->l == 0 && begin_s1 + it1->r == end_s1 && it2->l == 0 && begin_s2 + it2->r == end_s2)
	{
		if (Compare(it1, it2))
			return pair<borders, borders>(*it1, *it2);

	}*/



	while (it1 != stack1.end() || it2 != stack2.end())
	{
		T_Str s;
		
		//запускаем рекурсию по спискам
			res = s.RunFindSubstr(begin_s1 + it1->l, begin_s1 + it1->r, begin_s2 + it2->l, begin_s2 + it2->r);
			if ((res.first.getLen() == (*it1).getLen()) || (res.second.getLen() == (*it2).getLen()))
				return res;
			if ((++it2) != stack2.end() && it1->getLen() + (it2)->getLen() >= (++it1)->getLen() + stack2.begin()->getLen())
				it1--;
			else
				it2 = stack2.begin();
	}
}

bool T_Str::Compare(borders a, borders b)
{

	return false;
}


int borders::getLen()
{
	return r - l;
}

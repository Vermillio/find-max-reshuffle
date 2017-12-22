#ifndef STR_H
#define STR_H
#define MAX_LEN 100
#include <iostream>
#include <list>
#include <vector>
#include <utility>
#include <array>

using namespace std;

typedef struct borders
{
	int l, r;
	borders(int a, int b) : l(a), r(b) {};
	int getLen();
};

class T_Str
{
public:
	string::iterator begin_s1, end_s1, begin_s2, end_s2;
	array<bool, MAX_LEN> is_shared_1;
	array<bool, MAX_LEN> is_shared_2;
	vector<int> pointers1, pointers2;
	list<borders> stack1, stack2;

	void MarkSymbolsOccuredInBoth();
	//void InitUtility();
	void indexSort(vector<int> &index, string::iterator sbegin, string::iterator send);
	list<borders> MakeBordersList(string::iterator begin, string::iterator end, array<bool, MAX_LEN> arr);
	void insert_byLenDesc(list<borders> &p, int l, int r);
	pair<borders, borders> DoFindSubstr();

	bool Compare(borders a, borders b);
	T_Str(string::iterator a, string::iterator b, string::iterator c, string::iterator d) : begin_s1(a), end_s1(b), begin_s2(c), end_s2(d)	{};
	T_Str() {};


	pair<borders, borders> RunFindSubstr(string::iterator begin_s1, string::iterator end_s1, string::iterator begin_s2, string::iterator end_s2);
	string FindSubstr(string s1, string s2);
	void demo();
};

class FindSubstring
{
private:

	T_Str S;

public:

	friend T_Str;

	string substr;

	
};


#endif
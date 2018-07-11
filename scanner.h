#ifndef scanner_hpp
#define scanner_hpp
/*
   function ： 过滤不需要的字符并读取需要的string
*/
#include "exception.h"
#include <string>
using std::string;
class scanner
{
	string st;
	int len,l;
public:
	scanner(string &_st) { st = _st; l = 0; len = st.length(); }
	~scanner() {};
	bool isexsit(char c = ' ');
	string getstr(char c = ' ');
	string getstring();
};
inline bool scanner::isexsit(char c)
{
	while (l<len && (st[l] == ' ' || st[l] == '\t' || st[l] == c))  l++;
	if (l<len && st[l] == '\n') { l++; return false; }
	if (l >= len) return false; else return true;
}

inline string scanner::getstr(char c)
{
	string ans = "";
	while (l < len && st[l] != ' '  && st[l] != '\t' && st[l] != c && st[l] != '\n')
	{
		ans += st[l];
		l++;
	}
	return ans;
}
inline string scanner::getstring()
{
	bool flag = 0; string ans = "";
	for (int &i = l; i < len; i++)
	{
		if (flag)
		{
			if (st[i] == '\\')
			{
				i++;
				if (i >= len) throw error();
				if (st[i] == '\"' || st[i] == '\'' || st[i] == '\\' || st[i] == '\?') ans += st[i];
				if (st[i] == 'n') ans += '\n';
				if (st[i] == 't') ans += '\t';
				if (st[i] == 'r') ans += '\r';
				if (st[i] == '0') ans += '\0';
				continue;
			}
			else if (st[i] == '"') { i++; return ans; }
			else ans += st[i];
		}
		if (st[i] == '"')
		{
			flag ^= 1;
			if (flag == 0) { i++; return ans; }
		}
	}
	return ans;
}

inline int StringToInt(string &st)
{
	int flag = 1, ans = 0, i = 0;
	int len = st.length();
	if (st[i] == '-') { i++; flag = -1; }
	for (; i < len; i++)
		if ((st[i] <= '9') && (st[i] >= '0'))
		{
			ans = ans * 10 + st[i] - '0';
		}
		else throw error();
		return flag * ans;
}
#endif

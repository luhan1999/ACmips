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
int StringToInt(string &st);
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
#endif

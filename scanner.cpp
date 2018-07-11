#include "scanner.h"

string scanner::getstring()
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
int StringToInt(string &st)
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

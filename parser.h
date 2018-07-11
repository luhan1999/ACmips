#ifndef parser_H
#define parser_H
/* 
    function:用于读入所有.s文件并对其进行存储，把数据区的内容读入。
*/
#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include "Commond.h"
#include "scanner.h"
#include "CPU.h"
#include "Memory.h"
extern int heap;
//lab用来存text内的标签位置
std::map<string, int> lab;
//loc用来存data内标签对应的位置
std::map<string, int> loc;
string s1,s2,s3;
void parser(std::ifstream &fin, std::vector<Commond> &commond, CPU &cpu, Memory &memory)
{
	int line = 0;
	int flag = 0; // flag == 0表示在data区，flag == 1 表示在text区 
	Commond tmp1; commond.push_back(tmp1);
	std::string str;
	//#注释注意要特判
	while (std::getline(fin, str))   //TODO 不知道结束怎么判断 
	{
		s1 = ""; s2 = ""; s3 = "";
		if (str == "") continue;
		Commond tmp;
		line++; 
		scanner st(str);
		if (st.isexsit('\n')) str = st.getstr('\n');
		else  {
			commond.push_back(tmp);
			continue;
		}
		if (str == ".data")
		{
			flag = 1;
			commond.push_back(tmp);
			continue;
		}
		if (str == ".text")
		{
			flag = 0;
			commond.push_back(tmp);
			continue;
		}
		//处理label
		if (str[str.length() - 1] == ':')
		{
			if (flag == 0)
			{
				str.erase(str.end() - 1);
				lab[str] = line;
				commond.push_back(tmp);
				continue;
			}
			else
			{
				str.erase(str.end() - 1);
				loc[str] = heap;
				commond.push_back(tmp);
				continue;
			}
		}
		if (str == ".align")
		{
			if (st.isexsit(' ')) s1 = st.getstr(' ');
			int n = StringToInt(s1);
			int Mod = 1 << n;
			while (heap % Mod != 0) heap++;  //$30 == fp
			commond.push_back(tmp);
			continue;
		}
		if (str == ".ascii")
		{
			s1 = st.getstring();
			memory.storestring(heap, s1);
			commond.push_back(tmp);
			continue;
		}

		if (str == ".asciiz")
		{
			s1 = st.getstring(); s1 = s1 + '\0';
			memory.storestring(heap, s1);
			commond.push_back(tmp);
			continue;
		}
		if (str == ".byte")
		{
			while (st.isexsit(','))
			{
				s1 = st.getstr(',');
				int x = StringToInt(s1);
				memory.store(heap, x, 1);
				heap ++;
			}
			commond.push_back(tmp);
			continue;
		}
		if (str == ".half")
		{
			while (st.isexsit(','))
			{
				s1 = st.getstr(',');
				int x = StringToInt(s1);
				memory.store(heap, x, 2);
				heap += 2;
			}
			commond.push_back(tmp);
			continue;
		}
		if (str == ".word")
		{
			while (st.isexsit(','))
			{
				s1 = st.getstr(',');
				int x = StringToInt(s1);
				memory.store(heap, x, 4);
				heap += 4;
			}
			commond.push_back(tmp);
			continue;
		}

		if (str == ".space")
		{
			if (st.isexsit(' ')) s1 = st.getstr('\n');
			int n = StringToInt(s1);
			heap += n;
			commond.push_back(tmp);
			continue;
		}

		tmp.opt = tranc[str];
		if (tmp.opt <= sw && tmp.opt >= la)
		{
			//如果是标签的话，那s3 = "";
			if (st.isexsit(',')) s1 = st.getstr(',');
			if (st.isexsit(',')) s2 = st.getstr('(');
			if (st.isexsit('(')) s3 = st.getstr(')');
			//f == 1表示是标签 ,f == 0 表示不是标签
			if (s3 == "")
			{
				tmp.f = 1; tmp.x1 = id[s1]; tmp.s = s2;
			}
			else
			{
				tmp.f = 0; tmp.x1 = id[s1]; tmp.x2 = StringToInt(s2); tmp.x3 = id[s3];
			}
		}
		else
		{
			if (st.isexsit(',')) s1 = st.getstr(',');
			if (st.isexsit(',')) s2 = st.getstr(',');
			if (st.isexsit(',')) s3 = st.getstr(',');

			if (s1 == "") {}
			else if (s2 == "")
            {  
				//f == 1 表示是标签 f == 0表示是寄存器
				if (tmp.opt == b || tmp.opt == j || tmp.opt == jal)
				{
					tmp.f = 1; tmp.s = s1;
				}
				else
				{
					tmp.f = 0; tmp.x1 = id[s1];
				}
			} 
			else if (s3 == "")
			{
				tmp.size = 2; tmp.x1 = id[s1];
				if (tmp.opt >= beqz && tmp.opt <= bltz)
				{
					tmp.f = 1; tmp.s = s2;
				}
				else
				{
					//0表示是寄存器 1表示是立即数
					if (s2[0] == '$')
					{
						tmp.f = 0; tmp.x2 = id[s2];
					}
					else {
						tmp.f = 1; tmp.x2 = StringToInt(s2);
					}
				}
			}
			else
			{
				tmp.size = 3;
				if (tmp.opt >= beq && tmp.opt <= blt)
				{
					tmp.x1 = id[s1];
					//0表示是寄存器 1表示是立即数
					if (s2[0] == '$')
					{
						tmp.f = 0;
						tmp.x2 = id[s2];
						tmp.s = s3;
					}
					else
					{
						tmp.f = 1;
						tmp.x2 = StringToInt(s2);
						tmp.s = s3;
					}
				}
				else {
					tmp.x1 = id[s1]; tmp.x2 = id[s2];
					if (s3[0] == '$')
					{
						tmp.f = 0; tmp.x3 = id[s3];
					}
					else {
						tmp.f = 1; tmp.x3 = StringToInt(s3);
					}
				}
				
			}
		}
		commond.push_back(tmp);
	}
	//for (int i = 1; i <= line; i++)
		//std::cout << commond[i].opt << " " << commond[i].s1 << " " << commond[i].s2 << " " << commond[i].s3 << std::endl;
}
#endif


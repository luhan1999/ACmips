#ifndef Memory_H
#define Memory_H
/*
   function:����ģ���ڴ�
*/
#include<cstring>
#include<string>
using std::string;
class Memory
{
public:
	char *R;
	Memory();
	~Memory();
	int load(int star, int len);
	void store(int star, int x, int len);
	void storestring(int &star, string &st);

};
#endif 


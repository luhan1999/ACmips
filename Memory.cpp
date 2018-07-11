#include "Memory.h"
Memory::Memory()
{
	R = new char[4 * 1024 * 1024];
	for (int i = 0; i < 4 * 1024 * 1024; i++) R[i] = 0;
}
Memory::~Memory()
{
	delete[] R;
}
//& 0xff ��֤����32λ��ȷ
//��ֵֻ�ǽ��ж�����λ�ĸ��ƣ�������ô���ͣ���Ҫʲô���ͣ�����ʲô����
int Memory::load(int star, int len)
{
	int ans = 0;
	for (int i = 0; i < len; i++)
		ans |= (R[star + i] & 0xff) << (8 * i);
	return ans;
}
void Memory::store(int star, int x, int len)
{
	for (int i = 0; i < len; i++)
		R[star + i] = (x >> (8 * i)) & 0xff;
}
void Memory::storestring(int &star, string &st)
{
	for (int i = 0; i < st.length(); i++)
		R[star + i] = st[i];
	star = star + st.length();
}

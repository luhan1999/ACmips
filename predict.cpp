#include "predict.h"
predict::predict() :state(0) {
	for (int i = 0; i < n; i++) p[i] = 0;
}
bool predict::jump()
{
	if (p[state] <= 1) return false;
	return true;
}
void predict::upload(int t)
{
	if (t == 0)
	{
		p[state]--; if (p[state] < 0) p[state] = 0;
	}
	else
	{
		p[state]++; if (p[state] > 3) p[state] = 3;
	}
	state = ((state << 1) & ((1 << n) - 1)) + t;
}
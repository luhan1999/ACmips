#ifndef prelabel_H
#define prelabel_H
#include <iostream>
#include <algorithm>
#include <cstdio>
#include "Commond.h"
#include "CPU.h"
#include "Memory.h"
#include "parser.h"
#include <cstdio>
#include <vector>
#include <string>
void prefunction(std::vector<Commond> &commond)
{
	for (int i = 1; i < commond.size(); i++)
	{
		Commond *t = &commond[i];
		if (t->opt >= beq && t->opt <= blt)
		{
			t->x3 = lab[t->s];
			continue;
		}
		if (t->opt >= beqz && t->opt <= bltz)
		{
			t->x2 = lab[t->s];
			continue;
		}
		if (t->opt == b || t->opt == j || t->opt ==jal) {
			t->x1 = lab[t->s];
			continue;
		}


		if (t->f == 1)
		  if (t->opt >= la && t->opt <= sw)
		{
			  t->x2 = loc[t->s];
		}
	}
}
#endif 

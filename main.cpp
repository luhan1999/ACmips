#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
using std::vector;
using std::string;
#include "Memory.h"
#include "parser.h"
#include "Commond.h"
#include "inti.h"
#include "CPU.h"
//#include "exec.h"
#include "prelabel.h"
#include "process.h"
vector<Commond>commond;
int heap = 0;  //用于分配内存
int ans = 0;  //用于return
std::ifstream fin;
int main(int argc, char *argv[])
{
	inti();
	Memory memory;
	CPU cpu;
	fin.open(argv[1]);
	parser(fin,commond,cpu,memory);
	fin.close();
	prefunction(commond);
	//exec(commond, cpu, memory,ans);
	process(commond, cpu, memory,ans);
	return ans;
}

#ifndef process_H
#define process_H
/*
   五级流水实现
*/
#include "Commond.h"
#include "CPU.h"
#include "Memory.h"
#include "parser.h"
#include "predict.h"
#include <cstdio>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <cstdio>

void prerecord();

int getdata3(CPU &cpu, Commond *t);

int getdata2(CPU &cpu, Commond *t);

//fir 
void IF(std::vector<Commond> &commond, CPU &cpu, Memory &memory);

//num1 num2 num3 numb nums

void ID(std::vector<Commond> &commond, CPU &cpu, Memory &memory);

void EX(std::vector<Commond> &commond, CPU &cpu, Memory &memory);

void MA(std::vector<Commond> &commond, CPU &cpu, Memory &memory);

void WB(std::vector<Commond> &commond, CPU &cpu, Memory &memory, int &ans);

void process(std::vector<Commond> &commond, CPU &cpu, Memory &memory, int &ans);
#endif 

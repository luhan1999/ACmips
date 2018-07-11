#ifndef parser_H
#define parser_H
/* 
    function:用于读入所有.s文件并对其进行存储，把数据区的内容读入。
*/
#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <map>
#include "Commond.h"
#include "scanner.h"
#include "CPU.h"
#include "Memory.h"
extern int heap;
//lab用来存text内的标签位置
extern std::map<string, int> lab;
//loc用来存data内标签对应的位置
extern std::map<string, int> loc;

void parser(std::ifstream &fin, std::vector<Commond> &commond, CPU &cpu, Memory &memory);
#endif


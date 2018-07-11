#ifndef parser_H
#define parser_H
/* 
    function:���ڶ�������.s�ļ���������д洢���������������ݶ��롣
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
//lab������text�ڵı�ǩλ��
extern std::map<string, int> lab;
//loc������data�ڱ�ǩ��Ӧ��λ��
extern std::map<string, int> loc;

void parser(std::ifstream &fin, std::vector<Commond> &commond, CPU &cpu, Memory &memory);
#endif


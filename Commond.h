
#ifndef Commond_H
#define Commond_H
#include <string>
#include <map>
using std::string;
using std::map;


enum opttype
{
	add, addu, addiu, sub, subu, mul, mulu, _div, divu, //����mul�������������ʽ
	_xor, xoru, neg, negu, rem, remu, li,
	seq, sge, sgt, sle, slt, sne,
	b, beq, bne, bge, ble, bgt, blt, beqz, bnez, blez, bgez, bgtz, bltz, j, jr, jal, jalr,
	la, lb, lh, lw,
	sb, sh, sw,
	move, mfhi, mflo,
	nop, syscall
};
class Commond
{
public:
	opttype opt; string s;  int x1; int x2; int x3;
	int f; int size; int p_pre;
	Commond() :opt(nop), s(""), f(0), p_pre(-1) {}
};

//id������¼�Ĵ���ָ���λ��
extern map<string, int> id;
extern map <string, opttype> tranc;
void StringToOpt();


#endif
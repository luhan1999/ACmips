
#ifndef Commond_H
#define Commond_H
#include <string>
#include <map>
using std::string;
using std::map;

enum opttype
{
	add, addu, addiu, sub, subu, mul, mulu, _div, divu, //考虑mul里面包含俩种形式
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

map <string, opttype> tranc;
void StringToOpt()
{
	tranc["add"] = add;
	tranc["addu"] = addu;
	tranc["addiu"] = addiu;
	tranc["sub"] = sub;
	tranc["subu"] = subu;
	tranc["mul"] = mul;
	tranc["mulu"] = mulu;
	tranc["div"] = _div;
	tranc["divu"] = divu;
	tranc["xor"] = _xor;
	tranc["xoru"] = xoru;
	tranc["neg"] = neg;
	tranc["negu"] = negu;
	tranc["rem"] = rem;
	tranc["remu"] = remu;
	tranc["li"] = li;
	tranc["seq"] = seq;
	tranc["sge"] = sge;
	tranc["sgt"] = sgt;
	tranc["sle"] = sle;
	tranc["slt"] = slt;
	tranc["sne"] = sne;
	tranc["b"] = b;
	tranc["beq"] = beq;
	tranc["bne"] = bne;
	tranc["bge"] = bge;
	tranc["ble"] = ble;
	tranc["bgt"] = bgt;
	tranc["blt"] = blt;
	tranc["beqz"] = beqz;
	tranc["bnez"] = bnez;
	tranc["blez"] = blez;
	tranc["bgez"] = bgez;
	tranc["bgtz"] = bgtz;
	tranc["bltz"] = bltz;
	tranc["j"] = j;
	tranc["jr"] = jr;
	tranc["jal"] = jal;
	tranc["jalr"] = jalr;
	tranc["la"] = la;
	tranc["lb"] = lb;
	tranc["lh"] = lh;
	tranc["lw"] = lw;
	tranc["sb"] = sb;
	tranc["sh"] = sh;
	tranc["sw"] = sw;
	tranc["move"] = move;
	tranc["mfhi"] = mfhi;
	tranc["mflo"] = mflo;
	tranc["nop"] = nop;
	tranc["syscall"] = syscall;
}


#endif
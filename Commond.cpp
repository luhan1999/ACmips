#include "Commond.h"

map <string, opttype> tranc;

map<string, int> id;
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


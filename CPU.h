#ifndef CPU_H
#define CPU_H
/*
   function:模拟CPU里面寄存器的操作
*/

#include "Commond.h"
#include <map>
#include <string>
using std::map;
using std::string;

#define maxn (4 * 1024 * 1024)

class CPU {
public:
	int p[35];
	CPU() {
		for (int i = 0; i <= 34; i++) p[i] = 0;
		p[id["$sp"]] = maxn;
	}
};

inline void id_inti()
{
	id["$0"] = id["$zero"] = 0;
	id["$1"] = id["$at"] = 1;
	id["$2"] = id["$v0"] = 2;
	id["$3"] = id["$v1"] = 3;
	id["$4"] = id["$a0"] = 4;
	id["$5"] = id["$a1"] = 5;
	id["$6"] = id["$a2"] = 6;
	id["$7"] = id["$a3"] = 7;
	id["$8"] = id["$t0"] = 8;
	id["$9"] = id["$t1"] = 9;
	id["$10"] = id["$t2"] = 10;
	id["$11"] = id["$t3"] = 11;
	id["$12"] = id["$t4"] = 12;
	id["$13"] = id["$t5"] = 13;
	id["$14"] = id["$t6"] = 14;
	id["$15"] = id["$t7"] = 15;
	id["$16"] = id["$s0"] = 16;
	id["$17"] = id["$s1"] = 17;
	id["$18"] = id["$s2"] = 18;
	id["$19"] = id["$s3"] = 19;
	id["$20"] = id["$s4"] = 20;
	id["$21"] = id["$s5"] = 21;
	id["$22"] = id["$s6"] = 22;
	id["$23"] = id["$s7"] = 23;
	id["$24"] = id["$t8"] = 24;
	id["$25"] = id["$t9"] = 25;
	id["$26"] = id["$k0"] = 26;
	id["$27"] = id["$k1"] = 27;
	id["$28"] = id["$gp"] = 28;
	id["$29"] = id["$sp"] = 29;  //栈指针
	id["$30"] = id["$fp"] = 30;  //堆指针
	id["$31"] = id["$ra"] = 31;  //返回address
	id["$pc"] = 32;
	id["$hi"] = 33;
	id["$lo"] = 34;
}

#endif 

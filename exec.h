#ifndef exec_H
#define exec_H
/*
   function: 暴力顺序执行大模拟
*/
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
/*
inline int getdata3(CPU &cpu,Commond *t)
{
	if (t->f == 0) return cpu.p[t->x3]; 
	else return t->x3;
}
inline int getdata2(CPU &cpu, Commond *t)
{
	if (t->f == 0) return cpu.p[t->x2];
	else return t->x2;
} 
void exec(std::vector<Commond> &commond, CPU &cpu, Memory &memory,int &flag)
{
	int line = lab["main"];
	bool boo = 1;  int cnt = 0;
	while (boo)
	{
		line++; 
		cnt++; std::cout << cnt;
		std::cout << s[line] << std::endl;
		Commond *t = &commond[line];
		switch (t->opt)
		{
		//4.1算术与逻辑指令
		case add:case addu:case addiu:
		{  cpu.p[t->x1] = cpu.p[t->x2] + getdata3(cpu,t); break; }
		case sub:case subu:
		{  cpu.p[t->x1] = cpu.p[t->x2] - getdata3(cpu,t); break; }

		//
		case mul:
		{
			if (t->size == 2)
			{
				long long x = cpu.p[t->x1];
				long long y = getdata2(cpu, t);
				x = x * y;
				cpu.p[34] = x;
				cpu.p[33] = x >> 32;
			}
			else
			{
				int x = cpu.p[t->x2];
				int y = getdata3(cpu,t);
				cpu.p[t->x1] = x * y;
			}
			break;
		}
		case mulu:
		{
			if (t->size == 2)
			{
				unsigned long long x = cpu.p[t->x1];
				unsigned long long y = getdata2(cpu, t);
				x = x * y;
				cpu.p[34] = x;
				cpu.p[33] = x >> 32;
			}
			else
			{
				unsigned int x = cpu.p[t->x2];
				unsigned int y = getdata3(cpu, t);
				cpu.p[t->x1] = x * y;
			}
			break;
		}

		case _div:
		{
			if (t->size == 2)
			{
				int x = cpu.p[t->x1];
				int y = getdata2(cpu, t);
				cpu.p[34] = x / y;
				cpu.p[33] = x % y;     //hi
			}
			else
			{
				int x = cpu.p[t->x2];
				int y = getdata3(cpu, t);
				cpu.p[t->x1] = x / y;
			}
			break;
		}

		case divu:
		{
			if (t->size == 2)
			{
				unsigned int x = cpu.p[t->x1];
				unsigned int y = getdata2(cpu, t);
				cpu.p[34] = x / y;
				cpu.p[33] = x % y;     //hi
			}
			else
			{
				unsigned int x = cpu.p[t->x2];
				unsigned int y = getdata3(cpu, t);
				cpu.p[t->x1] = x / y;
			}
			break;
		}

		case _xor: case xoru:
		{   cpu.p[t->x1] = cpu.p[t->x2] xor getdata3(cpu,t); break; }

		case neg:
		{  	cpu.p[t->x1] = -getdata2(cpu,t); break;  }

		//是不是这么取反？
		case negu:
		{   cpu.p[t->x1] = ~getdata2(cpu,t); break; }
		
		case rem:
		{
			int x = cpu.p[t->x2];
			int y = getdata3(cpu, t);
			cpu.p[t->x1] = x % y;
			break;
		}

		case remu:
		{
			unsigned int x = cpu.p[t->x2];
			unsigned int y = getdata3(cpu, t);
			cpu.p[t->x1] = x % y;
			break;
		}

		//4.2常数操作指令
		case li: { cpu.p[t->x1] = t->x2; break; }

				 //比较的时候需不需要考虑类型
		 //4.3比较指令
		case seq: { cpu.p[t->x1] = (cpu.p[t->x2] == getdata3(cpu,t)); break; }
		case sge: { cpu.p[t->x1] = (cpu.p[t->x2] >= getdata3(cpu, t)); break; }
		case sgt: { cpu.p[t->x1] = (cpu.p[t->x2] > getdata3(cpu, t)); break; }
		case sle: { cpu.p[t->x1] = (cpu.p[t->x2] <= getdata3(cpu, t)); break; }
		case slt: { cpu.p[t->x1] = (cpu.p[t->x2] < getdata3(cpu, t)); break; }
		case sne: { cpu.p[t->x1] = (cpu.p[t->x2] != getdata3(cpu, t)); break; }


				  //4.4分支与跳转
		case b: { line = t->x1; break; }
		case beq: { if (cpu.p[t->x1] == getdata2(cpu, t)) line = t->x3; break; }
		case bne: { if (cpu.p[t->x1] != getdata2(cpu, t)) line = t->x3; break; }
		case bge: { if (cpu.p[t->x1] >= getdata2(cpu, t)) line = t->x3; break; }
		case ble: { if (cpu.p[t->x1] <= getdata2(cpu, t)) line = t->x3; break; }
		case bgt: { if (cpu.p[t->x1] > getdata2(cpu, t)) line = t->x3; break; }
		case blt: { if (cpu.p[t->x1] < getdata2(cpu, t)) line = t->x3; break; }
		case beqz: { if (cpu.p[t->x1] == 0) line = t->x2; break; }
		case bnez: { if (cpu.p[t->x1] != 0) line = t->x2; break; }
		case blez: { if (cpu.p[t->x1] <= 0) line = t->x2; break; }
		case bgez: { if (cpu.p[t->x1] >= 0) line = t->x2; break; }
		case bgtz: { if (cpu.p[t->x1] > 0) line = t->x2; break; }
		case bltz: { if (cpu.p[t->x1] < 0) line = t->x2; break; }

		case j: { line = t->x1; break; }
		case jr: { line = cpu.p[t->x1]; break; }
		case jal: { cpu.p[31] = line; line = t->x1; break; }
		case jalr: { cpu.p[31] = line; line = cpu.p[t->x1]; break; }
      
				   //4.5 load指令
		case la: { cpu.p[t->x1] = t->x2; break; }
		case lb:
		{
			int tmp;
			if (t->f == 0) tmp = cpu.p[t->x3] + t->x2;
			else tmp = t->x2;
			cpu.p[t->x1] = memory.load(tmp, 1);
			break;
		}
		case lh:
		{
			int tmp;
			if (t->f == 0) tmp = cpu.p[t->x3] + t->x2;
			else tmp = t->x2;
			cpu.p[t->x1] = memory.load(tmp, 2);
			break;
		}
		case lw:
		{
			int tmp;
			if (t->f == 0) tmp = cpu.p[t->x3] + t->x2;
			else tmp = t->x2;
			cpu.p[t->x1] = memory.load(tmp, 4);
			break;
		}

		//4.6 store指令
		case sb:
		{
			int tmp;
			if (t->f == 0) tmp = cpu.p[t->x3] + t->x2;
			else tmp = t->x2;
			memory.store(tmp, cpu.p[t->x1], 1);
			break;
		}
		case sh:
		{
			int tmp;
			if (t->f == 0) tmp = cpu.p[t->x3] + t->x2;
			else tmp = t->x2;
			memory.store(tmp, cpu.p[t->x1], 2);
			break;
		}
		case sw:
		{
			int tmp;
			if (t->f == 0) tmp = cpu.p[t->x3] + t->x2;
			else tmp = t->x2;
			memory.store(tmp, cpu.p[t->x1], 4);
			break;
		}

		//数据移动指令
		case move:
		{
			cpu.p[t->x1] = cpu.p[t->x2];
			break;
		}
		case mfhi:
		{
			cpu.p[t->x1] = cpu.p[33];
			break;
		}
		case mflo:
		{
			cpu.p[t->x1] = cpu.p[34];
			break;
		}
		case nop: { break; }
		case syscall:
		{
			switch (cpu.p[2])
			{
			case 1: {std::cout << cpu.p[4]; break; }
			case 4:
			{
				int l = cpu.p[4];
				while (memory.R[l] != '\0')
				{
					std::cout << memory.R[l];
					l++;
					
				}
				//std::cout << '\0'<< std::endl;
				break;
			}
			case 5:
			{
				std::cin >> cpu.p[2];
				break;
			}
			case 8:
			{
				string st; std::cin >> st;
				int len = st.length(); len = std::min(len, cpu.p[5] + 1);
				//是不是这么写的？
				//memcpy(&memory.R[cpu.p[4]], &st, len);
				for (int i = 0; i < len; i++)
					memory.R[cpu.p[4] + i] = st[i];
				memory.R[cpu.p[4] + len] = '\0';
				break;
			}
			case 9:
			{
				cpu.p[2] = heap;
				heap += cpu.p[4];
				break;
			}
			case 10:
			{
				boo = 0; flag = 0;
				break;
			}
			case 17:
			{
				boo = 0; flag = cpu.p[4];
				break;
			}
			}
		}
		}
		//std::cout << "display" << std::endl;
		for (int i = 1; i <= 34; i++)
	      std::cout << i << ": " << cpu.p[i] << " "; 
		std::cout << heap;
		std::cout << std::endl;
		//if (cnt == 594) //3155 
		//{
		//	cnt++; cnt--; std::cin >> cnt;
		//}
		//if (cnt > 2000) std::cin >> x;
	}
} */
#endif 

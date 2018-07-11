#ifndef process_H
#define process_H
/*
   五级流水实现
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
#include "predict.h"

int boo;     //判断代码是否结束
int fir;                                                                                 //IF
int sec,num1, num2, num3, numb, nums;                                                    //ID
int thd, result; int resultlo; int resulthi; int pos; int op; int l; int r; int size3;   //EX
int four; int res; int rl;int rh; int place; int o;int v0; int a0; int b5 = 0; int size4;//MA

vector<predict>pre;
int register_lock[35];
int jump_opt;                
bool isnext;
bool room_lock;            
struct typedata {
	int currentline;                       //表示当前第几行
	int num[3]; int isRsrc[3];             //存储数据，以及是否是寄存器的标号
	int result, rl, rh;                    //存储计算结果以及lo和hi的结果
	int op;                                //表示比较结果，1为true，0为false
	int size;                              //表示数据的size等一些内容
}data[6];
int flag[6];                               //判断某个阶段是否被处理
void prerecord()
{
	for (int i = 1; i <= 5; i++)
	{
		data[i].currentline = 0;
		data[i].num[0] = 0; data[i].num[1] = 0; data[i].num[2] = 0;
		data[i].isRsrc[0] = 0; data[i].isRsrc[1] = 0; data[i].isRsrc[2] = 0;
		data[i].result = 0;  data[i].rl = 0; data[i].rh = 0;
		data[i].op = 0; data[i].size = 0;
		flag[i] = 0;
    }
	memset(register_lock, 0, sizeof(register_lock));
	jump_opt = 0;
	room_lock = 0;
}

inline int getdata3(CPU &cpu, Commond *t)
{
	if (t->f == 0)
	{   
		if (register_lock[t->x3]) isnext = 0;
		return cpu.p[t->x3];
	}
	else return t->x3;
}
inline int getdata2(CPU &cpu, Commond *t)
{
	if (t->f == 0)
	{
		if (register_lock[t->x2]) isnext = 0;
		return cpu.p[t->x2];
	}
	else return t->x2;
}

//fir 
void IF(std::vector<Commond> &commond, CPU &cpu, Memory &memory)
{
	if (flag[1] != 0) return;
	cpu.p[32]++; fir = cpu.p[32];
	flag[1] = 1;
}

//num1 num2 num3 numb nums

void ID(std::vector<Commond> &commond, CPU &cpu, Memory &memory)
{
	if (flag[1] == 0 || flag[2] == 1) return;

	Commond *t = &commond[fir];
	sec = fir;
	isnext = 1;

	switch (t->opt)
	{
		//4.1
		case add: case addu:case addiu: case sub:case subu: case _xor: case xoru:
		case rem: case remu:
		{ 
			
			num1 = t->x1;   
			num2 = cpu.p[t->x2];     if (register_lock[t->x2]) isnext = 0;
			num3 = getdata3(cpu,t);  
			if (isnext == 1) register_lock[num1]++;
		            	else return;
			break; 
	    }

		case mul: case mulu: case _div: case divu:
		{
			if (t->size == 2) 
			  { 
				 num1 = cpu.p[t->x1];  if (register_lock[t->x1]) isnext = 0;
				 num2 = getdata2(cpu, t);
				 if (isnext == 1)
				 {
					 register_lock[33]++;
					 register_lock[34]++;
				 }
				 else return;
		      }
			else 
			  { 
				num1 = t->x1; 
				num2 = cpu.p[t->x2];   if (register_lock[t->x2]) isnext = 0;
				num3 = getdata3(cpu,t);
				if (isnext == 1) register_lock[num1]++;
				else return;
			  }
			nums = t->size;
			break;
		}

		case neg: case negu:
		{  	
			num1 = t->x1;  
			num2 = getdata2(cpu,t); 
			if (isnext == 1) register_lock[num1]++;
			else return;
			break;  
		}

		case li: 
		{ 
			num1 = t->x1; 
			num2 = t->x2; 
			if (isnext == 1) register_lock[num1]++;
			else return;
			break; 
	    }

		//4.3
		case seq: case sge: case sgt: case sle: case slt: case sne:
		  { 
			num1 = t->x1; 
			num2 = cpu.p[t->x2];  if (register_lock[t->x2]) isnext = 0;
			num3 = getdata3(cpu,t); 
			if (isnext == 1) register_lock[num1]++;
			else return;
			break; 
		   }

		//4.4
		case b: 
		  { 
			num1 = t->x1; 
			cpu.p[32] = num1;
			break; 
		  }
		case beq: case bne: case bge: case ble: case bgt: case blt: 
		  { 
			num1 = cpu.p[t->x1];  if (register_lock[t->x1]) isnext = 0;
			num2 = getdata2(cpu, t); 
			num3 = t->x3;  
			if (isnext == 0)  return;

			if (t->p_pre == -1) {
				predict tmp;
				pre.push_back(tmp); 
				t->p_pre = pre.size() - 1;
			}

			if (pre[t->p_pre].jump()) 
			{ 
			   jump_opt = 1;
			   cpu.p[32] = num3;
			} 
			else
			{
			   jump_opt = 0;
			}

			break; 
		  }
    
		case beqz: case bnez: case blez: case bgez: case bgtz:  case bltz: 
		  { 
			 num1 = cpu.p[t->x1]; if (register_lock[t->x1]) isnext = 0;
			 num2 = t->x2; 

			 if (isnext == 0) return;

			 if (t->p_pre == -1) {
				 predict tmp;
				 pre.push_back(tmp);
				 t->p_pre = pre.size() - 1;
			 }

			 if (pre[t->p_pre].jump())
			 {
				 jump_opt = 1;
				 cpu.p[32] = num2;
			 }
			 else
			 {
				 jump_opt = 0;
			 }

			 break; 
		  }

		case j: case jal: 
		  {  
			 num1 = t->x1; 
			 cpu.p[32] = num1;
			 break; 
	      }
		case jr: case jalr:
		  { 
			 num1 = cpu.p[t->x1];
			 if (register_lock[t->x1] == 0) cpu.p[32] = num1;
			 else return;
			 break; 
		   }
      
		//4.5 
		case la: 
		   { 
			  num1 = t->x1;  
			  num2 = t->x2; 
			  register_lock[t->x1]++;
			  break; 
		   }
		case lb: case lh: case lw: case sb: case sh: case sw:
		{ 
		   if (room_lock == 1) return;
		   numb = t->f; num1 = t->x1; num2 = t->x2; 
		   if (t->f == 0)
		     {
			   num3 = cpu.p[t->x3];
			   if (register_lock[t->x3]) return;
		      }
		   room_lock = 1;
		   register_lock[t->x1]++;
		   break; 
		}


		case move:
		{	
		   num1 = t->x1;
		   num2 = cpu.p[t->x2]; 
		   if (register_lock[t->x2]) return;
		   register_lock[t->x1]++;
		   break;
		}
		case mfhi:
		{ 
		   num1 = t->x1; 
		   num2 = cpu.p[33];  
		   if (register_lock[33]) return;
		   register_lock[t->x1]++;	  
		   break;
		}
		case mflo:
		{
			num1 = t->x1; 
			num2 = cpu.p[34]; 
			if (register_lock[34]) return;
			register_lock[t->x1]++;
			break;
		}
		case nop: { break; }

		case syscall:
		{
			num1 = cpu.p[2]; num2 = cpu.p[4]; num3 = cpu.p[5];
			if (register_lock[2]) return;
			switch (num1)
			{
			case 1: case 4: 
			{
				if (register_lock[4]) return;
				break;
			}
			case 5:
			{
				register_lock[2] ++;
				break;
			}
			case 8: 
			  {
				if (register_lock[4] || register_lock[5] ) return;
				if (room_lock == 1) return;
				room_lock = 1;
				break;
			  }
			case 9:
			  {
				if (register_lock[4]) return;
				if (room_lock == 1) return;
				room_lock = 1;
				register_lock[2]++;
				break;
			   } 
			case 17:
			  {
				if (register_lock[4]) return;
				break;
			  }
			}
		}
	}
	flag[1] = 0; flag[2] = 1;
}

void EX(std::vector<Commond> &commond, CPU &cpu, Memory &memory)
{
	op = 0;
	bool isbjump = 0;
	if (flag[2] == 0 || flag[3] == 1) return;
	Commond *t = &commond[sec];
	thd = sec;
	switch (t->opt)
	{
		//4.1
	   case add:case addu:case addiu:
	   {  pos = num1;  result = num2 + num3; break; }
	   case sub:case subu:
	   {  pos = num1;  result = num2 - num3; break; }
	   case mul:
	   {
		if (nums == 2)
		{
			long long x = (long long)num1 * (long long)num2;
			resultlo = x;
			resulthi = x >> 32;
		}
		else
		{
			pos = num1; result = num2 * num3;
		}
		size3 = nums;
		break;
	   }
	  case mulu:
	   {
		  if (nums == 2)
		  {
			unsigned long long x = (unsigned long long)num1 * (unsigned long long)num2;
			resultlo = x;
			resulthi = x >> 32;
		  }
		  else
		  {
			pos = num1;
			result = (unsigned int)num2 * (unsigned int)num3;
		  }
		  size3 = nums;
		  break;
	   }

	   case _div:
	   {
         if (nums == 2)
		  {
			resultlo = num1 / num2;
			resulthi = num1 % num2;     //hi
		  }
		 else
		 {
			pos = num1;
			result = num2 / num3;
		 }
		 size3 = nums;
		 break;
	   }

	   case divu:
	   {
		  if (nums == 2)
		  {
			resultlo = (unsigned int)num1 / (unsigned int)num2;
			resulthi = (unsigned int)num1 % (unsigned int)num2;     //hi
		  }
		  else
		  {
			pos = num1;
			result = (unsigned int)num2 / (unsigned int)num3;
		  }
		  size3 = nums;
		  break;
	   }

	   case _xor: case xoru:
	   {   pos = num1; result = num2 xor num3; break; }

	   case neg:
	   {   pos = num1; result = -num2; break;  }
       case negu:
	   {   pos = num1; result = ~num2; break; }
       case rem:
	   {
		   pos = num1;
		   result = num2 % num3;
		   break;
	   }
	   case remu:
	   {
		  pos = num1; 
		  result = (unsigned int)num2 % (unsigned int)num3;
		  break;
	   }

	//4.2常数操作指令
	   case li:  { pos = num1; result = num2; break; }
    //4.3比较指令
	   case seq: { pos = num1; result = (num2 == num3); break; }
	   case sge: { pos = num1; result = (num2 >= num3); break; }
	   case sgt: { pos = num1; result = (num2 > num3); break; }
	   case sle: { pos = num1; result = (num2 <= num3); break; }
	   case slt: { pos = num1; result = (num2 < num3); break; }
	   case sne: { pos = num1; result = (num2 != num3); break; }


	//4.4分支与跳转
	   case b: {  break; }
	   case beq: { op = (num1 == num2); isbjump = 1;  pos = num3; break; }
	   case bne: { op = (num1 != num2); isbjump = 1; pos = num3; break; }
	   case bge: { op = (num1 >= num2); isbjump = 1; pos = num3; break; }
	   case ble: { op = (num1 <= num2); isbjump = 1;  pos = num3; break; }
	   case bgt: { op = (num1 > num2);  isbjump = 1;  pos = num3; break; }
	   case blt: { op = (num1 < num2);  isbjump = 1;  pos = num3; break; }
	   case beqz: { op = (num1 == 0); isbjump = 1;   pos = num2; break; }
	   case bnez: { op = (num1 != 0); isbjump = 1;   pos = num2; break; }
	   case blez: { op = (num1 <= 0); isbjump = 1;   pos = num2; break; }
	   case bgez: { op = (num1 >= 0); isbjump = 1;   pos = num2; break; }
	   case bgtz: { op = (num1 > 0);  isbjump = 1;  pos = num2; break; }
	   case bltz: { op = (num1 < 0);  isbjump = 1;  pos = num2; break; }

	   case j: case jr: case jal: case jalr: { op = 1; pos = num1; break; }


	//4.5 load指令
   	   case la: { pos = num1; result = num2; break; }
	   case lb: case lh: case lw: case sb: case sh: case sw:
	   {
		 pos = num1;
		 if (numb == 0) result = num2 + num3;
		 else result = num2;
		 break;
	   }
	//数据移动指令
	   case move: { pos = num1; result = num2; break;}
	   case mfhi: { pos = num1; result = num2; break;}
	   case mflo: { pos = num1; result = num2; break;}
	   case nop: { break; }
	   case syscall: { l = num1; r = num2; size3 = num3; }
	}
	flag[3] = 1; flag[2] = 0;
	
	if (isbjump)
	{
		if (op == 1 && jump_opt == 0) {
			flag[1] = 0; 
			cpu.p[32] = pos;
			pre[t->p_pre].upload(1);
		}
		if (op == 0 && jump_opt == 1){
			flag[1] = 0; 
			cpu.p[32] = thd;
			pre[t->p_pre].upload(0);
		}
	}
}

void MA(std::vector<Commond> &commond, CPU &cpu, Memory &memory)
{   
	if (flag[3] == 0 || flag[4] == 1) return;
	Commond *t = &commond[thd];
	four = thd;
	switch (t->opt)
	{
	   case la: { cpu.p[pos] = result; register_lock[pos]--; b5 = 0; break; }
	   case lb: { cpu.p[pos] = memory.load(result, 1); register_lock[pos]--; room_lock = 0; b5 = 0;  break; }
	   case lh: { cpu.p[pos] = memory.load(result, 2); register_lock[pos]--; room_lock = 0; b5 = 0; break; }
	   case lw: { cpu.p[pos] = memory.load(result, 4); register_lock[pos]--; room_lock = 0; b5 = 0; break; }
	   case sb: { memory.store(result, cpu.p[pos], 1); register_lock[pos]--; room_lock = 0; b5 = 0; break; }
	   case sh: { memory.store(result, cpu.p[pos], 2); register_lock[pos]--; room_lock = 0; b5 = 0; break; }
	   case sw: { memory.store(result, cpu.p[pos], 4); register_lock[pos]--; room_lock = 0; b5 = 0; break; }
	   default: {
		   res = result; rl = resultlo; rh = resulthi; place = pos; o = op;
		   v0 = l; a0 = r; b5 = 1; size4 = size3;
	   }
    } 
	flag[4] = 1; flag[3] = 0;
}

void WB(std::vector<Commond> &commond, CPU &cpu, Memory &memory, int &ans)
{
	if (flag[4] == 0)  return; flag[4] = 0;
	Commond *t = &commond[four];
	switch (t->opt)
	{
	  case add:case addu:case addiu: case sub:case subu:  case _xor: case xoru:
	  case neg: case negu: case rem: case remu: case li:
	  {  cpu.p[place] = res; register_lock[place]--; break; }
	  case mul: case mulu: case _div: case divu:
	  {
		if (size4 == 2)
		{
			cpu.p[34] = rl; register_lock[34]--;
			cpu.p[33] = rh; register_lock[33]--;
		}
		else {
			cpu.p[place] = res; register_lock[place]--;
		}
		break;
	  }

	  case seq: case sge: case sgt: case sle: case slt: case sne: { cpu.p[place] = res; register_lock[place]--;  break; }
		  //4.4分支与跳转
	  case b: { break; }
	  case beq: case bne: case bge:case ble:case bgt: case blt: case beqz: case bnez: 
	  case blez: case bgez: case bgtz: case bltz: 
	  {   break; }

	  case j: case jr: {  break; }
	  case jal: case jalr: { cpu.p[31] = four;  break; }
	  case move: case mfhi: case mflo: { cpu.p[place] = res; register_lock[place]--; break; }
      case nop: { break; }
	  case syscall:
	  {
		switch (v0)
		{
		  case 1: {std::cout << a0; break; }
		  case 4:
		    {
			  int lp = a0;
			  while (memory.R[lp] != '\0')
			    {
				  std::cout << memory.R[lp];
				  lp++;
			    }
			  break;
		    }
		  case 5:
		    {
			  std::cin >> cpu.p[2];
			  register_lock[2]--;
			  break;
		    }
		  case 8:
		   {
			  string st; std::cin >> st;
			  int len = st.length(); len = std::min(len, size4 + 1);
			  for (int i = 0; i < len; i++)
				memory.R[a0 + i] = st[i];
			  memory.R[a0 + len] = '\0';
			  room_lock = 0;
			  break;
		    }
		   case 9:
		    {
			  cpu.p[2] = heap;
			  heap += a0;
			  register_lock[2]--;
			  room_lock = 0;
			  break;
		    }
		   case 10:
		    {
			  boo = 0; ans = 0;
			  break;
		    }
		   case 17:
		   {
			  boo = 0; ans = a0;
			  break;
		   }
		}
	  }
	}
}

void process(std::vector<Commond> &commond, CPU &cpu, Memory &memory,int &ans)
{
	cpu.p[32] = lab["main"]; 
	boo = 1; prerecord();
	while (boo){
		WB(commond, cpu, memory, ans);
		MA(commond, cpu, memory);
		EX(commond, cpu, memory);
		ID(commond, cpu, memory);
		IF(commond, cpu, memory); 
		/*cnt++;
		std::cout << cnt;
		std::cout << s[cpu.p[32]] << std::endl;
		for (int i = 1; i <= 34; i++)
		  std::cout << i << ": " << cpu.p[i] << " ";
		std::cout << std::endl; */
	} 
} 
#endif 

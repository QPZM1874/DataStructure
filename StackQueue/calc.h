#ifndef CALC_H_INCLUDE
#define CALC_H_INCLUDE

#include <iostream>
#include <strstream>
#include "lnkStack.h"
using namespace std;

// 求后缀表达式类CalculatorClass类的申明
class Calculator
{
private:
    lnkStack<double> s;		// 这个栈用于压入保存操作数
    bool GetTwoOperands(double& opd1, double& opd2); 	// 从栈顶弹出两个操作数opd1和opd2
    void Compute(char op);  	// 调用GetTwoOperands，并按op运算对两个操作数进行计算
public:
    Calculator();
    void Run(const char * expr);// 后缀表达式的读入，在遇到符号"="时 ，启动求值计算
    void clear();   	// 计算器的清除(清空计算栈s)，为随后的下一次计算做准备
};

#endif // CALC_H_INCLUDE

#ifndef CALC_H_INCLUDE
#define CALC_H_INCLUDE

#include <iostream>
#include <strstream>
#include "lnkStack.h"
using namespace std;

// ���׺���ʽ��CalculatorClass�������
class Calculator
{
private:
    lnkStack<double> s;		// ���ջ����ѹ�뱣�������
    bool GetTwoOperands(double& opd1, double& opd2); 	// ��ջ����������������opd1��opd2
    void Compute(char op);  	// ����GetTwoOperands������op������������������м���
public:
    Calculator();
    void Run(const char * expr);// ��׺���ʽ�Ķ��룬����������"="ʱ ��������ֵ����
    void clear();   	// �����������(��ռ���ջs)��Ϊ������һ�μ�����׼��
};

#endif // CALC_H_INCLUDE

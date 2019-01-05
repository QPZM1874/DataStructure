// ��������Calculator��ʵ��

#include "calc.h"

Calculator::Calculator():s(0)  // ������ʼ�����ʼ�������Ա
{

}

void Calculator::clear()
{
    s.clear();
}

bool Calculator::GetTwoOperands(double& opd1, double& opd2)
{

    if (s.isEmpty())
    {
        cerr << "Missing operand!" <<endl;
        return false;
    }
    s.pop(opd1); 							// �Ҳ�����
    if (s.isEmpty())
    {
        cerr << "Missing operand!" <<endl;
        return false;
    }
    s.pop(opd2)	;						// �������
    return true;
}

void Calculator::Compute(char op)
{
    bool result;
    double operand1, operand2;
    result = GetTwoOperands(operand1, operand2);
    if (result == true)
        switch(op)
        {
        case '+' :
            s.push(operand2 + operand1);
            break;
        case '-' :
            s.push(operand2 - operand1);
            break;
        case '*' :
            s.push(operand2 * operand1);
            break;
        case '/' :
            if (operand1 == 0.0)
            {
                cerr << "Divide by 0!" << endl;
                s.clear();
            }
            else
                s.push(operand2 / operand1);
            break;
        }
    else
        s.clear();
}

// ����expr������ʽ���磺"(10+5)/5*(10+20)="
void Calculator::Run(const char * expr)
{
    // ���ַ���������ͷ������ʽ���ȼ�����������ʹ��
    istrstream exprStream(expr);

    char c;
    double newOperand, res;
    while (exprStream >> c&&c != '\0')
    {
        switch(c)
        {
        case ' ':
            break;
        case '+' :
        case '-' :
        case '*' :
        case '/' :
            Compute(c);
            break;
        default :
            exprStream.putback(c);
            exprStream >> newOperand;
            s.push(newOperand);
            break;
        }
    }

    if (!s.isEmpty())
    {
        s.pop(res);
        cout << expr << res << endl; 					// ӡ����ֵ�������
    }

}

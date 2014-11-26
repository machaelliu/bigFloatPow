#ifndef _BIG_FLOAT_H_
#define _BIG_FLOAT_H_

#include <iostream>
#include <sstream>
#include <cstdlib>
using namespace std;
namespace n_big_float
{

    /* ����һ���࣬��ʾ��ĸ����� */
    /****************************************************************************
      @ Ҫ��������� >> �� cin ������
      @ Ҫ��������� << �� cout << �������������ǰ���ͽ�β 0
      @ Ҫ��������� +�������������� BigFloat �ĺͣ�������� BigFloat ����
      @ Ҫ�������з� *����������BigFloat ���͵ĳ˻�
      @ ����ʱҪע�� digits Ϊ +INF �� -INF �����
     ****************************************************************************/
    class BigFloat
    {
        friend ostream &operator<<(ostream &os, const BigFloat &bigNum);
        friend istream &operator>>(istream &is, BigFloat &bigNum);
        friend bool operator==(const BigFloat &bigNum1, const BigFloat &bigNum2);

        public:
        BigFloat():sign('+'), digits("0"), exp(0)
        {
        }

        BigFloat(double num):exp(0)
        {
            if (num >= 0)
            {
                sign = '+';
            }
            else
            {
                sign = '-';
                num = -num;
            }

            ostringstream ss;
            ss << num;
            if (!formalize(ss.str()))
            {
                cerr << "wrong big number format" << endl;
                exit(-1);
            }
        }

        private:

        // ����λ��'+' �� '-'
        char sign;
        
        // β������񻯺󣬱������󳤶�Ϊ MAX_MANT_LEN������ MAX_MANT_LEN �Ĳ���ֱ�ӽ�ȥ
        string digits;

        // ָ������ΧΪ [-MAX_EXP, +MAX_EXP]�����������Χ��Ϊ��������͸�����
        int exp; 

        static const int MAX_EXP = 500;
        static const string::size_type MAX_MANT_LEN = 500;

        private:
        bool formalize(string);
        public:
        static string addMant(const string &num1, const string &num2);
        string mulOneBit(char bit);
    };

    // �������������
    ostream& operator<<(ostream &os, const BigFloat &num);
    istream& operator>>(istream &is, BigFloat &num);
}

#endif

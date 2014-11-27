#include "big_float.h"

namespace n_big_float
{

    // �����������Ƿ�Ϸ������Ϸ����񻯣��������������ã���Ϊ���ܻ�� digits 
    // ������
    bool BigFloat::formalize(string strNum)
    {
        bool mantAllZero = true; // ��ʶβ�������Ƿ�ȫ 0 
        bool intAllZero = true; // ��ʶβ�������Ƿ�ȫ 0
        string::size_type intFstNotZeroIx = 0; // ��������������һ����Ϊ0������
        string::size_type mantFstNotZeroIx = 0; // β������������һ����Ϊ0������
        char givenSign = '+';
        string::size_type numBegIx = 0;
        string::size_type str_size = strNum.size();
        string::size_type backNotZeroIx; // ��β����ǰ����һ����Ϊ0��λ������

        // �������λ
        if ('+' == strNum[0]|| '-' == strNum[0] )
        {
            if (str_size < 2)
            {
                return false;
            }
            givenSign = strNum[0];
            numBegIx = 1;
        }
        sign = givenSign;

        string::size_type dotIx = strNum.find('.', numBegIx);


        // ��С�����β(���������ֲ���ֻ��С��������)�����ַǷ�
        if (dotIx == str_size - 1)
        {
            return false;
        }
        // ����������С���㿪ͷ�������ֲ���ֻ��С��
        else if (dotIx == numBegIx)
        {
            for (string::size_type ix=dotIx+1; ix != str_size; ++ix)
            {
                if (strNum[ix] < '0' || strNum[ix] > '9')
                {
                    return false;
                }
                else if (mantAllZero && strNum[ix] != '0')
                {
                    mantAllZero = false;
                    mantFstNotZeroIx = ix;
                }
            }

            // β��ȫΪ 0
            if (mantAllZero)
            {
                digits = "0";
            }
            else   // β����ȫΪ 0
            {
                // ȥ��β���� 0 
                for (string::size_type ix = str_size - 1; ; --ix)
                {
                    if (strNum[ix] != '0')
                    {
                        backNotZeroIx = ix;
                        break;
                    }
                }

                exp = dotIx - mantFstNotZeroIx + 1;
                digits = strNum.substr(mantFstNotZeroIx, backNotZeroIx - mantFstNotZeroIx + 1); 
                //cout << "backNotZeroIx:" << backNotZeroIx << endl;
                //cout << "mantFstNotZeroIx:" << mantFstNotZeroIx << endl;
                //cout << "digits:" << digits << endl;
                //cout << "exp:" << exp << endl;
            }
        }
        // ������С���㣬ֻ������
        else if (dotIx == strNum.npos)
        {
            for (string::size_type ix = numBegIx; ix != str_size; ++ix)
            {
                if (strNum[ix] < '0' || strNum[ix] > '9')
                {
                    return false;
                }
                else if (intAllZero && strNum[ix] != '0')
                {
                    intAllZero = false;
                    intFstNotZeroIx = ix;
                }
            }

            if (intAllZero)
            {
                digits = "0";
            }
            else
            {
                // ��ȥ�����е�ǰ��0������С�����Ƶ�������ǰ��
                exp = str_size - intFstNotZeroIx;

                // ȥ��β���� 0 
                for (string::size_type ix = str_size - 1; ; --ix)
                {
                    if (strNum[ix] != '0')
                    {
                        backNotZeroIx = ix;
                        break;
                    }
                }

                digits = strNum.substr(intFstNotZeroIx, backNotZeroIx - intFstNotZeroIx + 1);
            }

        }
        // ����С���㣬������������Ҳ��С������
        else 
        {
            // �����������
            for (string::size_type ix = numBegIx; ix != dotIx; ++ix)
            {
                if (strNum[ix] < '0' || strNum[ix] > '9')
                {
                    return false;
                }
                else if (intAllZero && strNum[ix] != '0')
                {
                    intAllZero = false;
                    intFstNotZeroIx = ix;
                }
            }

            // ���С������
            for (string::size_type ix = dotIx + 1; ix != str_size; ++ix)
            {
                if (strNum[ix] < '0' || strNum[ix] > '9')
                {
                    return false;
                }
                else if (mantAllZero && strNum[ix] != '0')
                {
                    mantAllZero = false;
                    mantFstNotZeroIx = ix;
                }
            }

            if (intAllZero) // ��������ȫΪ 0 
            {
                //cout << "1" << endl;
                if (mantAllZero) // С������ȫ 0
                {
                    digits = "0";
                }
                else // С�����ֲ�ȫΪ0�������ܺ�ǰ�� 0
                {
                    // ��������ȫ0��β����ǰ��0�����������ֺ�β��ǰ��0ȥ���󣬽�
                    // С����ŵ�������ǰ�棬��ָ��������Ӧ����
                    exp = dotIx - mantFstNotZeroIx + 1;

                    // ȥ��β���� 0 
                    for (string::size_type ix = str_size - 1; ; --ix)
                    {
                        if (strNum[ix] != '0')
                        {
                            backNotZeroIx = ix;
                            break;
                        }
                    }
                    digits = strNum.substr(mantFstNotZeroIx, backNotZeroIx - mantFstNotZeroIx + 1);
                }
            }
            // �������ֲ�ȫΪ 0 
            else
            {
                if (mantAllZero) // ������ȫΪ0�� С��ȫ 0
                {
                    // ȥ������β���� 0 
                    for (string::size_type ix = dotIx -1; ix != intFstNotZeroIx; --ix)
                    {
                        if (strNum[ix] != '0')
                        {
                            backNotZeroIx = ix;
                            break;
                        }
                    }

                    exp = dotIx - intFstNotZeroIx;
                    digits = strNum.substr(intFstNotZeroIx, backNotZeroIx - intFstNotZeroIx + 1);
                }
                else // ������С�����ֶ���ȫΪ0
                {
                    // ȥ��С��β���� 0 
                    for (string::size_type ix = str_size - 1; ix != dotIx ; --ix)
                    {
                        if (strNum[ix] != '0')
                        {
                            backNotZeroIx = ix;
                            break;
                        }
                    }

                    exp = dotIx - intFstNotZeroIx;

                    // ȥ��С����
                    digits = strNum.substr(intFstNotZeroIx, dotIx - intFstNotZeroIx);
                    digits += strNum.substr(dotIx + 1, backNotZeroIx - dotIx);
                }

            }
        }

        // ����߽����
        if (exp > MAX_EXP)
        {
            // �������� -INF���������� +INF
            digits = "INF";
        }
        else if (exp < -MAX_EXP)
        {
            digits = "0";
        }

        if ("0" == digits || "INF" == digits)
        {
            exp = 0;
        } 
        else if (digits.size() > MAX_MANT_LEN)
        {
            digits = digits.substr(0, 500);
        }

        return true;
    } // end of formalize

    // ����β����ӣ��൱���Ҷ������
    string BigFloat::addMant(const string &num1, const string &num2)
    {
#ifdef DEBUG
        cout << "in addMant: " << endl;
#endif

        string::size_type size1 = num1.size();

        string::size_type size2 = num2.size();
        string::size_type lZeroNums = 0; // �϶̵���Ҫ����ǰ�� 0 �ĸ���
        string sum;
        string longerNum;
        if (size1 > size2)
        {
            lZeroNums = size1 - size2;
            string zeros(lZeroNums, '0');
            sum = zeros + num2;
            longerNum = num1;
#ifdef DEBUG
        cout << "sum = " << sum << endl;
#endif

        }
        else
        {
            lZeroNums = size2 - size1;
            string zeros(lZeroNums, '0');
            sum = zeros + num1;
            longerNum = num2;
#ifdef DEBUG
        cout << "sum = " << sum << endl;
#endif

        }

        int carry = 0;
#ifdef DEBUG
        cout << "size = " << sum.size() << endl;
#endif
        // ������ͬ���������
        string::size_type ix = sum.size() - 1;
        for (string::reverse_iterator iter = sum.rbegin(); 
                iter != sum.rend(); ++iter, --ix)
        {
            *iter += longerNum[ix] - '0' + carry;
            if (*iter > '9')
            {
                *iter -= 10;
                carry = 1;
            }
            else
            {
                carry = 0;
            }
#ifdef DEBUG
        cout << *iter << endl;
#endif
        }

        if (1 == carry)
        {
            sum = "1" + sum;
            return sum;
        }
        else
        {
            return sum;
        }
    }

    // β������һλ����
    string BigFloat::mulOneBit(char bit)
    {
        int carry = 0;
        bit -= '0';
        string prdt;

        for (string::const_reverse_iterator iter = digits.rbegin();
                iter != digits.rend(); ++iter)
        {
            int bitPrdt = (*iter - '0') * bit + carry;
            prdt += bitPrdt % 10 + '0';
            carry = bitPrdt / 10;
        }

        if (0 != carry)
        {
            prdt += carry + '0';
        }

        // �� prdt ����
        char aBit;
        string::size_type forwardIx = 0;
        string::size_type backwardIx = prdt.size();
        while (forwardIx < backwardIx)
        {
            aBit = prdt[backwardIx];
            prdt[backwardIx] = prdt[forwardIx];
            prdt[forwardIx] = aBit;
        }

        return prdt;
    }


    // �������������
    ostream& operator<<(ostream& os, const BigFloat &bigNum)
    {
        if (1 == bigNum.digits.size())
        {
            if ('-' == bigNum.sign && bigNum.digits != "0")
            {
                os << '-';
            }
            os << bigNum.digits << ".0";

            if (bigNum.digits != "0" && bigNum.exp != 1)
            {
                os << " " << "E" << bigNum.exp - 1;
            }

            os << endl;
        }
        else if ("INF" == bigNum.digits)
        {
            os << bigNum.sign << "INF" << endl;
        }
        else
        {
            if ('-' == bigNum.sign)
            {
                os << '-';
            }

            // �����׼��ѧ��ʾ������ 3.456 E5
            os << bigNum.digits[0] << "." << bigNum.digits.substr(1);

            if (bigNum.exp != 1)
            {
                os << " " << "E" << bigNum.exp - 1;
            }

            os << endl;
        }

        return os;
    }

    ///* �������� */
    //BigFloat& BigFloat::operator<<=(int shitfs)
    //{
    //    if (digits != "0" && digits != "INF" && shitfs != 0)
    //    {
    //        exp += shitfs;

    //        if (exp > MAX_EXP)
    //        {
    //            digits = "INF";
    //            exp = 0;
    //        }
    //        else if (exp < MAX_EXP)
    //        {
    //            digits = "0";
    //            exp = 0;
    //        }
    //    }

    //    return *this;
    //}

    //// ��������
    //BigFloat& BigFloat::operator>>=(int shitfs)
    //{
    //    (*this) <<= -shitfs;
    //    return *this;
    //}


    bool operator==(const BigFloat &bigNum1, const BigFloat &bigNum2)
    {
        if (bigNum1.sign != bigNum2.sign)
        {
            return false;
        }

        if (bigNum1.digits != bigNum2.digits)
        {
            return false;
        }

        if (bigNum1.exp != bigNum2.exp)
        {
            return false;
        }

        return true;
    }

    istream &operator>>(istream &is, BigFloat &bigNum)
    {
        string num;
        is >> num;

        if (is)
        {
            if (!bigNum.formalize(num))
            {
                // �����ʽ���ԣ��������Ĵ���״̬
                is.clear(istream::failbit);
            }
        }

        return is;
    }


} // end of namespace



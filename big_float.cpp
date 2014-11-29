#include "big_float.h"

namespace n_big_float
{
    bool BigFloat::setSign(char sign)
    {
        if (sign != '+' && sign != '-')
        {
            return false;
        }

        this->sign = sign;
        return true;
    }

    bool BigFloat::setDigits(const string &digits)
    {
        if ("INF" == digits)
        {
            this->digits = "INF";
        }
        else
        {
            for (string::size_type ix = 0; ix != digits.size(); ++ix)
            {
                if (digits[ix] < '0' || digits[ix] > '9')
                {
                    return false;
                }
            }
        }
        this->digits = digits;
        return true;
    }

    bool BigFloat::setExp(const int exp)
    {
        if (abs(exp) > MAX_EXP)
        {
            return false;
        }
        else
        {
            this->exp = exp;
            return true;
        }
    }


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
                digits = strNum.substr(mantFstNotZeroIx, backNotZeroIx 
                        - mantFstNotZeroIx + 1); 
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

    // β������һλ����
    string BigFloat::mulOneBit(char bit) const
    {
        if (bit > '9' || bit < '0')
        {
            return "";
        }

        int carry = 0;
        bit -= '0';
        string prdt;

        for (string::const_reverse_iterator iter = digits.rbegin();
                iter != digits.rend(); ++iter)
        {
#ifdef T_mulOneBit
            cout << *iter << endl;
#endif
            int bitPrdt = (*iter - '0') * bit + carry;
            prdt += bitPrdt % 10 + '0';
            carry = bitPrdt / 10;
        }

        if (0 != carry)
        {
            prdt += carry + '0';
        }
#ifdef T_mulOneBit
            cout << "before reverse, prdt = " <<  prdt << endl;
#endif

        // �� prdt ����
        char aBit;
        string::size_type forwardIx = 0;
        string::size_type backwardIx = prdt.size() - 1;
        while (forwardIx < backwardIx)
        {
            aBit = prdt[backwardIx];
            prdt[backwardIx] = prdt[forwardIx];
            prdt[forwardIx] = aBit;
            ++forwardIx;
            --backwardIx;
        }

        return prdt;
    }

    // ����β����ӣ��൱���Ҷ������
    string addBigInt(const string &num1, const string &num2)
    {
#ifdef T_addBigInt
        cout << "in addBigInt: " << endl;
#endif
        // ������
        for (string::size_type ix = 0; ix != num1.size(); ++ix)
        {
            if (num1[ix] > '9' || num1[ix] < '0')
            {
                return "";
            }
        }

        for (string::size_type ix = 0; ix != num2.size(); ++ix)
        {
            if (num2[ix] > '9' || num2[ix] < '0')
            {
                return "";
            }
        }

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
#ifdef T_addBigInt
        cout << "sum = " << sum << endl;
#endif

        }
        else
        {
            lZeroNums = size2 - size1;
            string zeros(lZeroNums, '0');
            sum = zeros + num1;
            longerNum = num2;
        }

        int carry = 0;
#ifdef T_addBigInt
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

    // �������������
    ostream& operator<<(ostream& os, const BigFloat &bigNum)
    {
        const char sign = bigNum.sign;
        const string digits = bigNum.digits;
        const int exp = bigNum.exp;

        if ("INF" == digits)
        {
            os << sign << "INF" << endl;
        }
        //else if (1 == digits.size())
        //{
        //    if ('-' == sign && digits != "0")
        //    {
        //        os << '-';
        //    }
        //    os << digits << ".0";

        //    if (digits != "0" && exp != 1)
        //    {
        //        os << " " << "E" << exp - 1;
        //    }
        //}
        else
        {
            if ('-' == sign)
            {
                os << '-';
            }

           // // �����׼��ѧ��ʾ������ 3.456 E5
           // os << digits[0] << "." << digits.substr(1);

           // if (exp != 1)
           // {
           //     os << " " << "E" << exp - 1;
           // }

            // ��������ʾ��
            if (exp <= 0)
            {
                string zeros(-exp, '0');
                os << "0." << zeros << digits;
            }
            else
            {
                if (exp > static_cast<int>(digits.size()))
                {
                    string zeros(exp - digits.size(), '0');
                    os << digits << zeros;
                }
                else if (exp > static_cast<int>(digits.size()))
                {
                    os << digits.substr(0, exp) << "." << digits.substr(exp);
                }
                else
                {
                    os << digits;
                }
            }
        }

        return os;
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
    // �����󸡵�����ˣ�������β���Ŵ��������Ȼ�����
    BigFloat operator*(const BigFloat &bigNum1, const BigFloat &bigNum2)
    {
#ifdef T_opMul
        cout << "num1: " << bigNum1 << endl;
        cout << "num2: " << bigNum2 << endl;
#endif
        BigFloat prdtNum;

        if ("0" == bigNum1.digits || "0" == bigNum2.digits)
        {
            prdtNum.setSign('+');
            prdtNum.setDigits("0");
            prdtNum.setExp(0);
            return prdtNum;
        }
        else if ("INF" == bigNum1.digits)
        {
            prdtNum.setSign(bigNum1.sign);
            prdtNum.setDigits("INF");
            prdtNum.setExp(0);
            return prdtNum;
        }
        else if ("INF" == bigNum2.digits)
        {
            prdtNum.setSign(bigNum2.sign);
            prdtNum.setDigits("INF");
            prdtNum.setExp(0);
            return prdtNum;
        }

        string prdt;

        string::size_type ix = 0;
        for (string::const_reverse_iterator iter = bigNum2.digits.rbegin();
                iter != bigNum2.digits.rend(); ++iter)
        {
            string zeros(ix, '0');
            prdt = addBigInt(prdt, bigNum1.mulOneBit(*iter) + zeros);
            ++ix;
        }
#ifdef T_opMul
        cout << "prdt = " << prdt << endl;
#endif


        // ����Ƿ�ȫΪ0�����ǣ���ȥ����β�� 0
        string::size_type mantFstNotZeroIx;
        for (mantFstNotZeroIx = 0; mantFstNotZeroIx < prdt.size(); 
                ++mantFstNotZeroIx )
        {
            if (prdt[mantFstNotZeroIx] != 0)
            {
                break;
            }
        }

        // ȫ 0
        if (prdt.size() == mantFstNotZeroIx)
        {
            prdtNum.setDigits("0");
            prdtNum.setSign('+');
            prdtNum.setExp(0);
        }
        else
        {
            string::size_type backNotZeroIx = prdt.size() - 1;
            for (backNotZeroIx = prdt.size() - 1; ; --backNotZeroIx)
            {
                if ('0' != prdt[backNotZeroIx])
                {
                    break;
                }
            }

            // ���ڰ���������ģ�����Ŵ�����Ҫ��ȥ
            int prdtExp = bigNum1.exp + bigNum2.exp - bigNum1.digits.size() 
                - bigNum2.digits.size();
#ifdef T_opMul
            cout << "num1.exp = " << bigNum1.exp << endl;
            cout << "num2.exp = " << bigNum2.exp << endl;
            cout << "num1.digits.size = " << bigNum1.digits.size() << endl;
            cout << "num2.digits.size = " << bigNum2.digits.size() << endl;
#endif

            // ȥ����β�� 0 
            prdtExp += prdt.size() - 1 - backNotZeroIx;
            prdt = prdt.substr(mantFstNotZeroIx, 
                    backNotZeroIx - mantFstNotZeroIx + 1);
#ifdef T_opMul
            cout << "mantFstNotZeroIx = " << mantFstNotZeroIx << endl;
            cout << "backNotZeroIx = " << backNotZeroIx << endl;
            cout << "prdt = " << prdt << endl;
#endif

#ifdef T_opMul
            cout << "exp = " << prdtExp << endl;
#endif

            // ��������С��С��
            prdtExp += prdt.size();

#ifdef T_opMul
            cout << "exp after = " << prdtExp << endl;
#endif
            // �������
            if (bigNum1.sign == bigNum2.sign)
            {
                prdtNum.setSign('+');
            }
            else
            {
                prdtNum.setSign('-');
            }


            // ���ý��
            if (prdtExp > BigFloat::MAX_EXP)
            {
                prdtNum.setExp(0);
                prdtNum.setDigits("INF");
            }
            else if (prdtExp < -BigFloat::MAX_EXP)
            {
                prdtNum.setSign('+');
                prdtNum.setExp(0);
                prdtNum.setDigits("0");
            }
            else
            {
                // ����β��
                if (prdt.size() > BigFloat::MAX_MANT_LEN)
                {
                     prdtNum.setDigits(prdt.substr(0, BigFloat::MAX_MANT_LEN));
                }
                else
                {
#ifdef T_opMul
                    cout << "prdt = " << prdt << endl;
#endif
                    prdtNum.setDigits(prdt);
#ifdef T_opMul
                    cout << "result.digits = " << prdtNum.digits << endl;
#endif
                }

                // ����ָ��
                prdtNum.setExp(prdtExp);
            }
        }

        return prdtNum;
    }   // end of operator*


} // end of namespace



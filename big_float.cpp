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


    // 检查给定参数是否合法，若合法则规格化，参数不能是引用，因为可能会对 digits 
    // 本身规格化
    bool BigFloat::formalize(string strNum)
    {
        bool mantAllZero = true; // 标识尾数部分是否全 0 
        bool intAllZero = true; // 标识尾数部分是否全 0
        string::size_type intFstNotZeroIx = 0; // 整数部分左数第一个不为0的索引
        string::size_type mantFstNotZeroIx = 0; // 尾数部分左数第一个不为0的索引
        char givenSign = '+';
        string::size_type numBegIx = 0;
        string::size_type str_size = strNum.size();
        string::size_type backNotZeroIx; // 从尾部往前数第一个不为0的位的索引

        // 处理符号位
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


        // 以小数点结尾(包含了数字部分只含小数点的情况)，数字非法
        if (dotIx == str_size - 1)
        {
            return false;
        }
        // 除符号外以小数点开头，即数字部分只有小数
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

            // 尾数全为 0
            if (mantAllZero)
            {
                digits = "0";
            }
            else   // 尾数不全为 0
            {
                // 去掉尾部的 0 
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
        // 不存在小数点，只有整数
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
                // 舍去整数中的前导0，并将小数点移到数字最前端
                exp = str_size - intFstNotZeroIx;

                // 去掉尾部的 0 
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
        // 存在小数点，既有整数部分也有小数部分
        else 
        {
            // 检查整数部分
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

            // 检查小数部分
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

            if (intAllZero) // 整数部分全为 0 
            {
                //cout << "1" << endl;
                if (mantAllZero) // 小数部分全 0
                {
                    digits = "0";
                }
                else // 小数部分不全为0，但可能含前导 0
                {
                    // 整数部分全0，尾数有前导0，将整数部分和尾数前导0去掉后，将
                    // 小数点放到数字最前面，对指数进行相应调整
                    exp = dotIx - mantFstNotZeroIx + 1;

                    // 去掉尾部的 0 
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
            // 整数部分不全为 0 
            else
            {
                if (mantAllZero) // 整数不全为0， 小数全 0
                {
                    // 去掉整数尾部的 0 
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
                else // 整数、小数部分都不全为0
                {
                    // 去掉小数尾部的 0 
                    for (string::size_type ix = str_size - 1; ix != dotIx ; --ix)
                    {
                        if (strNum[ix] != '0')
                        {
                            backNotZeroIx = ix;
                            break;
                        }
                    }

                    exp = dotIx - intFstNotZeroIx;

                    // 去掉小数点
                    digits = strNum.substr(intFstNotZeroIx, dotIx - intFstNotZeroIx);
                    digits += strNum.substr(dotIx + 1, backNotZeroIx - dotIx);
                }

            }
        }

        // 处理边界情况
        if (exp > MAX_EXP)
        {
            // 负无穷用 -INF，正无穷用 +INF
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

    // 尾数乘以一位整数
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

        // 将 prdt 反向
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

    // 浮点尾数相加，相当于右对齐相加
    string addBigInt(const string &num1, const string &num2)
    {
#ifdef T_addBigInt
        cout << "in addBigInt: " << endl;
#endif
        // 检查参数
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
        string::size_type lZeroNums = 0; // 较短的数要补的前导 0 的个数
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
        // 长度相同的两数相加
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

    // 输出操作符重载
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

           // // 输出标准科学表示法，如 3.456 E5
           // os << digits[0] << "." << digits.substr(1);

           // if (exp != 1)
           // {
           //     os << " " << "E" << exp - 1;
           // }

            // 输出常规表示法
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
                // 输入格式不对，设置流的错误状态
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
    // 两个大浮点数相乘，将两个尾数放大成整数，然后相乘
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


        // 检查是否全为0，若是，则去掉结尾的 0
        string::size_type mantFstNotZeroIx;
        for (mantFstNotZeroIx = 0; mantFstNotZeroIx < prdt.size(); 
                ++mantFstNotZeroIx )
        {
            if (prdt[mantFstNotZeroIx] != 0)
            {
                break;
            }
        }

        // 全 0
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

            // 由于按整数计算的，因而放大因子要减去
            int prdtExp = bigNum1.exp + bigNum2.exp - bigNum1.digits.size() 
                - bigNum2.digits.size();
#ifdef T_opMul
            cout << "num1.exp = " << bigNum1.exp << endl;
            cout << "num2.exp = " << bigNum2.exp << endl;
            cout << "num1.digits.size = " << bigNum1.digits.size() << endl;
            cout << "num2.digits.size = " << bigNum2.digits.size() << endl;
#endif

            // 去掉结尾的 0 
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

            // 将整数缩小成小数
            prdtExp += prdt.size();

#ifdef T_opMul
            cout << "exp after = " << prdtExp << endl;
#endif
            // 处理符号
            if (bigNum1.sign == bigNum2.sign)
            {
                prdtNum.setSign('+');
            }
            else
            {
                prdtNum.setSign('-');
            }


            // 设置结果
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
                // 处理尾数
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

                // 处理指数
                prdtNum.setExp(prdtExp);
            }
        }

        return prdtNum;
    }   // end of operator*


} // end of namespace



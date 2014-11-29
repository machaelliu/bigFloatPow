#include <iostream>
#include <string>
#include "big_float.h"
#include "debug.h"
using namespace std;
using namespace n_big_float;

int main(void)
{
    // 

#ifdef T_addBigInt
    string num1("123");
    string num2("4567");

    string sum = addBigInt(num1, num2);

    if (sum == "")
    {
        cerr << "error in addBigInt" << endl;
        return -1;
    }

    cout << num1 << " + " << num2 << " = " << sum << endl;
#endif 

#ifdef T_mulOneBit
    BigFloat bigNum;
    cout << "enter a big float: ";
    cin >> bigNum;
    cout << "digits = " << bigNum.digits << endl;
    cout << "exp = " << bigNum.exp << endl;

    string resu(bigNum.mulOneBit('0'));

    if ("" == resu)
    {
        cerr << "mulOneBit error"  << endl;
        return -1;
    }
    cout << "result is " << resu << endl;
#endif

#ifdef T_opMul

    BigFloat num1(100);
    BigFloat num2;
    cout << "Enter a number : ";
    cin >> num2;
    BigFloat prdt = num1 * num2;

    cout << "result is : \n" << prdt << endl;
#endif

    return 0;
}

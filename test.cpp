#include <iostream>
#include <string>
#include "big_float.h"
using namespace std;
using namespace n_big_float;

//#define T_addMant
#define T_mulOneBit

int main(void)
{
    // 

#ifdef T_addMant
    string num1("123");
    string num2("4567");

    string sum = BigFloat::addMant(num1, num2);

    if (sum == "")
    {
        cerr << "error in addMant" << endl;
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

    string resu(bigNum.mulOneBit('8'));

    if ("" == resu)
    {
        cerr << "mulOneBit error"  << endl;
        return -1;
    }
    cout << "result is " << resu << endl;
#endif

    return 0;
}

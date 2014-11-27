#include <iostream>
#include <string>
#include "big_float.h"
using namespace std;
using namespace n_big_float;

int main(void)
{

    string num1("1234");
    string num2("4567");

    string sum = BigFloat::addMant(num1, num2);
    cout << sum << endl;

    return 0;
}

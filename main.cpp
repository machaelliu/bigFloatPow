#include <iostream>
#include <string>
#include "big_float.h"
#include "debug.h"
using namespace std;
using namespace n_big_float;


int main()
{
    // 获取基数
    cout << "enter a big float: ";
    BigFloat num;
    cin >> num;
    string line;

    while (!cin)
    {
        cin.clear();
        cerr << "not a valid float number, try again: "  << endl;
        getline(cin, line);
        cin >> num;
    }

    // 获取指数
    cout << "enter the exponent:";
    int exp;
    cin >> exp;

    while (!cin || exp < 0)
    {
        cin.clear();
        cerr << "not a valid non-negative integer, try again: "  << endl;
        getline(cin, line);
        cin >> num;
    }

    // 开始计算
    BigFloat prdt(1);

    for (int ix = 0; ix < exp; ++ix)
    {
        prdt = prdt * num;
    }

    cout << "prdt is: " << prdt << endl;
    return 0;
}

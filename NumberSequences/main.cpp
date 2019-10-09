#include <iostream>
#include <string>
#include "libs/bigint.h"
#include "libs/strutils.h"

using std::cin;
using std::cout;
using std::endl;

BigString BigIntToString(const BigInt& big_int)
{
    return "0";
}

int main()
{
    BigString input;
    cin >> input;
    trim(input);
    BigInt a(input);
    cout << BigIntToString(a);
    return 0;
}

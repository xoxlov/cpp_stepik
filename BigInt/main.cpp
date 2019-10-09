#include <iostream>
#include "big_int_sample.h"
#include "bigint/BigIntegerLibrary.hh"

int main()
{
    sample();

    std::cout << bigIntegerToString(BigFibonacci(10)) << std::endl;

    return 0;
}

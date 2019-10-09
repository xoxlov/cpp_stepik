#include <string>
#include <cstdlib>
#include "bigint.h"

BigInt::BigInt(BigString strValue)
{
    sign = positive;
    auto currentChar = strValue.begin();
    while (*currentChar == '+' || *currentChar == '-' && currentChar != strValue.end())
    {
        sign = static_cast<Sign>(sign * (*currentChar == '-' ? negative : positive));
        ++currentChar;
    }
    valueInteger = {};
    while (*currentChar != '.' && *currentChar != ',' && currentChar != strValue.end())
    {
        valueInteger.push_back(std::atoi(*currentChar));
    }
    valueFraction = {};
}

BigInt::BigInt(const BigInt& other):
    sign(other.sign),
    valueInteger(other.valueInteger),
    valueFraction(other.valueFraction)
{
}

void BigInt::operator=(const BigInt& other)
{
}

BigInt::BigInt(unsigned x)
{
}

BigInt::BigInt(int x)
{
}

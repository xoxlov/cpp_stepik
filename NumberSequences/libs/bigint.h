#pragma once
#include <vector>
#include <string>

using BigString = std::string;
using BigNumber = std::vector<int>;

class BigInt {

public:
    enum Sign { negative = -1, zero = 0, positive = 1 };

protected:
    Sign sign;
    BigNumber valueInteger{};
    BigNumber valueFraction{};

public:
    BigInt() : sign(zero), valueInteger(0), valueFraction(0) {}
    explicit BigInt(BigString);
    // Copy constructor
    BigInt(const BigInt& other);

    // Assignment operator
    void operator=(const BigInt &other);

    // Constructors from primitive integer types
    explicit BigInt(unsigned int x);
    explicit BigInt(int x);
};

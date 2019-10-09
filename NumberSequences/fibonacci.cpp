#include "fibonacci.h"

long long fibonacci(int x) {
    if (x == 0)
        return 0;
    long long fib = 1, prev = 0;
    auto mult = 1;
    if (x < 0) {
        x = -x;
        mult = x % 2? 1: -1;
    }
    while (--x) {
        fib = fib + prev;
        prev = fib - prev;
    }
    return mult * fib;
}

int fibonacciIndex(long long x) {
    long long fib = 1, prev = 0;
    unsigned short index = 0;
    while (++index && fib < x) {
        fib = fib + prev;
        prev = fib - prev;
    }
    return (fib == x? index: -1);
}

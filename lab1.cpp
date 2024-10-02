#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <sstream>
#include "Bigint.h"



int main() {
    BigInt a, b, sum, sub, mul;
    std::string n = "5784abde982aa027d6fb10d409256f4ef79389842c6e41388735d12326d1829d9bfa21c15170e07eead079eb90eccc2602d17c924df43829d047624747a1cd312c32e66b1b35fc20254fb75c51234b32f7f11aa513fe4bcdfcc2549cfbde1dc625bc92ea559141dfab69";
    std::string k = "2";
    a = n;
    b = k;

    sum = sum.longAdd(a, b);
    sub = sub.longSub(a, b);
    mul = mul.multiplyDigitByBigInt(a, 0);

    std::cout << "Result: " << a.to_hex() << std::endl;
    std::cout << "Result: " << b.to_hex() << std::endl;
    std::cout << "Result: " << sum.to_hex() << std::endl;
    std::cout << "Result: " << sub.to_hex() << std::endl;
    std::cout << "Result: " << mul.to_hex() << std::endl;

    return 0;
}
#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <sstream>
#include "Bigint.h"



int main() {
    BigInt a, b, sum;
    std::string n = "949672964ad86556ef462";
    std::string k = "949672964ad86556ef462";
    a = n;
    b = k;

    sum = sum.longAdd(a, b);

    std::cout << "Result: " << a.to_hex() << std::endl;
    std::cout << "Result: " << b.to_hex() << std::endl;
    std::cout << "Result: " << sum.to_hex() << std::endl;

    return 0;
}
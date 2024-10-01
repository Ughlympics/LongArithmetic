#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <sstream>
#include "Bigint.h"



int main() {
    BigInt a, b, sum;
    std::string n = "4d3c91c445";
    std::string k = "426946294298";
    a = n;
    b = k;

    sum = sum.longAdd(a, b);

    std::cout << "Result: " << a.to_hex() << std::endl;
    std::cout << "Result: " << sum.to_hex() << std::endl;

    return 0;
}
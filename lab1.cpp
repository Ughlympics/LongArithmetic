#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <sstream>
#include "Bigint.h"



int main() {
    BigInt a, b, sum;
    std::string n = "4d3c91c4";
    //std::string k = "0x0";
    a = n;
    //b = k;

    ////sum = sum.longAdd(a, b);

    std::cout << "Result: " << a.to_hex() << std::endl;
    //std::cout << "Result: " << b.to_hex() << std::endl;

    return 0;
}
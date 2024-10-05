#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <sstream>
#include "Bigint.h"



int main() {
    BigInt a, b, c, sum, sub, mul, bigmul, div, d;
    std::string n = "935234324698";
    std::string k = "21464189545";
    std::string z = "5784abde9";
    a = n;
    b = k;
    c = z; 

    //sum = sum.longAdd(a, b);
    //sub = sub.longSub(a, b);
    //mul = mul.multiplyDigitByBigInt(a, 0);
    //bigmul = bigmul.multiplyBigInt(a, c);
    div = a.divide(a, b);


    std::cout << "First number: " << a.to_hex() << std::endl;
    std::cout << "Second: " << b.to_hex() << std::endl;
    std::cout << "SumResult: " << sum.to_hex() << std::endl;
    std::cout << "SubResult: " << sub.to_hex() << std::endl;
    std::cout << "MulDigitResult: " << mul.to_hex() << std::endl;
    std::cout << "MulResult: " << bigmul.to_hex() << std::endl;
    std::cout << "DivResult: " << div.to_hex() << std::endl;
    //std::cout << "MulResult: " << d.to_hex() << std::endl;

    return 0;
}
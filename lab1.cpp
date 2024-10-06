#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <sstream>
#include "Bigint.h"



int main() {
    BigInt a, b, c, sum, sub, mul, bigmul, div, mod, win;
    std::string n = "4324fd3ea27642";
    std::string k = "4796787";
    std::string z = "FFFFFFFF00000000FFFFFFFF)";
    a = n;
    b = k;
    c = z; 

    //sum = sum.longAdd(a, b);
    //sub = sub.longSub(a, b);
    //mul = mul.multiplyDigitByBigInt(a, 0);
    //bigmul = bigmul.multiplyBigInt(a, a);
    div = div.divide(a, b);
    //mod = a.modulo(a, b);
    //win = win.LongPowerWindow(a, 6);


    std::cout << "First number: " << (a.to_hex()) << std::endl;
    std::cout << "Second: " << b.to_hex() << std::endl;
    //std::cout << "SumResult: " << sum.to_hex() << std::endl;
    //std::cout << "SubResult: " << sub.to_hex() << std::endl;
    //std::cout << "MulDigitResult: " << mul.to_hex() << std::endl;
    //std::cout << "MulResult: " << bigmul.to_hex() << std::endl;
    //std::cout << "DivResult: " << div.to_hex() << std::endl;
    //std::cout << "ModResult: " << mod.to_hex() << std::endl;
    //std::cout <<" ModResult: " << win.to_hex() << std::endl;

    return 0;
}
#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <sstream>
#include "Bigint.h"

//28a895cfd0200f098e2effaf19391c4a837ff199610c9bd4241b1a226effbc0ba1e4c9f81cd703a4212c02f96767adbc1e336b9d2cc5eccc98bd202bddc8fa5011f2df252fbb1843b3422db8f63129bad292c3b42a2402cf732500d8f0954fdc329c8a197a41fd984ca46b69caa59553ba92bacac9646d1a9c4508c3111f7ebf
//2dc02054ff689a01dc9b1ad05270aa78a271b0c9bf058834f55843a616f85232421f0ce4a84eac70a626ecaa949f174ef2b436a4142e1dcf790dfd232a613e9a
//20736a58fe16964aa40fbafbcb63175b370f70823dd4212ff42bfbc778478b757e15cb8f9eb1bc33ae07f2366f07c6bade3f8cb1745bd0622073c835d9ed17b9897730a542ab333ec3f25e91a36787064d30eb8c5a396d5345f580b8104249d9d90cf6a85a2ce2e09a2ef2df9308cc0c9f57ff7727e6b0f56294dafff4c3b994
int main() {
    BigInt a, b, c, sum, sub, mul, bigmul, div, mod, win;
    std::string n = "005bacee0fa2df83945c0fc49fb66476fcb4ced88ae514d563fd41feb21a619c0728bac89ae15a630b861223a014e92a1ee22def63726800899497f776c515f483cfa7e3844cc09f5ba9327be3c6d514776997dc1ed17e6f4680c4d2f7a2485feee891a6782e43051cdacaa91735c710e3f7bab85ac4bf9c7407b398a7a2d33e";
    std::string k = "bb7ddef8f49e14e07a0f33697ff1f52eba7f164c9349392e4f86f2c7f2848e9ba52e48630690ddc9706d03aaa1f6c6c1087b2c303cb4e7e0041657f98c3729ce";
    std::string z = "FFFFFFFF00000000FFFFFFFF";
    a = n;
    b = k;
    c = z; 

    sum = sum.longAdd(a, b);
    sub = sub.longSub(a, b);
    //mul = mul.LongMulOneDigit(a, 0x4233ae87);
    bigmul = bigmul.multiplyBigInt(a, b);
    div = div.divide(a, b);
    //mod = a.modulo(a, b);
    //win = win.LongPowerWindow(a, 6);


    std::cout << "First number: " << (a.to_hex()) << std::endl;
    std::cout << "Second: " << b.to_hex() << std::endl;
    std::cout << "SumResult: " << sum.to_hex() << std::endl;
    std::cout << "SubResult: " << sub.to_hex() << std::endl;
    //std::cout << "MulDigitResult: " << mul.to_hex() << std::endl;
    std::cout << "MulResult: " << bigmul.to_hex() << std::endl;
    std::cout << "DivResult: " << div.to_hex() << std::endl;
    //std::cout << "ModResult: " << mod.to_hex() << std::endl;
    //std::cout <<" WinResult: " << win.to_hex() << std::endl;

    return 0;
}
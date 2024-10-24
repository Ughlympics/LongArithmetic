#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <sstream>
#include "Bigint.h"

//c38027f97d1bc3787fca237180234602e0d61e48fd1b80e8642d181247ff3a1eb6105d541517c202ac9118e369ea32f0ce6aafc8a6fefe2993bec3befca44512
//28a895cfd0200f098e2effaf19391c4a837ff199610c9bd4241b1a226effbc0ba1e4c9f81cd703a4212c02f96767adbc1e336b9d2cc5eccc98bd202bddc8fa5011f2df252fbb1843b3422db8f63129bad292c3b42a2402cf732500d8f0954fdc329c8a197a41fd984ca46b69caa59553ba92bacac9646d1a9c4508c3111f7ebf
//2dc02054ff689a01dc9b1ad05270aa78a271b0c9bf058834f55843a616f85232421f0ce4a84eac70a626ecaa949f174ef2b436a4142e1dcf790dfd232a613e9a
//20736a58fe16964aa40fbafbcb63175b370f70823dd4212ff42bfbc778478b757e15cb8f9eb1bc33ae07f2366f07c6bade3f8cb1745bd0622073c835d9ed17b9897730a542ab333ec3f25e91a36787064d30eb8c5a396d5345f580b8104249d9d90cf6a85a2ce2e09a2ef2df9308cc0c9f57ff7727e6b0f56294dafff4c3b994
int main() {
    BigInt a, b, c, d, sum, sub, bigmul, div, mod, gsd, test ;
    std::string n = "28a895cfd0200f098e2effaf19391c4a837ff199610c9bd4241b1a226effbc0ba1e4c9f81cd703a4212c02f96767adbc1e336b9d2cc5eccc98bd202bddc8fa5011f2df252fbb1843b3422db8f63129bad292c3b42a2402cf732500d8f0954fdc329c8a197a41fd984ca46b69caa59553ba92bacac9646d1a9c4508c3111f7ebf";
    std::string k = "20736a58fe16964aa40fbafbcb63175b370f70823dd4212ff42bfbc778478b757e15cb8f9eb1bc33ae07f2366f07c6bade3f8cb1745bd0622073c835d9ed17b9897730a542ab333ec3f25e91a36787064d30eb8c5a396d5345f580b8104249d9d90cf6a85a2ce2e09a2ef2df9308cc0c9f57ff7727e6b0f56294dafff4c3b994";
    std::string l = "c38027f97d1bc3787fca237180234602e0d61e48fd1b80e8642d181247ff3a1eb6105d541517c202ac9118e369ea32f0ce6aafc8a6fefe2993bec3befca44512";
    std::string m = "10000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
    a = n;
    b = k;
    c = l;
    d = m;

    //sum = a + b;
    //sub = sub.longSub(a, b);
    //bigmul = bigmul.multiplyBigInt(a, b);
    //div = div.divide(d, c);
    //mod = mod.modulo(a, b);
    //gsd = gsd.BigIntGSD(a, b);
    //test = test.lcm(a, b);
    test = test.LongModPowerBarrett(a, b, c);


    std::cout << "First number: " << (a.to_hex()) << std::endl;
    std::cout << "Second: " << b.to_hex() << std::endl;
   /* std::cout << "SumResult: " << sum.to_hex() << std::endl;
    std::cout << "SubResult: " << sub.to_hex() << std::endl;
    std::cout << "MulResult: " << bigmul.to_hex() << std::endl;
    std::cout << "DivResult: " << div.to_hex() << std::endl;
    std::cout << "Mod: " << mod.to_hex() << std::endl;*/
    std::cout << "Test: " << test.to_hex() << std::endl;

    return 0;
}
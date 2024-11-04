#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <sstream>
#include <random>
#include "Bigint.h"
#include "Benchmark.h"

//c38027f97d1bc3787fca237180234602e0d61e48fd1b80e8642d181247ff3a1eb6105d541517c202ac9118e369ea32f0ce6aafc8a6fefe2993bec3befca44512
//28a895cfd0200f098e2effaf19391c4a837ff199610c9bd4241b1a226effbc0ba1e4c9f81cd703a4212c02f96767adbc1e336b9d2cc5eccc98bd202bddc8fa5011f2df252fbb1843b3422db8f63129bad292c3b42a2402cf732500d8f0954fdc329c8a197a41fd984ca46b69caa59553ba92bacac9646d1a9c4508c3111f7ebf
//2dc02054ff689a01dc9b1ad05270aa78a271b0c9bf058834f55843a616f85232421f0ce4a84eac70a626ecaa949f174ef2b436a4142e1dcf790dfd232a613e9a
//20736a58fe16964aa40fbafbcb63175b370f70823dd4212ff42bfbc778478b757e15cb8f9eb1bc33ae07f2366f07c6bade3f8cb1745bd0622073c835d9ed17b9897730a542ab333ec3f25e91a36787064d30eb8c5a396d5345f580b8104249d9d90cf6a85a2ce2e09a2ef2df9308cc0c9f57ff7727e6b0f56294dafff4c3b994

std::string generateHexNumber(size_t length) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, 15);

    std::ostringstream hexStream;

    for (size_t i = 0; i < length; ++i) {
        int randomValue = dist(gen);
        hexStream << std::hex << std::nouppercase << randomValue;
    }

    return hexStream.str();
}

int main() {
    BigInt a, b, c, sum, sub, lcm, bigmul,  gsd, test, res ;
    std::string n = "283527121300cddeaa5d2750e2fabe17bc2289f575609de72dbd34d03ad2be472abec4f8cdb6653a8459867f72ff4840e9de7e9e3b8a08ce0427d24f14acf4f2ef1ace93e8b3ee9ec59f508c4e919a8a2e5cd550df1e31b387c67397f36423795907cc0c8a38f46c26979782030a9b5475db2902fac12161cc1ae853d68e00fe2ef29736ad778321830cc82a0c13e5333e982be0c2c33fa12ef9bdc1e030d8181cdece4c44cf7a22a10a971a5734b0626592cab867f1299c0f4e95a9cb0fbe57f634c1b7345a7dba629936ffa88f0367423f47d92dee707f9c3118d91ff0a75cbfc76da3e7fc37072b57bb59c4540b39f5f526454ba269cd334432f3bd6da23e";
    std::string k = "97154d63a6f38d0eed65a0a94a689ea40aa804d06070a49b15ecb58368217fc2863a1155c5831ab59e541e8e3705faa0d4f93a8fdd2074b522de6f4eae0f86915aedcc05eec2cbe27ab930a243f955eaf5bf6a9ce3491c1d9831a87eb9abf88c8dc2d1a8258aee9d456dacd4312467278b27dfe19d7285f62caec31c8552e3b0f1c98027810a2b4c36950fe611d782bbc5d165e47576158d8dd635f73cde2403d712bf2192c7057dfd147a890c05b7f3e241e284951186dd9ea725d09b0cabae413c38b07abb74a82f4d3b9ddfc1a9b608da2d0eeba99bada422ae12f32934e2202bb1a31be0ac177df36c2d890fe184fbc750f4bcf4cd8cfb3b261a5244af96";
    std::string l = "c02fc3804ec372be0b90bee955ee916c226a690198c14022d87d843387256f279383f067845aa2af5f1ea9b0a8e4e0fe0d5d595ee8cd4b07f7fc4cc2456f98fe9c5edaddcacda558f2077069ec8c9ccebbdaa64c683dcb5bb24511741ce9d821c2bfcb0179499e8bbc1e63e4ad7a5ff87c4dadc226f3905f0da40a51ae3c36a97c8778c82be4774cdfbbba2f59017b369c4f03fafab8e73ee43b1950ca47a985eca5933931327ca84bfa82256256b5ba7184cd8471121f7921aebe4951da5ab6f9a674994d7bd947cab52444e00f547678d067c8e03222ee6890885e1422fef4d19407105b7365b7604a6a59fab56d5d8c7b361d08ac595bcb6fd9d38e20984d";
 
    a = n;
    b = k;
    c = l;

    ///*sd = gsd.BigIntGSD(a, b);
    //lcm = lcm.lcm(a, b);
    //sum = sum.mod_longAdd(a, b, c);
    sub = sub.mod_longSub(a, b, c);
    //bigmul = a.mod_squareBigInt(c);*/
    //res = res.LongModPowerBarrett(a, b, c);

    //std::cout << "GSD: " << gsd.to_hex() << std::endl;
    //std::cout << "LCM: " << lcm.to_hex() << std::endl;
    //std::cout << "SUm: " << sum.to_hex() << std::endl;
    std::cout << "SUB: " << sub.to_hex() << std::endl;
    //std::cout << "Bigmil: " << bigmul.to_hex() << std::endl;
    std::cout << "Result: " << res.to_hex() << std::endl;

    

    //sum = a + b;
    //sub = b - a;
    //bigmul = bigmul.multiplyBigInt(a, b);
    //div = div.divide(d, c);
    //mod = mod.modulo(a, b);
    //gsd = gsd.BigIntGSD(a, b);
    //test = test.LongPowerWindow(a, 2);
    //test = test.LongModPowerBarrett(a, b, c);


    //std::vector<double> times;  
    //double total_time = 0.0;
    //size_t length = 512;
    //double total = 0.0;
    //for (int i = 0; i < 100; ++i) {
    //    std::string hexNumber1 = generateHexNumber(length);
    //    std::string hexNumber2 = generateHexNumber(length);
    //    std::string hexNumber3 = generateHexNumber(length - 10);
    //    std::cout << "Hex number " << (i + 1) << ": " << hexNumber1 << std::endl;
    //    std::cout << "Hex number " << (i + 1) << ": " << hexNumber2 << std::endl;
    //    std::cout << "Hex number " << (i + 1) << ": " << hexNumber3 << std::endl;
    //    BigInt left, right, res, extra;
    //    left = hexNumber1;
    //    right = hexNumber2;
    //    extra = hexNumber3;
    //    {
    //        Benchmark benchmark("Summation time for iteration " + std::to_string(i + 1));
    //        //res = res.BigIntGSD(left, right);
    //        res = res.LongModPowerBarrett(extra, left, right);
    //        //res = res.mod_longAdd(left, right, extra);
    //        //res = left.mod_squareBigInt(right);
    //        double elapsed_time = benchmark.getElapsedTime(); 
    //        times.push_back(elapsed_time); 
    //        total_time += elapsed_time;
    //    }
    //    std::cout << "Result: " << res.to_hex() << std::endl;
    //}

    /*std::cout << "First number: " << (a.to_hex()) << std::endl;
    std::cout << "Second: " << b.to_hex() << std::endl;
    std::cout << "SumResult: " << sum.to_hex() << std::endl;
    std::cout << "SubResult: " << sub.to_hex() << std::endl;
    std::cout << "MulResult: " << bigmul.to_hex() << std::endl;
    std::cout << "DivResult: " << div.to_hex() << std::endl;
    std::cout << "Mod: " << mod.to_hex() << std::endl;*/
    //std::cout << "Test: " << test.to_hex() << std::endl;

    //std::cout << "Total time for all iterations: " << total_time << " seconds." << std::endl;

    return 0;
}
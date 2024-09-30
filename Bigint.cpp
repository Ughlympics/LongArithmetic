#include "Bigint.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <sstream>

const uint16_t MaxSize = 512;
const int64_t int32_size = 4294967296;

//default constructors
BigInt::BigInt() : count{ 1 }, size{ 1 } {
	num = new uint32_t[size];
	for (int i = 0; i < size; ++i)
		num[i] = 0;
}

BigInt::BigInt(uint32_t _default_num, size_t _chunks, size_t _size) : count{ _chunks }, size{ _size } {
    num = new uint32_t[count];

    for (size_t i = 0; i < count - 1; ++i) {
        num[i] = 0; 
    }

    num[count - 1] = _default_num;
}

BigInt::BigInt(const BigInt& copy) : count{ copy.count }, size{ copy.size }
{
    num = new uint32_t[count];
    for (int i = 0; i < count; ++i)
        num[i] = copy.num[i];
}

//overloaded operators
BigInt& BigInt::operator=(const std::string& hex_str) {
    if (hex_str.length() > MaxSize + 2) {
        throw std::length_error("Error: String exceeds maximum length");
    }

    /*if (hex_str.length() <= 2 || hex_str[0] != '0' || hex_str[1] != 'x' ||
        !std::all_of(hex_str.begin() + 2, hex_str.end(), [](char c) -> bool {
            return (std::isalpha(c) && std::tolower(c) < 'g') || std::isdigit(c);
            }))
    {
        return *this;
    }*/
    size_t length = hex_str.length();
    size_t newCount = (length / 8) + 1 ;

    if (count < newCount) {
        count = newCount;
        delete[] num;
        num = new uint32_t[count]; 
    }

    for (uint16_t i = 0; i < count; ++i) {
        num[i] = 0; 
    }

    std::string rev = reverseString(hex_str);
    
    size = rev.length();

    for (size_t i = 0; i < size ; i += 8) {
        std::string hexChunk = rev.substr(i, 8);

        num[i / 8] = static_cast<uint32_t>(std::stoul(hexChunk, nullptr, 16));
    }

    return *this;
}

BigInt& BigInt::operator=(const BigInt& copy)
{
    if (num)
        delete[] num;

    count = copy.count;
    num = new uint32_t[count];
    for (int i = 0; i < count; ++i)
        num[i] = copy.num[i];

    return *this;
}

//print function
std::string BigInt::to_hex() const {
    if (count == 0 || num == nullptr) {
        return "0x0";
    }

    std::string result = "";

    for (size_t i = 0; i < count; ++i) {
        std::stringstream ss;
        ss << std::hex << std::setfill('0') << std::setw(8) << num[i];
        result += ss.str(); 
    }
    
    return /*removeLeadingZeros*/(reverseString(result));
}

//operations
BigInt BigInt::longAdd(const BigInt& left, const BigInt& right) {
    BigInt result, helper;
    if (size_check(left, right) == left.size) {
        result = left;
        helper = right;
    }
    else { 
        result = right;
        helper = left;
    }

    /*uint32_t carry = 0;
    for (size_t i, j = 0; i < size_check(left, right) + 2; i++) {
        result.num[i] = result.num[i] + helper.num[i] + carry

    }*/
    uint32_t carry = 0;
    size_t i = 0, j = 0;

    for (; i < size_check(left, right); ++i, ++j) {
        uint32_t helperValue = (j < helper.count) ? helper.num[j] : 0;

        uint64_t temp = static_cast<uint64_t>(result.num[i]) + helperValue + carry;

        carry = (temp >> 32) & 0x1;
        result.num[i] = static_cast<uint32_t>(temp);
    }


    return result; 
}

//close functions 
    std::string reverseString(const std::string & input) {
        if (input.length() < 2) {
            return input;
        }
        std::string reversed = input;
        std::reverse(reversed.begin(), reversed.end());
        return reversed;
    }


    //std::string removeLeadingZeros(const std::string& input) {
    //    if (input.empty()) {
    //        return "0";
    //    }

    //    size_t n = 0; // Начинаем с нулевого индекса
    //    size_t k = input.length();

    //    // Пропускаем все ведущие нули
    //    while (n < k && input[n] == '0') {
    //        n++;
    //    }

    //    // Если все символы - нули, возвращаем "0"
    //    if (n == k) {
    //        return "0";
    //    }

    //    // Возвращаем подстроку без ведущих нулей
    //    return input.substr(n);
    //    }
    

    size_t size_check(const BigInt& left, const BigInt& right) {
        if (left.size > right.size) {
            return left.size;
        }
        else { return right.size; }
    }



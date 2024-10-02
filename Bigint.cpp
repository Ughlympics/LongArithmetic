#include "Bigint.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <sstream>
#include <vector>

const uint16_t MaxCount = 64;
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

    std::string rev = reverseBlocks(hex_str);
    
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
    /**/
    return (reverseBlocksBack(result));
}

//operations
BigInt BigInt::longAdd(const BigInt& left, const BigInt& right) {
    BigInt result, helper, helperr;
    helper = left;
    helperr = right;

    result.resize(MaxCount);

    helper.resize(MaxCount);
    helperr.resize(MaxCount);

    uint64_t carry = 0; 

    for (size_t i = 0; i < MaxCount; ++i) {
        uint64_t sum = static_cast<uint64_t>(helper.num[i]) + helperr.num[i] + carry; 

        if (sum >= int32_size) { 
            carry = 1;
            result.num[i] = static_cast<uint32_t>(sum % int32_size); 
        }
        else {
            carry = 0; 
            result.num[i] = static_cast<uint32_t>(sum); 
        }
    }
    return result;
}

BigInt BigInt::longSub(const BigInt& left, const BigInt& right) {
    BigInt result;
    BigInt minuend = left; 
    BigInt subtrahend = right; 

    minuend.resize(MaxCount);
    subtrahend.resize(MaxCount);
    result.resize(MaxCount);

    int64_t borrow = 0;

    for (size_t i = 0; i < MaxCount; ++i) {
        int64_t diff = static_cast<int64_t>(minuend.num[i]) - subtrahend.num[i] - borrow;

        if (diff < 0) {  
            diff += int32_size;  
            borrow = 1;  
        }
        else {
            borrow = 0;  
        }

        result.num[i] = static_cast<uint32_t>(diff);
    }

    if (borrow > 0) {
        std::cerr << "Warning: Result is negative!" << std::endl;
    }
    return result;
}

BigInt BigInt::multiplyDigitByBigInt(const BigInt& number, uint32_t digit) {
    BigInt result;
    if (digit == 0) {
        return result;
    }
 
    result.resize(MaxCount);
    BigInt minuend = number;
    minuend.resize(MaxCount);

    uint64_t carry = 0;

    for (size_t i = 0; i < MaxCount; ++i) {
        uint64_t product = static_cast<uint64_t>(minuend.num[i]) * digit + carry;

        result.num[i] = static_cast<uint32_t>(product);

        carry = product >> 32;
    }

    if (carry > 0) {
        result.resize(result.count + 1); 
        result.num[result.count - 1] = static_cast<uint32_t>(carry);
    }

    return result;
}

//all reverse realization))
    std::string reverseBlocks(const std::string& input) {
        std::string result = input;
        size_t length = result.length();

        if (length % 8 != 0) {
            size_t padding = 8 - (length % 8);

            result.insert(0, padding, '0');
        }
        size_t blockSize = 8;
        std::vector<std::string> blocks;

        for (size_t i = 0; i < result.length(); i += blockSize) {
            blocks.push_back(result.substr(i, blockSize));
        }

        std::reverse(blocks.begin(), blocks.end());

        std::string reversed;
        for (const auto& block : blocks) {
            reversed += block;
        }

        return reversed;
    }
    std::string reverseBlocksBack(const std::string& input) {
        size_t blockSize = 8;
        std::vector<std::string> blocks;

        for (size_t i = 0; i < input.length(); i += blockSize) {
            blocks.push_back(input.substr(i, blockSize));
        }

        std::reverse(blocks.begin(), blocks.end());

        std::string result;
        for (const auto& block : blocks) {
            result += block;
        }

        size_t firstNonZero = result.find_first_not_of('0');
        if (firstNonZero == std::string::npos) {
            return "0";
        }

        return result.substr(firstNonZero);
    }

    //other functions
    

    size_t size_check(const BigInt& left, const BigInt& right) {
        if (left.size > right.size) {
            return left.size;
        }
        else { return right.size; }
    }

    void BigInt::resize(size_t newCount) {
        if (count == newCount) {
            return; 
        }

        uint32_t* newNum = new uint32_t[newCount];

        for (size_t i = 0; count && i < newCount; ++i) {
            newNum[i] = num[i];
        }

        for (size_t i = count; i < newCount; ++i) {
            newNum[i] = 0;
        }

        delete[] num;
 
        num = newNum;
        count = newCount;
    }


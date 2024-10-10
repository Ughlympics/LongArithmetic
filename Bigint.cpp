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

std::string hexToBinary(const std::string& hex) {
    std::string binary; 

    const std::string binaryLookup[16] = {
        "0000", "0001", "0010", "0011", "0100", "0101",
        "0110", "0111", "1000", "1001", "1010", "1011",
        "1100", "1101", "1110", "1111"
    };

    for (char c : hex) {
        int value;

        if (c >= '0' && c <= '9') {
            value = c - '0';
        }
        else if (c >= 'a' && c <= 'f') {
            value = c - 'a' + 10;
        }
        else if (c >= 'A' && c <= 'F') {
            value = c - 'A' + 10; 
        }
        else {
            throw std::invalid_argument("Invalid hex character");
        }

        binary += binaryLookup[value];
    }

    size_t first_one = binary.find('1');
    if (first_one != std::string::npos) {
        return binary.substr(first_one);
    }

    return "0";
}

//operations
BigInt BigInt::longAdd(const BigInt& left, const BigInt& right) {
    BigInt result, helper, helperr;
    helper = left;
    helperr = right;
    size_t _count = count_check(left, right);

    result.resize(_count + 1);

    helper.resize(_count + 1);
    helperr.resize(_count + 1);

    uint64_t carry = 0; 

    for (size_t i = 0; i < _count; ++i) {
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
    BigInt minuend; 
    BigInt subtrahend;
    size_t _count = count_check(left, right);
    if (left < right) {
        throw std::invalid_argument("Subtraction error: right operand is greater than left operand.");
    }
    minuend = left;
    subtrahend = right;
      

    minuend.resize(_count);
    subtrahend.resize(_count);
    result.resize(_count);

    uint32_t borrow = 0;

    for (size_t i = 0; i < _count; ++i) {
        uint32_t diff = static_cast<uint32_t>(minuend.num[i]) - subtrahend.num[i] - borrow;

        if (diff > minuend.num[i]) {
            diff += int32_size;  
            borrow = 1;  
        }
        else {
            borrow = 0;  
        }

        result.num[i] = static_cast<uint32_t>(diff);
    }
    return result;
}

BigInt BigInt::LongMulOneDigit(const BigInt& number, uint32_t digit) {
    BigInt result;
    if (digit == 0) {
        return result;
    }
 
    result.resize(number.count + 1);
    BigInt minuend = number;
    minuend.resize(number.count + 1);

    uint64_t carry = 0;

    for (size_t i = 0; i < number.count + 1; ++i) {
        uint64_t temp = static_cast<uint64_t>(minuend.num[i]) * digit + carry;

        result.num[i] = (temp & 0xFFFFFFFF);

        carry = temp >> 32;
    }

    return result;
}

BigInt BigInt::multiplyBigInt(const BigInt& left, const BigInt& right) {
    BigInt result;
    result.resize(MaxCount);

    for (size_t i = 0; i < right.count; i++) {
        BigInt temp;
        temp = LongMulOneDigit(left, right.num[i]);
        temp = temp.shiftBitsToHigh(i * 32);
        result = result.longAdd(result, temp);
    }
    return result;
}

BigInt BigInt::divide(const BigInt& A, const BigInt& B) {
    BigInt Q, C;
    BigInt R = A;

    size_t k = B.bitLength();
    size_t t;
    
    while (!comparsion(R, B)) {
        t = R.bitLength();
        //std::cout << "TTTT: " << t << std::endl;
        C = B.shiftBitsToHigh(t - k);
        //std::cout << "B (before shift): " << B.to_hex() << std::endl;
        //std::cout << "C (after shift): " << C.to_hex() << std::endl;
        if (comparsion(R, C)) {
            t = t - 1;
            C = B.shiftBitsToHigh(t - k);
            //std::cout << "C2: " << C.to_hex() << std::endl;
        }

        R = R.longSub(R, C);
        //std::cout << "After subtraction R: " << R.to_hex() << std::endl;
        BigInt shiftValue;
        shiftValue = "1";
        shiftValue.resize(count + t - k);
        shiftValue = shiftValue.shiftBitsToHigh(t - k);
        Q = Q.longAdd(Q, shiftValue);
    }

    return  Q;
}
BigInt BigInt::modulo(const BigInt& A, const BigInt& B) {
    BigInt Q, C;
    BigInt R = A;

    size_t k = B.bitLength();
    size_t t;

    while (!comparsion(R, B)) {
        t = R.bitLength();
        C = B.shiftBitsToHigh(t - k);
        if (comparsion(R, C)) {
            t = t - 1;
            C = B.shiftBitsToHigh(t - k);
        }

        R = R.longSub(R, C);
        BigInt shiftValue;
        shiftValue = "1";
        shiftValue.resize(count + t - k);
        shiftValue = shiftValue.shiftBitsToHigh(t - k);
        Q = Q.longAdd(Q, shiftValue);
    }

    return  R;
}

BigInt BigInt::LongPowerWindow(const BigInt& left, int right) {
    std::string bit = intToBinary(right);
    std::reverse(bit.begin(), bit.end());
    std::cout << "Bit: " << bit << std::endl;

    BigInt A = left;
    BigInt result;
    result = "1";

    size_t m = bit.length();
    std::cout << "M: " << m << std::endl;

    for (size_t i = 0; i < m; i++) {
        if (bit[i] == '1') {
            result = multiplyBigInt(result, A);
            std::cout << "result: " << result.to_hex() << std::endl;
        }
        A = multiplyBigInt(A, A);
        std::cout << A.to_hex() << std::endl;
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
    

    size_t count_check(const BigInt& left, const BigInt& right) {
        if (left.count > right.count) {
            return left.count;
        }
        else { return right.count; }
    }

    void BigInt::resize(size_t newCount) {

        if (this->count == newCount) {
            return; 
        }

        uint32_t* newNum = new uint32_t[newCount];

        for (size_t i = 0;  i < std::min(count, newCount); ++i) {
            newNum[i] = num[i];
        }

        for (size_t i = count; i < newCount; ++i) {
            newNum[i] = 0;
        }

        delete[] num;
 
        num = newNum;
        count = newCount;
    }

    ////////////
    size_t BigInt::bitLength() const {
        size_t bitLength = 0;

        for (size_t i = count - 1; i >= 0; --i) { 
            if (num[i] != 0) {
                for (int j = 31; j >= 0; --j) {
                    if (num[i] & (1 << j)) {
                        bitLength = i * 32 + j + 1;
                        return bitLength;
                    }
                }
            }
        }

        return bitLength; 
    }

    BigInt BigInt::shiftBitsToHigh(size_t n) const {
        BigInt result(*this);

        size_t chunkShift = n / 32;
        size_t bitShift = n % 32;    

        result.resize(count + chunkShift);

        if (chunkShift > 0) {
            for (size_t i = count; i-- > 0;) {
                result.num[i + chunkShift] = result.num[i];
            }

            for (size_t i = 0; i < chunkShift; ++i) {
                result.num[i] = 0;
            }
        }

        if (bitShift > 0) {
            uint32_t carry = 0; 
            for (size_t i = 0; i < count + chunkShift; ++i) {
                uint64_t current = (static_cast<uint64_t>(result.num[i]) << bitShift) | carry;
                result.num[i] = static_cast<uint32_t>(current);
                carry = current >> 32; 
            
            }
        }

        return result;
    }

    bool BigInt::operator>=(const BigInt& other) const {
        if (count != other.count) {
            return count > other.count;
        }

        for (size_t i = count - 1 ; i >= 0; --i) {
            if (this->num[i] != other.num[i]) {
                return this->num[i] > other.num[i];
            }
        }

        return true;
    }

    bool BigInt::operator==(const BigInt& other) const {
        if (count != other.count) {
            return false;
        }

        for (size_t i = 0; i < count; ++i) {
            if (num[i] != other.num[i]) {
                return false;
            }
        }

        return true;
    }
  

    bool BigInt::operator<(const BigInt& other) const {
      
        return false;
    }

    BigInt BigInt::operator<<(unsigned long long shift) const {
        BigInt result = *this;

        size_t blockShift = shift / 32;
        size_t bitShift = shift % 32;    

        result.resize(count + blockShift);

        for (size_t i = count; i-- > 0;) { 
            if (i >= blockShift) {
                result.num[i] = result.num[i - blockShift];
            }
            else {
                result.num[i] = 0;
            }
        }

        if (bitShift > 0) {
            uint32_t carry = 0;
            for (size_t i = 0; i < result.count; ++i) {
                uint64_t temp = (static_cast<uint64_t>(result.num[i]) << bitShift) | carry;
                carry = static_cast<uint32_t>(temp >> 32);
                result.num[i] = static_cast<uint32_t>(temp); 
            }

            if (carry > 0) {
                result.resize(result.count + 1);
                result.num[result.count - 1] = carry;
            }
        }

        return result;
    }

    std::string intToBinary(int n) {
        std::string binary;
        while (n > 0) {
            binary = (n % 2 == 0 ? "0" : "1") + binary;
            n /= 2;
        }
        return binary.empty() ? "0" : binary;  
    }
    bool BigInt::comparsion(const BigInt& left, const BigInt& right) const {
        const BigInt* longerPtr = &left;
        const BigInt* shorterPtr = &right;
        bool longer = selector(longerPtr, shorterPtr);

        size_t diff = longerPtr->count - shorterPtr->count;

        /*if(diff > 0){
            for (size_t i = longerPtr->count; i > diff ; --i) {
                if (longerPtr->num[i] != 0) {
                    return longer;
                }
            }
        }*/

        for (int l = longerPtr->count - diff - 1, s = shorterPtr->count - 1; s >= 0 && l >= 0; --l, --s)
        {
            if (longerPtr->num[l] > shorterPtr->num[s]) {
                return longer;
            }
            else if (longerPtr->num[l] < shorterPtr->num[s]) {
                return !longer;
            }
        }

        return false;
    }
    bool BigInt::selector(const BigInt*& left, const BigInt*& right) const{
        const BigInt* temp;
        if (left->count < right->count){
            temp = left;
            left = right;
            right = temp;
            return true;
        }
        return false;
    }

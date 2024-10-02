#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <sstream>



//size_t

class BigInt {
private:
		uint32_t* num;
		size_t count; //number of all chunks
		size_t size; //number of all elements
public:
	//constructors
	BigInt();
	BigInt(uint32_t _default_num, size_t _chunks , size_t _size);
	BigInt(const BigInt& copy);

	~BigInt() {
		delete[] num;
	}

	//overloaded operators
	BigInt& operator=(const std::string& hex_str);
	BigInt& operator=(const BigInt& copy);

//print realize
	std::string to_hex() const;
	

	
	//operations
	BigInt longAdd(const BigInt& left, const BigInt& right);
	BigInt longSub(const BigInt& left, const BigInt& right);
	BigInt multiplyDigitByBigInt(const BigInt& number, uint32_t digit);

	//check
	friend size_t size_check(const BigInt& left, const BigInt& right);
	void resize(size_t newCount);

	
};

//close func
std::string reverseString(const std::string& input);
std::string reverseBlocks(const std::string& input);
std::string reverseBlocksBack(const std::string& input);



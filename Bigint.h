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

	//check
	friend size_t size_check(const BigInt& left, const BigInt& right);

	
};

//close func
std::string reverseString(const std::string& input);
std::string removeLeadingZeros(const std::string& input);



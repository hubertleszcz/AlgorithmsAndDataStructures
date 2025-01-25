#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define MAX_SIZE 16

#include <stdio.h>
#include <string.h>


/*
* class that implements my own string. The max size is 16, because it's the safest size for the buffer, which max size is 3 (MAX or MIN) + 10(lenght of MAX_INT)
*/
class Token {
public:
	char token[MAX_SIZE];
	int length;

	Token();

	/*
	* funtion for reading token from the console input
	*/
	void readToken();

	/*
	* funtion for printing token to the console
	*/
	void printToken();

	/*
	* funtion that returns true if token is a number. Else it returns false
	*/
	bool isANumber();

	/*
	* funtion for adding a number at the end of the token ( token + to_string(number)
	*/
	void extendTokenByNumber(int number);

	// operators
	friend bool operator==(Token token, const char* other);
	
	friend bool operator!=(Token token, const char* other);

	Token& operator=(Token second);

	Token& operator++(){
		return *this;
	};

	Token& operator++(int) {
		return *this;
	};

	~Token() = default;

};
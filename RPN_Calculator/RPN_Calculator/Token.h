#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define MAX_SIZE 16

#include <stdio.h>
#include <string.h>

class Token {
public:
	char token[MAX_SIZE];
	int length;

	Token();

	void readToken();

	void printToken();

	bool isANumber();

	void extendTokenByNumber(int numer);

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
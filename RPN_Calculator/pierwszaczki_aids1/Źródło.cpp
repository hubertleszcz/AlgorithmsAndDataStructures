#include <iostream>
#include "Priorities.h"

using namespace std;

bool isANumber(string token) {
	return token[0] >= '0' && token[0] <= '9';

}

int getPriority(string token) {
	if (token == "+") {
		return Priority::PLUS;

	}
	else if (token == "-") {
		return Priority::MINUS;
	}
	else if (token == "*") {
		return Priority::MULTIPLICATION;
	}
	else if (token == "/") {
		return Priority::DIVISION;
	}
	else if (token == "(") {
		return Priority::LEFT_PARENTHESIS;
	}
	else if (token == ")") {
		return Priority::RIGHT_PARENTHESIS;
	}
}


//TODO:
//1. Parse input
//2. Shunting yard algorithm with basic operators (+,-,*,/)
//3. own string
void parseInfix() {
	string currentToken;

	while (cin >> currentToken) {
		if (currentToken == ".") break;
		else if (isANumber(currentToken));
		else {
			cout << getPriority(currentToken) << " ";
		}
	}
	cout << endl;
}


int main() {
	int phaseCount;
	cin >> phaseCount;

	for (int i = 0; i < phaseCount; i++) {
		parseInfix();
	}
	while (true);
	return 0;
}
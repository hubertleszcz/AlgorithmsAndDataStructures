#include <iostream>
#include <stack>
#include <string>
#include <queue>
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
//1. Shunting yard algorithm with basic operators (+,-,*,/)
//2. own string
//3. own stack
//4. own queue
void parseInfix() {
	queue <string> output;
	stack <string> operators;
	string currentToken;
	string top;

	while (cin >> currentToken) {
		if (currentToken == ".") break;
		else if (isANumber(currentToken)) {
			output.push(currentToken);
			cout << currentToken << " ";
		}
		else {
			while (!operators.empty() && getPriority(operators.top()) >= getPriority(currentToken)) {
				top = operators.top();
				output.push(top);
				cout << top << " ";
				operators.pop();
			}
			operators.push(currentToken);
		}
	}

	while (!operators.empty()) {
		top = operators.top();
		output.push(top);
		cout << top << " ";
		operators.pop();
	}

	cout << endl;
}


int main() {
	int phraseCount;
	cin >> phraseCount;

	for (int i = 0; i < phraseCount; i++) {
		parseInfix();
	}
	while (true);
	return 0;
}
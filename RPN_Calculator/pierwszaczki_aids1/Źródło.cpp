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
	else if (token == "N") {
		return Priority::NEGATION;
	}
}

void printEntireStack(stack<int> numbers) {
	
	int n = numbers.size();
	int* tab = new int[numbers.size()];

	while (!numbers.empty()) {
		tab[numbers.size() - 1] = numbers.top();
		numbers.pop();
	}

	for (int i = n-1; i >=0; i--) {
		cout << tab[i] << " ";
	}

	delete[] tab;
}

int stackTopAndPop(stack <int>& numbers) {
	int a = numbers.top();
	numbers.pop();
	return a;
}

void functionOperations(string op, stack <int>& numbers) {
	int a, b, c;
	if (op == "N") {
		a = stackTopAndPop(numbers);
		numbers.push((-1) * a);
	}
	else if (op == "IF") {
		a = stackTopAndPop(numbers);
		
		b = stackTopAndPop(numbers);

		c = stackTopAndPop(numbers);
	
		if (c > 0) {
			numbers.push(b);
		}
		else numbers.push(a);
	}


}


bool arithmeticOperation(string op, stack<int>& numbers) {
	cout << op << " ";
	printEntireStack(numbers);
	cout << endl;
	int a, b;

	if (op == "+") {
		b = stackTopAndPop(numbers);
		a = stackTopAndPop(numbers);
		numbers.push(a + b);
	}
	else if (op == "*") {
		b = stackTopAndPop(numbers);
		a = stackTopAndPop(numbers);
		numbers.push(a * b);
	}
	else if (op == "-") {
		b = stackTopAndPop(numbers);
		a = stackTopAndPop(numbers);
		numbers.push(a - b);
	}
	else if (op == "/") {
		b = stackTopAndPop(numbers);
		a = stackTopAndPop(numbers);
		if (b == 0) {
			cout << "ERROR\n\n";
			return false;
		}

		numbers.push(a / b);
	}
	else {
		functionOperations(op, numbers);
	}
	
	return true;
}

bool isAFuntion(string op) {
	if (op == "N" || op == "IF") return true;
	return false;
}

void basicParsing(string currentToken, stack<string>& operators, queue <string>& output) {
	string top;
	if (isANumber(currentToken)) {
		output.push(currentToken);
		cout << currentToken << " ";
	}
	else if (currentToken == ")") {
		while (!operators.empty()) {
			if (operators.top() == "(") break;
			else {
				top = operators.top();
				output.push(top);
				cout << top << " ";
				operators.pop();
			}
		}
		operators.pop();
	}
	else {
		while (!operators.empty() && getPriority(operators.top()) >= getPriority(currentToken) && !isAFuntion(currentToken) && operators.top() != "(") {
			top = operators.top();
			output.push(top);
			cout << top << " ";
			operators.pop();
		}
		operators.push(currentToken);
	}

}


void calculateRPN(queue <string> tokens) {
	stack<int> numbers;
	string currentToken;
	
	while (!tokens.empty()) {
		currentToken = tokens.front();
		tokens.pop();
		if (isANumber(currentToken)) {
			numbers.push(stoi(currentToken));
		}

		else {

			if (getPriority(currentToken) <= Priority::NEGATION) {
				if(!arithmeticOperation(currentToken, numbers)) return;

			}

		}

	}
	cout << numbers.top() << endl << endl;

}




//TODO:
//1. if operation
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
		basicParsing(currentToken, operators, output);
	}

	while (!operators.empty()) {
		top = operators.top();
		output.push(top);
		cout << top << " ";
		operators.pop();
	}

	cout << endl;
	calculateRPN(output);
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
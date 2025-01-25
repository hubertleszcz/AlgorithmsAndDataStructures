#include <iostream>
#include <stack>
#include <string>
#include <queue>
#include "Priorities.h"

using namespace std;

bool isANumber(string token) {
	return token[0] >= '0' && token[0] <= '9';
}

int getArgs(string function) {
	string temp = "";

	for (int i = 3; i < function.length(); i++) {
		temp += function[i];
	}

	return stoi(temp);

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
	else if (token == "IF") {
		return Priority::IF;
	}
	else if (token == "MIN") {
		return Priority::MIN;
	}
	else if (token == "MAX") {
		return Priority::MAX;
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
		std::cout << tab[i] << " ";
	}

	delete[] tab;
}

template <typename T>
T stackTopAndPop(stack <T>& numbers) {
	T a = numbers.top();
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

	else if (op[0] == 'M') {
		int arguments = getArgs(op);
		if (op[2] == 'N') {
			int min = 0x0FFFFFF0;
			for (int i = 0; i < arguments; i++) {
				a = stackTopAndPop(numbers);
				if (a < min) min = a;
			}
			numbers.push(min);
		}
		else {
			int max = (-1) * 0x0FFFFFF0;
			for (int i = 0; i < arguments; i++) {
				a = stackTopAndPop(numbers);

				if (a > max) max = a;

			}
			numbers.push(max);
		}
		

	}

}


bool arithmeticOperation(string op, stack<int>& numbers) {
	//std::cout << op << " ";
	//printEntireStack(numbers);
	//std::cout << endl;
	int a, b;

	if (op == "+") {
		b = stackTopAndPop<int>(numbers);
		a = stackTopAndPop<int>(numbers);
		numbers.push(a + b);
	}
	else if (op == "*") {
		b = stackTopAndPop<int>(numbers);
		a = stackTopAndPop<int>(numbers);
		numbers.push(a * b);
	}
	else if (op == "-") {
		b = stackTopAndPop<int>(numbers);
		a = stackTopAndPop<int>(numbers);
		numbers.push(a - b);
	}
	else if (op == "/") {
		b = stackTopAndPop<int>(numbers);
		a = stackTopAndPop<int>(numbers);
		if (b == 0) {
			std::cout << "ERROR\n\n";
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
	if (op == "IF" || op == "MIN" || op == "MAX") return true;
	return false;
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

			if(!arithmeticOperation(currentToken, numbers)) return;
		}

	}
	std::cout << numbers.top() << endl << endl;

}




//TODO:
//1. cleaner code
//2. own string
//3. own stack
//4. own queue
//5. optimization
void basicParsing(stack<string>& operators, queue <string>& output) {
	int temp;
	stack <int> functionArgs;
	string top;
	string currentToken;
	while (true) {
		cin >> currentToken;
		if (currentToken == ".") break;

		if (isANumber(currentToken)) {
			output.push(currentToken);
			//std::cout << currentToken << " ";
		}
		else if (isAFuntion(currentToken)) {
			operators.push(currentToken);
			functionArgs.push(1);
		}
		else if (currentToken == ",") {
			while (operators.top() != "(") {
				top = stackTopAndPop(operators);

				if (isAFuntion(top)) {
					temp = stackTopAndPop(functionArgs);

					if (top != "IF") {
						top += to_string(temp);
					}
				}

				output.push(top);
				//std::cout << top << " ";
			}
			functionArgs.top()++;
		}
		else if (currentToken == ")") {
			while (!operators.empty()) {
				if (operators.top() == "(") break;
				else {
					top = stackTopAndPop(operators);

					if (isAFuntion(top)) {
						temp = stackTopAndPop(functionArgs);

						if (top != "IF") {
							top += to_string(temp);

						}
					}

					output.push(top);
					//std::cout << top << " ";
				}
			}
			operators.pop();
		}
		else {
			while (!operators.empty() && getPriority(operators.top()) >= getPriority(currentToken) && currentToken != "N" && operators.top() != "(") {
				top = stackTopAndPop(operators);

				if (isAFuntion(top)) {
					temp = stackTopAndPop(functionArgs);

					if (top != "IF") {
						top += to_string(temp);

					}
				}

				output.push(top);
				//std::cout << top << " ";
			}
			operators.push(currentToken);
		}

	}

	while (!operators.empty()) {
		top = stackTopAndPop(operators);

		if (isAFuntion(top)) {
			temp = stackTopAndPop(functionArgs);

			if (top != "IF") {
				top += to_string(temp);

			}
		}

		output.push(top);
		//std::cout << top << " ";
	}
}

void parseInfix() {
	queue <string> output;
	stack <string> operators;
	string currentToken;
	string top;
	basicParsing(operators, output);


	std::cout << endl;
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
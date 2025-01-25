#include <iostream>
#include <stack>
#include <string>
#include <queue>
#include "Priorities.h"

using namespace std;

/*
* Funtion that returns true if given token is a number and false when it's not
* @param token - token to check
*/
bool isANumber(string token) {
	return token[0] >= '0' && token[0] <= '9';
}

/*
* function that returns the argument count from MIN or MAX operations
* @param function - MIN or MAX token to check
*/
int getArgs(string function) {
	string temp = "";

	for (int i = 3; i < function.length(); i++) {
		temp += function[i];
	}

	return stoi(temp);

}

/*
* function that returns the priority of the operator or function
* @param token - token to check
*/
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

/*
* function that prints the stack from top to bottom
* param @numbers - stack to print out
*/

void printEntireStack(stack<int> numbers) {

	int n = numbers.size();
	stack<int> temp;

	while (!numbers.empty()) {
		cout << numbers.top() << " ";
		temp.push(numbers.top());
		numbers.pop();
	}

	while (!temp.empty()) {
		numbers.push(temp.top());
		temp.pop();
	}

}


/*
* function that makes the pop and top stack operations shorter in code
* @param stack - stack on which the operations are performed
*/
template <typename T>
T stackTopAndPop(stack <T>& stack) {
	T a = stack.top();
	stack.pop();
	return a;
}

/*
* function which performs operations like negation, IF, MIN and MAX
* @param op - operator
* @param numbers - stack of numbers used in operations
*/

void functionOperations(string op, stack <int>& numbers) {
	int a, b, c;
	// negation
	if (op == "N") {
		a = stackTopAndPop(numbers);
		numbers.push((-1) * a);
	}
	else if (op == "IF") {

		// IF ( a , b , c ) - if ( a > 0 ) returns b, else returns c

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
		// MIN operation
		if (op[2] == 'N') {
			int min = 0x0FFFFFF0;
			for (int i = 0; i < arguments; i++) {
				a = stackTopAndPop(numbers);
				if (a < min) min = a;
			}
			numbers.push(min);
		}
		// MAX operation
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

/*
* function that performs +,-,*,/ operation and returns true if it's successful ( when it's not dividing by 0
* @param op - operator
* @param numbers - stack of numbers used in operations
*/
bool arithmeticOperation(string op, stack<int>& numbers) {
	std::cout << op << " ";
	printEntireStack(numbers);
	std::cout << endl;
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


/*
* function that returns true if given operator is a function and false if it's not
* @param op - operator
*/
bool isAFuntion(string op) {
	if (op == "IF" || op == "MIN" || op == "MAX") return true;
	return false;
}

/*
* function that calculates the expression in postfix notation
* @param tokens - postfix expression
*/
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
			if (!arithmeticOperation(currentToken, numbers)) return;
		}

	}
	// the result of the expression
	std::cout << numbers.top() << endl << endl;

}

/*
* function that reduces the operator's count on the stack during shunting yard algorithm. Basically it pops the operators from the stack, can possibly
* extend them by the arguments count and pushes them to the postfix notation
* @param operators - operators stack
* @param functionArgs - stack for the function arguments counts
* @param output - postfix notation
*/
void reduceOperators(stack<string>& operators, stack<int>& functionArgs, queue<string>& output) {
	int temp;
	string top;

	top = stackTopAndPop(operators);

	if (isAFuntion(top)) {
		temp = stackTopAndPop(functionArgs);

		if (top != "IF") {
			top += to_string(temp);
		}
	}

	output.push(top);
	std::cout << top << " ";
}

//TODO:
//1. own string
//2. own stack
//3. own queue
//4. optimization

/*
* function that performs the Shunting yard algorithm. Basically it creates postfix notation of expression given in infix notation
* @param operators - operators stack
* @output - postfix notation expression
*/
void shuntingYard(stack<string>& operators, queue <string>& output) {

	stack <int> functionArgs;
	string currentToken;
	while (true) {
		cin >> currentToken;
		// expression end
		if (currentToken == ".") break;

		if (isANumber(currentToken)) {
			// for numbers just pushes the token to output
			output.push(currentToken);
			std::cout << currentToken << " ";
		}
		else if (isAFuntion(currentToken)) {
			// for functions just pushes the token to the operators stack
			operators.push(currentToken);
			functionArgs.push(1);
		}
		else if (currentToken == ",") {
			// pops operators while the stack's top is not "(" and increases funtion's arguments count
			while (operators.top() != "(") {
				reduceOperators(operators, functionArgs, output);
			}
			functionArgs.top()++;
		}
		else if (currentToken == ")") {
			// pops operators to output as long as the "(" is not at the stack's top
			while (!operators.empty()) {
				if (operators.top() == "(") break;
				else {
					reduceOperators(operators, functionArgs, output);
				}
			}
			operators.pop();
		}
		else {
			// rest of the operators
			while (!operators.empty() &&
				getPriority(operators.top()) >= getPriority(currentToken) &&
				currentToken != "N" && /* checks for the operator being left-associative */
				operators.top() != "(") {
				reduceOperators(operators, functionArgs, output);

			}
			operators.push(currentToken);
		}

	}
	
	// pops operators to output after the expression parsing
	while (!operators.empty()) {
		reduceOperators(operators, functionArgs, output);
	}
	std::cout << endl;
}

/*
* funtion that handles every infix notation expression given by user
*/
void parseInfix() {
	queue <string> output;
	stack <string> operators;

	shuntingYard(operators, output);
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
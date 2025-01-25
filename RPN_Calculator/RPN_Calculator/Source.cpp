#include <iostream>
#include <string>
#include <queue>
#include <chrono>
#include "Stack.h"
#include "Priorities.h"
#include "Token.h"


using namespace std;

/*
* function that returns the argument count from MIN or MAX operations
* @param function - MIN or MAX token to check
*/
int getArgs(Token function) {
	string temp = "";

	for (int i = 3; i < strlen(function.token); i++) {
		temp += function.token[i];
	}

	return stoi(temp);

}

/*
* function that returns the priority of the operator or function
* @param token - token to check
*/
int getPriority(Token token) {
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

void printEntireStack(Stack<int>* numbers) {
	Stack<int> temp;

	while (!numbers->empty()) {
		printf("%d ",numbers->top());
		temp.push(numbers->top());
		numbers->pop();
	}

	while (!temp.empty()) {
		numbers->push(temp.top());
		temp.pop();
	}

}


/*
* function that makes the pop and top stack operations shorter in code
* @param stack - stack on which the operations are performed
*/
template <typename T>
T stackTopAndPop(Stack <T>* stack) {
	T a = stack->top();
	stack->pop();
	return a;
}

/*
* function which performs operations like negation, IF, MIN and MAX
* @param op - operator
* @param numbers - stack of numbers used in operations
*/

void functionOperations(Token op, Stack<int>* numbers) {
	int a, b, c;
	// negation
	if (op == "N") {
		a = stackTopAndPop(numbers);
		numbers->push((-1) * a);
	}
	else if (op == "IF") {

		// IF ( a , b , c ) - if ( a > 0 ) returns b, else returns c

		a = stackTopAndPop(numbers);

		b = stackTopAndPop(numbers);

		c = stackTopAndPop(numbers);

		if (c > 0) {
			numbers->push(b);
		}
		else numbers->push(a);
	}

	else if (op.token[0] == 'M') {

		int arguments = getArgs(op);
		// MIN operation
		if (op.token[2] == 'N') {
			int min = 0x0FFFFFF0;
			for (int i = 0; i < arguments; i++) {
				a = stackTopAndPop(numbers);
				if (a < min) min = a;
			}
			numbers->push(min);
		}
		// MAX operation
		else {
			int max = (-1) * 0x0FFFFFF0;
			for (int i = 0; i < arguments; i++) {
				a = stackTopAndPop(numbers);

				if (a > max) max = a;

			}
			numbers->push(max);
		}


	}

}

/*
* function that performs +,-,*,/ operation and returns true if it's successful ( when it's not dividing by 0
* @param op - operator
* @param numbers - stack of numbers used in operations
*/
bool arithmeticOperation(Token op, Stack<int>* numbers) {
	op.printToken();
	printEntireStack(numbers);
	printf("\n");
	int a, b;

	if (op == "+") {
		b = stackTopAndPop<int>(numbers);
		a = stackTopAndPop<int>(numbers);
		numbers->push(a + b);
	}
	else if (op == "*") {
		b = stackTopAndPop<int>(numbers);
		a = stackTopAndPop<int>(numbers);
		numbers->push(a * b);
	}
	else if (op == "-") {
		b = stackTopAndPop<int>(numbers);
		a = stackTopAndPop<int>(numbers);
		numbers->push(a - b);
	}
	else if (op == "/") {
		b = stackTopAndPop<int>(numbers);
		a = stackTopAndPop<int>(numbers);
		if (b == 0) {
			std::cout << "ERROR\n\n";
			return false;
		}

		numbers->push(a / b);
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
bool isAFuntion(Token op) {
	if (op == "IF" || op == "MIN" || op == "MAX") return true;
	return false;
}

/*
* function that calculates the expression in postfix notation
* @param tokens - postfix expression
*/
void calculateRPN(queue <Token> tokens) {
	Stack<int> numbers;
	Token currentToken;

	while (!tokens.empty()) {
		currentToken = tokens.front();
		tokens.pop();
		if (strlen(currentToken.token) == 0) break;
		if (currentToken.isANumber()) {
			numbers.push(stoi(currentToken.token));
		}
		else {
			if (!arithmeticOperation(currentToken, &numbers)) return;
		}

	}
	// the result of the expression
	printf("%d\n", numbers.top());

}

/*
* function that reduces the operator's count on the stack during shunting yard algorithm. Basically it pops the operators from the stack, can possibly
* extend them by the arguments count and pushes them to the postfix notation
* @param operators - operators stack
* @param functionArgs - stack for the function arguments counts
* @param output - postfix notation
*/
void reduceOperators(Stack<Token>* operators, Stack<int>* functionArgs, queue<Token>& output) {
	int temp;
	Token top;

	top = stackTopAndPop(operators);

	if (isAFuntion(top)) {
		temp = stackTopAndPop(functionArgs);

		if (top != "IF") {
			top.extendTokenByNumber(temp);
		}
	}

	output.push(top);
	top.printToken();
}


/*
* function that performs the Shunting yard algorithm. Basically it creates postfix notation of expression given in infix notation
* @param operators - operators stack
* @output - postfix notation expression
*/
void shuntingYard(Stack<Token>* operators, queue <Token>& output) {

	Stack <int> functionArgs;
	Token currentToken;
	while (true) {
		currentToken.readToken();
		// expression end
		if (currentToken == ".") break;

		if (currentToken.isANumber()) {
			// for numbers just pushes the token to output
			output.push(currentToken);
			currentToken.printToken();
		}
		else if (isAFuntion(currentToken)) {
			// for functions just pushes the token to the operators stack
			operators->push(currentToken);
			functionArgs.push(1);
		}
		else if (currentToken == ",") {
			// pops operators while the stack's top is not "(" and increases funtion's arguments count
			while (operators->top() != "(") {
				reduceOperators(operators, &functionArgs, output);
			}
			functionArgs.incrementTop();
		}
		else if (currentToken == ")") {
			// pops operators to output as long as the "(" is not at the stack's top
			while (!operators->empty()) {
				if (operators->top() == "(") break;
				else {
					reduceOperators(operators, &functionArgs, output);
				}
			}
			operators->pop();
		}
		else {
			// rest of the operators
			while (!operators->empty() &&
				getPriority(operators->top()) >= getPriority(currentToken) &&
				currentToken != "N" && /* checks for the operator being left-associative */
				operators->top() != "(") {
				reduceOperators(operators, &functionArgs, output);

			}
			operators->push(currentToken);
		}

	}
	
	// pops operators to output after the expression parsing
	while (!operators->empty()) {
		reduceOperators(operators, &functionArgs, output);
	}
	printf("\n");
}

/*
* funtion that handles every infix notation expression given by user
*/
void parseInfix() {
	queue <Token> output;
	Stack <Token> operators;

	shuntingYard(&operators, output);
	calculateRPN(output);
}

//TODO:
//1. own queue

int main() {
	// auto start = std::chrono::high_resolution_clock::now();
	int phraseCount;
	cin >> phraseCount;

	for (int i = 0; i < phraseCount; i++) {
		parseInfix();
	}
	// auto end = std::chrono::high_resolution_clock::now();
	// std::chrono::duration<double> duration = end - start;
	// cout << duration.count();
	while (true);
	return 0;
}
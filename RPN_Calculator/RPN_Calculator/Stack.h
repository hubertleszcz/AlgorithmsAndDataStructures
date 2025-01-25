#pragma once
#include "StackNode.h"
#include "Token.h"

/*
* my implementation of stack data structure built on a list
*/
template <typename T>
class Stack {
private:
	StackNode<T>* last;
	int size;
public:

	Stack();

	void push(T data);

	void pop();

	T top();

	bool empty();

	void incrementTop();

	~Stack();
};
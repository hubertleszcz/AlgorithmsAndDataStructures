#pragma once
#include "Token.h"


template <typename T>
class StackNode {
public:
	T data;
	StackNode<T>* prev;

	StackNode();
	StackNode(T data);

	StackNode& operator=(const StackNode& other) {
		if (this != &other) {  
			this->data = other.data;
			this->prev = other.prev;
		}
		return *this;
	}
};
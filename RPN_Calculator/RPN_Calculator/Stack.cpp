#include "Stack.h"

template class Stack<int>;
template class Stack<Token>;

template<typename T>
Stack<T>::Stack() {
	this->last = nullptr;
	this->size = 0;
}

template<typename T>
void Stack<T>::push(T data) {

	StackNode<T>* newNode = new StackNode<T>(data);
	newNode->prev = this->last;

	this->last = newNode;
	this->size++;
}

template<typename T>
void Stack<T>::pop() {

	StackNode<T>* temp = this->last;

	this->last = this->last->prev;

	this->size--;
	delete temp;
}

template<typename T>
T Stack<T>::top() {
	return this->last->data;
}

template<typename T>
bool Stack<T>::empty() {
	return this->size == 0;
}

template<typename T>
void Stack<T>::incrementTop() {
	this->last->data++;
}
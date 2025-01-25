#include "StackNode.h"

template class StackNode<int>;
template class StackNode<Token>;

template <typename T>
StackNode<T>::StackNode() {
	this->prev = nullptr;
}

template <typename T>
StackNode<T>::StackNode(T data) {
	this->data = data;
	this->prev = nullptr;
}
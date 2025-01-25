#include "QueueNode.h"

template class QueueNode<Token>;

template<typename T>
QueueNode<T>::QueueNode() {
	this->next = nullptr;
}

template<typename T>
QueueNode<T>::QueueNode(T data) {
	this->data = data;
	this->next = nullptr;
}
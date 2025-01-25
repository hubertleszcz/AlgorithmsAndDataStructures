#pragma once
#include "QueueNode.h"

/*
* my implementation of queue data structure built on a list
*/
template <typename T>
class Queue {
private:
	int size;
	QueueNode<T>* head;
	QueueNode<T>* tail;
public:
	Queue();

	void push(T data);
	
	void pop();

	T front();

	bool empty();

	~Queue();
};
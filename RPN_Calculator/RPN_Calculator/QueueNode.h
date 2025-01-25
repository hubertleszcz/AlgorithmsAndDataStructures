#pragma once
#include "Token.h"

template <typename T>
class QueueNode {
public:
	T data;
	QueueNode<T>* next;

	QueueNode();
	QueueNode(T data);
};
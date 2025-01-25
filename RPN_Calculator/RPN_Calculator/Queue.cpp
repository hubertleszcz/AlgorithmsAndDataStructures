#include "Queue.h"

template class Queue<Token>;

template <typename T>
Queue<T>::Queue() {
	this->head = nullptr;
	this->tail = nullptr;
	this->size = 0;
}

template <typename T>
void Queue<T>::push(T data) {
	QueueNode<T>* newNode = new QueueNode<T>(data);
	if (this->tail) {
		this->tail->next = newNode;
	}
	else {
		this->head = newNode; 
	}
	this->tail = newNode; 
	this->size++;
}

template <typename T>
void Queue<T>::pop() {

	QueueNode<T>* temp = this->head;
	this->head = this->head->next;

	if (!this->head) {
		this->tail = nullptr;
	}

	delete temp;
	this->size--;
}

template <typename T>
T Queue<T>::front() {
	return this->head->data;
}

template <typename T>
bool Queue<T>::empty() {
	return this->size == 0;
}

template <typename T>
Queue<T>::~Queue() {
	while (this->size != 0) {
		this->pop();
	}
}
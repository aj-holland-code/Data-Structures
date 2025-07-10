// Queue
// -----
// 
// This is a C++ implementation of a queue.
// This is a a template class that wraps around my custom doubly linked list class, 
// as the Stack class does. 
// The special member functions are also defaulted as per Stack.

#ifndef QUEUE_H
#define	QUEUE_H

#include "..\Doubly_Linked_List\Doubly_Linked_List.h"

class RuntimeException2 {
public:
	RuntimeException2(const std::string& err) { errorMsg = err; }
	std::string getMessage() const { return errorMsg; }
private:
	std::string errorMsg;
};


class QueueEmptyException : public RuntimeException2 {
public:
	QueueEmptyException(const std::string& err) : RuntimeException2(err) {}
};


template <typename T>
class Queue {
public:
	Queue() = default;
	Queue(T elem)  { enqueue(elem); }
	Queue(const Queue& other) = default;
	Queue(Queue&& other) = default;
	Queue& operator=(const Queue& other) = default;
	Queue& operator=(Queue&& other) = default;
	
	int size() { return list.getSize(); }
	bool isEmpty() { return (size() == 0); }
	void enqueue(T elem);
	std::optional<T> dequeue();
	std::optional<T> front();
	std::optional<T> back();
private:
	DoublyLinkedList<T>	list;
};


// Member Function Definitions
// ===========================

// Adds the element onto the back of the queue.
template <typename T>
void Queue<T>::enqueue(T elem) {
	list.insertAtTail(elem);
}


// Removes the element at the head of the queue.
template <typename T>
std::optional<T> Queue<T>::dequeue() {
	if (isEmpty())
		throw QueueEmptyException("Queue is empty");
	list.removeFirst();
}


// Returns the element at the front of the queue.
template<class T>
std::optional<T> Queue<T>::front() {
	return list.peekFirst();
}


// Returns the element at the rear of the queue.
template<class T>
std::optional<T> Queue<T>::back() {
	return list.peekLast();
}


#endif	// QUEUE_H
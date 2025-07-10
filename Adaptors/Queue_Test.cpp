// Queue
// -----
// 
// See YouTube video "Data Structures Easy to Advanced Course - Full Tutorial from a Google Engineer"
// for an illustrated explanation on queues: https://youtu.be/RBSGKlAvoiM
// 
// The notes below are taken from the video.
// 
// Notes on Queues
// ---------------
// 
// A queue is a linear data structure that models real world queues through
// two primary operations; enqueue (aka adding, offering) and dequeue (aka
// polling, removing).
// 
// Queues are used:
// 1) To efficiently keep track of the x most recently added elements.
// 2) In web server request management to enable a first come, first served
//    approach.
// 3) In Breadth First Search (BFS) graph traversal.
// 
// A queue is usually a container adapter, implemented by an array or a 
// (singly or doubly) linked list.
//
// 
// Time Complexity of Operations
// -----------------------------
// 
// Enqueue				O(1)
// Dequeue				O(1)
// Peeking				O(1)
// Is Empty				O(1)
// Contains				O(n)
// Removal				O(n) 
//
// Special Member Functions
// ------------------------
//
// This class uses the same doubly linked list for the underlying structure as the 
// Stack class. The Stack special member functions have been tested thoroughly, so
// there doesn't seem much value in repeating what are essentially the same tests
// here.

#include <iomanip>
#include <iostream>

#include "Queue.h"

int main() {
	std::cout << std::boolalpha;

	// 1. Test a queue with the default constructor
	std::cout << "(1) Test queue using the default constructor...\n";
	Queue<int> q1;
	std::optional<int> frontElem;
	std::optional<int> backElem;
	
	std::cout << "Is q1 empty:  " << q1.isEmpty() << '\n';
	std::cout << "Is q1.size(): " << q1.size() << '\n';

	// Enqueue elements
	for (int i = 0; i < 11; i++)
		q1.enqueue(i);

	// Access/dequeue elements
	std::cout << "\nAccess contents of the queue:\n";
	for (int i = 0; i < 12; i++) {
		try {
			std::cout << "Iteration      " << i << '\n';

			frontElem = q1.front();
			if (!frontElem.has_value())
				std::cout << "No front element!\n";
			else
				std::cout << "Front element: " << frontElem.value() << '\n';

			backElem = q1.back();
			if (!backElem.has_value())
				std::cout << "No back element!\n";
			else
				std::cout << "Back element:  " << backElem.value() << '\n';

			std::cout << "Is q1 empty:   " << q1.isEmpty() << '\n';
			std::cout << "Is q1.size():  " << q1.size() << "\n\n";
			q1.dequeue();
		}
		catch (QueueEmptyException& qe) {
			std::cout << '\n' << qe.getMessage() << '\n';
		}
	}
	
	/************************************************************************/

	// 2. Test a queue using the converting constructor
	std::cout << "\n\n(2) Test converting constructor...\n";
	Queue<int> q2(1000);
	std::cout << std::boolalpha;
	std::cout << "Is q2 empty:  " << q2.isEmpty() << '\n';
	std::cout << "Is q2.size(): " << q2.size() << '\n';

	// Enqueue elements
	for (int i = 900; i >= 0; i -= 100)
		q2.enqueue(i);

	// Access/dequeue elements
	std::cout << "\nAccess contents of the queue:\n";
	for (int i = 0; i < 12; i++) {
		try {
			std::cout << "Iteration      " << i << '\n';

			frontElem = q2.front();
			if (!frontElem.has_value())
				std::cout << "No front element!\n";
			else
				std::cout << "Front element: " << frontElem.value() << '\n';

			backElem = q2.back();
			if (!backElem.has_value())
				std::cout << "No back element!\n";
			else
				std::cout << "Back element:  " << backElem.value() << '\n';

			std::cout << "Is q2 empty:   " << q2.isEmpty() << '\n';
			std::cout << "Is q2.size():  " << q2.size() << "\n\n";
			q2.dequeue();
		}
		catch (QueueEmptyException& qe) {
			std::cout << '\n' << qe.getMessage() << '\n';
		}
	}	
}
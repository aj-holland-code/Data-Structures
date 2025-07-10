// Stack
// -----
// 
// This is a C++ implementation of a stack. It is a template class, with a full specialisation
// for doubles (this is to illustrate how that works on a class with small code footprint, 
// rather than due to any compelling reason to have a stack double specialisation).
// 
// 
// The Special Member Functions
// ----------------------------
// 
// The defaults for the special member functions are sufficient (marked as default to make this clear).
// The underlying structure (my own doubly linked list class) has robust solutions for copy and move
// operations, taking care of any memory requirements there, so in this class it is 
// simply a case of the member list being copied or moved, which the compiler can handle automatically.

#ifndef STACK_H
#define	STACK_H

#include "..\Doubly_Linked_List\Doubly_Linked_List.h"

class StackEmptyException : public std::runtime_error {
public:
	StackEmptyException(const std::string& err) : std::runtime_error(err) {}
};


template <typename T>
class Stack {
public:
	Stack();
	Stack(T elem);
	Stack(const Stack& other) = default;
	Stack(Stack&& other) noexcept = default;
	Stack& operator=(const Stack& other) = default;
	Stack& operator=(Stack&& other) noexcept = default;
	~Stack() = default;

	int size();
	bool isEmpty();
	void push(T elem);
	std::optional<T> pop();
	std::optional<T> top();
private:
	DoublyLinkedList<T> m_list;
};


// Member Function Definitions
// ===========================

// Default constructor.
template <typename T>
Stack<T>::Stack() {}


// Converting constructor - creates a new Stack containing the element passed in.
template <typename T>
Stack<T>::Stack(T elem) {
	push(elem);
}


// Returns the current size of the stack.
template <typename T>
int Stack<T>::size() {
	return m_list.getSize();
}


// Returns true if the stack is currently empty, otherwise false.
template <typename T>
bool Stack<T>::isEmpty() {
	return (size() == 0);
}


// Pushes an element onto the stack.
template <typename T>
void Stack<T>::push(T elem) {
	return m_list.insertAtTail(elem);
}


// Pops the top element off the stack.
// Returns null if list is empty.
template <typename T>
std::optional<T> Stack<T>::pop() {
	return m_list.removeLast();
}


// Returns a reference to the top element of the stack, 
// but does NOT remove it from the stack.
// Returns null if list is empty.
template <typename T>
std::optional<T> Stack<T>::top() {
	return m_list.peekLast();
}

/************************************************************************************************/
/**************************** CLASS TEMPLATE SPECIALISATION *************************************/

// Specialisation for doubles.
// There isn't any real need for this, since doubles don't need any special treatment here and so
// the functionality is exactly the same as the main template.
// But a full example of a class template specialisation of a data structure is helpful to show how it works.
template <>
class Stack<double> {
public:
	Stack() {}
	Stack(double elem);
	int size();
	bool isEmpty();
	void push(double elem);
	std::optional<double> pop();
	std::optional<double> top();
private:
	DoublyLinkedList<double> m_list;
};


// METHOD DEFINITIONS

// Creates a stack for double values with an initial element.
Stack<double>::Stack(double elem) {
	push(elem);
}


// Returns the current size of the stack.
int Stack<double>::size() {
	return m_list.getSize();
}


// Returns true if the stack is currently empty, otherwise false.
bool Stack<double>::isEmpty() {
	return (m_list.getSize() == 0);
}


// Pushes an element onto the stack.
void Stack<double>::push(double elem) {
	return m_list.insertAtTail(elem);
}


// Pops the top element off the stack.
// Returns null if list is empty.
std::optional<double> Stack<double>::pop() {
	return m_list.removeLast();
}


// Returns a reference to the top element of the stack, 
// but does NOT remove it from the stack.
// Returns null if list is empty.
std::optional<double> Stack<double>::top() {
	return m_list.peekLast();
}


#endif  // STACK_H
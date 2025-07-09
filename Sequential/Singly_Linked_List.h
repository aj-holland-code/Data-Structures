// Singly Linked List
// ------------------
// 
//
// The Special Member Functions
// ----------------------------
// 
// Copy constructor - traverse the source list one node at a time, copying the data
// across to this list.
// 
// Move constructor - this list takes over ownership of the source list and sets
// the copy list to null.
// 
// Copy assignment operator - uses the copy-and-swap idiom, since this is safe
// (and fairly simple).
// 
// Move assignment operator - this uses the move variant of the copy-and-swap idiom
// (the move-and-swap idiom?) for the same reasons - safety and simplicity.
// 
// 
// Future Improvements/To-Do List
// ------------------------------
// 
// 1. Add iterators.
// 2. A merge function (merging another list into this one) would be a good one 
//    to add.
// 3. Add a sort function. The doubly linked list implementation has got a
//    sort function added to the public interface, so it would not be too
//    difficult to add a similar version for this class.

#ifndef SINGLY_LINKED_LIST_H
#define SINGLY_LINKED_LIST_H

#include <initializer_list>
#include <optional>
#include <utility>				// For std::exchange


// Define the Node class to hold the data.
template <typename T>
class Node {
public:
	Node(T data) : m_data{ data } { }
	T m_data;
	Node<T>* next = nullptr;
};


// The template for the singly linked list class.
template <typename T>
class SinglyLinkedList {
public:	
	SinglyLinkedList() = default;
	SinglyLinkedList<T>(std::initializer_list<T> ilist);
	SinglyLinkedList(const SinglyLinkedList& other);
	SinglyLinkedList(SinglyLinkedList&& other) noexcept;
	SinglyLinkedList& operator=(const SinglyLinkedList& other);
	SinglyLinkedList& operator=(SinglyLinkedList&& other) noexcept;
	~SinglyLinkedList();

	void clear();
	bool isEmpty() { return getSize() == 0; }
	int getSize() { return size; }
	std::optional<int> deleteAt(unsigned int pos);
	void insert(T elem);
	void insertAtHead(T elem);
	void insertAtTail(T elem);
	std::optional<int> insertAt(T elem, unsigned int pos);
	std::optional<T> peekFirst();
	std::optional<T> peekLast();
	void printList();
	void printListRecursive();
	void reverseList();	
private:
	void swap(SinglyLinkedList& other);
	Node<T>* getNewNode(T elem);
	void insertAtPos(T elem, unsigned int pos);
	void print();
	void printForwards(Node<T>* node);
	void printReverse(Node<T>* node);
	void reverseListIterative();
	void reverseListRecursive(Node<T>* current);
private:	
	int size = 0;
	Node<T>* head = nullptr;
	Node<T>* tail = nullptr;
};

/********************************************************************************************/
/*************************** Member Function Definitions ************************************/

// Special Member Functions
// ------------------------

// std::initializer_list constructor
template<typename T>
SinglyLinkedList<T>::SinglyLinkedList(std::initializer_list<T> ilist) {
	typename std::initializer_list<T>::iterator it = ilist.begin();
	for (; it != ilist.end(); it++)
		insert(*it);
}


// Copy constructor
template<typename T>
SinglyLinkedList<T>::SinglyLinkedList(const SinglyLinkedList& other) {
	Node<T>* currentOther = other.head;	    // Node used to traverse other list

	while (currentOther) {
		insertAtTail(currentOther->m_data);	// Copy from other list into this
		currentOther = currentOther->next;  // Move to next node in other
	}
}


// Move constructor
template<typename T>
SinglyLinkedList<T>::SinglyLinkedList(SinglyLinkedList&& other) noexcept :
	size{ std::exchange(other.size, {}) },
	head{ std::exchange(other.head, {}) }, 
	tail{ std::exchange(other.tail, {}) }
{ }


// Copy assignment operator
template <typename T>
SinglyLinkedList<T>& SinglyLinkedList<T>::operator=(const SinglyLinkedList& other) {
	SinglyLinkedList<T> temp(other); // Element-wise copy of the contents of other
	swap(temp);		// swap this and temp object's contents
	return *this;	// this is now a deep copy of other
}	// temp destroyed - the list previously associated with this object is deallocated


// Move assignment operator
template <typename T>
SinglyLinkedList<T>& SinglyLinkedList<T>::operator=(SinglyLinkedList&& other) noexcept {
	SinglyLinkedList<T> temp(std::move(other)); // temp assumes ownership of other
	swap(temp);		// swap this and temp's contents
	return *this;	// this has now assumed ownership of list previously owned by other
}   // temp destroyed - list previously associated with this is deallocated


// Private swap utility function.
// This object takes over the list in the temporary object (which want to keep).
// The temporary object takes over the list in this object (which we want to delete).
template <typename T>
void SinglyLinkedList<T>::swap(SinglyLinkedList& other) {
	using std::swap;

	// We definitely want to swap the head and tail pointers, since the memory
	// currently associated with this list needs to be deallocated in the destructor
	// when it runs for other (temp in the assignment operator itself), and that 
	// needs to know the bounds of the list to deallocate no more and no less than
	// all the nodes currently in the list.
	// 
	// Therefore use std::swap for these fields. The size of this list is no longer needed
	// once it assumes the size of the other list, so we could use std::exchange to zero 
	// it out instead of swapping this list's size into it, but it doesn't seems worth
	// making this a special case here, since it will be zeroed out in the destructor
	// anyway (via the clear() function). 
	swap(size, other.size);
	swap(head, other.head);
	swap(tail, other.tail);
}


// Destructor
template <typename T>
SinglyLinkedList<T>::~SinglyLinkedList() {
	clear();
}

/******************************************************************************/

// Other Member Functions
// ----------------------

// Removes all nodes from the list.
// Leaves the list in an empty but valid state.
template<typename T>
void SinglyLinkedList<T>::clear() {
	Node<T>* current = head;

	while (current) {
		Node<T>* next = current->next;
		delete current;
		current = nullptr;
		current = next;
	}
	size = 0;				// Reset the size
	head = tail = nullptr;	// Reset the head and tail pointers
}

// Deletes an existing node at pos -- if pos is a valid position given 
// the current state of the list.
// Returns position of deleted element, or null if no deletion takes place.
template<typename T>
std::optional<int> SinglyLinkedList<T>::deleteAt(unsigned int pos) {
	// Invalid position - return null without deleting anything
	if (pos == 0 || pos > size)
		return {};

	// Delete the head node (special case)
	if (pos == 1) {		
		// Set a pointer to current second element, 
		// or null if head is the only node.
		Node<T>* next = head->next;
		delete head;	// Delete memory for head node
		head = next;	// Old second element (or null) becomes new head
	}
	else {
		// All other cases require traversing list to find element
		// prior to the one to be deleted
		int current_pos = 1;
		Node<T>* prev = head;

		while (current_pos < pos - 1) {
			prev = prev->next;
			current_pos++;
		}

		// prev should now be pointing to node before to-be-deleted node
		// Set current to point to the to-be-deleted node
		Node<T>* current = prev->next;

		// Set before node's next to point to node after current
		prev->next = current->next;

		delete current;		// Delete the relevant node		

		if (pos == size)
			// Reset tail if it's the old tail node that's been deleted
			tail = prev;
	}
	size--;	// Decrement size to reflect delete
	return pos;
}


// Inserts a new node at the tail of the list.
template<typename T>
void SinglyLinkedList<T>::insert(T elem) {
	insertAtTail(elem);
}


// Inserts a new node at the head of the list.
template<typename T>
void SinglyLinkedList<T>::insertAtHead(T elem) {
	Node<T>* newNode = getNewNode(elem);

	if (isEmpty())
		head = tail = newNode;
	else {
		newNode->next = head;
		head = newNode;
	}
	size++;		// Make sure size is updated
}


// Inserts a new node at the tail of the list.
template<typename T>
void SinglyLinkedList<T>::insertAtTail(T elem) {
	Node<T>* newNode = getNewNode(elem);

	if (isEmpty())
		head = tail = newNode;
	else {
		tail->next = newNode;
		tail = newNode;
	}
	size++;		// Make sure size is updated
}


// Inserts a new node at the pos -- if pos is a valid position given 
// the current state of the list.
template<typename T>
std::optional<int> SinglyLinkedList<T>::insertAt(T elem, unsigned int pos) {
	// Invalid position:
	// Lowest valid input position is 1 as list starts at 1.
	// Highest valid input position is size + 1 (to become new tail).
	// No insert performed - return null.
	if (pos > size + 1 || pos == 0)
		return {};

	// Otherwise insert is valid.
	// Insert at head if first position specified.
	if (pos == 1)
		insertAtHead(elem);

	// Insert at tail if position beyond current tail specified.
	else if (pos == size + 1)
		insertAtTail(elem);
	else
		// Insert elements in the middle of the list somewhere
		insertAtPos(elem, pos);
	return pos;
}



// Check the value of the last node -- O(1)
// Returns null for an empty list.
template<typename T>
std::optional<T> SinglyLinkedList<T>::peekFirst() {
	if (head)
		return head->m_data;
	else
		return {};
}


// Check the value of the last node -- O(1)
// Returns the value or null if the list is empty.
template<typename T>
std::optional<T> SinglyLinkedList<T>::peekLast() {
	if (tail)
		return tail->m_data;
	else
		return {};
}


// Prints the data in the list in head-to-tail order.
template<typename T>
void SinglyLinkedList<T>::printList() {
	Node<T>* current = head;

	while (current) {
		std::cout << current->m_data << " ";
		current = current->next;
	}
	std::cout << "\n\n";
}


// Recursive print method.
template<typename T>
void SinglyLinkedList<T>::printListRecursive() {
	print();
}


// Reverses the nodes of the list. 
// The logic works, without special cases, for lists of 0-n nodes in length.
// This is a wrapper method that dispatches the work to a utility method;
// we have the option of plugging in whichever logical approach to the 
// problem we wish.
template<typename T>
void SinglyLinkedList<T>::reverseList() {
	reverseListIterative();
	//reverseListRecursive(head);
}


/**************************************************************************/

// Private Function Declarations
// -----------------------------


// Utility method that creates a new Node on the heap and 
// returns the pointer to the node.
template<typename T>
Node<T>* SinglyLinkedList<T>::getNewNode(T elem) {
	Node<T>* newNode = new Node(elem);
	return newNode;
}


// Utility method that inserts a new node at the pos - a valid
// position that is found somewhere in the middle of the list.
template<typename T>
void SinglyLinkedList<T>::insertAtPos(T elem, unsigned int pos) {
	int current_pos = 1;
	Node<T>* current = head;

	// Traverse until element immediately prior to input position found
	while (current && current_pos < pos - 1) {
		current = current->next;
		current_pos++;
	}

	// current now points to element prior to where insert should be
	// Now store the address of the element that will come after
	// the newly inserted element.
	// If the element is going where the existing tail is, we need
	// to make sure its next pointer is correctly handled as it will
	// be pointing to null.
	Node<T>* next = nullptr;

	// This function is only called on lists with two or more elements
	// and where the insertion is not at the head or tail position.
	// This means the current pointer here is never advanced further than the 
	// penultimate element, and therefore will always be pointing to a 
	// valid node itself and its next pointer will always be pointing to
	// a valid node.
	// Consequently, this test is redundant, but it is added to silence
	// the compiler warning about a possible null pointer dereference.
	if (current && current->next)
		next = current->next;

	Node<T>* newNode = getNewNode(elem);	// Create new node

	// Hook up pointers to and from the new node
	current->next = newNode;
	newNode->next = next;

	// Finally, increment the size to reflect addition of a new node
	size++;
}


// Calls one of two recursive print functions
// that print the forwards or backwards.
template<typename T>
void SinglyLinkedList<T>::print() {
	// We can tweak here which version of the function to call
	printForwards(head);
	printReverse(head);
}



// Recursive private function that prints the list in first-node-to-last order.
// This approach avoids having to make head pointer public in this class.
// 
// Call this passing in the head node to start. It prints the node data first,
// and the moves to next node, and continuing until the end of the list.
// This ensures the data is printed in the head to tail node order.
template<typename T>
void SinglyLinkedList<T>::printForwards(Node<T>* node) {
	if (!node) {
		// Reached the end of the list
		std::cout << '\n';
		return;
	}

	// Print then call function
	std::cout << node->m_data << " ";
	printForwards(node->next);
}


// Recursive print function that prints the list in
// reverse order.
//
// Pass in node (usually the head). The recursive function call
// happens first, continuing with each node until reaching
// the end of the list. 
// 
// The printing happens on the stack unwinding, so this ensures
// the print order is tail to head.
template<typename T>
void SinglyLinkedList<T>::printReverse(Node<T>* node) {
	// Call private method to do the actual work.
	// This approach avoids having to make head pointer public in this class.
	if (!node)
		// Reached the end of the list
		return;

	// Call function then print
	printReverse(node->next);
	std::cout << node->m_data << " ";

	// Back at head - print new line to finish
	if (node == head)
		std::cout << '\n';
}

// Utility method that reverses the list iteratively.
template<typename T>
void SinglyLinkedList<T>::reverseListIterative() {
	Node<T>* curr = head;
	Node<T>* next = nullptr;
	Node<T>* prev = nullptr;

	// Traverse list one node at a time, rewiring the link on each as we go.
	while (curr) {
		next = curr->next;	// Store the address of the next node
		curr->next = prev;	// Rewire the curr node to point to prev node
		prev = curr;		// Advance prev to curr node
		curr = next;		// Advance curr to next node
	}

	// All links now reversed - all that's left is to tidy up head & tail.
	tail = head;	// Previous head is now tail
	head = prev;	// Previous tail (address stored in prev) is now head
}


// Utility method that reverses the list recursively.
template<typename T>
void SinglyLinkedList<T>::reverseListRecursive(Node<T>* current) {
	if (!current || !current->next) {
		// Exit condition
		// No current element (empty list) or
		// No next element (end of populated list reached)
		tail = head;	// Reset tail of list (previously the head)
		head = current;	// Reset head of list (previously the tail)
		return;
	}

	reverseListRecursive(current->next);
	Node<T>* next = current->next;
	next->next = current;
	current->next = nullptr;
}


#endif // End of SINGLY_LINKED_LIST_H

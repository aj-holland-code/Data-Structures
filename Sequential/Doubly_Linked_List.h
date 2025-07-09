// Doubly Linked List
// ------------------
// 
// This is a C++ implementation of a doubly linked list. As with the dynamic array class,
// some of the logic is based on the Java doubly linked list class demonstrated by 
// William Fiset in his YouTube data structures course video 
// (see the test file for more details).
// 
// However, I've also made this a template class, as with the dynamic array, and there 
// is also a considerable amount of extra functionality added (including iterative and 
// recursive versions of some functions).
// 
// The functions are well commented in the code itself, so in most cases additional
// analysis here is not really necessary, but there is some for cases where I 
// feel extra discussion is warranted.
// 
// Same rationale for using raw pointers as in the dynamic array class. Using them
// can be quite painful in some instances; avoiding memory leaks in the special
// member functions can be especially awkward, since the memory required for a 
// list cannot be allocated or deallocated in one large chunk, as it can be for a
// dynamic array. Instead it is a series of chunks of a single node in size, which 
// is more fiddly.
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
// Copy assignment operator - cppreference states that in the copy assignment operator
// for std::list (a bidirectional list) "memory owned by *this may be reused when 
// possible." 
// 
// I did experiment with trying to reuse the memory currently allocated to this object
// where possible, but it makes the function more complicated. I've currently gone with
// the copy-and-swap approach again here, as in the dynamic array, since it makes matters
// simpler and safer.
// 
// Move assignment operator - this uses the move equivalent of the copy-and-swap idiom
// (the move-and-swap idiom?) for the same reasons - safety and simplicity.
// 
// The Sort Function
// -----------------
// 
// My general approach in these data structures is to try to refrain from using standard
// library functions and algorithms where possible, so that opportunities to think 
// through the logic and write the code necessary to achieve the results required
// are maximised. However, in this case I've circumvented that and fallen back on 
// using standard sort.
// 
// Potentially, the most efficient way to accomplish sorting a list is to copy the
// elements sequentially into a vector, use the library sort to do the sorting, 
// and then copy the sorted elements sequentially back into the list, 
// so this is what I've done.
// 
// An acknowledgement here to Amir Kirsh & Adam Segoli Schubert for the idea to use
// a vector/standard sort to sort a list, as suggested in their CPPCon 2021 presentation
// Back to Basics: Algorithmic Complexity.
// 
// It might be possible to develop a solution that instead traverses the list and 
// swaps elements around to ultimately sort it, but it would most likely be less
// efficient than doing it the way previously described, so it feels like it would be
// a lot of pain for not much reward, hence I've adopted the "library approach" instead.
// 
// 
// Future Improvements/To-Do List
// ------------------------------
// 
// 1. Iterators would be useful.
// 2. The print() function should really be replaced, or at least called by, an 
//    overloaded stream output operator, particularly in the absence of iterators.
// 3. A swap function that swaps two elements in the list by reordering the nodes
//    rather than copying the data could be useful. For cheap-to-copy types like int, 
//    it seems like an academic exercise, but it may actually be useful for
//    more expensive-to-copy types (although there is no function like this on
//    the public interface of std::list).
// 4. Use smart pointers to take care of memory handling.

#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include <algorithm>
#include <iostream>
#include <optional>
#include <stdexcept>
#include <type_traits>
#include <vector>

// Template for classes to store doubly linked list nodes.
template <typename T>
class Node {
public:
	Node(T data) : data{ data } {}
	T data;
	Node<T>* prev = nullptr;
	Node<T>* next = nullptr;
};


// The template for the doubly linked list class.
template<typename T>
class DoublyLinkedList {
public:
	DoublyLinkedList() = default;
	DoublyLinkedList(const DoublyLinkedList& other);
	DoublyLinkedList(DoublyLinkedList&& other) noexcept;
	DoublyLinkedList& operator=(const DoublyLinkedList& other);
	DoublyLinkedList& operator=(DoublyLinkedList&& other) noexcept;
	~DoublyLinkedList();

	int getSize() { return size; }
	bool contains(Node<T> node) { return indexOf(node) != -1; }
	bool isEmpty() { return (getSize() == 0); }

	void clear();
	Node<T>* getOriginalListHead();
	Node<T>* getOriginalListTail();
	void setOriginalListHead();
	void setOriginalListTail();
	void insert(T data);
	void insertAtHead(T data);
	void insertAtTail(T data);
	void merge(DoublyLinkedList<T>& other_list);
	std::optional<T> peekFirst();
	std::optional<T> peekLast();
	std::optional<T> removeAt(int index);
	std::optional<T> removeFirst();
	std::optional<T> removeLast();
	int indexOf(T data);
	void reverseList();
	void sort();
	void printList();
private:
	void swap(DoublyLinkedList& other);
	Node<T>* getNewNode(T elem);
	std::optional<T> removeNode(Node<T>* node);
	void reverseListIterative();
	void reverseListRecursive(Node<T>* node);
	void printListIterative();
	void printListReverse();
	void printListRecursive(Node<T>* node);

	int size = 0;
	Node<T>* head = nullptr;
	Node<T>* tail = nullptr;

	// These are special variables purely used for internal testing of the merge functionality
	Node<T>* original_head = nullptr;
	Node<T>* original_tail = nullptr;
};

/********************************************************************************************/
/*************************** Member Function Definitions ************************************/

// Special Member Functions
// ------------------------

// Copy constructor
template <typename T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList& other) {
	// Traverses the list in the copy object; holds link to current node to be copied.
	Node<T>* currentOther = other.head;

	// Copy contents from each node in other into this list.
	while (currentOther) {
		insertAtTail(currentOther->data);
		currentOther = currentOther->next;	// Move to next node in other list
	}
}

// Move constructor
template <typename T>
DoublyLinkedList<T>::DoublyLinkedList(DoublyLinkedList&& other) noexcept :
	size{ std::exchange(other.size, {}) },
	head{ std::exchange(other.head, {}) },
	tail{ std::exchange(other.tail, {}) }
{ }

// Copy assignment operator
template <typename T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(const DoublyLinkedList& other) {
	DoublyLinkedList<T> temp(other); // Element-wise copy of the contents of other
	swap(temp);		// swap this and temp object's contents
	return *this;	// this is now a deep copy of other
}	// temp destroyed - the list previously associated with this object is deallocated


// Move assignment operator
template <typename T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(DoublyLinkedList&& other) noexcept {
	DoublyLinkedList<T> temp(std::move(other));	 // temp assumes ownership of other's contents
	swap(temp);		// swap this and temp's contents
	return *this;	// this has now assumed ownership of list previously owned by other
}   // temp destroyed - list previously associated with this is deallocated


// Swap function.
// This object takes over the list in the temporary object (which want to keep).
// The temporary object takes over the list in this object (which we want to delete).
template <typename T>
void DoublyLinkedList<T>::swap(DoublyLinkedList& other) {
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
	swap(this->size, other.size);
	swap(this->head, other.head);
	swap(this->tail, other.tail);	
}


// Destructor 
template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
	clear();
}

// Other Member Functions
// ----------------------

// Remove all the elements of this list -- O(n).
// Steps through the list from head to tail, freeing up the memory allocated
// to each node as it goes.
template <typename T>
void DoublyLinkedList<T>::clear() {
	Node<T>* current = head;
	int nodes{};

	while (current) {						// Traverse from head to tail of list
		nodes++;
		Node<T>* next = current->next;		// Store address of next element
		current->prev = nullptr;
		current->next = nullptr;
		delete current;						// Delete current element
		current = next;						// Move to next element
	}

	std::cout << "Deleted " << nodes << " nodes in clear()...\n";
	head = tail = nullptr;		// Set head and tail to null
	size = 0;					// Reset size to 0
}


// Insert new element at the end of this list -- O(1)
template <typename T>
void DoublyLinkedList<T>::insert(T data) {
	insertAtTail(data);
}


// Creates a new node on the heap and returns a pointer to it.
template <typename T>
Node<T>* DoublyLinkedList<T>::getNewNode(T data) {
	Node<T>* newNode = new Node(data); // Create new node using data
	return newNode;
}


// Insert new element at the head of this list -- O(1).
template <typename T>
void DoublyLinkedList<T>::insertAtHead(T data) {
	Node<T>* newNode = getNewNode(data);

	if (isEmpty())
		head = tail = newNode;	// If list empty, new node is head and tail
	else {
		// Otherwise, update head node to be the new node and wire it up to the existing list
		newNode->next = head;	// Point new node next to current head
		head->prev = newNode;	// Set current head prev to new node
		head = newNode;			// Update head to be the new node
	}
	size++;						// Increment size
}


// Insert new element at the end of this list -- O(1)
template <typename T>
void DoublyLinkedList<T>::insertAtTail(T data) {
	Node<T>* newNode = getNewNode(data);

	if (isEmpty())
		head = tail = newNode;	// If list empty, new node is head and tail
	else {
		// Otherwise, update tail node to be the new node and wire it up to the existing list
		newNode->prev = tail;	// Point new node prev to current tail
		tail->next = newNode;	// Set current tail next to new node
		tail = newNode;			// Update tail to be the new node
	}
	size++;						// Increment size
}



// Returns the data from the first node, or null if list empty -- O(1)
template <typename T>
std::optional<T> DoublyLinkedList<T>::peekFirst() {
	if (isEmpty())
		return {};
	return head->data;
}


// Returns the data from the last node, or null if list empty -- O(1)
template <typename T>
std::optional<T> DoublyLinkedList<T>::peekLast() {
	if (isEmpty())
		return {};
	return tail->data;
}


// Removes and returns the first value at the head of the linked list
// if there is one; otherwise does nothing and returns null -- O(1)
template <typename T>
std::optional<T> DoublyLinkedList<T>::removeFirst() {
	if (isEmpty())
		return {};

	T first = head->data;			// Save data from first node
	Node<T>* newHead = head->next;  // Save the new head location (current second node)
	delete head;				    // Remove the existing head
	head = newHead;					// Set head to the new head location
	--size;							// Update the list size

	if (isEmpty())
		tail = nullptr;				// Set tail to null if list now empty
	else
		head->prev = nullptr;		// Else set prev of head to null 

	return first;
}


// Removes and returns the last value at the tail of the linked list
// if there is one; otherwise does nothing and returns null -- O(1)
template <typename T>
std::optional<T> DoublyLinkedList<T>::removeLast() {
	if (isEmpty())
		return {};

	T last = tail->data;					 // Save data from last node
	Node<T>* newTail = tail->prev;			 // Save the new tail location
	delete tail;							 // Remove the existing tail
	tail = newTail;							 // Set the new tail location
	--size;									 // Update the list size

	if (isEmpty())
		head = nullptr;						 // Set head to null if list now empty
	else
		tail->next = nullptr;				 // Else set next of tail to null 

	return last;
}


// Removes and returns the node in the list at the index specified.
// If the index is invalid, no action is taken and a null
// value is returned.
//
// If the node to be removed is head or tail, call the specialist method
// that handles that removal -- O(1).
// 
// Otherwise we have to track down the node in the middle of the list -- O(n)
// 
// There is a slightly more sophisticated method to identifying the node than a simple
// linear search from head to tail. 
// First, whether the index is in the first or second half of the list is determined. 
// If it's in the first half of the list, the search starts at the second index and
// moves forward (we already know it is not the head node, so that can be ignored).
// Or if it's in the second half of the list, the search starts at the penultimate node
// and moves backward (we already know it is not the tail node, so that can be ignored). 
template <typename T>
std::optional<T> DoublyLinkedList<T>::removeAt(int index) {
	// Return null for an empty list, or if the index is invalid
	if (isEmpty() || index < 1 || index > size)
		return {};

	if (index == 1)			// Remove head node
		return removeFirst();

	if (index == getSize())	// Remove tail node
		return removeLast();

	// Otherwise we have a valid index somewhere in the middle of the list.
	int currentIndex{};
	Node<T>* current = nullptr;

	if (index <= (size / 2)) {
		// index is in the front half of the list
		// Start from second node & work forwards until found
		current = head->next;
		currentIndex = 2;
		while (current && currentIndex < index) {
			current = current->next;
			currentIndex++;
		}
	}
	else {
		// index is in the back half of the list
		// Start from penultimate node & work backwards until found
		current = tail->prev;
		currentIndex = size - 1;
		while (current && currentIndex > index) {
			current = current->prev;
			currentIndex--;
		}
	}
	// Current should now be pointing to the correct node to be removed
	return removeNode(current);
}


// Utility method that removes a node from the list -- O(1)
template<typename T>
std::optional<T> DoublyLinkedList<T>::removeNode(Node<T>* node) {
	T data = node->data;			// Store data to be deleted

	// Set previous node next to point to node following this one
	node->prev->next = node->next;

	// Set next node prev to point to node preceding this one
	node->next->prev = node->prev;
	delete node;					// Delete this node
	size--;							// Decrease list size by one
	return data;					// Return the data deleted from the list
}


// Find the index of a particular value in the linked list -- O(n)
template<typename T>
int DoublyLinkedList<T>::indexOf(T data) {
	int index = 1;
	Node<T>* current = head;

	// Search for a null data item - safe for non-arithmetic types only.
	// A bit messy here as a zero integral element is not a null element
	// but would meet the !data condition, and we don't want to drop into
	// this branch of the code for that situation.
	if (!data && !(std::is_arithmetic<T>::value)) {
		while (current) {
			if (!current->data)
				return index;	// Return index of first null element found.
			index++;
			current = current->next;
		}
	}
	// Search for a non-null data item - safe for both arithmetic & non-arithmetic types.
	else {
		while (current) {
			if (data == current->data)
				return index;
			index++;
			current = current->next;
		}
	}
	return -1;
}


// Reverses the order of the nodes of the list -- O(n)
// 
// The logic works, without special cases, for lists of 0-n nodes in length.
// This is a wrapper method that dispatches the work to a utility method;
// we have the option of plugging in whichever logical approach to the 
// problem we wish.
template<typename T>
void DoublyLinkedList<T>::reverseList() {
	//reverseListIterative();
	reverseListRecursive(tail);
}


// Utility method that reverses the list iteratively.
template<typename T>
void DoublyLinkedList<T>::reverseListIterative() {
	// Walk through list from tail to head, rewiring each node on the way
	Node<T>* prev = nullptr;
	Node<T>* current = tail;

	while (current) {
		current->next = current->prev;		// Previous node becomes next node
		current->prev = prev;				// Next node becomes previous node
		prev = current;						// Move prev back one node
		current = current->next;			// Move current back one node
	}

	// Head and tail are swapped
	Node<T>* temp = head;
	head = tail;
	tail = temp;
}


// Utility method that reverses the list recursively.
template<typename T>
void DoublyLinkedList<T>::reverseListRecursive(Node<T>* node) {
	if (!node)		// Base case
		return;

	// Otherwise, swap the next and previous
	Node<T>* temp = node->next;
	node->next = node->prev;
	node->prev = temp;

	// If node next is now null, the list is fully reversed
	if (!node->next) {
		// Swap head and tail
		temp = head;
		head = tail;
		tail = temp;
	}

	// Otherwise keep going
	reverseListRecursive(node->next);
}

// Sorts the list into ascending order.
template<typename T>
void DoublyLinkedList<T>::sort() {
	std::vector<T> v1(size);	// Create a vector large enough to store list contents
	Node<T>* current = head;	// Set a pointer to the beginning of the list
	int count = 0;				// Create and initialise a counter variable (for vector)

	// Step 1: copy list contents to a vector
	while (current) {						// Traverse loop from beginning to end
		v1[count++] = current->data;		// Add current element to vector
		current = current->next;			// Move to next element in the list
	}

	// Step 2: Sort the vector
	std::sort(v1.begin(), v1.end());

	// Step 3: Copy the elements back in sorted order in the list
	current = head;							// Reset point to the beginning of the list
	count = 0;								// Reset counter to zero

	while (current) {
		current->data = v1[count++];		// Copy element into list element + increment counter
		current = current->next;			// Move to next element in the list		
	}
}

// Takes a reference to other_list and merges its contents with this list.
// For this function to work effectively this list and other_list must be
// in sorted order, so that a sorted list results from the merge.
//
// This merge works in what I think would be a similar way that standard library
// container lists work, in that iterators are still valid. 
// In other words, the pointers of elements are rewired to reshape the list, but
// the elements remain in the same nodes at the same memory addresses. 
template <typename T>
void DoublyLinkedList<T>::merge(DoublyLinkedList<T>& other_list) {

	Node<T>* list_ptr = head;					// Set a pointer to head of this list
	Node<T>* other_list_ptr = other_list.head;	// Set a pointer to head of the other list

	Node<T>* dummy_ptr = getNewNode(INT_MIN);	// Create a dummy node
	Node<T>* new_tail = dummy_ptr;				// Set tail to dummy

	// Traverse the two lists to build the new list order.
	// Begin at the dummy node, hooking that up to the lowest element of the two lists, 
	// then hook that one up to the next lowest element, and so on.
	// Advance a temporary tail pointer to each newly-situated node, so that at the end of this
	// loop tail will already be at the actual tail of the list.
	// The head pointer is reset after the main processing.
	while (list_ptr && other_list_ptr) {
		if (list_ptr->data <= other_list_ptr->data) {
			// Current element in this list should be next in line
			new_tail->next = list_ptr;	// Wire up to next element
			list_ptr->prev = new_tail;	// Set next element to point back to current tail
			new_tail = list_ptr;		// Advance tail forward to next element
			list_ptr = list_ptr->next;	// Move to next item in this list			
		}
		else {
			// Current element in the other list should be next in line
			new_tail->next = other_list_ptr;		// Wire up to next element
			other_list_ptr->prev = new_tail;		// Point back to current tail
			new_tail = other_list_ptr;				// Advance tail forward to next element
			other_list_ptr = other_list_ptr->next;	// Move to next item in the other list			
		}
	}

	if (list_ptr) {
		// If there are still some elements left in the original list formation,
		// simply slot them onto the end of the new formation.
		new_tail->next = list_ptr;
		new_tail = tail;
	}

	if (other_list_ptr) {
		// If there are still some elements left in the other list,
		// simply slot them onto the end of the new formation.
		new_tail->next = other_list_ptr;
		new_tail = other_list.tail;
	}

	// List is in right order now - just need to tidy up some details to finish		
	head = dummy_ptr->next;		// Reset head pointer to first "real" element in list

	// Reset tail pointer
	if (head)
		// If there was one or more elements across both lists, set the tail to point to
		// the last of the reformed list, which will be indicated by new_tail
		tail = new_tail;
	else
		tail = nullptr;			// If neither list had any elements, set tail to null

	size += other_list.size;	// Adjust the size to allow for the elements of both lists	
	delete dummy_ptr;			// Dummy node will need to be decoupled from the list

	// Decommission the other list by nulling out the head and tail pointers.
	other_list.head = nullptr;
	other_list.tail = nullptr;
	other_list.size = 0;
}

// Utility methods used for debugging merge()
// ------------------------------------------

template <typename T>
Node<T>* DoublyLinkedList<T>::getOriginalListHead() {
	return original_head;
}

// Utility method used for merge().
template <typename T>
Node<T>* DoublyLinkedList<T>::getOriginalListTail() {
	return original_tail;
}

// Set these variables to allow testing of their movement (or not).
// These are added purely to do a quick simulation of iterators, without actually
// having to go to all the trouble of setting up iterators, to see if this merge works
// in a similar way to that used in standard library containers such as List.
// They are set here and NOT mutated in any way!
template <typename T>
void DoublyLinkedList<T>::setOriginalListHead() {
	original_head = head;
}


template <typename T>
void DoublyLinkedList<T>::setOriginalListTail() {
	original_tail = tail;
}


// Prints the full contents of the linked list -- O(n)
// Either iterative or recursive logic can be plugged in here via
// use of a helper method.
template<typename T>
void DoublyLinkedList<T>::printList() {
	//printListIterative();
	printListRecursive(head);
	//std::cout << "\nList in reverse order:\n";
	//printListReverse();
}


// Utility method that prints the full contents of the linked list 
// using iterative logic
template<typename T>
void DoublyLinkedList<T>::printListIterative() {
	Node<T>* current = head;

	while (current) {
		std::cout << current->data << " ";
		current = current->next;
	}
	std::cout << '\n';
}


// Utility method that prints the full contents of the linked list in reverse order
// using iterative logic
template<typename T>
void DoublyLinkedList<T>::printListReverse() {
	Node<T>* current = tail;

	while (current) {
		std::cout << current->data << " ";
		current = current->prev;
	}
	std::cout << '\n';
}


// Utility method that prints the full contents of the linked list 
// using iterative logic
template<typename T>
void DoublyLinkedList<T>::printListRecursive(Node<T>* node) {
	if (!node) {
		std::cout << '\n';
		return;
	}

	std::cout << node->data << " ";
	printListRecursive(node->next);
}


#endif // DOUBLY_LINKED_LIST_H


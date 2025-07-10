// Priority Queue
// --------------
// 
// This is a C++ implementation of a priority queue (made a template class).
// 
// 
// A Container Adaptor Data Structure
// ----------------------------------
// 
// The priority queue is another container adaptor, meaning that some of 
// the key functionality is actually implemented by another, sequential, data structure, 
// which is used as a member of the class. 
// 
// This class provides a restricted interface to that member (underlying) structure, 
// to produce the queue functionality. 
// It uses the C++ standard library vector as the underlying data structure. 
// 
// Special Member Functions
// ------------------------
// 
// Consequently, there is no need to explicitly define special member functions, since 
// the defaults will call the requisite functions in the underlying vector, which will 
// handle requirements (and the other member variables of this class are ints, 
// so no need to worry about them either).
// 
// The special members are marked as default on the interface here for clarity, however.

#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <concepts>
#include <vector>
#include "..\Queue\Queue.h"

class PriorityQueueEmptyException : public QueueEmptyException {
public:
	PriorityQueueEmptyException(const std::string& err) :
		QueueEmptyException(err) {
	}
};

// Concept to require the template parameter to have comparison operators.
// These are necessary to allow the elements in the queue to be prioritised.
template <typename T>
concept Comparable = requires(T a) {
	a < 1;
	a <= 1;
	a > 1;
	a >= 1;
	a == 1;
	a != 1;
};

template <typename T> requires Comparable<T>
class PQueue {
public:
	PQueue() : PQueue(0) {}		// No-arg constructor; default size of zero
	PQueue(int size);
	PQueue(const PQueue& other) = default;
	PQueue(PQueue&& other) = default;
	PQueue& operator=(const PQueue& other) = default;
	PQueue& operator=(PQueue&& other) = default;
	~PQueue() = default;

	bool isEmpty();
	int size();
	void clear();
	const T& top();
	void pop();
	bool contains(T elem);
	void add(T elem);
	bool remove(T elem);
	std::optional<T> removeAt(int index);
	void print();
	bool isPQValid();
private:
	bool less(int i, int j);
	void sink(int k);
	void swim(int k);
	void swap(int i, int j);
	bool isMinHeap(int k);
private:
	int heapSize = 0;			// Number of elements in the heap
	int heapCapacity = 0;		// Internal heap capacity
	std::vector<T> heap;		// A dynamic array to track elements in the heap	
};


// Public Member Function Definitions
// ==================================

// Construct a PQ with an initial capacity.
template <typename T> requires Comparable<T>
PQueue<T>::PQueue(int size) : heapSize{ size } {
	heap.resize(heapSize);
}


// Returns true if this PQ is empty; otherwise returns false.
template <typename T> requires Comparable<T>
bool PQueue<T>::isEmpty() {
	return (size() == 0);
}


// Returns the size of this PQ.
template <typename T> requires Comparable<T>
int PQueue<T>::size() {
	return heapSize;
}


// Clears all elements from this PQ completely -- O(n).
template <typename T> requires Comparable<T>
void PQueue<T>::clear() {
	heap.clear();	// Clear the underlying heap	
	heapSize = 0;	// Reset size to 0
}


// Returns a reference to the element with the lowest priority in this PQ.
// If the PQ is empty, an empty priority queue exception is thrown.
template <typename T> requires Comparable<T>
const T& PQueue<T>::top() {
	if (isEmpty())
		throw PriorityQueueEmptyException("Priority Queue is empty");
	const T& top_elem = heap[0];
	return top_elem;
}


// Removes the root of the heap -- O(log(n))
template <typename T> requires Comparable<T>
void PQueue<T>::pop() {
	removeAt(0);
}


// Returns true if elem is in this heap, else returns false -- O(n)
template <typename T> requires Comparable<T>
bool PQueue<T>::contains(T elem) {
	// Linear scan to check if elem is in the PQ
	for (int i = 0; i < heapSize; i++)
		if (heap[i] == elem)
			return true;
	return false;
}


// Adds an element to the PQ -- O(n)
// N.b. the internal capacity of this PQ may be out of sync with that
// of the underlying vector...
template <typename T> requires Comparable<T>
void PQueue<T>::add(T elem) {
	if (heapSize < heapCapacity)
		heap.push_back(elem);
	else {						// Expand heap capacity if necessary
		heap.push_back(elem);
		heapCapacity++;
	}
	swim(heapSize);
	heapSize++;
}


// Returns true if the specified element is removed from the PQ;
// otherwise returns false -- O(log(n))
template <typename T> requires Comparable<T>
bool PQueue<T>::remove(T elem) {
	// Linear removal via search
	for (int i = 0; i < heapSize; i++) {
		if (elem == heap[i]) {
			removeAt(i);
			return true;
		}
	}
	return false;
}


// If the specified index is valid, removes the node at that index 
// and returns its value;
// Otherwise nothing is removed and null is returned -- O(log(n))
template <typename T> requires Comparable<T>
std::optional<T> PQueue<T>::removeAt(int index) {
	if (index >= heapSize)
		return {};	// Do nothing if there is no element at this index

	heapSize--;
	T removed_data = heap[index];	// Get a copy of to-be-removed element	
	swap(index, heapSize);			// Move to-be-deleted element to end of heap
	heap.pop_back();				// Remove last heap element

	// If it happens to be the last element in the heap being removed,
	// there's no need to do anything else so we can simply return here.
	if (index == heapSize)
		return removed_data;

	// Otherwise, we need to sink or swim the element
	T elem = heap[index];
	sink(index);					// Try sinking element
	if (heap[index] == elem)		// If sinking doesn't work, try swimming
		swim(index);

	return removed_data;
}


// Prints the contents of the PQ (the heap) -- O(n)
template <typename T> requires Comparable<T>
void PQueue<T>::print() {
	for (int i = 0; i < heap.size(); i++)
		std::cout << heap[i] << "  ";
	std::cout << "\n\n";
}


// Returns true if this PQ is in a valid state.
// 
// In real world use, we would not want a method
// like this to be on the public interface, as it's
// too much of an internal matter to be of relevance
// to the user. 
// 
// But it's useful for learning purposes to
// have it public so it can be called from test code.
template <typename T> requires Comparable<T>
bool PQueue<T>::isPQValid() {
	return isMinHeap(0);	// Start from the root of the heap
}

/***************************************************************************************************************/

// Private Utility Member Functions
// ================================


// Private helper function that tests if the value of node i 
// is less than or equal to the value of node j -- O(1)
// Assumes that i and j are valid indices.
template <typename T> requires Comparable<T>
bool PQueue<T>::less(int i, int j) {
	T node1 = heap[i];
	T node2 = heap[j];
	return node1 <= node2;
}


// Private helper function that performs a top-down node sink -- O(log(n))
template <typename T> requires Comparable<T>
void PQueue<T>::sink(int k) {
	while (true) {
		int left = 2 * k + 1;	// Find k's left child
		int right = 2 * k + 2;	// Find k's right child
		int smallest = left;	// Default left child as the smallest

		// Now find which is smaller, the left or right child
		if (right < heapSize && less(right, left))
			smallest = right;

		// Stop if outside the bounds of the tree
		// or stop early if we cannot sink k anymore
		if (left >= heapSize || less(k, smallest))
			break;

		// Move down the tree following the smallest node
		swap(smallest, k);
		k = smallest;
	}
}


// Private helper function that swims a node up the heap -- O(log(n))
template <typename T> requires Comparable<T>
void PQueue<T>::swim(int k) {
	int parent = (k - 1) / 2;	// Store the index of the parent node of k

	// Keep swimming until either the root is reached or
	// the current value is greater than or equal to the parent.
	while (k > 0 && less(k, parent)) {
		swap(parent, k);		// Exchange k with the parent
		k = parent;				// Set k to parent value
		parent = (k - 1) / 2;	// Store the index of the next parent node of k			
	}
}


// Private helper function that swaps two nodes -- O(1)
// Assumes that i and j are valid indices.
template <typename T> requires Comparable<T>
void PQueue<T>::swap(int i, int j) {
	T& i_elem = heap[i];	// Get i's element
	T& j_elem = heap[j];	// Get j's element

	// Do the swap
	T temp = i_elem;
	i_elem = j_elem;
	j_elem = temp;
}


// Private helper function that recursively checks if this heap is a 
// valid min heap. 
// This method is just for testing purposes to make
// sure the heap invariant is still being maintained.
// 
// Call this method with k = 0 to start at the root.
template <typename T> requires Comparable<T>
bool PQueue<T>::isMinHeap(int k) {
	// If we are outside the bounds of the heap return true
	if (k >= heapSize)
		return true;

	int left = 2 * k + 1;
	int right = 2 * k + 2;

	// Make sure that the current node k is less than
	// both of its children, left and right, if they exist.
	// return false otherwise to indicate an invalid heap.
	if (left < heapSize && !less(k, left))
		return false;
	if (right < heapSize && !less(k, right))
		return false;

	// Recurse on both children to make sure they're also valid heaps
	return isMinHeap(left) && isMinHeap(right);
}


#endif	// PRIORITY_QUEUE_H


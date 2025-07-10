// Indexed Priority Queue
// ----------------------
// 
// This is a C++ implementation of an indexed priority queue.
// 
// An Container Adaptor Data Structure
// -----------------------------------
// 
// The indexed priority queue is another container adaptor. This implementation
// uses raw arrays; there are five arrays used in total, although only three are
// crucial to the operation of the queue - the other two are supporting structures.
// 
// The three core arrays are:
// 1) The values array - this is template type array, which allows the user to use
//    any type that meets the Comparable requirements as the value. In this
//    implementation, in practice, a fundamental type is best (see the notes on the
//    concept for further details).
// 2) A position map array - an array of ints (positions need only be referred to in 
//    simple integral numeric terms).
// 3) An index map array - an array of ints for the same reason as the position map.
// 
// The two supporting arrays are lookup tables, storing the relative positions for each 
// node in the heap:
// 1) parent - an array of ints; stores the index (position) in the heap of the parent 
//    for each node.
// 2) child - an array of ints; stores the index (position) in the heap of a node's
//    left child node.
// 
// These values are calculated upfront in the constructor for all nodes within the 
// bounds of the array [0-maxNodes). Since the maximum size queue is fixed for
// the life of the queue, the positions in the underlying heap are fixed, so 
// consequently the parent and child values are fixed for the life accordingly -
// there is no need to amend them after they're initially set.
// 
// The parent and child indices are used in the sink and swim operations.
// However, they can be considered optional - in the standard priority queue
// implementation, the parent and child indices are calculated on demand.
//
//
// Future Improvements
// -------------------
//
// 1. The queue currently only supports on template parameter, which allows the 
//    user to specify the type for that value only; the key is hardcoded as
//    an integer. Adding a second template parameter would allow the user to
//    specify the key type as well (e.g. they may wish to use a string as a key).
// 
// 2. Consider throwing an exception for the increase operation where the key is not found.
//    It currently returns cleanly without doing anything in this situation,
//    but arguably the user should be notified in some way. An alternative is to use
//    an std::optional return type, as per the update operation.


#ifndef INDEXED_PRIORITY_QUEUE
#define INDEXED_PRIORITY_QUEUE

#include <algorithm>		// For std::min
#include <concepts>
#include <exception>
#include <functional>		// For std::less & std::greater
#include <map>				// Print names function uses a map (keys to names)
#include <optional>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>


// Exception to be thrown when the queue is empty.
class QueueEmptyException : public std::runtime_error {
public:
	// no need to override what() since we can just use std::runtime_error::what()
	QueueEmptyException(const std::string& err) : std::runtime_error(err) {}
};


// Exception to be thrown when the queue already contains a key
// matching that of a key to be inserted.
class QueueDuplicateException : public std::runtime_error {
public:
	QueueDuplicateException(const std::string& err) : std::runtime_error(err) {}
};


// Exception to be thrown when the key searched for cannot
// be found in the queue.
class KeyOutOfBoundsException : public std::runtime_error {
public:
	// Pass error message by const reference.
	KeyOutOfBoundsException(std::string const& error_msg) noexcept
		: std::runtime_error(error_msg) {}
	// what() in std::runtime_error will handle this as desired
};


// Exception to be thrown when the key searched for cannot
// be found in the queue.
class KeyNotFoundException : public std::runtime_error {
public:
	// Pass error message by const reference.
	KeyNotFoundException(std::string const& error_msg) noexcept
		: std::runtime_error(error_msg) {}
	// what() in std::runtime_error will handle this as desired
};

// Concept to require the template parameter to have comparison operators.
// These are necessary to allow the elements in the queue to be found/inserted/removed.
// 
// I could add more constraints to satisfy the print function requirements, 
// but as these are really debugging functions rather than the core part of 
// the public interface, I will disregard that. Therefore a class that has
// > < operators defined will satisfy the constraints here, but can still fail 
// to compile in terms of the print functions if they are called, 
// due to other requirements (one example being the need for a not operator).
//
// Another option would be to specialise the print functions to suit the
// type, but that is only justified if there is a real reason to have that
// particular type as an index value. I'm only really creating a user-defined
// type in some tests to test the concept itself works, not because I'm expecting UDTs 
// to be viable as queue values.
// 
// In practice, we would really only want or need to use a primitive type
// as the value, in which case it will work fine.
template <typename T>
concept Comparable = requires(T a) {
	a < a;
	a > a;	
};

// Exclude doubles
template <typename T>
concept Integral = !std::same_as<T, double>;

// Combine the two concepts
template <typename T>
concept ComparableIntegral = Comparable<T> && Integral<T>;

template<typename T> requires ComparableIntegral<T>
class IndexedPriorityQueue {
	static const int DEFAULT_MAX_NODES = 25;
	static const int DEFAULT_DEGREE = 2;
public:
	IndexedPriorityQueue(int deg, int maxSize);
	IndexedPriorityQueue(const IndexedPriorityQueue& other);
	IndexedPriorityQueue(IndexedPriorityQueue&& other) noexcept;
	IndexedPriorityQueue& operator=(const IndexedPriorityQueue& other);
	IndexedPriorityQueue& operator=(IndexedPriorityQueue&& other) noexcept;
	~IndexedPriorityQueue();

	bool isMinHeap();
	bool isEmpty();
	int size();
	bool contains(int keyIndex);
	int peekMinKeyIndex();
	int pollMinKeyIndex();
	std::optional<T> peekMinValue();
	std::optional<T> pollMinValue();
	void insert(int keyIndex, T value);
	std::optional<T> removeKey(int keyIndex);
	std::optional<T> update(int keyIndex, T newValue);
	void decrease(int keyIndex, T newValue);
	void increase(int keyIndex, T newValue);
	void printArrays();
	void printNames(std::map<T, std::string>& namesMap);
private:
	void swap(IndexedPriorityQueue& other);
	void printCharacter(char c, int num);
	bool validMinHeap(int index);
	bool keyInBounds(int keyIndex);
	void keyExists(int keyIndex);
	void removeNode(int keyIndex);
	void swap(int first, int second);
	void sink(int index);
	void swim(int index);
	bool lowerValue(int heapPosA, int heapPosB);
	int minChild(int parentIndex);
private:
	int noNodes;		// Number of nodes in the IPQ
	int maxNodes;		// The maximum number of nodes in the IPQ
	int degree;			// The degree of every node in the IPQ (how many children a node can have)
	int* child;			// Lookup array to track child indices of nodes
	int* parent;		// Lookup array to track parent indices of nodes

	// The Position Map maps Key Indexes to where the position of that
	// key is represented in the priority queue in the domain [0, maxNodes).
	int* positionMap;

	// The Inverse Map stores the indexes of the keys in the range
	// [0, maxNodes) that make up the priority queue. 
	// It should be noted that inverseMap and positionMap are the inverse 
	// of the other, so: 
	// positionMap[inverseMap[i]] = inverseMap[positionMap[i]] = i
	int* inverseMap;

	// The values associated with the keys. It is very important to note
	// that this array is indexed by the key indexes.
	T* values;
};

// Explicit Member Function Specialisations - Declarations
// -------------------------------------------------------

template<>
inline void IndexedPriorityQueue<int>::removeNode(int keyIndex);

template<>
inline void IndexedPriorityQueue<int>::printNames(std::map<int, std::string>& namesMap);

template <>
inline void IndexedPriorityQueue<int>::printArrays();

template <>
inline void IndexedPriorityQueue<char>::printArrays();


// Indexed Priority Queue Public Member Function Definitions
// =========================================================

// Special Member Functions
// ------------------------

// Constructor
template<typename T> requires ComparableIntegral<T>
IndexedPriorityQueue<T>::IndexedPriorityQueue(int deg, int maxSize) {
	if (maxSize <= 0) // Don't throw exception, simply set to default
		maxNodes = DEFAULT_MAX_NODES;
	else
		maxNodes = maxSize;

	// This implementation is going to use a binary heap, so that means
	// a node can have 2 children max, hence the degree will default to this
	// and ignore the constructor parameter.
	// If a different type of heap is required, reactivate this line and
	// use the value passed in (but must be a minimum of 2).
	//degree = std::max(2, deg);
	degree = DEFAULT_DEGREE;

	// Now the degree has been determined, the maximum number of nodes can be confirmed.
	// It must be at least three, since a single node has potentially two children, 
	// and it must allow for at least that to be a valid heap.
	// 
	// There is no prescribed upper limit for the number of nodes, so the user is 
	// free to set it as high as they like, however, if they provide a zero or 
	// negative value, it will be defaulted to 25.
	maxNodes = std::max(degree + 1, maxNodes);
	noNodes = 0;	// Start with zero nodes

	// Allocate the space for the arrays
	child = new int[maxNodes];
	parent = new int[maxNodes];
	values = new T[maxNodes];
	positionMap = new int[maxNodes];
	inverseMap = new int[maxNodes];
	
	// Setup the parent and child indices.
	// Initialise the position and inverse maps.
	for (int i = 0; i < maxNodes; i++) {
		parent[i] = (i - 1) / degree;
		child[i] = i * degree + 1;
		positionMap[i] = -1;
		inverseMap[i] = -1;
		values[i] = -1;
	}
}


// Copy constructor
template<typename T> requires ComparableIntegral<T>
IndexedPriorityQueue<T>::IndexedPriorityQueue(const IndexedPriorityQueue& other) {
	this->noNodes = other.noNodes;
	this->maxNodes = other.maxNodes;
	this->degree = other.degree;
	
	// Allocate the required memory for the arrays
	this->child = new int[maxNodes];
	this->parent = new int[maxNodes];
	this->values = new T[maxNodes];
	this->positionMap = new int[maxNodes];
	this->inverseMap = new int[maxNodes];
		
	// Copy contents from other into this for the arrays
	for (int i = 0; i < maxNodes; ++i) {
		this->child[i] = other.child[i];
		this->parent[i] = other.parent[i];
		this->values[i] = other.values[i];
		this->positionMap[i] = other.positionMap[i];
		this->inverseMap[i] = other.inverseMap[i];		
	}
}


// Move constructor
template<typename T> requires ComparableIntegral<T>
IndexedPriorityQueue<T>::IndexedPriorityQueue(IndexedPriorityQueue&& other) noexcept :
	noNodes{ std::exchange(other.noNodes, {}) },
	maxNodes{ std::exchange(other.maxNodes, {}) },
	degree{ std::exchange(other.degree, {}) }, 
	child{ new int[maxNodes] },
	parent{ new int[maxNodes] },
	values{ new T[maxNodes] },
	positionMap{ new int[maxNodes] },
	inverseMap{ new int[maxNodes] }
{
	// Move contents from other into this for the arrays
	for (int i = 0; i < maxNodes; ++i) {
		child[i] = std::exchange(other.child[i], {});
		parent[i] = std::exchange(other.parent[i], {});
		values[i] = std::exchange(other.values[i], {});
		positionMap[i] = std::exchange(other.positionMap[i], {});
		inverseMap[i] = std::exchange(other.inverseMap[i], {});
	}
}


// Copy assignment operator
template<typename T> requires ComparableIntegral<T>
IndexedPriorityQueue<T>& IndexedPriorityQueue<T>::operator=(const IndexedPriorityQueue& other) {
	IndexedPriorityQueue<T> temp(other);
	swap(temp);
	return *this;
}


// Move assignment operator
template<typename T> requires ComparableIntegral<T>
IndexedPriorityQueue<T>& IndexedPriorityQueue<T>::operator=(IndexedPriorityQueue&& other) noexcept {
	IndexedPriorityQueue<T> temp(std::move(other));
	swap(temp);
	return *this;
}


// Custom swap function
template<typename T> requires ComparableIntegral<T>
void IndexedPriorityQueue<T>::swap(IndexedPriorityQueue& other)  {
	using std::swap;
	swap(noNodes, other.noNodes);
	swap(maxNodes, other.maxNodes);
	swap(degree, other.degree);
	swap(child, other.child);
	swap(parent, other.parent);
	swap(values, other.values);
	swap(positionMap, other.positionMap);
	swap(inverseMap, other.inverseMap);	
}


// Destructor
template<typename T> requires ComparableIntegral<T>
IndexedPriorityQueue<T>::~IndexedPriorityQueue() {
	delete[] child;
	delete[] parent;
	delete[] values;
	delete[] positionMap;
	delete[] inverseMap;	
}


/***********************************************************************************/

// Other Indexed Priority Queue Member Functions
// ---------------------------------------------

// Test function to check if the underlying structure of this IPQ
// is a valid minimum heap.
// Returns true if it is, else returns false.
template<typename T> requires ComparableIntegral<T>
bool IndexedPriorityQueue<T>::isMinHeap() {
	return validMinHeap(0);
}


// Returns true if this IPQ is empty, otherwise returns false.
template<typename T> requires ComparableIntegral<T>
bool IndexedPriorityQueue<T>::isEmpty() {
	return (noNodes == 0);
}


// Returns the number of nodes in this IPQ.
template<typename T> requires ComparableIntegral<T>
int IndexedPriorityQueue<T>::size() {
	return noNodes;
}


// Returns true if this IPQ contains a key at keyIndex, else returns false.
// 
// The keyIndex must be within bounds for this IPQ for it to 
// be checked in the first place, so a bounds check is first performed. 
// If this fails, throw a KeyOutOfBoundsException.
// If it succeeds, continue to check if that index has a valid entry or not.
template<typename T> requires ComparableIntegral<T>
bool IndexedPriorityQueue<T>::contains(int keyIndex) {
	if (!keyInBounds(keyIndex))
		throw KeyOutOfBoundsException(std::to_string(keyIndex) + " out of bounds");
	return positionMap[keyIndex] != -1;
}

// Returns the index of the minimum key in the IPQ
// (the highest priority node).
// Throws exception if the queue is empty.
template<typename T> requires ComparableIntegral<T>
int IndexedPriorityQueue<T>::peekMinKeyIndex() {
	if (isEmpty()) // Check size first - avoids null pointer exceptions
		throw QueueEmptyException("IPQ is empty");
	return inverseMap[0];
}


// Returns the key of the minimum value node in the IPQ
// (the highest priority node) and removes it from
// the queue.
template<typename T> requires ComparableIntegral<T>
int IndexedPriorityQueue<T>::pollMinKeyIndex() {
	// Returns the index of the position map entry for the minimum key
	// (or throws exception if IPQ empty).
	int minKeyIndex = peekMinKeyIndex();
	removeKey(minKeyIndex);
	return minKeyIndex;
}


// Returns the lowest value currently in the IPQ
// (which is the highest priority node).
// Otherwise returns a null value if the queue is empty.
template<typename T> requires ComparableIntegral<T>
std::optional<T> IndexedPriorityQueue<T>::peekMinValue() {
	if (isEmpty())
		return {};
	return values[inverseMap[0]];
}


// Returns the lowest value currently in the IPQ
// (which is the highest priority node) and 
// removes it from the queue.
// Otherwise returns a null value if the queue is empty.
template<typename T> requires ComparableIntegral<T>
std::optional<T> IndexedPriorityQueue<T>::pollMinValue() {
	std::optional<T> minValue = peekMinValue();

	if (!minValue.has_value())	// Queue is empty
		return {};

	removeKey(peekMinKeyIndex());
	return minValue;
}


// Insert keyIndex and value into the IPQ.
// 
// If the key is not within the current bounds of this IPQ, 
// throw a KeyOutOfBoundsException.
// 
// If keyIndex is already in use in this IPQ. 
// throw a QueueDuplicateException.
template<typename T> requires ComparableIntegral<T>
void IndexedPriorityQueue<T>::insert(int keyIndex, T value) {
	// If key not in bounds, indicate this with exception.
	if (!keyInBounds(keyIndex))
		throw KeyOutOfBoundsException(std::to_string(keyIndex) + " out of bounds");

	if (contains(keyIndex))
		throw QueueDuplicateException(std::to_string(keyIndex) + " already exists in the queue");

	// An insertion is always placed first at the bottom right of the binary heap
	// and its position is subsequently adjusted to maintain the heap invariant.
	positionMap[keyIndex] = noNodes;
	inverseMap[noNodes] = keyIndex;
	values[keyIndex] = value;

	// Swim the new node up the heap to its correct position (if necessary).
	// Finally, update the node count.
	swim(noNodes++);
}

// Private utility function that removes the node associated with keyIndex 
// from the IPQ.
// There is no need to do any key validation, as that has already been done
// by the removeKey function that is calling this one.
// Removing the node ultimately is a case of voiding its values in the core arrays.
template<typename T> requires ComparableIntegral<T>
void IndexedPriorityQueue<T>::removeNode(int keyIndex) {
	values[keyIndex] = {};			// Clear out the value from the values array
	positionMap[keyIndex] = -1;		// Remove the key from the position map
	inverseMap[noNodes] = -1;		// Remove the position from the inverse map
}


// If a node associated with keyIndex is found, it is removed from the IPQ
// and its value returned.
// 
// If the key is not within the current bounds of this IPQ, it fails
// quietly; no processing occurs and an empty std::optional is returned.
// 
// If the key is within bounds but not found, a KeyNotFoundException is thrown.
// 
// Otherwise, the node for this key is removed from the queue, and its value
// is returned.
template<typename T> requires ComparableIntegral<T>
std::optional<T> IndexedPriorityQueue<T>::removeKey(int keyIndex) {
	// If key not in bounds there's nothing more we can do
	// so return early (and cleanly).
	if (!keyInBounds(keyIndex))
		return {};

	// Check the key actually exists in this queue.
	keyExists(keyIndex);

	// Get the position in the heap for this key
	const int heapPosition = positionMap[keyIndex];

	// Swap the to-be-removed node with the heap last node
	swap(heapPosition, --noNodes);

	// The previous last node is now at the position of the
	// to-be-removed node, so sink it down if necessary
	sink(heapPosition);

	// Or swim the node up if necessary
	swim(heapPosition);

	T value = values[keyIndex];		// Save the value of the node

	removeNode(keyIndex);			// Remove node from the queue
	return value;					// Return the node's value
}



// Updates the value for the node with keyIndex with newValue 
// and adjusts the position in the IPQ for that node.
// 
// If the key is not within the current bounds of this IPQ, it fails
// quietly (no processing occurs and the method ends).
// As this function returns a value, it simply returns an empty
// value of type T.
// 
// If keyIndex is not found in this IPQ, a KeyNotFoundException is thrown.
template<typename T> requires ComparableIntegral<T>
std::optional<T> IndexedPriorityQueue<T>::update(int keyIndex, T newValue) {
	// If key not in bounds there's nothing more
	// we can do, so return early (and cleanly).
	if (!keyInBounds(keyIndex))
		return {};

	// Key is in bounds, but is it currently an active, valid key?
	keyExists(keyIndex);

	const int heapPosition = positionMap[keyIndex];	// Find the key's heap position
	T oldValue = values[keyIndex];					// Retrieve the existing value

	// One is the minimum value allowed
	// Reject updates that would breach that condition
	if (newValue >= 1) {
		values[keyIndex] = newValue;	// Overwrite existing with new value

		// Now sink or swim the amended node as appropriate
		sink(heapPosition);
		swim(heapPosition);
	}

	return oldValue;					// Return the old value
}


// Strictly decreases the value associated with keyIndex to newValue. 
// 
// If the key is not within the current bounds of this IPQ, it fails
// quietly (no processing occurs and the method ends). 
// 
// If the key is not found, a KeyNotFoundException is thrown.
// 
// If the newValue is greater than or equal to the existing value
// for this node, no update is permitted and no further processing occurs.
template<typename T> requires ComparableIntegral<T>
void IndexedPriorityQueue<T>::decrease(int keyIndex, T newValue) {
	// If key not in bounds there's nothing more
	// we can do, so return early (and cleanly).
	if (!keyInBounds(keyIndex))
		return;

	// Key is in bounds, but is it currently an active, valid key?
	keyExists(keyIndex);

	// The new value must be less than the existing value for this
	// keyIndex, but also be a value of one or higher, for this
	// update operation to proceed.
	if (std::less<T>{}(newValue, values[keyIndex]) && newValue >= 1) {
		values[keyIndex] = newValue;

		// As the value has now decreased, we know the node
		// either needs to swim up or stay where it is.
		swim(positionMap[keyIndex]);
	}
}

// Strictly increases the value associated with keyIndex to newValue. 
// 
// If the key is not within the current bounds of this IPQ, it fails
// quietly (no processing occurs and the method ends).
// 
// If the key is not found, a KeyNotFoundException is thrown.
// 
// If the newValue is less than or equal to the existing value
// for this node, no update is permitted and no further processing occurs.
template<typename T> requires ComparableIntegral<T>
void IndexedPriorityQueue<T>::increase(int keyIndex, T newValue) {
	// If key not in bounds there's nothing more
	// we can do, so return early (and cleanly).
	if (!keyInBounds(keyIndex))
		return;

	// Key is in bounds, but is it currently an active, valid key?
	keyExists(keyIndex);

	// If the new value is greater than the existing value for this
	// keyIndex, and it is at least a value of one,
	// the update operation is permitted.
	if (std::greater<T>{}(newValue, values[keyIndex]) && newValue >= 1) {
		values[keyIndex] = newValue;

		// As the value has now increased, we know the node
		// either needs to sink down or stay where it is.
		sink(positionMap[keyIndex]);
	}
}


// Test method that prints the contents of the various arrays that
// make up the heap.
template<typename T> requires ComparableIntegral<T>
void IndexedPriorityQueue<T>::printArrays() {
	const int TEXT_FIELD_LENGTH = 15;
	const int NUMERIC_FIELD_LENGTH = 6;

	std::cout << "\n\n";

	// Headers
	printCharacter(' ', TEXT_FIELD_LENGTH);	// Print 15 spaces (for side bar labels)

	// Allow up to five spaces to print each array value
	for (int i = 0; i < maxNodes; i++) {
		std::cout << i;
		printCharacter(' ', NUMERIC_FIELD_LENGTH - std::to_string(i).length());
	}
	std::cout << "\n\n";

	// On a new line each time, print sidebar label to identify 
	// the array being printed and then values for that array
	std::cout << "Values";
	printCharacter(' ', 9);
	for (int i = 0; i < maxNodes; i++) {
		if (!values[i])
			std::cout << "NULL  ";
		else {
			std::cout << values[i];
			printCharacter(' ', NUMERIC_FIELD_LENGTH - std::to_string(values[i]).length());
		}
	}
	std::cout << "\n";

	std::cout << "Position Map";
	printCharacter(' ', 3);
	for (int i = 0; i < maxNodes; i++) {
		std::cout << positionMap[i];
		printCharacter(' ', NUMERIC_FIELD_LENGTH - std::to_string(positionMap[i]).length());
	}
	std::cout << "\n";

	std::cout << "Inverse Map";
	printCharacter(' ', 4);
	for (int i = 0; i < maxNodes; i++) {
		std::cout << inverseMap[i];
		printCharacter(' ', NUMERIC_FIELD_LENGTH - std::to_string(inverseMap[i]).length());
	}
	std::cout << "\n\n";
}


// Test method that prints out the names we're testing with 
// and their respective keys and values.
// 
// This makes it easier to follow what's happening before and
// after various IPQ transactions.
// 
// This is an internal function on the IPQ class as we need
// access to the values in the IPQ, but we also
// need the names setup in the test code, so they are passed
// in as a parameter from there.
template<typename T> requires ComparableIntegral<T>
void IndexedPriorityQueue<T>::printNames(std::map<T, std::string>& namesMap) {
	std::cout << "Name               ";
	std::cout << "Key Index ";
	std::cout << "Value     ";
	std::cout << "\n";
	std::cout << "____               ";		// Underline Name
	std::cout << "_________ ";				// Underline Key Index
	std::cout << "____      ";       		// Underline Value
	std::cout << "\n\n";

	for (int i = 0; i < maxNodes; i++) {
		std::string name;
		typename std::map<T, std::string>::iterator kv = namesMap.find(i);
		if (kv != namesMap.end()) {
			name = namesMap[i];
		}
		std::cout << name;
		printCharacter(' ', 20 - name.length());
		std::cout << i;
		printCharacter(' ', 10 - std::to_string(i).length());

		// Inverse map entry might be -1, which means it 
		// will blow up trying to access the element
		// in the position map
		T* value = nullptr;
		if (inverseMap[i] >= 0) {
			value = &values[positionMap[inverseMap[i]]];
		}

		if (!value) {
			std::cout << "NULL";
			printCharacter(' ', 10 - strlen("NULL"));
		}
		else {
			std::cout << *value;
			printCharacter(' ', 10 - std::to_string(*value).length());
		}
		std::cout << '\n';
	}
	std::cout << "\n\n";
}

/******************************************************************************************/

// Indexed Priority Queue Private Member Function Definitions
// ----------------------------------------------------------


// Private utility method that handles printing to the standard output
// stream a repetitive sequence of a character.
// c - the character to print
// num - the number of times to print it
template<typename T> requires ComparableIntegral<T>
void IndexedPriorityQueue<T>::printCharacter(char c, int num) {
	for (int i = 0; i < num; i++)
		std::cout << c;
}


// Private utility method used for testing purposes.
// If the minimum heap invariant is observed in the heap
// underlying this IPQ, it returns true, else returns false.
template<typename T> requires ComparableIntegral<T>
bool IndexedPriorityQueue<T>::validMinHeap(int index) {
	int from = child[index];
	int to = std::min(noNodes, from + degree);

	for (int j = from; j < to; j++) {
		if (!lowerValue(index, j))
			return false;
		if (!validMinHeap(j))
			return false;
	}
	return true;
}


// Private utility method that checks if keyIndex is within the current
// valid bounds on this IPQ. Returns true if so, else returns false.
// 
// Fiset implemented it as an exception-throwing function, but after
// having problems with exceptions, I revisited the topic in C++.
// That led me to informed opinion that for relatively common occurrences like 
// going out of bounds, throwing an exception is overkill.
// 
// Therefore I've changed the validation of this function to simply check 
// and return a bool, rather than creating a potentially complicated 
// exception chain.
template<typename T> requires ComparableIntegral<T>
bool IndexedPriorityQueue<T>::keyInBounds(int keyIndex) {
	return (keyIndex >= 0 && keyIndex < maxNodes);
}


// Private utility function that checks if keyIndex exists
// in this IPQ.
// If so, it simply returns with no further processing; 
// otherwise it throws a KeyNotFoundException.
template<typename T> requires ComparableIntegral<T>
void IndexedPriorityQueue<T>::keyExists(int keyIndex) {
	if (!contains(keyIndex))
		throw KeyNotFoundException("Key " + std::to_string(keyIndex) + " not found");
}



// Private utility method that swaps the entries at index first
// and index second in the position map and the inverse map.
template<typename T> requires ComparableIntegral<T>
void IndexedPriorityQueue<T>::swap(int first, int second) {
	// Swap Position Map entries first
	positionMap[inverseMap[second]] = first;
	positionMap[inverseMap[first]] = second;

	// Now swap Inverse Map entries
	int temp = inverseMap[first];
	inverseMap[first] = inverseMap[second];
	inverseMap[second] = temp;
}


// Private utility method that moves a node down the heap 
// ("sinks" it down the heap), based on its value, if it
// is causing the heap invariant to be broken, i.e. if
// its value is too high (min heap) or too low (max heap)
// for the position where it is currently on the heap.
template<typename T> requires ComparableIntegral<T>
void IndexedPriorityQueue<T>::sink(int index) {
	for (int child = minChild(index); child != -1; ) {
		swap(index, child);
		index = child;
		child = minChild(index);
	}
}


template<typename T> requires ComparableIntegral<T>
void IndexedPriorityQueue<T>::swim(int index) {
	// Find the value of the newly inserted node.
	// Access through index, which is the highest current
	// index in the arrays in this IPQ.
	// 
	// We can use this same index to retrieve the value of the 
	// parent node of this newly inserted node.

	// If the value of the new node is lower than that of its parent, 
	// we help the new node "swim up" the heap; 
	// i.e. we swap the position and inverse array entries for these nodes.	
	while (lowerValue(index, parent[index])) {
		swap(index, parent[index]);

		// Now move up the heap to the parent of the newly inserted node
		// and repeat the same checks/swaps as necessary.
		// We end this process when the new node is in the correct place as per the 
		// heap invariant.
		index = parent[index];
	}
}


// Private utility method used to compare the values of two
// different nodes in the heap making up this IPQ, using
// the heap position of the nodes to locate their values.
// 
// Returns true if the value at heapPosA is less 
// than the value at heapPosB, else returns false.
template<typename T> requires ComparableIntegral<T>
bool IndexedPriorityQueue<T>::lowerValue(int heapPosA, int heapPosB) {
	return std::less<T>{}
	(values[inverseMap[heapPosA]], values[inverseMap[heapPosB]]);
}


// From the parent node at parentIndex find which of its child nodes
// has the lower value and return the index of that node.
// Returns -1 if the node has no children, or if any child nodes
// have higher values than it does.
template<typename T> requires ComparableIntegral<T>
int IndexedPriorityQueue<T>::minChild(int parentIndex) {
	int index = -1;
	int from = child[parentIndex];
	int to = std::min(noNodes, from + degree);

	for (int childIndex = from; childIndex < to; childIndex++) {
		if (lowerValue(childIndex, parentIndex))
			index = parentIndex = childIndex;
	}
	return index;
}

/*************************************************************************************************/

// Explicit Member Function Specialisations - Definitions
// ------------------------------------------------------
 
// This is a version of the removeNode member function specialised for ints.
// Other non-numeric data types can be nulled out when they're removed from the
// values array, but you can't just null out an integer, so
// an alternative is required.
template<>
inline void IndexedPriorityQueue<int>::removeNode(int keyIndex) {
	// Remove node from the queue.
	// Cannot simply blank out an int variable as with other data types.
	// Need to set it to something.
	// Minus 1 is not a valid value for a priority (must be positive one or higher)
	// so it is a good "null node" indicator.
	values[keyIndex] = -1;
	positionMap[keyIndex] = -1;		// Remove the key from the position map
	inverseMap[noNodes] = -1;		// Remove the position from the inverse map
}


// Delete the decrease function only for short type only 
// (arbitrary example of how to delete a template class member function).
template<>
void IndexedPriorityQueue<short>::decrease(int keyIndex, short newValue) = delete;

// Test method that prints out the names we're testing with 
// and their respective keys and values.
// 
// This makes it easier to follow what's happening before and
// after various IPQ transactions.
// 
// This is an internal method on the IPQ class as we need
// access to the values in the IPQ, but we also
// need the names setup in the test code, so they are passed
// in as a parameter from there.
//
// This is a specialised version for printing int values.
template<>
inline void IndexedPriorityQueue<int>::printNames(std::map<int, std::string>& namesMap) {
	std::cout << "Name               ";
	std::cout << "Key Index ";
	std::cout << "Value     ";
	std::cout << "\n";
	std::cout << "____               ";		// Underline Name
	std::cout << "_________ ";				// Underline Key Index
	std::cout << "____      ";       		// Underline Value
	std::cout << "\n\n";

	for (int i = 0; i < maxNodes; i++) {
		std::string name;
		std::map<int, std::string>::iterator kv = namesMap.find(i);
		if (kv != namesMap.end()) {
			name = namesMap[i];
		}
		std::cout << name;
		printCharacter(' ', 20 - name.length());
		std::cout << i;
		printCharacter(' ', 10 - std::to_string(i).length());

		// Inverse map entry might be -1, which means it 
		// will blow up trying to access the element
		// in the position map
		int value = -1;
		if (inverseMap[i] >= 0) {
			value = values[positionMap[inverseMap[i]]];
		}

		if (value == INT_MAX) {
			std::cout << "NULL";
			printCharacter(' ', 10 - strlen("NULL"));
		}
		else {
			std::cout << value;
			printCharacter(' ', 10 - std::to_string(value).length());
		}
		std::cout << '\n';
	}
	std::cout << "\n\n";
}


// Test method that prints the contents of the various arrays that
// make up the heap.
// This is a specialised version for printing int values.
template <>
inline void IndexedPriorityQueue<int>::printArrays() {
	const int TEXT_FIELD_LENGTH = 15;
	const int NUMERIC_FIELD_LENGTH = 5;

	std::cout << "\n\n";

	// Headers
	printCharacter(' ', TEXT_FIELD_LENGTH);	// Print 15 spaces (for side bar labels)

	// Allow up to five spaces to print each array value
	for (int i = 0; i < maxNodes; i++) {
		std::cout << i;
		printCharacter(' ', NUMERIC_FIELD_LENGTH - std::to_string(i).length());
	}
	std::cout << "\n\n";

	// On a new line each time, print sidebar label to identify 
	// the array being printed and then values for that array
	std::cout << "Values";
	printCharacter(' ', 9);
	for (int i = 0; i < maxNodes; i++) {
		if (values[i] == INT_MAX)
			std::cout << "NULL ";
		else {
			std::cout << values[i];
			printCharacter(' ', NUMERIC_FIELD_LENGTH - std::to_string(values[i]).length());
		}
	}
	std::cout << "\n";

	std::cout << "Position Map";
	printCharacter(' ', 3);
	for (int i = 0; i < maxNodes; i++) {
		std::cout << positionMap[i];
		printCharacter(' ', NUMERIC_FIELD_LENGTH - std::to_string(positionMap[i]).length());
	}
	std::cout << "\n";

	std::cout << "Inverse Map";
	printCharacter(' ', 4);
	for (int i = 0; i < maxNodes; i++) {
		std::cout << inverseMap[i];
		printCharacter(' ', NUMERIC_FIELD_LENGTH - std::to_string(inverseMap[i]).length());
	}
	std::cout << "\n\n";
}

// Test method that prints the contents of the various arrays that
// make up the heap.
// This is a specialised version for printing char values.
template <>
inline void IndexedPriorityQueue<char>::printArrays() {
	const int TEXT_FIELD_LENGTH = 15;
	const int NUMERIC_FIELD_LENGTH = 6;
	const int VALUES_FIELD_LENGTH = 7;

	std::cout << "\n\n";

	// Headers
	printCharacter(' ', TEXT_FIELD_LENGTH);	// Print 15 spaces (for side bar labels)

	// Allow up to five spaces to print each array value
	for (int i = 0; i < maxNodes; i++) {
		std::cout << i;
		printCharacter(' ', NUMERIC_FIELD_LENGTH - std::to_string(i).length());
	}
	std::cout << "\n\n";

	// On a new line each time, print sidebar label to identify 
	// the array being printed and then values for that array
	std::cout << "Values";
	printCharacter(' ', 9);
	for (int i = 0; i < maxNodes; i++) {
		if (!values[i])
			std::cout << "NULL  ";
		else {
			std::cout << values[i];
			printCharacter(' ', VALUES_FIELD_LENGTH - std::to_string(values[i]).length());
		}
	}
	std::cout << "\n";

	std::cout << "Position Map";
	printCharacter(' ', 3);
	for (int i = 0; i < maxNodes; i++) {
		std::cout << positionMap[i];
		printCharacter(' ', NUMERIC_FIELD_LENGTH - std::to_string(positionMap[i]).length());
	}
	std::cout << "\n";

	std::cout << "Inverse Map";
	printCharacter(' ', 4);
	for (int i = 0; i < maxNodes; i++) {
		std::cout << inverseMap[i];
		printCharacter(' ', NUMERIC_FIELD_LENGTH - std::to_string(inverseMap[i]).length());
	}
	std::cout << "\n\n";
}


#endif // INDEXED_PRIORITY_QUEUE
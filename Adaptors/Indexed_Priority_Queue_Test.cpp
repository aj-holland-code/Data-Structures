// Indexed Priority Queue
// ----------------------
// 
// See YouTube video "Data Structures Easy to Advanced Course - Full Tutorial from a Google Engineer"
// for an illustrated discussion: https://youtu.be/RBSGKlAvoiM
// The notes below are taken from the video.
// 
// What is an Indexed Priority Queue?
// ---------------------------------------------
// 
// An Indexed Priority Queue (IPQ) is a traditional priority queue variant that,
// in addition to the regular PQ operations, supports quick updates and 
// deletions of key-value pairs.
// 
// Usefulness of IPQ
// -----------------
// 
// It is very important to be able to dynamically update the priority queue
// (value) of certain people (keys). The IPQ data structure lets us do this
// efficiently. 
// 
// The first step to using an IPQ is to assign index values to all the keys,
// forming a bidirectional mapping.
// 
// Reason for Mapping
// ------------------
// 
// Priority queues are typically implemented as heaps under the hood, which 
// internally use arrays that we want to enable indexing into. 
// 
// NOTE: often the keys themselves are integers in the range [0, N), so there 
// is no need for the mapping, but it's handy to be able to support any type 
// of key (such as names).
// 
// ki = key index
// 
// 
// Time Complexity of Operations (IPQ as a Binary Heap)
// ----------------------------------------------------
// 
// Operation			    Indexed Binary Heap PQ
// ---------                ----------------------
// 
// delete(ki)				O(log(n))
// valueOf(ki)				O(1)
// contains					O(1)
// peekMinKeyIndex()		O(1)
// pollMinKeyIndex()		O(log(n))
// peekMinValue()			O(1)
// pollMinValue()			O(log(n))
// insert(ki, value)		O(log(n))
// update(ki, value)		O(log(n))
// decreaseKey(ki, value)	O(log(n))
// increaseKey(ki, value)	O(log(n))
// 
// 
// Node position lookups are constant time - O(1).
// Node repositioning may be up to logarithmic time - O(log(n)).
// 
// This means that:
// 
// Functions that only look up values can be performed in constant time,
// as they only require checking array entries.
// valueOf, contains, peeks
// 
// and
// 
// Functions that change the heap in some way can be performed in no
// worse than logarithmic time, as they may require swapping parent
// and child nodes in the heap, with the worst possible case being
// swapping the newly inserted node from the last position (where new nodes are 
// inserted) and swimming it right the way up to the root position in the heap.
// delete, polls, inserts, updates, decreaseKey, increaseKey.
//
//
// A Quick Conceptual Overview of the the IPQ Works
// ------------------------------------------------
//
// A queueing system for patients awaiting medical treatment is a useful analogy for considering how the
// IPQ data structure works.
// 
// We use an integer as the data type for the keys in this queue.
// We can imagine this key corresponding to a the name of a patient in the queue,
// with the name itself being stored in a separately outside this DS.
// The key, or key index, is the crucial piece of data that allows us to
// navigate and interact with the queue (hence key index is the input parameter 
// on numerous functions on the public and private interface of the queue).
// 
// At the next level down of analysis, we can conceptualise the queue in 
// terms of the binary heap to give us an understanding of what's going on with 
// the queue at any particular time. This is a minimum heap, where the minimum 
// value must always be in the first position, i.e. at the top of the heap.
// 
// A Sample Data Set
// -----------------
// 
// The following is a reduced version of data used in some of the test functions
// below, simplified here to make the examples shorter and more manageable. Let's
// say we have the following data about a set of patients:
// 
// 
// Name			Key Index						Value
//				(identifies person in queue)	(represents person's priority in queue)
// ----			----------------------------    ---------------------------------------
// 
// Anna			0								3 (lowest number so highest priority)
// Bella		1								15
// Carly		2								11	
// Dylan		3								17 (highest number so lowest priority)
// Emily		4								7
// 
// 
// Initial State of the Heap After Insertions
// ------------------------------------------
// 
// If the data is inserted in a queue in the order top to bottom as shown above, 
// the queue gradually builds up. The state of the heap after the last two nodes is
// worth showing, as some heap adjustment is required:
// 
// p = position, k = key, v = value
// 
// After Dylan (key 3, value 17) inserted:
//							
//							p0
//							k0
//							v3
//						   /  \
//						 p1    p2
//						 k15   k2
//						 v7	   v11
//	                    /					
//                    p3
//                    k3
//                    v17
// 
// This is fine - value 3 is the lowest value and is at the top of the heap.
// But consider the situation after the the last of the current patients, 
// Emily (key 4, value 7), is added to the queue (at the end): 
// 
//                          p0
//							k0
//							v3
//						   /  \
//						 p1    p2
//						 k15   k2
//						 v7	   v11
//	                    /  \					
//                     p3   p4
//                     k3   k4
//                     v17  v7
// 
// The problem now is that Emily has value 7 and her "parent" at this point is Bella, 
// who has a value of 15. This violates one of the heap invariants, which is that a 
// parent must have a lower value than its children. 
// 
// Therefore at this point, before the insertion process for Emily can be considered 
// complete, she and Bella must swap places, i.e. key 15 and key 14 nodes are swapped:
// 
//						    p0
//							k0
//							v3
//						   /  \
//						 p1   p2
//						 k4   k2
//						 v7	  v11
//	                    /  \					
//                     p3   p4
//                     k3   k1
//                     v17  v15 
//
// Now the heap invariant has been restored and the insertion process is complete.
// After the initial insertions of keys 1-4, the arrays would store the following data:
// 
// ki     0   1   2   3   4
// -------------------------
// vals   3   15  11  17  7
// pm     0   4   2   3   1
// im     0   4   2   3   1
// 
// ki = key index 
//		- the key for the name
// 
// values = values
//		- the key in the top row corresponds to this value
// 
// pm = position map 
//		- the key in the top row is stored at this position in the heap
// 
// im = inverse map 
//      - as the name implies, this is an inversion of the position map: 
//        now think of the number in the top row as the position in the heap; 
//        at this position, this key is stored
//
// 
// State of the Heap After a Removal
// ---------------------------------
//
// Let's say that Emily (key 4, value 7) is then removed from the queue. The removal
// process would swap her node for the last node in the queue, so mid-removal,
// the heap would look like this:
// 
//                          p0
//							k0
//							v3
//						   /  \
//						 p1   p2
//						 k1   k2
//						 v15  v11
//	                    /  \					
//                     p3   p4
//                     k3   k4
//                     v17  v7
// 
// Removing Emily's node is easier now, since it is a case now of removing the last node:
//
//                          k0
//							v3
//						   /  \
//						 p1   p2
//						 k1   k2
//						 v15  v11
//	                    /					
//                     p3 
//                     k3
//                     v17
//
// In this case, there is no need for any further action, as the heap invariants are
// satisfied. The underlying arrays would now look like this (-1 indicates a null entry, 
// which in this instance has overwritten Emily's data):
// 
// ki      0   1   2   3   4
// --------------------------
// vals    3   15  11  17  -1
// pm      0   1   2   3   -1
// im      0   1   2   3   -1

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <vector>

#include "Indexed_Priority_Queue.h"

// Main test functions
void testConcept();
void testDeletedIPQTypesFunctions();
void testEmptyIPQ();
void testCopyConstructor();
void testMoveConstructor();
void testCopyAssignmentOperator();
void testMoveAssignmentOperator();

void testOneElementIPQ();
void testPollIPQ();
void testContainsAndRemoveCharIPQ();
void testContainsAndRemoveIPQ();
void testDecreaseValue();
void testIncreaseValue();
void testUpdateValue();

// Supplementary test functions
//void printIPQ(IndexedPriorityQueue<int, int>& ipq);

// Utility functions declarations
void print_separator();
void printLogStart(const char* s);
void printLogEnd(const char* s);
void printSpaces(int noSpaces);
void printUnderscores(int noUnderscores);

int main() {
	// Call test functions
	testConcept();
	testDeletedIPQTypesFunctions();
	testEmptyIPQ();
	testCopyConstructor();
	testMoveConstructor();
	testCopyAssignmentOperator();
	testMoveAssignmentOperator();

	testOneElementIPQ();
	testPollIPQ();
	testContainsAndRemoveCharIPQ();
	testContainsAndRemoveIPQ();
	testDecreaseValue();
	testIncreaseValue();
	testUpdateValue();
}

void print_separator() {
	std::cout << "\n--------------------------------------------------------------\n";
}

void printLogStart(const char* s) {
	std::cout << "Start of " << s << "\n\n";
}

void printLogEnd(const char* s) {
	std::cout << "\n\nEnd of " << s << "\n\n";
}

// Prints a space character to standard output, noSpaces times.
void printSpaces(int noSpaces) {
	for (int i = 0; i < noSpaces; i++)
		std::cout << " ";
}

// Prints an underscore character to standard output, noUnderscores times.
void printUnderscores(int noUnderscores) {
	for (int i = 0; i < noUnderscores; i++)
		std::cout << "_";
}

/******************************************************************************************/
/******************************* Test Functions *******************************************/

// A simple wrapper class for an integer (no equality operators defined)
class WrappedInt {
public:
	WrappedInt() = default;
	WrappedInt(int num) : m_number{ num } {}
	friend std::ostream& operator<<(std::ostream& out, const WrappedInt& wi);
	int getNumber(int num) const { return m_number; }
	void setNumber(int num) { m_number = num; }
private:
	int m_number{};
};

std::ostream& operator<<(std::ostream& out, const WrappedInt& wi) {
	out << "Integer value: " << wi.m_number;
	return out;
}

// Defining a default spaceship operator provides the comparison operators
// needed to be able to instantiate a queue of this type.
class WrappedLong {
public:
	WrappedLong() = default;
	WrappedLong(long num) : m_number{ num } { }	// Converting constructor
	friend std::ostream& operator<<(std::ostream& out, const WrappedLong& wi);
	int getNumber(long num) const { return m_number; }
	void setNumber(long num) { m_number = num; }

	// Should give us our comparison operators
	auto operator<=>(const WrappedLong& rhs) const = default;
private:
	long m_number{};
};

std::ostream& operator<<(std::ostream& out, const WrappedLong& wl) {
	out << "Long value: " << wl.m_number;
	return out;
}

void testConcept() {
	printLogStart(__FUNCTION__);
	std::cout << std::boolalpha;

	// 1. A class with no equality operators
	std::cout << "(1) A queue of WrappedInt should not work...\n\n";
	WrappedInt wi1;		// Should store 0
	WrappedInt wi2(50);	// Should store 50

	std::cout << "wi1: " << wi1 << '\n';
	std::cout << "wi2: " << wi2 << '\n';

	// Error: no comparison operators defined for WrappedInt
	//std::cout << "wi1 > wi2: " << (wi1 > wi2) << '\n';
	//std::cout << "wi1 < wi2: " << (wi1 < wi2) << '\n';

	// Therefore WrappedInt cannot satisfy the IPQ constraints
	//IndexedPriorityQueue<WrappedInt> q1(0, 10);
	print_separator();

	/**************************************************************************/

	// 2. A class with equality operators
	std::cout << "\n\n(2) A queue of WrappedLong should (partially) work...\n\n";
	WrappedLong wl1;		// Should store 0
	WrappedLong wl2(50);	// Should store 50

	std::cout << "wl1: " << wl1 << '\n';
	std::cout << "wl2: " << wl2 << "\n\n";

	// Comparison operators defined for WrappedLong (via spaceship operator)
	std::cout << "wl1 > wi2: " << (wl1 > wl2) << '\n';
	std::cout << "wl1 < wi2: " << (wl1 < wl2) << '\n';
	bool less = std::less<WrappedLong>{}(wl1, wl2);
	std::cout << "wl1 is std::less than wl2...\n";

	// WrappedLong satisfies the DEFINED IPQ constraints - 
	// a queue of WrappedLong CAN be instantiated
	IndexedPriorityQueue<WrappedLong> q2(0, 10);
	long lvals[] = { 50l, 10l, 15l, 6l };


	for (int i = 0; i < std::size(lvals); i++)
		q2.insert(i, lvals[i]);	// Runs WrappedLong converting constructor

	// Output some details about q2
	// Cannot output contents of a WrappedLong queue.
	// The print function would need to be specialised for this type to work
	// (needs a not operator etc).
	std::cout << "Is q2 empty:       " << q2.isEmpty() << '\n';
	std::cout << "q2 size:           " << q2.size() << '\n';

	// The first four keys should be found - the rest should not be!
	for (int i = 0; i < 10; ++i)
		// Runs WrappedLong converting constructor
		std::cout << "q2 contains key " << q2.contains(i) << '\n';
		
	print_separator();

	/**************************************************************************/

	// 3. Use a primitive type as the value - should work fine
	std::cout << "\n\n(3) Check a queue of longs works...\n";
	IndexedPriorityQueue<long> q3(0, 10);
		
	// Insert a few (long) values
	for (int i = 0; i < std::size(lvals); i++)
		q3.insert(i, lvals[i]);

	std::cout << "\nContents of q3:\n\n";
	q3.printArrays();
	std::cout << "Is q3 empty:       " << q3.isEmpty() << '\n';
	std::cout << "q3 size:           " << q3.size() << '\n';

	// The first four keys should be found - the rest should not be!
	for (int i = 0; i < 10; ++i)
		std::cout << "q3 contains key "    << q3.contains(i) << '\n';

	printLogEnd(__FUNCTION__);
}

//void printIPQ(IndexedPriorityQueue<int, int>& ipq) {
//	IndexedPriorityQueue<int, int> tempIPQ = ipq;
//
//	while (!ipq.isEmpty()) {
//		std::pair<int, int> tempPair;
//		tempPair = ipq.top();
//		ipq.pop();
//		std::cout << "Key = " << tempPair.first << "\tValue = " << tempPair.second << "\n";
//	}
//	std::cout << "\n";
//}


// There is an class template specialisation for an IPQ of doubles.
// It has a private constructor.
// This is an experimentation to see how to prevent a class template being instantiated
// for a certain data type.
// There's no absolute reason why a double couldn't be used for a queue, although I would 
// think priorities being based on numbers with fractions is a bit impractical, so I think 
// in terms of trying out how to do this, choosing to experiment with double is a good choice.
void testDeletedIPQTypesFunctions() {
	printLogStart(__FUNCTION__);
	std::cout << std::boolalpha;


	// 1. Instantiating an IPQ of type double is prevented altogether
	//IndexedPriorityQueue<double> q1(0, 0); // A double queue fails static_assert	
	
	
	IndexedPriorityQueue<int> q2(0, 0);		 // No problem instantiating an int type queue
	std::cout << "Is q2 empty: " << q2.isEmpty() << "\n\n";

	// 2. Preventing an IPQ of type short from using a specific function
	// Again, this is an arbitrary example to illustrate how this works.
	// No real design reason why a short IPQ shouldn't be able to use the contains
	// operation, but it's a useful enough case study!
	IndexedPriorityQueue<short> q3(0, 0);		 // No problem instantiating a short type queue
	std::cout << "Is q3 empty: " << q3.isEmpty() << '\n';

	q3.insert(5, 2);
	q3.printArrays();
	std::cout << "Is q3 empty:       " << q3.isEmpty() << '\n';
	std::cout << "q3 size:           " << q3.size() << '\n';
	std::cout << "q3 contains key 5: " << q3.contains(5) << '\n';
	std::cout << "q3 contains key 8: " << q3.contains(8) << '\n';

	// Try a decrease... should fail for short (arbitrary example)
	//q3.decrease(5, 1); // Error - deleted function...
	q3.increase(5, 10);	 // Fine
	q3.printArrays();

	printLogEnd(__FUNCTION__);
}

void testEmptyIPQ() {
	printLogStart(__FUNCTION__);

	int n{ 0 };
	int n2 = (0 - 1) / 2;
	std::cout << "n2: " << n2 << '\n';

	IndexedPriorityQueue<int> q1(0, 0);

	std::cout << std::boolalpha;

	int num1{ 10 };
	int num2{ 10 };
	std::cout << num1 << " is less than " << num2 << ": " << std::less<int>{}(num1, num2) << "\n\n";

	std::cout << "q1 is empty:      " << q1.isEmpty() << '\n';
	std::cout << "q1 size:          " << q1.size() << '\n';
	std::cout << "q1 is a min heap: " << q1.isMinHeap() << '\n';
	std::cout << "\nCurrent contents of this IPQ:";
	q1.printArrays();

	int keyIndex = -10;
	// Test an negative index...
	try {
		//int keyIndex = -10;
		//std::cout << "IPQ contains " << keyIndex << ": " << q1.contains(keyIndex) << '\n';

		// Test a zero index...
		keyIndex = 0;
		std::cout << "IPQ contains " << keyIndex << ": " << q1.contains(keyIndex) << '\n';

		// Test an index greater than the capacity of the underlying heap...
		keyIndex = 50;
		std::cout << "IPQ contains " << keyIndex << ": " << q1.contains(keyIndex) << '\n';

		// Test a valid key index not found
		keyIndex = 10;
		std::cout << "IPQ contains " << keyIndex << ": " << q1.contains(keyIndex) << '\n';
	}
	catch (const KeyOutOfBoundsException& koob) {
		std::cout << "\ncontains failed: " << koob.what() << '\n';
	}

	// Check peek key min index
	try {
		std::cout << "The index of the minimum key is... " << q1.peekMinKeyIndex() << '\n';
	}
	catch (const QueueEmptyException& qee) {
		std::cout << "\nPeek min key failed: " << qee.what() << '\n';
	}

	printLogEnd(__FUNCTION__);
}


void testCopyConstructor() {
	printLogStart(__FUNCTION__);
	std::cout << std::boolalpha;

	// 1. Test copy construct from empty queue
	std::cout << "(1) Copy construct from an empty IPQ...\n";
	IndexedPriorityQueue<int> q1(0, 0);

	std::cout << "q1 is empty:      " << q1.isEmpty() << '\n';
	std::cout << "q1 size:          " << q1.size() << '\n';
	std::cout << "q1 is a min heap: " << q1.isMinHeap() << '\n';
	std::cout << "\nCurrent contents of q1:";
	q1.printArrays();

	std::cout << "Copy construct from q1...\n";
	IndexedPriorityQueue<int> q2(q1);

	std::cout << "\n\nState of objects after copy constructing...\n\n";

	std::cout << "q1 is empty:      " << q1.isEmpty() << '\n';
	std::cout << "q1 size:          " << q1.size() << '\n';
	std::cout << "q1 is a min heap: " << q1.isMinHeap() << '\n';
	std::cout << "\nCurrent contents of q1:";
	q1.printArrays();

	std::cout << "q2 is empty:      " << q2.isEmpty() << '\n';
	std::cout << "q2 size:          " << q2.size() << '\n';
	std::cout << "q2 is a min heap: " << q2.isMinHeap() << '\n';
	std::cout << "\nCurrent contents of q2:";
	q2.printArrays();
	print_separator();

	/*****************************************************************************/

	// 2. Test copy construct from populated queue
	std::cout << "\n\n(2) Copy construct from populated queue...\n";
	IndexedPriorityQueue<int> q3(0, 0);

	// Insert the values into the tree
	int values[] = { 3, 15, 11, 17, 7 };

	for (int i = 0; i < std::size(values); i++)
		q3.insert(i, values[i]);

	std::cout << "q3 is empty:      " << q3.isEmpty() << '\n';
	std::cout << "q3 size:          " << q3.size() << '\n';
	std::cout << "q3 is a min heap: " << q3.isMinHeap() << '\n';
	std::cout << "\nCurrent contents of q3:";
	q3.printArrays();

	std::cout << "\n\nCopy construct q4 from q3...\n\n";
	IndexedPriorityQueue<int> q4(q3);

	std::cout << "\n\nState of objects after copy constructing...\n\n";
	std::cout << "q3 is empty:      " << q3.isEmpty() << '\n';
	std::cout << "q3 size:          " << q3.size() << '\n';
	std::cout << "q3 is a min heap: " << q3.isMinHeap() << '\n';
	std::cout << "\nCurrent contents of q3:";
	q3.printArrays();

	std::cout << "\n\n";
	std::cout << "q4 is empty:      " << q4.isEmpty() << '\n';
	std::cout << "q4 size:          " << q4.size() << '\n';
	std::cout << "q4 is a min heap: " << q4.isMinHeap() << '\n';
	std::cout << "\nCurrent contents of q4:";
	q4.printArrays();

	printLogEnd(__FUNCTION__);
}


void testMoveConstructor() {
	printLogStart(__FUNCTION__);
	std::cout << std::boolalpha;

	// 1. Test move construct from empty queue
	std::cout << "(1) Move construct from an empty IPQ...\n";
	IndexedPriorityQueue<int> q1(0, 0);

	std::cout << "q1 is empty:      " << q1.isEmpty() << '\n';
	std::cout << "q1 size:          " << q1.size() << '\n';
	std::cout << "q1 is a min heap: " << q1.isMinHeap() << '\n';
	std::cout << "\nCurrent contents of q1:";
	q1.printArrays();

	std::cout << "Move construct from q1...\n";
	IndexedPriorityQueue<int> q2(std::move(q1));

	std::cout << "\n\nState of objects after move constructing...\n\n";

	std::cout << "q1 is empty:      " << q1.isEmpty() << '\n';
	std::cout << "q1 size:          " << q1.size() << '\n';
	std::cout << "q1 is a min heap: " << q1.isMinHeap() << '\n';
	std::cout << "\nCurrent contents of q1:";
	q1.printArrays();

	std::cout << "q2 is empty:      " << q2.isEmpty() << '\n';
	std::cout << "q2 size:          " << q2.size() << '\n';
	std::cout << "q2 is a min heap: " << q2.isMinHeap() << '\n';
	std::cout << "\nCurrent contents of q2:";
	q2.printArrays();
	print_separator();

	/*****************************************************************************/

	// 2. Test move construct from populated queue
	std::cout << "\n\n(2) Move construct from populated queue...\n";
	IndexedPriorityQueue<int> q3(0, 0);

	// Insert the values into the queue
	int values[] = { 3, 15, 11, 17, 7 };

	for (int i = 0; i < std::size(values); i++)
		q3.insert(i, values[i]);

	std::cout << "q3 is empty:      " << q3.isEmpty() << '\n';
	std::cout << "q3 size:          " << q3.size() << '\n';
	std::cout << "q3 is a min heap: " << q3.isMinHeap() << '\n';
	std::cout << "\nCurrent contents of q3:";
	q3.printArrays();

	std::cout << "\nNow move construct q4 from q3...\n";
	IndexedPriorityQueue<int> q4(std::move(q3));

	std::cout << "\n\nState of objects after move constructing...\n\n";
	std::cout << "q3 is empty:      " << q3.isEmpty() << '\n';
	std::cout << "q3 size:          " << q3.size() << '\n';
	std::cout << "q3 is a min heap: " << q3.isMinHeap() << '\n';
	std::cout << "\nCurrent contents of q3:";
	q3.printArrays();

	std::cout << "\n\n";
	std::cout << "q4 is empty:      " << q4.isEmpty() << '\n';
	std::cout << "q4 size:          " << q4.size() << '\n';
	std::cout << "q4 is a min heap: " << q4.isMinHeap() << '\n';
	std::cout << "\nCurrent contents of q4:";
	q4.printArrays();

	printLogEnd(__FUNCTION__);
}


void testCopyAssignmentOperator() {
	printLogStart(__FUNCTION__);
	std::cout << std::boolalpha;

	// 1. Test copy assign empty to empty
	std::cout << "(1) Copy assign from an empty queue into an empty queue...\n";
	IndexedPriorityQueue<int> q1(0, 0);
	std::cout << "q1 is empty:      " << q1.isEmpty() << '\n';
	std::cout << "q1 size:          " << q1.size() << '\n';
	std::cout << "q1 is a min heap: " << q1.isMinHeap() << '\n';
	std::cout << "\nCurrent contents of q1:";
	q1.printArrays();

	IndexedPriorityQueue<int> q2(0, 0);
	std::cout << "q2 is empty:      " << q2.isEmpty() << '\n';
	std::cout << "q2 size:          " << q2.size() << '\n';
	std::cout << "q2 is a min heap: " << q2.isMinHeap() << '\n';
	std::cout << "\nCurrent contents of q2:";
	q2.printArrays();

	std::cout << "\nCopy assign q2 into q1...\n";
	q1 = q2;

	std::cout << "\n\nAfter copy assign...\n";
	std::cout << "q1 is empty:      " << q1.isEmpty() << '\n';
	std::cout << "q1 size:          " << q1.size() << '\n';
	std::cout << "q1 is a min heap: " << q1.isMinHeap() << '\n';
	std::cout << "\nCurrent contents of q1:";
	q1.printArrays();

	std::cout << "q2 is empty:      " << q2.isEmpty() << '\n';
	std::cout << "q2 size:          " << q2.size() << '\n';
	std::cout << "q2 is a min heap: " << q2.isMinHeap() << '\n';
	std::cout << "\nCurrent contents of q2:";
	q2.printArrays();
	print_separator();

	/*****************************************************************************/

	// 2. Test copy assign empty to populated
	std::cout << "\n\n(2) Copy assign from an empty queue into a populated queue...\n";
	IndexedPriorityQueue<int> q3(0, 0);
	IndexedPriorityQueue<int> q4(0, 0);

	// Insert values into the q3 but leave q4 empty
	int values[] = { 3, 15, 11, 17, 7 };

	for (int i = 0; i < std::size(values); i++)
		q3.insert(i, values[i]);

	std::cout << "\nBefore copy assign...\n";
	std::cout << "Contents of q3:\n";
	std::cout << "q3 is empty:      " << q3.isEmpty() << '\n';
	std::cout << "q3 size:          " << q3.size() << '\n';
	std::cout << "q3 is a min heap: " << q3.isMinHeap() << '\n';
	std::cout << "\nCurrent contents of q3:";
	q3.printArrays();

	std::cout << "Contents of q4:\n";
	std::cout << "q4 is empty:      " << q4.isEmpty() << '\n';
	std::cout << "q4 size:          " << q4.size() << '\n';
	std::cout << "q4 is a min heap: " << q4.isMinHeap() << '\n';
	std::cout << "\nCurrent contents of q4:";
	q4.printArrays();

	std::cout << "\nCopy assign q4 into q3...\n";
	q3 = q4;

	std::cout << "\n\nAfter copy assign...\n";
	std::cout << "q3 is empty:      " << q3.isEmpty() << '\n';
	std::cout << "q3 size:          " << q3.size() << '\n';
	std::cout << "q3 is a min heap: " << q3.isMinHeap() << '\n';
	std::cout << "\nCurrent contents of q3:";
	q3.printArrays();

	std::cout << "q4 is empty:      " << q4.isEmpty() << '\n';
	std::cout << "q4 size:          " << q4.size() << '\n';
	std::cout << "q4 is a min heap: " << q4.isMinHeap() << '\n';
	std::cout << "\nCurrent contents of q4:";
	q4.printArrays();
	print_separator();

	/*****************************************************************************/

	// 3. Test copy assign populated into empty
	std::cout << "\n\n(3) Copy assign from a populated queue into an empty queue...\n";

	IndexedPriorityQueue<int> q5(0, 0);
	IndexedPriorityQueue<int> q6(0, 0);

	// Populate q6 but not q5
	for (int i = 0; i < std::size(values); i++)
		q6.insert(i, values[i]);

	std::cout << "\nBefore copy assign...\n";
	std::cout << "q5 is empty:      " << q5.isEmpty() << '\n';
	std::cout << "q5 size:          " << q5.size() << '\n';
	std::cout << "q5 is a min heap: " << q5.isMinHeap() << '\n';
	std::cout << "\nCurrent contents of q5:";
	q5.printArrays();

	std::cout << "q6 is empty:      " << q6.isEmpty() << '\n';
	std::cout << "q6 size:          " << q6.size() << '\n';
	std::cout << "q6 is a min heap: " << q6.isMinHeap() << '\n';
	std::cout << "\nCurrent contents of q6:";
	q6.printArrays();

	std::cout << "\n\nCopy assign populated q6 into empty q5...\n";
	q5 = q6;

	std::cout << "\nAfter copy assign...\n";
	std::cout << "q5 is empty:      " << q5.isEmpty() << '\n';
	std::cout << "q5 size:          " << q5.size() << '\n';
	std::cout << "q5 is a min heap: " << q5.isMinHeap() << '\n';
	std::cout << "\nCurrent contents of q5:";
	q5.printArrays();

	std::cout << "q6 is empty:      " << q6.isEmpty() << '\n';
	std::cout << "q6 size:          " << q6.size() << '\n';
	std::cout << "q6 is a min heap: " << q6.isMinHeap() << '\n';
	std::cout << "\nCurrent contents of q6:";
	q6.printArrays();
	print_separator();

	/*****************************************************************************/

	// 4. Test copy assign populated into populated
	std::cout << "\n\n(4) Copy assign from a populated tree into another populated tree...\n";

	IndexedPriorityQueue<int> q7(0, 0);
	IndexedPriorityQueue<int> q8(0, 0);

	// Populate q7
	for (int i = 0; i < std::size(values); i++)
		q7.insert(i, values[i]);

	// Populate q8 with some different contents
	int values2[] = { 9, 6, 12, 8, 2, 14, 20, 34, 23, 19 };
	for (int i = 0; i < std::size(values2); i++)
		q8.insert(i, values2[i]);

	std::cout << "\nBefore copy assign...\n";
	std::cout << "q7 is empty:      " << q7.isEmpty() << '\n';
	std::cout << "q7 size:          " << q7.size() << '\n';
	std::cout << "q7 is a min heap: " << q7.isMinHeap() << '\n';
	std::cout << "\nCurrent contents of q7:";
	q7.printArrays();

	std::cout << "q8 is empty:      " << q8.isEmpty() << '\n';
	std::cout << "q8 size:          " << q8.size() << '\n';
	std::cout << "q8 is a min heap: " << q8.isMinHeap() << '\n';
	std::cout << "\nCurrent contents of q8:";
	q8.printArrays();

	std::cout << "\n\nCopy assign populated q8 into q7 (has different contents)...\n";
	q7 = q8;
	std::cout << "\nAfter copy assign...\n";
	std::cout << "q7 is empty:      " << q7.isEmpty() << '\n';
	std::cout << "q7 size:          " << q7.size() << '\n';
	std::cout << "q7 is a min heap: " << q7.isMinHeap() << '\n';
	std::cout << "\nCurrent contents of q7:";
	q7.printArrays();

	std::cout << "Contents of tree3:\n";
	std::cout << "q8 is empty:      " << q8.isEmpty() << '\n';
	std::cout << "q8 size:          " << q8.size() << '\n';
	std::cout << "q8 is a min heap: " << q8.isMinHeap() << '\n';
	std::cout << "\nCurrent contents of q8:";
	q8.printArrays();

	printLogEnd(__FUNCTION__);
}

void testMoveAssignmentOperator() {
	printLogStart(__FUNCTION__);
	std::cout << std::boolalpha;

	// 1. Test move assign empty to empty
	std::cout << "(1) Move assign from an empty queue into an empty queue...\n";
	IndexedPriorityQueue<int> q1(0, 0);
	std::cout << "q1 is empty:      " << q1.isEmpty() << '\n';
	std::cout << "q1 size:          " << q1.size() << '\n';
	std::cout << "q1 is a min heap: " << q1.isMinHeap() << '\n';
	std::cout << "\nCurrent contents of q1:";
	q1.printArrays();

	IndexedPriorityQueue<int> q2(0, 0);
	std::cout << "q2 is empty:      " << q2.isEmpty() << '\n';
	std::cout << "q2 size:          " << q2.size() << '\n';
	std::cout << "q2 is a min heap: " << q2.isMinHeap() << '\n';
	std::cout << "\nCurrent contents of q2:";
	q2.printArrays();

	std::cout << "\nCopy assign q2 into q1...\n";
	q1 = std::move(q2);

	std::cout << "\n\nAfter move assign...\n";
	std::cout << "q1 is empty:      " << q1.isEmpty() << '\n';
	std::cout << "q1 size:          " << q1.size() << '\n';
	std::cout << "q1 is a min heap: " << q1.isMinHeap() << '\n';
	std::cout << "\nCurrent contents of q1:";
	q1.printArrays();

	std::cout << "q2 is empty:      " << q2.isEmpty() << '\n';
	std::cout << "q2 size:          " << q2.size() << '\n';
	std::cout << "q2 is a min heap: " << q2.isMinHeap() << '\n';
	std::cout << "\nCurrent contents of q2:";
	q2.printArrays();
	print_separator();

	/*****************************************************************************/

	// 2. Test move assign empty to populated
	std::cout << "\n\n(2) Move assign from an empty queue into a populated queue...\n";
	IndexedPriorityQueue<int> q3(0, 0);
	IndexedPriorityQueue<int> q4(0, 0);

	// Insert values into the q3 but leave q4 empty
	int values[] = { 3, 15, 11, 17, 7 };

	for (int i = 0; i < std::size(values); i++)
		q3.insert(i, values[i]);

	std::cout << "\nBefore move assign...\n";
	std::cout << "Contents of q3:\n";
	std::cout << "q3 is empty:      " << q3.isEmpty() << '\n';
	std::cout << "q3 size:          " << q3.size() << '\n';
	std::cout << "q3 is a min heap: " << q3.isMinHeap() << '\n';
	std::cout << "\nCurrent contents of q3:";
	q3.printArrays();

	std::cout << "Contents of q4:\n";
	std::cout << "q4 is empty:      " << q4.isEmpty() << '\n';
	std::cout << "q4 size:          " << q4.size() << '\n';
	std::cout << "q4 is a min heap: " << q4.isMinHeap() << '\n';
	std::cout << "\nCurrent contents of q4:";
	q4.printArrays();

	std::cout << "\nMove assign q4 into q3...\n";
	q3 = std::move(q4);

	std::cout << "\n\nAfter move assign...\n";
	std::cout << "q3 is empty:      " << q3.isEmpty() << '\n';
	std::cout << "q3 size:          " << q3.size() << '\n';
	std::cout << "q3 is a min heap: " << q3.isMinHeap() << '\n';
	std::cout << "\nCurrent contents of q3:";
	q3.printArrays();

	std::cout << "q4 is empty:      " << q4.isEmpty() << '\n';
	std::cout << "q4 size:          " << q4.size() << '\n';
	std::cout << "q4 is a min heap: " << q4.isMinHeap() << '\n';
	std::cout << "\nCurrent contents of q4:";
	q4.printArrays();
	print_separator();

	/*****************************************************************************/

	// 3. Test move assign populated into empty
	std::cout << "\n\n(3) Move assign from a populated queue into an empty queue...\n";

	IndexedPriorityQueue<int> q5(0, 0);
	IndexedPriorityQueue<int> q6(0, 0);

	// Populate q6 but not q5
	for (int i = 0; i < std::size(values); i++)
		q6.insert(i, values[i]);

	std::cout << "\nBefore move assign...\n";
	std::cout << "q5 is empty:      " << q5.isEmpty() << '\n';
	std::cout << "q5 size:          " << q5.size() << '\n';
	std::cout << "q5 is a min heap: " << q5.isMinHeap() << '\n';
	std::cout << "\nCurrent contents of q5:";
	q5.printArrays();

	std::cout << "q6 is empty:      " << q6.isEmpty() << '\n';
	std::cout << "q6 size:          " << q6.size() << '\n';
	std::cout << "q6 is a min heap: " << q6.isMinHeap() << '\n';
	std::cout << "\nCurrent contents of q6:";
	q6.printArrays();

	std::cout << "\n\nMove assign populated q6 into empty q5...\n";
	q5 = std::move(q6);

	std::cout << "\nAfter move assign...\n";
	std::cout << "q5 is empty:      " << q5.isEmpty() << '\n';
	std::cout << "q5 size:          " << q5.size() << '\n';
	std::cout << "q5 is a min heap: " << q5.isMinHeap() << '\n';
	std::cout << "\nCurrent contents of q5:";
	q5.printArrays();

	std::cout << "q6 is empty:      " << q6.isEmpty() << '\n';
	std::cout << "q6 size:          " << q6.size() << '\n';
	std::cout << "q6 is a min heap: " << q6.isMinHeap() << '\n';
	std::cout << "\nCurrent contents of q6:";
	q6.printArrays();
	print_separator();

	/*****************************************************************************/

	// 4. Test move assign populated into populated
	std::cout << "\n\n(4) Move assign from a populated tree into another populated tree...\n";

	IndexedPriorityQueue<int> q7(0, 0);
	IndexedPriorityQueue<int> q8(0, 0);

	// Populate q7
	for (int i = 0; i < std::size(values); i++)
		q7.insert(i, values[i]);

	// Populate q8 with some different contents
	int values2[] = { 9, 6, 12, 8, 2, 14, 20, 34, 23, 19 };
	for (int i = 0; i < std::size(values2); i++)
		q8.insert(i, values2[i]);

	std::cout << "\nBefore move assign...\n";
	std::cout << "q7 is empty:      " << q7.isEmpty() << '\n';
	std::cout << "q7 size:          " << q7.size() << '\n';
	std::cout << "q7 is a min heap: " << q7.isMinHeap() << '\n';
	std::cout << "\nCurrent contents of q7:";
	q7.printArrays();

	std::cout << "q8 is empty:      " << q8.isEmpty() << '\n';
	std::cout << "q8 size:          " << q8.size() << '\n';
	std::cout << "q8 is a min heap: " << q8.isMinHeap() << '\n';
	std::cout << "\nCurrent contents of q8:";
	q8.printArrays();

	std::cout << "\n\nMove assign populated q8 into q7 (has different contents)...\n";
	q7 = std::move(q8);

	std::cout << "\nAfter move assign...\n";
	std::cout << "q7 is empty:      " << q7.isEmpty() << '\n';
	std::cout << "q7 size:          " << q7.size() << '\n';
	std::cout << "q7 is a min heap: " << q7.isMinHeap() << '\n';
	std::cout << "\nCurrent contents of q7:";
	q7.printArrays();

	std::cout << "Contents of tree3:\n";
	std::cout << "q8 is empty:      " << q8.isEmpty() << '\n';
	std::cout << "q8 size:          " << q8.size() << '\n';
	std::cout << "q8 is a min heap: " << q8.isMinHeap() << '\n';
	std::cout << "\nCurrent contents of q8:";
	q8.printArrays();

	printLogEnd(__FUNCTION__);
}


/************************************************************************************/

// Other Test Functions
// --------------------

void testOneElementIPQ() {
	printLogStart(__FUNCTION__);

	IndexedPriorityQueue<int> q1(0, 0);
	std::cout << std::boolalpha;
	std::vector<std::string> names;
	names.push_back("Anna");
	q1.insert(0, 3);

	std::cout << "q1 is empty:       " << q1.isEmpty() << '\n';
	std::cout << "q1 size:           " << q1.size() << '\n';
	std::cout << "q1 is a min heap:  " << q1.isMinHeap() << '\n';
	std::cout << "peek min key:      " << q1.peekMinKeyIndex() << '\n';
	std::cout << "q1 contains key 0: " << q1.contains(0) << '\n';
	std::cout << "q1 contains key 5: " << q1.contains(5) << '\n';

	std::cout << "\nCurrent contents of this IPQ:";
	q1.printArrays();

	std::cout << "\n\n";
	std::optional<int> minVal = q1.pollMinValue();
	if (minVal.has_value())
		std::cout << "poll min val:        " << minVal.value() << '\n';
	std::cout << "\nCurrent contents of this IPQ:";
	q1.printArrays();

	std::cout << "\n\n";
	std::cout << "q1 is empty:       " << q1.isEmpty() << '\n';
	std::cout << "q1 size:           " << q1.size() << '\n';
	std::cout << "q1 is a min heap:  " << q1.isMinHeap() << '\n';

	minVal = q1.peekMinValue();
	if (minVal.has_value())
		std::cout << "q1 peek min val:   " << minVal.value() << '\n';

	try {
		std::cout << "peek min key:      " << q1.peekMinKeyIndex() << '\n';
	}
	catch (QueueEmptyException& qee) {
		std::cout << qee.what() << '\n';
	}

	std::cout << "q1 contains key 0: " << q1.contains(0) << '\n';
	std::cout << "q1 contains key 5: " << q1.contains(5) << '\n';

	std::cout << "\n\n";
	try {
		std::optional<int> removed = q1.removeKey(0);
		if (removed.has_value())
			std::cout << "Remove key 0 returned old key " << removed.value() << '\n';
	}
	catch (std::exception& ex) {
		std::cout << "Hitting the catch block...\n";
		std::cout << "Exception is: " << typeid(ex).name() << '\n';
		std::cout << ex.what() << '\n';
	}

	printLogEnd(__FUNCTION__);
}



void testPollIPQ() {
	printLogStart(__FUNCTION__);

	IndexedPriorityQueue<int> q1(0, 0);
	std::cout << std::boolalpha;
	int values[20] = { 3, 15, 11, 17, 7, 9, 2, 1, 6, 5, 16, 4 };

	for (int i = 0; i < 12; i++)
		q1.insert(i, values[i]);

	std::cout << "q1 is empty:       " << q1.isEmpty() << '\n';
	std::cout << "q1 size:           " << q1.size() << '\n';
	std::cout << "q1 is a min heap:  " << q1.isMinHeap() << '\n';
	std::cout << "peek min key:      " << q1.peekMinKeyIndex() << '\n';

	std::cout << "\nCurrent contents of this IPQ:";
	q1.printArrays();

	std::cout << "\n\n";
	for (int i = 0; i < std::size(values); i++)
		std::cout << "IPQ contains key " << i << ":\t" << q1.contains(i) << '\n';

	print_separator();

	/*********************************************************************************/

	// Insert another value
	//std::cout << "\nCurrent contents of this IPQ after inserting key 12/value 2:";
	//q1.insert(12, 2);
	//q1.printArrays();

	std::vector<int> queueValues;

	// Try polling
	while (!q1.isEmpty()) {
		print_separator();
		std::cout << "\n\n";
		std::optional<int> minVal = q1.pollMinValue();
		if (minVal.has_value()) {
			std::cout << "min val: " << minVal.value() << '\n';
			queueValues.push_back(minVal.value());
		}

		std::cout << "\nCurrent contents of this IPQ after polling:";
		q1.printArrays();
		std::cout << "q1 is empty:       " << q1.isEmpty() << '\n';
		std::cout << "q1 size:           " << q1.size() << '\n';
		std::cout << "q1 is a min heap:  " << q1.isMinHeap() << '\n';

		try {
			std::cout << "peek min key:      " << q1.peekMinKeyIndex() << '\n';
		}
		catch (QueueEmptyException& qe) {
			std::cout << qe.what();
		}
	}

	std::cout << "\n\nAT END OF POLLING!!\n\n";
	std::cout << "Values in the IPQ in ascending order:\n\n";
	for (int i = 0; i < queueValues.size(); i++)
		std::cout << queueValues[i] << "  ";
	std::cout << "\n\n";
	print_separator();

	/*************************************************************************/

	std::cout << "\n\nNow try rebuilding the queue as it was...\n";
	for (int i = 0; i < 12; i++)
		q1.insert(i, values[i]);
	q1.insert(12, 2);

	std::cout << "q1 is empty:       " << q1.isEmpty() << '\n';
	std::cout << "q1 size:           " << q1.size() << '\n';
	std::cout << "q1 is a min heap:  " << q1.isMinHeap() << '\n';
	std::cout << "peek min key:      " << q1.peekMinKeyIndex() << '\n';

	std::cout << "\nCurrent contents of this IPQ:";
	q1.printArrays();

	printLogEnd(__FUNCTION__);
}

void testContainsAndRemoveCharIPQ() {
	printLogStart(__FUNCTION__);
	IndexedPriorityQueue<char> q1(0, 0);
	std::cout << std::boolalpha;

	char values[25] = { 'C', 'O', 'K', 'Q', 'G', 'I', 'B', 'A', 'F', 'E', 'P', 'D', 'B' };
	std::vector<std::string> names(25);
	std::fill(names.begin(), names.end(), "None");

	// Array initialised - overwrite with meaningful names
	names[0] = "Anna";
	names[1] = "Bella";
	names[2] = "Carly";
	names[3] = "Dylan";
	names[4] = "Emily";
	names[5] = "Fred";
	names[6] = "George";
	names[7] = "Henry";
	names[8] = "Isaac";
	names[9] = "James";
	names[10] = "Kelly";
	names[11] = "Laura";
	names[12] = "Barney";

	// Setup keys to names mapping
	std::map<char, std::string> keysToNames;
	for (int i = 0; i < 25; i++)
		keysToNames[i] = names[i];

	for (int i = 0; i < 13; i++)
		q1.insert(i, values[i]);

	std::cout << "q1 is empty:        " << q1.isEmpty() << '\n';
	std::cout << "q1 size:            " << q1.size() << '\n';
	std::cout << "q1 is a min heap:   " << q1.isMinHeap() << '\n';
	std::cout << "peek min key index: " << q1.peekMinKeyIndex() << '\n';

	std::cout << "\nCurrent contents of this IPQ:\n\n";

	q1.printNames(keysToNames);
	q1.printArrays();

	std::cout << "\n\n";
	for (int i = 0; i < std::size(values); i++)
		std::cout << "IPQ contains key " << i << ":\t" << q1.contains(i) << '\n';
	print_separator();

	/*******************************************************************************/

	// Removing from the IPQ
	std::cout << "\nNow testing removing items from within the IPQ (not polling):\n\n";
	std::optional<char> removeVal;

	// Emily
	std::cout << "\nRemove Emily...\n";

	try {
		removeVal = q1.removeKey(4);		// Remove Emily from IPQ
	}
	catch (std::exception& ex) {
		std::cout << "Hitting the catch block...\n";
		std::cout << "Exception is: " << typeid(ex).name() << '\n';
		std::cout << ex.what() << '\n';
	}

	if (removeVal.has_value())
		std::cout << "Emily's removed value is: " << removeVal.value() << '\n';
	else
		std::cout << "Error: no value returned from remove of Emily...\n";

	std::cout << "\nCurrent contents of this IPQ:\n\n";
	q1.printArrays();
	print_separator();

	/*******************************************************************************/

	// Kelly
	std::cout << "\nRemove Kelly...\n";

	try {
		removeVal = q1.removeKey(10);		// Remove Kelly from IPQ
	}
	catch (std::exception& ex) {
		std::cout << "Hitting the catch block...\n";
		std::cout << "Exception is: " << typeid(ex).name() << '\n';
		std::cout << ex.what() << '\n';
	}

	if (removeVal.has_value())
		std::cout << "Kelly's removed value is: " << removeVal.value() << '\n';
	else
		std::cout << "Error: no value returned from remove of Kelly...\n";

	std::cout << "\nCurrent contents of this IPQ:\n\n";
	q1.printArrays();
	print_separator();

	/*******************************************************************************/

	// Fred
	std::cout << "\nRemove Fred...\n";

	try {
		removeVal = q1.removeKey(5);		// Remove Fred from IPQ
	}
	catch (std::exception& ex) {
		std::cout << "Hitting the catch block...\n";
		std::cout << "Exception is: " << typeid(ex).name() << '\n';
		std::cout << ex.what() << '\n';
	}

	if (removeVal.has_value())
		std::cout << "Fred's removed value is: " << removeVal.value() << '\n';
	else
		std::cout << "Error: no value returned from remove of Fred...\n";

	std::cout << "\nCurrent contents of this IPQ:\n\n";
	q1.printArrays();
	print_separator();

	/*******************************************************************************/

	// Anna
	std::cout << "\nRemove Anna...\n";

	try {
		removeVal = q1.removeKey(0);		// Remove Anna from IPQ
	}
	catch (std::exception& ex) {
		std::cout << "Hitting the catch block...\n";
		std::cout << "Exception is: " << typeid(ex).name() << '\n';
		std::cout << ex.what() << '\n';
	}

	if (removeVal.has_value())
		std::cout << "Anna's removed value is: " << removeVal.value() << '\n';
	else
		std::cout << "Error: no value returned from remove of Anna...\n";

	std::cout << "\nCurrent contents of this IPQ:\n\n";
	q1.printArrays();
	print_separator();

	/*******************************************************************************/

	// Key not present in IPQ
	std::cout << "\nRemove a non-existent key (23)...\n";
	removeVal.reset();

	try {
		removeVal = q1.removeKey(23);		// Remove 23 from IPQ	
	}
	catch (std::exception& ex) {
		std::cout << "Hitting the catch block...\n";
		std::cout << "Exception is: " << typeid(ex).name() << '\n';
		std::cout << ex.what() << '\n';
	}

	if (removeVal.has_value())
		std::cout << "ERROR - remove key 23 returned: " << removeVal.value() << '\n';
	else
		std::cout << "Cannot remove key 23 as it is not in the IPQ...\n";

	std::cout << "\nCurrent contents of this IPQ:\n\n";
	q1.printArrays();
	print_separator();

	/*******************************************************************************/

	// Dylan
	std::cout << "\nRemove Dylan...\n";
	try {
		removeVal = q1.removeKey(3);		// Remove Dylan from IPQ	
	}
	catch (std::exception& ex) {
		std::cout << "Hitting the catch block...\n";
		std::cout << "Exception is: " << typeid(ex).name() << '\n';
		std::cout << ex.what() << '\n';
	}
	if (removeVal.has_value())
		std::cout << "Dylan's removed value is: " << removeVal.value() << '\n';
	else
		std::cout << "Error: no value returned from remove of Dylan...\n";

	std::cout << "\nCurrent contents of this IPQ:\n\n";
	q1.printArrays();
	print_separator();

	/*******************************************************************************/

	// Bella
	std::cout << "\nRemove Bella...\n";
	try {
		removeVal = q1.removeKey(1);		// Remove Bella from IPQ	
	}
	catch (std::exception& ex) {
		std::cout << "Hitting the catch block...\n";
		std::cout << "Exception is: " << typeid(ex).name() << '\n';
		std::cout << ex.what() << '\n';
	}
	if (removeVal.has_value())
		std::cout << "Bella's removed value is: " << removeVal.value() << '\n';
	else
		std::cout << "Error: no value returned from remove of Bella ...\n";

	std::cout << "\nCurrent contents of this IPQ:\n\n";
	q1.printArrays();
	print_separator();

	/*******************************************************************************/

	// Carly
	std::cout << "\nRemove Carly...\n";

	try {
		removeVal = q1.removeKey(2);		// Remove Carly from IPQ	
	}
	catch (std::exception& ex) {
		std::cout << "Hitting the catch block...\n";
		std::cout << "Exception is: " << typeid(ex).name() << '\n';
		std::cout << ex.what() << '\n';
	}
	if (removeVal.has_value())
		std::cout << "Carly's removed value is: " << removeVal.value() << '\n';
	else
		std::cout << "Error: no value returned from remove of Carly ...\n";

	std::cout << "\nCurrent contents of this IPQ:\n\n";
	q1.printArrays();
	print_separator();

	/******************************************************************************/

	// George
	std::cout << "\n\nIPQ contains George (key 6): " << q1.contains(6) << '\n';
	std::cout << "q1 is empty:        " << q1.isEmpty() << '\n';
	std::cout << "q1 size:            " << q1.size() << '\n';
	std::cout << "q1 is a min heap:   " << q1.isMinHeap() << '\n';
	std::cout << "peek min key index: " << q1.peekMinKeyIndex() << '\n';

	try {
		removeVal = q1.removeKey(6);		// Remove George from IPQ	
	}
	catch (std::exception& ex) {
		std::cout << "Hitting the catch block...\n";
		std::cout << "Exception is: " << typeid(ex).name() << '\n';
		std::cout << ex.what() << '\n';
	}
	if (removeVal.has_value())
		std::cout << "George's removed value is: " << removeVal.value() << '\n';
	else
		std::cout << "Error: no value returned from remove of George ...\n";

	std::cout << "\nCurrent contents of this IPQ:\n\n";
	q1.printArrays();
	print_separator();

	/******************************************************************************/

	// Isaac
	std::cout << "\n\nIPQ contains Isaac (key 8): " << q1.contains(8) << '\n';

	try {
		removeVal = q1.removeKey(8);		// Remove Isaac from IPQ	
	}
	catch (std::exception& ex) {
		std::cout << "Hitting the catch block...\n";
		std::cout << "Exception is: " << typeid(ex).name() << '\n';
		std::cout << ex.what() << '\n';
	}
	if (removeVal.has_value())
		std::cout << "Isaac's removed value is: " << removeVal.value() << '\n';
	else
		std::cout << "Error: no value returned from remove of Isaac...\n";

	std::cout << "\nCurrent contents of this IPQ:\n\n";
	q1.printArrays();
	print_separator();

	/******************************************************************************/

	// Laura
	std::cout << "\n\nIPQ contains Laura (key 11): " << q1.contains(11) << '\n';

	try {
		removeVal = q1.removeKey(11);	// Remove Laura from IPQ	
	}
	catch (std::exception& ex) {
		std::cout << "Hitting the catch block...\n";
		std::cout << "Exception is: " << typeid(ex).name() << '\n';
		std::cout << ex.what() << '\n';
	}
	if (removeVal.has_value())
		std::cout << "Laura's removed value is: " << removeVal.value() << '\n';
	else
		std::cout << "Error: no value returned from remove of Laura ...\n";

	std::cout << "\nCurrent contents of this IPQ:\n\n";
	q1.printArrays();
	print_separator();

	/******************************************************************************/

	// Henry
	std::cout << "\n\nIPQ contains Henry (key 7): " << q1.contains(7) << '\n';

	try {
		removeVal = q1.removeKey(7);		// Remove Henry from IPQ	
	}
	catch (std::exception& ex) {
		std::cout << "Hitting the catch block...\n";
		std::cout << "Exception is: " << typeid(ex).name() << '\n';
		std::cout << ex.what() << '\n';
	}
	if (removeVal.has_value())
		std::cout << "Henry's removed value is: " << removeVal.value() << '\n';
	else
		std::cout << "Error: no value returned from remove of Henry ...\n";

	std::cout << "\nCurrent contents of this IPQ:\n\n";
	q1.printArrays();
	print_separator();

	/******************************************************************************/

	// Barney
	std::cout << "\n\nIPQ contains Barney (key 12): " << q1.contains(12) << '\n';
	try {
		removeVal = q1.removeKey(12);	// Remove Barney from IPQ	
	}
	catch (std::exception& ex) {
		std::cout << "Hitting the catch block...\n";
		std::cout << "Exception is: " << typeid(ex).name() << '\n';
		std::cout << ex.what() << '\n';
	}
	if (removeVal.has_value())
		std::cout << "Barney's removed value is: " << removeVal.value() << '\n';
	else
		std::cout << "Error: no value returned from remove of Barney ...\n";

	std::cout << "\nCurrent contents of this IPQ:\n\n";
	q1.printArrays();
	print_separator();

	/******************************************************************************/

	// Finally, James
	std::cout << "\n\nIPQ contains James (key 9): " << q1.contains(9) << '\n';

	try {
		removeVal = q1.removeKey(9);		// Remove James from IPQ	
	}
	catch (std::exception& ex) {
		std::cout << "Hitting the catch block...\n";
		std::cout << "Exception is: " << typeid(ex).name() << '\n';
		std::cout << ex.what() << '\n';
	}
	if (removeVal.has_value())
		std::cout << "James's removed value is: " << removeVal.value() << '\n';
	else
		std::cout << "Error: no value returned from remove of James ...\n";

	std::cout << "\nCurrent contents of this IPQ:\n\n";
	q1.printArrays();
	print_separator();

	std::cout << "q1 is empty:        " << q1.isEmpty() << '\n';
	std::cout << "q1 size:            " << q1.size() << '\n';
	std::cout << "q1 is a min heap:   " << q1.isMinHeap() << '\n';

	try {
		std::cout << "peek min key index: " << q1.peekMinKeyIndex() << '\n';
	}
	catch (QueueEmptyException& qe) {
		std::cout << qe.what() << '\n';
	}

	std::cout << "\nWho's left in the queue now?\n\n";
	for (int i = 0; i < 13; i++)
		std::cout << "q1 contains " << names[i] << " - key " << i << ": "
		<< q1.contains(i) << '\n';
	print_separator();

	/********************************************************************************/

	std::cout << "\nTry to remove Dylan... again (will fail as he's already been removed)\n";
	removeVal.reset();

	try {
		removeVal = q1.removeKey(3);		// Remove Dylan from IPQ	
	}
	catch (std::exception& ex) {
		std::cout << "Hitting the catch block...\n";
		std::cout << "Exception is: " << typeid(ex).name() << '\n';
		std::cout << ex.what() << '\n';
	}
	if (removeVal.has_value())
		std::cout << "ERROR: removal of Dylan's has returned: " << removeVal.value()
		<< " - this shouldn't happen as Dylan has already been removed "
		<< "so fresh removal should fail!!\n";
	else
		std::cout << "Success: no value returned from remove of Dylan since he cannot be removed after being removed previously...\n";

	printLogEnd(__FUNCTION__);
}


void testContainsAndRemoveIPQ() {
	printLogStart(__FUNCTION__);

	IndexedPriorityQueue<int> q1(0, 0);
	std::cout << std::boolalpha;

	int values[25] = { 3, 15, 11, 17, 7, 9, 2, 1, 6, 5, 16, 4, 2 };
	std::vector<std::string> names(25);
	std::fill(names.begin(), names.end(), "None");

	// Array initialised - overwrite with meaningful names
	names[0] = "Anna";
	names[1] = "Bella";
	names[2] = "Carly";
	names[3] = "Dylan";
	names[4] = "Emily";
	names[5] = "Fred";
	names[6] = "George";
	names[7] = "Henry";
	names[8] = "Isaac";
	names[9] = "James";
	names[10] = "Kelly";
	names[11] = "Laura";
	names[12] = "Barney";

	// Setup keys to names mapping
	std::map<int, std::string> keysToNames;
	for (int i = 0; i < 25; i++)
		keysToNames[i] = names[i];

	for (int i = 0; i < std::size(values); i++)
		q1.insert(i, values[i]);

	std::cout << "q1 is empty:        " << q1.isEmpty() << '\n';
	std::cout << "q1 size:            " << q1.size() << '\n';
	std::cout << "q1 is a min heap:   " << q1.isMinHeap() << '\n';
	std::cout << "peek min key index: " << q1.peekMinKeyIndex() << '\n';

	std::cout << "\nCurrent contents of this IPQ:\n\n";

	q1.printNames(keysToNames);
	q1.printArrays();

	std::cout << "\n\n";
	for (int i = 0; i < std::size(values); i++)
		std::cout << "IPQ contains key " << i << ":\t" << q1.contains(i) << '\n';
	print_separator();

	/*******************************************************************************/

	// Removing from the IPQ
	std::cout << "\nNow testing removing items from within the IPQ (not polling):\n\n";
	std::optional<int> removeVal;

	// Emily
	std::cout << "\nRemove Emily...\n";

	try {
		removeVal = q1.removeKey(4);		// Remove Emily from IPQ
	}
	catch (std::exception& ex) {
		std::cout << "Hitting the catch block...\n";
		std::cout << "Exception is: " << typeid(ex).name() << '\n';
		std::cout << ex.what() << '\n';
	}

	if (removeVal.has_value())
		std::cout << "Emily's removed value is: " << removeVal.value() << '\n';
	else
		std::cout << "Error: no value returned from remove of Emily...\n";

	std::cout << "\nCurrent contents of this IPQ:\n\n";
	q1.printArrays();
	print_separator();

	/*******************************************************************************/

	// Kelly
	std::cout << "\nRemove Kelly...\n";

	try {
		removeVal = q1.removeKey(10);		// Remove Kelly from IPQ
	}
	catch (std::exception& ex) {
		std::cout << "Hitting the catch block...\n";
		std::cout << "Exception is: " << typeid(ex).name() << '\n';
		std::cout << ex.what() << '\n';
	}

	if (removeVal.has_value())
		std::cout << "Kelly's removed value is: " << removeVal.value() << '\n';
	else
		std::cout << "Error: no value returned from remove of Kelly...\n";

	std::cout << "\nCurrent contents of this IPQ:\n\n";
	q1.printArrays();
	print_separator();

	/*******************************************************************************/

	// Fred
	std::cout << "\nRemove Fred...\n";

	try {
		removeVal = q1.removeKey(5);		// Remove Fred from IPQ
	}
	catch (std::exception& ex) {
		std::cout << "Hitting the catch block...\n";
		std::cout << "Exception is: " << typeid(ex).name() << '\n';
		std::cout << ex.what() << '\n';
	}

	if (removeVal.has_value())
		std::cout << "Fred's removed value is: " << removeVal.value() << '\n';
	else
		std::cout << "Error: no value returned from remove of Fred...\n";

	std::cout << "\nCurrent contents of this IPQ:\n\n";
	q1.printArrays();
	print_separator();

	/*******************************************************************************/

	// Anna
	std::cout << "\nRemove Anna...\n";

	try {
		removeVal = q1.removeKey(0);		// Remove Anna from IPQ
	}
	catch (std::exception& ex) {
		std::cout << "Hitting the catch block...\n";
		std::cout << "Exception is: " << typeid(ex).name() << '\n';
		std::cout << ex.what() << '\n';
	}

	if (removeVal.has_value())
		std::cout << "Anna's removed value is: " << removeVal.value() << '\n';
	else
		std::cout << "Error: no value returned from remove of Anna...\n";

	std::cout << "\nCurrent contents of this IPQ:\n\n";
	q1.printArrays();
	print_separator();

	/*******************************************************************************/

	// Key not present in IPQ
	std::cout << "\nRemove a non-existent key (23)...\n";
	removeVal.reset();

	try {
		removeVal = q1.removeKey(23);		// Remove 23 from IPQ	
	}
	catch (std::exception& ex) {
		std::cout << "Hitting the catch block...\n";
		std::cout << "Exception is: " << typeid(ex).name() << '\n';
		std::cout << ex.what() << '\n';
	}

	if (removeVal.has_value())
		std::cout << "ERROR - remove key 23 returned: " << removeVal.value() << '\n';
	else
		std::cout << "Cannot remove key 23 as it is not in the IPQ...\n";

	std::cout << "\nCurrent contents of this IPQ:\n\n";
	q1.printArrays();
	print_separator();

	/*******************************************************************************/

	// Dylan
	std::cout << "\nRemove Dylan...\n";
	try {
		removeVal = q1.removeKey(3);		// Remove Dylan from IPQ	
	}
	catch (std::exception& ex) {
		std::cout << "Hitting the catch block...\n";
		std::cout << "Exception is: " << typeid(ex).name() << '\n';
		std::cout << ex.what() << '\n';
	}
	if (removeVal.has_value())
		std::cout << "Dylan's removed value is: " << removeVal.value() << '\n';
	else
		std::cout << "Error: no value returned from remove of Dylan...\n";

	std::cout << "\nCurrent contents of this IPQ:\n\n";
	q1.printArrays();
	print_separator();

	/*******************************************************************************/

	// Bella
	std::cout << "\nRemove Bella...\n";
	try {
		removeVal = q1.removeKey(1);		// Remove Bella from IPQ	
	}
	catch (std::exception& ex) {
		std::cout << "Hitting the catch block...\n";
		std::cout << "Exception is: " << typeid(ex).name() << '\n';
		std::cout << ex.what() << '\n';
	}
	if (removeVal.has_value())
		std::cout << "Bella's removed value is: " << removeVal.value() << '\n';
	else
		std::cout << "Error: no value returned from remove of Bella ...\n";

	std::cout << "\nCurrent contents of this IPQ:\n\n";
	q1.printArrays();
	print_separator();

	/*******************************************************************************/

	// Carly
	std::cout << "\nRemove Carly...\n";

	try {
		removeVal = q1.removeKey(2);		// Remove Carly from IPQ	
	}
	catch (std::exception& ex) {
		std::cout << "Hitting the catch block...\n";
		std::cout << "Exception is: " << typeid(ex).name() << '\n';
		std::cout << ex.what() << '\n';
	}
	if (removeVal.has_value())
		std::cout << "Carly's removed value is: " << removeVal.value() << '\n';
	else
		std::cout << "Error: no value returned from remove of Carly ...\n";

	std::cout << "\nCurrent contents of this IPQ:\n\n";
	q1.printArrays();
	print_separator();

	/******************************************************************************/

	// George
	std::cout << "\n\nIPQ contains George (key 6): " << q1.contains(6) << '\n';
	std::cout << "q1 is empty:        " << q1.isEmpty() << '\n';
	std::cout << "q1 size:            " << q1.size() << '\n';
	std::cout << "q1 is a min heap:   " << q1.isMinHeap() << '\n';
	std::cout << "peek min key index: " << q1.peekMinKeyIndex() << '\n';

	try {
		removeVal = q1.removeKey(6);		// Remove George from IPQ	
	}
	catch (std::exception& ex) {
		std::cout << "Hitting the catch block...\n";
		std::cout << "Exception is: " << typeid(ex).name() << '\n';
		std::cout << ex.what() << '\n';
	}
	if (removeVal.has_value())
		std::cout << "George's removed value is: " << removeVal.value() << '\n';
	else
		std::cout << "Error: no value returned from remove of George ...\n";

	std::cout << "\nCurrent contents of this IPQ:\n\n";
	q1.printArrays();
	print_separator();

	/******************************************************************************/

	// Isaac
	std::cout << "\n\nIPQ contains Isaac (key 8): " << q1.contains(8) << '\n';

	try {
		removeVal = q1.removeKey(8);		// Remove Isaac from IPQ	
	}
	catch (std::exception& ex) {
		std::cout << "Hitting the catch block...\n";
		std::cout << "Exception is: " << typeid(ex).name() << '\n';
		std::cout << ex.what() << '\n';
	}
	if (removeVal.has_value())
		std::cout << "Isaac's removed value is: " << removeVal.value() << '\n';
	else
		std::cout << "Error: no value returned from remove of Isaac...\n";

	std::cout << "\nCurrent contents of this IPQ:\n\n";
	q1.printArrays();
	print_separator();

	/******************************************************************************/

	// Laura
	std::cout << "\n\nIPQ contains Laura (key 11): " << q1.contains(11) << '\n';

	try {
		removeVal = q1.removeKey(11);	// Remove Laura from IPQ	
	}
	catch (std::exception& ex) {
		std::cout << "Hitting the catch block...\n";
		std::cout << "Exception is: " << typeid(ex).name() << '\n';
		std::cout << ex.what() << '\n';
	}
	if (removeVal.has_value())
		std::cout << "Laura's removed value is: " << removeVal.value() << '\n';
	else
		std::cout << "Error: no value returned from remove of Laura ...\n";

	std::cout << "\nCurrent contents of this IPQ:\n\n";
	q1.printArrays();
	print_separator();

	/******************************************************************************/

	// Henry
	std::cout << "\n\nIPQ contains Henry (key 7): " << q1.contains(7) << '\n';

	try {
		removeVal = q1.removeKey(7);		// Remove Henry from IPQ	
	}
	catch (std::exception& ex) {
		std::cout << "Hitting the catch block...\n";
		std::cout << "Exception is: " << typeid(ex).name() << '\n';
		std::cout << ex.what() << '\n';
	}
	if (removeVal.has_value())
		std::cout << "Henry's removed value is: " << removeVal.value() << '\n';
	else
		std::cout << "Error: no value returned from remove of Henry ...\n";

	std::cout << "\nCurrent contents of this IPQ:\n\n";
	q1.printArrays();
	print_separator();

	/******************************************************************************/

	// Barney
	std::cout << "\n\nIPQ contains Barney (key 12): " << q1.contains(12) << '\n';
	try {
		removeVal = q1.removeKey(12);	// Remove Barney from IPQ	
	}
	catch (std::exception& ex) {
		std::cout << "Hitting the catch block...\n";
		std::cout << "Exception is: " << typeid(ex).name() << '\n';
		std::cout << ex.what() << '\n';
	}
	if (removeVal.has_value())
		std::cout << "Barney's removed value is: " << removeVal.value() << '\n';
	else
		std::cout << "Error: no value returned from remove of Barney ...\n";

	std::cout << "\nCurrent contents of this IPQ:\n\n";
	q1.printArrays();
	print_separator();

	/******************************************************************************/

	// Finally, James
	std::cout << "\n\nIPQ contains James (key 9): " << q1.contains(9) << '\n';

	try {
		removeVal = q1.removeKey(9);		// Remove James from IPQ	
	}
	catch (std::exception& ex) {
		std::cout << "Hitting the catch block...\n";
		std::cout << "Exception is: " << typeid(ex).name() << '\n';
		std::cout << ex.what() << '\n';
	}
	if (removeVal.has_value())
		std::cout << "James's removed value is: " << removeVal.value() << '\n';
	else
		std::cout << "Error: no value returned from remove of James ...\n";

	std::cout << "\nCurrent contents of this IPQ:\n\n";
	q1.printArrays();
	print_separator();

	std::cout << "q1 is empty:        " << q1.isEmpty() << '\n';
	std::cout << "q1 size:            " << q1.size() << '\n';
	std::cout << "q1 is a min heap:   " << q1.isMinHeap() << '\n';

	try {
		std::cout << "peek min key index: " << q1.peekMinKeyIndex() << '\n';
	}
	catch (QueueEmptyException& qe) {
		std::cout << qe.what() << '\n';
	}

	std::cout << "\nWho's left in the queue now?\n\n";
	for (int i = 0; i < 13; i++)
		std::cout << "q1 contains " << names[i] << " - key " << i << ": "
		<< q1.contains(i) << '\n';
	print_separator();

	/********************************************************************************/

	std::cout << "\nTry to remove Dylan... again (will fail as he's already been removed)\n";
	removeVal.reset();

	try {
		removeVal = q1.removeKey(3);		// Remove Dylan from IPQ	
	}
	catch (std::exception& ex) {
		std::cout << "Hitting the catch block...\n";
		std::cout << "Exception is: " << typeid(ex).name() << '\n';
		std::cout << ex.what() << '\n';
	}
	if (removeVal.has_value())
		std::cout << "ERROR: removal of Dylan's has returned: " << removeVal.value()
		<< " - this shouldn't happen as Dylan has already been removed "
		<< "so fresh removal should fail!!\n";
	else
		std::cout << "Success: no value returned from remove of Dylan since he cannot be removed after being removed previously...\n";

	printLogEnd(__FUNCTION__);
}


void testDecreaseValue() {
	printLogStart(__FUNCTION__);

	// Basic setup for a testable queue
	IndexedPriorityQueue<int> q1(0, 0);
	std::cout << std::boolalpha;

	int values[25] = { 3, 15, 11, 17, 7, 9, 2, 1, 6, 5, 16, 4, 2 };
	std::vector<std::string> names(25);
	std::fill(names.begin(), names.end(), "None");

	// Array initialised - overwrite with meaningful names
	names[0] = "Anna";
	names[1] = "Bella";
	names[2] = "Carly";
	names[3] = "Dylan";
	names[4] = "Emily";
	names[5] = "Fred";
	names[6] = "George";
	names[7] = "Henry";
	names[8] = "Isaac";
	names[9] = "James";
	names[10] = "Kelly";
	names[11] = "Laura";
	names[12] = "Barney";

	// Setup keys to names mapping
	std::map<int, std::string> keysToNames;
	for (int i = 0; i < 25; i++)
		keysToNames[i] = names[i];

	for (int i = 0; i < 13; i++)
		q1.insert(i, values[i]);

	std::cout << "q1 is empty:        " << q1.isEmpty() << '\n';
	std::cout << "q1 size:            " << q1.size() << '\n';
	std::cout << "q1 is a min heap:   " << q1.isMinHeap() << '\n';
	std::cout << "peek min key index: " << q1.peekMinKeyIndex() << '\n';

	std::cout << "\nCurrent contents of this IPQ:\n\n";

	q1.printNames(keysToNames);
	q1.printArrays();
	print_separator();

	/*******************************************************************************/

	// Change some values
	std::cout << "\n\nNow testing decreasing values for keys...\n";

	// 1. Key out of bounds
	q1.decrease(30, 0); // Key 30 not in IPQ
	std::cout << "Decrease of key 30 (out of bounds) has failed silently -- as expected...\n";

	// 2. Key not found
	std::cout << "\n\n";
	try {
		q1.decrease(20, 0);
	}
	catch (std::exception& ex) {
		std::cout << "Hitting the catch block...\n";
		std::cout << "Exception is: " << typeid(ex).name() << '\n';
		std::cout << ex.what() << '\n';
	}

	// 3. Try to increase Henry's value with decrease function (fail)
	std::cout << "\nIncrease Henry (key=7) from 1 to 8 (should fail):\n\n";
	q1.decrease(7, 8);
	q1.printNames(keysToNames);
	q1.printArrays();
	print_separator();

	/****************************************************************************/

	// 4. Decrease Dylan
	std::cout << "\nDecrease Dylan (key=3) from 17 to 14:\n\n";
	q1.decrease(3, 14);
	q1.printNames(keysToNames);
	q1.printArrays();
	print_separator();

	/****************************************************************************/

	// 5. Decrease Bella
	std::cout << "\nDecrease Bella (key=1) from 15 to 4:\n\n";
	q1.decrease(1, 4);
	q1.printNames(keysToNames);
	q1.printArrays();
	print_separator();

	/****************************************************************************/

	// 6. Decrease Kelly
	std::cout << "\nDecrease Kelly (key=10) from 16 to 1:\n\n";
	q1.decrease(10, 1);
	q1.printNames(keysToNames);
	q1.printArrays();
	print_separator();

	printLogEnd(__FUNCTION__);
}



void testIncreaseValue() {
	printLogStart(__FUNCTION__);

	// Basic setup for a testable queue
	IndexedPriorityQueue<int> q1(0, 0);
	std::cout << std::boolalpha;

	int values[25] = { 3, 15, 11, 17, 7, 9, 2, 1, 6, 5, 16, 4, 2 };
	std::vector<std::string> names(25);
	std::fill(names.begin(), names.end(), "None");

	// Array initialised - overwrite with meaningful names
	names[0] = "Anna";
	names[1] = "Bella";
	names[2] = "Carly";
	names[3] = "Dylan";
	names[4] = "Emily";
	names[5] = "Fred";
	names[6] = "George";
	names[7] = "Henry";
	names[8] = "Isaac";
	names[9] = "James";
	names[10] = "Kelly";
	names[11] = "Laura";
	names[12] = "Barney";

	// Setup keys to names mapping
	std::map<int, std::string> keysToNames;
	for (int i = 0; i < 25; i++)
		keysToNames[i] = names[i];

	for (int i = 0; i < 13; i++)
		q1.insert(i, values[i]);

	std::cout << "q1 is empty:        " << q1.isEmpty() << '\n';
	std::cout << "q1 size:            " << q1.size() << '\n';
	std::cout << "q1 is a min heap:   " << q1.isMinHeap() << '\n';
	std::cout << "peek min key index: " << q1.peekMinKeyIndex() << '\n';

	std::cout << "\nCurrent contents of this IPQ:\n\n";

	q1.printNames(keysToNames);
	q1.printArrays();
	print_separator();

	/*******************************************************************************/

	// Change some values
	std::cout << "\n\nNow testing increasing values for keys...\n";

	// 1. Key out of bounds
	q1.increase(30, 0); // Key 30 not in IPQ
	std::cout << "Increase of key 30 (out of bounds) has failed silently -- as expected...\n";

	// 2. Key not found
	std::cout << "\n\n";
	try {
		q1.increase(20, 0);	// Key 20 within bounds but not in queue
	}
	catch (std::exception& ex) {
		std::cout << "Hitting the catch block...\n";
		std::cout << "Exception is: " << typeid(ex).name() << '\n';
		std::cout << ex.what() << '\n';
	}

	// 3. Try to decrease Fred's value with increase function (fail)
	std::cout << "\nDecrease Fred (key=5) from 9 to 3 (should fail):\n\n";
	q1.increase(5, 3);
	q1.printNames(keysToNames);
	q1.printArrays();
	print_separator();

	/****************************************************************************/

	// 4. Increase Anna
	std::cout << "\nIncrease Anna (key=0) from 3 to 10:\n\n";
	q1.increase(0, 10);
	q1.printNames(keysToNames);
	q1.printArrays();
	print_separator();

	/****************************************************************************/

	// 5. Increase Emily
	std::cout << "\nIncrease Emily (key=4) from 7 to 19:\n\n";
	q1.increase(4, 19);
	q1.printNames(keysToNames);
	q1.printArrays();
	print_separator();

	/****************************************************************************/

	// 6. Increase Barney
	std::cout << "\nIncrease Barney (key=12) from 2 to 20:\n\n";
	q1.increase(12, 20);
	q1.printNames(keysToNames);
	q1.printArrays();
	print_separator();

	printLogEnd(__FUNCTION__);
}


void testUpdateValue() {
	printLogStart(__FUNCTION__);

	// Basic setup for a testable queue
	IndexedPriorityQueue<int> q1(0, 0);
	std::cout << std::boolalpha;

	int values[25] = { 3, 15, 11, 17, 7, 9, 2, 1, 6, 5, 16, 4, 2 };
	std::vector<std::string> names(25);
	std::fill(names.begin(), names.end(), "None");

	// Array initialised - overwrite with meaningful names
	names[0] = "Anna";
	names[1] = "Bella";
	names[2] = "Carly";
	names[3] = "Dylan";
	names[4] = "Emily";
	names[5] = "Fred";
	names[6] = "George";
	names[7] = "Henry";
	names[8] = "Isaac";
	names[9] = "James";
	names[10] = "Kelly";
	names[11] = "Laura";
	names[12] = "Barney";

	// Setup keys to names mapping
	std::map<int, std::string> keysToNames;
	for (int i = 0; i < 25; i++)
		keysToNames[i] = names[i];

	for (int i = 0; i < 13; i++)
		q1.insert(i, values[i]);

	std::cout << "q1 is empty:        " << q1.isEmpty() << '\n';
	std::cout << "q1 size:            " << q1.size() << '\n';
	std::cout << "q1 is a min heap:   " << q1.isMinHeap() << '\n';
	std::cout << "peek min key index: " << q1.peekMinKeyIndex() << '\n';

	std::cout << "\nCurrent contents of this IPQ:\n\n";

	q1.printNames(keysToNames);
	q1.printArrays();
	print_separator();

	/*******************************************************************************/

	// Update some values
	std::cout << "\nUpdate some of the values now...\n";
	std::optional<int> oldValue;

	// 1. Key out of bounds
	oldValue = q1.update(30, 0);	// Key 30 beyond bounds
	if (oldValue.has_value())
		std::cout << "Error: " << oldValue.value() << " returned from update key 30"
		<< " (out of bounds) - value should be 0";
	else
		std::cout << "Success: no value returned from update key 30 (out of bounds)\n";

	// 2. Key not found
	std::cout << "\n\n";
	try {
		oldValue = q1.update(20, 0);	// Key 20 within bounds but not in queue
	}
	catch (std::exception& ex) {
		std::cout << "Hitting the catch block...\n";
		std::cout << "Exception is: " << typeid(ex).name() << '\n';
		std::cout << ex.what() << '\n';
	}


	// 3. Decrease Fred's value with update function
	std::cout << "\nDecrease Fred (key=5) from 9 to 3 using update:\n";
	oldValue = q1.update(5, 3);

	if (oldValue.has_value())
		std::cout << "Fred's old value is: " << oldValue.value() << "\n\n";
	else
		std::cout << "Error: problem with update to Fred as no value returned...\n";
	q1.printNames(keysToNames);
	q1.printArrays();
	print_separator();

	/****************************************************************************/

	// 4. Change Bella, but make it same value so no real update
	std::cout << "\nUpdate Bella (key=1) from 15 to 15 (no change):\n";
	oldValue = q1.update(1, 15);
	if (oldValue.has_value())
		std::cout << "Bella's old value is: " << oldValue.value() << "\n\n";
	else
		std::cout << "Error: problem with update to Bella as no value returned...\n";
	q1.printNames(keysToNames);
	q1.printArrays();
	print_separator();

	/****************************************************************************/

	// 5. Update George - increase
	std::cout << "\nUpdate George (key=6) from 2 to 13:\n";
	oldValue = q1.update(6, 13);
	if (oldValue.has_value())
		std::cout << "George's old value is: " << oldValue.value() << "\n\n";
	else
		std::cout << "Error: problem with update as no value returned...\n";
	q1.printNames(keysToNames);
	q1.printArrays();
	print_separator();

	/****************************************************************************/

	// 6. Update Henry - decrease (should fail as negative number - disallowed)
	std::cout << "\nUpdate Henry (key=7) from 1 to -12 (should fail as negative numbers not allowed):\n";
	oldValue = q1.update(7, -12);
	if (oldValue.has_value())
		std::cout << "Henry's old value is: " << oldValue.value() << "\n\n";
	else
		std::cout << "Error: problem with update to Henry as no value returned...\n";
	q1.printNames(keysToNames);
	q1.printArrays();
	print_separator();

	/****************************************************************************/

	// 7. Update Dylan - decrease
	std::cout << "\nUpdate Dylan (key=3) from 17 to 1:\n";
	oldValue = q1.update(3, 1);
	if (oldValue.has_value())
		std::cout << "Dylan's old value is: " << oldValue.value() << "\n\n";
	else
		std::cout << "Error: problem with update to Dylan as no value returned...\n";
	q1.printNames(keysToNames);
	q1.printArrays();

	printLogEnd(__FUNCTION__);
}
// Priority Queue
// --------------
// 
// See YouTube video "Data Structures Easy to Advanced Course - Full Tutorial from a Google Engineer"
// for an illustrated discussion: https://youtu.be/RBSGKlAvoiM
// The notes below are taken from the video.
// 
// Notes on Priority Queues
// ------------------------
// 
// A Priority Queue (PQ) is an Abstract Data Type (ADT).
// It operates in a similar way to a normal queue, except that each element 
// has a certain priority. The priority of the elements in the PQ determines
// the order in which they are removed from it.
// 
// Note: A PQ supports only comparable data, meaning that the data inserted
// into it must be orderable in some way, either from least to 
// greatest, or from greatest to least. This is to enable the relative
// priorities to be determined.
//
// PQs can be implemented with various Data Structures (DSs), but a heap is
// the canonical underlying DS of a PQ.
// 
// A heap is a tree-based DS that satisfies the following
// heap invariant (also called a heap property):
// If A is a parent node of B, then A is ordered with respect to B for 
// all nodes A, B in the heap.
// 
// PQs are used:
// 1) In some implementations of Dijkstra's Shortest Path algorithm.
// 2) To dynamically fetch the 'next best' or 'next worst' element.
// 3) In Huffman coding (which is often used for lossless data compression).
// 4) Best First Search (BFS) algorithms, such as A*, use PQs to 
//    continuously grab the next most promising node.
// 5) By Minimum Spanning Tree (MST) algorithms.
// 
// 
// Time Complexity of Operations
// -----------------------------
// 
// Binary Heap Construction					O(n)
// Polling									O(log(n))
// Peeking									O(1)
// Adding									O(log(n))
// 
// Naïve Removing							O(n)
// Advanced Removing (Using Hash Table)		O(log(n)
// Naïve Contains							O(n)
// Advanced Contains (Using Hash Table)		O(1)
//
// N.B.
// 1) There is an algorithm that constructs a Binary Heap from an array in O(n) time, 
//    but is not covered in this series 
//    (this algorithm also forms the basis of the heap sort algorithm)
// 2) Using a hash table to help optimise these operations incurs a linear
//    space cost and also adds some overhead to the binary heap implementation
//    (accessing table during swaps).
// 
// 
// Removing Elements 
// -----------------
//
// The inefficiency of the removal algorithm in a heap is largely due to
// the necessity of performing a linear search to find out the element's index.
// If a lookup table (using a hash table) is used to find nodes instead,
// the lookup time becomes constant, by mapping a key (the node value) to 
// another value (the index).
//
//
// Implementing a Priority Queue
// -----------------------------
// 
// Priority queues are usually implemented with heaps since this give them the
// best possible time complexity.
// 
// The Priority Queue (PQ) is an Abstract Data Type (ADT), hence heaps are not
// the only way to implement PQs. As an example, we could use an unsorted list,
// but this would not give us the best possible time complexity.
// 
// 
// Priority Queue with Binary Heap
// -------------------------------
// 
// There are many types of heaps we could use to implement a priority queue, 
// including:
// 
// - Binary Heap
// - Fibonacci Heap
// - Binomial Heap
// - Pairing Heap
// 
// A binary heap is a binary tree that supports the heap invariant:
// *In a binary tree every node has exactly two children.*
// 
// A complete binary tree is a tree in which every level, except possibly the
// last, is completely filled and all the nodes are as far left as possible.
// 
// 
// Binary Heap Representation
// --------------------------
// 
// A binary heap is canonically, elegantly, and efficiently represented by an array.
// Array representation also allows convenient access to parents and children:
// 
// If i is the parent node index (in a zero-based index):
// Left child index:  2i + 1
// Right child index: 2i + 2

#include <algorithm>
#include <functional>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <vector>

#include "Priority_Queue.h"

// Main test functions
void testNegation();
void testConcept();
void testEmptyPriorityQueue();
void testPriorityQueue();

int main() {
	// Call test functions
	testNegation();
	testConcept();
	testEmptyPriorityQueue();
	testPriorityQueue();
}

/***************************************************************************************************************************************/
/********************************** Test Functions *************************************************************************************/

// Negation
// --------
// 
// Negation can be a useful trick for inverting the priority order in a heap.
// 
// For example, if we have a min heap, it might be something like this:
// 2, 3, 5, 7, 11, 13
// 
// But if we negate the numbers before adding them to the heap, it can be a quick way
// to turn it into a min heap, e.g. add -13, -11 etc. We can then negate them again on the way
// out:
// -13, -11, -7, -5, -3, -2
// 
// Polling the highest priority item gives us -13, which negated is 13
// and so on with -11/11 etc.
void testNegation() {
	// 1. Test ints
	std::cout << "(1) Test negation on ints...\n";
	std::negate<int> intNegator{};

	int nums[] = { 2, 3, 5, 7, 11, 13 };
	std::vector<int> negatedNums(6);

	std::cout << "capacity of negatedNums: " << negatedNums.capacity() << '\n';
	std::cout << "size of negatedNums:     " << negatedNums.size() << '\n';

	std::cout << "\nNumbers in order min-to-max:\n";
	for (int i = 0; i < std::size(nums); i++)
		std::cout << nums[i] << "  ";

	// Negate numbers
	for (int i = 0; i < std::size(nums); i++)
		negatedNums[i] = intNegator(nums[i]);

	std::cout << "\n\nNumbers in order max-to-min:\n";
	for (int i = std::size(negatedNums) - 1; i >= 0; i--)
		std::cout << std::abs(negatedNums[i]) << "  ";

	std::cout << "\n\nFor validation purposes, the numbers in negatedNums array unmodified:\n";
	for (int i = 0; i < std::size(negatedNums); i++)
		std::cout << negatedNums[i] << "  ";
	
	/*************************************************************************************/

	// 2. Test strings
	std::cout << "\n\n(2) Test negation on strings...\n";

	// Doesn't work: no - operator on std::string
	//std::negate<std::string> stringNegator{};

	std::string names[] = { "Arthur", "Bill", "Fred", "Don", "Mark", "Ted", "Gary" };

	std::vector<std::string> namesAsc;	// Sorted ascending array
	std::vector<std::string> namesDesc;	// Sorted descending array

	// Create a vec of names and sort ascending
	for (int i = 0; i < std::size(names); i++)
		namesAsc.push_back(names[i]);
	std::sort(namesAsc.begin(), namesAsc.end());

	// Create a vec of names and sort descending
	for (int i = 0; i < std::size(names); i++)
		namesDesc.push_back(names[i]);
	std::sort(namesDesc.begin(), namesDesc.end(), std::greater{});

	std::cout << "\n\nContents of namesAsc:\n";
	for (int i = 0; i < std::size(namesAsc); i++)
		std::cout << namesAsc[i] << "  ";

	std::cout << "\n\nContents of namesDesc:\n";
	for (int i = 0; i < std::size(namesDesc); i++)
		std::cout << namesDesc[i] << "  ";	
}


// Class without comparison operators to test PQ concept.
class Person {
public:
	Person(int a) : Person(a, "Barry White") {}	
	Person(const char* n) : Person(51, n) {}
	Person(int a, const char* n) : age{ a }, name{ n } {
		std::cout << name << " created...\n";
	}

	int getAge() { return age; }
	std::string& getName() { return name; }

	friend std::ostream& operator<<(std::ostream& out, const Person& person);
private:
	int age{};
	std::string name{};	
};

std::ostream& operator<<(std::ostream& out, const Person& person) {
	out << "Name: " << person.name << "\tAge: " << person.age << '\n';
	return out;
}

// Test the comparable concept on the class.
void testConcept() {
	// 1. Use a fundamental type that we know will work
	std::cout << "\n(1) Test a double pq (works)...\n";
	PQueue<double> pq1;
	std::cout << std::boolalpha;

	// Add some elements
	double values[] = { 3.45, 6.76, 2.34, 5.67, 7.89, 0.45, 5.67 };

	for (int i = 0; i < std::size(values); ++i)
		pq1.add(values[i]);

	std::cout << "\nTest basic functions...\n";
	std::cout << "Contents of pq1:\n";
	pq1.print();

	std::cout << "PQ is empty: " << pq1.isEmpty() << '\n';
	std::cout << "Size PQ:     " << pq1.size() << '\n';
	std::cout << "PQ is valid: " << pq1.isPQValid() << "\n\n";

	std::cout << "Now pop elements off the queue...\n";

	// top throws exception so catch here...
	while (true) {
		double element{};
		try {
			element = pq1.top();
			std::cout << "Size PQ:                       " << pq1.size() << '\n';
			std::cout << "Next element off the queue is: " << element << '\n';
			std::cout << "Pop the element off the queue...\n\n";
			pq1.pop();
		}
		catch (PriorityQueueEmptyException& pqe) {
			std::cout << "End of queue reached...\n";
			break;
		}
	}

	std::cout << "\nAfter popping...\n";
	std::cout << "PQ is empty:   " << pq1.isEmpty() << '\n';
	std::cout << "Size PQ:       " << pq1.size() << '\n';
	std::cout << "PQ is valid:   " << pq1.isPQValid() << "\n\n";

	/********************************************************************************/

	// 2. Use a UDT with no comparison operators defined
	std::cout << "\n(2) Test a Person pq (doesn't work)...\n";

	// Test all three constructor options
	Person p1(54);						// 1. Supply age only
	Person p2("Richard Kimble");		// 2. Supply name only
	Person p3(46, "Samuel Gerrard");	// 3. Supply age and name

	// Print the details
	std::cout << "\n\nThe details of the people:\n\n";
	std::cout << "Person 1 | " << p1 << '\n';
	std::cout << "Person 2 | " << p2 << '\n';
	std::cout << "Person 3 | " << p3 << '\n';

	// These statements won't compile as there are no such operators defined for Person
	//std::cout << "p1 < p2:  " << (p1 < p2) << '\n';
	//std::cout << "p1 > p2:  " << (p1 > p2) << '\n';
	//std::cout << "p1 == p2: " << (p1 == p2) << '\n';

	// Therefore, creating a queue to store Person objects won't compile
	// due to the defined constraints not being satisfied
	//PQueue<Person> personQueue(3);
}

void testEmptyPriorityQueue() {
	std::cout << "Test an empty priority queue...\n";
	PQueue<int> pq1;
	std::cout << std::boolalpha;

	// 1. Empty, size, valid.
	std::cout << "\n(1) Test basic functions...\n";
	std::cout << "PQ is empty: " << pq1.isEmpty() << '\n';
	std::cout << "Size PQ:     " << pq1.size() << '\n';
	std::cout << "PQ is valid: " << pq1.isPQValid() << '\n';


	// 2. Top
	std::cout << "\n(2) Test call to top()...\n";
	try {
		int val = pq1.top();
		std::cout << "val returned from top: " << val << '\n';
	}
	catch (PriorityQueueEmptyException& pqe) {
		std::cout << "Exception calling top(): " << pqe.getMessage() << "\n\n";
	}


	// 3. Pop
	std::cout << "\n(3) Test call to pop()...\n";
	pq1.pop();	// Does nothing in an empty queue (no exception)

	// 4. Contains
	std::cout << "\n\n(4) Test contains()...\n";
	for (int i = 1; i <= 5; i++)
		std::cout << "PQ contains " << i << ": " << pq1.contains(i) << '\n';

	// 5. Remove
	std::cout << "\n\n(5) Test remove items...\n";
	for (int i = 1; i <= 5; i++)
		std::cout << "PQ removed at index " << i << ": " << pq1.remove(i) << '\n';


	// 6. Remove at
	std::cout << "\n\n(6) Test removeAt()...\n";
	std::optional<int> removed;
	for (int i = 1; i <= 5; i++) {
		removed = pq1.removeAt(i);
		if (removed.has_value())
			std::cout << "ERROR! PQ removed " << i << ": " << pq1.remove(i)
			<< " when PQ is empty!!\n";
		else
			std::cout << "PQ removed " << i << ": " << removed.has_value() << '\n';
	}

	// 7. Clear (should have no effect)
	std::cout << "\n\n(7) Test clear()";
	pq1.clear();
	std::cout << "\n\nContents of PQ:\n";
	pq1.print();
	std::cout << "PQ is valid: " << pq1.isPQValid();	
}


void testPriorityQueue() {
	std::cout << "Test a populated priority queue...\n";

	PQueue<int> pq1;
	int nums[] = { 5, 6, 12, 8, 7, 14, 19, 13, 12, 11 };
	int numsSize = std::size(nums);

	// Setup PQ with data
	for (int i = 0; i < numsSize; i++) {
		std::cout << "Iteration " << i << ":\n";
		pq1.add(nums[i]);
		pq1.print();
	}

	// What is or isn't true about the PQ
	std::cout << std::boolalpha;
	std::cout << "PQ is empty:        " << pq1.isEmpty() << '\n';
	std::cout << "PQ is valid:        " << pq1.isPQValid() << '\n';
	std::cout << "Size of PQ:         " << pq1.size() << "\n\n";

	// Test contains
	for (int i = 0; i < numsSize; i++)
		std::cout << "PQ contains " << nums[i] << ":\t" << pq1.contains(nums[i]) << '\n';

	for (int i = 0; i < 5; i++)
		std::cout << "PQ contains " << i * 10 << ":\t" << pq1.contains(i * 10) << '\n';

	// Test clear
	std::cout << "\nClear elements from PQ...\n";
	pq1.clear();
	std::cout << "\nContents of PQ after clear:\n";
	pq1.print();
	std::cout << "PQ is empty:        " << pq1.isEmpty() << '\n';
	std::cout << "PQ is valid:        " << pq1.isPQValid() << '\n';
	std::cout << "Size of PQ:         " << pq1.size() << "\n\n";

	// Repopulate PQ
	// Setup PQ with data
	for (int i = 0; i < numsSize; i++)
		pq1.add(nums[i]);

	std::cout << "\nContents of PQ after repopulating it:\n";
	pq1.print();
	std::cout << "PQ is empty:        " << pq1.isEmpty() << '\n';
	std::cout << "PQ is valid:        " << pq1.isPQValid() << '\n';
	std::cout << "Size of PQ:         " << pq1.size() << "\n\n";

	// Test add of a lower number
	std::cout << "\nAdd 1 to PQ (lower than current root):\n";
	pq1.add(1);
	pq1.print();

	/*****************************************************************************/

	// Test remove of a number at the bottom of the tree
	std::cout << "\n(2) Remove 12 from PQ (one of the higher values)...\n";
	pq1.clear();
	std::cout << "\nContents of the tree before remove:\n";

	int nums2[] = { 1, 5, 2, 8, 6, 2, 2, 13, 12, 11, 7, 10, 15, 3 };

	for (int i = 0; i < std::size(nums2); i++)
		pq1.add(nums2[i]);

	pq1.print();

	std::cout << "\nContents of the tree after remove:\n";
	pq1.remove(12);
	pq1.print();

	// Call top() & pop()
	std::cout << "\n\nRemove some elements via pop():\n";
	for (int i = 0; i < 5; i++) {
		std::cout << "Top element: " << pq1.top() << '\n';
		pq1.pop();
	}

	std::cout << "\nContents of PQ after removals:\n";
	pq1.print();
	std::cout << "PQ is empty:        " << pq1.isEmpty() << '\n';
	std::cout << "PQ is valid:        " << pq1.isPQValid() << '\n';
	std::cout << "Size of PQ:         " << pq1.size() << "\n\n";
	
	/*****************************************************************************/

	// Reset the PQ to its original state
	std::cout << "\n(3) Rebuild the PQ...\n";
	pq1.clear();
	for (int i = 0; i < std::size(nums2); i++)
		pq1.add(nums2[i]);

	pq1.print();
	std::cout << "PQ is empty:        " << pq1.isEmpty() << '\n';
	std::cout << "PQ is valid:        " << pq1.isPQValid() << '\n';
	std::cout << "Size of PQ:         " << pq1.size() << "\n\n";

	for (int i = 0; i < 10; i++) {
		std::cout << "Remove the element at index 6...\n";
		pq1.removeAt(6);
		pq1.print();
		std::cout << "PQ is empty:        " << pq1.isEmpty() << '\n';
		std::cout << "PQ is valid:        " << pq1.isPQValid() << '\n';
		std::cout << "Size of PQ:         " << pq1.size() << "\n\n";
	}

	std::cout << "\nContinue popping until queue is empty...\n";
	while (!pq1.isEmpty()) {
		std::cout << "\n-----------------------------------------------\n";
		int popped = pq1.top();
		pq1.pop();
		std::cout << "Popped value is: " << popped << '\n';
		std::cout << "Contents of PQ:\n";
		pq1.print();
	}

	std::cout << "PQ is empty:        " << pq1.isEmpty() << '\n';
	std::cout << "PQ is valid:        " << pq1.isPQValid() << '\n';
	std::cout << "Size of PQ:         " << pq1.size() << "\n\n";	
}
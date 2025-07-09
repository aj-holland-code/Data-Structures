// Dynamic Array
// -------------
// 
// See YouTube video "Data Structures Easy to Advanced Course - Full Tutorial from a Google Engineer"
// for illustrated discussion.
// https://youtu.be/RBSGKlAvoiM
// 
// The Dynamic Array data structure example used in that video is coded in Java; 
// this is implemented in C++ so differs considerably in places.
// The notes below are taken from the video.
// 
// Notes on Static & Dynamic Arrays
// --------------------------------
// 
// A static array is a fixed length container containing N elements that are
// indexable from the range [0, N-1].
// Indexable means that each slot/index in the array can be referenced with 
// a number.
// 
// Static arrays are used for various purposes:
// 
// 1. Storing and accessing sequential data.
// 2. Temporarily storing objects.
// 3. As buffers for IO routines.
// 4. Lookup tables and inverse lookup tables.
// 5. Returning multiple values from a function.
// 6. Caching answers to subproblems in dynamic programming. 
//
// Dynamic arrays can grow and shrink in size. They are often implemented with
// a static array:
// 
// 1. Create a static array with an initial capacity.
// 2. Add elements to the underlying static array, keeping track of the number
//    of elements.
// 3. If adding another element will exceed the capacity, create a new static array
//    with twice the capacity and copy the original elements into it.
// 
// 
// Time Complexity
// ---------------
// 
// Access for static arrays and dynamic arrays				O(1)
// Searching for static arrays and dynamic arrays			O(n)
// Appending for dynamic arrays								O(1)
// Insertion and deletion for dynamic arrays				O(n)

#include <algorithm>
#include <iomanip>
#include <iostream>

// User-defined header files
#include "Dynamic_Array.h"

// Main test functions
void testDefaultDynamicArray();
void testOneElementArray();
void testMultiElementArray();
void testElementsContents();
void testCopyConstructor();
void testCopyAssignmentOperator();
void testMoveConstructor();
void testMoveAssignmentOperator();

int main() {
	// Call test functions
	//testDefaultDynamicArray();
	//testOneElementArray();
	//testMultiElementArray();
	//testElementsContents();
	//testCopyConstructor();
	//testCopyAssignmentOperator();
	//testMoveConstructor();
	testMoveAssignmentOperator();
}

/******************************************************************************************************************************************************/
/******************************** Test Functions ******************************************************************************************************/

void testDefaultDynamicArray() {
	std::cout << std::boolalpha;

	// 1. Default size array
	std::cout << "Create an array of the default size:\n";
	DynamicArray<int> da1;
	std::cout << "da1 default capacity: " << da1.capacity() << '\n';
	std::cout << "da1 default size:     " << da1.size() << '\n';
	std::cout << "da1 empty:            " << da1.isEmpty() << '\n';

	// Check what we've got
	std::cout << "\nCurrent contents of da1:\n";
	std::cout << da1 << '\n';

	// Contains
	std::optional<int> removed;
	for (int i = 0; i < 5; i++) {
		std::cout << "\n\n";
		std::cout << "Array contains " << i * 10 << ": "
			<< da1.contains(i * 10) << '\n';
		std::cout << "Index of       " << i * 10 << ": "
			<< da1.indexOf(i * 10) << '\n';
		std::cout << i * 10 << " removed:        "
			<< da1.remove(i * 10) << '\n';
	}
}


void testOneElementArray() {
	std::cout << std::boolalpha;

	// 1. Default size array
	std::cout << "Create an array of the default size:\n";
	DynamicArray<int> da1(1);
	da1.add(10);
	std::cout << "da1 default capacity: " << da1.capacity() << '\n';
	std::cout << "da1 default size:     " << da1.size() << '\n';
	std::cout << "da1 empty:            " << da1.isEmpty() << '\n';

	// Check what we've got
	std::cout << "\nCurrent contents of da1:\n";
	std::cout << da1 << '\n';

	// Contains
	std::optional<int> removed;
	for (int i = 0; i < 5; i++) {
		std::cout << "\n\n";
		std::cout << "Array contains " << i * 10 << ": "
			<< da1.contains(i * 10) << '\n';
		std::cout << "Index of       " << i * 10 << ": "
			<< da1.indexOf(i * 10) << '\n';
		std::cout << i * 10 << " removed:        "
			<< da1.remove(i * 10) << '\n';
		std::cout << "\nCurrent contents of da1:\n";
		std::cout << da1 << '\n';
	}
}


void testMultiElementArray() {
	std::cout << std::boolalpha;

	// 1. Default size array
	std::cout << "Create an array of the default size:\n";
	DynamicArray<int> da1;

	// Add 10 elements
	for (int i = 1; i < 11; i++)
		da1.add(i);

	std::cout << "da1 default capacity: " << da1.capacity() << '\n';
	std::cout << "da1 default size:     " << da1.size() << '\n';
	std::cout << "da1 empty:            " << da1.isEmpty() << '\n';
	std::cout << "\nCurrent contents of da1:\n";
	std::cout << da1 << '\n';

	// Add another 10 elements (invokes a resize)
	for (int i = 11; i < 21; i++)
		da1.add(i);

	std::cout << "da1 current capacity: " << da1.capacity() << '\n';
	std::cout << "da1 current size:     " << da1.size() << '\n';
	std::cout << "\nCurrent contents of da1:\n";
	std::cout << da1 << "\n\n";

	/***********************************************************************/

	// Test clear operation
	std::cout << "\nTest clear:\n";
	da1.clear();
	std::cout << "da1 current capacity: " << da1.capacity() << '\n';
	std::cout << "da1 current size:     " << da1.size() << '\n';
	std::cout << "da1 empty:            " << da1.isEmpty() << '\n';
	std::cout << "\nCurrent contents of da1:\n";
	std::cout << da1 << '\n';

	// Add elements back in 
	for (int i = 0; i < 210; i += 10)
		da1.add(i);

	std::cout << "da1 current capacity: " << da1.capacity() << '\n';
	std::cout << "da1 current size:     " << da1.size() << '\n';
	std::cout << "da1 empty:            " << da1.isEmpty() << '\n';
	std::cout << "\nCurrent contents of da1:\n";
	std::cout << da1 << '\n';
	std::cout << da1 << "\n\n";

	/********************************************/

	std::cout << "\nTest set function....\n";
	bool setWorked = false;
	for (int i = 9; i < 14; i++) {
		setWorked = da1.set(i, i + 1);
		std::cout << "Element " << i << " set to " << i + 1 << ": "
			<< setWorked << '\n';
	}
	std::cout << "\nCurrent contents of da1:\n";
	std::cout << da1 << "\n\n";

	/********************************************/

	std::cout << "\nTest get function....\n";
	for (int i = 0; i < da1.size(); i++) {
		int item = da1.get(i);
		std::cout << "Element " << i << ": " << item << '\n';
	}

	/********************************************/

	std::cout << "\n\nTest remove functions....\n";
	std::optional<int> removedAt;
	for (int i = 9; i < 14; i++) {
		removedAt = da1.removeAt(i);
		if (removedAt.has_value())
			std::cout << removedAt.value() << " successfully removed...\n";
		else
			std::cout << "ERROR removing item at index " << i << '\n';
	}
	std::cout << "\nCurrent contents of da1:\n";
	std::cout << da1 << '\n';

	bool removed = false;
	std::cout << "\n\n";
	for (int i = 0; i < 4; i++) {
		removed = da1.remove(i * 10);
		if (removed)
			std::cout << "Item at index " << i << " successfully removed...\n";
		else
			std::cout << "ERROR removing item at index " << i << '\n';
	}

	std::cout << "\nCurrent contents of da1:\n";
	std::cout << da1 << '\n';
}


void testElementsContents() {

	std::cout << std::boolalpha;

	// 1. Default size array
	std::cout << "Create an array of the default size:\n";
	DynamicArray<int> da1;
	std::cout << "\nCurrent contents of da1:\n";
	std::cout << da1 << '\n';
	std::cout << "da1 default size: " << da1.size() << '\n';
	std::cout << "da1 empty:        " << da1.isEmpty() << '\n';

	std::cout << "\n\nTest contains on an empty array:\n";
	bool contained = false;
	for (int i = 1; i < 11; i++) {
		contained = da1.contains(i);
		std::cout << "Array contains " << i * 10 << ": " << contained << '\n';
	}

	std::cout << "\n\nTest indexOf on an empty array:\n";
	int index{};
	for (int i = 1; i < 11; i++) {
		index = da1.indexOf(i);
		std::cout << "Index of " << i * 10 << " is: " << index << '\n';
	}

	/***********************************************************************/

	std::cout << "\n\nNow add some elements to the array:\n";
	// Add some elements to the array
	for (int i = 0; i < 110; i += 10) {
		da1.add(i);
	}
	std::cout << "\nCurrent contents of da1:\n";
	std::cout << da1 << '\n';
	std::cout << "da1 default size: " << da1.size() << '\n';
	std::cout << "da1 empty:        " << da1.isEmpty() << '\n';

	std::cout << "\n\nTest contains on a populated array:\n";
	contained = false;
	for (int i = 1; i < 21; i++) {
		contained = da1.contains(i * 10);
		std::cout << "Array contains " << i * 10 << ": " << contained << '\n';
	}

	std::cout << "\n\nTest indexOf on a populated array:\n";
	index = 0;
	for (int i = 1; i < 21; i++) {
		index = da1.indexOf(i * 10);
		std::cout << "Index of " << i * 10 << " is: " << index << '\n';
	}

	/***********************************************************************/

	std::cout << "\n\nAdd another few elements (expand capacity)...\n";
	int nums[] = { 23, 34, 45, 12, 33, 54, 19, 78, 47, 27 };
	for (int i = 0; i < 3; i++) {
		for (int i = 0; i < 10; i++) {
			da1.add(nums[i]);
		}
	}

	std::cout << "\nCurrent contents of da1:\n";
	std::cout << da1 << '\n';
	std::cout << "da1 default size: " << da1.size() << '\n';
	std::cout << "da1 empty:        " << da1.isEmpty() << "\n\n";

	/***********************************************************************/

	std::cout << "\nRemove a few items...\n";
	da1.remove(nums[2]);
	da1.remove(nums[5]);
	std::cout << "\nCurrent contents of da1:\n";
	std::cout << da1 << '\n';
	std::cout << "da1 default size: " << da1.size() << '\n';
	std::cout << "da1 empty:        " << da1.isEmpty() << "\n\n";

	/***********************************************************************/

	std::cout << "\nClear existing array...\n";
	da1.clear();
	std::cout << "\nCurrent contents of da1:\n";
	std::cout << da1 << '\n';
	std::cout << "da1 default size: " << da1.size() << '\n';
	std::cout << "da1 empty:        " << da1.isEmpty() << '\n';
}

void testCopyConstructor() {
	std::cout << std::boolalpha;

	std::cout << "\nTest copy constructor...\n\n";
	// Create a new array
	DynamicArray<int> da1;

	// Add some elements to the array
	for (int i = 0; i < 210; i += 10) {
		da1.add(i);
	}

	std::cout << "\nCurrent contents of da1:\n";
	std::cout << da1 << '\n';
	std::cout << "da1 default size: " << da1.size() << '\n';
	std::cout << "da1 empty:        " << da1.isEmpty() << '\n';

	// Now copy construct from the first array
	DynamicArray<int> da2(da1);
	std::cout << "\n\nCurrent contents of da2:\n";
	std::cout << da2 << '\n';
	std::cout << "da2 default size: " << da2.size() << '\n';
	std::cout << "da2 empty:        " << da2.isEmpty() << '\n';

	// Copy construct via the other way
	DynamicArray<int> da3 = da1;
	std::cout << "\n\nCurrent contents of da3:\n";
	std::cout << da3 << '\n';
	std::cout << "da3 default size: " << da3.size() << '\n';
	std::cout << "da3 empty:        " << da3.isEmpty() << '\n';

	// Copy construct an empty array
	std::cout << "\n\nCopy constructing from an empty array...\n\n";
	DynamicArray<int> da4;

	// Manually calling the destructor is the only way to get a DynamicArray instance
	// object into a state where the underlying array is null.
	da4.~DynamicArray();
	DynamicArray<int> da5(da4);
	std::cout << "\n\nCurrent contents of da4:\n";
	std::cout << da4 << '\n';
	std::cout << "da4 default size: " << da4.size() << '\n';
	std::cout << "da4 empty:        " << da4.isEmpty() << '\n';

	std::cout << "\n\nCurrent contents of da5:\n";
	std::cout << da5 << '\n';
	std::cout << "da5 default size: " << da5.size() << '\n';
	std::cout << "da5 empty:        " << da5.isEmpty() << '\n';
}

void testCopyAssignmentOperator() {
	std::cout << std::boolalpha;

	// 1. Populated array
	std::cout << "\n(1) Copy assign from populated array...\n\n";

	// Create a new array
	DynamicArray<int> da1;

	// Add some elements to the array
	for (int i = 0; i < 110; i += 10) {
		da1.add(i);
	}

	std::cout << "\nCurrent contents of da1:\n";
	std::cout << da1 << '\n';
	std::cout << "da1 default size: " << da1.size() << '\n';
	std::cout << "da1 empty:        " << da1.isEmpty() << '\n';

	// Create another array
	DynamicArray<int> da2;

	// Add some elements to the array
	for (int i = 0; i < 20; ++i) {
		da2.add(i);
	}

	std::cout << "\nCurrent contents of da2:\n";
	std::cout << da2 << '\n';
	std::cout << "da2 default size: " << da2.size() << '\n';
	std::cout << "da2 empty:        " << da2.isEmpty() << '\n';

	std::cout << "\n\nCopy assign da2 into da1...\n";
	da1 = da2;	// copy assign

	std::cout << "\nCurrent contents of da1:\n";
	std::cout << da1 << '\n';
	std::cout << "da1 default size: " << da1.size() << '\n';
	std::cout << "da1 empty:        " << da1.isEmpty() << '\n';

	std::cout << "\nCurrent contents of da2:\n";
	std::cout << da2 << '\n';
	std::cout << "da2 default size: " << da2.size() << '\n';
	std::cout << "da2 empty:        " << da2.isEmpty() << '\n';

	/*********************************************************************/

	// 2. Copy assign from an empty array
	std::cout << "\n\n(2) Copy assign from an empty array into a populated array...\n";
	DynamicArray<int> da3;

	// Populate da3
	for (int i = 0; i < 5; ++i)
		da3.add(i);

	DynamicArray<int> da4;
	da4.~DynamicArray();	// Manually call destructor so array is null
	
	std::cout << "\n\nCurrent contents of da3:\n";
	std::cout << da3 << '\n';
	std::cout << "da3 size:         " << da3.size() << '\n';
	std::cout << "da3 empty:        " << da3.isEmpty() << '\n';

	std::cout << "\n\nCurrent contents of da4:\n";
	std::cout << da4 << '\n';
	std::cout << "da4 size:         " << da4.size() << '\n';
	std::cout << "da4 empty:        " << da4.isEmpty() << '\n';;

	// Copy assign empty array into populated array
	std::cout << "\nNow copy assign da4 into da3...\n";
	da3 = da4;

	std::cout << "\n\nContents of da3 after copy assign:\n";
	std::cout << da3 << '\n';
	std::cout << "da3 size:         " << da3.size() << '\n';
	std::cout << "da3 empty:        " << da3.isEmpty() << '\n';

	std::cout << "\n\nContents of da4 after copy assign:\n";
	std::cout << da4 << '\n';
	std::cout << "da4 size:         " << da4.size() << '\n';
	std::cout << "da4 empty:        " << da4.isEmpty() << '\n';
}

void testMoveConstructor() {
	std::cout << std::boolalpha;

	// 1. Move construct from populated array
	std::cout << "\n(1) Test move construct from a populated array...\n\n";
	// Create a new array
	DynamicArray<int> da1;

	// Add some elements to the array
	for (int i = 0; i < 210; i += 10) {
		da1.add(i);
	}

	std::cout << "\nCurrent contents of da1:\n";
	std::cout << da1 << '\n';
	std::cout << "da1 default size: " << da1.size() << '\n';
	std::cout << "da1 empty:        " << da1.isEmpty() << '\n';

	// Now move construct from the first array
	DynamicArray<int> da2(std::move(da1));
	std::cout << "\n\nAfter move constructing da2 from da1...\n";
	std::cout << "\n\nCurrent contents of da2:\n";
	std::cout << da2 << '\n';
	std::cout << "da2 default size: " << da2.size() << '\n';
	std::cout << "da2 empty:        " << da2.isEmpty() << '\n';

	std::cout << "\n\nCurrent contents of da1:\n";
	std::cout << da1 << '\n';
	std::cout << "da1 default size: " << da1.size() << '\n';
	std::cout << "da1 empty:        " << da1.isEmpty() << '\n';

	/**********************************************************************/

	// 2. Move construct via the assign construct
	std::cout << "\n\n(2) Test move constructor via =...\n";
	DynamicArray<int> da3;
	
	for (int i = 0; i < 5; ++i)
		da3.add(i);

	std::cout << "\n\nCurrent contents of da3:\n";
	std::cout << da3 << '\n';
	std::cout << "da3 default size: " << da3.size() << '\n';
	std::cout << "da3 empty:        " << da3.isEmpty() << '\n';

	std::cout << "\n\nMove constructing da4 from da3...\n";
	DynamicArray<int> da4 = std::move(da3);
	
	std::cout << "\n\nContents of da3 after move constructing:\n";
	std::cout << da3 << '\n';
	std::cout << "da3 default size: " << da3.size() << '\n';
	std::cout << "da3 empty:        " << da3.isEmpty() << '\n';

	std::cout << "\n\nContents of da4 after move constructing:\n";
	std::cout << da4 << '\n';
	std::cout << "da4 default size: " << da4.size() << '\n';
	std::cout << "da4 empty:        " << da4.isEmpty() << '\n';

	/**********************************************************************/

	// 3. Move construct from empty array
	std::cout << "\n\n(3) Move constructing from an empty array...\n\n";
	DynamicArray<int> da5;

	// Manually calling the destructor is the only way to get a DynamicArray instance
	// object into a state where the underlying array is null.
	da5.~DynamicArray();
	std::cout << "\n\nCurrent contents of da5:\n";
	std::cout << da5 << '\n';
	std::cout << "da5 default size: " << da5.size() << '\n';
	std::cout << "da5 empty:        " << da5.isEmpty() << '\n';

	std::cout << "\nMove construct da6 from da5...\n";
	DynamicArray<int> da6(std::move(da5));
	
	std::cout << "\n\nContents of da5 after move constructing:\n";
	std::cout << da5 << '\n';
	std::cout << "da5 default size: " << da5.size() << '\n';
	std::cout << "da5 empty:        " << da5.isEmpty() << '\n';

	std::cout << "\n\nContents of da6 after move constructing:\n";
	std::cout << da6 << '\n';
	std::cout << "da6 default size: " << da6.size() << '\n';
	std::cout << "da6 empty:        " << da6.isEmpty() << '\n';	
}

void testMoveAssignmentOperator() {
	std::cout << std::boolalpha;

	// 1. Move larger array into smaller
	std::cout << "\n(1) Test move larger array into smaller array...\n\n";

	// Create a new array
	DynamicArray<int> da1;

	// Add 10 elements to da1
	for (int i = 0; i < 110; i += 10) {
		da1.add(i);
	}

	std::cout << "\nCurrent contents of da1:\n";
	std::cout << da1 << '\n';
	std::cout << "da1 default size: " << da1.size() << '\n';
	std::cout << "da1 empty:        " << da1.isEmpty() << '\n';

	// Create another array
	DynamicArray<int> da2;

	// Add 20 elements to the da2
	for (int i = 0; i < 20; ++i) {
		da2.add(i);
	}

	std::cout << "\nCurrent contents of da2:\n";
	std::cout << da2 << '\n';
	std::cout << "da2 default size: " << da2.size() << '\n';
	std::cout << "da2 empty:        " << da2.isEmpty() << '\n';

	std::cout << "\n\nMove assign da2 into da1...\n";
	da1 = std::move(da2);	// move assign

	std::cout << "\nContents of da1 after move assign:\n";
	std::cout << da1 << '\n';
	std::cout << "da1 default size: " << da1.size() << '\n';
	std::cout << "da1 empty:        " << da1.isEmpty() << '\n';

	std::cout << "\nContents of da2 after move assign:\n";
	std::cout << da2 << '\n';
	std::cout << "da2 default size: " << da2.size() << '\n';
	std::cout << "da2 empty:        " << da2.isEmpty() << '\n';

	/**********************************************************************/
	
	// 2. Move populated arrays
	std::cout << "\n(2) Test move smaller array into larger array...\n\n";

	DynamicArray<int> da3;
	
	// Add 15 elements to da3
	for (int i = 0; i < 15; ++i) {
		da3.add(i);
	}

	DynamicArray<int> da4;

	// Add 5 elements to da4
	for (int i = 0; i < 5; ++i) {
		da4.add(i);
	}

	std::cout << "\nCurrent contents of da3:\n";
	std::cout << da3 << '\n';
	std::cout << "da3 size:          " << da3.size() << '\n';
	std::cout << "da3 empty:         " << da3.isEmpty() << '\n';

	std::cout << "\nCurrent contents of da4:\n";
	std::cout << da4 << '\n';
	std::cout << "da4 size:          " << da4.size() << '\n';
	std::cout << "da4 empty:         " << da4.isEmpty() << '\n';

	// Move assign da4 (smaller) into da3 (larger)
	da3 = std::move(da4);

	std::cout << "\n\nContents of da3 after move assign:\n";
	std::cout << da3 << '\n';
	std::cout << "da3 default size: " << da3.size() << '\n';
	std::cout << "da3 empty:        " << da3.isEmpty() << '\n';

	std::cout << "\n\nContents of da4 after move assign:\n";
	std::cout << da4 << '\n';
	std::cout << "da4 default size: " << da4.size() << '\n';
	std::cout << "da4 empty:        " << da4.isEmpty() << '\n';

	/**********************************************************************/

	// 3. Move empty array into populated array
	std::cout << "\n(3) Test empty array into populated array...\n\n";
	
	DynamicArray<int> da5;
	// Add 5 elements to da5
	for (int i = 0; i < 5; ++i) {
		da5.add(i);
	}

	DynamicArray<int> da6;
	da6.~DynamicArray();	// Manually call destructor so array is empty

	std::cout << "\n\nCurrent contents of da5:\n";
	std::cout << da5 << '\n';
	std::cout << "da5 default size: " << da5.size() << '\n';
	std::cout << "da5 empty:        " << da5.isEmpty() << '\n';

	std::cout << "\n\nCurrent contents of da6:\n";
	std::cout << da6 << '\n';
	std::cout << "da6 default size: " << da6.size() << '\n';
	std::cout << "da6 empty:        " << da6.isEmpty() << '\n';

	// Move empty da6 into populated da5
	std::cout << "\n\nNow move empty da6 into populated da5...\n";
	da5 = std::move(da6);

	std::cout << "\n\nContents of da5 after move:\n";
	std::cout << da5 << '\n';
	std::cout << "da5 default size: " << da5.size() << '\n';
	std::cout << "da5 empty:        " << da5.isEmpty() << '\n';

	std::cout << "\n\nContents of da6 after move:\n";
	std::cout << da6 << '\n';
	std::cout << "da6 size:         " << da6.size() << '\n';
	std::cout << "da6 empty:        " << da6.isEmpty() << '\n';
}
// Singly Linked List
// ------------------
// 
// See My Code School YouTube video for illustrated discussion - "Data Structures - Course Using C and C++"
// https://youtu.be/B31LgI4Y4DQ
// 
// See the Doubly Linked List test file for more background on linked lists as a whole.
//
// This class is equivalent to the forward_list class in the C++ standard library 
// (cppreference states that std::forward_list is implemented as a singly linked list).
// 
// A singly linked list supports forward traversal only, which makes accessing 
// some nodes more difficult (and therefore more costly) compared to a doubly
// linked list that supports bi-directional traversal.
// 
// However, a singly linked list has an advantage in that nodes only
// need one pointer (a next pointer), compared to two needed in the doubly 
// linked list (previous and next), so it requires less memory.

#include <algorithm>
#include <iomanip>
#include <iostream>

// User-defined header files
#include "Singly_Linked_List.h"

// Special Member test functions
void testEmptyList();
void testCopyConstructor();
void testMoveConstructor();
void testCopyAssignmentOperatorEmptyLists();
void testCopyAssignmentOperatorPopulatedLists();
void testMoveAssignmentOperatorEmptyLists();
void testMoveAssignmentOperatorPopulatedLists();

// Other test function declarations
void testPopulatedList();
void testInsertAtMiddle();
void testDeleteAt();
void testClearList();
void testReverseList();
void testPrintListRecursiveForwards();
void testPrintListRecursiveReverse();
void testInitializerConstructor();

// Utility functions declarations
void print_separator();
void printLogStart(const char* s);
void printLogEnd(const char* s);


int main() {
	// Call special member test functions
	//testEmptyList();
	//testCopyConstructor();
	//testMoveConstructor();
	//testCopyAssignmentOperatorEmptyLists();
	//testCopyAssignmentOperatorPopulatedLists();
	//testMoveAssignmentOperatorEmptyLists();
	testMoveAssignmentOperatorPopulatedLists();

	// Call other test functions
	//testPopulatedList();
	//testInsertAtMiddle();
	//testDeleteAt();
	//testClearList();
	//testReverseList();
	//testPrintListRecursiveForwards();
	//testPrintListRecursiveReverse();
	//testInitializerConstructor();
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


/*******************************************************************************************************************************************************/
/******************************** Test Functions *******************************************************************************************************/

// Special Member Functions Tests
// ==============================

void testEmptyList() {
	printLogStart(__FUNCTION__);

	// Setup a new (empty list)
	SinglyLinkedList<int> sll;

	if (sll.isEmpty())
		std::cout << "List is empty\n";
	else
		std::cout << "Error: empty list is not empty!!\n";

	if (!sll.peekFirst())
		std::cout << "List has no head node\n";
	else
		std::cout << "Error: empty list has a head node!!\n";

	if (!sll.peekLast())
		std::cout << "List has no tail node\n";
	else
		std::cout << "Error: empty list has a tail node!!\n";

	std::cout << "\nThe current contents of the list are:\n";
	sll.printList();

	printLogEnd(__FUNCTION__);
}


void testCopyConstructor() {
	std::cout << std::boolalpha;

	// 1. Test copy empty list
	std::cout << "(1) Empty list...\n";
	SinglyLinkedList<int> original;
	SinglyLinkedList<int> copy(original);

	std::cout << "\nCurrent contents of original list:\n";
	original.printList();
	std::cout << "Is original empty: " << original.isEmpty() << '\n';
	std::cout << "Size of original:  " << original.getSize() << '\n';

	std::cout << "\nCurrent contents of copy list:\n";
	copy.printList();
	std::cout << "Is copy empty:     " << copy.isEmpty() << '\n';
	std::cout << "Size of  copy:     " << copy.getSize() << '\n';

	// Make sure the newly copied list is usable 
	copy.insertAtHead(10);
	copy.insertAtTail(20);
	copy.insertAtTail(30);
	std::cout << "\nContents of copy list after adding some more items:\n";
	copy.printList();
	std::cout << "Is copy empty:     " << copy.isEmpty() << '\n';
	std::cout << "Size of  copy:     " << copy.getSize() << '\n';

	/****************************************************************************/

	// 2. Test copy a one element list
	std::cout << "\n\n(2) One element list...\n";
	original.insertAtHead(10);
	SinglyLinkedList<int> copy2(original);

	std::cout << "\nCurrent contents of original list:\n";
	original.printList();
	std::cout << "Is original empty: " << original.isEmpty() << '\n';
	std::cout << "Size of original:  " << original.getSize() << '\n';

	std::cout << "\nCurrent contents of copy2 list:\n";
	copy2.printList();
	std::cout << "Is copy2 empty:    " << copy2.isEmpty() << '\n';
	std::cout << "Size of  copy:     " << copy2.getSize() << '\n';

	// Make sure the newly copied list is usable 
	copy2.insertAtHead(20);
	copy2.insertAtTail(30);
	copy2.insertAtTail(40);
	std::cout << "\nContents of copy2 list after adding some more elements:\n";
	copy2.printList();
	std::cout << "Is copy2 empty:    " << copy2.isEmpty() << '\n';
	std::cout << "Size of copy2:     " << copy2.getSize() << '\n';

	/****************************************************************************/

	// 3. Test copy a multi element list
	std::cout << "\n\n(3) Multi element list...\n";

	for (int i = 20; i < 150; i += 10)
		original.insertAtTail(i);
	SinglyLinkedList<int> copy3(original);

	std::cout << "\nCurrent contents of original list:\n";
	original.printList();
	std::cout << "Is original empty: " << original.isEmpty() << '\n';
	std::cout << "Size of original:  " << original.getSize() << '\n';

	std::cout << "\nCurrent contents of copy3 list:\n";
	copy3.printList();
	std::cout << "Is copy3 empty:    " << copy3.isEmpty() << '\n';
	std::cout << "Size of copy3:     " << copy3.getSize() << '\n';

	// Just check both lists can cope with elements being added/removed
	original.deleteAt(1);
	original.insertAtHead(100);
	original.insertAtTail(230);
	original.insertAtTail(240);
	std::cout << "\nContents of original list after adding/removing:\n";
	original.printList();
	std::cout << "Is original empty:  " << original.isEmpty() << '\n';
	std::cout << "Size of original:   " << original.getSize() << '\n';

	copy3.deleteAt(1);
	copy3.insertAtHead(200);
	copy3.insertAtTail(300);
	copy3.insertAtTail(400);
	std::cout << "\nContents of copy3 list after adding/removing:\n";
	copy3.printList();
	std::cout << "Is copy3 empty:     " << copy3.isEmpty() << '\n';
	std::cout << "Size of copy3:      " << copy3.getSize() << '\n';
}

void testMoveConstructor() {
	std::cout << std::boolalpha;

	// 1. Test move an empty list
	std::cout << "(1) Empty list...\n";
	SinglyLinkedList<int> original;
	SinglyLinkedList<int> copy(std::move(original));

	std::cout << "\nCurrent contents of original list:\n";
	original.printList();
	std::cout << "Is original empty: " << original.isEmpty() << '\n';
	std::cout << "Size of original:  " << original.getSize() << '\n';

	std::cout << "\nCurrent contents of copy list:\n";
	copy.printList();
	std::cout << "Is copy empty:     " << copy.isEmpty() << '\n';
	std::cout << "Size of  copy:     " << copy.getSize() << '\n';

	// Make sure the newly copied list is usable 
	copy.insertAtHead(10);
	copy.insertAtTail(20);
	copy.insertAtTail(30);
	std::cout << "\nContents of copy list after adding some more items:\n";
	copy.printList();
	std::cout << "Is copy empty:     " << copy.isEmpty() << '\n';
	std::cout << "Size of  copy:     " << copy.getSize() << '\n';

	/****************************************************************************/

	// 2. Test move a one element list
	std::cout << "\n\n(2) One element list...\n";
	original.insertAtHead(10);
	SinglyLinkedList<int> copy2(std::move(original));

	std::cout << "\nCurrent contents of original list:\n";
	original.printList();
	std::cout << "Is original empty: " << original.isEmpty() << '\n';
	std::cout << "Size of original:  " << original.getSize() << '\n';

	std::cout << "\nCurrent contents of copy2 list:\n";
	copy2.printList();
	std::cout << "Is copy2 empty:    " << copy2.isEmpty() << '\n';
	std::cout << "Size of  copy:     " << copy2.getSize() << '\n';

	// Make sure the newly copied list is usable 
	copy2.insertAtHead(20);
	copy2.insertAtTail(30);
	copy2.insertAtTail(40);
	std::cout << "\nContents of copy2 list after adding some more elements:\n";
	copy2.printList();
	std::cout << "Is copy2 empty:    " << copy2.isEmpty() << '\n';
	std::cout << "Size of copy2:     " << copy2.getSize() << '\n';

	/****************************************************************************/

	// 3. Test move a multi element list
	std::cout << "\n\n(3) Multi element list...\n";

	for (int i = 20; i < 150; i += 10)
		original.insertAtTail(i);
	
	std::cout << "\nContents of original list before move:\n";
	original.printList();
	std::cout << "Is original empty: " << original.isEmpty() << '\n';
	std::cout << "Size of original:  " << original.getSize() << '\n';

	std::cout << "\n\nNow move construct copy3 from original...\n\n";
	SinglyLinkedList<int> copy3(std::move(original));

	// Original list may now be in an unusable stats
	std::cout << "\nContents of original list after move:\n";
	original.printList();
	std::cout << "Is original empty: " << original.isEmpty() << '\n';
	std::cout << "Size of original:  " << original.getSize() << '\n';

	std::cout << "\nContents of copy3 list after move:\n";
	copy3.printList();
	std::cout << "Is copy3 empty:    " << copy3.isEmpty() << '\n';
	std::cout << "Size of copy3:     " << copy3.getSize() << '\n';

	// Check copy list can cope with elements being added/removed
	copy3.deleteAt(1);
	copy3.insertAtHead(200);
	copy3.insertAtTail(300);
	copy3.insertAtTail(400);
	std::cout << "\nContents of copy3 list after adding/removing:\n";
	copy3.printList();
	std::cout << "Is copy3 empty:     " << copy3.isEmpty() << '\n';
	std::cout << "Size of copy3:      " << copy3.getSize() << '\n';
}

void testCopyAssignmentOperatorEmptyLists() {
	std::cout << std::boolalpha;

	// 1. Test copy empty list into an already empty list
	std::cout << "(1) Empty list assigned into empty list...\n";
	SinglyLinkedList<int> list1;
	SinglyLinkedList<int> list2;

	std::cout << "\nCurrent contents of list1:\n";
	list1.printList();
	std::cout << "Is original empty: " << list1.isEmpty() << '\n';
	std::cout << "Size of original:  " << list1.getSize() << '\n';

	std::cout << "\nCurrent contents of list2:\n";
	list2.printList();
	std::cout << "Is original empty: " << list2.isEmpty() << '\n';
	std::cout << "Size of original:  " << list2.getSize() << '\n';

	// Copy list2 into list1
	list1 = list2;
	std::cout << "\n\nAfter copying list2 into list1...\n";

	std::cout << "\nCurrent contents of list1:\n";
	list1.printList();
	std::cout << "Is original empty: " << list1.isEmpty() << '\n';
	std::cout << "Size of original:  " << list1.getSize() << '\n';

	std::cout << "\nCurrent contents of list2:\n";
	list2.printList();
	std::cout << "Is original empty: " << list2.isEmpty() << '\n';
	std::cout << "Size of original:  " << list2.getSize() << '\n';

	/****************************************************************************/

	// 2. Test copy empty list into an populated list
	std::cout << "\n\n(2) Empty list assigned into populated list...\n";

	// Add some elements to list
	for (int i = 0; i < 11; ++i)
		list1.insertAtTail(i);

	std::cout << "\nCurrent contents of list1:\n";
	list1.printList();
	std::cout << "Is original empty: " << list1.isEmpty() << '\n';
	std::cout << "Size of original:  " << list1.getSize() << '\n';

	std::cout << "\nCurrent contents of list2:\n";
	list2.printList();
	std::cout << "Is original empty: " << list2.isEmpty() << '\n';
	std::cout << "Size of original:  " << list2.getSize() << '\n';

	// Copy list2 into list1
	list1 = list2;
	std::cout << "\n\nAfter copying list2 into list1...\n";

	std::cout << "\nCurrent contents of list1:\n";
	list1.printList();
	std::cout << "Is original empty: " << list1.isEmpty() << '\n';
	std::cout << "Size of original:  " << list1.getSize() << '\n';

	std::cout << "\nCurrent contents of list2:\n";
	list2.printList();
	std::cout << "Is original empty: " << list2.isEmpty() << '\n';
	std::cout << "Size of original:  " << list2.getSize() << '\n';

	/****************************************************************************/

	// 3. Test copy populated into an empty list
	std::cout << "\n\n(3) Populated list assigned into empty list...\n";

	// Clear list1
	list1.clear();

	// Add some elements to list2
	for (int i = 0; i < 11; ++i)
		list2.insertAtTail(i);

	std::cout << "\nCurrent contents of list1:\n";
	list1.printList();
	std::cout << "Is original empty: " << list1.isEmpty() << '\n';
	std::cout << "Size of original:  " << list1.getSize() << '\n';

	std::cout << "\nCurrent contents of list2:\n";
	list2.printList();
	std::cout << "Is original empty: " << list2.isEmpty() << '\n';
	std::cout << "Size of original:  " << list2.getSize() << '\n';

	// Copy list2 into list1
	list1 = list2;
	std::cout << "\n\nAfter copying list2 into list1...\n";

	std::cout << "\nCurrent contents of list1:\n";
	list1.printList();
	std::cout << "Is original empty: " << list1.isEmpty() << '\n';
	std::cout << "Size of original:  " << list1.getSize() << '\n';

	std::cout << "\nCurrent contents of list2:\n";
	list2.printList();
	std::cout << "Is original empty: " << list2.isEmpty() << '\n';
	std::cout << "Size of original:  " << list2.getSize() << '\n';

	/****************************************************************************/

	// 4. Self-assign with copy
	std::cout << "\n\n(4) Self-assign empty list...\n";
	SinglyLinkedList<int> list3;

	std::cout << "\nCurrent contents of list3:\n";
	list3.printList();
	std::cout << "Is list3 empty: " << list3.isEmpty() << '\n';
	std::cout << "Size of list3:  " << list3.getSize() << '\n';

	std::cout << "\nSelf-assign list3...\n";
	list3 = list3;

	std::cout << "\nContents of list3 after self-assign:\n";
	list3.printList();
	std::cout << "Is list3 empty: " << list3.isEmpty() << '\n';
	std::cout << "Size of list3:  " << list3.getSize() << '\n';
}


void testCopyAssignmentOperatorPopulatedLists() {
	std::cout << std::boolalpha;

	// 1. Test copy lists of equal sizes
	std::cout << "(1) 10-element list copied into ten-element list...\n";
	SinglyLinkedList<int> list1;
	SinglyLinkedList<int> list2;

	// Add some elements to list1
	for (int i = 1; i < 11; ++i)
		list1.insertAtTail(i);

	// Add some elements to list2
	for (int i = 11; i < 21; ++i)
		list2.insertAtTail(i);

	std::cout << "\nCurrent contents of list1:\n";
	list1.printList();
	std::cout << "Is list1 empty:         " << list1.isEmpty() << '\n';
	std::cout << "Size of list1:          " << list1.getSize() << '\n';
	std::cout << "First element of list1: " << list1.peekFirst().value() << '\n';
	std::cout << "Last element of list1:  " << list1.peekLast().value() << '\n';

	std::cout << "\nCurrent contents of list2:\n";
	list2.printList();
	std::cout << "Is list2 empty:         " << list2.isEmpty() << '\n';
	std::cout << "Size of list2:          " << list2.getSize() << '\n';
	std::cout << "First element of list2: " << list2.peekFirst().value() << '\n';
	std::cout << "Last element of list2:  " << list2.peekLast().value() << '\n';

	// Copy list2 into list1
	list1 = list2;
	std::cout << "\n\nAfter copying list1 into list1...\n";

	std::cout << "\nCurrent contents of list1:\n";
	list1.printList();
	std::cout << "Is list1 empty:         " << list1.isEmpty() << '\n';
	std::cout << "Size of list1:          " << list1.getSize() << '\n';
	std::cout << "First element of list1: " << list1.peekFirst().value() << '\n';
	std::cout << "Last element of list1:  " << list1.peekLast().value() << '\n';

	std::cout << "\nCurrent contents of list2:\n";
	list2.printList();
	std::cout << "Is list2 empty:         " << list2.isEmpty() << '\n';
	std::cout << "Size of list2:          " << list2.getSize() << '\n';
	std::cout << "First element of list2: " << list2.peekFirst().value() << '\n';
	std::cout << "Last element of list2:  " << list2.peekLast().value() << '\n';

	/****************************************************************************/

	// 2. Copy longer list into longer list 
	std::cout << "\n\n(2) Copy a longer list into a shorter list (triggers extra memory to be allocated)...\n";

	SinglyLinkedList<int> list3;
	SinglyLinkedList<int> list4;

	// Add 5 elements to list3
	for (int i = 10; i < 60; i += 10)
		list3.insertAtTail(i);

	// Add 10 elements to list4
	for (int i = 110; i < 210; i += 10)
		list4.insertAtTail(i);

	std::cout << "\nCurrent contents of list3:\n";
	list3.printList();
	std::cout << "Is list3 empty:         " << list3.isEmpty() << '\n';
	std::cout << "Size of list3:          " << list3.getSize() << '\n';
	std::cout << "First element of list3: " << list3.peekFirst().value() << '\n';
	std::cout << "Last element of list3:  " << list3.peekLast().value() << '\n';

	std::cout << "\nCurrent contents of list4:\n";
	list4.printList();
	std::cout << "Is list4 empty:         " << list4.isEmpty() << '\n';
	std::cout << "Size of list4:          " << list4.getSize() << '\n';
	std::cout << "First element of list4: " << list4.peekFirst().value() << '\n';
	std::cout << "Last element of list4:  " << list4.peekLast().value() << '\n';

	// Copy list4 into list3
	list3 = list4;
	std::cout << "\n\nAfter copying list4 into list3...\n";

	std::cout << "\nCurrent contents of list3:\n";
	list3.printList();
	std::cout << "Is list3 empty:         " << list3.isEmpty() << '\n';
	std::cout << "Size of list3:          " << list3.getSize() << '\n';
	std::cout << "First element of list3: " << list3.peekFirst().value() << '\n';
	std::cout << "Last element of list3:  " << list3.peekLast().value() << '\n';

	std::cout << "\nCurrent contents of list4:\n";
	list4.printList();
	std::cout << "Is list4 empty:         " << list4.isEmpty() << '\n';
	std::cout << "Size of list4:          " << list4.getSize() << '\n';
	std::cout << "First element of list4: " << list4.peekFirst().value() << '\n';
	std::cout << "Last element of list4:  " << list4.peekLast().value() << '\n';

	/****************************************************************************/

	// 3. Copy shorter list into longer list 
	std::cout << "\n\n(3) Copy a shorter list into a longer list (triggers memory to be deallocated)...\n";

	SinglyLinkedList<int> list5;
	SinglyLinkedList<int> list6;

	// Add 12 elements to list5
	for (int i = 0; i < 60; i += 5)
		list5.insertAtTail(i);

	// Add 4 elements to list6
	for (int i = 0; i < 4; ++i)
		list6.insertAtTail(i);

	std::cout << "\nCurrent contents of list5:\n";
	list5.printList();
	std::cout << "Is list5 empty:         " << list5.isEmpty() << '\n';
	std::cout << "Size of list5:          " << list5.getSize() << '\n';
	std::cout << "First element of list5: " << list5.peekFirst().value() << '\n';
	std::cout << "Last element of list5:  " << list5.peekLast().value() << '\n';

	std::cout << "\nCurrent contents of list6:\n";
	list6.printList();
	std::cout << "Is list6 empty:         " << list6.isEmpty() << '\n';
	std::cout << "Size of list6:          " << list6.getSize() << '\n';
	std::cout << "First element of list6: " << list6.peekFirst().value() << '\n';
	std::cout << "Last element of list6:  " << list6.peekLast().value() << '\n';

	// Copy list6 into list5
	list5 = list6;
	std::cout << "\n\nAfter copying list6 into list5...\n";

	std::cout << "\nCurrent contents of list5:\n";
	list5.printList();
	std::cout << "Is list5 empty:         " << list5.isEmpty() << '\n';
	std::cout << "Size of list5:          " << list5.getSize() << '\n';
	std::cout << "First element of list5: " << list5.peekFirst().value() << '\n';
	std::cout << "Last element of list5:  " << list5.peekLast().value() << '\n';

	std::cout << "\nCurrent contents of list6:\n";
	list6.printList();
	std::cout << "Is list6 empty:         " << list6.isEmpty() << '\n';
	std::cout << "Size of list6:          " << list6.getSize() << '\n';
	std::cout << "First element of list6: " << list6.peekFirst().value() << '\n';
	std::cout << "Last element of list6:  " << list6.peekLast().value() << '\n';

	/****************************************************************************/

	// 5. Self-assign with copy
	std::cout << "\n\n(5) Self-assign populated list...\n";
	SinglyLinkedList<int> list7;

	// Add some elements to list7
	for (int i = 0; i < 5; ++i)
		list7.insertAtTail(i);

	std::cout << "\nCurrent contents of list7:\n";
	list7.printList();
	std::cout << "Is list3 empty: " << list7.isEmpty() << '\n';
	std::cout << "Size of list3:  " << list7.getSize() << '\n';

	std::cout << "\nSelf-assign list7...\n";
	list7 = list7;

	std::cout << "\nContents of list7 after self-assign:\n";
	list7.printList();
	std::cout << "Is list7 empty: " << list7.isEmpty() << '\n';
	std::cout << "Size of list7:  " << list7.getSize() << '\n';
}


void testMoveAssignmentOperatorEmptyLists() {
	std::cout << std::boolalpha;

	// 1. Test move empty list into an already empty list
	std::cout << "(1) Empty list moved into empty list...\n";
	SinglyLinkedList<int> list1;
	SinglyLinkedList<int> list2;

	std::cout << "\nCurrent contents of list1:\n";
	list1.printList();
	std::cout << "Is original empty: " << list1.isEmpty() << '\n';
	std::cout << "Size of original:  " << list1.getSize() << '\n';

	std::cout << "\nCurrent contents of list2:\n";
	list2.printList();
	std::cout << "Is original empty: " << list2.isEmpty() << '\n';
	std::cout << "Size of original:  " << list2.getSize() << '\n';

	// Move list2 into list1
	list1 = std::move(list2);
	std::cout << "\n\nAfter moving list1 into list1...\n";

	std::cout << "\nCurrent contents of list1:\n";
	list1.printList();
	std::cout << "Is original empty: " << list1.isEmpty() << '\n';
	std::cout << "Size of original:  " << list1.getSize() << '\n';

	std::cout << "\nCurrent contents of list2:\n";
	list2.printList();
	std::cout << "Is original empty: " << list2.isEmpty() << '\n';
	std::cout << "Size of original:  " << list2.getSize() << '\n';

	/****************************************************************************/

	// 2. Test move empty list into an populated list
	std::cout << "\n\n(2) Empty list moved into populated list...\n";

	SinglyLinkedList<int> list3;
	SinglyLinkedList<int> list4;

	// Add some elements to list
	for (int i = 0; i < 11; ++i)
		list3.insertAtTail(i);

	std::cout << "\nCurrent contents of list3:\n";
	list3.printList();
	std::cout << "Is list3 empty:         " << list3.isEmpty() << '\n';
	std::cout << "Size of list3:          " << list3.getSize() << '\n';
	std::cout << "First element of list3: " << list3.peekFirst().value() << '\n';
	std::cout << "Last element of list3:  " << list3.peekLast().value() << '\n';

	std::cout << "\nCurrent contents of list4:\n";
	list4.printList();
	std::cout << "Is list4 empty:         " << list4.isEmpty() << '\n';
	std::cout << "Size of list4:          " << list4.getSize() << '\n';

	// Move list4 into list3
	list3 = std::move(list4);
	std::cout << "\n\nAfter moving list4 into list3...\n";

	std::cout << "\nContents of list3 after move:\n";
	list3.printList();
	std::cout << "Is original empty:      " << list3.isEmpty() << '\n';
	std::cout << "Size of original:       " << list3.getSize() << '\n';

	std::cout << "\nContents of list4 after move:\n";
	list4.printList();
	std::cout << "Is list4 empty:         " << list4.isEmpty() << '\n';
	std::cout << "Size of list4:          " << list4.getSize() << '\n';

	/****************************************************************************/

	// 3. Test copy populated into an empty list
	std::cout << "\n\n(3) Populated list assigned into empty list...\n";

	SinglyLinkedList<int> list5;
	SinglyLinkedList<int> list6;

	// Add some elements to list6
	for (int i = 0; i < 11; ++i)
		list6.insertAtTail(i);

	std::cout << "\nCurrent contents of list5:\n";
	list5.printList();
	std::cout << "Is list5 empty:         " << list5.isEmpty() << '\n';
	std::cout << "Size of list5:          " << list5.getSize() << '\n';

	std::cout << "\nCurrent contents of list6:\n";
	list6.printList();
	std::cout << "Is list6 empty:         " << list6.isEmpty() << '\n';
	std::cout << "Size of list6:          " << list6.getSize() << '\n';
	std::cout << "First element of list6: " << list6.peekFirst().value() << '\n';
	std::cout << "Last element of list6:  " << list6.peekLast().value() << '\n';

	// Move list6 into list5
	list5 = std::move(list6);
	std::cout << "\n\nAfter moving list6 into list5...\n";

	std::cout << "\nContents of list5 after move:\n";
	list5.printList();
	std::cout << "Is list5 empty:         " << list5.isEmpty() << '\n';
	std::cout << "Size of list5:          " << list5.getSize() << '\n';
	std::cout << "First element of list5: " << list5.peekFirst().value() << '\n';
	std::cout << "Last element of list5:  " << list5.peekLast().value() << '\n';

	std::cout << "\nContents of list6 after move:\n";
	list6.printList();
	std::cout << "Is list6 empty:         " << list6.isEmpty() << '\n';
	std::cout << "Size of list6:          " << list6.getSize() << '\n';

	/****************************************************************************/

	// 4. Test move self-assign
	std::cout << "\n\n(4) Test self-move-assigning an empty list...\n";

	SinglyLinkedList<int> list7;

	std::cout << "\nCurrent contents of list7:\n";
	list7.printList();
	std::cout << "Is list7 empty:         " << list7.isEmpty() << '\n';
	std::cout << "Size of list7:          " << list7.getSize() << '\n';

	list7 = std::move(list7);
	std::cout << "After move self-assign...\n";
	std::cout << "\nContents of list7 after move:\n";
	list7.printList();
	std::cout << "Is list7 empty:         " << list7.isEmpty() << '\n';
	std::cout << "Size of list7:          " << list7.getSize() << '\n';
}


void testMoveAssignmentOperatorPopulatedLists() {
	std::cout << std::boolalpha;

	// 1. Test move lists of equal sizes
	std::cout << "(1) 10-element list moved into ten-element list...\n";
	SinglyLinkedList<int> list1;
	SinglyLinkedList<int> list2;

	// Add some elements to list1
	for (int i = 1; i < 11; ++i)
		list1.insertAtTail(i);

	// Add some elements to list2
	for (int i = 11; i < 21; ++i)
		list2.insertAtTail(i);

	std::cout << "\nCurrent contents of list1:\n";
	list1.printList();
	std::cout << "Is list1 empty:         " << list1.isEmpty() << '\n';
	std::cout << "Size of list1:          " << list1.getSize() << '\n';
	std::cout << "First element of list1: " << list1.peekFirst().value() << '\n';
	std::cout << "Last element of list1:  " << list1.peekLast().value() << '\n';

	std::cout << "\nCurrent contents of list2:\n";
	list2.printList();
	std::cout << "Is list2 empty:         " << list2.isEmpty() << '\n';
	std::cout << "Size of list2:          " << list2.getSize() << '\n';
	std::cout << "First element of list2: " << list2.peekFirst().value() << '\n';
	std::cout << "Last element of list2:  " << list2.peekLast().value() << '\n';

	// Move list2 into list1
	list1 = std::move(list2);
	std::cout << "\n\nAfter moving list1 into list1...\n";

	std::cout << "\nContents of list1 after moving:\n";
	list1.printList();
	std::cout << "Is list1 empty:         " << list1.isEmpty() << '\n';
	std::cout << "Size of list1:          " << list1.getSize() << '\n';
	std::cout << "First element of list1: " << list1.peekFirst().value() << '\n';
	std::cout << "Last element of list1:  " << list1.peekLast().value() << '\n';

	std::cout << "\nContents of list2 after moving:\n";
	list2.printList();
	std::cout << "Is list2 empty:         " << list2.isEmpty() << '\n';
	std::cout << "Size of list2:          " << list2.getSize() << '\n';

	/****************************************************************************/

	// 2. Move longer list into longer list 
	std::cout << "\n\n(2) Move a longer list into a shorter list (triggers extra memory to be allocated)...\n";

	SinglyLinkedList<int> list3;
	SinglyLinkedList<int> list4;

	// Add 5 elements to list3
	for (int i = 10; i < 60; i += 10)
		list3.insertAtTail(i);

	// Add 10 elements to list4
	for (int i = 110; i < 210; i += 10)
		list4.insertAtTail(i);

	std::cout << "\nCurrent contents of list3:\n";
	list3.printList();
	std::cout << "Is list3 empty:         " << list3.isEmpty() << '\n';
	std::cout << "Size of list3:          " << list3.getSize() << '\n';
	std::cout << "First element of list3: " << list3.peekFirst().value() << '\n';
	std::cout << "Last element of list3:  " << list3.peekLast().value() << '\n';

	std::cout << "\nCurrent contents of list4:\n";
	list4.printList();
	std::cout << "Is list4 empty:         " << list4.isEmpty() << '\n';
	std::cout << "Size of list4:          " << list4.getSize() << '\n';
	std::cout << "First element of list4: " << list4.peekFirst().value() << '\n';
	std::cout << "Last element of list4:  " << list4.peekLast().value() << '\n';

	// Move list4 into list3
	list3 = std::move(list4);
	std::cout << "\n\nAfter moving list4 into list3...\n";

	std::cout << "\nContents of list3 after move:\n";
	list3.printList();
	std::cout << "Is list3 empty:         " << list3.isEmpty() << '\n';
	std::cout << "Size of list3:          " << list3.getSize() << '\n';
	std::cout << "First element of list3: " << list3.peekFirst().value() << '\n';
	std::cout << "Last element of list3:  " << list3.peekLast().value() << '\n';

	std::cout << "\nContents of list4 after move:\n";
	list4.printList();
	std::cout << "Is list4 empty:         " << list4.isEmpty() << '\n';
	std::cout << "Size of list4:          " << list4.getSize() << '\n';

	/****************************************************************************/

	// 3. Move shorter list into longer list 
	std::cout << "\n\n(3) Copy a shorter list into a longer list (triggers memory to be deallocated)...\n";

	SinglyLinkedList<int> list5;
	SinglyLinkedList<int> list6;

	// Add 12 elements to list5
	for (int i = 0; i < 60; i += 5)
		list5.insertAtTail(i);

	// Add 4 elements to list6
	for (int i = 0; i < 4; ++i)
		list6.insertAtTail(i);

	std::cout << "\nCurrent contents of list5:\n";
	list5.printList();
	std::cout << "Is list5 empty:         " << list5.isEmpty() << '\n';
	std::cout << "Size of list5:          " << list5.getSize() << '\n';
	std::cout << "First element of list5: " << list5.peekFirst().value() << '\n';
	std::cout << "Last element of list5:  " << list5.peekLast().value() << '\n';

	std::cout << "\nCurrent contents of list6:\n";
	list6.printList();
	std::cout << "Is list6 empty:         " << list6.isEmpty() << '\n';
	std::cout << "Size of list6:          " << list6.getSize() << '\n';
	std::cout << "First element of list6: " << list6.peekFirst().value() << '\n';
	std::cout << "Last element of list6:  " << list6.peekLast().value() << '\n';

	// Move list6 into list5
	list5 = std::move(list6);
	std::cout << "\n\nAfter moving list6 into list5...\n";

	std::cout << "\nContents of list5 after move:\n";
	list5.printList();
	std::cout << "Is list5 empty:         " << list5.isEmpty() << '\n';
	std::cout << "Size of list5:          " << list5.getSize() << '\n';
	std::cout << "First element of list5: " << list5.peekFirst().value() << '\n';
	std::cout << "Last element of list5:  " << list5.peekLast().value() << '\n';

	std::cout << "\nContents of list6 after move:\n";
	list6.printList();
	std::cout << "Is list6 empty:         " << list6.isEmpty() << '\n';
	std::cout << "Size of list6:          " << list6.getSize() << '\n';

	/****************************************************************************/

	// 4. Test move self-assign
	std::cout << "\n\n(4) Test self-move-assigning a populated list...\n";

	SinglyLinkedList<int> list7;

	for (int i = 100; i < 1100; i += 100)
		list7.insertAtTail(i);

	std::cout << "\nCurrent contents of list7:\n";
	list7.printList();
	std::cout << "Is list7 empty:         " << list7.isEmpty() << '\n';
	std::cout << "Size of list7:          " << list7.getSize() << '\n';
	std::cout << "First element of list7: " << list7.peekFirst().value() << '\n';
	std::cout << "Last element of list7:  " << list7.peekLast().value() << '\n';

	list7 = std::move(list7);
	std::cout << "After move self-assign...\n";
	std::cout << "\nContents of list7 after move:\n";
	list7.printList();
	std::cout << "Is list7 empty:         " << list7.isEmpty() << '\n';
	std::cout << "Size of list7:          " << list7.getSize() << '\n';
	std::cout << "First element of list7: " << list7.peekFirst().value() << '\n';
	std::cout << "Last element of list7:  " << list7.peekLast().value() << '\n';
}


/******************************************************************************/

// Other Test Functions
// --------------------


void testPopulatedList() {
	printLogStart(__FUNCTION__);

	SinglyLinkedList<std::string> sll;

	std::cout << "\nContents of list to begin with:\n";
	sll.printList();

	// Now add some elements
	std::string words[] = { "I", "have", "of", "late,", "but",
		"wherefore", "I;", "know", "not,", "lost", "all", "my",
		"mirth,", "foregone", "all", "custom", "of", "exercises.",
		"and,", "indeed,", "it", "goes", "so", "heavily", "with",
		"my", "disposition", "that", "I", "have", "cancelled",
		"my", "Netflix", "subscription", "forthwith."};

	sll.insertAtHead("Hamlet: ");

	for (int i = 0; i < std::size(words); i++)
		sll.insert(words[i]);

	std::cout << "\nContents of list after insertions:\n";
	sll.printList();

	printLogEnd(__FUNCTION__);
}


// Test inserting some elements in the middle of an existing list
// (plus error conditions thereof).
void testInsertAtMiddle() {
	printLogStart(__FUNCTION__);

	SinglyLinkedList<int> sll;

	// 1. Insert into middle of empty list (no insert)
	std::cout << std::boolalpha;
	std::cout << "sll empty: " << sll.isEmpty() << '\n';
	int num1 = 50;
	if (!sll.insertAt(num1, 5)) {
		std::cout << "Cannot insert into the middle of an empty list!\n";
		std::cout << "sll empty: " << sll.isEmpty() << '\n';
	}

	// Create some elements to populate the list (using other methods)
	for (int i = 7; i >= 2; i--)
		sll.insertAtHead(i);

	std::cout << "\nInitial contents of list:\n";
	sll.printList();

	// 2. Insert into position zero (not valid)
	if (!sll.insertAt(num1, 0)) {
		std::cout << "Cannot insert into the zeroth element of a list!\n";
		std::cout << "sll empty: " << sll.isEmpty() << '\n';
		sll.printList();
	}

	// 3. Insert at element one (calls insertAtHead)
	if (sll.insertAt(1, 1)) {
		std::cout << "Successfully inserted into position 1 on list:\n";
		sll.printList();
	}

	// 4. Insert at a new last element position (calls insertAtTail)
	if (sll.insertAt(num1, 9)) {
		std::cout << "Successfully inserted into last position 9 on list:\n";
		sll.printList();
	}

	// 5. Insert at a middle position (calls helper function)
	if (sll.insertAt(100, 5)) {
		std::cout << "Successfully inserted into position 5 on list:\n";
		sll.printList();
	}

	// 6. Insert at current tail position -
	// calls helper function; tail moves up one
	if (sll.insertAt(6, 8)) {
		std::cout << "Successfully inserted into position 8 on list:\n";
		sll.printList();
	}

	// 7. Insert at current second position
	if (sll.insertAt(500, 2)) {
		std::cout << "Successfully inserted into position 2 on list:\n";
		sll.printList();
	}

	// 8. Insert at unviable position
	if (!sll.insertAt(500, 56)) {
		std::cout << "Cannot insert at position 56 on list!\n";
		sll.printList();
	}

	// 9. Insert at negative position
	if (!sll.insertAt(500, -100)) {
		std::cout << "Cannot insert at position -100 on list!\n";
		sll.printList();
	}

	printLogEnd(__FUNCTION__);
}


// Test deleting elements at specified positions in the list
// (plus error conditions thereof).
void testDeleteAt() {
	printLogStart(__FUNCTION__);
	SinglyLinkedList<int> sll;

	// 1. Delete from an empty list
	std::cout << std::boolalpha;
	std::cout << "sll empty: " << sll.isEmpty() << '\n';
	if (!sll.deleteAt(5)) {
		std::cout << "Cannot delete from an empty list!\n";
		std::cout << "sll empty: " << sll.isEmpty() << '\n';
	}

	// Populate list
	for (int i = 1; i < 11; i++)
		sll.insertAtTail(i);

	std::cout << "\nContents of the list:\n";
	sll.printList();

	// 2. Delete from position 0
	std::cout << "sll empty: " << sll.isEmpty() << '\n';
	if (!sll.deleteAt(0)) {
		std::cout << "Cannot delete from position 0!\n";
		sll.printList();
	}

	// 3. Delete from position 20 (beyond current list size)
	if (!sll.deleteAt(20)) {
		std::cout << "Cannot delete from position 20!\n";
		sll.printList();
	}

	// 4. Delete the head element
	if (sll.deleteAt(1)) {
		std::cout << "Head element deleted - old second element now new head...\n";
		sll.printList();
	}

	// 5. Delete the tail element
	if (sll.deleteAt(9)) {
		std::cout << "Tail element deleted - old penultimate element now new tail...\n";
		sll.printList();
	}

	// 6. Delete an element in the middle
	if (sll.deleteAt(4)) {
		std::cout << "Fourth element deleted...\n";
		sll.printList();
	}

	// 7. Repeatedly delete the second element
	for (int i = 0; i < 6; i++) {
		if (sll.deleteAt(2)) {
			std::cout << "Second element deleted...\n";
			sll.printList();
		}
	}

	// 8. Delete element one when there is only a head left
	if (sll.deleteAt(1)) {
		std::cout << "Head/only element deleted...\n";
		sll.printList();
		std::cout << "List is empty: " << sll.isEmpty() << '\n';
	}

	// 9. Delete element one when there is only a head left
	if (!sll.deleteAt(1)) {
		std::cout << "Cannot delete now that the list is empty...\n";
		sll.printList();
		std::cout << "List is empty: " << sll.isEmpty() << '\n';
	}

	printLogEnd(__FUNCTION__);
}


void testClearList() {
	printLogStart(__FUNCTION__);

	SinglyLinkedList<int> sll;

	// 1. Clear an empty linked list
	std::cout << std::boolalpha;
	std::cout << "Contents of list:\n";
	sll.printList();
	std::cout << "List is empty: " << sll.isEmpty() << '\n';
	sll.clear();
	std::cout << "List is empty: " << sll.isEmpty() << '\n';

	// 2. Clear a list with one element
	sll.insertAtHead(20);
	std::cout << "\n\nContents of list:\n";
	sll.printList();
	std::cout << "Clear list...\n";
	sll.clear();
	sll.printList();
	std::cout << "List is empty: " << sll.isEmpty() << '\n';

	// 3. Clear a list with two elements
	sll.insertAtHead(20);
	sll.insertAtHead(10);
	std::cout << "\n\nContents of list:\n";
	sll.printList();
	std::cout << "Clear list...\n";
	sll.clear();
	std::cout << "\n\nContents of list:\n";
	sll.printList();
	std::cout << "List is empty: " << sll.isEmpty() << '\n';


	// 3. Clear a list with multiple elements
	for (int i = 1; i < 21; i++)
		sll.insertAt(i, i);
	std::cout << "\n\nContents of list:\n";
	sll.printList();
	std::cout << "Clear list...\n";
	sll.clear();
	std::cout << "\n\nContents of list:\n";
	sll.printList();
	std::cout << "List is empty: " << sll.isEmpty() << '\n';

	printLogEnd(__FUNCTION__);
}


// Test the method that reverses the list using ordinary iterative logic.
void testReverseList() {
	printLogStart(__FUNCTION__);

	SinglyLinkedList<int> sll;

	// 1. Test an empty list
	std::cout << "Contents of list before reverse:\n";
	sll.printList();
	sll.reverseList();
	std::cout << "Contents of list after reverse:\n";
	sll.printList();

	// 2. Test a list with one node
	std::cout << "\n\nContents of list before reverse:\n";
	sll.insertAtHead(10);
	sll.printList();
	sll.reverseList();
	std::cout << "Contents of list after reverse:\n";
	sll.printList();

	// 3. Test a list with two nodes
	std::cout << "\n\nContents of list before reverse:\n";
	sll.insertAtHead(20);
	sll.printList();
	sll.reverseList();
	std::cout << "Contents of list after reverse:\n";
	sll.printList();

	// 4. Test a list with three nodes
	std::cout << "\n\nContents of list before reverse:\n";
	sll.clear();
	sll.insertAtHead(10);
	sll.insertAtHead(20);
	sll.insertAtHead(30);
	sll.printList();
	sll.reverseList();
	std::cout << "Contents of list after reverse:\n";
	sll.printList();

	// 5. Test a list with multiple
	std::cout << "\n\nContents of list before reverse:\n";
	sll.clear();

	// With list now empty, insert a decent number of nodes
	for (int i = 0; i < 21; i++)
		sll.insertAtHead(i * 10);
	sll.printList();
	sll.reverseList();
	std::cout << "\nContents of list after reverse:\n";
	sll.printList();
	std::cout << "\nReverse list again - should return it to the original order:\n";
	sll.reverseList();
	sll.printList();

	printLogEnd(__FUNCTION__);
}


void testPrintListRecursiveForwards() {
	printLogStart(__FUNCTION__);

	SinglyLinkedList<int> sll;

	// 1. Test printing empty list
	std::cout << "\nEmpty list...\n";
	std::cout << "\nContents of list:\n";
	sll.printListRecursive();

	// 2. Test printing a list with one element
	std::cout << "\nList with one element...\n";
	sll.insertAtHead(10);
	std::cout << "Contents of list:\n";
	sll.printListRecursive();

	// 3. Test printing a list with two elements
	std::cout << "\nList with two elements...\n";
	sll.insertAtHead(0);
	std::cout << "Contents of list:\n";
	sll.printListRecursive();

	// 4. Test printing a list with three elements
	std::cout << "\nList with three elements...\n";
	sll.insertAtHead(-10);
	std::cout << "Contents of list:\n";
	sll.printListRecursive();

	// 5. Test printing a list with multiple elements
	std::cout << "\nList with multiple elements...\n";
	sll.clear();

	for (int i = 0; i <= 50; i++)
		sll.insertAt(i, i + 1);
	std::cout << "Contents of list:\n";
	sll.printListRecursive();

	printLogEnd(__FUNCTION__);
}


void testPrintListRecursiveReverse() {
	printLogStart(__FUNCTION__);

	SinglyLinkedList<int> sll;

	// 1. Test printing empty list
	std::cout << "\nEmpty list...\n";
	std::cout << "\nContents of list:\n";
	sll.printListRecursive();

	// 2. Test printing a list with one element
	std::cout << "\nList with one element...\n";
	sll.insertAtHead(10);
	std::cout << "Contents of list:\n";
	sll.printListRecursive();

	// 3. Test printing a list with two elements
	std::cout << "\nList with two elements...\n";
	sll.insertAtHead(0);
	std::cout << "Contents of list:\n";
	sll.printListRecursive();

	// 4. Test printing a list with three elements
	std::cout << "\nList with three elements...\n";
	sll.insertAtHead(-10);
	std::cout << "Contents of list:\n";
	sll.printListRecursive();

	// 5. Test printing a list with multiple elements
	std::cout << "\nList with multiple elements...\n";
	sll.clear();

	for (int i = 0; i <= 50; i++)
		sll.insertAt(i, i + 1);
	std::cout << "Contents of list:\n";
	sll.printListRecursive();

	printLogEnd(__FUNCTION__);
}


void testInitializerConstructor() {
	printLogStart(__FUNCTION__);

	std::cout << "Create a singly-linked list of empty ints with the initializer_list constructor...\n";
	SinglyLinkedList<int> sll1{ {}, {}, {} };
	sll1.printList();

	std::cout << "Create a populated singly-linked list of ints with the initializer_list constructor...\n";
	SinglyLinkedList<int> sll2{ 10, 20, 30, 40, 50 };
	sll2.printList();

	std::cout << "\n\nCreate a singly-linked list of empty strings with the initializer_list constructor...\n";
	SinglyLinkedList<std::string> sll3{ {}, {}, {} };
	sll3.printList();

	std::cout << "Create a populated singly-linked list of strings with the initializer_list constructor...\n";
	SinglyLinkedList<std::string> sll4{ "What", "a", "piece", "of",
	"work", "is", "a", "man,", "how", "noble", "in", "reason,",
	"how", "infinite", "in", "faculties,", "in", "form", "and", "moving",
	"how", "express", "and", "admirable;", "in", "action", "how", "like",
	"Arnold", "Schwarzenegger", "in", "his", "prime."};
	sll4.printList();

	printLogEnd(__FUNCTION__);
}
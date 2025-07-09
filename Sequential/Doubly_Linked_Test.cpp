// Doubly Linked List
// ------------------
// 
// Based on example in YouTube video:
// "Data Structures Easy to Advanced Course - Full Tutorial from a Google Engineer"
//  
// https://youtu.be/RBSGKlAvoiM
// 
// This solution covers the Doubly Linked List data structure. The example used in that
// video is coded in Java; this is implemented in C++ so differs considerably in places
// (there are also a number of additional functions added to the class here
// that are not covered in that video).
// 
// The notes below are taken from the video.
// 
// 
// Linked Lists
// ------------
// 
// A linked list is a sequential list of nodes that hold data that point to other
// nodes also holding data.
// 
// Linked lists are used for various purposes:
// 
// 1. List, Queue, & Stack implementations.
// 2. Circular lists.
// 3. Real world objects, such as trains.
// 4. Separate chaining, which present certain Hashtable implementations to
//    deal with hashing collisions.
// 5. Implementations of adjacency lists in graphs.
//
// Terminology:
// 
// 1. Head:    The first node in a linked list
// 2. Tail:    The last node in a linked list
// 3. Pointer: A reference to another node (usually an actual pointer variable in C++)
// 4. Node:    An object containing data and a pointer or pointers.
// 
// 
// Singly Linked Lists
// -------------------
// 
// - Singly linked lists maintain a reference to the head and tail nodes for
//   quick additions and removals. 
// - Each node holds only one reference - to the next node.
// - They have a simple implementation and use little memory, but cannot easily 
//   access previous elements.
// 
// 
// Doubly Linked Lists
// -------------------
// 
// - Doubly linked lists also maintain a reference to the head and tail nodes for the 
//   same reason - to enable quick additions and removals.
// - However, each node holds *two* references - one to the next node and one to the
//   previous node.
// - They can be traversed backwards (allowing easy access to previous elements), 
//   but the require twice as much memory as a singly linked list.
// - The implementation of a doubly linked list is also more complex than that of 
//   a singly linked list, as each node has two pointers that need setting.
// 
// 
// Time Complexity of Operations
// -----------------------------
// 
// Operation				SLL							DLL
// ---------				---							---
// 
// Search					O(n)						O(n)
// Insert (head)			O(1)						O(1)
// Insert (tail)			O(1)						O(1)
// Remove at head			O(1)						O(1)
// Remove at tail			O(n)						O(1)
// Remove in middle			O(n)						O(n)
//
// Note: remove at tail from a singly linked list is a LINEAR operation even if we
// have a tail pointer setup, as we still need to advance a traversal pointer to 
// the node immediately before the tail (so that we can reference it, which we 
// will need to do as it will become the new tail node).

#include <algorithm>
#include <iomanip>
#include <iostream>

// User-defined header files
#include "Doubly_Linked_List.h"

// Tests for the special member functions
void testEmptyList();
void testCopyConstructor();
void testMoveConstructor();
void testCopyAssignmentOperatorEmptyLists();
void testCopyAssignmentOperatorPopulatedLists();
void testMoveAssignmentOperatorEmptyLists();
void testMoveAssignmentOperatorPopulatedLists();

// Tests for the other functions
void testInsertAtHead();
void testInsertAtTail();
void testRemoveFirst();
void testRemoveLast();
void testIndexOf();
void testRemoveAt();
void testReverseList();
void testListSort();
void testMerge();

int main() {
	// Call test functions for special member functions
	//testEmptyList();
	//testCopyConstructor();
	//testMoveConstructor();
	//testCopyAssignmentOperatorEmptyLists();
	//testCopyAssignmentOperatorPopulatedLists();
	//testMoveAssignmentOperatorEmptyLists();
	//testMoveAssignmentOperatorPopulatedLists();

	// Call test functions for other member functions
	/*testInsertAtHead();
	testInsertAtTail();
	testRemoveLast();
	testRemoveFirst();
	testIndexOf();
	testRemoveAt();
	testReverseList();
	testListSort();
	testMerge();*/
}

/*******************************************************************************************************************************************************/
/******************************** Test Functions *******************************************************************************************************/

// Special Member Functions Tests
// ==============================

void testEmptyList() {
	DoublyLinkedList<int> dll;

	// 1. Is list reporting as empty?
	std::cout << std::boolalpha;
	std::cout << "list is empty: " << dll.isEmpty() << '\n';

	// 2. Peek first
	if (!dll.peekFirst())
		std::cout << "There is no first element to peek at!\n";

	// 3. Peek last
	if (!dll.peekLast())
		std::cout << "There is no last element to peek at!\n";

	// 4. size check
	std::cout << "Size of the list is " << dll.getSize() << " elements\n";

	// 5. Print list
	std::cout << "\nThe current contents of the list are:\n";
	dll.printList();

	// 6. clear list
	dll.clear();
	std::cout << "\nThe contents of the list after clear:\n";
	dll.printList();
}

void testCopyConstructor() {
	std::cout << std::boolalpha;

	// 1. Test copy empty list
	std::cout << "Empty list...\n";
	DoublyLinkedList<int> original;
	DoublyLinkedList<int> copy(original);

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
	std::cout << "\n\nOne element list...\n";
	original.insertAtHead(10);
	DoublyLinkedList<int> copy2(original);

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
	std::cout << "\n\nMulti element list...\n";

	for (int i = 20; i < 150; i += 10)
		original.insertAtTail(i);
	DoublyLinkedList<int> copy3(original);

	std::cout << "\nCurrent contents of original list:\n";
	original.printList();
	std::cout << "Is original empty: " << original.isEmpty() << '\n';
	std::cout << "Size of original:  " << original.getSize() << '\n';

	std::cout << "\nCurrent contents of copy3 list:\n";
	copy3.printList();
	std::cout << "Is copy3 empty:    " << copy3.isEmpty() << '\n';
	std::cout << "Size of copy3:     " << copy3.getSize() << '\n';

	// Just check both lists can cope with elements being added/removed
	original.removeFirst();
	original.insertAtHead(100);
	original.insertAtTail(230);
	original.insertAtTail(240);
	std::cout << "\nContents of original list after adding/removing:\n";
	original.printList();
	std::cout << "Is original empty:  " << original.isEmpty() << '\n';
	std::cout << "Size of original:   " << original.getSize() << '\n';

	copy3.removeFirst();
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

	// 1. Test move empty list
	std::cout << "Move construct an empty list...\n";
	DoublyLinkedList<int> original;

	std::cout << "\nContents of original list before move:\n";
	original.printList();
	std::cout << "Is original empty: " << original.isEmpty() << '\n';
	std::cout << "Size of original:  " << original.getSize() << '\n';

	DoublyLinkedList<int> copy(std::move(original));

	std::cout << "\nContents of copy list after move:\n";
	copy.printList();
	std::cout << "Is copy empty:     " << copy.isEmpty() << '\n';
	std::cout << "Size of copy:      " << copy.getSize() << '\n';

	// Make sure the newly copied list is usable 
	copy.insertAtHead(10);
	copy.insertAtTail(20);
	copy.insertAtTail(30);
	std::cout << "\nContents of copy list after inserting some more elements:\n";
	copy.printList();
	std::cout << "Is copy empty:     " << copy.isEmpty() << '\n';
	std::cout << "Size of  copy:     " << copy.getSize() << '\n';

	/****************************************************************************/

	// 2. Test move a one element list
	std::cout << "\n\nMove construct a one element list...\n";
	original.insertAtHead(10);

	std::cout << "\nContents of original list before move:\n";
	original.printList();
	std::cout << "Is original empty: " << original.isEmpty() << '\n';
	std::cout << "Size of original:  " << original.getSize() << '\n';

	DoublyLinkedList<int> copy2(std::move(original));

	std::cout << "\nContents of copy2 list after move:\n";
	copy2.printList();
	std::cout << "Is copy2 empty:    " << copy2.isEmpty() << '\n';
	std::cout << "Size of  copy:     " << copy2.getSize() << '\n';

	// Make sure the newly copied list is usable 
	copy2.insertAtHead(20);
	copy2.insertAtTail(30);
	copy2.insertAtTail(40);
	std::cout << "\nCurrent contents of copy2 list:\n";
	copy2.printList();
	std::cout << "Is copy2 empty:    " << copy2.isEmpty() << '\n';
	std::cout << "Size of copy2:     " << copy2.getSize() << '\n';

	/****************************************************************************/

	// 3. Test move a multi element list
	std::cout << "\n\nMove construct a multi element list...\n";

	DoublyLinkedList<int> multi;

	for (int i = 20; i < 150; i += 10)
		multi.insertAtTail(i);

	std::cout << "\nContents of multi list before move:\n";
	multi.printList();
	std::cout << "Is multi empty: " << multi.isEmpty() << '\n';
	std::cout << "Size of multi:  " << multi.getSize() << '\n';

	DoublyLinkedList<int> copy3(std::move(multi));

	// multi should be unusable now
	std::cout << "\n\nAfter move operation...\n";
	std::cout << "Is multi empty: " << multi.isEmpty() << '\n';
	std::cout << "Size of multi:  " << multi.getSize() << '\n';

	std::optional<int> first = multi.peekFirst();
	if (!first.has_value())
		std::cout << "multi has no head element (must be an empty list now)...\n";

	std::cout << "\nContents of copy3 list after move:\n";
	copy3.printList();
	std::cout << "Is copy3 empty: " << copy3.isEmpty() << '\n';
	std::cout << "Size of copy3:  " << copy3.getSize() << '\n';

	copy3.removeFirst();
	copy3.insertAtHead(200);
	copy3.insertAtTail(300);
	copy3.insertAtTail(400);
	std::cout << "\nContents of copy3 list after some more elements added:\n";
	copy3.printList();
	std::cout << "Is copy3 empty:  " << copy3.isEmpty() << '\n';
	std::cout << "Size of copy3:   " << copy3.getSize() << '\n';
}

void testCopyAssignmentOperatorEmptyLists() {
	std::cout << std::boolalpha;

	// 1. Test copy empty list into an already empty list
	std::cout << "(1) Empty list assigned into empty list...\n";
	DoublyLinkedList<int> list1;
	DoublyLinkedList<int> list2;

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
	DoublyLinkedList<int> list3;

	// Add some elements to list3
	for (int i = 0; i < 11; ++i)
		list3.insertAtTail(i);

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
	DoublyLinkedList<int> list1;
	DoublyLinkedList<int> list2;

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

	DoublyLinkedList<int> list3;
	DoublyLinkedList<int> list4;


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

	DoublyLinkedList<int> list5;
	DoublyLinkedList<int> list6;

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
	DoublyLinkedList<int> list7;

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
	DoublyLinkedList<int> list1;
	DoublyLinkedList<int> list2;

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

	DoublyLinkedList<int> list3;
	DoublyLinkedList<int> list4;

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

	DoublyLinkedList<int> list5;
	DoublyLinkedList<int> list6;

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

	DoublyLinkedList<int> list7;

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
	DoublyLinkedList<int> list1;
	DoublyLinkedList<int> list2;

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

	DoublyLinkedList<int> list3;
	DoublyLinkedList<int> list4;

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

	DoublyLinkedList<int> list5;
	DoublyLinkedList<int> list6;

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

	DoublyLinkedList<int> list7;

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


/*************************************************************************************/
/*************************************************************************************/

// Tests of Other Functions
// ========================

void testInsertAtHead() {
	DoublyLinkedList<int> dll;

	// 1. Test on empty list
	std::cout << std::boolalpha;
	std::cout << "Is list empty: " << dll.isEmpty() << '\n';
	std::cout << "Size of list: " << dll.getSize() << '\n';

	dll.insertAtHead(20);
	std::cout << "\nContents of list after first insert at head:\n";
	dll.printList();
	std::cout << "Is list empty: " << dll.isEmpty() << '\n';
	std::cout << "Size of list: " << dll.getSize() << '\n';

	// 2. Test on populated list
	dll.insertAtHead(10);
	std::cout << "\nContents of list after second insert at head:\n";
	dll.printList();
	std::cout << "Is list empty: " << dll.isEmpty() << '\n';
	std::cout << "Size of list: " << dll.getSize() << '\n';

	// 3. Test again on populated list
	dll.clear();
	std::cout << "\nCurrent contents of list before starting insertions:\n";
	dll.printList();
	std::cout << "Is list empty: " << dll.isEmpty() << '\n';
	std::cout << "Size of list: " << dll.getSize() << '\n';

	for (int i = 10; i >= 0; i--) {
		dll.insertAtHead(i * 10);
		std::cout << "\nContents of list after inserting " << (i * 10) << ":\n";
		dll.printList();
	}

	std::cout << "\nIs list empty: " << dll.isEmpty() << '\n';
	std::cout << "Size of list: " << dll.getSize() << '\n';
}


void testInsertAtTail() {
	DoublyLinkedList<int> dll;

	// 1. Test on empty list
	std::cout << std::boolalpha;
	std::cout << "Is list empty: " << dll.isEmpty() << '\n';
	std::cout << "Size of list: " << dll.getSize() << '\n';

	dll.insertAtTail(10);
	std::cout << "\nContents of list after first insert at tail:\n";
	dll.printList();
	std::cout << "Is list empty: " << dll.isEmpty() << '\n';
	std::cout << "Size of list: " << dll.getSize() << '\n';

	/**************************************************************************************/

	// 2. Test on populated list
	dll.insertAtTail(20);
	std::cout << "\nContents of list after second insert at tail:\n";
	dll.printList();
	std::cout << "Is list empty: " << dll.isEmpty() << '\n';
	std::cout << "Size of list: " << dll.getSize() << '\n';

	/**************************************************************************************/

	// 3. Test again on populated list
	dll.clear();
	std::cout << "\nCurrent contents of list before starting insertions:\n";
	dll.printList();
	std::cout << "Is list empty: " << dll.isEmpty() << '\n';
	std::cout << "Size of list: " << dll.getSize() << '\n';

	for (int i = 0; i <= 10; i++) {
		dll.insertAtTail(i * 10);
		std::cout << "\nContents of list after inserting " << (i * 10) << ":\n";
		dll.printList();
	}

	std::cout << "\nIs list empty: " << dll.isEmpty() << '\n';
	std::cout << "Size of list: " << dll.getSize() << '\n';
}




void testRemoveFirst() {
	DoublyLinkedList<int> dll;
	std::cout << std::boolalpha;

	// 1. Remove first from empty list
	std::cout << "\nTest an empty list...\n";
	std::cout << "Contents of list before remove:\n";
	dll.printList();
	if (!dll.removeFirst()) {
		std::cout << "removeFirst from empty list handled gracefully...\n";
		std::cout << "Contents of list after remove:\n";
		dll.printList();
		std::cout << "Is list empty: " << dll.isEmpty() << '\n';
		std::cout << "Size of list:  " << dll.getSize() << '\n';
	}

	/**************************************************************************************/

	// 2. Remove first from a single element list
	std::cout << "\nTest a list with a single element...\n";
	dll.insertAtHead(10);
	std::cout << "Contents of list before remove:\n";
	dll.printList();
	std::cout << "Is list empty: " << dll.isEmpty() << '\n';
	std::cout << "Size of list:  " << dll.getSize() << '\n';

	std::optional<int> firstRemoved = dll.removeFirst();
	if (firstRemoved.has_value())
		std::cout << "Removed first element is: " << firstRemoved.value() << '\n';
	else
		std::cout << "Error returning value of first removed node!\n";

	std::cout << "\nContents of list after remove:\n";
	dll.printList();
	std::cout << "Is list empty: " << dll.isEmpty() << '\n';
	std::cout << "Size of list:  " << dll.getSize() << '\n';

	/**************************************************************************************/

	// 3. Remove first from a two element list
	std::cout << "\nTest a list with two elements...\n";
	dll.insertAtHead(20);
	dll.insertAtHead(10);
	std::cout << "Contents of list before remove:\n";
	dll.printList();
	std::cout << "Is list empty: " << dll.isEmpty() << '\n';
	std::cout << "Size of list:  " << dll.getSize() << '\n';

	firstRemoved = dll.removeFirst();
	if (firstRemoved.has_value())
		std::cout << "Removed first element is: " << firstRemoved.value() << '\n';
	else
		std::cout << "Error returning value of first removed node!\n";

	std::cout << "\nContents of list after remove:\n";
	dll.printList();
	std::cout << "Is list empty: " << dll.isEmpty() << '\n';
	std::cout << "Size of list:  " << dll.getSize() << '\n';

	/**************************************************************************************/

	// 4. Remove first from a list with three elements
	std::cout << "\nTest a list with three elements...\n";
	dll.clear();
	firstRemoved.reset();
	dll.insertAtHead(30);
	dll.insertAtHead(20);
	dll.insertAtHead(10);
	std::cout << "Contents of list before remove:\n";
	dll.printList();
	std::cout << "Is list empty: " << dll.isEmpty() << '\n';
	std::cout << "Size of list:  " << dll.getSize() << '\n';

	firstRemoved = dll.removeFirst();
	if (firstRemoved.has_value())
		std::cout << "Removed first element is: " << firstRemoved.value() << '\n';
	else
		std::cout << "Error returning value of first removed node!\n";

	std::cout << "\nContents of list after remove:\n";
	dll.printList();
	std::cout << "Is list empty: " << dll.isEmpty() << '\n';
	std::cout << "Size of list:  " << dll.getSize() << '\n';

	/**************************************************************************************/

	// 5. Remove first from a list with four elements
	std::cout << "\nTest a list with four elements...\n";
	dll.clear();
	firstRemoved.reset();
	dll.insertAtHead(40);
	dll.insertAtHead(30);
	dll.insertAtHead(20);
	dll.insertAtHead(10);
	std::cout << "Contents of list before remove:\n";
	dll.printList();
	std::cout << "Is list empty: " << dll.isEmpty() << '\n';
	std::cout << "Size of list:  " << dll.getSize() << '\n';

	firstRemoved = dll.removeFirst();
	if (firstRemoved.has_value())
		std::cout << "Removed first element is: " << firstRemoved.value() << '\n';
	else
		std::cout << "Error returning value of first removed node!\n";

	std::cout << "\nContents of list after remove:\n";
	dll.printList();
	std::cout << "Is list empty: " << dll.isEmpty() << '\n';
	std::cout << "Size of list:  " << dll.getSize() << '\n';

	/**************************************************************************************/

	// 6. Remove first from a list with many elements
	std::cout << "\nTest a list with many elements...\n";
	dll.clear();
	firstRemoved.reset();
	for (int i = 30; i >= 0; i--)
		dll.insertAtHead(i);

	std::cout << "Contents of list before remove:\n";
	dll.printList();
	std::cout << "Is list empty: " << dll.isEmpty() << '\n';
	std::cout << "Size of list:  " << dll.getSize() << '\n';

	firstRemoved = dll.removeFirst();
	if (firstRemoved.has_value())
		std::cout << "Removed first element is: " << firstRemoved.value() << '\n';
	else
		std::cout << "Error returning value of first removed node!\n";

	std::cout << "\nContents of list after remove:\n";
	dll.printList();
	std::cout << "Is list empty: " << dll.isEmpty() << '\n';
	std::cout << "Size of list:  " << dll.getSize() << '\n';
}


void testRemoveLast() {
	DoublyLinkedList<int> dll;
	std::cout << std::boolalpha;

	// 1. Remove last from empty list
	std::cout << "\nTest an empty list...\n";
	std::cout << "Contents of list before remove:\n";
	dll.printList();
	if (!dll.removeLast()) {
		std::cout << "removeLast from empty list handled gracefully...\n";
		std::cout << "\nContents of list after remove:\n";
		dll.printList();
		std::cout << "Is list empty: " << dll.isEmpty() << '\n';
		std::cout << "Size of list:  " << dll.getSize() << '\n';
	}

	/**************************************************************************************/

	// 2. Remove last from a single element list
	std::cout << "\nTest a list with a single element...\n";
	dll.insertAtHead(10);
	std::cout << "Contents of list before remove:\n";
	dll.printList();
	std::cout << "Is list empty: " << dll.isEmpty() << '\n';
	std::cout << "Size of list:  " << dll.getSize() << '\n';

	std::optional<int> lastRemoved = dll.removeLast();
	if (lastRemoved.has_value())
		std::cout << "Removed last element is: " << lastRemoved.value() << '\n';
	else
		std::cout << "Error returning value of last removed node!\n";

	std::cout << "\nContents of list after remove:\n";
	dll.printList();
	std::cout << "Is list empty: " << dll.isEmpty() << '\n';
	std::cout << "Size of list:  " << dll.getSize() << '\n';

	/**************************************************************************************/

	// 3. Remove last from a two element list
	std::cout << "\nTest a list with two elements...\n";
	dll.insertAtHead(20);
	dll.insertAtHead(10);
	std::cout << "Contents of list before remove:\n";
	dll.printList();
	std::cout << "Is list empty: " << dll.isEmpty() << '\n';
	std::cout << "Size of list:  " << dll.getSize() << '\n';

	lastRemoved = dll.removeLast();
	if (lastRemoved.has_value())
		std::cout << "Removed last element is: " << lastRemoved.value() << '\n';
	else
		std::cout << "Error returning value of last removed node!\n";

	std::cout << "\nContents of list after remove:\n";
	dll.printList();
	std::cout << "Is list empty: " << dll.isEmpty() << '\n';
	std::cout << "Size of list:  " << dll.getSize() << '\n';

	/**************************************************************************************/

	// 4. Remove last from a list with three elements
	std::cout << "\nTest a list with three elements...\n";
	dll.clear();
	lastRemoved.reset();
	dll.insertAtHead(30);
	dll.insertAtHead(20);
	dll.insertAtHead(10);
	std::cout << "Contents of list before remove:\n";
	dll.printList();
	std::cout << "Is list empty: " << dll.isEmpty() << '\n';
	std::cout << "Size of list:  " << dll.getSize() << '\n';

	lastRemoved = dll.removeLast();
	if (lastRemoved.has_value())
		std::cout << "Removed last element is: " << lastRemoved.value() << '\n';
	else
		std::cout << "Error returning value of last removed node!\n";

	std::cout << "\nContents of list after remove:\n";
	dll.printList();
	std::cout << "Is list empty: " << dll.isEmpty() << '\n';
	std::cout << "Size of list:  " << dll.getSize() << '\n';

	/**************************************************************************************/

	// 5. Remove last from a list with four elements
	std::cout << "\nTest a list with four elements...\n";
	dll.clear();
	lastRemoved.reset();
	dll.insertAtHead(40);
	dll.insertAtHead(30);
	dll.insertAtHead(20);
	dll.insertAtHead(10);
	std::cout << "Contents of list before remove:\n";
	dll.printList();
	std::cout << "Is list empty: " << dll.isEmpty() << '\n';
	std::cout << "Size of list:  " << dll.getSize() << '\n';

	lastRemoved = dll.removeLast();
	if (lastRemoved.has_value())
		std::cout << "Removed last element is: " << lastRemoved.value() << '\n';
	else
		std::cout << "Error returning value of last removed node!\n";

	std::cout << "\nContents of list after remove:\n";
	dll.printList();
	std::cout << "Is list empty: " << dll.isEmpty() << '\n';
	std::cout << "Size of list:  " << dll.getSize() << '\n';

	/**************************************************************************************/

	// 6. Remove last from a list with many elements
	std::cout << "\nTest a list with many elements...\n";
	dll.clear();
	lastRemoved.reset();
	for (int i = 30; i >= 0; i--)
		dll.insertAtHead(i);

	std::cout << "\nContents of list before remove:\n";
	dll.printList();
	std::cout << "Is list empty: " << dll.isEmpty() << '\n';
	std::cout << "Size of list:  " << dll.getSize() << '\n';

	lastRemoved = dll.removeLast();
	if (lastRemoved.has_value())
		std::cout << "Removed last element is: " << lastRemoved.value() << '\n';
	else
		std::cout << "Error returning value of last removed node!\n";

	std::cout << "\nContents of list after remove:\n";
	dll.printList();
	std::cout << "Is list empty: " << dll.isEmpty() << '\n';
	std::cout << "Size of list:  " << dll.getSize() << '\n';
}

void testIndexOf() {
	DoublyLinkedList<int> dll;
	std::cout << std::boolalpha;

	// 1. Find index on an empty list
	std::cout << "\nTest an empty list...\n";
	int searchVal = 10;
	int index = dll.indexOf(searchVal);
	if (index == -1)
		std::cout << "Cannot find the index of any value if the list is empty!\n";
	else
		std::cout << "ERROR: where has an index come from in an empty list?!\n";

	/**************************************************************************************/

	// 2. Find the index of the only element in a one-element list
	std::cout << "\nTest a one element list...\n";
	dll.insertAtHead(searchVal);
	std::cout << "\nCurrent contents of list:\n";
	dll.printList();

	index = dll.indexOf(searchVal);
	if (index == 1)
		std::cout << "Value found at index: " << index << '\n';
	else
		std::cout << "ERROR: value not found correctly! Found at index " << index << '\n';

	/**************************************************************************************/

	// 3. Find the index of an element not existing in a one-element list
	std::cout << "\nTest a one element list...\n";
	searchVal = 50;
	index = dll.indexOf(searchVal);
	if (index == -1)
		std::cout << "Correct result: " << searchVal << " not found.\n";
	else
		std::cout << "ERROR: " << searchVal << " found at index " << index << " : this is not the correct result!\n";

	/**************************************************************************************/

	// 4. Find the index of an element in a two-element list
	std::cout << "\nTest a search for an item in a two element list...\n";
	searchVal = 10;
	dll.insertAtHead(searchVal * 2);
	std::cout << "\nCurrent contents of list:\n";
	dll.printList();
	index = dll.indexOf(searchVal);
	if (index == 2)
		std::cout << "Correct result: " << searchVal << " found at index " << index << '\n';
	else
		std::cout << "ERROR: " << searchVal << " not found: this is not the correct result!\n";

	/**************************************************************************************/

	// 5. Find the index of an element not existing in a multi list
	std::cout << "\nTest a search for an item not existing in a multi element list...\n";
	searchVal = 78;
	dll.clear();

	for (int i = 1; i <= 25; i++)
		dll.insertAtTail(i);

	std::cout << "\nCurrent contents of list:\n";
	dll.printList();

	index = dll.indexOf(searchVal);
	if (index == -1)
		std::cout << "Correct result: " << searchVal << " not found!\n";
	else
		std::cout << "ERROR: " << searchVal << " found at index " << index << " - this is not the correct result!\n";

	/**************************************************************************************/

	// 6. Find the index of an element existing in a multi list
	std::cout << "\nTest a search for an item existing in a multi element list...\n";
	searchVal = 20;
	std::cout << "\nCurrent contents of list:\n";
	dll.printList();

	index = dll.indexOf(searchVal);
	if (index == 20)
		std::cout << "Correct result: " << searchVal << " found at index " << index << '\n';
	else
		std::cout << "ERROR: " << searchVal << " not found at index " << index << " - this is not the correct result!\n";
}


void testRemoveAt() {
	DoublyLinkedList<int> dll;
	std::cout << std::boolalpha;

	// 1. Remove from an empty list
	std::cout << "\nTest an empty list...\n";
	std::cout << "Contents of list before remove:\n";
	dll.printList();
	std::optional<int> deletedData = dll.removeAt(4);
	if (deletedData)
		std::cout << "ERROR: should not get deleted data back from empty list remove!\n";
	else
		std::cout << "No data returned from empty list remove\n";

	std::cout << "Contents of list after remove:\n";
	dll.printList();

	/**************************************************************************************/

	// 2. Remove at an invalid index
	std::cout << "\nTest an invalid index...\n";
	for (int i = 1; i < 10; i++)
		dll.insertAtTail(i);
	std::cout << "Contents of list before remove at index 12:\n";
	dll.printList();
	deletedData = dll.removeAt(12);
	if (deletedData)
		std::cout << "ERROR: should not get deleted data back from an invalid index remove!\n";
	else
		std::cout << "No data returned from invalid index remove\n";

	std::cout << "\nContents of list after remove:\n";
	dll.printList();

	/**************************************************************************************/

	// 3. Remove head from one element list
	std::cout << "\nTest remove head of single element list...\n";
	dll.clear();
	dll.insertAtHead(10);

	std::cout << "Contents of list before remove at index 1:\n";
	dll.printList();
	deletedData = dll.removeAt(1);
	if (!deletedData.has_value())
		std::cout << "ERROR: should get deleted data back!\n";
	else
		std::cout << deletedData.value() << " returned from index 1 remove\n";

	std::cout << "\nContents of list after remove:\n";
	dll.printList();

	/**************************************************************************************/

	// 4. Remove head from two element list
	std::cout << "\nTest remove head of two element list...\n";
	dll.clear();
	dll.insertAtHead(20);
	dll.insertAtHead(10);

	std::cout << "Contents of list before remove at index 1:\n";
	dll.printList();
	deletedData = dll.removeAt(1);
	if (!deletedData.has_value())
		std::cout << "ERROR: should get deleted data back!\n";
	else
		std::cout << deletedData.value() << " returned from index 1 remove\n";

	std::cout << "\nContents of list after remove:\n";
	dll.printList();

	/**************************************************************************************/

	// 5. Remove head from multi element list
	std::cout << "\nTest remove head of multi element list...\n";
	dll.clear();

	for (int i = 1; i < 11; i++)
		dll.insertAtTail(i * 10);

	std::cout << "Contents of list before remove at index 1:\n";
	dll.printList();
	deletedData = dll.removeAt(1);
	if (!deletedData.has_value())
		std::cout << "ERROR: should get deleted data back!\n";
	else
		std::cout << deletedData.value() << " returned from index 1 remove\n";

	std::cout << "\nContents of list after remove:\n";
	dll.printList();

	/**************************************************************************************/

	// 6. Remove tail from two element list
	std::cout << "\nTest remove tail from two element list...\n";
	dll.clear();
	dll.insertAtHead(20);
	dll.insertAtHead(10);

	std::cout << "Contents of list before remove at index 2:\n";
	dll.printList();
	deletedData = dll.removeAt(2);
	if (!deletedData.has_value())
		std::cout << "ERROR: should get deleted data back!\n";
	else
		std::cout << deletedData.value() << " returned from index 2 remove\n";

	std::cout << "\nContents of list after remove:\n";
	dll.printList();

	/**************************************************************************************/

	// 7. Remove tail from multi element list
	std::cout << "\nTest remove tail from multi element list...\n";
	dll.clear();
	for (int i = 0; i < 11; i++)
		dll.insertAtTail(i * 10);

	std::cout << "Contents of list before remove at index 11:\n";
	dll.printList();
	deletedData = dll.removeAt(11);
	if (!deletedData.has_value())
		std::cout << "ERROR: should get deleted data back!\n";
	else
		std::cout << deletedData.value() << " returned from index 11 remove\n";

	std::cout << "\nContents of list after remove:\n";
	dll.printList();

	/**************************************************************************************/

	// 8. Remove at invalid index from multi element list
	std::cout << "\nTest remove from an invalid index in a multi element list...\n";
	dll.insertAtTail(100);
	std::cout << "Contents of list before remove at index 15:\n";
	dll.printList();
	deletedData = dll.removeAt(15);
	if (!deletedData.has_value())
		std::cout << "Cannot delete at index 15 - not in list!\n";
	else
		std::cout << "ERROR: somehow value returned invalid index remove!\n";

	std::cout << "\nContents of list after remove:\n";
	dll.printList();

	/**************************************************************************************/

	// 9. Remove from somewhere in the lower middle of a multi element list
	std::cout << "\nTest remove element from the first half of a populated list...\n";
	dll.clear();

	for (int i = 1; i < 21; i++)
		dll.insertAtTail(i);

	std::cout << "Contents of list before remove at index 7:\n";
	dll.printList();
	deletedData = dll.removeAt(7);
	if (!deletedData.has_value())
		std::cout << "ERROR: somehow value returned invalid index remove!\n";
	else
		std::cout << deletedData.value() << " deleted from index 7\n";

	std::cout << "\nContents of list after remove:\n";
	dll.printList();

	/**************************************************************************************/

	// 10. Remove from somewhere in the upper middle of a multi element list
	std::cout << "\nTest remove element from the second half of a list...\n";

	DoublyLinkedList<int> dll2;
	for (int i = 1; i < 11; ++i)
		dll2.insertAtTail(i * 10);

	std::cout << "Contents of list before remove at index 7:\n";
	dll2.printList();
	deletedData = dll2.removeAt(7);
	if (!deletedData.has_value())
		std::cout << "ERROR: somehow value returned invalid index remove!\n";
	else
		std::cout << deletedData.value() << " deleted from index 7\n";

	std::cout << "\nContents of list after remove:\n";
	dll2.printList();
	std::cout << "\nSize of list: " << dll2.getSize() << "\n\n";
}


// Test code for reversing list. 
// Internal implementation can be tweaked in the public facing method.
void testReverseList() {
	DoublyLinkedList<int> dll;
	std::cout << std::boolalpha;

	// 1. Reverse an empty list
	std::cout << "Reverse an empty list...\n";
	std::cout << "\nCurrent contents of list:\n";
	dll.printList();
	dll.reverseList();
	std::cout << "\nCurrent contents of list:\n";
	dll.printList();

	std::optional<int> currentHead = dll.peekFirst();
	std::optional<int> currentTail = dll.peekLast();

	if (currentHead.has_value())
		std::cout << "Current head: " << currentHead.value() << '\n';
	if (currentTail.has_value())
		std::cout << "Current tail: " << currentTail.value() << '\n';


	/**************************************************************************************/

	// 2. Reverse a one element list
	std::cout << "Reverse a one element list...\n";
	dll.insertAtHead(10);
	std::cout << "\nCurrent contents of list:\n";
	dll.printList();
	dll.reverseList();
	std::cout << "\nCurrent contents of list:\n";
	dll.printList();

	currentHead = dll.peekFirst();
	currentTail = dll.peekLast();

	if (currentHead.has_value())
		std::cout << "Current head: " << currentHead.value() << '\n';
	if (currentTail.has_value())
		std::cout << "Current tail: " << currentTail.value() << '\n';

	/**************************************************************************************/

	// 3. Reverse a two element list
	std::cout << "Reverse a two element list...\n";
	dll.insertAtHead(20);
	std::cout << "\nCurrent contents of list:\n";
	dll.printList();
	dll.reverseList();
	std::cout << "\nCurrent contents of list:\n";
	dll.printList();

	currentHead = dll.peekFirst();
	currentTail = dll.peekLast();

	if (currentHead.has_value())
		std::cout << "Current head: " << currentHead.value() << '\n';
	if (currentTail.has_value())
		std::cout << "Current tail: " << currentTail.value() << '\n';

	/**************************************************************************************/

	// 3. Reverse a three element list
	std::cout << "Reverse a three element list...\n";
	dll.clear();
	dll.insertAtTail(10);
	dll.insertAtTail(20);
	dll.insertAtTail(30);
	std::cout << "\nCurrent contents of list:\n";
	dll.printList();
	dll.reverseList();
	std::cout << "\nCurrent contents of list:\n";
	dll.printList();

	currentHead = dll.peekFirst();
	currentTail = dll.peekLast();

	if (currentHead.has_value())
		std::cout << "Current head: " << currentHead.value() << '\n';
	if (currentTail.has_value())
		std::cout << "Current tail: " << currentTail.value() << '\n';

	/**************************************************************************************/

	// 4. Reverse a multi element list
	std::cout << "\n\nReverse a multi element list...\n";
	dll.clear();
	for (int i = 1; i < 21; i++)
		dll.insertAtTail(i * 10);
	std::cout << "\nCurrent contents of list:\n";
	dll.printList();

	currentHead = dll.peekFirst();
	currentTail = dll.peekLast();

	if (currentHead.has_value())
		std::cout << "Current head: " << currentHead.value() << '\n';
	if (currentTail.has_value())
		std::cout << "Current tail: " << currentTail.value() << '\n';

	std::cout << "\nNow reverse multi element list...\n";
	dll.reverseList();

	std::cout << "\nContents of multi element list after reversing:\n";
	dll.printList();
	currentHead = dll.peekFirst();
	currentTail = dll.peekLast();

	if (currentHead.has_value())
		std::cout << "Current head: " << currentHead.value() << '\n';
	if (currentTail.has_value())
		std::cout << "Current tail: " << currentTail.value() << '\n';

	std::cout << "\nNow reverse multi element list again...\n";
	dll.reverseList();
	std::cout << "\nContents of list after reversing again:\n";
	dll.printList();

	currentHead = dll.peekFirst();
	currentTail = dll.peekLast();

	if (currentHead.has_value())
		std::cout << "Current head: " << currentHead.value() << '\n';
	if (currentTail.has_value())
		std::cout << "Current tail: " << currentTail.value() << '\n';
}


void testListSort() {
	DoublyLinkedList<int> dll;
	std::cout << std::boolalpha;

	// 1. Sort an empty list
	std::cout << "Sort an empty list...\n";
	std::cout << "\nContents of list before sort:\n";
	dll.printList();
	dll.sort();
	std::cout << "\nContents of list after sort:\n";
	dll.printList();

	/**************************************************************************************/

	// 2. Reverse a one element list
	std::cout << "\n\nSort a one element list...\n";
	dll.insertAtHead(10);
	std::cout << "\nContents of list before sort:\n";
	dll.printList();
	dll.sort();
	std::cout << "\nContents of list after sort:\n";
	dll.printList();

	/**************************************************************************************/

	// 3. Reverse a two element list
	std::cout << "\n\nSort a two element list...\n";
	dll.insertAtHead(20);
	std::cout << "\nContents of list before sort:\n";
	dll.printList();
	dll.sort();
	std::cout << "\nContents of list after sort:\n";
	dll.printList();

	/**************************************************************************************/

	// 3. Reverse a three element list
	std::cout << "\n\nSort a three element list...\n";
	dll.clear();
	dll.insertAtTail(40);
	dll.insertAtTail(10);
	dll.insertAtTail(6);
	std::cout << "\nContents of list before sort:\n";
	dll.printList();
	dll.sort();
	std::cout << "\nContents of list after sort:\n";
	dll.printList();

	/**************************************************************************************/

	// 4. Sort a multi element list
	std::cout << "\n\nSort a multi element unsorted list...\n";
	dll.clear();

	int unsortedNums[20] = { 5, 1, 8, 10, 12, -4, 89, 21, 98, 43,
							11, 43, 41, 37, 68, 22, 20, 74, 71, 19 };
	for (int i = 0; i < 20; i++)
		dll.insertAtTail(unsortedNums[i]);

	std::cout << "\nContents of list before sort:\n";
	dll.printList();
	dll.sort();
	std::cout << "\nContents of list after sort:\n";
	dll.printList();

	/**************************************************************************************/

	// 5. Sort a multi element list (sorted already)
	std::cout << "\n\nSort an multi element list already in sorted order...\n";
	std::cout << "\nContents of list before sort:\n";
	dll.printList();
	dll.sort();
	std::cout << "\nContents of list after sort:\n";
	dll.printList();
}


void testMerge() {
	DoublyLinkedList<int> dll1;
	DoublyLinkedList<int> dll2;
	std::cout << std::boolalpha;

	// 1. Merge on empty lists
	std::cout << "Empty lists merge...\n";
	std::cout << "Before merge main list:\n";
	dll1.printList();
	std::cout << "Before merge other list:\n";
	dll2.printList();
	std::cout << "\nMain list size:  " << dll1.getSize() << '\n';
	std::cout << "Other list size: " << dll2.getSize() << '\n';

	dll1.merge(dll2);
	std::cout << "\n\n";
	std::cout << "After merge main list:\n";
	dll1.printList();
	std::cout << "After merge other list:\n";
	dll2.printList();
	std::cout << "\nMain list size:  " << dll1.getSize() << '\n';
	std::cout << "Other list size: " << dll2.getSize() << '\n';

	/****************************************************************************************/

	// 2. Merge where main list is empty but other list is not empty
	std::cout << "\n\nMerge populated list into empty list...\n";
	dll2.insertAtHead(10);
	dll2.insertAtTail(20);
	dll2.insertAtTail(30);
	dll2.insertAtTail(40);
	dll2.insertAtTail(50);
	std::cout << "Before merge main list:\n";
	dll1.printList();
	std::cout << "Before merge other list:\n";
	dll2.printList();
	std::cout << "\nMain list size:  " << dll1.getSize() << '\n';
	std::cout << "Other list size: " << dll2.getSize() << '\n';

	dll1.merge(dll2);
	std::cout << "\n\n";
	std::cout << "After merge main list:\n";
	dll1.printList();
	std::cout << "After merge other list:\n";
	dll2.printList();
	std::cout << "\nMain list size:  " << dll1.getSize() << '\n';
	std::cout << "Other list size: " << dll2.getSize() << '\n';

	/****************************************************************************************/

	// 3. Merge where main list is populated but other list is empty
	std::cout << "\n\nMerge empty list into populated list...\n";
	dll1.clear();
	dll2.clear();

	for (int i = 0; i < 11; i++) {
		int num = i * 10;
		dll1.insertAtTail(num);
		dll1.insertAtTail(num + 5);
	}

	std::cout << "Before merge main list:\n";
	dll1.printList();
	std::cout << "Before merge other list:\n";
	dll2.printList();
	std::cout << "\nMain list size:  " << dll1.getSize() << '\n';
	std::cout << "Other list size: " << dll2.getSize() << '\n';

	dll1.merge(dll2);
	std::cout << "\n\n";
	std::cout << "After merge main list:\n";
	dll1.printList();
	std::cout << "After merge other list:\n";
	dll2.printList();
	std::cout << "\nMain list size:  " << dll1.getSize() << '\n';
	std::cout << "Other list size: " << dll2.getSize() << '\n';

	/****************************************************************************************/

	// 4. Merge where main list is populated and other list is populated
	std::cout << "\n\nMerge populated list into an already populated list...\n";
	dll1.clear();
	dll2.clear();

	for (int i = 0; i < 11; i++)
		dll1.insertAtTail(i * 10);

	for (int i = 0; i < 11; i++)
		dll2.insertAtTail((i * 10) + 5);

	std::cout << "Before merge main list:\n";
	dll1.printList();
	std::cout << "Before merge other list:\n";
	dll2.printList();
	std::cout << "\nMain list size:  " << dll1.getSize() << '\n';
	std::cout << "Other list size: " << dll2.getSize() << '\n';

	dll1.merge(dll2);
	std::cout << "\n\n";
	std::cout << "After merge main list:\n";
	dll1.printList();
	std::cout << "After merge other list:\n";
	dll2.printList();
	std::cout << "\nMain list size:  " << dll1.getSize() << '\n';
	std::cout << "Other list size: " << dll2.getSize() << '\n';

	/****************************************************************************************/

	// 5. Merge where there are numerous elements of similar size in each list
	std::cout << "\n\nMerge lists with similar elements...\n";
	dll1.clear();
	dll2.clear();

	for (int i = 0; i < 101; i++)
		dll1.insertAtTail(i);

	for (int i = 10; i < 151; i++) {
		if (i % 2 == 0)				// Insert all even numbers
			dll2.insertAtTail(i);
	}

	std::cout << "Before merge main list:\n";
	dll1.printList();
	std::cout << "Before merge other list:\n";
	dll2.printList();
	std::cout << "\nMain list size:  " << dll1.getSize() << '\n';
	std::cout << "Other list size: " << dll2.getSize() << '\n';

	std::cout << "\n\nExtra tests just to make sure: are pointers to certain elements still valid after the merge...\n";
	dll1.setOriginalListHead();
	dll1.setOriginalListTail();
	Node<int>* oldListHead = dll1.getOriginalListHead();
	Node<int>* oldListTail = dll1.getOriginalListTail();
	std::cout << "Original list head element: " << oldListHead->data << '\n';
	std::cout << "Original list head address: " << oldListHead << '\n';
	std::cout << "Original list tail element: " << oldListTail->data << '\n';
	std::cout << "Original list tail address: " << oldListTail << '\n';

	dll1.merge(dll2);
	std::cout << "\n\n";
	std::cout << "After merge main list:\n";
	dll1.printList();
	std::cout << "After merge other list:\n";
	dll2.printList();
	std::cout << "\nMain list size:  " << dll1.getSize() << '\n';
	std::cout << "Other list size: " << dll2.getSize() << '\n';

	// Refresh the mock iterators
	oldListHead = dll1.getOriginalListHead();
	oldListTail = dll1.getOriginalListTail();
	std::cout << "Original list head element: " << oldListHead->data << '\n';
	std::cout << "Original list head address: " << oldListHead << '\n';
	std::cout << "Original list tail element: " << oldListTail->data << '\n';
	std::cout << "Original list tail address: " << oldListTail << '\n';
}
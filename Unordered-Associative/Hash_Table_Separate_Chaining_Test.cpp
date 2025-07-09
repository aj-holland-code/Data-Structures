// Hash Table
// ----------
// 
// Based on example in YouTube video:
// "Data Structures Easy to Advanced Course - Full Tutorial from a Google Engineer"//  
// https://youtu.be/RBSGKlAvoiM
// 
// This solution covers the hash table data structure. 
// The example used in that video is coded in Java; this is implemented in C++ so
// differs considerably in places. 
// 
// The notes below are taken from the video. They begin covering hash tables in 
// general, and then continue to cover the specific type of hash table being 
// implemented here, which is a separate chaining solution.
// 
// Hash Tables - A Crash Course
// ----------------------------
// 
// A Hash Table (HT) is a data structure that provides a mapping from keys
// to values using a technique calling hashing. 
// This is referred to as key-value pairs.
// Keys must be unique, but values can be repeated.
// 
// HTs are often used to track item frequencies. For example, counting the
// number of times a word appears in a given text.
// 
// The key-value pairs you can place in a HT can be of any type; 
// they don't necessarily have to be strings and numbers, they can be objects.
// However, the keys must be hashable.
// 
// 
// Hash Functions
// --------------
// 
// A Hash Function - H(x) - is a function that maps a key 'x' to a whole
// number in a fixed range. 
// 
// If H(x) is equal to H(y), x and y *might* be equal.
// But we can say with certainty that if H(y) is not equal to H(x), 
// x and are *not* equal. This means that instead of comparing x and y directly, a 
// more effective method is to compare their hash values first, and only then 
// compare x and y. 
// 
// This is especially useful for comparing large data items (such as the contents of files), 
// since comparing them character-by-character is slow. If the hashes of the two files 
// are not equal, we know for sure that the file contents are not the same. If the hashes
// are the same, we know there is a chance the contents are the same and that we do then
// need to do the character-by-character comparison to determine this one way or the other.
// 
// Hash functions for files are more sophisticated than those used for hash tables. 
// Files use cryptographic hash functions (aka checksums).
// 
// Hash functions *MUST* be deterministic. This means that if H(x) = y, H(x)
// must always produce y and never another value. This is critical to the
// correct functioning of a hash function. No randomness permitted!
// 
// Hash functions should be uniform to minimise the number of hash collisions.
// A hash collision is when two objects x, y hash to the same value,
// i.e. H(x) = H(y).
// 
// 
// What Makes a Key of Type T Hashable?
// ------------------------------------
// 
// Hash functions must be deterministic. To ensure deterministic behaviour, keys used in
// the hash table must be immutable data types. If a key of type T is immutable, and we 
// have a hash function H(k) defined for all keys of type T, a key of type T is 
// therefore hashable.
// 
// 
// How Does a Hash Table Work?
// ---------------------------
// 
// Ideally, we want the hash table to offer very fast insertion, lookup, and 
// removal time for the data we are placing within it. 
// 
// We can offer these functions operating in constant time (O(1)) using a hash
// function as a way to index into the table. However, to ensure this, the table
// must have a good uniform hash function.
// 
// In the event of hash collisions, we need a collision resolution mechanism. 
// Two of the most popular are separate chaining and open addressing.
// 
// 1) Separate chaining uses multiple auxiliary data structures to deal with collisions.
//    A DS (usually a linked list) holds all the different values that hashed to a particular
//    value.
// 2) Open addressing retains all the data within a large array.
//    Collisions are dealt with by finding another place within the hash table for the object 
//    to be stored by offsetting it from the position to which it hashes. 
// 
// 
// Time Complexity of Operations
// -----------------------------
// 
// Operation				Average					Worst
// 
// Insertion				O(1)*					O(n)
// Removal					O(1)*					O(n)
// Search					O(1)*					O(n)
//
// *Reminder: the constant time behaviour depends on good uniform hashing!
//
//
// Separate Chaining
// -----------------
// 
// Separate chaining is one of many strategies used to resolve hash collisions.
// A data structure is maintained to hold all the different values 
// the hashing method produces.
//
// The data structure used to cache the hash values is usually but not exclusively
// a linked list. Other implementations use one or more of: arrays, binary trees, 
// self-balancing trees etc. However, be aware that some of these are more memory
// intensive and complex to implement than a simple linked list, which is perhaps why
// they are used less frequently in hashtable implementations.
// 
// In order to maintain O(1) insertion and lookup time complexity after the
// HT gets full, a new Hash Table (HT) with a larger capacity should be created, 
// with the items rehashed and reinserted and dispersed throughout the new HT at 
// different locations (than they were located at in the original HT).
// 
// To remove key-value pairs from the HT, do the lookup for the pair and then
// remove the node from the linked list structure.

#include <bit>
#include <iomanip>
#include <iostream>
#include <limits>

// User-defined header files
#include "Hash_Table_Separate_Chaining.h"

// Main test functions
void testEntryClass();
void testNormaliseIndex();
void testEmptyHashTable();
void testCopyConstructor();
void testMoveConstructor();
void testCopyAssignmentOperator();
void testMoveAssignmentOperator();

void testSingleEntryHashTable();
void testMultipleEntryHashTable();
void testGetValueFromTable();
void testRemoveValueFromTable();
void testResizeTable();
void testPrintHashTableContents();

// Supporting functions for tests
int normaliseIndex(int value, int max);

// Utility functions declarations
void print_separator();
void printLogStart(const char* s);
void printLogEnd(const char* s);
void printSpaces(int noSpaces);
void printUnderscores(int noUnderscores);

int main() {
	// Call test functions here	
	testEntryClass();
	testNormaliseIndex();
	testEmptyHashTable(); 
	testCopyConstructor();
	testMoveConstructor();
	testCopyAssignmentOperator();
	testMoveAssignmentOperator();

	testSingleEntryHashTable();
	testMultipleEntryHashTable();
	testGetValueFromTable();
	testRemoveValueFromTable();
	testResizeTable();
	testPrintHashTableContents();	
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

/****************************************************************************************/
/****************************** Test Functions ******************************************/

// First, test the entry class in isolation to make sure it works as expected.
void testEntryClass() {
	printLogStart(__FUNCTION__);
	std::cout << std::boolalpha;

	// Quickly test the Entry class itself
	int ids[] = { 1, 2, 3, 4, 5 };
	std::string names[] = { "Billy", "Jimmy", "Larry", "Sammy", "Fred" };
	Entry<int, std::string> e1(ids[0], names[0]);
	Entry<int, std::string> e2(ids[1], names[1]);
	Entry<int, std::string> e3(ids[2], names[2]);
	Entry<int, std::string> e4(ids[3], names[3]);
	Entry<int, std::string> e5(ids[4], names[4]);
	Entry<int, std::string> e6(ids[0], names[0]);

	Entry<int, std::string> entries[6];
	entries[0] = e1;
	entries[1] = e2;
	entries[2] = e3;
	entries[3] = e4;
	entries[4] = e5;
	entries[5] = e6;

	for (int i = 0; i < std::size(entries); i++) {
		std::cout << "\n";
		std::cout << "ID:   " << entries[i].key << '\n';
		std::cout << "Name: " << entries[i].value << '\n';
		std::cout << "Hash: " << entries[i].hash << '\n';
	}

	std::cout << "\n\n";
	std::cout << "e1 == e2: " << (e1 == e2) << '\n';
	std::cout << "e1 == e3: " << (e1 == e3) << '\n';
	std::cout << "e1 == e4: " << (e1 == e4) << '\n';
	std::cout << "e1 == e5: " << (e1 == e5) << '\n';
	std::cout << "e1 == e6: " << (e1 == e6) << '\n';

	printLogEnd(__FUNCTION__);
}



// Test the normalising function (copied in this file from header).
// The function in the header file is tested when testing other functions
// that call on it, but it's useful to test it here in isolation
// (for one thing to inspect how it works more closely).
void testNormaliseIndex() {
	printLogStart(__FUNCTION__);

	std::cout << "\nThe normaliseIndex function is based on bit masking on this value: 0x7FFFFFFF\n";

	int bitmask = 0x7FFFFFFF;
	std::cout << "bitmask: " << bitmask << '\n';

	print_separator();

	/************************************************************************/

	std::cout << "\nTest the normalising function in isolation...\n\n";

	const int MAX = 15;
	int index = 0;

	// Headers
	std::cout << "Value";
	printSpaces(5);
	std::cout << "Normalised Index\n";

	// Underlining
	printUnderscores(5);
	printSpaces(5);
	printUnderscores(18);
	std::cout << "\n\n";

	for (int i = 0; i < 100; i++) {
		index = normaliseIndex(i, MAX); // Always yields index in range [0-14)

		std::cout << i;
		int noSpaces = i < 10 ? 9 : 8;
		printSpaces(noSpaces);
		std::cout << index << '\n';
	}
	print_separator();

	/*************************************************************************/

	// What does the function do internally to the number?
	std::cout << "\nTest the normalise function's bitmasking...\n";

	// Headers
	std::cout << "Value";
	printSpaces(10);
	std::cout << "Masked Value\n";

	// Underlining
	printUnderscores(10);
	printSpaces(10);
	printUnderscores(14);
	std::cout << "\n\n";
	int maskedValue = 0;
	int value = std::numeric_limits<int>::min();

	// Do 100 examples - that's plenty
	for (int i = 0; i <= 100; i++) {
		maskedValue = (value & 0x7FFFFFFF);

		std::cout << value++;
		int noSpaces = i < 10 ? 9 : 8;
		printSpaces(noSpaces);
		std::cout << maskedValue << '\n';
	}
	print_separator();

	/*****************************************************************************/

	std::cout << "\nTest negative number...\n";
	int testHash = -68718177;	// Troublesome hash that's come up in test
	int positiveHash = (testHash & 0x7FFFFFFF);

	std::cout << "testHash:     " << testHash << '\n';
	std::cout << "positiveHash: " << positiveHash << '\n';

	int result = positiveHash % 8;
	std::cout << "result:   " << result << '\n';

	printLogEnd(__FUNCTION__);
}

// Converts a value to an index.
// Essentially, this strips the negative sign and places the value
// in the domain [0, max)
int normaliseIndex(int value, int max) {
	return (value & 0x7FFFFFFF) % max;
}



void testEmptyHashTable() {
	printLogStart(__FUNCTION__);
	std::cout << std::boolalpha;

	ChainedHashTable<std::string, int> table(5);
	std::cout << "table default capacity:     " << ChainedHashTable<std::string, int>::DEFAULT_CAPACITY << '\n';
	std::cout << "table default load factor:  " << ChainedHashTable<std::string, int>::DEFAULT_LOAD_FACTOR << '\n';
	std::cout << "table is empty:             " << table.isEmpty() << '\n';
	std::cout << "table size:                 " << table.size() << '\n';

	std::cout << "\nAfter clear:\n";
	table.clear();
	std::cout << "table default capacity:     " << ChainedHashTable<std::string, int>::DEFAULT_CAPACITY << '\n';
	std::cout << "table default load factor:  " << ChainedHashTable<std::string, int>::DEFAULT_LOAD_FACTOR << '\n';
	std::cout << "table is empty:             " << table.isEmpty() << '\n';
	std::cout << "table size:                 " << table.size() << '\n';
	print_separator();

	/*********************************************************************************/

	ChainedHashTable<std::string, int> table2(10);
	std::cout << "table2 is empty:            " << table2.isEmpty() << '\n';
	std::cout << "table2 size:                " << table2.size() << '\n';

	std::cout << "\nAfter clear:\n";
	table2.clear();
	std::cout << "table2 default capacity:    " << ChainedHashTable<std::string, int>::DEFAULT_CAPACITY << '\n';
	std::cout << "table2 default load factor: " << ChainedHashTable<std::string, int>::DEFAULT_LOAD_FACTOR << '\n';
	std::cout << "table2 is empty:            " << table2.isEmpty() << '\n';
	std::cout << "table2 size:                " << table2.size() << '\n';
	print_separator();

	/*********************************************************************************/

	ChainedHashTable<std::string, int> table3(20, 0.8);
	std::cout << "table3 is empty:            " << table3.isEmpty() << '\n';
	std::cout << "table3 size:                " << table3.size() << '\n';

	std::cout << "\nAfter clear:\n";
	table3.clear();
	std::cout << "table3 is empty:            " << table3.isEmpty() << '\n';
	std::cout << "table3 size:                " << table3.size() << '\n';
	print_separator();

	/*********************************************************************************/

	ChainedHashTable<std::string, int> table4;
	std::cout << "table4 is empty:            " << table4.isEmpty() << '\n';
	std::cout << "table4 size:                " << table4.size() << '\n';

	std::cout << "\nAfter clear:\n";
	table4.clear();
	std::cout << "table4 is empty:            " << table4.isEmpty() << '\n';
	std::cout << "table4 size:                " << table4.size() << '\n';
	
	printLogEnd(__FUNCTION__);
}

void testCopyConstructor() {
	printLogStart(__FUNCTION__);
	std::cout << std::boolalpha;

	// 1. Test empty table
	std::cout << "(1) Test copy construct from empty table...\n";
	ChainedHashTable<std::string, int> table1;
	std::cout << "table1 is empty:            " << table1.isEmpty() << '\n';
	std::cout << "table1 size:                " << table1.size() << '\n';

	std::cout << "\nCopy construct new table from table1...\n";
	ChainedHashTable<std::string, int> table2(table1);

	std::cout << "\nAfter copy construction...\n";
	std::cout << "table1 is empty:            " << table1.isEmpty() << '\n';
	std::cout << "table1 size:                " << table1.size() << '\n';
	std::cout << "table2 is empty:            " << table2.isEmpty() << '\n';
	std::cout << "table2 size:                " << table2.size() << '\n';	
	print_separator();

	/*********************************************************************************/
	
	// 2. Test populated table
	std::cout << "\n\n(2) Test copy construct from populated table...\n";
	ChainedHashTable<std::string, int> table3(20);

	// Add elements
	std::string names[] = { "Al Swearengen", "Cy Tolliver", "Dan Dority",
							"Johnny Burns", "Jimmy Irons", "Doc Cochran" };
	int ages[] = { 62, 62, 39, 34, 38, 50 };

	for (int i = 0; i < std::size(names); ++i)
		table3.insert(names[i], ages[i]);

	// Table 3
	std::cout << "Contents of table3:\n";
	table3.print();
	std::cout << "table3 is empty:            " << table3.isEmpty() << '\n';
	std::cout << "table3 size:                " << table3.size() << '\n';

	std::cout << "\nCopy construct new table from table3...\n";
	ChainedHashTable<std::string, int> table4(table3);

	std::cout << "\nAfter copy construction...\n";
	std::cout << "\nContents of table3:\n";
	table3.print();
	std::cout << "table3 is empty:            " << table3.isEmpty() << '\n';
	std::cout << "table3 size:                " << table3.size() << '\n';

	std::cout << "\nContents of table4:\n";
	table4.print();
	std::cout << "table4 is empty:            " << table4.isEmpty() << '\n';
	std::cout << "table4 size:                " << table4.size() << '\n';
	
	printLogEnd(__FUNCTION__);
}

void testMoveConstructor() {
	printLogStart(__FUNCTION__);
	std::cout << std::boolalpha;

	// 1. Test empty table
	std::cout << "(1) Test move construct table2 from empty table1...\n";
	ChainedHashTable<std::string, int> table1;
	std::cout << "table1 is empty:            " << table1.isEmpty() << '\n';
	std::cout << "table1 size:                " << table1.size() << '\n';

	std::cout << "\nMove construct new table from table1...\n";
	ChainedHashTable<std::string, int> table2(std::move(table1));

	std::cout << "\nAfter move construction...\n";
	std::cout << "table1 is empty:            " << table1.isEmpty() << '\n';
	std::cout << "table1 size:                " << table1.size() << '\n';
	std::cout << "table2 is empty:            " << table2.isEmpty() << '\n';
	std::cout << "table2 size:                " << table2.size() << '\n';
	print_separator();

	/*********************************************************************************/

	// 2. Test populated table
	std::cout << "\n\n(2) Test move construct from populated table...\n";
	ChainedHashTable<std::string, int> table3(20);

	// Add elements
	std::string names[] = { "Al Swearengen", "Cy Tolliver", "Dan Dority",
							"Johnny Burns", "Jimmy Irons", "Doc Cochran" };
	int ages[] = { 62, 62, 39, 34, 38, 50 };

	for (int i = 0; i < std::size(names); ++i)
		table3.insert(names[i], ages[i]);

	// Table 3
	std::cout << "Contents of table3:\n";
	table3.print();
	std::cout << "table3 is empty:            " << table3.isEmpty() << '\n';
	std::cout << "table3 size:                " << table3.size() << '\n';

	std::cout << "\nMove construct table4 from table1...\n";
	ChainedHashTable<std::string, int> table4(std::move(table3));

	std::cout << "\nAfter move construction...\n";
	std::cout << "\nContents of table3:\n";
	table3.print();
	std::cout << "table3 is empty:            " << table3.isEmpty() << '\n';
	std::cout << "table3 size:                " << table3.size() << '\n';

	std::cout << "\nContents of table4:\n";
	table4.print();
	std::cout << "table4 is empty:            " << table4.isEmpty() << '\n';
	std::cout << "table4 size:                " << table4.size() << '\n';

	printLogEnd(__FUNCTION__);
}


void testCopyAssignmentOperator() {
	printLogStart(__FUNCTION__);
	std::cout << std::boolalpha;

	// 1. Test copy assign empty to empty
	std::cout << "(1) Copy assign from an empty table into an empty table...\n";
	ChainedHashTable<std::string, int> table1;
	ChainedHashTable<std::string, int> table2;

	std::cout << "\nBefore copy assign...\n";
	std::cout << "table1 is empty:            " << table1.isEmpty() << '\n';
	std::cout << "table1 size:                " << table1.size() << '\n';	
	std::cout << "table1 is empty:            " << table1.isEmpty() << '\n';
	std::cout << "table1 size:                " << table1.size() << '\n';

	std::cout << "\nCopy assign table2 into table1...\n";
	table1 = table2;
	std::cout << "\nAfter copy assign...\n";
	std::cout << "table1 is empty:            " << table1.isEmpty() << '\n';
	std::cout << "table1 size:                " << table1.size() << '\n';
	std::cout << "table2 is empty:            " << table2.isEmpty() << '\n';
	std::cout << "table2 size:                " << table2.size() << '\n';
	print_separator();

	/*****************************************************************************/

	// 2. Test copy assign empty to populated
	std::cout << "\n\n(2) Copy assign from an empty table into an populated table...\n";

	ChainedHashTable<std::string, int> table3;

	// Add elements
	std::string names[] = { "Al Swearengen", "Cy Tolliver", "Dan Dority",
							"Johnny Burns", "Jimmy Irons", "Doc Cochran" };
	int ages[] = { 62, 62, 39, 34, 38, 50 };

	for (int i = 0; i < std::size(names); ++i)
		table1.insert(names[i], ages[i]);

	std::cout << "\nBefore copy assign...\n";
	std::cout << "\nContents of table1:\n";
	table1.print();
	std::cout << "table1 is empty:            " << table1.isEmpty() << '\n';
	std::cout << "table1 size:                " << table1.size() << '\n';
	
	std::cout << "\nCopy assign empty table3 into populated tree1...\n";
	table1 = table3;
	std::cout << "\nAfter copy assign...\n";

	// table1 should now be empty
	std::cout << "Contents of tree1:\n";
	table1.print();
	std::cout << "table1 is empty:            " << table1.isEmpty() << '\n';
	std::cout << "table1 size:                " << table1.size() << '\n';

	// table3 should still be empty
	std::cout << "Contents of tree3:\n";
	table3.print();
	std::cout << "table3 is empty:            " << table3.isEmpty() << '\n';
	std::cout << "table3 size:                " << table3.size() << '\n';
	print_separator();

	/*****************************************************************************/

	// 3. Test copy assign populated into empty
	std::cout << "\n\n(3) Copy assign from a populated tree into an empty tree...\n";

	// Repopulate table1
	for (int i = 0; i < std::size(names); ++i)
		table1.insert(names[i], ages[i]);

	std::cout << "\nBefore copy assign...\n";
	
	// Should now be populated
	std::cout << "Contents of table1:\n";
	table1.print();
	std::cout << "table3 is empty:            " << table3.isEmpty() << '\n';
	std::cout << "table3 size:                " << table3.size() << '\n';

	// Should (still) be empty
	std::cout << "Contents of table2:\n";
	table2.print();
	std::cout << "table2 is empty:            " << table2.isEmpty() << '\n';
	std::cout << "table2 size:                " << table2.size() << '\n';

	std::cout << "\nCopy assign populated table1 into empty table2..\n";
	table2 = table1;
	std::cout << "\nAfter copy assign...\n";

	// Contents should be unchanged
	std::cout << "Contents of table1:\n";
	table1.print();
	std::cout << "table1 is empty:            " << table1.isEmpty() << '\n';
	std::cout << "table1 size:                " << table1.size() << '\n';

	// Should now have same contents as table1
	std::cout << "\nContents of table2:\n";
	table2.print();
	std::cout << "table2 is empty:            " << table2.isEmpty() << '\n';
	std::cout << "table2 size:                " << table2.size() << '\n';
	print_separator();

	/*****************************************************************************/

	// 4. Test copy assign populated into populated
	std::cout << "\n\n(4) Copy assign from a populated table into another populated table...\n";

	// Create a new tree with some different contents
	ChainedHashTable <std::string, int> table4;

	// Populate table4
	table4.insert("Fred Flintstone", 40);
	table4.insert("Barney Rubble", 40);
	table4.insert("Wilma Flintstone", 40);
	table4.insert("Betty Rubble", 40);

	std::cout << "\nBefore copy assign...\n";
	std::cout << "Contents of table4:\n";
	table4.print();
	std::cout << "table4 is empty:            " << table4.isEmpty() << '\n';
	std::cout << "table4 size:                " << table4.size() << '\n';

	// tree1 still empty
	std::cout << "\nCopy assign populated table4 into table3 (has different contents)...\n";
	table3 = table4;
	std::cout << "\nAfter copy assign...\n";

	// Should now mirror contents of table3
	std::cout << "Contents of table3:\n";
	table3.print();
	std::cout << "table3 is empty:            " << table3.isEmpty() << '\n';
	std::cout << "table3 size:                " << table3.size() << '\n';
	
	// Should be unchanged
	std::cout << "Contents of table4:\n";
	table4.print();
	std::cout << "table4 is empty:            " << table4.isEmpty() << '\n';
	std::cout << "table4 size:                " << table4.size() << '\n';

	printLogEnd(__FUNCTION__);
}


void testMoveAssignmentOperator() {
	printLogStart(__FUNCTION__);
	std::cout << std::boolalpha;

	// 1. Test copy assign empty to empty
	std::cout << "(1) Move assign from an empty table into an empty table...\n";
	ChainedHashTable<std::string, int> table1;
	ChainedHashTable<std::string, int> table2;

	std::cout << "\nBefore move assign...\n";
	std::cout << "table1 is empty:            " << table1.isEmpty() << '\n';
	std::cout << "table1 size:                " << table1.size() << '\n';
	std::cout << "table2 is empty:            " << table2.isEmpty() << '\n';
	std::cout << "table2 size:                " << table2.size() << '\n';

	std::cout << "\nMove assign table2 into table1...\n";
	table1 = std::move(table2);
	std::cout << "\nAfter move assign...\n";
	std::cout << "table1 is empty:            " << table1.isEmpty() << '\n';
	std::cout << "table1 size:                " << table1.size() << '\n';
	std::cout << "table2 is empty:            " << table2.isEmpty() << '\n';
	std::cout << "table2 size:                " << table2.size() << '\n';
	print_separator();

	/*****************************************************************************/

	// 2. Test move assign empty to populated
	std::cout << "\n\n(2) Move assign from an empty table into an populated table...\n";

	ChainedHashTable<std::string, int> table3;

	// Add elements
	std::string names[] = { "Al Swearengen", "Cy Tolliver", "Dan Dority",
							"Johnny Burns", "Jimmy Irons", "Doc Cochran" };
	int ages[] = { 62, 62, 39, 34, 38, 50 };

	for (int i = 0; i < std::size(names); ++i)
		table1.insert(names[i], ages[i]);

	std::cout << "\nBefore move assign...\n";
	std::cout << "\nContents of table1:\n";
	table1.print();
	std::cout << "table1 is empty:            " << table1.isEmpty() << '\n';
	std::cout << "table1 size:                " << table1.size() << '\n';

	std::cout << "\nMove assign empty table3 into populated tree1...\n";
	table1 = std::move(table3);
	std::cout << "\nAfter move assign...\n";

	// table1 should now be empty
	std::cout << "Contents of tree1:\n";
	table1.print();
	std::cout << "table1 is empty:            " << table1.isEmpty() << '\n';
	std::cout << "table1 size:                " << table1.size() << '\n';

	// table3 should still be empty
	std::cout << "Contents of tree3:\n";
	table3.print();
	std::cout << "table3 is empty:            " << table3.isEmpty() << '\n';
	std::cout << "table3 size:                " << table3.size() << '\n';
	print_separator();

	/*****************************************************************************/

	// 3. Test move assign populated into empty
	std::cout << "\n\n(3) Move assign from a populated tree into an empty tree...\n";

	// Repopulate table1
	for (int i = 0; i < std::size(names); ++i)
		table1.insert(names[i], ages[i]);

	std::cout << "\nBefore move assign...\n";

	// Should now be populated
	std::cout << "Contents of table1:\n";
	table1.print();
	std::cout << "table3 is empty:            " << table3.isEmpty() << '\n';
	std::cout << "table3 size:                " << table3.size() << '\n';

	// Should (still) be empty
	std::cout << "Contents of table2:\n";
	table2.print();
	std::cout << "table2 is empty:            " << table2.isEmpty() << '\n';
	std::cout << "table2 size:                " << table2.size() << '\n';

	std::cout << "\nMove assign populated table1 into empty table2..\n";
	table2 = std::move(table1);
	std::cout << "\nAfter move assign...\n";

	// Contents should be unchanged
	std::cout << "Contents of table1:\n";
	table1.print();
	std::cout << "table1 is empty:            " << table1.isEmpty() << '\n';
	std::cout << "table1 size:                " << table1.size() << '\n';

	// Should now have same contents as table1
	std::cout << "\nContents of table2:\n";
	table2.print();
	std::cout << "table2 is empty:            " << table2.isEmpty() << '\n';
	std::cout << "table2 size:                " << table2.size() << '\n';
	print_separator();

	/*****************************************************************************/

	// 4. Test move assign populated into populated
	std::cout << "\n\n(4) Move assign from a populated table into another populated table...\n";

	// Create a new tree with some different contents
	ChainedHashTable <std::string, int> table4;

	// Populate table4
	table4.insert("Fred Flintstone", 40);
	table4.insert("Barney Rubble", 40);
	table4.insert("Wilma Flintstone", 40);
	table4.insert("Betty Rubble", 40);

	std::cout << "\nBefore copy assign...\n";
	std::cout << "Contents of table4:\n";
	table4.print();
	std::cout << "table4 is empty:            " << table4.isEmpty() << '\n';
	std::cout << "table4 size:                " << table4.size() << '\n';

	// tree1 still empty
	std::cout << "\nCopy assign populated table4 into table3 (has different contents)...\n";
	table3 = std::move(table4);
	std::cout << "\nAfter copy assign...\n";

	// Should now mirror contents of table3
	std::cout << "Contents of table3:\n";
	table3.print();
	std::cout << "table3 is empty:            " << table3.isEmpty() << '\n';
	std::cout << "table3 size:                " << table3.size() << '\n';

	// Should be unchanged
	std::cout << "Contents of table4:\n";
	table4.print();
	std::cout << "table4 is empty:            " << table4.isEmpty() << '\n';
	std::cout << "table4 size:                " << table4.size() << '\n';

	printLogEnd(__FUNCTION__);
}




void testSingleEntryHashTable() {
	printLogStart(__FUNCTION__);

	ChainedHashTable<std::string, int> table;
	std::cout << std::boolalpha;
	std::cout << "\nBefore inserting a key-value pair:\n\n";
	std::cout << "table default capacity:    " << ChainedHashTable<std::string, int>::DEFAULT_CAPACITY << '\n';
	std::cout << "table default load factor: " << ChainedHashTable<std::string, int>::DEFAULT_LOAD_FACTOR << '\n';
	std::cout << "table is empty:            " << table.isEmpty() << '\n';
	std::cout << "table size:                " << table.size() << '\n';

	std::cout << "\nAfter inserting a key-value pair:\n\n";
	int inserted = table.insert("Al Swearengen", 55);
	std::cout << "Value inserted:            " << inserted << '\n';
	std::cout << "table is empty:            " << table.isEmpty() << '\n';
	std::cout << "table size:                " << table.size() << '\n';

	// Insert with an key that already exists in the table.
	// Will just update the value for that key.
	std::cout << "\nInserting a key-value pair using the same key:\n\n";
	inserted = table.insert("Al Swearengen", 62);
	std::cout << "Value inserted:            " << inserted << '\n';
	std::cout << "table is empty:            " << table.isEmpty() << '\n';
	std::cout << "table size:                " << table.size() << '\n';

	print_separator();

	/***********************************************************************************/

	std::cout << "\nAfter clear:\n\n";
	table.clear();
	std::cout << "table default capacity:    " << ChainedHashTable<std::string, int>::DEFAULT_CAPACITY << '\n';
	std::cout << "table default load factor: " << ChainedHashTable<std::string, int>::DEFAULT_LOAD_FACTOR << '\n';
	std::cout << "table is empty:            " << table.isEmpty() << '\n';
	std::cout << "table size:                " << table.size() << '\n';

	printLogEnd(__FUNCTION__);
}


void testMultipleEntryHashTable() {
	printLogStart(__FUNCTION__);

	ChainedHashTable<std::string, int> table(10);
	std::cout << std::boolalpha;
	std::cout << "\nBefore inserting a key-value pair:\n";
	std::cout << "table default capacity:    " << ChainedHashTable<std::string, int>::DEFAULT_CAPACITY << '\n';
	std::cout << "table default load factor: " << ChainedHashTable<std::string, int>::DEFAULT_LOAD_FACTOR << '\n';
	std::cout << "table is empty:            " << table.isEmpty() << '\n';
	std::cout << "table size:                " << table.size() << '\n';

	std::string names[] = { "Al Swearengen", "Cy Tolliver", "Dan Dority",
							"Johnny Burns", "Jimmy Irons", "Doc Cochran"};
	int ages[] = { 62, 62, 39, 34, 38 };
	int inserted{};


	for (int i = 0; i < 5; i++) {
		std::cout << "\nAfter inserting a key-value pair: " << i + 1 << '\n';
		inserted = table.insert(names[i], ages[i]);
		std::cout << "Value inserted:            " << inserted << '\n';
		std::cout << "table size:                " << table.size() << '\n';
		std::cout << "table contains key " << names[i] << ": " <<
			table.containsKey(names[i]) << '\n';
		std::cout << "table has key " << names[i] << ": " <<
			table.hasKey(names[i]) << '\n';
	}

	std::cout << "\nAfter initial inserts...\n";
	table.print();
	print_separator();

	/*************************************************************************/

	std::cout << "\nInserting a key-value pair using the same key and same value:\n";
	inserted = table.insert("Al Swearengen", 62);
	std::cout << "Value inserted:            " << inserted << '\n';
	std::cout << "table is empty:            " << table.isEmpty() << '\n';
	std::cout << "table size:                " << table.size() << '\n';

	table.print();
	print_separator();

	/***********************************************************************************/


	std::cout << "\nInserting a key-value pair using the same key but different value:\n";
	inserted = table.insert("Al Swearengen", 150);
	std::cout << "Value inserted:            " << inserted << '\n';
	std::cout << "table is empty:            " << table.isEmpty() << '\n';
	std::cout << "table size:                " << table.size() << '\n';

	table.print();
	print_separator();

	/*************************************************************************/

	std::cout << "\nAfter clear:\n";
	table.clear();
	std::cout << "table is empty:            " << table.isEmpty() << '\n';
	std::cout << "table size:                " << table.size() << '\n';

	table.print();

	printLogEnd(__FUNCTION__);
}


void testGetValueFromTable() {
	printLogStart(__FUNCTION__);

	ChainedHashTable<std::string, int> table(10);
	std::cout << std::boolalpha;

	std::string names[] = { "Al Swearengen", "Cy Tolliver", "Dan Dority",
							"Johnny Burns", "Jimmy Irons", "" };
	std::string names2[] = { "Doc Cochran", "Sol Starr", "Seth Bullock", "Trixie" };
	int ages[] = { 62, 59, 39, 34, 38 };

	for (int i = 0; i < 5; i++)
		table.insert(names[i], ages[i]);

	std::cout << "\nAfter inserting key-value pairs:\n";
	std::cout << "table default capacity:    " << ChainedHashTable<std::string, int>::DEFAULT_CAPACITY << '\n';
	std::cout << "table default load factor: " << ChainedHashTable<std::string, int>::DEFAULT_LOAD_FACTOR << '\n';
	std::cout << "table is empty:            " << table.isEmpty() << '\n';
	std::cout << "table size:                " << table.size() << '\n';

	std::optional<int> htValue;

	std::cout << "\n\nSearching on keys in the hashtable...\n";
	for (int i = 0; i < 6; i++) {
		htValue = table.get(names[i]);

		if (htValue.has_value())
			std::cout << names[i] << " has value " << htValue.value() << '\n';
		else
			std::cout << names[i] << " not found in hash table\n";
	}

	// Now search for a few dummy names
	std::cout << "\n\nSearching on keys not in the hashtable...\n";
	for (int i = 0; i < 4; i++) {
		htValue = table.get(names2[i]);

		if (htValue.has_value())
			std::cout << names2[i] << " has value " << htValue.value() << '\n';
		else
			std::cout << names2[i] << " not found in hash table\n";
	}
	printLogEnd(__FUNCTION__);
}


void testRemoveValueFromTable() {
	printLogStart(__FUNCTION__);
	ChainedHashTable<std::string, int> table(10);
	std::cout << std::boolalpha;

	std::string names[] = { "Al Swearengen", "Cy Tolliver", "Dan Dority",
							"Johnny Burns", "Jimmy Irons", "" };
	std::string names2[] = { "Doc Cochran", "Sol Starr", "Seth Bullock", "Trixie" };
	int ages[] = { 62, 59, 39, 34, 38 };
	int ages2[] = { 54, 45, 37, 34 };

	for (int i = 0; i < 4; i++)
		table.insert(names2[i], ages2[i]);

	std::cout << "\nAfter inserting key-value pairs:\n";
	std::cout << "table default capacity:    " << ChainedHashTable<std::string, int>::DEFAULT_CAPACITY << '\n';
	std::cout << "table default load factor: " << ChainedHashTable<std::string, int>::DEFAULT_LOAD_FACTOR << '\n';
	std::cout << "table is empty:            " << table.isEmpty() << '\n';
	std::cout << "table size:                " << table.size() << '\n';

	std::optional<int> htValue;

	std::cout << "\n\nCurrent contents of the hash table...\n\n";
	std::cout << "Name";
	printSpaces(16);
	std::cout << "Age" << '\n';
	std::cout << "----";
	printSpaces(16);
	std::cout << "---\n\n";

	for (int i = 0; i < std::size(names2); i++) {
		std::cout << names2[i];
		printSpaces(20 - names2[i].length());
		htValue = table.get(names2[i]);

		if (htValue.has_value())
			std::cout << htValue.value() << '\n';
		else
			std::cout << "No age found!\n";
	}

	std::string name = "Tony Soprano";
	std::cout << name;
	printSpaces(20 - name.length());
	htValue = table.get(name);
	if (htValue.has_value())
		std::cout << htValue.value() << '\n';
	else
		std::cout << "No age found!\n";
	print_separator();

	/****************************************************************/

	// Test removal of data
	std::cout << "\nNow let's remove existing entries...\n";
	std::optional<int> removed;

	for (int i = 0; i < std::size(names2); i++) {
		std::cout << "\n\nRemove " << names2[i] << ":\n";

		removed = table.remove(names2[i]);

		if (removed.has_value())
			std::cout << removed.value() << " removed from hash table...\n";
		else
			std::cout << "Cannot remove entry not in table!\n";
		std::cout << "table is empty:            " << table.isEmpty() << '\n';
		std::cout << "table size:                " << table.size() << '\n';
	}
	print_separator();

	/****************************************************************/

	std::cout << "\nAttempt to remove non-existing entries...\n";

	for (int i = 0; i < std::size(names); i++) {
		std::cout << "\n\nRemove " << names[i] << ":\n";

		removed = table.remove(names[i]);

		if (removed.has_value())
			std::cout << removed.value() << " removed from hash table...\n";
		else
			std::cout << "Cannot remove entry not in table!\n";
		std::cout << "table is empty:            " << table.isEmpty() << '\n';
		std::cout << "table size:                " << table.size() << '\n';
	}
	print_separator();

	/****************************************************************/

	std::cout << "\nAfter removing key-value pairs:\n";
	std::cout << "table default capacity:    " << ChainedHashTable<std::string, int>::DEFAULT_CAPACITY << '\n';
	std::cout << "table default load factor: " << ChainedHashTable<std::string, int>::DEFAULT_LOAD_FACTOR << '\n';
	std::cout << "table is empty:            " << table.isEmpty() << '\n';
	std::cout << "table size:                " << table.size() << '\n';

	printLogEnd(__FUNCTION__);
}



void testResizeTable() {
	printLogStart(__FUNCTION__);

	ChainedHashTable<std::string, int> table(2);
	std::cout << std::boolalpha;

	std::cout << "Create a table with an initial capacity of 2...\n";
	std::cout << "table is empty:            " << table.isEmpty() << '\n';
	std::cout << "table size:                " << table.size() << '\n';

	// Create keys and values to insert...
	std::string names[] = { "Al Swearengen", "Cy Tolliver", "Dan Dority",
							"Johnny Burns", "Jimmy Irons", "Doc Cochran",
							"Sol Starr", "Seth Bullock", "Trixie",
							"Leon", "Mr Wu", "Joanie Stubbs",
							"Eddie Sawyer", "Andy Cramed", "Charlie Utter",
							"EB Farnum", "Wild Bill Hickock", "Silas Adams" };
	int ages[] = { 62, 59, 39, 34, 38, 54, 45, 37, 34,
					39, 51, 38, 52, 46, 50, 55, 53, 40 };

	for (int i = 0; i < std::size(names); i++)
		table.insert(names[i], ages[i]);

	std::cout << "\nAfter inserting key-value pairs:\n";
	std::cout << "table default capacity:    " << ChainedHashTable<std::string, int>::DEFAULT_CAPACITY << '\n';
	std::cout << "table default load factor: " << ChainedHashTable<std::string, int>::DEFAULT_LOAD_FACTOR << '\n';
	std::cout << "table is empty:            " << table.isEmpty() << '\n';
	std::cout << "table size:                " << table.size() << '\n';

	std::optional<int> htValue;

	std::cout << "\n\nCurrent contents of the hashtable...\n\n";
	std::cout << "Name";
	printSpaces(16);
	std::cout << "Age" << '\n';
	std::cout << "----";
	printSpaces(16);
	std::cout << "---\n\n";

	for (int i = 0; i < std::size(names); i++) {
		std::cout << names[i];
		printSpaces(20 - names[i].length());
		htValue = table.get(names[i]);

		if (htValue.has_value())
			std::cout << htValue.value() << '\n';
		else
			std::cout << "No age found!\n";
	}
	print_separator();

	/**************************************************************************/

	// Try reinserting the same values
	std::cout << "\nInsert duplicate values...\n";

	for (int i = 0; i < std::size(names); i++)
		table.insert(names[i], ages[i]);

	std::cout << "\nAfter inserting key-value pairs:\n";
	std::cout << "table default capacity:    " << ChainedHashTable<std::string, int>::DEFAULT_CAPACITY << '\n';
	std::cout << "table default load factor: " << ChainedHashTable<std::string, int>::DEFAULT_LOAD_FACTOR << '\n';
	std::cout << "table is empty:            " << table.isEmpty() << '\n';
	std::cout << "table size:                " << table.size() << '\n';

	std::cout << "\n\nCurrent contents of the hashtable...\n\n";
	std::cout << "Name";
	printSpaces(16);
	std::cout << "Age" << '\n';
	std::cout << "----";
	printSpaces(16);
	std::cout << "---\n\n";

	for (int i = 0; i < std::size(names); i++) {
		std::cout << names[i];
		printSpaces(20 - names[i].length());
		htValue = table.get(names[i]);

		if (htValue.has_value())
			std::cout << htValue.value() << '\n';
		else
			std::cout << "No age found!\n";
	}
	print_separator();

	/**************************************************************************/

	// Try changing the same values
	std::cout << "\nUpdating the values...\n";

	for (int i = 0; i < std::size(names); i++)
		table.insert(names[i], i);


	std::cout << "\n\nCurrent contents of the hashtable...\n\n";
	std::cout << "Name";
	printSpaces(16);
	std::cout << "Age" << '\n';
	std::cout << "----";
	printSpaces(16);
	std::cout << "---\n\n";

	for (int i = 0; i < std::size(names); i++) {
		std::cout << names[i];
		printSpaces(20 - names[i].length());
		htValue = table.get(names[i]);

		if (htValue.has_value())
			std::cout << htValue.value() << '\n';
		else
			std::cout << "No age found!\n";
	}

	printLogEnd(__FUNCTION__);
}


void testPrintHashTableContents() {
	printLogStart(__FUNCTION__);

	ChainedHashTable<std::string, int> table(10);
	std::cout << std::boolalpha;

	// Do a lot of inserts to really push the table capacity
	std::cout << "Clear the table...\n";
	table.clear();
	std::cout << "table is empty:            " << table.isEmpty() << '\n';
	std::cout << "table size:                " << table.size() << '\n';

	// Create a large table
	for (int i = 1; i <= 1000; i++) {
		table.insert(std::string{ "Billy" }.append(std::to_string(i)), i);
	}

	std::cout << "\nAfter inserting key-value pairs:\n";
	std::cout << "table is empty:            " << table.isEmpty() << '\n';
	std::cout << "table size:                " << table.size() << "\n\n\n";

	// Print the entire contents of the hashtable
	table.print();
	print_separator();

	/**************************************************************************/

	// Now clear contents
	table.clear();
	std::cout << "\nContents of table after clear...\n";
	table.print();
	std::cout << "table is empty:            " << table.isEmpty() << '\n';
	std::cout << "table size:                " << table.size() << '\n';

	printLogEnd(__FUNCTION__);
}
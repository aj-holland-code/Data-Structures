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
// implemented here, which is an open addressing solution.
//
// 
// Open Addressing Basics
// ----------------------
// 
// The goal of a Hash Table (HT) is to construct a mapping from keys to values. 
// Keys must be hashable, so we need a hash function that converts keys to whole
// numbers.
// 
// We use the hash function defined on our key set to index into an array (the HT).
// 
// Hash functions are not perfect, therefore sometimes two keys, k1 and k2, hash
// to the same value. When this happens, we have a hash collision
// i.e. H(k1) = H(k2).
// 
// Open addressing is another method of resolving this issue.
// 
// When using open addressing as a collision resolution technique, the key-value
// pairs are stored in the table (array) itself, as opposed to in a separate data
// structure (as used in separate chaining). 
// 
// This means we need to be careful about the size of the hash table and how many 
// elements are currently in the table... because we may regularly have collisions 
// and need to find other slots to place data when collisions occur. If there are 
// few other slots, it will be very difficult to successfully place the data!
// 
// Therefore, with an open addressing collision solution, in order to maintain 
// satisfactory performance, there is a particular onus on monitoring if the table's
// threshold has been exceeded; what this means is, establishing whether the number of 
// buckets currently in use in the table exceeds the pre-determined point at which
// the table has used up as many buckets as it reasonably can at its current
// size and a resizing is required to create further capacity.
// 
// Load factor =  items in table
//	              --------------
//                size of table
// 
// The O(1) constant time behaviour attributed to hash tables assumes the load 
// factor (ɑ) is kept below a certain fixed value. 
// This means once ɑ exceeds the threshold, we need to increase the table size 
// (ideally exponentially, i.e. double).
// 
// 
// The key idea of open addressing
// -------------------------------
// 
// When inserting a key-value pair (k, v) into the hash table, we hash the key and
// obtain an original position for where this key-value pair belongs, i.e. H(k).
// 
// If the position the key hashes to is occupied, we try another position in the 
// hash table by offsetting the current position subject to a probing sequence P(x).
// We keep doing this until an unoccupied slot is found.
//
//
// General insertion method for open addressing
// --------------------------------------------
// 
// On a table of size N, this the insertion goes as follows:
// 
//		x := 1
//		keyHash := H(k)
//		index := keyHash
// 
//		while table[index] != null:
//			index = (keyHash + P(k, x)) mod N
//			x = x + 1
// 
//		insert (k, v) at table[index]
// 
// Where H(k) is the hash for the key k and P(k, x) is the probing function
// 
// We move along one position at a time, until we find an open slot in the table, 
// we can then insert the key-value pair into that position.
//
//
// Chaos with cycles
// -----------------
// 
// In most randomly selected probing sequences, modulo N will produce a cycle
// shorter than the table size. This becomes problematic when you are trying to
// insert a key-value pair and all the buckets on the cycle are occupied 
// because you will get stuck in an infinite loop!
// 
// The general consensus on the solution to this issue is to avoid it by 
// restricting the domain of probing functions to those that produce a cycle
// of exactly length N (there are a few exceptions with special properties that
// can produce shorter cycles).
//
// Techniques such as linear probing, quadratic probing, and double hashing are
// all subject to the issue of causing cycles, which is why these methods are
// very specific. 
// 
// Note that open addressing is very sensitive to the hashing function and probing
// functions used. This is less of a concern (although still an issue) if the
// collision resolution method used is separate chaining.
//
//
// Linear Probing
// --------------
// 
// Linear Probing (LP) is a probing method that probes according to a linear 
// formula, specifically:
// 
// P(x) = ax + b where a(!null), b are constants
// (Note: constant b is obsolete...)
// 
// However, not all linear functions are viable because they are unable to 
// produce a cycle of order N. This issue needs to be addressed.
// 
// The question is, what value(s) of the constant a in P(x) = ax produce(s)
// a full cycle modulo N?
// 
// The answer is when a and N are relatively prime. 
// Two numbers are relatively prime if their Greatest Common Denominator (GCD) is
// equal to one.
// Hence, when GCD(a, N) = 1, the probing function P(x) will be able to generate
// a complete cycle and we will always be able to find an empty bucket!
//
//
// Quadratic Probing (QP)
// ----------------------
// 
// QP is a probing method that probes according to a quadratic formula, 
// specifically:
// 
// P(x) = ax squared + bx + c
// where
// a, b, c are constants and a ≠ 0 (otherwise we degrade to linear probing).
// 
// However, not all quadratic functions are viable, since some are unable to 
// produce a cycle of order N. 
// 
// There are numerous ways to approach this problem. Three popular ones are:
// 1) Let P(x) = x squared; keep the table size a prime number > 3; and also 
// keep α ≤ ½ (i.e. keep load factor less than half).
// 2) Let P(x) = (x squared + x) / 2 and keep the table size a power of two.
// 3) Let P(x) = (-1x) * x squared and keep the table size a prime N 
// where N ≡ 3 mod 4.
//
//
// Double Hashing (DH)
// -------------------
// 
// DH is a probing method that probes according to a constant multiple of
// another hash function, specifically:
// 
// P(k,x) = x*H2(k)
// where H2(k) is a second hash function
// 
// H2(k) must hash the same type of keys as H1(k).
// N.B. Double hashing reduces to linear probing (except that the constant is
// unknown until runtime).
// 
// Since DP reduces to linear probing at runtime, we may end up with a linear 
// probing function such as:
// P(x) = 3x, H1(k) = 4, and a table size of 9 (N = 9), in which case we end up 
// with a 4-7-1 cycle occurring...
// 
// To fix the issue of cycles, the table size is set to be a prime number, and
// the value of of ƍ (Delta):
// 
// ƍ = H2(k) mod N
// If ƍ = 0, we are guaranteed to be stuck in a cycle, so when this happens, set
// ƍ = 1.
// 
// Notice that 1 ≤ ƍ < N and GCD(ƍ, N) = 1 since N is prime. Hence, with these
// conditions we know that modulo N the sequence:
// H1(k), H1(k) + 1ƍ, H1(k) + 2ƍ, H1(k) + 3ƍ, H1(k) + 4ƍ...
// is certain to have order N -- meaning we can hit every slot in the hash table.
// 
// Whenever we want to use double hashing, we need to create a new function H2(k)
// that knows how to hash keys of type T. There are many well known high quality 
// hash functions for these fundamental data types. Hence, we can use and combine
// them to construct our function H2(k). They are frequently selected from a pool
// called universal hash functions, which generally operate on one fundamental
// data type.
//
// 
// Issues with Removing
// --------------------
// 
// If we naively remove, that is we simply set a removed element slot to null, we may
// run into problems when searching for another element in a later transaction.
// If during probing for the element being searched it hits that null slot before
// finding the element itself, the search will assume that the element has not been 
// found and report failure, when in fact the element is at a slot further on in the 
// table!
// 
// Tombstones
// ----------
// 
// To avoid this issue, we can use tombstone values in the table. This marks a slot
// as not currently in use but having been used before, thus allowing the search to 
// continue.
// 
// Tombstones can end up cluttering up the table, so we can remove them all when we 
// next resize the table. However, we can also reduce their negative impact in a 
// relatively low cost operation, by the technique of lazy deletion or lazy relocation.
// 
// Lazy deletion means that when we next search for an element that hashes initially to a
// slot with a tombstone, we can note that tombstone position, and after probing to 
// find the element in its current position, we can shift the element to the position
// of the first tombstone encountered and overwrite its current position with a null value.
// 
// This removes the tombstone from the table and means that the element if searched for 
// again will be found at that first position it hashes to, removing the need 
// to do further probing to find it.

#include <bit>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>
#include "Hash_Table_Quadratic_Probing.h"

// Main test functions
void testPowerOf2();
void testQuadraticProbing();
void testEmptyHTQP();
void testCopyConstructor();
void testMoveConstructor();
void testCopyAssignmentOperator();
void testMoveAssignmentOperator();

void testGetFunctionEmptyTable();
void testOneEntryHTQP();
void testMultiEntryHTQP();
void testTableResizing();
void testDuplicateKeys();

// Utility functions declarations
void print_separator();
void printLogStart(const char* s);
void printLogEnd(const char* s);
void printSpaces(int noSpaces);
void printUnderscores(int noUnderscores);

int main() {
	// Test functions for quadratic probing open address hash table 
	testPowerOf2();
	testQuadraticProbing();
	//testEmptyHTQP();			// Careful! Creates large tables so takes a long time to run
	testCopyConstructor();
	testMoveConstructor();
	testCopyAssignmentOperator();
	testMoveAssignmentOperator();

	testGetFunctionEmptyTable();
	testOneEntryHTQP();
	testMultiEntryHTQP();
	testTableResizing();
	testDuplicateKeys();
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

// Utility Function Tests
// ----------------------

// Special test function to test (in isolation) the power of 2 calculations
// needed in the quadratic probing HT solution.
// It's in a private method so I want to explicitly test it here.
void testPowerOf2() {
	printLogStart(__FUNCTION__);

	for (unsigned int num = 0; num < 51; num++) {
		std::cout << '\n';
		std::cout << "num:            " << num << '\n';
		std::cout << "bit_floor(num): " << std::bit_floor(num) << '\n';
		std::cout << "bit_ceil(num):  " << std::bit_ceil(num) << '\n';
	}

	std::cout << "\n\nTest 100k:\n";
	unsigned int num = 100'000;
	std::cout << '\n';
	std::cout << "num:            " << num << '\n';
	std::cout << "bit_floor(num): " << std::bit_floor(num) << '\n';
	std::cout << "bit_ceil(num):  " << std::bit_ceil(num) << '\n';

	printLogEnd(__FUNCTION__);
}


// Special test function to test (in isolation) the quadratic probing 
// code in the HT solution.
// It's in a private method so I want to explicitly test it here.
void testQuadraticProbing() {
	printLogStart(__FUNCTION__);

	for (int value = 0; value < 101; value++) {
		int squarePlusValue = value * value + value;
		int divByTwoValue = squarePlusValue >> 1;
		std::cout << "\n";
		std::cout << "value:                    " << value << '\n';
		std::cout << "value squared plus value: " << squarePlusValue << '\n';
		std::cout << "sq value divided by two:  " << divByTwoValue << '\n';
	}

	printLogEnd(__FUNCTION__);
}

/***************************************************************************************/

// Special Member Function Tests
// -----------------------------

void testEmptyHTQP() {
	printLogStart(__FUNCTION__);

	std::cout << "\nCreate hash table to store int-string key-value pairs...\n";
	std::cout << std::boolalpha;

	// 1. Create a HT without supplying a capacity or load factor
	std::cout << "\n\n(1) table1 - construct without a capacity or load factor...\n";
	HTQuadraticProbing<int, std::string> table1;
	std::cout << "table1 size:  " << table1.size() << '\n';
	std::cout << "table1 empty: " << table1.isEmpty() << '\n';
	std::cout << "\nCurrent contents of table1:\n\n";
	table1.printTable();
	print_separator();

	/*******************************************************************/

	// 2. Create a HT with a capacity but no load factor
	std::cout << "\n\n(2) table2 - construct with a capacity of 7 but no load factor...\n";
	HTQuadraticProbing<int, std::string> table2(7);
	std::cout << "table2 size:  " << table2.size() << '\n';
	std::cout << "table2 empty: " << table2.isEmpty() << '\n';
	std::cout << "\nCurrent contents of table2:\n\n";
	table2.printTable();
	print_separator();

	/*******************************************************************/


	// 3. Create a HT with a capacity and a load factor
	std::cout << "\n\n(3) table3 - construct with a capacity of 31 and a load factor of 0.85...\n";
	HTQuadraticProbing<int, std::string> table3(31, 0.85);	
	std::cout << "table3 size:  " << table3.size() << '\n';
	std::cout << "table3 empty: " << table3.isEmpty() << '\n';
	std::cout << "\nCurrent contents of table4:\n\n";
	table3.printTable();
	print_separator();

	/*******************************************************************/

	// 4. Create a HT with a capacity and a load factor (too low)
	std::cout << "\n\n(4) table4 - construct with a capacity of 100k and a load factor of 0...\n";
	HTQuadraticProbing<int, std::string> table4(100000, 0);
	
	std::cout << "table4 size:  " << table4.size() << '\n';
	std::cout << "table4 empty: " << table4.isEmpty() << '\n';
	//std::cout << "\nCurrent contents of table4:\n\n";
	//table4.printTable();
	print_separator();

	/*******************************************************************/

	// 5. Create a HT with a capacity and a load factor (too high)
	std::cout << "\n\n(5) table5 - construct with a capacity of 100k and a load factor that's too high...\n";
	constexpr double tooHigh = std::numeric_limits<double>::max();
	std::string bigNum = std::to_string(tooHigh);
	std::cout << "The value used for the load factor will be: " << bigNum << "\n\n\n";
	HTQuadraticProbing<int, std::string> table5(100000, tooHigh);
	
	std::cout << "table5 size:  " << table5.size() << '\n';
	std::cout << "table5 empty: " << table5.isEmpty() << '\n';
	//std::cout << "\nCurrent contents of table5:\n\n";
	//table5.printTable();
	print_separator();

	/*******************************************************************/

	// Test clear
	std::string tableNames[5] = { "table1", "table2", "table3", "table4", "table5" };
	std::optional<std::string> s1;

	for (int i = 0; i < 5; i++) {
		std::cout << "Test running clear function on " << tableNames[i];

		switch (i) {
		case 0:
			table1.clear();
			std::cout << "\nCurrent contents of table after clear:\n\n";
			table1.printTable();
			break;
		case 1:
			table2.clear();
			std::cout << "\nCurrent contents of table after clear:\n\n";
			table2.printTable();
			print_separator();
			break;
		case 2:
			table3.clear();
			std::cout << "\nCurrent contents of table after clear:\n\n";
			table3.printTable();
			print_separator();
			break;
		case 3:
			table4.clear();
			std::cout << "\nCurrent contents of table after clear:\n\n";
			table4.printTable();
			print_separator();
			break;
		case 4:
			table5.clear();
			std::cout << "\nCurrent contents of table after clear:\n\n";
			table5.printTable();
			print_separator();
			break;
		default:
			std::cout << "ERROR in switch!\n";
		}
	}

	printLogEnd(__FUNCTION__);
}


void testCopyConstructor() {
	printLogStart(__FUNCTION__);
	std::cout << std::boolalpha;

	// 1. Test empty table
	std::cout << "(1) Test copy construct from empty table...\n";
	HTQuadraticProbing<std::string, int> table1;
	std::cout << "\nInitial contents of table1 after construction:\n\n";
	table1.printTable();
	std::cout << "table1 is empty:            " << table1.isEmpty() << '\n';
	std::cout << "table1 size:                " << table1.size() << "\n\n";

	std::cout << "\nCopy construct new table from table1...\n";
	HTQuadraticProbing<std::string, int> table2(table1);

	std::cout << "\nAfter copy construction...\n";
	std::cout << "\nCurrent contents of table1:\n\n";
	table1.printTable();
	std::cout << "table1 is empty:            " << table1.isEmpty() << '\n';
	std::cout << "table1 size:                " << table1.size() << "\n\n";

	std::cout << "\nCurrent contents of table2:\n\n";
	table2.printTable();
	std::cout << "table2 is empty:            " << table2.isEmpty() << '\n';
	std::cout << "table2 size:                " << table2.size() << '\n';
	print_separator();

	/*********************************************************************************/

	// 2. Test populated table
	std::cout << "\n\n(2) Test copy construct from populated table...\n";
	HTQuadraticProbing<std::string, int> table3;

	// Add elements
	std::string names[] = { "Al Swearengen", "Cy Tolliver", "Dan Dority",
							"Johnny Burns", "Jimmy Irons", "Doc Cochran" };
	int ages[] = { 62, 62, 39, 34, 38, 50 };

	for (int i = 0; i < std::size(names); ++i)
		table3.insert(names[i], ages[i]);

	// Table 3
	std::cout << "\n\nInitial contents of table3:\n\n";
	table3.printTable();
	std::cout << "table3 is empty:            " << table3.isEmpty() << '\n';
	std::cout << "table3 size:                " << table3.size() << '\n';

	std::cout << "\n\nCopy construct new table from table3...\n\n";
	HTQuadraticProbing<std::string, int> table4(table3);

	std::cout << "\n\nAfter copy construction...\n\n";
	std::cout << "\n\nContents of table3:\n\n";
	table3.printTable();
	std::cout << "table3 is empty:            " << table3.isEmpty() << '\n';
	std::cout << "table3 size:                " << table3.size() << "\n\n";

	std::cout << "\n\nContents of table4:\n\n";
	table4.printTable();
	std::cout << "table4 is empty:            " << table4.isEmpty() << '\n';
	std::cout << "table4 size:                " << table4.size() << '\n';

	printLogEnd(__FUNCTION__);
}


void testMoveConstructor() {
	printLogStart(__FUNCTION__);
	std::cout << std::boolalpha;

	// 1. Test empty table
	std::cout << "(1) Test move construct from empty table...\n";
	HTQuadraticProbing<std::string, int> table1;
	std::cout << "\n\nInitial contents of table1 after construction:\n\n";
	table1.printTable();
	std::cout << "table1 is empty:            " << table1.isEmpty() << '\n';
	std::cout << "table1 size:                " << table1.size() << '\n';

	std::cout << "\nMove construct new table from table1...\n";
	HTQuadraticProbing<std::string, int> table2(std::move(table1));

	std::cout << "\nAfter move construction...\n";
	std::cout << "\nCurrent contents of table1:\n\n";
	table1.printTable();
	std::cout << "table1 is empty:            " << table1.isEmpty() << '\n';
	std::cout << "table1 size:                " << table1.size() << "\n\n";

	std::cout << "\nCurrent contents of table2:\n\n";
	table2.printTable();
	std::cout << "table2 is empty:            " << table2.isEmpty() << '\n';
	std::cout << "table2 size:                " << table2.size() << '\n';
	print_separator();

	/*********************************************************************************/

	// 2. Test populated table
	std::cout << "\n\n(2) Test move construct from populated table...\n";
	HTQuadraticProbing<std::string, int> table3;

	// Add elements
	std::string names[] = { "Al Swearengen", "Cy Tolliver", "Dan Dority",
							"Johnny Burns", "Jimmy Irons", "Doc Cochran" };
	int ages[] = { 62, 62, 39, 34, 38, 50 };

	for (int i = 0; i < std::size(names); ++i)
		table3.insert(names[i], ages[i]);

	// Table 3
	std::cout << "\n\nInitial contents of table3:\n\n";
	table3.printTable();
	std::cout << "table3 is empty:            " << table3.isEmpty() << '\n';
	std::cout << "table3 size:                " << table3.size() << '\n';

	std::cout << "\n\nMove construct new table from table3...\n\n";
	HTQuadraticProbing<std::string, int> table4(std::move(table3));

	std::cout << "\n\nAfter move construction...\n\n";
	std::cout << "\n\nContents of table3:\n\n";
	table3.printTable();
	std::cout << "table3 is empty:            " << table3.isEmpty() << '\n';
	std::cout << "table3 size:                " << table3.size() << "\n\n";

	std::cout << "\n\nContents of table4:\n\n";
	table4.printTable();
	std::cout << "table4 is empty:            " << table4.isEmpty() << '\n';
	std::cout << "table4 size:                " << table4.size() << '\n';

	printLogEnd(__FUNCTION__);
}


void testCopyAssignmentOperator() {
	printLogStart(__FUNCTION__);
	std::cout << std::boolalpha;

	// 1. Test copy assign empty to empty
	std::cout << "(1) Copy assign from an empty table into an empty table...\n";
	HTQuadraticProbing<std::string, int> table1;
	HTQuadraticProbing<std::string, int> table2;

	std::cout << "\nBefore copy assign...\n";
	std::cout << "table1 is empty:            " << table1.isEmpty() << '\n';
	std::cout << "table1 size:                " << table1.size() << '\n';
	std::cout << "table2 is empty:            " << table2.isEmpty() << '\n';
	std::cout << "table2 size:                " << table2.size() << '\n';

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

	HTQuadraticProbing<std::string, int> table3;

	// Add elements
	std::string names[] = { "Al Swearengen", "Cy Tolliver", "Dan Dority",
							"Johnny Burns", "Jimmy Irons", "Doc Cochran" };
	int ages[] = { 62, 62, 39, 34, 38, 50 };

	for (int i = 0; i < std::size(names); ++i)
		table1.insert(names[i], ages[i]);

	std::cout << "\nBefore copy assign...\n";
	std::cout << "\nContents of table1:\n\n";
	table1.printTable();
	std::cout << "table1 is empty:            " << table1.isEmpty() << '\n';
	std::cout << "table1 size:                " << table1.size() << '\n';

	std::cout << "\n\nCopy assign empty table3 into populated table1...\n";
	table1 = table3;
	std::cout << "\nAfter copy assign...\n";

	// table1 should now be empty
	std::cout << "\n\nContents of table1:\n\n";
	table1.printTable();
	std::cout << "table1 is empty:            " << table1.isEmpty() << '\n';
	std::cout << "table1 size:                " << table1.size() << '\n';

	// table3 should still be empty
	std::cout << "\n\nContents of table3:\n\n";
	table3.printTable();
	std::cout << "table3 is empty:            " << table3.isEmpty() << '\n';
	std::cout << "table3 size:                " << table3.size() << '\n';
	print_separator();

	/*****************************************************************************/

	// 3. Test copy assign populated into empty
	std::cout << "\n\n(3) Copy assign from a populated table into an empty table...\n";

	// Repopulate table1
	for (int i = 0; i < std::size(names); ++i)
		table1.insert(names[i], ages[i]);

	std::cout << "\nBefore copy assign...\n";

	// Should now be populated
	std::cout << "\n\nContents of table1:\n\n";
	table1.printTable();
	std::cout << "table1 is empty:            " << table1.isEmpty() << '\n';
	std::cout << "table1 size:                " << table1.size() << '\n';

	// Should (still) be empty
	std::cout << "\n\nContents of table2:\n\n";
	table2.printTable();
	std::cout << "table2 is empty:            " << table2.isEmpty() << '\n';
	std::cout << "table2 size:                " << table2.size() << '\n';

	std::cout << "\n\nCopy assign populated table1 into empty table2..\n\n";
	table2 = table1;
	std::cout << "\nAfter copy assign...\n";

	// Contents should be unchanged
	std::cout << "\n\nContents of table1:\n\n";
	table1.printTable();
	std::cout << "table1 is empty:            " << table1.isEmpty() << '\n';
	std::cout << "table1 size:                " << table1.size() << '\n';

	// Should now have same contents as table1
	std::cout << "\n\nContents of table2:\n\n";
	table2.printTable();
	std::cout << "table2 is empty:            " << table2.isEmpty() << '\n';
	std::cout << "table2 size:                " << table2.size() << '\n';
	print_separator();

	/*****************************************************************************/

	// 4. Test copy assign populated into populated
	std::cout << "\n\n(4) Copy assign from a populated table into another populated table...\n";

	// Create a new tree with some different contents
	HTQuadraticProbing<std::string, int> table4;

	// Populate table4
	table4.insert("Fred Flintstone", 40);
	table4.insert("Barney Rubble", 40);
	table4.insert("Wilma Flintstone", 40);
	table4.insert("Betty Rubble", 40);

	std::cout << "\nBefore copy assign...\n";
	std::cout << "\n\nContents of table4:\n\n";
	table4.printTable();
	std::cout << "table4 is empty:            " << table4.isEmpty() << '\n';
	std::cout << "table4 size:                " << table4.size() << '\n';

	// tree1 still empty
	std::cout << "\n\nCopy assign populated table4 into table2 (has different contents)...\n";
	table2 = table4;
	std::cout << "\n\nAfter copy assign...\n\n";

	// Should now mirror contents of table3
	std::cout << "\n\nContents of table2:\n\n";
	table2.printTable();
	std::cout << "table2 is empty:            " << table2.isEmpty() << '\n';
	std::cout << "table2 size:                " << table2.size() << '\n';

	// Should be unchanged
	std::cout << "\n\nContents of table4:\n\n";
	table4.printTable();
	std::cout << "table4 is empty:            " << table4.isEmpty() << '\n';
	std::cout << "table4 size:                " << table4.size() << '\n';

	printLogEnd(__FUNCTION__);
}

void testMoveAssignmentOperator() {
	printLogStart(__FUNCTION__);
	std::cout << std::boolalpha;

	// 1. Test move assign empty to empty
	std::cout << "(1) Move assign from an empty table into an empty table...\n";
	HTQuadraticProbing<std::string, int> table1;
	HTQuadraticProbing<std::string, int> table2;

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

	HTQuadraticProbing<std::string, int> table3;

	// Add elements
	std::string names[] = { "Al Swearengen", "Cy Tolliver", "Dan Dority",
							"Johnny Burns", "Jimmy Irons", "Doc Cochran" };
	int ages[] = { 62, 62, 39, 34, 38, 50 };

	for (int i = 0; i < std::size(names); ++i)
		table1.insert(names[i], ages[i]);

	std::cout << "\nBefore move assign...\n";
	std::cout << "\n\nContents of table1:\n\n";
	table1.printTable();
	std::cout << "table1 is empty:            " << table1.isEmpty() << '\n';
	std::cout << "table1 size:                " << table1.size() << '\n';

	std::cout << "\n\nMove assign empty table3 into populated table1...\n";
	table1 = std::move(table3);
	std::cout << "\nAfter move assign...\n";

	// table1 should now be empty
	std::cout << "\n\nContents of table1:\n\n";
	table1.printTable();
	std::cout << "table1 is empty:            " << table1.isEmpty() << '\n';
	std::cout << "table1 size:                " << table1.size() << '\n';

	// table3 should still be empty
	std::cout << "\n\nContents of table3:\n\n";
	table3.printTable();
	std::cout << "table3 is empty:            " << table3.isEmpty() << '\n';
	std::cout << "table3 size:                " << table3.size() << '\n';
	print_separator();

	/*****************************************************************************/

	// 3. Test move assign populated into empty
	std::cout << "\n\n(3) Move assign from a populated table into an empty table...\n";

	// Repopulate table1
	for (int i = 0; i < std::size(names); ++i)
		table1.insert(names[i], ages[i]);

	std::cout << "\nBefore move assign...\n";

	// Should now be populated
	std::cout << "\n\nContents of table1:\n\n";
	table1.printTable();
	std::cout << "table1 is empty:            " << table1.isEmpty() << '\n';
	std::cout << "table1 size:                " << table1.size() << '\n';

	// Should (still) be empty
	std::cout << "\n\nContents of table2:\n\n";
	table2.printTable();
	std::cout << "table2 is empty:            " << table2.isEmpty() << '\n';
	std::cout << "table2 size:                " << table2.size() << '\n';

	std::cout << "\n\nMove assign populated table1 into empty table2..\n\n";
	table2 = std::move(table1);
	std::cout << "\nAfter move assign...\n";

	// Contents should be unchanged
	std::cout << "\n\nContents of table1:\n\n";
	table1.printTable();
	std::cout << "table1 is empty:            " << table1.isEmpty() << '\n';
	std::cout << "table1 size:                " << table1.size() << '\n';

	// Should now have same contents as table1
	std::cout << "\n\nContents of table2:\n\n";
	table2.printTable();
	std::cout << "table2 is empty:            " << table2.isEmpty() << '\n';
	std::cout << "table2 size:                " << table2.size() << '\n';
	print_separator();

	/*****************************************************************************/

	// 4. Test move assign populated into populated
	std::cout << "\n\n(4) Move assign from a populated table into another populated table...\n";

	// Create a new tree with some different contents
	HTQuadraticProbing<std::string, int> table4;

	// Populate table4
	table4.insert("Fred Flintstone", 40);
	table4.insert("Barney Rubble", 40);
	table4.insert("Wilma Flintstone", 40);
	table4.insert("Betty Rubble", 40);

	std::cout << "\nBefore move assign...\n";
	std::cout << "\n\nContents of table4:\n\n";
	table4.printTable();
	std::cout << "table4 is empty:            " << table4.isEmpty() << '\n';
	std::cout << "table4 size:                " << table4.size() << '\n';

	// tree1 still empty
	std::cout << "\n\nMove assign populated table4 into table2 (has different contents)...\n";
	table2 = table4;
	std::cout << "\n\nAfter move assign...\n\n";

	// Should now mirror contents of table3
	std::cout << "\n\nContents of table2:\n\n";
	table2.printTable();
	std::cout << "table2 is empty:            " << table2.isEmpty() << '\n';
	std::cout << "table2 size:                " << table2.size() << '\n';

	// Should be unchanged
	std::cout << "\n\nContents of table4:\n\n";
	table4.printTable();
	std::cout << "table4 is empty:            " << table4.isEmpty() << '\n';
	std::cout << "table4 size:                " << table4.size() << '\n';

	printLogEnd(__FUNCTION__);
}



/***************************************************************************************/

// Other Test Functions
// --------------------

void testGetFunctionEmptyTable() {
	printLogStart(__FUNCTION__);
	std::cout << std::boolalpha;

	// Test get function
	std::cout << "\n\nTest get/hasKey functions on empty table:\n";
	HTQuadraticProbing<int, std::string> table1;
	std::cout << "\ntable1 constructed with default capacity and load factor...\n";
	std::cout << "table1 size:  " << table1.size() << '\n';
	std::cout << "table1 empty: " << table1.isEmpty() << '\n';
	std::cout << "\nCurrent contents of table1:\n\n";
	table1.printTable();

	std::optional<std::string> ret_val = table1.get(10);
	std::cout << "table1.get(10): ";
	if (!ret_val.has_value())
		std::cout << " NOT FOUND!\n";

	std::cout << "table1.hasKey(50): " << table1.hasKey(50) << '\n';

	printLogEnd(__FUNCTION__);
}


void testOneEntryHTQP() {
	printLogStart(__FUNCTION__);

	std::cout << std::boolalpha;

	// 1. Test get() function
	std::cout << "\n\n(1) Test insert on a default constructed hashtable:\n\n";
	HTQuadraticProbing<int, std::string> table1;

	std::optional<std::string> ret_val = table1.insert(57, "Cy Tolliver");
	if (ret_val.has_value())
		std::cout << "Value returned from insert is: " << ret_val.value() << '\n';

	std::cout << "table1 size:  " << table1.size() << '\n';
	std::cout << "table1 empty: " << table1.isEmpty() << '\n';

	// Try inserting on the same key...
	ret_val = table1.insert(57, "Al Swearengen");
	if (ret_val.has_value())
		std::cout << "Value returned from insert is: " << ret_val.value() << '\n';
	
	std::cout << "table1 size:  " << table1.size() << '\n';
	std::cout << "table1 empty: " << table1.isEmpty() << '\n';
	print_separator();

	/************************************************************/

	// 2. Test get() and hasKey()
	std::cout << "\n\n(2) Test get()/hasKey() functions...\n\n";
	for (int i = 50; i < 60; i++) {
		std::cout << "Table has key " << i << ": " << table1.hasKey(i) << '\n';
		ret_val = table1.get(i);
		if (ret_val.has_value())
			std::cout << "Value returned from get(" << i << ") is: " << ret_val.value() << "\n\n";
	}
	print_separator();

	/************************************************************/

	// 3. Test removing elements
	std::cout << "\n\n(3) Test remove() functions...\n\n";

	for (int i = 50; i < 60; i++) {
		ret_val = table1.remove(i);

		if (ret_val.has_value())
			std::cout << "Value removed from the table is: " << ret_val.value() << "\n\n";
		else
			std::cout << "Cannot remove entry for " << i << " from the table as no such key exists!\n\n";
	}

	std::cout << "\nState of the table after remove:\n\n";
	table1.printTable();
	std::cout << "table1 size:  " << table1.size() << '\n';
	std::cout << "table1 empty: " << table1.isEmpty() << '\n';
	print_separator();

	/*******************************************************************************/

	// 4. Test clearing the table
	std::cout << "\n\n(4) Test clearing (and removing from) table... repeatedly...\n\n";
	for (int i = 0; i < 10; i++) {
		table1.clear();
		if (!table1.remove(i))
			std::cout << "Remove " << i << " failed...\n";
	}

	std::cout << "\nState of the table after clear:\n\n";
	table1.printTable();
	std::cout << "table1 size:  " << table1.size() << '\n';
	std::cout << "table1 empty: " << table1.isEmpty() << '\n';

	printLogEnd(__FUNCTION__);
}


void testMultiEntryHTQP() {
	printLogStart(__FUNCTION__);
	std::cout << std::boolalpha;

	// 1. Try to avoid hitting the resize function here - test that last...
	std::cout << "\n\n(1) Set up a table with multiple entries...\n\n";
	HTQuadraticProbing<int, std::string> table1(19, 0.75);

	std::cout << "\nState of the table after initial construction:\n\n";
	table1.printTable();
	std::cout << "table1 size:  " << table1.size() << '\n';
	std::cout << "table1 empty: " << table1.isEmpty() << '\n';
	print_separator();

	/*******************************************************************************/

	// 2. Insert numerous values
	std::cout << "\n\n(2) Test multiple inserts into the table...\n\n";
	std::optional<std::string> inserted;

	std::string names[] = {
		"Al Swearengen", "Dan Dority", "Johnny Burns", "Davey", "Trixie", "Jewel",
		"Sol Starr", "Seth Bullock", "Wild Bill Hicock", "Charlie Utter",
		"Calamity Jane", "EB Farnum", "Richardson", "Cy Tolliver", "Joanie Stubbs",
		"Eddie Sawyer", "Leon", "Reverend Smith", "Andy Cramed", "Doc Cochran",
		"Whitney Ellsworth", "AW Merrick", "Tom Nuttall", "Harry Manning"
	};

	for (int i = 1; i < 21; i++) {
		inserted = table1.insert(i, names[i]);
		if (inserted.has_value())
			std::cout << "Old value in table was: " << inserted.value() << '\n';
		else
			std::cout << "Fresh insert of " << names[i] << " into table.\n";
	}
	std::cout << "\nState of the table after initial construction:\n\n";
	table1.printTable();
	std::cout << "table1 size:  " << table1.size() << '\n';
	std::cout << "table1 empty: " << table1.isEmpty() << '\n';
	print_separator();

	/*******************************************************************************/

	// 3. Reinsert values already inserted
	std::cout << "\n\n(3) Test reinserting the same values...\n\n";

	for (int i = 1; i < 21; i++) {
		inserted = table1.insert(i, names[i]);
		if (inserted.has_value())
			std::cout << "Old value in table was: " << inserted.value() << '\n';
		else
			std::cout << "Fresh insert of " << names[i] << " into table.\n";
	}
	std::cout << "\nState of the table after initial construction:\n\n";
	table1.printTable();
	std::cout << "table1 size:  " << table1.size() << '\n';
	std::cout << "table1 empty: " << table1.isEmpty() << '\n';
	print_separator();

	/*******************************************************************************/

	// 4. Find and get the keys
	std::cout << "\n\n(4) Test finding and getting the keys...\n\n";

	for (int i = 0; i < std::size(names); i++) {
		std::cout << "\n";
		std::cout << "table contains " << names[i] << ": " << table1.hasKey(i) << '\n';
		inserted = table1.get(i);
		if (!inserted.has_value())
			std::cout << names[i] << " not found in table!\n";
		else
			std::cout << names[i] << " found with key " << i << "\n";
	}

	printLogEnd(__FUNCTION__);
}



void testTableResizing() {
	printLogStart(__FUNCTION__);
	std::cout << std::boolalpha;

	// Create a table that gradually increases in size with insertions
	std::cout << "\n\n(1) Set up a table and insert more items as we go along...\n\n";
	HTQuadraticProbing<int, std::string> table1(5, 0.85);

	std::string names[] = {
		"Al Swearengen", "Dan Dority", "Johnny Burns", "Davey", "Trixie", "Jewel",
		"Sol Starr", "Seth Bullock", "Wild Bill Hicock", "Charlie Utter",
		"Calamity Jane", "EB Farnum", "Richardson", "Cy Tolliver", "Joanie Stubbs",
		"Eddie Sawyer", "Leon", "Reverend Smith", "Andy Cramed", "Doc \"Leave the Amos out of there\" Cochran",
		"Whitney Ellsworth", "AW Merrick", "Tom Nuttall", "Harry Manning"
	};

	for (int i = 0; i < std::size(names); i++) {
		std::cout << "--------------------------------------------------------------\n";
		std::cout << "\n\n";
		table1.insert(i, names[i]);
		std::cout << names[i] << " inserted...\n";
		std::cout << "table1 size:  " << table1.size() << "\n\n";
		table1.printTable();
	}
	print_separator();

	/********************************************************************************/

	// 2. Change the table about a bit
	std::cout << "\n\n(2) Test some deletions, insertions etc to change the table, create some tombstones etc...\n\n";

	// A few removals...
	int removals{};
	for (int i = 0; i < table1.size(); i++) {
		if (removals <= 10) {
			table1.remove(i);
			removals++;
		}
	}

	std::cout << removals << " entries have been removed from the table\n";
	std::cout << "table1 size:  " << table1.size() << '\n';
	std::cout << "\nContents of table after removes...\n\n";
	table1.printTable();

	// Now some insertions...
	table1.insert(30, "Myles");
	table1.insert(31, "Dora");
	table1.insert(32, "General Fields");
	table1.insert(33, "Steve");
	table1.insert(34, "Hostetler");
	table1.insert(35, "Aunt Lou");
	table1.insert(36, "Frances Wollcott");
	table1.insert(37, "Jack Langrishe");
	table1.insert(38, "Silas Adams");
	table1.insert(39, "Alma Garrett");
	table1.insert(40, "Brom Garrett");
	table1.insert(41, "William Bullock");
	table1.insert(42, "Martha Bullock");
	table1.insert(43, "Frances Wollcott");
	table1.insert(44, "Jack McCall");
	table1.insert(45, "Sofia Metz");
	table1.insert(46, "Frances Wollcott");
	table1.insert(47, "Mr Wu");
	table1.insert(48, "Con Stapleton");
	table1.insert(49, "Blazanov");
	table1.insert(50, "George Hearst");

	std::cout << "\nThe table after some more insertions...\n";
	std::cout << "table1 size:  " << table1.size() << "\n\n";
	table1.printTable();
	print_separator();

	/****************************************************************************/

	// 3. Test inserts are found
	std::cout << "\n\n(3) Check for the presence of the recently inserted keys...\n\n";

	for (int i = 30; i < 60; i++)
		std::cout << "Table has key " << i << ": " << table1.hasKey(i) << '\n';

	printLogEnd(__FUNCTION__);
}


void testDuplicateKeys() {
	printLogStart(__FUNCTION__);

	// 1. Test the initial inserts
	std::cout << "\n\n(1) Test first " << std::quoted("round") << " of inserts...\n";
	
	HTQuadraticProbing<int, std::string> table1(5, 0.85);

	std::string names[] = {
		"Al Swearengen", "Dan Dority", "Johnny Burns", "Davey", "Trixie", "Jewel",
		"Sol Starr", "Seth Bullock", "Wild Bill Hicock", "Charlie Utter",
		"Calamity Jane", "EB Farnum", "Richardson", "Cy Tolliver", "Joanie Stubbs",
		"Eddie Sawyer", "Leon", "Reverend Smith", "Andy Cramed", "Doc Cochran",
		"Whitney Ellsworth", "AW Merrick", "Tom Nuttall", "Harry Manning"
	};

	std::string names2[] = {
		"Al Swearengen", "Daniel Dority", "Johnny Burns", "Davey", "General Fields",
		"Jewel", "Sol Starr", "Seth Bullock", "William Hicock",
		"Charlie \"What Do You Think of My Frock Coat?\" Utter",
		"Jane Canary", "EB Farnum", "Could You Have Been Born, Richardson?",
		"Cyrus Tolliver", "Joanie Stubbs", "Eddie Sawyer", "Leon", "Reverend Smith",
		"Reverend Cramed", "Amos Cochran", "Whitney Ellsworth", "AW Merrick",
		"Tom Nuttall", "Harry Manning"
	};
	
	std::cout << "\n\n";
	for (int i = 0; i < std::size(names); i++) {
		if (table1.insert(i, names[i]) == names[i])
			std::cout << "Insert of " << names[i] << " failed...\n";
		else
			std::cout << names[i] << " inserted into table...\n";
	}
	std::cout << "\n\nContents of table after inserts...\n\n";
	table1.printTable();
	std::cout << "\ntable1 size:  " << table1.size() << "\n\n";
	print_separator();

	/****************************************************************************/

	// 2. Attempt to insert the same entries again
	std::cout << "\n\n(2)  Now try reinserting the same keys and values...\n\n";

	for (int i = 0; i < std::size(names); i++) {
		if (table1.insert(i, names[i]) == names[i])
			std::cout << "Insert of " << names[i] << " failed...\n";
		else
			std::cout << names[i] << " inserted into table...\n";
	}

	std::cout << "\nContents of table1 after (failed) reinserts:\n\n";
	table1.printTable();
	std::cout << "\ntable1 size after reinserts:  " << table1.size() << "\n\n";
	print_separator();

	/****************************************************************************/

	// 3. Insert some more new entries
	std::cout << "\n\n(3) Now try reinserting the same keys with some having *different* values...\n\n";

	for (int i = 0; i < std::size(names); i++) {
		std::optional<std::string> name = table1.insert(i, names[i]);

		if (name.has_value())
			std::cout << name.value() << " updated in table...\n";
		else
			std::cout << names[i] << " newly inserted into table...\n";
	}

	std::cout << "\nContents of table1 after inserts & reinserts:\n\n";
	table1.printTable();
	std::cout << "\ntable1 size after inserts/reinserts:  " << table1.size() << "\n\n";
	print_separator();

	printLogEnd(__FUNCTION__);
}
// Hash Table - Quadratic Probing
// ------------------------------
// 
// This is a C++ implementation of a hash table that uses an open addressing approach, 
// specifically one using quadratic probing. As with the other data structure
// implementations, the core logic is based on a Java class demonstrated 
// by William Fiset in his YouTube data structures course video (see the test file for 
// more details).
// 
// However, this solution especially deviates from the Fiset implementation,
// primarily due to the subtle - but sometimes significant - differences in the way
// Java and C++ handle things.
// 
// One of the key differences is that we can't use the actual key data type itself to
// identify whether a particular slot in the table is empty, filled, or a tombstone.
// 
// This is because C++ cannot deal with null in the same way Java does, so we
// have no way easily working out based on the key alone which type of slot
// it indicates.
// 
// A convenient solution is to have an additional data type to store this; 
// hence an enum class called SlotType has been added to the class.
// (The idea of using a slot enum came from here
// https://web.stanford.edu/class/archive/cs/cs106b/cs106b.1234/assignments/a6/)
// 
// I've taken the further decision to add a further, third, array to store this
// data field. This means that we can refer directly to that array (slotTable)
// to identify at any time what type of slot it is at a particular index. 
// The downside of this approach is that there is an additional array to maintain. 
// 
// An alternative would be to have another Entry type class (as used in the separate
// chaining implementation) that has the key and value, as the SC entry class does, 
// but then add a slot type field, and from there have an array that stores elements of 
// that Entry type. This would mean that all the data pertaining to an element is stored
// in a single array, rather than spread across three arrays.

#ifndef HASH_TABLE_QUADRATIC_PROBING_H
#define	HASH_TABLE_QUADRATIC_PROBING_H

#include <algorithm>
#include <bit>
#include <cmath>
#include <functional>
#include <iomanip>
#include <iostream>
#include <optional>
#include <vector>
#include <type_traits>


template <typename K, typename V>
class HTQuadraticProbing {
public:
	HTQuadraticProbing() : HTQuadraticProbing(DEFAULT_CAPACITY, DEFAULT_LOAD_FACTOR) { }
	HTQuadraticProbing(int initCapacity) : 
		HTQuadraticProbing(initCapacity, DEFAULT_LOAD_FACTOR) {  }
	HTQuadraticProbing(int initCapacity, double initLoadFactor);
	HTQuadraticProbing(const HTQuadraticProbing& other);
	HTQuadraticProbing(HTQuadraticProbing&& other) noexcept;
	HTQuadraticProbing& operator=(const HTQuadraticProbing& other);
	HTQuadraticProbing& operator=(HTQuadraticProbing&& other) noexcept;
	~HTQuadraticProbing();

	void clear();
	bool isEmpty();
	int size();
	std::optional<V> get(K key);
	bool hasKey(K key);
	std::optional<V> insert(K key, V value);
	std::optional<V> remove(K key);
	void printTable();
private:
	void swap(HTQuadraticProbing& other);
	static int next2Power(unsigned int number);
	void setUpAndInitialiseTables();
	static int quadraticProbe(int value);
	int normaliseIndex(int keyHash);
	void resizeTable();
	void deleteTable();
private:
	// Enumeration for the type of slots we will need to deal with in this HT
	enum class SlotType {
		EMPTY, FILLED, TOMBSTONE
	};

	// Default constants for the capacity and load of a HT
	inline static const int DEFAULT_CAPACITY = 7;
	inline static const double DEFAULT_LOAD_FACTOR = 0.65;

	bool contains{ false };	 // Indicates if an item is contained in the HT
	double loadFactor{};
	int capacity{};
	int modificationCount{};
	int threshold{};
	int usedBuckets{};	     // No. buckets used (includes deleted buckets)
	int keyCount{};		     // No. unique keys

	// Pointers to arrays storing key-value pairs.
	// An alternative is one array of a wrapper class that stores all three pieces 
	// of data, but we're going with the former approach here.
	K* keyTable{};
	V* valueTable{};
	SlotType* slotTable{};
};

// Quadratic Probing Hash Table Public Member Definitions
// ======================================================

// Special Member Functions
// ------------------------

// Constructor
// -----------
// 
// Here we setup the key and value tables that constitute the HT
// and the key variables that regulate the HT's efficient functioning.
// 
// The key variables are:
// - capacity:
// - loadFactor:
// - threshold:
// 
// HT Capacity
// -----------
//  
// - is set to the default capacity if the user has not supplied a value 
// - it is also set to the default capacity if the user supplies a zero
//   value or a negative value
// - the value will be converted (if necessary) to the largest
//   integral power of two not less than the value itself
// - if the (converted) value is less than the default capacity, the 
//   capacity will be set to the default instead
// 
// HT Load Factor
// --------------
// 
// - is set to the default capacity if the user has not supplied a value
// - it is also set to the default if the user supplies a zero
//   value or a negative value
// - it will also be set to the default if the user supplies a value that is not
//   a valid floating-point number, or if it exceeds the maximum capacity for
//   the data type.
// 
// HT Threshold
// ------------
// 
// - This will be set to result of the capacity multiplied by the load factor, 
//   converted to the closest integral value if necessary.

template <typename K, typename V>
HTQuadraticProbing<K, V>::HTQuadraticProbing(int initCapacity, double initLoadFactor) {
	std::cout << "Running HTQuadraticProbing(initCapacity, initLoadFactor)...\n";
	// Set capacity first
	if (initCapacity <= 0)
		capacity = DEFAULT_CAPACITY;
	capacity = std::max(DEFAULT_CAPACITY, next2Power(initCapacity));

	// Set the load factor.
	// If the user-supplied value is too low or too high, use the default.
	if (initLoadFactor <= 0.10 || initLoadFactor >= 0.90)
		loadFactor = DEFAULT_LOAD_FACTOR;
	else
		loadFactor = initLoadFactor;

	// Set threshold based on the above values
	threshold = static_cast<int>(capacity * loadFactor);

	// Finally, setup the key, value, and slot type tables
	// Their size is based on the capacity
	setUpAndInitialiseTables();	
}


// Clears up data and memory associated with the underlying arrays that
// make up the HT.
// 
// Unlike the clear() method, here there is no subsequent revival of the
// arrays with new memory.
template <typename K, typename V>
HTQuadraticProbing<K, V>::~HTQuadraticProbing() {
	deleteTable();
}


// Copy constructor
template <typename K, typename V>
HTQuadraticProbing<K, V>::HTQuadraticProbing(const HTQuadraticProbing& other) {
	// Ensure the arrays for this table have capacity equal to those in other	
	this->keyTable = new K[other.capacity];
	this->valueTable = new V[other.capacity];
	this->slotTable = new SlotType[other.capacity];

	// Copy over the data from the other table arrays to this
	for (int i = 0; i < other.capacity; i++) {
		this->keyTable[i] = other.keyTable[i];
		this->valueTable[i] = other.valueTable[i];
		this->slotTable[i] = other.slotTable[i];
	}

	// Now copy over the table management data
	this->loadFactor = other.loadFactor;
	this->capacity = other.capacity;
	this->modificationCount = other.modificationCount;
	this->threshold = other.threshold;
	this->usedBuckets = other.usedBuckets;
	this->keyCount = other.keyCount;
}


// Move constructor
template <typename K, typename V>
HTQuadraticProbing<K, V>::HTQuadraticProbing(HTQuadraticProbing&& other) noexcept :
	keyTable{ std::exchange(other.keyTable, {}) },
	valueTable{ std::exchange(other.valueTable, {}) },
	slotTable{ std::exchange(other.slotTable, {}) },
	loadFactor{ std::exchange(other.loadFactor, {}) },
	capacity{ std::exchange(other.capacity, {}) },
	modificationCount{ std::exchange(other.modificationCount, {}) },
	threshold{ std::exchange(other.threshold, {}) },
	usedBuckets{ std::exchange(other.usedBuckets, {}) },
	keyCount{ std::exchange(other.keyCount, {}) }
{ }


// Copy assignment operator
template <typename K, typename V>
HTQuadraticProbing<K, V>& HTQuadraticProbing<K, V>::operator=(const HTQuadraticProbing& other) {
	HTQuadraticProbing<K, V> temp(other);
	swap(temp);	
	return *this;
}


// Move assignment operator
template <typename K, typename V>
HTQuadraticProbing<K, V>& HTQuadraticProbing<K, V>::operator=(HTQuadraticProbing&& other)
	noexcept {
	HTQuadraticProbing<K, V> temp(std::move(other));
	swap(temp);
	return *this;
}


// Private utility function that transfers ownership of table resources from
// the other object to this object.
template <typename K, typename V>
void HTQuadraticProbing<K, V>::swap(HTQuadraticProbing& other) {
	using std::swap;
	swap(this->keyTable, other.keyTable);
	swap(this->valueTable, other.valueTable);
	swap(this->slotTable, other.slotTable);
	swap(this->loadFactor, other.loadFactor);
	swap(this->capacity, other.capacity);
	swap(this->modificationCount, other.modificationCount);
	swap(this->threshold, other.threshold);
	swap(this->usedBuckets, other.usedBuckets);
	swap(this->keyCount, other.keyCount);		
}

/****************************************************************************************/

// Other Public Member Functions
// -----------------------------

// Clears all the contents of the hash table.
template <typename K, typename V>
void HTQuadraticProbing<K, V>::clear() {
	// Clear the underlying tables
	deleteTable();

	// Important - don't leave arrays null otherwise null crashes could occur.
	// Reset the arrays to state they were in at the construction of the hash table.
	setUpAndInitialiseTables();

	// Update the key variables
	keyCount = 0;
	usedBuckets = 0;
	modificationCount++;
}


// Returns true if the HT is currently empty, else returns false.
template <typename K, typename V>
bool HTQuadraticProbing<K, V>::isEmpty() {
	return (keyCount == 0);
}


// Returns the number of keys currently inside the HT.
template <typename K, typename V>
int HTQuadraticProbing<K, V>::size() {
	return keyCount;
}


// Attempts to retrieve the value associated with key and returns the
// value if it is found in the HT.
// If the value is null, or no value is found for this
// key, it returns null.
template <typename K, typename V>
std::optional<V> HTQuadraticProbing<K, V>::get(K key) {
	int hash = std::hash<K>{}(key);
	const int index = normaliseIndex(hash);

	int currentIndex = index;	// Holds the current index in the table
	int firstTombstone = -1;	// Holds index of first tombstone encountered
	int probeOffset = 1;		// Holds the offset of the initial probe value

	// Start at the original hash index and quadratically probe until we find a 
	// the slot with a key that matches the key provided or we hit a null slot, 
	// in which case no entry exists in the HT for that key.
	do {
		// Skip over tombstones, but record position of first one encountered
		if (slotTable[currentIndex] == SlotType::TOMBSTONE) {
			if (firstTombstone == -1)
				firstTombstone = currentIndex;
		}
		else if (slotTable[currentIndex] == SlotType::FILLED) { // Found a filled slot
			if (keyTable[currentIndex] == key) {
				contains = true; // This slot contains the key we're searching for

				if (firstTombstone != -1) {
					// Previously encountered a tombstone.
					// Optimise search by swapping entries in the current slot
					// and the first tombstone slot.
					keyTable[firstTombstone] = keyTable[currentIndex];
					valueTable[firstTombstone] = valueTable[currentIndex];
					slotTable[firstTombstone] = SlotType::FILLED;

					// Clear the contents in current index and mark it as a tombstone
					keyTable[currentIndex] = {};
					valueTable[currentIndex] = {};
					slotTable[firstTombstone] = SlotType::TOMBSTONE;
					return valueTable[firstTombstone];
				} // end if 
				else {
					return valueTable[currentIndex]; // Simple return of found value
				}
			}
		}	// end else-if 
		else {
			// Key not found in HT - return null
			contains = false;
			return {};
		}
		// Setup for probing next slot (after tombstone found)
		currentIndex = normaliseIndex(hash + quadraticProbe(probeOffset++));
	} while (true);
}


// Returns true if key exists in this HT, otherwise returns false.
template <typename K, typename V>
bool HTQuadraticProbing<K, V>::hasKey(K key) {
	// Sets the 'contains' flag
	get(key);
	return contains;
}


// Inserts a key-value pair into the HT, using key and value provided.
// If the value already exists in the HT with that same key, the existing
// value in the HT is updated, and the old value is returned.
// If a fresh insert is performed, a null value is returned.
template <typename K, typename V>
std::optional<V> HTQuadraticProbing<K, V>::insert(K key, V value) {
	// If currently at or exceeding the current threshold, resize the HT
	if (usedBuckets >= threshold)
		resizeTable();

	int hash = std::hash<K>{}(key);
	const int index = normaliseIndex(hash);

	int currentIndex = index;	// Holds the current index in the HT
	int firstTombstone = -1;	// Holds index of first tombstone encountered
	int probeOffset = 1;		// Holds the offset of the initial probe value

	do {
		// Has the current slot been previously deleted?
		if (slotTable[currentIndex] == SlotType::TOMBSTONE) {
			if (firstTombstone == -1)
				// This is our first tombstone encountered.
				// Set the marker to the current index (i.e. position of this tombstone).
				firstTombstone = currentIndex;
		}
		// Does the current slot already contain a key?
		// TODO: Does the key check need performing? If the slot is filled
		// does that not mean it's the same key already and so the check is redundant?
		else if (slotTable[currentIndex] == SlotType::FILLED) {
			if (keyTable[currentIndex] == key) {
				// The key we're trying to insert already exists within the HT.
				// In this case, update the value associated with that key.
				V oldValue = valueTable[currentIndex];
				if (firstTombstone == -1)
					// We've not hit a tombstone, so simply update the value.
					valueTable[currentIndex] = value;
				else {
					// We've previously hit a tombstone.
					// We want to swap the tombstone, so 
					// set the current index to be a tombstone.
					keyTable[currentIndex] = {};
					valueTable[currentIndex] = {};
					slotTable[currentIndex] = SlotType::TOMBSTONE;

					// The previous tombstone position can now be used
					// to store the new entry.
					keyTable[firstTombstone] = key;
					valueTable[firstTombstone] = value;
					slotTable[firstTombstone] = SlotType::FILLED;
				}

				// Whether or not a tombstone has been encountered or not,
				// update the modification count and return the value that
				// we've inserted into the table.
				modificationCount++;
				return oldValue;
			}
		}	// end else-if
		else { // Current slot is empty, so an insertion/update can occur
			if (firstTombstone == -1) {	// No previously encountered deleted buckets
				usedBuckets++;
				keyCount++;
				keyTable[currentIndex] = key;
				valueTable[currentIndex] = value;
				slotTable[currentIndex] = SlotType::FILLED;
			}
			else {
				// Otherwise, we have previously encountered a tombstone.
				// Instead of inserting the new element at this current free bucket,
				// insert it at the location of that tombstone.
				keyCount++;
				keyTable[firstTombstone] = key;
				valueTable[firstTombstone] = value;
				slotTable[firstTombstone] = SlotType::FILLED;
			}
			modificationCount++;
			return {};
		}

		// If we reach here, we've hit an occupied slot so we need to 
		// probe for the next appropriate slot.
		currentIndex = normaliseIndex(hash + quadraticProbe(probeOffset++));
	} while (true);	// end of do-while	
}


// Removes a key-value pair from the HT and returns the deleted value.
// Returns null if the value itself is null, or if the key is not found.
template <typename K, typename V>
std::optional<V> HTQuadraticProbing<K, V>::remove(K key) {
	int hash = std::hash<K>{}(key);
	const int index = normaliseIndex(hash);

	int currentIndex = index;	// Holds the current index in the HT
	int firstTombstone = -1;	// Holds index of first tombstone encountered
	int probeOffset = 1;		// Holds the offset of the initial probe value

	// Starting at the hash index, quadratically probe until either we find the 
	// slot holding the key we're looking for, or we hit an empty slot,
	// in which case the key does not exist in the table.
	for (; ; currentIndex = normaliseIndex(hash + quadraticProbe(probeOffset++))) {
		// 1. Current slot holds a tombstone - skip over it
		if (slotTable[currentIndex] == SlotType::TOMBSTONE)
			continue;

		// 2. Current slot is empty - key not found - return
		if (slotTable[currentIndex] == SlotType::EMPTY)
			return {};

		// 3. Key is found at the current slot - proceed with removal
		if (keyTable[currentIndex] == key) {
			keyCount--;
			modificationCount++;

			// Save old value before it's removed
			V oldValue = valueTable[currentIndex];

			// This position now becomes a tombstone
			keyTable[currentIndex] = {};
			valueTable[currentIndex] = {};
			slotTable[currentIndex] = SlotType::TOMBSTONE;
			return oldValue;	// Finally, return the old value
		}
	}
}


// Prints the contents of all the three arrays that comprise this hash table.
template <typename K, typename V>
void HTQuadraticProbing<K, V>::printTable() {
	// Header labels
	std::cout << "SLOT NO.  ";
	std::cout << "SLOT TYPE  ";
	std::cout << "KEY                     ";
	std::cout << "VALUE                   ";
	std::cout << "\n";

	// Underlining
	std::cout << "_______   ";
	std::cout << "_________  ";
	std::cout << "___                     ";
	std::cout << "_____                   ";
	std::cout << "\n\n";

	// Now print the contents of the table
	for (int i = 0; i < capacity; i++) {
		std::cout << std::left << std::setw(10) << i;	// Slot No.

		std::string slotType;
		switch (slotTable[i]) {
		case SlotType::EMPTY:
			slotType = "Empty";
			break;
		case SlotType::FILLED:
			slotType = "Filled";
			break;
		case SlotType::TOMBSTONE:
			slotType = "Tombstone";
			break;
		default:
			slotType = "Error";
		}

		std::cout << std::setw(11) << std::left << slotType;		// Slot Type
		std::cout << std::setw(24) << std::left << keyTable[i];		// Key
		std::cout << std::setw(25) << std::left << valueTable[i];	// Value	
		std::cout << "\n";
	}
	std::cout << "\n\n";
}

/***************************************************************************************/

// Private Member Function Definitions
// -----------------------------------


// Private utility method that finds and returns the next power of two 
// above number specified.
template <typename K, typename V>
int HTQuadraticProbing<K, V>::next2Power(unsigned int number) {
	return std::bit_ceil(number);
}


// Private utility method that sets up the initial data in the arrays that
// comprise the hash table - arrays for keys, values, and slot types.
// 
// This is particularly crucial for the slot array, as all slots must be set to
// empty status initially, otherwise the table will not function properly
template <typename K, typename V>
void HTQuadraticProbing<K, V>::setUpAndInitialiseTables() {
	keyTable = new K[capacity];
	valueTable = new V[capacity];
	slotTable = new SlotType[capacity];

	for (int i = 0; i < capacity; i++) {
		keyTable[i] = {};
		valueTable[i] = {};
		slotTable[i] = SlotType::EMPTY;
	}
}


// Private utility method that performs the quadratic probe.
// Calculates the value of: 
// the value squared plus value, divided by two
// (division by two done by bitshifting one place to the right).
template <typename K, typename V>
int HTQuadraticProbing<K, V>::quadraticProbe(int value) {
	return (value * value + value) >> 1;
}


// Private utility method that converts a hash value to an index 
// and returns that index value.
// Essentially, this method strips the negative sign (if present)
// from keyHash and places the value in the domain [0, capacity)
template <typename K, typename V>
int HTQuadraticProbing<K, V>::normaliseIndex(int keyHash) {
	return (keyHash & 0x7FFFFFFF) % capacity;
}


// Private utility method that resizes the HT by a factor of two.
// In the process, all previous null and tombstone values are removed.
template <typename K, typename V>
void HTQuadraticProbing<K, V>::resizeTable() {
	// Increase the capacity to at least double the current capacity,
	// subject to power-of-two adjustment.
	int oldCapacity = capacity;	// Save old capacity as this is limit of old tables
	int newCapacity = capacity * 2;
	capacity = next2Power(newCapacity);
	threshold = static_cast<int>(capacity * loadFactor);

	K* oldKeyTable = new K[capacity];
	V* oldValueTable = new V[capacity];
	SlotType* oldSlotTable = new SlotType[capacity];

	// Swap the key tables
	K* tempKeyTable = keyTable;		// Retain link to existing key table
	keyTable = oldKeyTable;			// Set the current key table to the new table
	oldKeyTable = tempKeyTable;		// Set the old key table to the previous table

	// Swap the value tables
	V* tempValueTable = valueTable;	// Retain link to existing value table
	valueTable = oldValueTable;		// Set the current value table to the new table
	oldValueTable = tempValueTable;	// Set the old value table to the previous table

	// Swap the slot tables
	SlotType* tempSlotTable = slotTable; // Retain link to existing value table
	slotTable = oldSlotTable;			 // Set the current value table to the new table
	oldSlotTable = tempSlotTable;		 // Set the old value table to the previous table

	// Reset the key and used bucket counts to zero as the entire HT is 
	// about to be rebuilt from scratch.
	keyCount = 0;
	usedBuckets = 0;

	// Need to initialise the hash table arrays again 
	// as we're rebuilding the table from scratch
	setUpAndInitialiseTables();

	for (int i = 0; i < oldCapacity; i++) {
		if (oldSlotTable[i] != SlotType::EMPTY
			&& oldSlotTable[i] != SlotType::TOMBSTONE)
			// Not an empty or tombstone slot
			// Copy this key-value pair into the newly-expanded HT
			insert(oldKeyTable[i], oldValueTable[i]);

		oldKeyTable[i] = {};				// Clear out old key
		oldValueTable[i] = {};				// Clear out old value
		oldSlotTable[i] = SlotType::EMPTY;	// Clear out old slot type
	}

	// Finally, free up the memory used for the table transfer
	delete[] oldKeyTable;
	delete[] oldValueTable;
	delete[] oldSlotTable;
}


// Private utility method that clears the data from the underlying arrays
// that comprise the HT and also frees the memory associated with them.
template <typename K, typename V>
void HTQuadraticProbing<K, V>::deleteTable() {
	for (int i = 0; i < capacity; i++) {
		keyTable[i] = {};
		valueTable[i] = {};
		slotTable[i] = {};
	}

	delete[] keyTable;
	delete[] valueTable;
	delete[] slotTable;
	keyTable = nullptr;
	valueTable = nullptr;
	slotTable = nullptr;
}


#endif	// HASH_TABLE_QUADRATIC_PROBING_H


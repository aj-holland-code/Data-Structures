// Hash Table - Separate Chaining
// ------------------------------
// 
// This is a C++ implementation of a hash table that uses a separate chaining approach. 
// The core logic is based on the Java separate chaining hash table class demonstrated 
// by William Fiset in his YouTube data structures course video (see the test file for 
// more details), however, this has been made template class and adapted from there.
// 
// 
// An Associative Data Structure
// -----------------------------
// 
// This hash table works on the basis of storing key/value pairs (see the test file for
// more notes on the nature of hash tables and how they work). In this implementation, 
// since the key-value pairs are stored in a class called Entry (defined in this file),
// where it is useful to use the nomenclature "entry" to refer to this pairing as a 
// collective entity, I will do so. The hash table can, therefore, be thought of as 
// storing associated entries.
// 
// The table allows multiple entries to have the same value, but there can only be
// one entry with a particular key number, i.e. the keys must be unique. The elements
// are stored in buckets, but not in any particular order (since the bucket the element
// ends up in is determined by the hash of the key). 
// 
// This data structure is therefore along the lines of the std::unordered_map container 
// in the C++ standard library. It could be adapted to work like the C++ standard library
// container std::unordered_multimap, which accepts entries with duplicate keys, but
// the find, insert, and remove functions would all need to be amended to enable this
// to work.
// 
// Hash Collisions
// ---------------
//
// The nature of hash collisions and how to resolve them are covered in notes in
// the test file, but briefly, even though the keys are distinct, different elements may
// still hash to the same value (a hash collision), and where this happens, they clearly
// cannot all be stored in the same slot, so a collision resolution mechanism is required.
// 
// The mechanism used in separate chaining is to use an auxiliary data structure 
// and specifically this DS uses an array of linked lists to act as the table, with each
// particular linked list acting as a bucket. Each entry that hashes to a particular 
// hash value goes in the appropriate bucket. 
// 
// I've opted to use the standard library list class, although I could use 
// my own doubly linked list implementation.
//
// 
// Special Member Functions
// ------------------------
// 
// I've gone with the safe option again here, and used the copy-and-swap idiom for the
// copy and move assignment operators, as with previous data structures. There is no
// need to go into great detail on that again here, since it has been covered elsewhere,
// but the copy constructor merits a brief mention.
// 
// Copying the fundamental types used in the management of the table (for example, the
// size and threshold) is straightforward. The actual table itself is a little trickier, 
// since it involves heap memory. The approach is to create a table (i.e. an array of 
// linked lists) of the same size as that in the source object, and then copy over the 
// elements of all the buckets in that source object that have entries. This object will 
// then have the same empty buckets as the source object, but also have the same
// elements in the populated buckets, so ultimately this object mirrors the source
// object.
// 
// Clearing the Table
// ------------------
// 
// The clear() function is setup to reset the size to zero and clear the buckets
// of their contents, but it does not actually remove the buckets altogether.
// This could be done, but entails memory allocations and deallocations, and so I've
// opted here to minimise the expense (and risks) of doing that.
// 
// It seems this is one of the performance issues one would have to monitor if this
// table were actually used in real operational code; doing it as a training exercise
// it's hard to say whether it's better to retain memory once it's allocated to avoid
// the issues involved with acquiring and releasing it, or whether the priority should
// be to release unused memory for other purposes.
// 
// 
// Future Improvements
// -------------------
// 
// 1. Add iterators.
// 2. Add an element access operator [].
// 3. Add bucket functionality (bucket count, the specific bucket for a certain key, etc.)
// 4. Resolve the const correctness issue with the Entry class.

#ifndef HASH_TABLE_SEPARATE_CHAINING_H
#define HASH_TABLE_SEPARATE_CHAINING_H

#include <functional>
#include <list>
#include <optional>
#include <string>
#include <utility>		// For std::swap

// Potentially key should key be const, since it is supposed to be immutable.
// The problem here is that if it's made const, it makes the assign operations
// for Entry fail. One possible approach is an assignment operator overload
// for this class to work around that, but I'm not sure how this would work.
template <typename K, typename V>
class Entry {
public:
	Entry() {}
	Entry(K key, V value) : key{ key }, value{ value } {
		hash = std::hash<K>{}(key);
	}

	int hash = 0;
	K key{};
	V value{};
};

// Equality Operator Overload for the Entry Class
// 
// Note: it is necessary to distinguish the types for the pairs of 
// entries: e1 has T1 & T2; e2 has U1 & U2
// (i.e. if we just have T1 and T2 for the data types for both
// data elements in the pair, this won't compile!)
template<class T1, class T2, class U1, class U2>
bool operator==(const Entry<T1, T2>& e1, const Entry<U1, U2>& e2) {
	// If the object hashes aren't equal it's certain the objects aren't equal
	if (e1.hash != e2.hash)
		return false;
	else
		return (e1.value == e2.value);
}

template <typename K, typename V>
class ChainedHashTable {
public:
	ChainedHashTable(int capacity = DEFAULT_CAPACITY) :
		ChainedHashTable(capacity, DEFAULT_LOAD_FACTOR) { }
	ChainedHashTable(int capacity, double maxLoadFactor);	
	ChainedHashTable(const ChainedHashTable& other);
	ChainedHashTable(ChainedHashTable&& other) noexcept;
	ChainedHashTable& operator=(const ChainedHashTable& other);
	ChainedHashTable& operator=(ChainedHashTable&& other) noexcept;
	~ChainedHashTable();

	int size();
	bool isEmpty();
	void clear();
	bool containsKey(K key);
	bool hasKey(K key);
	std::optional<V> get(K key);
	V insert(K key, V value);
	std::optional<V> remove(K key);
	void print();
private:
	void swap(ChainedHashTable<K, V>& other);
	V bucketInsertEntry(int bucketIndex, Entry<K, V> entry);
	std::optional<V> bucketRemoveEntry(int bucketIndex, K key);
	std::list<Entry<K, V>>::iterator bucketSeekEntry(int bucketIndex, K key);
	int normaliseIndex(int keyHash);
	void resizeTable();
	void printTableContents();
public:
	static const int DEFAULT_CAPACITY = 3;
	inline static const double DEFAULT_LOAD_FACTOR = 0.75;
private:
	// Maximum % of available capacity allowed before resize
	double m_maxLoadFactor;

	// How many elements the table currently has the capacity to store
	int m_capacity;

	// Trigger point where resizing required, based on capacity multiplied by load factor
	int m_threshold;

	// How many elements are actually being stored in the table
	int m_size;

	// The heart of the data structure is an array of linked lists (containing entries),
	// which this pointer points to.
	std::list<Entry<K, V>>* m_table;
};

// Chained Hash Table Public Member Definitions
// ============================================

// Constructor
template <typename K, typename V>
ChainedHashTable<K, V>::ChainedHashTable(int capacity, double maxLoadFactor)
	: m_size{} {
	// Use default for the capacity of the hash
	// table if the user-supplied values are 'illegal'
	// (i.e too small or too large).
	if (capacity < 0 || capacity >= INT32_MAX)
		m_capacity = DEFAULT_CAPACITY;

	// Otherwise set to the larger of the user-supplied value or the
	// default value.
	else
		m_capacity = std::max(capacity, DEFAULT_CAPACITY);

	// The same principles apply to the logic for setting the load factor.
	if (maxLoadFactor < 0 || maxLoadFactor >= DBL_MAX)
		m_maxLoadFactor = DEFAULT_LOAD_FACTOR;
	else
		m_maxLoadFactor = maxLoadFactor;

	m_threshold = static_cast<int>(m_capacity * m_maxLoadFactor);
	m_table = new std::list<Entry<K, V>>[m_capacity];
}

// Copy constructor.
// Copies data from other, so that this object is a reflection
// of other, but it owns its own memory for the data.
template <typename K, typename V>
ChainedHashTable<K, V>::ChainedHashTable(const ChainedHashTable& other) {
	m_maxLoadFactor = other.m_maxLoadFactor;
	m_capacity = other.m_capacity;
	m_threshold = other.m_threshold;
	m_size = other.m_size;

	// Create a table of the same size
	m_table = new std::list<Entry<K, V>>[m_capacity];

	// Copy contents from source table to this.
	// Process through all the linked lists in the
	// current hashtable structure, looking for non-empty buckets.
	for (int i = 0; i < other.m_capacity; i++) {
		if (!other.m_table[i].empty()) {
			// If this bucket is not empty, process all its entries
			for (Entry<K, V> entry : other.m_table[i]) {
				// Calculate the bucket index
				int bucketIndex = normaliseIndex(entry.hash);

				// Insert this entry into the new table
				m_table[bucketIndex].push_back(entry);
			}			
		}
	}	// end of for-loop copying bucket contents from other table
}

// Move constructor.
// Allows this object takes over ownership of other's resources, so they can
// be set to empty without worrying about data loss or memory leaks.
template <typename K, typename V>
ChainedHashTable<K, V>::ChainedHashTable(ChainedHashTable&& other) noexcept :
	m_maxLoadFactor{ std::exchange(other.m_maxLoadFactor, {}) },
	m_capacity{ std::exchange(other.m_capacity, {}) },
	m_threshold{ std::exchange(other.m_threshold, {}) },
	m_size{ std::exchange(other.m_size, {}) },
	m_table{ std::exchange(other.m_table, {}) }
{ }


// Copy assignment operator.
// Copy the other table into a temporary object and swap that temporary object's
// contents with this table's contents.
template <typename K, typename V>
ChainedHashTable<K, V>& ChainedHashTable<K, V>::operator=(const ChainedHashTable& other) {
	ChainedHashTable<K, V> temp(other);
	swap(temp);
	return *this;
}


// Move assignment operator.
// Move the other table into a temporary object and swap that temporary object's
// contents with this table's contents.
template <typename K, typename V>
ChainedHashTable<K, V>& ChainedHashTable<K, V>::operator=(ChainedHashTable&& other) noexcept {
	ChainedHashTable<K, V> temp(std::move(other));
	swap(temp);
	return *this;
}

// Destructor
template <typename K, typename V>
ChainedHashTable<K, V>::~ChainedHashTable() {
	clear();
}

// Utility function to swap elements from one object to another
// (used by assignment operators).
template <typename K, typename V>
void ChainedHashTable<K, V>::swap(ChainedHashTable<K, V>& other) {
	using std::swap;
	swap(m_maxLoadFactor, other.m_maxLoadFactor);
	swap(m_capacity, other.m_capacity);
	swap(m_threshold, other.m_threshold);
	swap(m_size, other.m_size);
	swap(m_table, other.m_table);
}

/*****************************************************************************************/

// Other Public Member Functions
// -----------------------------


// Returns number of elements inside this hashtable.
template <typename K, typename V>
int ChainedHashTable<K, V>::size() {
	return m_size;
}


// Returns true if this hash table is empty, else returns false.
template <typename K, typename V>
bool ChainedHashTable<K, V>::isEmpty() {
	return (size() == 0);
}


// Clears all the contents of this hash table.
// Note that the table retains the capacity and the same threshold.
// 
// An alternative approach is to completely reset the table to its default
// state (as per the constructor), but this does make this operation more
// expensive, as that entails freeing and re-allocating memory.
// 
// Instead just retain the existing memory being managed here.
// We are clearing out the buckets here, but the underlying linked list
// will handle the memory operations for that.
template <typename K, typename V>
void ChainedHashTable<K, V>::clear() {
	// Reset the table to empty
	for (int i = 0; i < m_capacity; i++)
		m_table[i].clear();					// Clear each linked list
	
	m_size = 0;	// Reset the size to zero						
}


// Returns true if key is in the hashtable, else returns false.
template <typename K, typename V>
bool ChainedHashTable<K, V>::containsKey(K key) {
	return hasKey(key);
}


// Returns true if key is in the hashtable, else returns false.
template <typename K, typename V>
bool ChainedHashTable<K, V>::hasKey(K key) {
	int bucketIndex = normaliseIndex(std::hash<K>{}(key));

	// Is an entry for this key found within the linked list (the bucket) 
	// applicable to this key?
	return (bucketSeekEntry(bucketIndex, key) != std::end(m_table[bucketIndex]));
}


// Searches the hashtable for the value associated with key and returns 
// if found, else returns null if key is not found.
template <typename K, typename V>
std::optional<V> ChainedHashTable<K, V>::get(K key) {
	int bucketIndex = normaliseIndex(std::hash<K>{}(key));
	typename std::list<Entry<K, V>>::iterator existingEntry;
	existingEntry = bucketSeekEntry(bucketIndex, key);

	if (existingEntry != std::end(m_table[bucketIndex])) {
		Entry<K, V> entry = *existingEntry;
		return entry.value;
	}
	return {};
}


template <typename K, typename V>
V ChainedHashTable<K, V>::insert(K key, V value) {
	Entry<K, V> newEntry(key, value);
	int bucketIndex = normaliseIndex(std::hash<K>{}(key));
	return bucketInsertEntry(bucketIndex, newEntry);
}



// If the hashtable entry specified by key is found in the bucket 
// specified by bucketIndex, the entry is removed from the table
// and its value returned.
// Otherwise, a null value is returned.
template <typename K, typename V>
std::optional<V> ChainedHashTable<K, V>::remove(K key) {
	int bucketIndex = normaliseIndex(std::hash<K>{}(key));
	return bucketRemoveEntry(bucketIndex, key);
}


// Prints all the entries in the hashtable.
// Not a method that you'd typically want on a public interface
// but it is useful for testing the functionality here.
// It passes off the real work to a private helper method to make
// things at this level look a bit cleaner.
template <typename K, typename V>
void ChainedHashTable<K, V>::print() {
	printTableContents();
}

/****************************************************************************************/

// Chained Hash Table Private Member Definitions
// --------------------------------------------

// If the entry does not already exist in the bucket at bucketIndex, 
// the entry is inserted and its value returned.
// 
// If the entry already exists in the bucket at bucketIndex, there is
// a check to see if that existing entry's value differs from the proposed
// new value. If there is a change, the value for that entry in the bucket 
// is updated and the previous entry value is returned. 
// 
// Otherwise, there is no change to existing bucket values and the 
// entry value is returned.
template <typename K, typename V>
V ChainedHashTable<K, V>::bucketInsertEntry(int bucketIndex, Entry<K, V> entry) {
	// Check if the entry already exists in the bucket.
	typename std::list<Entry<K, V>>::iterator existingEntry;
	existingEntry = bucketSeekEntry(bucketIndex, entry.key);

	if (existingEntry != std::end(m_table[bucketIndex])) {
		// If the entry is found, check if it differs from the proposed new value
		Entry<K, V> foundEntry = *existingEntry;

		// Only update if the data has actually been changed
		if (!(foundEntry == entry)) {
			foundEntry.value = entry.value;			// Update the current value	
			*existingEntry = foundEntry;
		}
		return foundEntry.value;
	}

	// If entry not found, add it to the bucket
	m_table[bucketIndex].push_back(entry);
	if (++m_size > m_threshold)
		resizeTable();

	return entry.value;
}


// If the entry specified by key is found in the bucket specified
// by bucketIndex.
template <typename K, typename V>
std::optional<V> ChainedHashTable<K, V>::bucketRemoveEntry(int bucketIndex, K key) {
	// Check if the entry exists in the bucket.
	typename std::list<Entry<K, V>>::iterator removalEntry;
	removalEntry = bucketSeekEntry(bucketIndex, key);

	if (removalEntry != std::end(m_table[bucketIndex])) {
		// The entry to be removed has been found
		// Save the entry data
		Entry<K, V> entry = *removalEntry;

		// Remove entry from the relevant bucket	
		m_table[bucketIndex].erase(removalEntry);
		--m_size;					// Decrement size
		return entry.value;			// Return entry value		
	}

	return{};	// Return null if entry not found
}


// Searches the bucket specified by bucketIndex and returns an iterator to the entry 
// specified by key.
// If the entry is not found, the iterator points to element past the end of the bucket.
template <typename K, typename V>
std::list<Entry<K, V>>::iterator ChainedHashTable<K, V>::bucketSeekEntry(int bucketIndex, K key) {
	// Note: use of typename keyword to allow compilation of declaration of iterator.
	// Dependent type name
	typename std::list<Entry<K, V>>::iterator it;

	for (it = m_table[bucketIndex].begin();
		it != m_table[bucketIndex].end(); it++) {
		if (it->key == key)
			break;
	}
	return it;
}


// Converts a hash value to an index.
// Essentially, this strips the negative sign and places the hash value
// in the domain [0, capacity)
template <typename K, typename V>
int ChainedHashTable<K, V>::normaliseIndex(int keyHash) {
	return (keyHash & 0x7FFFFFFF) % m_capacity;
}


// Resizes this hashtable, increasing the capacity by a factor of 2.
// Processes through all entries in the existing hashtable and 
// reinserts them into the new, larger hashtable, before
// deleting the old hashtable. 
template <typename K, typename V>
void ChainedHashTable<K, V>::resizeTable() {
	int existingCapacity = m_capacity;	// Save the current capacity
	m_capacity *= 2;					// Double the current capacity

	// Recalculate the threshold based on this new capacity
	m_threshold = static_cast<int>(m_capacity * m_maxLoadFactor);

	// Create a new table with the newly increased capacity
	std::list<Entry<K, V>>* expandedTable = new std::list<Entry<K, V>>[m_capacity];

	// Process through all the linked lists in the
	// current hashtable structure, looking for non-empty buckets.
	for (int i = 0; i < existingCapacity; i++) {
		if (!m_table[i].empty()) {
			// If this bucket is not empty, process all its entries
			for (Entry<K, V> entry : m_table[i]) {
				// Calculate the bucket index
				int bucketIndex = normaliseIndex(entry.hash);

				// Insert this entry into the new table
				expandedTable[bucketIndex].push_back(entry);
			}
			// Clear up old data and memory
			m_table[i].clear();
		}		
	}
	delete[] m_table;
	m_table = expandedTable; // Set to new table with expanded capacity
}


// Prints the entire contents of the hash table.
template <typename K, typename V>
void ChainedHashTable<K, V>::printTableContents() {
	// Process through all the buckets in the table
	std::cout << "Current contents of this hashtable:\n";
	int emptyBuckets = 0;

	for (int i = 0; i < m_capacity; i++) {
		if (!m_table[i].empty()) {
			std::cout << "Contents of bucket " << i << '\n';
			// If this bucket is not empty, process all its entries
			for (Entry<K, V> entry : m_table[i]) {
				std::cout << std::left << std::setw(20) << entry.key;
				std::cout << entry.value << '\n';
			}
			std::cout << '\n';
		}
		else
			emptyBuckets++;
	}

	std::cout << "\nThere are " << emptyBuckets << " empty buckets.\n\n";
}

#endif	// HASH_TABLE_SEPARATE_CHAINING_H

// Dynamic Array
// -------------
//
// This is a C++ implementation of a dynamic array, loosely based on the Java dynamic
// array class demonstrated by William Fiset in his YouTube data structures course
// video (see the test file for more details), but made a template class so it can be 
// used to build classes to store different data types (there are no constraints 
// or restrictions on types).
// 
// It uses raw pointers, to illustrate the dynamic memory management techniques required
// to handle the needs of a dynamic array.
//
// The class is built around an array managed by a pointer that stores the data the
// user wishes to store. The capacity is used internally to represent the actual
// physical size of the array, while the length holds the logical size of the array, 
// i.e. how many meaningful data items the user is currently storing in it. However, 
// both values are available to the user; length via the size() member function, and
// capacity via a member function of the same name.
//
// There are three class invariants:
// 
// 1. The initial capacity can be set by the user via the constructor, but it must be at
//    least one; if set to be less than one, a default will override it to make it ten.
// 2. The length must be zero or higher.
// 3. The length must be less than or equal to the capacity.
//
// Array Bounds
// ------------
//
// One design decision I made with this implementation is to not use any exceptions:
// 
// - contains() returns true or false depending on whether the item to be searched for
//   is found in the array.
// - indexOf() returns -1 if the item it is asked to search for does not exist in the
//   array.
// - remove() searches on an item to remove, but if it is not found, it returns false.
//
// - get() returns the item at the index provided by the user, but there is no bounds
//   checking, so if the user supplies an index that is out of range, they get undefined
//   behaviour (mirrors the subscript [] operator in std::vector).
// - set() does check if the index provided to insert the item is valid, but if it is
//   not, it returns false to indicate a failed insert.
// - removeAt() uses an std::optional as the return type - it removes and returns the 
//   item at the specified index if the index is valid, but if it is not, it returns
//   a null.
//
// contains(), indexOf() and remove() work as perhaps expected, but the other functions 
// are concerned with array bounds and consequently could throw some sort of exception
// if those bounds are breached. However, I felt that this was unnecessary for a 
// couple of reasons:
// 
// 1) The user has the size() function to indicate what the bounds of the array are, so
//    can get the information they need to interact correctly with these functions.
// 2) Exceptions are "noisy" and it seems satisfactory (if not preferable) to indicate
//    failure in a cleaner and quieter fashion.
// 
// 
// The Dynamic Part - Adjusting the Size of the Array
// --------------------------------------------------
// 
// If the array's current capacity is already filled when an add request is made, the
// array capacity is doubled with a new heap memory allocation. The existing elements are 
// reseated in the new array, with the new element tapped onto the end, and the current 
// array memory is released.
//
// If an element is removed, the array size is reduced by one in a new memory allocation, 
// and the existing elements copied over to the new array, with the exception of the 
// to-be-removed element.
//
// The memory allocations and copying involved in these functions do slow them down to 
// linear O(n) time. Arguably the removal function could be amended to not reallocate
// each time and instead have the unused capacity increase by one, but at some point if 
// excess capacity remains unused it should be released. 
// 
// The current approach is a simple one that ensures priorities memory release over 
// minimising allocations (and element copying).
//
// 
// The Special Member Functions
// ----------------------------
//
// I've taken a "Rule of 5" approach here, as the class uses a raw pointer, so
// the copy & move constructors, the copy & move assignment operators, and the
// destructor are all implemented.
// 
// The destructor is fairly straightforward, in that it releases the heap memory for the 
// array and sets the pointer to null.
// 
// The copy and move operations follow the copy-and-swap idiom, so the assignment
// operators are defined in terms of their respective constructors. This approach
// priorities safety over speed; if the memory allocation in a copy assignment
// operation goes wrong, it will leave this object and the object to be copied
// in the state they were in before the operation began (safe), but it does incur extra
// copying, from the other object into a temp object (slow).
// 
// Swap Function
// -------------
// 
// A custom swap function passes ownership of resources to this object from the other
// object passed in. For the copy assignment operator, this is fine, as the other object 
// is itself a copy of the original object passed in, so that copy is no longer needed
// after the end of the assignment operator function. The result is what we want:
// the original object remains as it was, and this object is a copy of it (with a 
// deep copy of the array).
// 
// This also works for the move assignment operator, as this object takes ownership
// of the other object's resources directly, without doing it through an intermediary 
// copy of the object. Presumably the other object is no longer required, so it is not an 
// issue if it is left in an undefined state.
// 
// 
// Future Improvements/To-Do List
// ------------------------------
// 
// There are a number of improvements that could be made to the class, and hopefully I
// will be able to do this in future:
// 
// 1) An initializer_list constructor - particularly useful for a const class, as 
//    currently a const version can only specify the number of items to store, which
//    will be default initialised and once the array is constructed it can do nothing 
//    to modify them.
// 2) Iterators - allow neater traversal of the structure and enable it to be plugged  
//    into standard library algorithms.
// 3) A subscript operator [] - doesn't really add anything in terms of functionality
//    (it would do the same as the get() function), but improves the design.
// 4) Additional functionality similar to std::vector - extra functions like front(), 
//    back(), push_back(), pop_back(), etc. would make the class easier to use.
// 5) Some DRY tidying up may be possible - there a several functions in which items are 
//    copied from one array to another; a utility copy function seems an obvious solution,
//    but it is complicated by the fact that the destination array is not always the
//    one owned by the current object.

#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <iostream>
#include <optional>
#include <utility>

template <typename T>
class DynamicArray {
    static const int DEFAULT_CAPACITY = 10;
    static const int INCREASE_SIZE_FACTOR = 2;
public:
    DynamicArray(int capacity = DEFAULT_CAPACITY);
    DynamicArray(const DynamicArray& other);
    DynamicArray(DynamicArray&& other) noexcept;
    DynamicArray& operator=(const DynamicArray& other);
    DynamicArray& operator=(DynamicArray&& other) noexcept;
    ~DynamicArray();

    int capacity() const;
    int size() const;
    bool isEmpty();
    T get(int index) const;
    bool set(int index, T item);
    void clear();
    void add(const T& item);
    std::optional<T> removeAt(int remove_index);
    bool remove(T remove_item);
    int indexOf(T item) const;
    bool contains(T item) const;
private:
    void expand(int new_capacity);
    void swap(DynamicArray& other);

    int m_length{};   // Length reported to user
    int m_capacity{}; // Actual size of the array (may have more free slots beyond length)   
    T* m_items;       // The array itself
};


// Class Member Definitions
// ------------------------

// Constructor with a default argument for the array capacity.
// This prevents the addition of (and removes the need for) a default constructor.
// 
// An invariant of this class is that the capacity must be at least 1.
// If the user passes a zero or negative argument, the capacity defaults to 10. 
template <typename T>
DynamicArray<T>::DynamicArray(int capacity)
    : m_capacity{ capacity > 0 ? capacity : DEFAULT_CAPACITY } {
    m_items = new T[capacity]; // Allocate capacity * sizeof(T) memory for this array.  
    m_length = 0;              // Length is zero as there are no elements yet.
}

// Copy constructor.
template <typename T>
DynamicArray<T>::DynamicArray(const DynamicArray& other)
    : m_length{ other.m_length }, m_capacity{ other.m_capacity },
    m_items{ (other.m_items == nullptr) ? nullptr : new T[m_capacity] } {
    // If there are elements in other, copy them into this object
    if (m_items) {
        // The compiler complains about a possible buffer overrun using
        // m_length as the loop control variable.
        // The physical size of the array is determined by m_capacity, so
        // using that instead should remove the error.
        // 
        // However, that means that all the physical elements are copied from
        // other to this, but we only really want the logical elements copied.
        // A class invariant is that the length must be less than or equal
        // to the capacity, so as long as this is observed (and it is in the
        // code here), there would not be any issue with a buffer overrun.
        for (int i = 0; i < m_length; ++i)
            m_items[i] = other.m_items[i];
    }
}

// Move constructor
template <typename T>
DynamicArray<T>::DynamicArray(DynamicArray&& other) noexcept :
    m_length{ std::exchange(other.m_length, {}) },
    m_capacity{ std::exchange(other.m_capacity, {}) },
    m_items{ std::exchange(other.m_items, {}) }
{ }


// Copy assignment operator. 
// 
// It takes a copy (temp) of the other object using the copy constructor.
// This means the copy can be safely swapped into this object, without
// disturbing the contents of the other object.
// A reference to this object is returned, while temp dies at the end of this function, 
// and other remains as it was originally.
template <typename T>
DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray& other) {
    DynamicArray<T> temp(other);    // Copy other into temp
    swap(temp);                     // Swap contents of temp into this
    return *this;                   // Return this
}   // temp destroyed here

// Move assignment operator.
// 
// This function takes in the other object by const reference.
// The temp object takes over the ownership of other using the move constructor.
// The contents of the temp object are then swapped into this object.
// A reference to this object is returned, while temp dies at the end of this function, 
// and other is left in an empty but valid state.
template <typename T>
DynamicArray<T>& DynamicArray<T>::operator=(DynamicArray&& other) noexcept {
    DynamicArray<T> temp(std::move(other));    // Move construct temp from other
    swap(temp);                                // Swap contents of temp into this
    return *this;                              // Return this
}   // temp destroyed here


// Define a destructor to free the dynamically allocated memory.
template <typename T>
DynamicArray<T>::~DynamicArray() {
    delete[] m_items;
    m_items = nullptr;
}


// Returns the capacity of this array.
// The capacity is the amount of memory currently allocated to the array.
template <typename T>
int DynamicArray<T>::capacity() const {
    return m_capacity;
}

// Returns the size of this array.
// The size is the number of current elements in the array; i.e. the part of the array
// being actively used, not its entire size.
template <typename T>
int DynamicArray<T>::size() const {
    return m_length;
}


// Returns true if the size of the array (see above definition)
// is zero, else returns false (if positive one or higher).
template <typename T>
bool DynamicArray<T>::isEmpty() {
    return size() == 0;
}


// Returns the element in the array at the specified index.
// No bounds checking - as per the rationale on std::vector 
// (accessing an out-of-bounds index is UB).
// User beware!!
template <typename T>
T DynamicArray<T>::get(int index) const {
    return m_items[index];
}


// Returns true if the item specified is successfully inserted
// at the specified index, else returns false.
// The index argument must be valid for this array for a successful insert.
template <typename T>
bool DynamicArray<T>::set(int index, T item) {
    // Valid index between 0 and m_length - 1
    if (index >= 0 && index < m_length)
        m_items[index] = item;
    else
        return false;
    return true;
}


// Functionality similar to std::vector:
// clears the array of all existing elements, but leaves the 
// capacity unchanged.
template <typename T>
void DynamicArray<T>::clear() {
    // Clear the elements
    for (int i = 0; i < m_length; i++)
        m_items[i] = 0;
    m_length = 0;   // Length resets to zero so user "believes" it's zero
}


// Add a new element to the array.
// If the current capacity is insufficient to handle this, 
// we increase the size of the array (by default it is doubled in size).
template <typename T>
void DynamicArray<T>::add(const T& item) {
    if (m_length == m_capacity)
        expand(m_length * INCREASE_SIZE_FACTOR);
    m_items[m_length++] = item;
}


// Expand method. 
// Resizes the array when additional space is needed (i.e. the existing capacity is used
// and additional elements are being added).
template<typename T>
void DynamicArray<T>::expand(int new_capacity) {
    if (new_capacity <= m_capacity)
        return; // The necessary capacity is already available

    // Otherwise allocate more memory
    T* new_items = new T[new_capacity];

    // Copy the existing items over from the old array to the new array
    for (int i{}; i < m_length; ++i)
        new_items[i] = m_items[i];

    // Release the memory associated with the old array - it's no longer needed
    delete[] m_items;
    m_items = nullptr;

    // Make the current array point to the new array
    m_items = new_items;
    m_capacity = new_capacity;
}


// Places the contents of other into this array.
// 
// This object's capacity and length are taken from the other object;
// other has default values for those fields are they are no longer needed.
// 
// The items array (pointers) are swapped, so that this object assumes 
// ownership of the array managed by other, and vice versa.
// This means that when the other object (referred to by temp in the assignment
// operator functions) is destroyed at the end of those assignment operators
// it frees up the memory hitherto owned by this object's items array.
template <typename T>
void DynamicArray<T>::swap(DynamicArray& other) {
    using std::swap;
    this->m_capacity = std::exchange(other.m_capacity, {});
    this->m_length = std::exchange(other.m_length, {});
    swap(this->m_items, other.m_items);    
}


// Removes the element at the specified index and returns 
// a copy of that element.
template<typename T>
std::optional<T> DynamicArray<T>::removeAt(int remove_index) {
    if (remove_index > m_length)
        return {};   // Index not valid

    T remove_element = m_items[remove_index];   // Get item to be removed

    // Create a new array; the size is one element smaller 
    // than the existing array
    T* new_items = new T[m_length - 1];

    // Copy all elements from the existing array over to the new array
    // EXCEPT the element to be removed.
    for (int i{}, j{}; i < m_length; i++, j++) {
        // j used as index for new array; i used as index for existing array
        if (i == remove_index)
            // Set j back one so it is "one step" behind i.
            // This means the element to be removed is skipped over and the 
            // next iteration picks up with the subsequent element.
            j--;
        else
            new_items[j] = m_items[i];
    }

    // Delete the existing array
    delete[] m_items;
    m_items = nullptr;

    // Now set existing array to point to the new array 
    m_items = new_items;

    // Reduce length by one and also set capacity to this
    m_capacity = --m_length;
    return remove_element;    // Success!
}


// Removes the element specified if found and returns true, 
// else there is no removal and false is returned.
template<typename T>
bool DynamicArray<T>::remove(T remove_item) {
    for (int i = 0; i < m_length; i++) {
        if (m_items[i] == remove_item) {
            removeAt(i);
            return true;
        }
    }
    return false;
}


// Returns the index of the specified item if found;
// else returns -1.
template<typename T>
int DynamicArray<T>::indexOf(T item) const {
    for (int i = 0; i < m_length; i++) {
        if (m_items[i] == item)
            return i;
    }
    return -1;
}


// Returns true if the specified item is contained in this array;
// else returns false.
template<typename T>
bool DynamicArray<T>::contains(T item) const {
    return (indexOf(item) != -1);
}


#endif  // DYNAMIC_ARRAY_H

// Non-member output operator.
// It can get the data it needs to print the array from member functions
// on the public interface, so there is no need to make it a friend function.
template<typename T>
inline std::ostream& operator<<(std::ostream& os, const DynamicArray<T>& array) {
    for (int i{}; i < array.size(); i++)
        os << array.get(i) << " ";
    os << '\n';
    return os;
}
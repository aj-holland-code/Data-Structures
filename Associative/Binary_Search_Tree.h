// Binary Search Tree (BST)
// ------------------------
// 
// This is a C++ implementation of a binary search tree. The core logic is based on the 
// Java priority queue class demonstrated by William Fiset in his YouTube data structures course video 
// (see the test file for more details), however, this a template class. 
// 
// 
// An Associative Data Structure
// -----------------------------
// 
// This implementation is setup to reject any duplicate values, so can be thought
// of as having the characteristics of a set, i.e. it stores a collection of unique
// keys (the elements), sorted by those keys.
// 
// It is actually a fairly straightforward process to turn this into a tree suitable 
// for use as a multiset, i.e. a collection of keys sorted by keys that can be
// duplicates. To do this, we would remove the duplicate check from the add function 
// and adapt it to add in a duplicate element as either a left or right child of 
// the node it duplicates (although this may require shuffling another node to
// maintain the sorted order, depending on where the node being duplicated 
// currently sits in the tree).
// 
// Traversals
// ----------
// 
// Traversing trees can be a quite complicated process, with various approaches to 
// it, each requiring their own specific algorithm. 
// 
// The key traversal techniques are implemented here 
// (pre-, post-, level-, and in-order) and used to print the tree contents, 
// implementing them in both a recursive function and an iterative equivalent,
// to demonstrate the different approaches to the problem.
// 
// Special Member Functions
// ------------------------
// 
// The special member functions for the BST are similar to those in a doubly linked
// list. The copy/swap approach is adopted again here, and the functions are again
// fairly simple implementations of that paradigm barring the copy constructor.
// 
// In the copy constructor, we have to traverse the source tree to access its 
// contents, creating a new node in this tree to mirror each node in the source tree.
// We can use the add() function to add a new node to this tree, but traversing
// the source tree is more complex. 
// 
// I've used the same approach as used in a utility function that performs a level 
// order traversal (iteratively) to print the contents of the tree. It uses 
// an auxiliary data structure (a queue) to keep track of the child nodes of 
// the node currently being processed. The print function simply prints the current
// node in this tree, whereas the copy constructor uses the data from the current 
// node in the source tree to create a new node for this tree.
// 
// Future Improvements
// -------------------
// 
// 1) As just mentioned, the iterative level order print function and the copy
// constructor do the same traversal of a tree, so the code in each is very similar.
// There are subtle differences, which is why I've currently left them with their
// own specific versions of the algorithm used, but ideally there would be some
// utility function that could work for both to remove the code repetition.
// 
// 2) Add iterators.
// 
// 3) The add function uses the contains() function to check if the element to be
// added is a duplicate of any already stored in the tree. The cost of this search
// (usually logarithmic, but potentially up to linear) is a necessary burden in order
// to ensure the tree maintains unique elements.
// 
// However, in the case where the element is not already in the tree, the function is
// walking down the tree to check for the element, returning back up to report that 
// it is not there, then walking back down the tree to actually insert the new
// element, before finally returning to the root and reporting a successful insert.
// 
// Ideally, there would only be one walk up and down the tree, which either results
// in a successful insert or not, rather than potentially repeating the journey.


#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <algorithm>	// For std::max
#include <limits>		// For int min & max in isBinarySearchTree()
#include <optional>		// For functions potentially returning null
#include <queue>		// For level order iterative traversal function
#include <vector>

// Include header for my stack implementation - used here for iterative traversals of the tree
#include "..\Stack\Stack.h"

// Define a node class to hold node data & pointers
template <typename T>
class BSTNode {
public:
	BSTNode(T data) : data{ data } {}
	T data;
	BSTNode* left = nullptr;
	BSTNode* right = nullptr;
};


// Function that creates a new node for elem
// and returns a pointer to that node.
template <class T>
BSTNode<T>* newNode(T elem) {
	BSTNode<T>* temp = new BSTNode(elem);
	temp->data = elem;
	temp->left = nullptr;
	temp->right = nullptr;
	return temp;
}


// Enum for the different types of tree traversal supported in this 
// tree implementation.
enum class TreeTraversalOrder {
	IN_ORDER,
	LEVEL_ORDER,
	PRE_ORDER,
	POST_ORDER
};

// Concept to require the template parameter to have comparison operators.
// These are necessary to allow the elements in the queue to be prioritised.
template <typename T>
concept Comparable = requires(T a) {
	a < 1;
	a <= 1;
	a > 1;
	a >= 1;
	a == 1;
	a != 1;
};


// The class definition for a Binary Search Tree.
template <class T> requires Comparable<T>
class BinarySearchTree {
public:
	BinarySearchTree() = default;
	BinarySearchTree(const BinarySearchTree& other);
	BinarySearchTree(BinarySearchTree&& other) noexcept;
	BinarySearchTree& operator=(const BinarySearchTree& other);
	BinarySearchTree& operator=(BinarySearchTree&& other) noexcept;
	~BinarySearchTree();
	
	bool isBinarySearchTree();
	bool isEmpty();
	int	size();
	bool add(T elem);
	bool remove(T elem);
	bool contains(T elem);
	std::optional<T> find(T elem);
	int	height();
	void print(TreeTraversalOrder traversalOrder);
	void clear();
private:
	void swap(BinarySearchTree& other);
	bool isBSTUtil(BSTNode<T>* node, int minValue, int maxValue);
	BSTNode<T>* addElement(BSTNode<T>* node, T elem);
	bool containsElement(BSTNode<T>* node, T elem);
	BSTNode<T>* findElement(BSTNode<T>* node, T elem);
	BSTNode<T>* removeElement(BSTNode<T>* root, T elem);
	BSTNode<T>* findMin(BSTNode<T>* node);
	BSTNode<T>* findMinIterative(BSTNode<T>* node);
	BSTNode<T>* findMinRecursive(BSTNode<T>* node);
	BSTNode<T>* findMax(BSTNode<T>* node);
	BSTNode<T>* findMaxIterative(BSTNode<T>* node);
	BSTNode<T>* findMaxRecursive(BSTNode<T>* node);
	int findHeight(BSTNode<T>* node);
	void printPreOrder();
	void printPreOrderIteratively();
	void printPreOrderRecursively(BSTNode<T>* node);
	void printInOrder();
	void printInOrderIteratively();
	void printInOrderRecursively(BSTNode<T>* node);
	void printPostOrder();
	void printPostOrderIteratively();
	void printPostOrderRecursively(BSTNode<T>* node);
	void printLevelOrder();
	void printLevelOrderIteratively();
	void printLevelOrderRecursively();
	void processCurrentLevel(BSTNode<T>* node, int current_level);
	void removeBSTNode(BSTNode<T>* node);
private:
	int nodeCount = 0;			// Tracks number of nodes in this BST
	BSTNode<T>* root = nullptr;	// This BST is a rooted tree, hence this root node
};


// Member Function Definitions
// ===========================

// Special Member Functions
// ------------------------

// Copy constructor
template <typename T> requires Comparable<T>
BinarySearchTree<T>::BinarySearchTree(const BinarySearchTree& other) {
	// Use the same logic in the iterative level order print function
	// to traverse the tree. The new object can create new nodes to 
	// reflect those in the other object as the traversal goes, using the 
	// same values and adding those new nodes into the tree.
	BSTNode<T>* currentOther = other.root;
	std::queue<BSTNode<T>*> queue;

	// If other is empty, nothing is pushed onto the queue, so there's 
	// no further processing.
	if (currentOther)
		queue.push(other.root);

	// Continue while at least one undiscovered node
	while (!queue.empty()) {
		currentOther = queue.front();
		queue.pop();
		if (currentOther->left)
			queue.push(currentOther->left);
		if (currentOther->right)
			queue.push(currentOther->right);
		this->add(currentOther->data);
	}
}

// Move constructor
template <typename T> requires Comparable<T>
BinarySearchTree<T>::BinarySearchTree(BinarySearchTree&& other) noexcept :
	nodeCount{ std::exchange(other.nodeCount, {}) },
	root{ std::exchange(other.root, {}) }
{
	std::cout << "Running BST move constructor...\n";
}


// Copy assignment operator
template <typename T> requires Comparable<T>
BinarySearchTree<T>& BinarySearchTree<T>::operator=(const BinarySearchTree& other) {
	std::cout << "Running copy assignment operator...\n";
	BinarySearchTree<T> temp(other);	
	swap(temp);
	return *this;
}

// Move assignment operator
template <typename T> requires Comparable<T>
BinarySearchTree<T>& BinarySearchTree<T>::operator=(BinarySearchTree&& other) noexcept {
	std::cout << "Running move assignment operator...\n";
	BinarySearchTree<T> temp(std::move(other));
	swap(temp);
	return *this;
}


// Private utility function used by the assignment operators.
// Swaps the contents of this object and other.
template <typename T> requires Comparable<T>
void BinarySearchTree<T>::swap(BinarySearchTree& other) {
	// The using declaration enables the compiler to find std::swap 
	// as if it were local function.
	// This allows us to call swap using the unqualified name.
	// ADL then determines that std::swap fits these arguments, 
	// so it won't call this local swap function itself,
	using std::swap;					
	swap(nodeCount, other.nodeCount);	
	swap(root, other.root);
}


// Destructor
template <typename T> requires Comparable<T>
BinarySearchTree<T>::~BinarySearchTree() {
	clear();
}

/******************************************************************************/

// Other Member Functions
// ----------------------


// Returns true if this binary tree is a binary search tree;
// otherwise returns false.
//
// A binary tree is a binary search tree when the value of a node in the left 
// subtree is lower than or equal to the value in the parent node, 
// and the value of the node in the right subtree is higher than the value 
// in the parent node.
template <typename T> requires Comparable<T>
bool BinarySearchTree<T>::isBinarySearchTree() {
	return isBSTUtil(root, std::numeric_limits<int>::max(), std::numeric_limits<int>::min());
}


// Private utility recursive method that checks if the (sub)tree starting
// at node is a binary search tree.
// 
// It is a binary search tree when the node to the left contains
// a value lower than minValue, and the node to the right
// contain a value higher than maxValue.
template <typename T> requires Comparable<T>
bool BinarySearchTree<T>::isBSTUtil(BSTNode<T>* node, int minValue, int maxValue) {
	if (!node)			// Base condition: null node
		return true;

	if ((node->data < minValue && node->data > maxValue)
		&& isBSTUtil(node->left, minValue, node->data)
		&& isBSTUtil(node->right, node->data, maxValue))
		return true;
	else
		return false;
}


// Returns true if this tree has zero nodes; else returns false.
template <class T> requires Comparable<T>
bool BinarySearchTree<T>::isEmpty() {
	return (size() == 0);
}


// Returns the numer of nodes in this tree.
template <class T> requires Comparable<T>
int BinarySearchTree<T>::size() {
	return nodeCount;
}


// Returns false if a node with the same value as elem already
// exists in the tree, but otherwise will return true to indicate
// a successful addition.
template <class T> requires Comparable<T>
bool BinarySearchTree<T>::add(T elem) {
	if (contains(elem))		// Check if the element already exists
		return false;		// Don't add a duplicate element

	// Otherwise add to the tree
	root = addElement(root, elem);
	nodeCount++;
	return true;
}


// Private utility recursive method that adds the element to this tree
// and returns a pointer to the node storing it.
template <class T> requires Comparable<T>
BSTNode<T>* BinarySearchTree<T>::addElement(BSTNode<T>* node, T elem) {
	// Base case: found a leaf node (has no children)
	if (!node)
		node = newNode(elem);
	else {
		// Place the new node to left of current node
		// if its data is lower 
		if (elem < node->data)
			node->left = addElement(node->left, elem);
		else
			// Otherwise its data is higher, so place the 
			// new node to current node's right
			node->right = addElement(node->right, elem);
	}
	return node;
}


// Returns true if the element to be removed is successfully
// removed from this tree; else returns false.
template <typename T> requires Comparable<T>
bool BinarySearchTree<T>::remove(T elem) {
	if (containsElement(root, elem)) {
		root = removeElement(root, elem);	// Perform the removal
		nodeCount--;	// Drop node count by 1 to reflect node removal
		return true;	// Return true to indicate node successfully removed
	}
	return false;	// Else return false	
}


// Private utility method that removes the node containing the element 
// from this tree and returns a pointer to the removed node.
template <typename T> requires Comparable<T>
BSTNode<T>* BinarySearchTree<T>::removeElement(BSTNode<T>* root, T elem) {
	if (!root)
		return root;	// Return immediately if tree empty	

	if (elem < root->data)
		// The node we're looking for holds a lesser value than current node;
		// dig into the left subtree
		root->left = removeElement(root->left, elem);
	else if (elem > root->data)
		// The node we're looking for holds a higher value than current node;
		// dig into the right subtree
		root->right = removeElement(root->right, elem);
	else {
		// This is the node we're looking for - will be removed here.
		// But first determine if it has left, right, both, or no child nodes
		// as that determines what restructuring of the tree is required 
		// after the node is removed.
		if (!root->left) {
			// There is only a right subtree, or no subtree at all.
			// In this case, swap the to-be-removed node with its right child.
			BSTNode<T>* rightChild = root->right;
			delete root; // free the memory associated with the removed node
			return rightChild;
		}
		else if (!root->right) {
			// There is only a left subtree.
			// In this case, swap the to-be-removed node with its left child.
			BSTNode<T>* leftChild = root->left;
			delete root; // free the memory associated with the removed node
			return leftChild;
		}
		else {
			// If the to-be-removed node has two links, its successor can 
			// be either the largest value in its left subtree, or the
			// smallest value in the right subtree.
			// This implementation will take the latter approach.

			// Find leftmost node in right subtree
			BSTNode<T>* tmp = findMin(root->right);
			root->data = tmp->data;	// Swap the data

			// Dig into the right subtree and remove the leftmost node
			// we found and swapped data with, thus removing what is
			// temporarily a duplicate value.
			root->right = removeElement(root->right, tmp->data);
		}
	}
	return root;
}


// Private utility method to find node's leftmost node - i.e.
// the node after node with the smallest value.
// 
// The processing work is done by a further method; this
// allows the option of plugging in a method with either an iterative
// or a recursive approach.
template <typename T> requires Comparable<T>
BSTNode<T>* BinarySearchTree<T>::findMin(BSTNode<T>* node) {
	// return findMinIterative(node);
	return findMinRecursive(node);
}


// Private utility method that iteratively traverses
// to the leftmost node in the (sub)tree and returns
// a pointer to it.
template <typename T> requires Comparable<T>
BSTNode<T>* BinarySearchTree<T>::findMinIterative(BSTNode<T>* node) {
	BSTNode<T>* current = node;
	while (current->left)
		current = current->left;
	return current;
}


// Private utility method that recursively traverses
// to the leftmost node in the (sub)tree and returns
// a pointer to it.
template <typename T> requires Comparable<T>
BSTNode<T>* BinarySearchTree<T>::findMinRecursive(BSTNode<T>* node) {
	if (!node->left)
		// Base condition: leftmost node reached - return pointer to node
		return node;

	// Otherwise continue search in left subtree
	return findMinRecursive(node->left);
}


// Private utility method to find node's rightmost node - i.e.
// the node after node with the highest value.
// 
// The processing work is done by a further method; this
// allows the option of plugging in a method with either an iterative
// or a recursive approach.
template <typename T> requires Comparable<T>
BSTNode<T>* BinarySearchTree<T>::findMax(BSTNode<T>* node) {
	//findMaxIterative(node);
	return findMaxRecursive(node);
}


// Private utility method that iteratively traverses
// to the leftmost node in the (sub)tree and returns
// a pointer to it.
template <typename T> requires Comparable<T>
BSTNode<T>* BinarySearchTree<T>::findMaxIterative(BSTNode<T>* node) {
	BSTNode<T>* current = node;	// Can we eliminate this line/variable? Copy of root not root itself?
	while (current->right)
		current = current->right;
	return current;
}


// Private utility method that recursively traverses
// to the rightmost node in the (sub)tree and returns
// a pointer to it.
template <typename T> requires Comparable<T>
BSTNode<T>* BinarySearchTree<T>::findMaxRecursive(BSTNode<T>* node) {
	if (!node->right)
		// Base condition: rightmost node reached - return pointer to node
		return node;

	// Otherwise continue search in right subtree
	return findMaxRecursive(node->right);
}


// Returns true if the element specified is found in this BST;
// otherwise returns false.
template <typename T> requires Comparable<T>
bool BinarySearchTree<T>::contains(T elem) {
	return containsElement(root, elem);
}


// Private utility method that recursively looks for the specified 
// element in this tree, beginning the search at node.
// Returns true if a node containing the element is found; otherwise returns false.
template <typename T> requires Comparable<T>
bool BinarySearchTree<T>::containsElement(BSTNode<T>* node, T elem) {
	// Base case: reached bottom of tree and the value has not been found
	if (!node)
		return false;

	if (elem < node->data)		// Value lower than current value - go left
		return containsElement(node->left, elem);
	else if (elem > node->data)	// Value higher than current value - go right
		return containsElement(node->right, elem);

	// Value has been found
	return true;
}


// Returns the element specified if found in this BST;
// otherwise returns null.
template <typename T> requires Comparable<T>
std::optional<T> BinarySearchTree<T>::find(T elem) {
	if (findElement(root, elem))
		return elem;
	else
		return {};
}


// Private utility method that recursively looks for the specified element 
// in this BST, beginning the search at node.
// Returns a pointer to the node containing the element if found; 
// otherwise returns a null pointer.
template <typename T> requires Comparable<T>
BSTNode<T>* BinarySearchTree<T>::findElement(BSTNode<T>* node, T elem) {
	// Base case: reached bottom of tree and the value has not been found
	if (!node)
		return nullptr;

	if (elem < node->data)		// Value lower than current value - go left
		return findElement(node->left, elem);
	else if (elem > node->data)	// Value higher than current value - go right
		return findElement(node->right, elem);

	// Value has been found
	return node;
}


// Returns the height of the tree -- an O(n) operation.
template <typename T> requires Comparable<T>
int BinarySearchTree<T>::height() {
	return findHeight(root);
}


// Private utility method that recursively determines the height
// of this tree, rooted at node (node may be the root of the whole tree 
// or the root of a subtree thereof).
// 
// Returns the height as an integer representing the maximum number of levels
// the tree contains. 
// 
// The logic is based on finding the height of each node (subtree) in the tree.
// The height of a subtree is calculated through these steps:
// 1) Find the height of its left subtree.
// 2) Find the height of its right subtree.
// 3) Determine the subtree's maximum height, i.e. the higher of these two heights.
// 4) Add one to the maximum and return that value.
// 
// This is achieved through a traversal of the tree, digging down from each node
// until its leftmost point is reached, and then the same for the right.
// These extreme points are tree boundary or exit points, indicated with a null 
// node. 
// 
// Once the boundary of a subtree has been reached, the traversal heads back up the
// tree. A null node has a height of zero, so return zero for a null node. Once
// the traversal for that node receives these zero values, it adds one for that 
// node, and returns that to the next level up. 
// 
// The traversal eventually arrives back at the root node, where it has, through 
// this accumulative process, the heights of its left and right subtrees. 
// In turn, the maximum of these two heights is determined, and one is added to that
// to allow for the root level itself; this is the final value, representing the
// height of the tree, and so this value is returned to the function caller. 
//
// Time complexity: O(n)
template <typename T> requires Comparable<T>
int BinarySearchTree<T>::findHeight(BSTNode<T>* node) {
	if (!node)	// Leaf node - there are no further levels
		return 0;
	return std::max(findHeight(node->left), findHeight(node->right)) + 1;
}


// Removes all nodes from this tree.
template <typename T> requires Comparable<T>
void BinarySearchTree<T>::clear() {
	// First check if the tree has any nodes.
	// If not there's nothing to do here, so return immediately.
	if (root) {
		// Remove all nodes from root down
		removeBSTNode(root);
		
		// Reset root to null
		root = nullptr;
		nodeCount = 0;	// Reset the node count to zero
	}
}


// Private utility method that removes the subtree represented by
// node from the tree. 
// The memory associated with the nodes in the subtree is freed.
// If node is the root node, the tree will be completely removed.
template <typename T> requires Comparable<T>
void BinarySearchTree<T>::removeBSTNode(BSTNode<T>* node) {
	if (node) {
		// Remove node's subtrees
		removeBSTNode(node->left);
		removeBSTNode(node->right);

		// Remove current node
		delete node;
		node = nullptr;
	}
}


// Prints the entire contents of this BST, using the 
// mode of traversal specified in traversalOrder.
template <typename T> requires Comparable<T>
void BinarySearchTree<T>::print(TreeTraversalOrder traversalOrder) {
	switch (traversalOrder) {
	case TreeTraversalOrder::PRE_ORDER:
		printPreOrder();
		break;
	case TreeTraversalOrder::IN_ORDER:
		printInOrder();
		break;
	case TreeTraversalOrder::POST_ORDER:
		printPostOrder();
		break;
	case TreeTraversalOrder::LEVEL_ORDER:
		printLevelOrder();
		break;
	default:
		return;
	}
	std::cout << "\n\n";
}


// Private utility method that performs a pre-order print of the 
// contents of the tree rooted from node.
// 
// This method calls a further method to do the work; this gives
// the option of activating either the iterative or the recursive 
// traversal approach.
template <typename T> requires Comparable<T>
void BinarySearchTree<T>::printPreOrder() {
	//printPreOrderIteratively(node);
	printPreOrderRecursively(root);
}


// Pre-order traversal but handled with iterative logic.
// It will traverse the left part of a subtree before
// returning to traverse the right part of the subtree.
template <typename T> requires Comparable<T>
void BinarySearchTree<T>::printPreOrderIteratively() {
	BSTNode<T>* current = root;
	Stack<BSTNode<T>*> stack;

	while (current) { // Process until no more nodes in tree
		std::cout << current->data << " ";		// Print first

		if (current->right)
			stack.push(current->right);			// Store right child on stack

		if (current->left)
			// Next node to visit must be left child if there is one
			current = current->left;
		else {
			// No further left nodes - at the bottom of the tree
			// Return to the next unvisited right node (if any)
			if (stack.isEmpty())
				current = nullptr;
			else
				current = stack.pop().value();
		}
	}
}


// Pre-order traversal prints before the recursive calls.
// It will traverse the left part of a subtree before
// returning to traverse the right part of the subtree.
//
// Time complexity:		O(n) all cases
// Space complexity:	O(h) worst case; O(log n) average & worst cases	
template <typename T> requires Comparable<T>
void BinarySearchTree<T>::printPreOrderRecursively(BSTNode<T>* node) {
	if (!node)
		return;

	std::cout << node->data << " ";
	printPreOrderRecursively(node->left);
	printPreOrderRecursively(node->right);
}


// Private utility method that performs an in-order print of the 
// contents of the tree rooted from node.
// 
// This method calls a further method to do the work; this gives
// the option of activating either the iterative or the recursive 
// traversal approach.
template <typename T> requires Comparable<T>
void BinarySearchTree<T>::printInOrder() {
	//printInOrderIteratively();
	printInOrderRecursively(root);
}


// In-order traversal handled with iterative logic.
// Traverse the left part of a subtree before printing, 
// and then traverses the right part of the subtree.
template <typename T> requires Comparable<T>
void BinarySearchTree<T>::printInOrderIteratively() {
	BSTNode<T>* current = root;
	Stack<BSTNode<T>*> stack;

	// Process until no more nodes
	while (current || !stack.isEmpty()) {
		// Traverse to the leftmost node of current node
		while (current) {
			// If current not null, add current to stack
			// and move to the left child
			stack.push(current);
			current = current->left;
		}

		// Reached the leftmost point now, so get the most recently visited node
		current = stack.pop().value();
		std::cout << current->data << " ";

		// Left subtree of current node has been visited and the 
		// current node's data has been printed by this point
		// Now visit the current node's right subtree
		current = current->right;
	}	// end-while (all nodes processed by this point)
}


// In-order traversal prints between the recursive calls.
// Traverse the left part of a subtree before printing, 
// and then traverses the right part of the subtree.
//
// Time complexity:		O(n) all cases
// Space complexity:	O(h) worst case; O(log n) average & worst cases	
template <typename T> requires Comparable<T>
void BinarySearchTree<T>::printInOrderRecursively(BSTNode<T>* node) {
	if (!node)	// Base condition: reached a null node
		return;

	printInOrderRecursively(node->left);
	std::cout << node->data << " ";
	printInOrderRecursively(node->right);
}



// Private utility method that performs a post-order print of the 
// contents of the tree rooted from node.
// 
// This method calls a further method to do the work; this gives
// the option of activating either the iterative or the recursive 
// traversal approach.
template <typename T> requires Comparable<T>
void BinarySearchTree<T>::printPostOrder() {
	//printPostOrderIteratively();
	printPostOrderRecursively(root);
}


// Post-order traversal handled with iterative logic.
// Traverse the left part of a subtree and then traverse
// the right part of the subtree before printing.
template <typename T> requires Comparable<T>
void BinarySearchTree<T>::printPostOrderIteratively() {
	if (!root)
		return;

	BSTNode<T>* current = root;
	Stack<BSTNode<T>*> stack1;
	Stack<BSTNode<T>*> stack2;

	stack1.push(current);			// Push root onto the first to start

	while (!(stack1.isEmpty())) {
		current = stack1.pop().value();		// Get next element to process
		stack2.push(current);				// Push it onto the second stack

		// Push any children of the current node
		// onto the first stack for processing (left first; right second)
		if (current->left)
			stack1.push(current->left);
		if (current->right)
			stack1.push(current->right);
	}

	// All the nodes are in the correct order now on stack 2
	// Simply pop off one by one and print
	while (!(stack2.isEmpty())) {
		current = stack2.pop().value();
		std::cout << current->data << " ";
	}
}


// Post-order traversal prints after the recursive calls.
// Traverse the left part of a subtree and then traverse
// the right part of the subtree before printing.
// 
// Time complexity:		O(n) all cases
// Space complexity:	O(h) worst case; O(log n) average & worst cases	
template <typename T> requires Comparable<T>
void BinarySearchTree<T>::printPostOrderRecursively(BSTNode<T>* node) {
	if (!node)	// Base condition: reached a null node
		return;

	printPostOrderRecursively(node->left);
	printPostOrderRecursively(node->right);
	std::cout << node->data << " ";
}


// Private utility method that prints the contents of the tree in level order.
// 
// Time complexity:		O(n) all cases
// Space complexity:	O(1) best case; O(n) average & worst cases 
template <typename T> requires Comparable<T>
void BinarySearchTree<T>::printLevelOrder() {
	if (!root)		// If the tree is empty there's nothing to print
		return;

	// Choose either a recursive or an iterative approach
	printLevelOrderIteratively();
	//printLevelOrderRecursively();
}


// Private utility method that prints the contents of the tree in level order.
// 
// Time complexity:		O(n) all cases
// Space complexity:	O(1) best case; O(n) average & worst cases 
template <typename T> requires Comparable<T>
void BinarySearchTree<T>::printLevelOrderIteratively() {
	std::queue<BSTNode<T>*> queue;
	queue.push(root);

	// Continue while at least one undiscovered node
	while (!queue.empty()) {
		BSTNode<T>* current = queue.front();
		queue.pop();
		if (current->left)
			queue.push(current->left);
		if (current->right)
			queue.push(current->right);
		std::cout << current->data << " ";
	}
}


// Private utility method that prints the contents of the tree in level order.
// This version of the method uses recursive logic (within a further
// helper method called here).
template <typename T> requires Comparable<T>
void BinarySearchTree<T>::printLevelOrderRecursively() {
	int height = findHeight(root);

	for (int current_level = 0; current_level < height; current_level++)
		processCurrentLevel(root, current_level);
}


// Private utility method that prints the contents of the tree in level order.
// This version of the method uses recursive logic (within a further
// helper method called here).
template <typename T> requires Comparable<T>
void BinarySearchTree<T>::processCurrentLevel(BSTNode<T>* node, int current_level) {
	if (!node)
		return;

	if (current_level == 0)
		std::cout << node->data << " ";
	else if (current_level > 0) {
		processCurrentLevel(root->left, current_level - 1);
		processCurrentLevel(root->right, current_level - 1);
	}
}

#endif	// BINARY_SEARCH_TREE_H


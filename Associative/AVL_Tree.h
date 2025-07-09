// AVL Tree
// --------
// 
// This is a C++ implementation of a balanced binary search tree, specifically
// and AVL tree. The core logic is based on the Java AVL class demonstrated by 
// William Fiset in his YouTube data structures course video 
// (see the test file for more details), however, this version has been amended and
// enhanced, not least because it is a template class.
// 
// Much of the logic is similar to the ordinary binary search tree implementation, 
// however, I have altered the insert function here so that it doesn't do an initial
// check for duplicates. If the value to be inserted is already in the tree, this is
// discovered only when performing the insert, but if that is the case, the value is
// rejected and a null pointer is returned to signal the insert has failed.
// 
// The same principle has been applied to the removal operation, with a slight adjustment
// to allow for the fact that a null pointer does not indicate a failure in all removal
// cases (see comments in the remove() and removeHelper() functions for more details).

#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <concepts>
#include <queue>
#include <utility>			// For std::exchange

// The AVL tree node class. 
// Implements PrintableNode methods.
template <typename T>
class AVL_Node {
public:
	AVL_Node(T value) : data{ value } {}
	T data{};
	int balanceFactor{};
	int height{};
	AVL_Node* left{};
	AVL_Node* right{};	
};


// Enum for the different types of tree traversal supported in this 
// tree implementation.
enum class TraversalTreeOrder {
	IN_ORDER,
	LEVEL_ORDER,
	PRE_ORDER,
	POST_ORDER
};

// Concept to require the template parameter to have comparison operators.
// These are necessary to allow the elements in the queue to be found/inserted/removed 
// at/in/from the correct place in the tree,
template <typename T>
concept Comparable = requires(T a) {
	a < a;	
	a > a;
};


// The AVL Tree class.
template<typename T> requires Comparable<T>
class AVL_Tree {	
public:
	AVL_Tree() = default;
	AVL_Tree(const AVL_Tree& other);
	AVL_Tree(AVL_Tree&& other) noexcept;
	AVL_Tree& operator=(const AVL_Tree& other);
	AVL_Tree& operator=(AVL_Tree&& other) noexcept;
	~AVL_Tree();

	void clear();
	bool isEmpty();
	int height();
	int size();
	bool contains(T value);
	bool insert(T value);
	bool remove(T value);
	bool validateBST();
	void print(TraversalTreeOrder traversalOrder);
private:
	void swap(AVL_Tree& other);
	void removeAVLNode(AVL_Node<T>* node);
	bool containsHelper(AVL_Node<T>* node, T value);
	AVL_Node<T>* insertHelper(AVL_Node<T>* node, T value);
	AVL_Node<T>* removeHelper(AVL_Node<T>* node, T value, bool& nodeRemoved);
	void update(AVL_Node<T>* node);
	AVL_Node<T>* balance(AVL_Node<T>* node);
	AVL_Node<T>* leftLeftCase(AVL_Node<T>* node);
	AVL_Node<T>* leftRightCase(AVL_Node<T>* node);;
	AVL_Node<T>* rightLeftCase(AVL_Node<T>* node);
	AVL_Node<T>* rightRightCase(AVL_Node<T>* node);
	AVL_Node<T>* leftRotation(AVL_Node<T>* pivotNode);
	AVL_Node<T>* rightRotation(AVL_Node<T>* pivotNode);
	T findMin(AVL_Node<T>* node);
	T findMax(AVL_Node<T>* node);
	bool validateBSTInvariant(AVL_Node<T>* node);
	void printPreOrder(AVL_Node<T>* node);
	void printPostOrder(AVL_Node<T>* node);
	void printLevelOrder(AVL_Node<T>* node);
	void printInOrder(AVL_Node<T>* node);	
private:
	int nodeCount = 0;				// Tracks number of nodes in this AVL tree
	AVL_Node<T>* root = nullptr;	// The root of this AVL tree
};


// Member Function Definitions
// ===========================

// Special Member Functions
// ------------------------

// Copy constructor
template <typename T> requires Comparable<T>
AVL_Tree<T>::AVL_Tree(const AVL_Tree& other) {
	AVL_Node<T>* currentOther = other.root;
	std::queue<AVL_Node<T>*> queue;

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
		this->insert(currentOther->data);
	}
}

// Move constructor
template <typename T> requires Comparable<T>
AVL_Tree<T>::AVL_Tree(AVL_Tree&& other) noexcept :
	nodeCount{std::exchange(other.nodeCount, {})}, 
	root{ std::exchange(other.root, {}) }
{ }

// Copy assignment operator
template <typename T> requires Comparable<T>
AVL_Tree<T>& AVL_Tree<T>::operator=(const AVL_Tree& other) {
	AVL_Tree<T> temp(other);
	swap(temp);
	return *this;
}

// Move assignment operator
template <typename T> requires Comparable<T>
AVL_Tree<T>& AVL_Tree<T>::operator=(AVL_Tree&& other) noexcept {
	AVL_Tree<T> temp(std::move(other));
	swap(temp);
	return *this;
}


// Private utility function used by the assignment operators.
// Swaps the contents of this object and other.
template <typename T> requires Comparable<T>
void AVL_Tree<T>::swap(AVL_Tree& other) {
	using std::swap;
	swap(this->nodeCount, other.nodeCount);
	swap(this->root, other.root);
}


template <typename T> requires Comparable<T>
AVL_Tree<T>::~AVL_Tree() {
	clear();
}

/***************************************************************************/

// Other Member Functions
// ----------------------

// Removes all nodes from this tree.
template <typename T> requires Comparable<T>
void AVL_Tree<T>::clear() {
	// Check if the tree is empty first (in which case there's nothing to do)
	if (root) {
		removeAVLNode(root);

		root = nullptr; 	// Reset root to null
		nodeCount = 0;		// Reset the node count to zero
	}
}


// Returns true if the tree is empty (has zero nodes),
// else returns false.
template <typename T> requires Comparable<T>
bool AVL_Tree<T>::isEmpty() {
	return size() == 0;
}


// Returns the height of the tree.
// The height of a rooted tree is the number of edges between the tree's root and
// its farthest leaf. 
// This means a tree containing a single node has a height of 0.
template <typename T> requires Comparable<T>
int AVL_Tree<T>::height() {
	if (!root)
		return 0;
	return root->height;
}


// Returns the number of nodes in this tree.
template <typename T> requires Comparable<T>
int AVL_Tree<T>::size() {
	return nodeCount;
}


// Returns true if there is a node containing value in this tree;
// else returns false.
template <typename T> requires Comparable<T>
bool AVL_Tree<T>::contains(T value) {
	return containsHelper(root, value);
}


// Inserts value into a new node in this tree -- O(log(n)).
// 
// Note: this method does NOT perform a contains search first to eliminate any
// potential duplicates; the walk down the tree is done entirely in the
// helper method (so the tree is only traversed once for this
// transaction). 
// 
// This means it must identify during the actual insertion process whether the value
// is already in the tree and if it is, have some mechanism to report back that there is no
// newly inserted node. This comes in the form of a null pointer.
template <typename T> requires Comparable<T>
bool AVL_Tree<T>::insert(T value) {
	AVL_Node<T>* newRoot = insertHelper(root, value);
	if (!newRoot)
		return false;

	// Insert successful - update node count and root and return true
	nodeCount++;
	root = newRoot;
	return true;
}



// If value exists in this tree, remove it from the tree - O(log(n)).
template <typename T> requires Comparable<T>
bool AVL_Tree<T>::remove(T value) {
	bool nodeRemoved = false;

	// Use a boolean flag (nodeRemoved) to determine if the node
	// has actually been removed or not, rather than relying on the
	// memory address of the returned node pointer itself. 
	// 
	// Normally, getting a null pointer back indicates that the removal
	// has failed (i.e. the node doesn't actually exist in the tree in
	// the first place).
	// 
	// However, there is an exception case: if the tree only has a root node
	// and there is a call to remove that root node, a null pointer is 
	// returned here (so that the root node ends up pointing to null,
	// representing an empty tree).
	// 
	// Therefore the logic here needs to allow for the fact that a null 
	// pointer isn't necessarily a sign the removal has failed. 
	// Having a separate flag allows the function to circumvent the 
	// need to do an existence check for the node first before actually
	// deleting it (or not).
	AVL_Node<T>* newRoot = removeHelper(root, value, nodeRemoved);

	if (!nodeRemoved)
		// No node removed - return false
		return false;

	// Otherwise remove successful - update node count and root and return true
	nodeCount--;
	root = newRoot;
	return true;
}


// Public method, but only used for testing.
// Validates that a tree fulfils the basic BST invariant
// (left nodes smaller than node; right nodes larger than node).
// Returns true if that is the case, else returns false.
//
// The work is done in a private helper method.
// This allows us to pass in whatever node we like to that method to 
// check. 
// 
// In this public method calling it, we are passing in the root
// so this will check the validity of the entire tree.
template <typename T> requires Comparable<T>
bool AVL_Tree<T>::validateBST() {
	return validateBSTInvariant(root);
}


// Prints the entire contents of this AVL Tree, using the 
// mode of traversal specified in traversalOrder.
template <typename T> requires Comparable<T>
void AVL_Tree<T>::print(TraversalTreeOrder traversalOrder) {
	switch (traversalOrder) {
	case TraversalTreeOrder::PRE_ORDER:
		printPreOrder(root);
		break;
	case TraversalTreeOrder::IN_ORDER:
		printInOrder(root);
		break;
	case TraversalTreeOrder::POST_ORDER:
		printPostOrder(root);
		break;
	case TraversalTreeOrder::LEVEL_ORDER:
		printLevelOrder(root);
		break;
	default:
		return;
	}
	std::cout << "\n\n";
}


/***************************************************************************/

// Private Utility/Helper Functions
// --------------------------------

// Private utility method that removes nodes from this tree 
// and frees the memory associated with them.
template <typename T> requires Comparable<T>
void AVL_Tree<T>::removeAVLNode(AVL_Node<T>* node) {
	if (node) {
		// Recursively remove node's subtrees
		removeAVLNode(node->left);
		removeAVLNode(node->right);

		// Current node - scrub its data
		node->data = {};
		node->balanceFactor = 0;
		node->height = 0;
		node->left = nullptr;
		node->right = nullptr;

		// Current node - deallocate its memory
		delete node;
		node = nullptr;
	}
}


// Private utility method that returns true if this subtree (rooted at node) 
// contains a node with the same data value as the parameter value; 
// otherwise returns false.
template<typename T> requires Comparable<T>
bool AVL_Tree<T>::containsHelper(AVL_Node<T>* node, T value) {
	if (!node)			// Base case
		return false;	// If value not found in tree

	if (value < node->data)	     // Value less than current node's value, dig left
		return containsHelper(node->left, value);
	else if (value > node->data) // Value is greater, dig right
		return containsHelper(node->right, value);

	return true;		// If value is found in tree
}


// Private utility method to insert a new node containing value into this tree, 
// if it does not already exist in this tree.
// 
// If the insert is successful, the new (or old) root node is returned.
// If the insert is unsuccessful, null is returned.
template<typename T> requires Comparable<T>
AVL_Node<T>* AVL_Tree<T>::insertHelper(AVL_Node<T>* node, T value) {
	if (!node) { // Base case 
		AVL_Node<T>* newNode = new AVL_Node<T>(value);
		return newNode;
	}

	// If the value is less than the value in the node, insert in left subtree.
	if (value < node->data) {
		// Store the result of insert left in separate variable
		AVL_Node<T>* newLeftNode = insertHelper(node->left, value);
		if (!newLeftNode) 
			// Value has been discovered to be a duplicate.
			// Propagate the null back up the tree.
			// Nodes will retain their existing left node.
			return newLeftNode;

		// Otherwise a successful update.
		// Use stored result to be this node's new left node.
		node->left = newLeftNode;
	}
	// If the value is greater than the value in the node, insert in right subtree.
	else if (value > node->data) {
		AVL_Node<T>* newRightNode = insertHelper(node->right, value);
		if (!newRightNode)
			// Value has been discovered to be a duplicate.
			// Propagate the null back up the stack.
			// Nodes will retain their existing right node.
			return newRightNode;

		// Otherwise a successful update.
		// Use stored result to be this node's new right node.
		node->right = newRightNode;
	}
	else
		// Values are equal - duplicate value found -- return null
		return nullptr;

	// AVL Tree specific functionality (not found in an ordinary BST insert):
	update(node);			// Update balance factor and height values
	return balance(node);	// Re-balance the tree	
}


// Private utility method that removes the node containing value from 
// the tree (if it exists in the tree in the first place).
template<typename T> requires Comparable<T>
AVL_Node<T>* AVL_Tree<T>::removeHelper(AVL_Node<T>* node, T value, bool& nodeRemoved) {
	// Step 1: Perform standard node removal (as per ordinary BST)
	if (!node)
		return node;	// Base case - return null

	// If the value to be deleted is smaller than this node's value
	// it can only be found in its left subtree.
	if (value < node->data)
		node->left = removeHelper(node->left, value, nodeRemoved);

	// If the value to be deleted is greater than this node's value
	// it can only be found in its right subtree.
	else if (value > node->data)
		node->right = removeHelper(node->right, value, nodeRemoved);

	// Otherwise, the values must be equal. 
	// This means the node to be deleted has been found.
	else {
		// This is the case with only a right subtree, or no subtree at all.
		// Simply swap the node to be removed with its right child.
		if (!node->left) {
			AVL_Node<T>* rightChild = node->right;
			delete node;		// Free the memory for the node being removed
			nodeRemoved = true;	// Set removal flag
			return rightChild;
		}

		// This is the case with only a left subtree, or no subtree at all.
		// In this situation, swap the node to be removed with its left child.
		else if (!node->right) {
			AVL_Node<T>* leftChild = node->left;
			delete node;		// Free the memory for the node being removed
			nodeRemoved = true;	// Set removal flag
			return leftChild;
		}

		// When removing a node from a binary tree with two links the
		// successor of the node being removed can either be the largest
		// value in the left subtree or the smallest value in the right
		// subtree. Going here with removing the subtree with
		// the greatest height in hopes that this may help with balancing.
		else {
			// Choose to remove from left subtree
			if (node->left->height > node->right->height) {
				// Swap the value of the successor into the node
				T successorValue = findMax(node->left);
				node->data = successorValue;

				// Find the largest node in the left subtree
				node->left = removeHelper(node->left, successorValue, nodeRemoved);
			}
			else {
				// Swap the value of the successor into the node.
				T successorValue = findMin(node->right);
				node->data = successorValue;

				// Go into the right subtree and remove the leftmost node we
				// found and swapped data with. This prevents two
				// nodes in the tree having the same value.
				node->right = removeHelper(node->right, successorValue, nodeRemoved);
			}
		}
	} // end of else (node found)

	// Step 2: Update balance factor and height
	update(node);

	// Step 3: Re-balance tree
	return balance(node);
}


// Private utility method that updates a node's height and balance factor.
// However, if the node is null, return immediately.
template<typename T> requires Comparable<T>
void AVL_Tree<T>::update(AVL_Node<T>* node) {
	if (!node)
		return;

	// Get height of left and right subtrees of this node
	int leftNodeHeight = (node->left) ? node->left->height : -1;
	int rightNodeHeight = (node->right) ? node->right->height : -1;

	// Update this node's height
	node->height = 1 + std::max(leftNodeHeight, rightNodeHeight);

	// Update this node's balance factor
	node->balanceFactor = rightNodeHeight - leftNodeHeight;
}


// Private utility method that re-balances a node if its 
// balance factor is +2 or -2, in which case the tree invariant
// regarding balanced nodes has been disrupted and so tree rotations are required
// to restore it. However, if the node is null, nothing is done.
template<typename T> requires Comparable<T>
AVL_Node<T>* AVL_Tree<T>::balance(AVL_Node<T>* node) {
	if (!node)
		return nullptr;

	// Indicates a left-heavy subtree
	if (node->balanceFactor == -2) {
		// Left-Left case
		if (node->left->balanceFactor <= 0)
			return leftLeftCase(node);
		// Left-Right case
		else
			return leftRightCase(node);
	}
	// Indicates a right-heavy subtree
	else if (node->balanceFactor == 2) {
		// Right-Right case
		if (node->right->balanceFactor >= 0)
			return rightRightCase(node);
		// Right-Left case
		return rightLeftCase(node);
	}

	// Otherwise, the node either has a balance factor of -1, 0, or +1, 
	// all of which are acceptable, so no processing is needed.
	return node;
}


template<typename T> requires Comparable<T>
AVL_Node<T>* AVL_Tree<T>::leftLeftCase(AVL_Node<T>* node) {
	return rightRotation(node);
}


// The left-right case 'degrades' to the left-left case
// after a single left rotation.
template<typename T> requires Comparable<T>
AVL_Node<T>* AVL_Tree<T>::leftRightCase(AVL_Node<T>* node) {
	node->left = leftRotation(node->left);
	return leftLeftCase(node);
}


template<typename T> requires Comparable<T>
AVL_Node<T>* AVL_Tree<T>::rightRightCase(AVL_Node<T>* node) {
	return leftRotation(node);
}


// Private utility method
// The right-left case 'degrades' to the right-right case
// after a single right rotation.
template<typename T> requires Comparable<T>
AVL_Node<T>* AVL_Tree<T>::rightLeftCase(AVL_Node<T>* node) {
	node->right = rightRotation(node->right);
	return rightRightCase(node);
}


// Private utility method
template<typename T> requires Comparable<T>
AVL_Node<T>* AVL_Tree<T>::leftRotation(AVL_Node<T>* pivotNode) {
	AVL_Node<T>* pivotNewParent = pivotNode->right;
	pivotNode->right = pivotNewParent->left;
	pivotNewParent->left = pivotNode;

	// Pivot node is now lower on the tree (than its new parent), 
	// so it must be updated for height and balance factor first.
	update(pivotNode);

	// Update new parent for height and balance after pivot,
	// since new parent is now higher that pivot on the tree.
	update(pivotNewParent);
	return pivotNewParent;
}


// Private utility method.
template<typename T> requires Comparable<T>
AVL_Node<T>* AVL_Tree<T>::rightRotation(AVL_Node<T>* pivotNode) {
	AVL_Node<T>* pivotNewParent = pivotNode->left;
	pivotNode->left = pivotNewParent->right;
	pivotNewParent->right = pivotNode;

	// Pivot node is now lower on the tree (than its new parent), 
	// so it must be updated for height and balance factor first
	update(pivotNode);

	// Update new parent for height and balance after pivot,
	// since new parent is now higher that pivot on the tree.
	update(pivotNewParent);
	return pivotNewParent;
}


// Private utility method that finds the leftmost node of node
// (i.e. node with smallest value).
template<typename T> requires Comparable<T>
T AVL_Tree<T>::findMin(AVL_Node<T>* node) {
	while (node->left)
		node = node->left;
	return node->data;
}


// Private utility method that finds the rightmost node of node
// (i.e. node with largest value).
template<typename T> requires Comparable<T>
T AVL_Tree<T>::findMax(AVL_Node<T>* node) {
	while (node->right)
		node = node->right;
	return node->data;
}



// Private utility method used for testing.
// 
// Checks if the key BST invariant is upheld in this tree, rooted at node: 
// all left child nodes are smaller in value than their parent;
// all right child node are larger in value than their parent.
//
// Returns true if this is the case, else returns false.
template<typename T> requires Comparable<T>
bool AVL_Tree<T>::validateBSTInvariant(AVL_Node<T>* node) {
	if (!node)
		return true;

	T data = node->data;
	bool isValid = true;

	if (node->left)
		isValid = isValid && node->left->data < data;
	if (node->right)
		isValid = isValid && node->right->data > data;

	return (isValid
		&& validateBSTInvariant(node->left)
		&& validateBSTInvariant(node->right));
}


// Pre-order traversal prints before the recursive calls.
// It will traverse the left part of a subtree before
// returning to traverse the right part of the subtree.
//
// Time complexity:		O(n) all cases
// Space complexity:	O(h) worst case; O(log n) average & worst cases	
template<typename T> requires Comparable<T>
void AVL_Tree<T>::printPreOrder(AVL_Node<T>* node) {
	if (!node)
		return;

	std::cout << node->data << " ";
	printPreOrder(node->left);
	printPreOrder(node->right);
}


// Private utility method that performs an in-order print of the 
// contents of the tree rooted from node.
// 
// In-order traversal prints between the recursive calls.
// Traverse the left part of a subtree before printing, 
// and then traverses the right part of the subtree.
//
// Time complexity:		O(n) all cases
// Space complexity:	O(h) worst case; O(log n) average & worst cases	
template<typename T> requires Comparable<T>
void AVL_Tree<T>::printInOrder(AVL_Node<T>* node) {
	if (!node)	// Base condition: reached a null node
		return;

	printInOrder(node->left);
	std::cout << node->data << " ";
	printInOrder(node->right);
}


// Private utility method that performs a post-order print of the 
// contents of the tree rooted from node.
// 
// Post-order traversal prints after the recursive calls.
// Traverse the left part of a subtree and then traverse
// the right part of the subtree before printing.
// 
// Time complexity:		O(n) all cases
// Space complexity:	O(h) worst case; O(log n) average & worst cases	
template<typename T> requires Comparable<T>
void AVL_Tree<T>::printPostOrder(AVL_Node<T>* node) {
	if (!node)	// Base condition: reached a null node
		return;

	printPostOrder(node->left);
	printPostOrder(node->right);
	std::cout << node->data << " ";
}


// Private utility method that prints the contents of the tree in level order.
// 
// Time complexity:		O(n) all cases
// Space complexity:	O(1) best case; O(n) average & worst cases 
template<typename T> requires Comparable<T>
void AVL_Tree<T>::printLevelOrder(AVL_Node<T>* node) {
	if (!node)	// If the node is null, we can't print anything
		return;

	std::queue<AVL_Node<T>*> queue;
	queue.push(root);

	// Continue while at least one undiscovered node
	while (!queue.empty()) {
		AVL_Node<T>* current = queue.front();
		queue.pop();
		if (current->left)
			queue.push(current->left);
		if (current->right)
			queue.push(current->right);
		std::cout << current->data << " ";		
	}
}


#endif // AVL_TREE_H


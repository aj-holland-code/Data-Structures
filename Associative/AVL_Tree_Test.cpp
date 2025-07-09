// AVL Tree
// --------
// 
// Based on example in YouTube video:
// "Data Structures Easy to Advanced Course - Full Tutorial from a Google Engineer"
//  
// https://youtu.be/RBSGKlAvoiM
// 
// This solution covers an AVL tree data structure. 
// The example used in that video is coded in Java; this is implemented in C++ so
// differs considerably in places. 
// 
// The notes below are taken from the video. They begin covering balanced binary search trees in general, 
// and then continue to cover the specific type of balanced binary search tree being implemented here, 
// the AVL tree.
// 
//
// What is a Balanced Binary Search Tree (BBST)?
// ---------------------------------------------
// 
// A BBST is a self-balancing binary search tree. This type of tree will adjust
// itself in order to maintain a low (logarithmic) height, allowing for faster
// operations such as insertions and deletions. 
// 
// Binary Search Trees can degenerate into a chain for certain inputs, for example,
// increasing numbers, leading to operations at O(n) rather than O(log(n)) complexity. 
// BBSTs seek to address these problems, preventing the performance deterioration.
// 
// 
// Time Complexity of Operations - Binary Search Trees
// ---------------------------------------------------
// 
// Operation		Average		Worst
// ---------        -------     -----
// 
// Insert		    O(log(n))	O(n)
// Delete		    O(log(n))	O(n)
// Remove		    O(log(n))	O(n)
// Search		    O(log(n))	O(n)
//
//
// Time Complexity of Operations - Balanced Binary Search Trees
// ------------------------------------------------------------
// 
// Operation		Average		Worst
// ---------        -------     -----
// 
// Insert		    O(log(n))	O(log(n))
// Delete		    O(log(n))	O(log(n))
// Remove		    O(log(n))	O(log(n))
// Search		    O(log(n))	O(log(n))


// Tree Invariants
// ---------------
//
// The secret ingredient in most BBST algorithms is the clever use of a tree
// invariant and of tree rotations.
// 
// A tree invariant is a property/rule you impose on your tree that is must meet
// after every operation. To ensure that the invariant is always satisfied, a
// series of tree rotations are normally applied.
// 
// Recall that all BBSTs are BSTs, so the BST invariant also holds.
// This means that for every node n, n.left < n and n < n.right.
// (Assumes we only have unique values, otherwise we'd have to consider the 
// case where n.left <= n and n <= n.right.)
// 
// It doesn't matter what the structure of the tree looks like; what we care about
// is that the BST invariant holds.
// 
// This means that we can shuffle/transform/rotate values and nodes in the tree
// as we please -- as long as the BST invariant is satisfied!
//
// 
// AVL Trees
// ---------
// 
// An AVL tree is a self-balancing Binary Search Tree (BST), 
// in which the difference between the heights of left and right subtrees 
// for any node cannot be more than one.
//
// The AVL tree derives its names from its inventors: 
// (George) Adelson-Vesky and (Evgenii) Landis.
// 
// AVLs trees are one of many types of Balanced Binary Search Trees (BBSTs) that
// allow for logarithmic O(log(n)) insertion, deletion, and search operations.
// 
// It was actually the first type of BBST to be discovered; soon after, many other
// types of BBSTs began to emerge, including:
// 
// 1) The 2-3 Tree
// 2) The AA Tree
// 3) The Scapegoat Tree
// 4) The Red-Black Tree (the AVL Tree's main rival)
// 
// 
// The AVL Tree Invariant
// ----------------------
// 
// The property that keeps an AVL tree balanced is called the Balance Factor (BF).
// This is the difference between the height of the left subtree and the height
// of the right subtree of that node.
// 
// BF(node) = H(node.right) - H(node.left) [probably!]
// 
// Recall that H(x) is calculated as the number of edges between x and the 
// furthest leaf. A tree with one node has a height of zero (not one), as there
// are no edges.
// 
// The invariant in the AVL that forces it to remain balanced is the requirement
// that the balance factor is always either -1, 0, or +1. 
// If it is not, the balance factor is +-2, and the balance factor of a
// node is then adjusted using tree rotations. 
// 
// 
// Rotating Subtrees in an AVL Tree
// --------------------------------
// 
// An AVL tree may need to rotate nodes in one of the following four ways to 
// keep itself balanced:
// 
// 1. Left Rotation
// 
//    If adding a node to the right subtree of the right subtree causes the tree
//    to be out of balance, a single left rotation is required.
// 
// 2. Right Rotation
// 
//    If adding a node to the left subtree of the left subtree causes the tree
//    to be out of balance, a single right rotation is required.
// 
// 3. Left-Right Rotation
//    
//    If adding a node to the right subtree of a left subtree causes the tree to
//    be out of balance, a left-right rotation is required. 
//    This is a two-phase operation, consisting first of a left rotation and then
//    a right rotation.
// 
// 4. Right-Left Rotation
// 
//    If adding a node to the left subtree of a right subtree causes the tree to
//    be out of balance, a right-left rotation is required. 
//    This is a two-phase operation, consisting first of a right rotation and then
//    a left rotation.
//    
// 
// Node Information to Store
// -------------------------
// 
// 1. The actual value to be stored in the node. Must be comparable, in order to 
//    be able to determine how to insert it.
// 2. A value storing this node's balance factor.
// 3. The height of this node in the tree.
// 4. Pointers to the left/right child nodes.
// 
//  
// Advantages of an AVL Trees
// --------------------------
// 
// 1. They can self-balance.
// 2. They provide faster lookup than Red-Black trees [how, why?]
// 3. They have better search time complexity than other trees.
//
// 
// Applications of AVL Trees
// -------------------------
// 
// 1. Indexing huge records in databases.
// 2. Types of in-memory collections, including sets and dictionaries.
// 3. Database applications.
// 4. Optimised searches.

#include <cstdlib>			// For std::rand (used to randomise insert value)
#include <iomanip>
#include <iostream>
#include <time.h>			// For seeding random number generator (for above)

#include "AVL_Tree.h"

// Main test functions
void testConcept();
void testEmptyTree();
void testCopyConstructor();
void testMoveConstructor();
void testCopyAssignmentOperator();
void testMoveAssignmentOperator();

void testOneElementTree();
void testTwoElementTree();
void testThreeElementTree();
void testMultiElementTree();
void testRemoveElements();
void testRemoveElementsMultiTree();
void testClearElements();

// Supplementary test functions

// Utility functions declarations
void print_separator();
void printLogStart(const char* s);
void printLogEnd(const char* s);
void printSpaces(int noSpaces);
void printUnderscores(int noUnderscores);

int main() {
	// Call test functions here
	testConcept();
	testEmptyTree();
	testCopyConstructor();
	testMoveConstructor();
	testCopyAssignmentOperator();
	testMoveAssignmentOperator();

	testOneElementTree();
	testTwoElementTree();
	testThreeElementTree();
	testMultiElementTree();
	testRemoveElements();
	testRemoveElementsMultiTree();
	testClearElements();
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

/**************************************************************************/
/************************* Test Function Definitions **********************/

class Dog {
public:
	Dog(const char* name) : dName {name} {}	
	void setBonesEaten(int num) { noBonesEaten = num; }
private:
	std::string dName{};
	int noBonesEaten{};
};


void testConcept() {
	printLogStart(__FUNCTION__);

	// chars are fine to store in a tree
	AVL_Tree<char> charTree;
	charTree.insert('a');
	charTree.insert('b');
	charTree.insert('c');
	std::cout << "\nContents of char tree...\n";
	charTree.print(TraversalTreeOrder::LEVEL_ORDER);

	// Can't store Dogs in a tree as there's no comparison operators defined
	//AVL_Tree<Dog> dogTree;

	AVL_Tree<std::string> stringTree;
	stringTree.insert("Arthur");
	stringTree.insert("Ted");
	stringTree.insert("Charles");
	std::cout << "\n\nContents of string tree...\n";
	stringTree.print(TraversalTreeOrder::LEVEL_ORDER);

	printLogEnd(__FUNCTION__);
}


void testEmptyTree() {
	printLogStart(__FUNCTION__);

	AVL_Tree<int> tree;
	std::cout << std::boolalpha;
	std::cout << "\nContents of an empty tree...\n";
	tree.print(TraversalTreeOrder::LEVEL_ORDER);

	std::cout << "Tree empty:        " << tree.isEmpty() << '\n';
	std::cout << "Tree size:         " << tree.size() << '\n';
	std::cout << "Tree height:       " << tree.height() << '\n';
	std::cout << "Tree is valid BST: " << tree.validateBST() << '\n';
	int data = 10;
	std::cout << "Tree contains " << data << ":  " << tree.contains(data) << '\n';
	std::cout << "Tree removed  " << data << ":  " << tree.remove(data) << '\n';

	std::cout << "After running clear method..\.\n";
	tree.clear();
	tree.print(TraversalTreeOrder::LEVEL_ORDER);

	printLogEnd(__FUNCTION__);
}

void testCopyConstructor() {
	printLogStart(__FUNCTION__);
	std::cout << std::boolalpha;

	// 1. Test copy construct from empty tree
	std::cout << "(1) Copy construct from an empty AVL tree...\n";
	AVL_Tree<int> tree1;

	std::cout << "Contents of tree1:\n";
	tree1.print(TraversalTreeOrder::LEVEL_ORDER);
	std::cout << "Height of tree1 is: " << tree1.height() << '\n';
	std::cout << "tree1 is empty:     " << tree1.isEmpty() << '\n';
	std::cout << "tree1 size:         " << tree1.size() << '\n';

	std::cout << "Copy construct from tree1...\n";
	AVL_Tree<int> tree2(tree1);

	std::cout << "Contents of tree2:\n";
	tree2.print(TraversalTreeOrder::LEVEL_ORDER);
	std::cout << "Height of tree2 is: " << tree2.height() << '\n';
	std::cout << "tree2 is empty:     " << tree2.isEmpty() << '\n';
	std::cout << "tree2 size:         " << tree2.size() << '\n';
	print_separator();

	/*****************************************************************************/

	// 2. Test copy construct from populated tree
	std::cout << "\n\n(2) Copy construct from populated AVL tree...\n";
	AVL_Tree<int> tree3;

	// Insert the values into the tree
	int treeVals[] = { 10, 20, 30, 40, 50 };

	for (int i = 0; i < std::size(treeVals); i++)
		tree3.insert(treeVals[i]);

	std::cout << "Contents of tree3:\n";
	tree3.print(TraversalTreeOrder::LEVEL_ORDER);
	std::cout << "Height of tree3 is: " << tree3.height() << '\n';
	std::cout << "tree3 is empty:     " << tree3.isEmpty() << '\n';
	std::cout << "tree3 size:         " << tree3.size() << '\n';

	std::cout << "\nNow copy construct tree4 from tree3...\n";
	AVL_Tree<int> tree4(tree3);

	std::cout << "\n\nAfter copy constructing...\n";
	std::cout << "Contents of tree3:\n";
	tree3.print(TraversalTreeOrder::LEVEL_ORDER);
	std::cout << "Height of tree3 is: " << tree3.height() << '\n';
	std::cout << "tree3 is empty:     " << tree3.isEmpty() << '\n';
	std::cout << "tree3 size:         " << tree3.size() << '\n';

	std::cout << "\nContents of tree4:\n";
	tree4.print(TraversalTreeOrder::LEVEL_ORDER);
	std::cout << "Height of tree4 is: " << tree4.height() << '\n';
	std::cout << "tree4 is empty:     " << tree4.isEmpty() << '\n';
	std::cout << "tree4 size:         " << tree4.size() << '\n';

	printLogEnd(__FUNCTION__);
}

void testMoveConstructor() {
	printLogStart(__FUNCTION__);
	std::cout << std::boolalpha;

	// 1. Test move construct from empty tree
	std::cout << "(1) Move construct from an empty AVL tree...\n";
	AVL_Tree<int> tree1;

	std::cout << "Contents of tree1:\n";
	tree1.print(TraversalTreeOrder::LEVEL_ORDER);
	std::cout << "Height of tree1 is: " << tree1.height() << '\n';
	std::cout << "tree1 is empty:     " << tree1.isEmpty() << '\n';
	std::cout << "tree1 size:         " << tree1.size() << '\n';

	std::cout << "Move construct from tree1...\n";
	AVL_Tree<int> tree2(std::move(tree1));

	std::cout << "Contents of tree2:\n";
	tree2.print(TraversalTreeOrder::LEVEL_ORDER);
	std::cout << "Height of tree2 is: " << tree2.height() << '\n';
	std::cout << "tree2 is empty:     " << tree2.isEmpty() << '\n';
	std::cout << "tree2 size:         " << tree2.size() << '\n';
	print_separator();

	/*****************************************************************************/

	// 2. Test move construct from populated tree
	std::cout << "\n\n(2) Move construct from populated AVL tree...\n";
	AVL_Tree<int> tree3;

	// Insert the values into the tree
	int treeVals[] = { 10, 20, 30, 40, 50 };

	for (int i = 0; i < std::size(treeVals); i++)
		tree3.insert(treeVals[i]);

	std::cout << "\nContents of tree3:\n";
	tree3.print(TraversalTreeOrder::LEVEL_ORDER);
	std::cout << "Height of tree3 is: " << tree3.height() << '\n';
	std::cout << "tree3 is empty:     " << tree3.isEmpty() << '\n';
	std::cout << "tree3 size:         " << tree3.size() << '\n';

	std::cout << "\nNow move construct tree4 from tree3...\n";
	AVL_Tree<int> tree4(std::move(tree3));

	std::cout << "\n\nAfter move constructing...\n";
	std::cout << "Contents of tree3:\n";
	tree3.print(TraversalTreeOrder::LEVEL_ORDER);
	std::cout << "Height of tree3 is: " << tree3.height() << '\n';
	std::cout << "tree3 is empty:     " << tree3.isEmpty() << '\n';
	std::cout << "tree3 size:         " << tree3.size() << '\n';

	std::cout << "\nContents of tree4:\n";
	tree4.print(TraversalTreeOrder::LEVEL_ORDER);
	std::cout << "Height of tree4 is: " << tree4.height() << '\n';
	std::cout << "tree4 is empty:     " << tree4.isEmpty() << '\n';
	std::cout << "tree4 size:         " << tree4.size() << '\n';

	printLogEnd(__FUNCTION__);
}

void testCopyAssignmentOperator() {
	printLogStart(__FUNCTION__);
	std::cout << std::boolalpha;

	// 1. Test copy assign empty to empty
	std::cout << "(1) Copy assign from an empty tree into an empty tree...\n";
	AVL_Tree<int> tree1;
	std::cout << "\nBefore copy assign...\n";
	std::cout << "Height of tree1 is: " << tree1.height() << '\n';
	std::cout << "tree1 is empty:     " << tree1.isEmpty() << '\n';
	std::cout << "tree1 size:         " << tree1.size() << "\n\n";

	AVL_Tree<int> tree2;
	std::cout << "Height of tree2 is: " << tree2.height() << '\n';
	std::cout << "tree2 is empty:     " << tree2.isEmpty() << '\n';
	std::cout << "tree2 size:         " << tree2.size() << '\n';

	std::cout << "\nCopy assign tree2 into tree1...\n";
	tree1 = tree2;
	std::cout << "\nAfter copy assign...\n";
	std::cout << "Height of tree1 is: " << tree1.height() << '\n';
	std::cout << "tree1 is empty:     " << tree1.isEmpty() << '\n';
	std::cout << "tree1 size:         " << tree1.size() << "\n\n";

	std::cout << "Height of tree2 is: " << tree2.height() << '\n';
	std::cout << "tree2 is empty:     " << tree2.isEmpty() << '\n';
	std::cout << "tree2 size:         " << tree2.size() << '\n';
	print_separator();

	/*****************************************************************************/

	// 2. Test copy assign empty to populated
	std::cout << "(2) Copy assign from an empty tree into a populated tree...\n";

	// Add some elements to tree1
	// Insert the values into the tree
	int treeVals[] = { 11, 6, 15, 3, 8, 13, 17, 1, 5, 12, 14, 19 };

	for (int i = 0; i < std::size(treeVals); i++)
		tree1.insert(treeVals[i]);

	std::cout << "\nBefore copy assign...\n";
	std::cout << "Contents of tree1:\n";
	tree1.print(TraversalTreeOrder::LEVEL_ORDER);
	std::cout << "Height of tree1 is: " << tree1.height() << '\n';
	std::cout << "tree1 is empty:     " << tree1.isEmpty() << '\n';
	std::cout << "tree1 size:         " << tree1.size() << "\n\n";

	// tree2 still empty
	std::cout << "\nCopy assign empty tree2 into populated tree1...\n";
	tree1 = tree2;
	std::cout << "\nAfter copy assign...\n";
	std::cout << "Contents of tree1:\n";
	tree1.print(TraversalTreeOrder::LEVEL_ORDER);
	std::cout << "Height of tree1 is: " << tree1.height() << '\n';
	std::cout << "tree1 is empty:     " << tree1.isEmpty() << '\n';
	std::cout << "tree1 size:         " << tree1.size() << "\n\n";

	std::cout << "Height of tree2 is: " << tree2.height() << '\n';
	std::cout << "tree2 is empty:     " << tree2.isEmpty() << '\n';
	std::cout << "tree2 size:         " << tree2.size() << '\n';
	print_separator();

	/*****************************************************************************/

	// 3. Test copy assign populated into empty
	std::cout << "(3) Copy assign from a populated tree into an empty tree...\n";

	// Repopulate tree2
	for (int i = 0; i < std::size(treeVals); i++)
		tree2.insert(treeVals[i]);

	std::cout << "\nBefore copy assign...\n";
	std::cout << "Contents of tree2:\n";
	tree2.print(TraversalTreeOrder::LEVEL_ORDER);
	std::cout << "Height of tree2 is: " << tree2.height() << '\n';
	std::cout << "tree2 is empty:     " << tree2.isEmpty() << '\n';
	std::cout << "tree2 size:         " << tree2.size() << '\n';

	// tree1 still empty
	std::cout << "\nCopy assign populated tree2 into empty tree1...\n";
	tree1 = tree2;
	std::cout << "\nAfter copy assign...\n";
	std::cout << "Contents of tree1:\n";
	tree1.print(TraversalTreeOrder::LEVEL_ORDER);
	std::cout << "Height of tree1 is: " << tree1.height() << '\n';
	std::cout << "tree1 is empty:     " << tree1.isEmpty() << '\n';
	std::cout << "tree1 size:         " << tree1.size() << "\n\n";

	std::cout << "Contents of tree2:\n";
	tree2.print(TraversalTreeOrder::LEVEL_ORDER);
	std::cout << "Height of tree2 is: " << tree2.height() << '\n';
	std::cout << "tree2 is empty:     " << tree2.isEmpty() << '\n';
	std::cout << "tree2 size:         " << tree2.size() << '\n';
	print_separator();

	/*****************************************************************************/

	// 4. Test copy assign populated into populated
	std::cout << "(4) Copy assign from a populated tree into another populated tree...\n";

	// Create a new tree with some different contents
	AVL_Tree<int> tree3;

	// Populate tree3
	tree3.insert(7);
	tree3.insert(3);
	tree3.insert(10);
	tree3.insert(1);
	tree3.insert(11);
	tree3.insert(9);
	tree3.insert(4);

	std::cout << "\nBefore copy assign...\n";
	std::cout << "Contents of tree3:\n";
	tree3.print(TraversalTreeOrder::LEVEL_ORDER);
	std::cout << "Height of tree3 is: " << tree3.height() << '\n';
	std::cout << "tree3 is empty:     " << tree3.isEmpty() << '\n';
	std::cout << "tree3 size:         " << tree3.size() << '\n';

	// tree1 still empty
	std::cout << "\nCopy assign populated tree3 into tree1 (has different contents)...\n";
	tree1 = tree3;
	std::cout << "\nAfter copy assign...\n";
	std::cout << "Contents of tree1:\n";
	tree1.print(TraversalTreeOrder::LEVEL_ORDER);
	std::cout << "Height of tree1 is: " << tree1.height() << '\n';
	std::cout << "tree1 is empty:     " << tree1.isEmpty() << '\n';
	std::cout << "tree1 size:         " << tree1.size() << "\n\n";

	std::cout << "Contents of tree3:\n";
	tree3.print(TraversalTreeOrder::LEVEL_ORDER);
	std::cout << "Height of tree3 is: " << tree3.height() << '\n';
	std::cout << "tree3 is empty:     " << tree3.isEmpty() << '\n';
	std::cout << "tree3 size:         " << tree3.size() << '\n';

	printLogEnd(__FUNCTION__);
}


void testMoveAssignmentOperator() {
	printLogStart(__FUNCTION__);
	std::cout << std::boolalpha;

	// 1. Test move assign empty to empty
	std::cout << "(1) Move assign from an empty tree into an empty tree...\n";
	AVL_Tree<int> tree1;
	std::cout << "\nBefore move assign...\n";
	std::cout << "Height of tree1 is: " << tree1.height() << '\n';
	std::cout << "tree1 is empty:     " << tree1.isEmpty() << '\n';
	std::cout << "tree1 size:         " << tree1.size() << "\n\n";

	AVL_Tree<int> tree2;
	std::cout << "Height of tree2 is: " << tree2.height() << '\n';
	std::cout << "tree2 is empty:     " << tree2.isEmpty() << '\n';
	std::cout << "tree2 size:         " << tree2.size() << '\n';

	std::cout << "\nMove assign tree2 into tree1...\n";
	tree1 = std::move(tree2);
	std::cout << "\nAfter move assign...\n";
	std::cout << "Height of tree1 is: " << tree1.height() << '\n';
	std::cout << "tree1 is empty:     " << tree1.isEmpty() << '\n';
	std::cout << "tree1 size:         " << tree1.size() << "\n\n";

	std::cout << "Height of tree2 is: " << tree2.height() << '\n';
	std::cout << "tree2 is empty:     " << tree2.isEmpty() << '\n';
	std::cout << "tree2 size:         " << tree2.size() << '\n';
	print_separator();

	/*****************************************************************************/

	// 2. Test move assign empty to populated
	std::cout << "\n\n(2) Move assign from an empty tree into a populated tree...\n";

	// Add some elements to tree1
	// Insert the values into the tree
	int treeVals[] = { 11, 6, 15, 3, 8, 13, 17, 1, 5, 12, 14, 19 };

	for (int i = 0; i < std::size(treeVals); i++)
		tree1.insert(treeVals[i]);

	std::cout << "\nBefore move assign...\n";
	std::cout << "Contents of tree1:\n";
	tree1.print(TraversalTreeOrder::LEVEL_ORDER);
	std::cout << "Height of tree1 is: " << tree1.height() << '\n';
	std::cout << "tree1 is empty:     " << tree1.isEmpty() << '\n';
	std::cout << "tree1 size:         " << tree1.size() << "\n\n";

	// tree2 still empty
	std::cout << "\nMove assign empty tree2 into populated tree1...\n";
	tree1 = std::move(tree2);
	std::cout << "\nAfter move assign...\n";
	std::cout << "Contents of tree1:\n";
	tree1.print(TraversalTreeOrder::LEVEL_ORDER);
	std::cout << "Height of tree1 is: " << tree1.height() << '\n';
	std::cout << "tree1 is empty:     " << tree1.isEmpty() << '\n';
	std::cout << "tree1 size:         " << tree1.size() << "\n\n";

	std::cout << "Height of tree2 is: " << tree2.height() << '\n';
	std::cout << "tree2 is empty:     " << tree2.isEmpty() << '\n';
	std::cout << "tree2 size:         " << tree2.size() << '\n';
	print_separator();

	/*****************************************************************************/

	// 3. Test move assign populated into empty
	std::cout << "(3) Move assign from a populated tree into an empty tree...\n";

	// Repopulate tree2
	for (int i = 0; i < std::size(treeVals); i++)
		tree2.insert(treeVals[i]);

	std::cout << "\nBefore move assign...\n";
	std::cout << "Contents of tree2:\n";
	tree2.print(TraversalTreeOrder::LEVEL_ORDER);
	std::cout << "Height of tree2 is: " << tree2.height() << '\n';
	std::cout << "tree2 is empty:     " << tree2.isEmpty() << '\n';
	std::cout << "tree2 size:         " << tree2.size() << '\n';

	// tree1 still empty
	std::cout << "\nMove assign populated tree2 into empty tree1...\n";
	tree1 = std::move(tree2);
	std::cout << "\nAfter move assign...\n";
	std::cout << "Contents of tree1:\n";
	tree1.print(TraversalTreeOrder::LEVEL_ORDER);
	std::cout << "Height of tree1 is: " << tree1.height() << '\n';
	std::cout << "tree1 is empty:     " << tree1.isEmpty() << '\n';
	std::cout << "tree1 size:         " << tree1.size() << "\n\n";

	std::cout << "Contents of tree2:\n";
	tree2.print(TraversalTreeOrder::LEVEL_ORDER);
	std::cout << "Height of tree2 is: " << tree2.height() << '\n';
	std::cout << "tree2 is empty:     " << tree2.isEmpty() << '\n';
	std::cout << "tree2 size:         " << tree2.size() << '\n';
	print_separator();

	/*****************************************************************************/

	// 4. Test move assign populated into populated
	std::cout << "(4) Move assign from a populated tree into another populated tree...\n";

	// Create a new tree with some different contents
	AVL_Tree<int> tree3;

	// Populate tree3
	tree3.insert(7);
	tree3.insert(3);
	tree3.insert(10);
	tree3.insert(1);
	tree3.insert(11);
	tree3.insert(9);
	tree3.insert(4);

	std::cout << "\nBefore move assign...\n";
	std::cout << "Contents of tree3:\n";
	tree3.print(TraversalTreeOrder::LEVEL_ORDER);
	std::cout << "Height of tree3 is: " << tree3.height() << '\n';
	std::cout << "tree3 is empty:     " << tree3.isEmpty() << '\n';
	std::cout << "tree3 size:         " << tree3.size() << '\n';

	// tree1 still empty
	std::cout << "\nMove assign populated tree3 into tree1 (has different contents)...\n";
	tree1 = std::move(tree3);

	std::cout << "\nAfter move assign...\n";
	std::cout << "Contents of tree1:\n";
	tree1.print(TraversalTreeOrder::LEVEL_ORDER);
	std::cout << "Height of tree1 is: " << tree1.height() << '\n';
	std::cout << "tree1 is empty:     " << tree1.isEmpty() << '\n';
	std::cout << "tree1 size:         " << tree1.size() << "\n\n";

	std::cout << "Contents of tree3:\n";
	tree3.print(TraversalTreeOrder::LEVEL_ORDER);
	std::cout << "Height of tree3 is: " << tree3.height() << '\n';
	std::cout << "tree3 is empty:     " << tree3.isEmpty() << '\n';
	std::cout << "tree3 size:         " << tree3.size() << '\n';

	printLogEnd(__FUNCTION__);
}


void testOneElementTree() {
	printLogStart(__FUNCTION__);

	AVL_Tree<int> tree;
	std::cout << std::boolalpha;

	std::cout << "\nContents of tree with one element:\n\n";
	tree.insert(10);
	tree.print(TraversalTreeOrder::LEVEL_ORDER);

	std::cout << "\n\n";
	std::cout << "Tree empty:        " << tree.isEmpty() << '\n';
	std::cout << "Tree size:         " << tree.size() << '\n';
	std::cout << "Tree height:       " << tree.height() << '\n';
	std::cout << "Tree is valid BST: " << tree.validateBST() << '\n';

	int data = 10;
	std::cout << "Tree contains " << data << ":  " << tree.contains(data) << '\n';
	std::cout << "Tree removed  " << data << ":  " << tree.remove(data) << '\n';
	data = 20;
	std::cout << "Tree contains " << data << ":  " << tree.contains(data) << '\n';
	std::cout << "Tree removed  " << data << ":  " << tree.remove(data) << '\n';

	std::cout << "\nContents of tree after running clear method:\n\n";
	tree.clear();
	tree.print(TraversalTreeOrder::LEVEL_ORDER);

	printLogEnd(__FUNCTION__);
}


void testTwoElementTree() {
	printLogStart(__FUNCTION__);

	AVL_Tree<int> tree;
	std::cout << std::boolalpha;

	std::cout << "\n(1) Test a tree with two elements:\n";
	tree.insert(10);
	tree.insert(20);

	std::cout << "\nContents of tree after two elements inserted:\n\n";
	tree.print(TraversalTreeOrder::LEVEL_ORDER);

	std::cout << "\n\n";
	std::cout << "Tree empty:        " << tree.isEmpty() << '\n';
	std::cout << "Tree size:         " << tree.size() << '\n';
	std::cout << "Tree height:       " << tree.height() << '\n';
	std::cout << "Tree is valid BST: " << tree.validateBST() << "\n\n";

	std::cout << "(2) Test the contains/remove functions...\n\n";
	int data = 0;
	std::cout << "Tree contains " << data << ":  " << tree.contains(data) << '\n';
	std::cout << "Tree removed  " << data << ":  " << tree.remove(data) << '\n';
	data = 10;
	std::cout << "Tree contains " << data << ":  " << tree.contains(data) << '\n';
	std::cout << "Tree removed  " << data << ":  " << tree.remove(data) << '\n';
	data = 20;
	std::cout << "Tree contains " << data << ":  " << tree.contains(data) << '\n';
	std::cout << "Tree removed  " << data << ":  " << tree.remove(data) << '\n';
	data = 30;
	std::cout << "Tree contains " << data << ":  " << tree.contains(data) << '\n';
	std::cout << "Tree removed  " << data << ":  " << tree.remove(data) << '\n';

	std::cout << "\nContents of tree after running clear method:\n\n";
	tree.clear();
	tree.print(TraversalTreeOrder::LEVEL_ORDER);

	printLogEnd(__FUNCTION__);
}


void testThreeElementTree() {
	printLogStart(__FUNCTION__);
	AVL_Tree<int> tree;
	std::cout << std::boolalpha;

	std::cout << "\nContents of tree with three elements:\n\n";
	tree.insert(10);
	tree.insert(20);
	tree.insert(30);
	tree.print(TraversalTreeOrder::LEVEL_ORDER);

	printLogEnd(__FUNCTION__);
}



void testMultiElementTree() {
	printLogStart(__FUNCTION__);
	AVL_Tree<int> tree;
	std::cout << std::boolalpha;
	
	/* To insert random elements, activate/run this code
	   --------------------------------------------------
	std::srand(std::time(nullptr));
	std::cout << "\nContents of tree with multiple (random) elements:\n\n";

	for (int i = 0; i < 15; i++) {
		std::cout << "\n\n----------------------------------------------------------\n\n";
		int insertionValue = static_cast<int>(std::rand() % 100);
		std::cout << "Inserting " << insertionValue << " into the tree...\n";
		tree.insert(insertionValue);
		std::cout << "\n\nPrint tree in level-order:\n";
		tree.print(TraversalTreeOrder::LEVEL_ORDER);

		std::cout << "\n\n";
		std::cout << "Tree empty:        " << tree.isEmpty() << '\n';
		std::cout << "Tree size:         " << tree.size() << '\n';
		std::cout << "Tree height:       " << tree.height() << '\n';
		std::cout << "Tree is valid BST: " << tree.validateBST() << '\n';
	}*/

	// To bring about a specific sequence of events, activate/run this code
	// --------------------------------------------------------------------
	// 
	// This set of input data is setup to trigger various events in the tree:
	// 
	// 0			creates a left-left case
	// 63			creates a left-right case
	// 92			creates a right-left case
	// 82 (2nd)		duplicate value - rejected
	// 56			creates a right-left case
	// 105			creates a right-right case
	//
	// The other numbers in the array will insert without requiring rotations.
	//
	// N.B. These results are predicated on the array contents being in the 
	// order specified here! 
	// 
	// 82, 99, 77, 4, 0, 63, 23, 68, 92, 82, 56, 10, 102, 105

	int nums[] = { 82, 99, 77, 4, 0, 63, 23, 68, 92, 82, 56, 10, 102, 105 };
	for (int i = 0; i < std::size(nums); i++) {
		std::cout << "\n\n----------------------------------------------------------\n\n";
		std::cout << "Inserting " << nums[i] << " into the tree...\n";
		tree.insert(nums[i]);
		std::cout << "\n\nPrint tree in level-order:\n";
		tree.print(TraversalTreeOrder::LEVEL_ORDER);

		std::cout << "\n\n";
		std::cout << "Tree empty:        " << tree.isEmpty() << '\n';
		std::cout << "Tree size:         " << tree.size() << '\n';
		std::cout << "Tree height:       " << tree.height() << '\n';
		std::cout << "Tree is valid BST: " << tree.validateBST() << '\n';
	}

	printLogEnd(__FUNCTION__);
}


void testRemoveElements() {
	printLogStart(__FUNCTION__);
	AVL_Tree<int> tree;
	std::cout << std::boolalpha;

	// 1. Attempt to remove elements from an empty tree
	std::cout << "\nStart off with an empty tree...\n";
	for (int i = 0; i < 10; i++) {
		bool removed = tree.remove(i);
		std::cout << i << " removed: " << removed << '\n';
	}
	std::cout << "\n\n----------------------------------------------------------\n\n";

	/**********************************************************************************/

	// 2. Remove the only element of a one-element tree
	std::cout << "\nTest removal from a one-element tree...\n";
	int insertValue = 20;
	int nonInsertValue = 10;
	tree.insert(insertValue);
	std::cout << "\nTree contents:n";
	tree.print(TraversalTreeOrder::LEVEL_ORDER);

	bool removed = tree.remove(nonInsertValue);
	std::cout << nonInsertValue << " removed: " << removed << '\n';

	tree.insert(insertValue);
	removed = tree.remove(insertValue);
	std::cout << insertValue << " removed: " << removed << '\n';
	removed = tree.remove(insertValue);
	std::cout << insertValue << " removed: " << removed << '\n';
	removed = tree.remove(nonInsertValue);
	std::cout << nonInsertValue << " removed: " << removed << '\n';

	std::cout << "\n\n";
	std::cout << "Tree empty:        " << tree.isEmpty() << '\n';
	std::cout << "Tree size:         " << tree.size() << '\n';
	std::cout << "Tree height:       " << tree.height() << '\n';
	std::cout << "Tree is valid BST: " << tree.validateBST() << '\n';

	std::cout << "\n\n----------------------------------------------------------\n\n";

	/**********************************************************************************/

	// 3. Remove elements from a two-element tree
	std::cout << "\nTest removal from a two-element tree...\n";
	int insertValues[] = { 10, 20 };
	nonInsertValue = 30;

	tree.insert(insertValues[0]);
	tree.insert(insertValues[1]);
	std::cout << "\nTree contents:\n";
	tree.print(TraversalTreeOrder::LEVEL_ORDER);

	removed = tree.remove(nonInsertValue);
	std::cout << nonInsertValue << " removed: " << removed << '\n';

	removed = tree.remove(insertValues[0]);
	std::cout << insertValues[0] << " removed: " << removed << '\n';
	std::cout << "\nTree contents:\n";
	tree.print(TraversalTreeOrder::LEVEL_ORDER);

	removed = tree.remove(insertValues[1]);
	std::cout << insertValues[1] << " removed: " << removed << '\n';
	std::cout << "\nTree contents:\n";
	tree.print(TraversalTreeOrder::LEVEL_ORDER);

	removed = tree.remove(nonInsertValue);
	std::cout << nonInsertValue << " removed: " << removed << '\n';
	removed = tree.remove(insertValues[0]);
	std::cout << insertValues[0] << " removed: " << removed << '\n';
	removed = tree.remove(insertValues[1]);
	std::cout << insertValues[1] << " removed: " << removed << '\n';

	std::cout << "\n\n";
	std::cout << "Tree empty:        " << tree.isEmpty() << '\n';
	std::cout << "Tree size:         " << tree.size() << '\n';
	std::cout << "Tree height:       " << tree.height() << '\n';
	std::cout << "Tree is valid BST: " << tree.validateBST() << '\n';

	printLogEnd(__FUNCTION__);
}

void testRemoveElementsMultiTree() {
	printLogStart(__FUNCTION__);
	AVL_Tree<int> tree;
	std::cout << std::boolalpha;

	std::cout << "\nTest removal from a multi-element tree...\n";

	int nums[] = { 82, 99, 77, 4, 0, 63, 23, 68, 92, 82, 56, 10, 102, 105 };
	for (int i = 0; i < std::size(nums); i++)
		tree.insert(nums[i]);		

	std::cout << "\n\nPrint tree in level-order after inserting values:\n";
	tree.print(TraversalTreeOrder::LEVEL_ORDER);
	std::cout << "Tree empty:        " << tree.isEmpty() << '\n';
	std::cout << "Tree size:         " << tree.size() << '\n';
	std::cout << "Tree height:       " << tree.height() << '\n';
	std::cout << "Tree is valid BST: " << tree.validateBST() << '\n';

	std::cout << "\n\nNow perform the removals:\n";
	int removeNums[] = { 82, 0, 23, 105, 200 };

	// 82			creates a right-right case for 92 (its parent)
	// 0			will be removed without any rotations
	// 23			creates a "lowest right node replacement" case
	// 105          creates a left-right case for 102 (its parent)	
	// 200			non-existent element in this tree - tree will be unaffected
	for (int i = 0; i < std::size(removeNums); ++i) {
		std::cout << "Removing " << removeNums[i] << '\n';
		bool success = tree.remove(removeNums[i]);

		// Only concern ourselves with failed removes being reported
		if (!success)
			std::cout << "Removal of " << removeNums[i] << " failed...\n";

		std::cout << "\n\n";
		std::cout << "Contents of tree after removing " << removeNums[i] << '\n';
		tree.print(TraversalTreeOrder::LEVEL_ORDER);
		std::cout << "Tree empty:        " << tree.isEmpty() << '\n';
		std::cout << "Tree size:         " << tree.size() << '\n';
		std::cout << "Tree height:       " << tree.height() << '\n';
		std::cout << "Tree is valid BST: " << tree.validateBST() << '\n';
	}	
	
	printLogEnd(__FUNCTION__);
}


void testClearElements() {
	printLogStart(__FUNCTION__);
	AVL_Tree<int> tree;
	std::cout << std::boolalpha;

	std::cout << "\nTest clearing trees completely...\n";

	int elems[] = { 0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100 };

	for (int i = 0; i < std::size(elems); i++) {
		std::cout << "\n----------------------------------------------------------\n";
		std::cout << "\nInserting " << i + 1 << " elements into the tree...\n";

		int j = 0;
		while (j < i + 1) {
			tree.insert(elems[j++]);
		}

		std::cout << "\n\nPrint tree in level-order:\n";
		tree.print(TraversalTreeOrder::LEVEL_ORDER);
		std::cout << "\nTree height:       " << tree.height() << '\n';

		std::cout << "Clearing tree...\n";
		tree.clear();
		std::cout << "\n\nPrint tree in level-order:\n";
		tree.print(TraversalTreeOrder::LEVEL_ORDER);
		std::cout << "\n\n";
		std::cout << "Tree empty:        " << tree.isEmpty() << '\n';
		std::cout << "Tree size:         " << tree.size() << '\n';
		std::cout << "Tree height:       " << tree.height() << '\n';
		std::cout << "Tree is valid BST: " << tree.validateBST() << '\n';
	}
}

// Binary Search Tree
// ------------------
// 
// Based on example in YouTube video :
// "Data Structures Easy to Advanced Course - Full Tutorial from a Google Engineer"//  
// https://youtu.be/RBSGKlAvoiM
// 
// This solution covers a binary search tree (BST) data structure. 
// The example used in that video is coded in Java; this is implemented in C++ so
// differs considerably in places. The notes below are taken from the video.
// 
// 
// Trees - A Crash Course
// ----------------------
// 
// A tree is an undirected graph satisfying any of the following:
// 
// 1) An acyclic (no cycles) connected graph.
// 2) A connected graph with N nodes and N-1 edges.
// 3) Any graph in which any two vertices are connected by exactly one path.
// 
// - A rooted tree will have a reference to the root node of the tree. 
// - Any node can be the root of the tree! 
// - A child node is a node extending from another node; a parent node is the
//   inverse.
// - The root node has no parent, although it may be useful to assign the parent
//	 of the root node to be the root itself.
// - A leaf node is a node with no children.
// - A subtree is a tree contained entirely within another (usually denoted
//   with triangles).
// - A subtree can consist of a single node.
// 
// 
// Binary Trees
// ------------
// 
// A Binary Tree (BT) is a tree in which every node has at most two children.
// 
// 
// Binary Search Tree
// ------------------
// 
// A Binary Search Tree (BST) is a binary tree that satisfies the BST 
// invariant:
// The left subtree has smaller elements and the right tree has larger 
// elements.
// BSTs conceptually allow for duplicate values, but usually we want our
// tree to store unique values.
// 
// BSTs are used in:
// 1) Implementations of Maps and Set ADTs
// 2) Red-Black Trees
// 3) AVL Trees
// 4) Splay Trees
// 5) Implementations of Binary Heaps
// 6) Syntax Trees (used by calculators and compilers)
// 7) Treap - a probabilistic DS (uses a randomised BST)
// 
// 
// Time Complexity of Operations
// -----------------------------
// 
// Operation		Average			Worst
// ---------        -------         -----
// 
// Insert			O(log(n))		O(n)
// Delete			O(log(n))		O(n)
// Remove			O(log(n))		O(n)
// Search			O(log(n))		O(n)
//
// Worst cases may be encountered if tree degenerates into a line.
// Balanced Binary Trees are an attempt to overcome this problem.
// 
// 
// More on Binary Trees
// --------------------
//
// - In a binary tree, each node can have at most two children;
//   nodes can have a left child or a right child or both.
// - In a strict binary tree, each node has either 0 or 2 children.
// - In a complete binary tree, all levels, except possibly the last, 
//   are completely filled, and all nodes are as left as possible.
// - The max no of nodes at level n is n squared.
// - In a perfect binary tree, all levels are completely filled.
// - In a balanced binary tree, the difference between the height of left
//   and right subtrees for every node is not more than k (mostly 1)
// 
// Height = number of edges in longest path from root to a leaf
// Height of an empty tree = -1
// Height of tree with one node = 0
// 
// Number of nodes = height + 1 squared - 1
// Height of perfect binary tree = log base 2 (n+1) - 1
// Height of complete binary tree = log base 2 of n
// Min height = log base 2 of n (O log2n)
// Max height = n - 1 (O n)
// 
// A binary search tree (BST) is a binary tree in which where the value of a node in 
// the left subtree is lower than or equal to the value in the parent node, and the value
// of the node in the right subtree is higher than the value in the parent node.

#include <iomanip>
#include <iostream>

#include "Binary_Search_Tree.h"

// Main test functions
// Special member functions
void testEmptyBinarySearchTree();
void testCopyConstructor();
void testMoveConstructor();
void testCopyAssignmentOperator();
void testMoveAssignmentOperator();

// Other functions
void testOneElementBinarySearchTree();
void testTwoElementBinarySearchTree();
void testThreeElementBinarySearchTree();
void testMultiElementBinarySearchTree();
void testTreeRemovals();

// Utility functions declarations
void print_separator();
void printLogStart(const char* s);
void printLogEnd(const char* s);

int main() {
	// Call test functions here
	//testEmptyBinarySearchTree();
	//testCopyConstructor();
	//testMoveConstructor();
	testCopyAssignmentOperator();
	//testMoveAssignmentOperator();

	// Other member functions
	//testOneElementBinarySearchTree();
	//testTwoElementBinarySearchTree();
	//testThreeElementBinarySearchTree();
	//testMultiElementBinarySearchTree();
	//testTreeRemovals();
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

/***********************************************************************************/
/******************************* Test Functions ************************************/

// Utility test function that runs all of the types of
// print traversal functions for the tree specified.
template <typename T>
void runPrintFunctions(BinarySearchTree<T>& tree) {
	std::cout << "\nTest preorder print:\n";
	tree.print(TreeTraversalOrder::PRE_ORDER);

	std::cout << "\nTest inorder print:\n";
	tree.print(TreeTraversalOrder::IN_ORDER);

	std::cout << "\nTest level order print:\n";
	tree.print(TreeTraversalOrder::LEVEL_ORDER);

	std::cout << "\nTest post order print:\n";
	tree.print(TreeTraversalOrder::POST_ORDER);
}

// Class without comparison operators to test the BST concept.
class Person {
public:
	Person(int a) : Person(a, "Fred Turnip") {}
	Person(const char* n) : Person(51, n) {}
	Person(int a, const char* n) : age{ a }, name{ n } {
		std::cout << name << " created...\n";
	}
	friend std::ostream& operator<<(std::ostream& out, const Person& person);
private:
	int age{};
	std::string name{};
};

std::ostream& operator<<(std::ostream& out, const Person& person) {
	out << "Name: " << person.name << "\tAge: " << person.age << '\n';
	return out;
}

void testEmptyBinarySearchTree() {
	printLogStart(__FUNCTION__);

	// 1. Create an empty tree
	std::cout << "(1) Test an empty integer binary search tree...\n";
	BinarySearchTree<int> tree1;
	std::cout << std::boolalpha;

	std::cout << "\nState of empty tree before clear...\n";
	std::cout << "Height of tree is: " << tree1.height() << '\n';
	std::cout << "Tree is empty:     " << tree1.isEmpty() << '\n';
	std::cout << "Tree size:         " << tree1.size() << '\n';

	std::cout << "\nState of empty tree after clear...\n";
	tree1.clear();
	std::cout << "Height of tree is: " << tree1.height() << '\n';
	std::cout << "Tree is empty:     " << tree1.isEmpty() << '\n';
	std::cout << "Tree size:         " << tree1.size() << '\n';

	std::cout << "\nTest print output for this tree...\n";
	runPrintFunctions(tree1);
	print_separator();

	/***************************************************************************/

	// 2. Attempt to create a tree type with an invalid data type 
	// (a custom type that doesn't have any comparison operators defined).
	std::cout << "\n\n(2) Test trying to instantiate a BST with type that doesn't match constraints...\n";

	// Test all three constructor options
	Person p1(22);						// 1. Supply age only
	Person p2("Ted Smith");				// 2. Supply name only
	Person p3(33, "Billy Brass");		// 3. Supply age and name

	// Print the details
	std::cout << "\n\nThe details of the people:\n\n";
	std::cout << "Person 1 | " << p1 << '\n';
	std::cout << "Person 2 | " << p2 << '\n';
	std::cout << "Person 3 | " << p3 << '\n';

	// These statements won't compile as there are no such operators defined for Person
	//std::cout << "p1 < p2:  " << (p1 < p2) << '\n';
	//std::cout << "p1 > p2:  " << (p1 > p2) << '\n';
	//std::cout << "p1 == p2: " << (p1 == p2) << '\n';

	// Therefore, creating a binary search tree to store Person objects won't compile
	// due to the defined constraints not being satisfied.
	//BinarySearchTree<Person> personTree;
		
	printLogEnd(__FUNCTION__);
}


void testCopyConstructor() {
	printLogStart(__FUNCTION__);
	std::cout << std::boolalpha;

	// 1. Test copy construct from empty tree
	std::cout << "(1) Copy construct from empty BST...\n";
	BinarySearchTree<int> tree1;

	std::cout << "Contents of tree1:\n";
	runPrintFunctions(tree1);
	std::cout << "Height of tree1 is: " << tree1.height() << '\n';
	std::cout << "tree1 is empty:     " << tree1.isEmpty() << '\n';
	std::cout << "tree1 size:         " << tree1.size() << '\n';

	std::cout << "Copy construct from tree1...\n";
	BinarySearchTree<int> tree2(tree1);

	std::cout << "Contents of tree2:\n";
	runPrintFunctions(tree2);
	std::cout << "Height of tree2 is: " << tree2.height() << '\n';
	std::cout << "tree2 is empty:     " << tree2.isEmpty() << '\n';
	std::cout << "tree2 size:         " << tree2.size() << '\n';
	print_separator();

	/*****************************************************************************/

	// 2. Test copy construct from populated tree
	std::cout << "\n\n(2) Copy construct from populated BST...\n";
	BinarySearchTree<int> tree3;
	
	// Insert the values into the tree
	int treeVals[] = { 11, 6, 15, 3, 8, 13, 17, 1, 5, 12, 14, 19 };

	for (int i = 0; i < std::size(treeVals); i++)
		tree3.add(treeVals[i]);
	
	std::cout << "Contents of tree3:\n";
	runPrintFunctions(tree3);
	std::cout << "Height of tree3 is: " << tree3.height() << '\n';
	std::cout << "tree3 is empty:     " << tree3.isEmpty() << '\n';
	std::cout << "tree3 size:         " << tree3.size() << '\n';

	std::cout << "\nNow copy construct tree4 from tree3...\n";
	BinarySearchTree<int> tree4(tree3);

	std::cout << "Contents of tree3:\n";
	runPrintFunctions(tree3);
	std::cout << "Height of tree3 is: " << tree3.height() << '\n';
	std::cout << "tree3 is empty:     " << tree3.isEmpty() << '\n';
	std::cout << "tree3 size:         " << tree3.size() << '\n';

	std::cout << "\nContents of tree4:\n";
	runPrintFunctions(tree4);
	std::cout << "Height of tree4 is: " << tree4.height() << '\n';
	std::cout << "tree4 is empty:     " << tree4.isEmpty() << '\n';
	std::cout << "tree4 size:         " << tree4.size() << '\n';

	printLogEnd(__FUNCTION__);
}

void testMoveConstructor() {
	printLogStart(__FUNCTION__);
	std::cout << std::boolalpha;

	// 1. Test move construct from empty tree
	std::cout << "(1) Move construct from empty BST...\n";
	BinarySearchTree<int> tree1;

	std::cout << "Contents of tree1:\n";
	runPrintFunctions(tree1);
	std::cout << "Height of tree1 is: " << tree1.height() << '\n';
	std::cout << "tree1 is empty:     " << tree1.isEmpty() << '\n';
	std::cout << "tree1 size:         " << tree1.size() << '\n';

	std::cout << "Copy construct from tree1...\n";
	BinarySearchTree<int> tree2(std::move(tree1));

	std::cout << "Contents of tree2:\n";
	runPrintFunctions(tree2);
	std::cout << "Height of tree2 is: " << tree2.height() << '\n';
	std::cout << "tree2 is empty:     " << tree2.isEmpty() << '\n';
	std::cout << "tree2 size:         " << tree2.size() << '\n';
	print_separator();

	/*****************************************************************************/

	// 2. Test move construct from populated tree
	std::cout << "\n\n(2) Move construct from populated BST...\n";
	BinarySearchTree<int> tree3;

	// Insert the values into the tree
	int treeVals[] = { 11, 6, 15, 3, 8, 13, 17, 1, 5, 12, 14, 19 };

	for (int i = 0; i < std::size(treeVals); i++)
		tree3.add(treeVals[i]);

	std::cout << "Contents of tree1:\n";
	runPrintFunctions(tree3);
	std::cout << "Height of tree3 is: " << tree3.height() << '\n';
	std::cout << "tree3 is empty:     " << tree3.isEmpty() << '\n';
	std::cout << "tree3 size:         " << tree3.size() << '\n';

	std::cout << "\nNow move construct tree4 from tree3...\n";
	BinarySearchTree<int> tree4(std::move(tree3));
	std::cout << "Contents of tree3:\n";
	runPrintFunctions(tree3);
	std::cout << "Height of tree3 is: " << tree3.height() << '\n';
	std::cout << "tree3 is empty:     " << tree3.isEmpty() << '\n';
	std::cout << "tree3 size:         " << tree3.size() << '\n';

	std::cout << "\nContents of tree4:\n";
	runPrintFunctions(tree4);
	std::cout << "Height of tree4 is: " << tree4.height() << '\n';
	std::cout << "tree4 is empty:     " << tree4.isEmpty() << '\n';
	std::cout << "tree4 size:         " << tree4.size() << '\n';

	printLogEnd(__FUNCTION__);
}

void testCopyAssignmentOperator() {
	printLogStart(__FUNCTION__);
	std::cout << std::boolalpha;

	// Will be more sparing in running the print functions in this test function
	// to avoid the test output containing an overwhelming number of tree prints.

	// 1. Test copy assign empty to empty
	std::cout << "(1) Copy assign from an empty tree into an empty tree...\n";
	BinarySearchTree<int> tree1;
	std::cout << "\nBefore copy assign...\n";
	std::cout << "Height of tree1 is: " << tree1.height() << '\n';
	std::cout << "tree1 is empty:     " << tree1.isEmpty() << '\n';
	std::cout << "tree1 size:         " << tree1.size() << "\n\n";

	BinarySearchTree<int> tree2;	
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
	std::cout << "(2) Copy assign from an empty tree into an populated tree...\n";

	// Add some elements to tree1
	// Insert the values into the tree
	int treeVals[] = { 11, 6, 15, 3, 8, 13, 17, 1, 5, 12, 14, 19 };

	for (int i = 0; i < std::size(treeVals); i++)
		tree1.add(treeVals[i]);

	std::cout << "\nBefore copy assign...\n";
	std::cout << "Contents of tree1:\n";
	runPrintFunctions(tree1);
	std::cout << "Height of tree1 is: " << tree1.height() << '\n';
	std::cout << "tree1 is empty:     " << tree1.isEmpty() << '\n';
	std::cout << "tree1 size:         " << tree1.size() << "\n\n";

	// tree2 still empty
	std::cout << "\nCopy assign empty tree2 into populated tree1...\n";
	tree1 = tree2;
	std::cout << "\nAfter copy assign...\n";
	std::cout << "Contents of tree1:\n";
	runPrintFunctions(tree1);
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
		tree2.add(treeVals[i]);

	std::cout << "\nBefore copy assign...\n";
	std::cout << "Contents of tree2:\n";
	runPrintFunctions(tree2);
	std::cout << "Height of tree2 is: " << tree2.height() << '\n';
	std::cout << "tree2 is empty:     " << tree2.isEmpty() << '\n';
	std::cout << "tree2 size:         " << tree2.size() << '\n';
	
	// tree1 still empty
	std::cout << "\nCopy assign populated tree2 into empty tree1...\n";
	tree1 = tree2;
	std::cout << "\nAfter copy assign...\n";
	std::cout << "Contents of tree1:\n";
	runPrintFunctions(tree1);
	std::cout << "Height of tree1 is: " << tree1.height() << '\n';
	std::cout << "tree1 is empty:     " << tree1.isEmpty() << '\n';
	std::cout << "tree1 size:         " << tree1.size() << "\n\n";

	std::cout << "Contents of tree2:\n";
	runPrintFunctions(tree2);
	std::cout << "Height of tree2 is: " << tree2.height() << '\n';
	std::cout << "tree2 is empty:     " << tree2.isEmpty() << '\n';
	std::cout << "tree2 size:         " << tree2.size() << '\n';
	print_separator();

	/*****************************************************************************/

	// 4. Test copy assign populated into populated
	std::cout << "(4) Copy assign from a populated tree into another populated tree...\n";

	// Create a new tree with some different contents
	BinarySearchTree<int> tree3;

	// Populate tree3
	tree3.add(7);
	tree3.add(3);
	tree3.add(10);
	tree3.add(1);
	tree3.add(11);
	tree3.add(9);
	tree3.add(4);

	std::cout << "\nBefore copy assign...\n";
	std::cout << "Contents of tree3:\n";
	runPrintFunctions(tree3);
	std::cout << "Height of tree3 is: " << tree3.height() << '\n';
	std::cout << "tree3 is empty:     " << tree3.isEmpty() << '\n';
	std::cout << "tree3 size:         " << tree3.size() << '\n';

	// tree1 still empty
	std::cout << "\nCopy assign populated tree3 into tree1 (has different contents)...\n";
	tree1 = tree3;
	std::cout << "\nAfter copy assign...\n";
	std::cout << "Contents of tree1:\n";
	runPrintFunctions(tree1);
	std::cout << "Height of tree1 is: " << tree1.height() << '\n';
	std::cout << "tree1 is empty:     " << tree1.isEmpty() << '\n';
	std::cout << "tree1 size:         " << tree1.size() << "\n\n";

	std::cout << "Contents of tree3:\n";
	runPrintFunctions(tree3);
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
	BinarySearchTree<int> tree1;
	std::cout << "\nBefore move assign...\n";
	std::cout << "Height of tree1 is: " << tree1.height() << '\n';
	std::cout << "tree1 is empty:     " << tree1.isEmpty() << '\n';
	std::cout << "tree1 size:         " << tree1.size() << "\n\n";

	BinarySearchTree<int> tree2;
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
	std::cout << "\n\n(2) Move assign from an empty tree into an populated tree...\n";

	// Add some elements to tree1
	// Insert the values into the tree
	int treeVals[] = { 11, 6, 15, 3, 8, 13, 17, 1, 5, 12, 14, 19 };

	for (int i = 0; i < std::size(treeVals); i++)
		tree1.add(treeVals[i]);

	std::cout << "\nBefore move assign...\n";
	std::cout << "Contents of tree1:\n";
	tree1.print(TreeTraversalOrder::LEVEL_ORDER);
	std::cout << "Height of tree1 is: " << tree1.height() << '\n';
	std::cout << "tree1 is empty:     " << tree1.isEmpty() << '\n';
	std::cout << "tree1 size:         " << tree1.size() << "\n\n";

	// tree2 still empty
	std::cout << "\nMove assign empty tree2 into populated tree1...\n";
	tree1 = std::move(tree2);

	std::cout << "\nAfter move assign...\n";
	std::cout << "Contents of tree1:\n";
	tree1.print(TreeTraversalOrder::LEVEL_ORDER);
	std::cout << "Height of tree1 is: " << tree1.height() << '\n';
	std::cout << "tree1 is empty:     " << tree1.isEmpty() << '\n';
	std::cout << "tree1 size:         " << tree1.size() << "\n\n";

	std::cout << "Height of tree2 is: " << tree2.height() << '\n';
	std::cout << "tree2 is empty:     " << tree2.isEmpty() << '\n';
	std::cout << "tree2 size:         " << tree2.size() << '\n';
	print_separator();

	/*****************************************************************************/

	// 3. Test move assign populated into empty
	std::cout << "\n\n(3) Move assign from a populated tree into an empty tree...\n";

	// Repopulate tree2
	for (int i = 0; i < std::size(treeVals); i++)
		tree2.add(treeVals[i]);

	std::cout << "\nBefore move assign...\n";
	std::cout << "Contents of tree2:\n";
	tree2.print(TreeTraversalOrder::LEVEL_ORDER);
	std::cout << "Height of tree2 is: " << tree2.height() << '\n';
	std::cout << "tree2 is empty:     " << tree2.isEmpty() << '\n';
	std::cout << "tree2 size:         " << tree2.size() << '\n';

	// tree1 still empty
	std::cout << "\nMove assign populated tree2 into empty tree1...\n";
	tree1 = std::move(tree2);
	std::cout << "\nAfter move assign...\n";
	std::cout << "Contents of tree1:\n";
	tree1.print(TreeTraversalOrder::LEVEL_ORDER);
	std::cout << "Height of tree1 is: " << tree1.height() << '\n';
	std::cout << "tree1 is empty:     " << tree1.isEmpty() << '\n';
	std::cout << "tree1 size:         " << tree1.size() << "\n\n";

	std::cout << "Contents of tree2:\n";
	tree2.print(TreeTraversalOrder::LEVEL_ORDER);
	std::cout << "Height of tree2 is: " << tree2.height() << '\n';
	std::cout << "tree2 is empty:     " << tree2.isEmpty() << '\n';
	std::cout << "tree2 size:         " << tree2.size() << '\n';
	print_separator();

	/*****************************************************************************/

	// 4. Test move assign populated into populated
	std::cout << "\n\n(4) Move assign from a populated tree into another populated tree...\n";

	// Create a new tree with some different contents
	BinarySearchTree<int> tree3;

	// Populate tree3
	tree3.add(7);
	tree3.add(3);
	tree3.add(10);
	tree3.add(1);
	tree3.add(11);
	tree3.add(9);
	tree3.add(4);

	std::cout << "\nBefore move assign...\n";
	std::cout << "Contents of tree3:\n";
	tree3.print(TreeTraversalOrder::LEVEL_ORDER);
	std::cout << "Height of tree3 is: " << tree3.height() << '\n';
	std::cout << "tree3 is empty:     " << tree3.isEmpty() << '\n';
	std::cout << "tree3 size:         " << tree3.size() << '\n';

	// tree1 still empty
	std::cout << "\nMove assign populated tree3 into tree1 (has different contents)...\n";
	tree1 = std::move(tree3);
	std::cout << "\nAfter move assign...\n";
	std::cout << "Contents of tree1:\n";
	tree1.print(TreeTraversalOrder::LEVEL_ORDER);
	std::cout << "Height of tree1 is: " << tree1.height() << '\n';
	std::cout << "tree1 is empty:     " << tree1.isEmpty() << '\n';
	std::cout << "tree1 size:         " << tree1.size() << "\n\n";

	std::cout << "Contents of tree3:\n";
	tree3.print(TreeTraversalOrder::LEVEL_ORDER);
	std::cout << "Height of tree3 is: " << tree3.height() << '\n';
	std::cout << "tree3 is empty:     " << tree3.isEmpty() << '\n';
	std::cout << "tree3 size:         " << tree3.size() << '\n';

	printLogEnd(__FUNCTION__);
}



void testOneElementBinarySearchTree() {
	printLogStart(__FUNCTION__);

	// 1. Create tree with one element
	BinarySearchTree<int> tree1;
	std::cout << std::boolalpha;

	tree1.add(10);
	std::cout << "Height of tree is: " << tree1.height() << '\n';
	std::cout << "Tree is empty:     " << tree1.isEmpty() << '\n';
	std::cout << "Tree size:         " << tree1.size() << '\n';

	std::cout << "\nTest print output for this tree...\n";
	runPrintFunctions(tree1);

	// 2. Delete from the one element tree
	std::cout << "\nClear this tree...\n";
	tree1.clear();
	std::cout << "Height of tree is: " << tree1.height() << '\n';
	std::cout << "Tree is empty:     " << tree1.isEmpty() << '\n';
	std::cout << "Tree size:         " << tree1.size() << '\n';

	// Repopulate tree
	std::cout << "\n\nAdd one element back into tree...\n";
	tree1.add(5);
	std::cout << "\nContents of the tree:\n";
	tree1.print(TreeTraversalOrder::IN_ORDER);

	// Test contains
	for (int i = 1; i < 10; i++) {
		std::cout << i << " contained in tree: " << tree1.contains(i) << "\n\n";
		std::optional<int> elem = tree1.find(i);
		if (elem.has_value())
			std::cout << "Element found: " << elem.value() << '\n';
		else
			std::cout << "Element not found!\n";
	}
	
	printLogEnd(__FUNCTION__);
}



void testTwoElementBinarySearchTree() {
	printLogStart(__FUNCTION__);

	// 1. Create tree with two elements
	std::cout << "(1) Test adding two elements to a tree...\n";
	BinarySearchTree<int> tree1;
	std::cout << std::boolalpha;

	tree1.add(10);
	tree1.add(20);

	std::cout << "\nContents of tree after additions...\n";
	runPrintFunctions(tree1);

	std::cout << "Height of tree is: " << tree1.height() << '\n';
	std::cout << "Tree is empty:     " << tree1.isEmpty() << '\n';
	std::cout << "Tree size:         " << tree1.size() << '\n';	
	print_separator();

	/**********************************************************************************************/

	std::cout << "\n(2) Test contains method...\n\n";
	for (int i = 0; i < 50; i += 10)
		std::cout << "tree contains: " << i << ": " << tree1.contains(i) << '\n';

	printLogEnd(__FUNCTION__);
}


void testThreeElementBinarySearchTree() {
	printLogStart(__FUNCTION__);

	// 1. Create tree with three elements
	BinarySearchTree<int> tree1;
	std::cout << "(1) Test adding three elements to a tree...\n";
	std::cout << std::boolalpha;

	int nums[] = { 10, 20, 30 };

	// Should be true for the first round of insertions; subsequent
	// iterations should report false.
	for (int i = 1; i < 5; i++) {
		std::cout << "\n\nIteration " << i << ":\n";
		std::cout << nums[0] << " added to tree: " << tree1.add(nums[0]) << "\n";
		std::cout << nums[1] << " added to tree: " << tree1.add(nums[1]) << "\n";
		std::cout << nums[2] << " added to tree: " << tree1.add(nums[2]) << "\n";
	}
	
	// Should only contain three elements - duplicate values will be ignored
	std::cout << "\nContents of tree:\n";
	runPrintFunctions(tree1);
	std::cout << "Height of tree is: " << tree1.height() << '\n';
	std::cout << "Tree is empty:     " << tree1.isEmpty() << '\n';
	std::cout << "Tree size:         " << tree1.size() << '\n';

	std::cout << "\n\nAfter running clear()...\n";
	tree1.clear();
	std::cout << "Height of tree is: " << tree1.height() << '\n';
	std::cout << "Tree is empty:     " << tree1.isEmpty() << '\n';
	std::cout << "Tree size:         " << tree1.size() << '\n';
	print_separator();

	/************************************************************************************/

	// Should only contain three elements now as duplicates added...
	std::cout << "\n(2) Try successively adding elements to a tree...\n";
	int treeVals[] = { 10, 5, 15 };

	for (int i = 0; i < std::size(treeVals); i++) {
		std::cout << "\nContents of tree after " << treeVals[i] << " added...\n";
		tree1.add(treeVals[i]);
		runPrintFunctions(tree1);
		std::cout << "Height of tree is: " << tree1.height() << '\n';
		std::cout << "Tree is empty:     " << tree1.isEmpty() << '\n';
		std::cout << "Tree size:         " << tree1.size() << '\n';		
	}
	print_separator();

	/************************************************************************************/

	// Try a 50-20-10 arrangement
	tree1.clear();
	std::cout << "\nTry adding successively smaller elements to a tree...\n";

	int treeVals2[] = { 50, 20, 10 };
	for (int i = 0; i < std::size(treeVals2); i++) {
		std::cout << "\nContents of tree after " << treeVals2[i] << " added...\n";
		tree1.add(treeVals2[i]);
		runPrintFunctions(tree1);
		std::cout << "Height of tree is: " << tree1.height() << '\n';
		std::cout << "Tree is empty:     " << tree1.isEmpty() << '\n';
		std::cout << "Tree size:         " << tree1.size() << '\n';

		std::cout << "\n\n";	
	}

	printLogEnd(__FUNCTION__);
}


void testMultiElementBinarySearchTree() {
	printLogStart(__FUNCTION__);

	// 1. Create tree with multiple elements
	BinarySearchTree<int> tree1;
	std::cout << std::boolalpha;

	// Insert the values into the tree
	int treeVals[] = { 11, 6, 15, 3, 8, 13, 17, 1, 5, 12, 14, 19 };
	std::optional<int> prev;
	std::optional<int> next;

	for (int i = 0; i < std::size(treeVals); i++) {
		std::cout << "\nContents of tree after " << treeVals[i] << " added...\n";
		tree1.add(treeVals[i]);
		runPrintFunctions(tree1);
		std::cout << "Height of tree is: " << tree1.height() << '\n';
		std::cout << "Tree is empty:     " << tree1.isEmpty() << '\n';
		std::cout << "Tree size:         " << tree1.size() << '\n';		
		print_separator();
	}

	// Test a few finds
	std::cout << "\nTest find elements...\n";
	std::optional<int> item;
	std::vector<int> found;
	std::vector<int> notFound;

	for (int i = 0; i < 21; i++) {
		bool treeContains = tree1.contains(i);
		if (treeContains)
			std::cout << "Tree contains         " << i << '\n';
		else
			std::cout << "Tree DOES NOT contain " << i << '\n';
		item = tree1.find(i);

		if (item.has_value())
			found.push_back(i);
		else
			notFound.push_back(i);
	}
	print_separator();

	printLogEnd(__FUNCTION__);
}


void testTreeRemovals() {
	printLogStart(__FUNCTION__);

	// 1. Create an empty tree to start with
	BinarySearchTree<int> tree1;
	std::cout << std::boolalpha;
	int elem = 20;
	runPrintFunctions(tree1);
	bool removed = tree1.remove(elem);
	if (!removed)
		std::cout << "Success - cannot remove " << elem << " from tree!\n";
	print_separator();

	/****************************************************************************************/

	// 2. Add one element to tree
	elem = 10;
	tree1.add(elem);
	std::cout << "\nContents of tree before remove:\n";
	runPrintFunctions(tree1);

	std::cout << "\nContents of tree after remove non-existent item:\n";
	elem = 20;
	removed = tree1.remove(elem);
	if (!removed)
		std::cout << "Success - cannot remove " << elem << " from tree!\n";
	runPrintFunctions(tree1);

	std::cout << "\nContents of tree after attempted removal of tree's one element:\n";
	elem = 10;
	removed = tree1.remove(elem);
	if (removed)
		std::cout << "Success - removed " << elem << " from tree!\n";
	runPrintFunctions(tree1);
	print_separator();

	/****************************************************************************************/

	// Insert the values into the tree
	std::cout << "\nInsert some new values into the tree...\n";
	int treeVals[] = { 11, 6, 15, 3, 8, 13, 17, 1, 5, 12, 14, 19 };
	std::optional<int> prev;
	std::optional<int> next;

	for (int i = 0; i < std::size(treeVals); i++)
		tree1.add(treeVals[i]);
	runPrintFunctions(tree1);

	print_separator();

	/****************************************************************************************/

	std::cout << "\nNow delete some values...\n";

	// Provides a mix of deletion cases...
	// 1 is a node with no children
	// 8 is a node with a left child only
	// 13 is a node with both a left child and a right child
	// 17 is a node with a right child only
	// 11 is the root node
	int deleteVals[] = { 1, 8, 13, 17, 11 };

	for (int i = 0; i < std::size(deleteVals); ++i) {
		std::cout << "\nAbout to remove " << deleteVals[i] << " ...\n";
		tree1.remove(deleteVals[i]);
		std::cout << "\nContents of tree after " << deleteVals[i] << " removed:\n";
		runPrintFunctions(tree1);
		std::cout << "Height of tree is: " << tree1.height() << '\n';
		std::cout << "Tree is empty:     " << tree1.isEmpty() << '\n';
		std::cout << "Tree size:         " << tree1.size() << '\n';
		print_separator();
	}

	printLogEnd(__FUNCTION__);
}
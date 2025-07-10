// Stack
// -----
// 
// Based on example in YouTube video:
// "Data Structures Easy to Advanced Course - Full Tutorial from a Google Engineer"
//  
// https://youtu.be/RBSGKlAvoiM
// 
// This solution covers the stack data structure. This is a C++ version of the Java
// solution presented in the video, with additional functionality & tests I've added. 
// The notes below are taken from the video.
// 
// Notes on Stacks
// ---------------
//
// A stack is a single-ended linear data structure, which models a real-world
// stack by having two primary operations; push and pop.
// 
// It is a LIFO (Last-In-First-Out) data structure; what comes onto the stack
// last will also be what comes off the stack first.
// 
// They are commonly used for the following applications:
// 1) Undo mechanisms in text editors.
// 2) Compiler-syntax checking.
// 3) Modeling real-world scenarios like a pile of books or plates.
// 4) In programming languages to support recursion by keeping track of
//    previous function calls.
// 5) Depth First Searches (DFS) on a graph.
// 
// They can be implemented with an array, a singly-linked list, or even with
// a doubly-linked list.
//
// 
// Time Complexity of Operations
// -----------------------------
// 
// Operation				Via Linked List							
// ---------				---------------						
// 
// Pushing					O(1)						
// Popping					O(1)						
// Peeking					O(1)					
// Searching				O(n)						
// Size						O(1)	
//
//
// This Implementation
// -------------------
// 
// The stack is a container adaptor of an underlying data structure offering stack 
// functionality. It is a relatively simple data structure, since most of the work is
// done by the underlying structure; I've used my own doubly linked list implementation here.
//
// Since the stack itself is a relatively simple structure, there are fewer core tests required,
// and so I've done some extra tests that actually use the stack structure for some
// common practical programming problems that arise where a stack is a useful mechanism 
// to solve the problem (e.g. reversing a string).

#include <iomanip>
#include <iostream>

#include "Stack.h"

// Routine test functions
void testEmptyStack();
void testStackCopyConstructor();
void testStackMoveConstructor();
void testStackCopyAssignmentOperator();
void testStackMoveAssignmentOperator();
void testStackOtherFunctions();

// Functions that test the stack being used for practical operations
void testReverseStringWithStack();
void testReverseLinkedListWithStack();
void testCheckBalancedParenthesisWithStack();
void testStackDoubleSpecialisation();

// Supplementary test functions
bool parenthesisBalanced(std::string& expression);
bool isPair(const char& openingChar, const char& closingChar);


int main() {
	// Call routine test functions here
	//testEmptyStack();
	//testStackCopyConstructor();
	//testStackMoveConstructor();
	//testStackCopyAssignmentOperator();
	//testStackMoveAssignmentOperator();
	//testStackOtherFunctions();
	
	// Call the more interesting test functions here
	//testReverseStringWithStack();
	//testReverseLinkedListWithStack();
	//testCheckBalancedParenthesisWithStack();
	testStackDoubleSpecialisation();
}


/******************************************************************************************************************************************************/
/******************************** Test functions ******************************************************************************************************/

void testEmptyStack() {
	std::cout << std::boolalpha;

	// 1. Test an empty stack
	std::cout << "Create a stack using the default constructor test...\n";
	Stack<int> stack1;	// Create an empty stack
	std::optional<int> retVal;
	std::cout << "Is stack1 empty: " << stack1.isEmpty() << '\n';
	std::cout << "Size of stack1:  " << stack1.size() << "\n\n";

	retVal = stack1.top();
	if (!retVal.has_value())
		std::cout << "There is no top value on an empty stack!\n";

	retVal = stack1.pop();
	if (!retVal.has_value())
		std::cout << "There is no value to be popped on an empty stack!\n";	
}

void testStackCopyConstructor() {
	std::cout << std::boolalpha;

	// 1. Copy construct from an empty stack
	std::cout << "(1) Copy construct from an empty stack...\n";
	Stack<int> stack1;	// Create an empty stack

	std::optional<int> retVal;
	std::cout << "stack1 is empty: " << stack1.isEmpty() << '\n';
	std::cout << "Size of stack1:  " << stack1.size() << "\n\n";

	retVal = stack1.top();
	if (!retVal.has_value())
		std::cout << "There is no top value on an empty stack!\n";

	retVal = stack1.pop();
	if (!retVal.has_value())
		std::cout << "There is no value to be popped on an empty stack!\n";

	std::cout << "\n\nCopy construct stack2 from stack1...\n";
	Stack<int> stack2(stack1);

	std::cout << "stack2 is empty: " << stack2.isEmpty() << '\n';
	std::cout << "Size of stack2:  " << stack2.size() << "\n\n";

	retVal = stack2.top();
	if (!retVal.has_value())
		std::cout << "There is no top value on an empty stack!\n";

	retVal = stack2.pop();
	if (!retVal.has_value())
		std::cout << "There is no value to be popped on an empty stack!\n";

	/*******************************************************************/

	// 2. Copy construct from an populated stack
	std::cout << "\n\n(2) Copy construct from an populated stack...\n";
	Stack<int> stack3;	// Create an empty stack
	for (int i = 0; i < 11; i++)
		stack3.push(i);

	std::cout << "stack3 is empty: " << stack3.isEmpty() << '\n';
	std::cout << "Size of stack3:  " << stack3.size() << "\n\n";

	retVal = stack3.top();
	if (!retVal.has_value())
		std::cout << "No top reference!\n";
	else
		std::cout << "stack3 elem (top): " << retVal.value() << '\n';

	retVal = stack3.pop();
	if (!retVal.has_value())
		std::cout << "No top reference!\n";
	else
		std::cout << "stack3 elem (pop): " << retVal.value() << '\n';

	std::cout << "\n\nCopy construct stack4 from stack3...\n";
	Stack<int> stack4(stack3);

	std::cout << "stack4 is empty: " << stack4.isEmpty() << '\n';
	std::cout << "Size of stack4:  " << stack4.size() << "\n\n";

	retVal = stack4.top();
	if (retVal.has_value())
		std::cout << "stack4 elem (top): " << retVal.value() << '\n';		
	else
		std::cout << "No top reference!\n";

	retVal = stack4.pop();
	if (retVal.has_value())
		std::cout << "stack4 elem (pop): " << retVal.value() << '\n';
	else
		std::cout << "No top reference!\n";
}

void testStackMoveConstructor() {
	std::cout << std::boolalpha;

	// 1. Move construct from an empty stack
	std::cout << "(1) Move construct from an empty stack...\n";
	Stack<int> stack1;	// Create an empty stack

	std::optional<int> retVal;
	std::cout << "stack1 is empty: " << stack1.isEmpty() << '\n';
	std::cout << "Size of stack1:  " << stack1.size() << "\n\n";

	retVal = stack1.top();
	if (!retVal.has_value())
		std::cout << "There is no top value on an empty stack!\n";

	retVal = stack1.pop();
	if (!retVal.has_value())
		std::cout << "There is no value to be popped on an empty stack!\n";

	std::cout << "\n\nMove construct stack2 from stack1...\n";
	Stack<int> stack2(std::move(stack1));

	std::cout << "stack1 is empty: " << stack1.isEmpty() << '\n';
	std::cout << "Size of stack1:  " << stack1.size() << "\n\n";

	retVal = stack1.top();
	if (!retVal.has_value())
		std::cout << "There is no top value on an empty stack!\n";

	retVal = stack1.pop();
	if (!retVal.has_value())
		std::cout << "There is no value to be popped on an empty stack!\n";

	std::cout << "stack2 is empty: " << stack2.isEmpty() << '\n';
	std::cout << "Size of stack2:  " << stack2.size() << "\n\n";

	retVal = stack2.top();
	if (!retVal.has_value())
		std::cout << "There is no top value on an empty stack!\n";

	retVal = stack2.pop();
	if (!retVal.has_value())
		std::cout << "There is no value to be popped on an empty stack!\n";

	/*******************************************************************/

	// 2. Move construct from an populated stack
	std::cout << "\n\n(2) Move construct from an populated stack...\n";
	Stack<int> stack3;	// Create an empty stack
	for (int i = 0; i < 10; i++)
		stack3.push(i);

	std::cout << "stack3 is empty: " << stack3.isEmpty() << '\n';
	std::cout << "Size of stack3:  " << stack3.size() << "\n\n";

	retVal = stack3.top();
	if (!retVal.has_value())
		std::cout << "No top reference!\n";
	else
		std::cout << "stack3 elem (top): " << retVal.value() << '\n';

	std::cout << "\n\nMove construct stack4 from stack3...\n";
	Stack<int> stack4(std::move(stack3));

	std::cout << "stack3 is empty: " << stack3.isEmpty() << '\n';
	std::cout << "Size of stack3:  " << stack3.size() << "\n\n";

	retVal = stack3.top();
	if (retVal.has_value())
		std::cout << "stack3 elem (top): " << retVal.value() << '\n';
	else
		std::cout << "No top reference!\n";

	std::cout << "\n\n";
	std::cout << "stack4 is empty: " << stack4.isEmpty() << '\n';
	std::cout << "Size of stack4:  " << stack4.size() << "\n\n";

	retVal = stack4.top();
	if (retVal.has_value())
		std::cout << "stack4 elem (top): " << retVal.value() << '\n'; 
	else
		std::cout << "No top reference!\n";

	retVal = stack4.pop();
	if (retVal.has_value())
		std::cout << "stack4 elem (pop): " << retVal.value() << '\n';
	else
		std::cout << "No top reference!\n";
}

void testStackCopyAssignmentOperator() {
	std::cout << std::boolalpha;

	// 1. Test empty copy stack into an already empty stack
	std::cout << "(1) Empty stack assigned into empty stack...\n";
	Stack<int> stack1;
	Stack<int> stack2;

	stack1 = stack2;

	std::optional<int> retVal;
	std::cout << "stack1 is empty: " << stack1.isEmpty() << '\n';
	std::cout << "Size of stack1:  " << stack1.size() << "\n\n";

	retVal = stack1.top();
	if (!retVal.has_value())
		std::cout << "There is no top value for stack1!\n";

	std::cout << "stack1 is empty: " << stack1.isEmpty() << '\n';
	std::cout << "Size of stack1:  " << stack1.size() << "\n\n";

	retVal = stack2.top();
	if (!retVal.has_value())
		std::cout << "There is no top value for stack2!\n";

	std::cout << "stack2 is empty: " << stack2.isEmpty() << '\n';
	std::cout << "Size of stack2:  " << stack2.size() << "\n\n";	

	/****************************************************************************/

	// 2. Test copy populated stack into an empty stack
	std::cout << "\n\n(2) Copy populated stack into empty stack...\n";
	Stack<int> stack3;
	Stack<int> stack4;

	// Insert some values into stack4
	for (int i = 0; i < 5; ++i)
		stack4.push(i);

	std::cout << "\nBefore copy assign...\n";

	retVal = stack3.top();
	if (!retVal.has_value())
		std::cout << "There is no top value for stack3!\n";

	std::cout << "stack3 is empty: " << stack3.isEmpty() << '\n';
	std::cout << "Size of stack3:  " << stack3.size() << "\n\n";

	retVal = stack4.top();
	if (!retVal.has_value())
		std::cout << "There is no top value for stack4!\n";
	else
		std::cout << "stack4 top value: " << retVal.value() << '\n';

	std::cout << "stack4 is empty: " << stack4.isEmpty() << '\n';
	std::cout << "Size of stack4:  " << stack4.size() << "\n\n";

	std::cout << "\n\nCopy assign stack4 into stack3...\n";
	stack3 = stack4;

	std::cout << "\n\nAfter copy assign...\n";

	retVal = stack3.top();
	if (!retVal.has_value())
		std::cout << "There is no top value for stack3!\n";
	else
		std::cout << "stack3 top value: " << retVal.value() << '\n';

	std::cout << "stack3 is empty: " << stack3.isEmpty() << '\n';
	std::cout << "Size of stack3:  " << stack3.size() << "\n\n";

	retVal = stack4.top();
	if (!retVal.has_value())
		std::cout << "There is no top value for stack4!\n";
	else
		std::cout << "stack4 top value: " << retVal.value() << '\n';

	std::cout << "stack4 is empty: " << stack4.isEmpty() << '\n';
	std::cout << "Size of stack4:  " << stack4.size() << "\n\n";

	/****************************************************************************/

	// 3. Test copy empty stack into a populated stack
	std::cout << "\n\n(3) Empty stack assigned into populated stack...\n";

	Stack<int> stack5;
	Stack<int> stack6;

	// Insert some values into stack5
	for (int i = 0; i < 5; ++i)
		stack5.push(i);

	std::cout << "\nBefore copy assign...\n";

	retVal = stack5.top();
	if (!retVal.has_value())
		std::cout << "There is no top value for stack5!\n";
	else
		std::cout << "stack5 top value: " << retVal.value() << '\n';

	std::cout << "stack5 is empty: " << stack5.isEmpty() << '\n';
	std::cout << "Size of stack5:  " << stack5.size() << "\n\n";

	retVal = stack6.top();
	if (!retVal.has_value())
		std::cout << "There is no top value for stack6!\n";
	else
		std::cout << "stack6 top value: " << retVal.value() << '\n';

	std::cout << "stack6 is empty: " << stack6.isEmpty() << '\n';
	std::cout << "Size of stack6:  " << stack6.size() << "\n\n";

	std::cout << "\n\nCopy assign stack6 into stack5...\n";
	stack5 = stack6;

	std::cout << "\n\nAfter copy assign...\n";

	retVal = stack5.top();
	if (!retVal.has_value())
		std::cout << "There is no top value for stack5!\n";
	else
		std::cout << "stack5 top value: " << retVal.value() << '\n';

	std::cout << "stack5 is empty: " << stack5.isEmpty() << '\n';
	std::cout << "Size of stack5:  " << stack5.size() << "\n\n";

	retVal = stack6.top();
	if (!retVal.has_value())
		std::cout << "There is no top value for stack6!\n";
	else
		std::cout << "stack6 top value: " << retVal.value() << '\n';

	std::cout << "stack6 is empty: " << stack6.isEmpty() << '\n';
	std::cout << "Size of stack6:  " << stack6.size() << "\n\n";

	/****************************************************************************/

	// 4. Self-assign empty stack
	std::cout << "\n\n(4) Self-assign empty stack...\n";

	Stack<int> stack7;
	std::cout << "stack7 is empty: " << stack7.isEmpty() << '\n';
	std::cout << "Size of stack7:  " << stack7.size() << "\n\n";

	std::cout << "Self assign stack7 into stack7...\n";
	stack7 = stack7;

	std::cout << "After self-assign...\n";
	std::cout << "stack7 is empty: " << stack7.isEmpty() << '\n';
	std::cout << "Size of stack7:  " << stack7.size() << "\n\n";

	/****************************************************************************/

	// 5. Self-assign populated stack
	std::cout << "\n\n(5) Self-assign populated stack...\n";

	Stack<int> stack8;
	
	// Insert some values into stack9
	for (int i = 0; i < 5; ++i)
		stack8.push(i);

	retVal = stack8.top();
	if (!retVal.has_value())
		std::cout << "There is no top value for stack8!\n";
	else
		std::cout << "stack8 top value: " << retVal.value() << '\n';

	std::cout << "stack8 is empty: " << stack8.isEmpty() << '\n';
	std::cout << "Size of stack8:  " << stack8.size() << "\n\n";

	std::cout << "Self assign stack8 into stack8...\n";
	stack8 = stack8;

	std::cout << "After self-assign...\n";

	retVal = stack8.top();
	if (!retVal.has_value())
		std::cout << "There is no top value for stack8!\n";
	else
		std::cout << "stack8 top value: " << retVal.value() << '\n';

	std::cout << "stack8 is empty: " << stack8.isEmpty() << '\n';
	std::cout << "Size of stack8:  " << stack8.size() << "\n\n";	
}

void testStackMoveAssignmentOperator() {
	std::cout << std::boolalpha;

	// 1. Test move empty stack into an already empty stack
	std::cout << "(1) Empty stack move assigned into empty stack...\n";
	Stack<int> stack1;
	Stack<int> stack2;

	stack1 = std::move(stack2);

	std::optional<int> retVal;
	std::cout << "stack1 is empty: " << stack1.isEmpty() << '\n';
	std::cout << "Size of stack1:  " << stack1.size() << "\n\n";

	retVal = stack1.top();
	if (!retVal.has_value())
		std::cout << "There is no top value for stack1!\n";

	std::cout << "stack1 is empty: " << stack1.isEmpty() << '\n';
	std::cout << "Size of stack1:  " << stack1.size() << "\n\n";

	retVal = stack2.top();
	if (!retVal.has_value())
		std::cout << "There is no top value for stack2!\n";

	std::cout << "stack2 is empty: " << stack2.isEmpty() << '\n';
	std::cout << "Size of stack2:  " << stack2.size() << "\n\n";

	/****************************************************************************/

	// 2. Test move populated stack into an empty stack
	std::cout << "\n\n(2) Move populated stack into empty stack...\n";
	Stack<int> stack3;
	Stack<int> stack4;

	// Insert some values into stack4
	for (int i = 0; i < 5; ++i)
		stack4.push(i);

	std::cout << "\nBefore move assign...\n";

	retVal = stack3.top();
	if (!retVal.has_value())
		std::cout << "There is no top value for stack3!\n";

	std::cout << "stack3 is empty: " << stack3.isEmpty() << '\n';
	std::cout << "Size of stack3:  " << stack3.size() << "\n\n";

	retVal = stack4.top();
	if (!retVal.has_value())
		std::cout << "There is no top value for stack4!\n";
	else
		std::cout << "stack4 top value: " << retVal.value() << '\n';

	std::cout << "stack4 is empty: " << stack4.isEmpty() << '\n';
	std::cout << "Size of stack4:  " << stack4.size() << "\n\n";

	std::cout << "\n\nMove assign stack4 into stack3...\n";
	stack3 = std::move(stack4);

	std::cout << "\n\nAfter move assign...\n";

	retVal = stack3.top();
	if (!retVal.has_value())
		std::cout << "There is no top value for stack3!\n";
	else
		std::cout << "stack3 top value: " << retVal.value() << '\n';

	std::cout << "stack3 is empty: " << stack3.isEmpty() << '\n';
	std::cout << "Size of stack3:  " << stack3.size() << "\n\n";

	retVal = stack4.top();
	if (!retVal.has_value())
		std::cout << "There is no top value for stack4!\n";
	else
		std::cout << "stack4 top value: " << retVal.value() << '\n';

	std::cout << "stack4 is empty: " << stack4.isEmpty() << '\n';
	std::cout << "Size of stack4:  " << stack4.size() << "\n\n";

	/****************************************************************************/

	// 3. Test move empty stack into a populated stack
	std::cout << "\n\n(3) Empty stack move assigned into populated stack...\n";

	Stack<int> stack5;
	Stack<int> stack6;

	// Insert some values into stack5
	for (int i = 0; i < 5; ++i)
		stack5.push(i);

	std::cout << "\nBefore move assign...\n";

	retVal = stack5.top();
	if (!retVal.has_value())
		std::cout << "There is no top value for stack5!\n";
	else
		std::cout << "stack5 top value: " << retVal.value() << '\n';

	std::cout << "stack5 is empty: " << stack5.isEmpty() << '\n';
	std::cout << "Size of stack5:  " << stack5.size() << "\n\n";

	retVal = stack6.top();
	if (!retVal.has_value())
		std::cout << "There is no top value for stack6!\n";
	else
		std::cout << "stack6 top value: " << retVal.value() << '\n';

	std::cout << "stack6 is empty: " << stack6.isEmpty() << '\n';
	std::cout << "Size of stack6:  " << stack6.size() << "\n\n";

	std::cout << "\n\nMove assign stack6 into stack5...\n";
	stack5 = std::move(stack6);

	std::cout << "\n\nAfter move assign...\n";

	retVal = stack5.top();
	if (!retVal.has_value())
		std::cout << "There is no top value for stack5!\n";
	else
		std::cout << "stack5 top value: " << retVal.value() << '\n';

	std::cout << "stack5 is empty: " << stack5.isEmpty() << '\n';
	std::cout << "Size of stack5:  " << stack5.size() << "\n\n";

	retVal = stack6.top();
	if (!retVal.has_value())
		std::cout << "There is no top value for stack6!\n";
	else
		std::cout << "stack6 top value: " << retVal.value() << '\n';

	std::cout << "stack6 is empty: " << stack6.isEmpty() << '\n';
	std::cout << "Size of stack6:  " << stack6.size() << "\n\n";

	/****************************************************************************/

	// 4. Self-assign empty stack
	std::cout << "\n\n(4) Self-assign empty stack...\n";

	Stack<int> stack7;
	std::cout << "stack7 is empty: " << stack7.isEmpty() << '\n';
	std::cout << "Size of stack7:  " << stack7.size() << "\n\n";

	std::cout << "Self assign stack7 into stack7...\n";
	stack7 = std::move(stack7);

	std::cout << "After self-assign...\n";
	std::cout << "stack7 is empty: " << stack7.isEmpty() << '\n';
	std::cout << "Size of stack7:  " << stack7.size() << "\n\n";

	/****************************************************************************/

	// 5. Self-assign populated stack
	std::cout << "\n\n(5) Self-assign populated stack...\n";

	Stack<int> stack8;

	// Insert some values into stack9
	for (int i = 0; i < 5; ++i)
		stack8.push(i);

	retVal = stack8.top();
	if (!retVal.has_value())
		std::cout << "There is no top value for stack8!\n";
	else
		std::cout << "stack8 top value: " << retVal.value() << '\n';

	std::cout << "stack8 is empty: " << stack8.isEmpty() << '\n';
	std::cout << "Size of stack8:  " << stack8.size() << "\n\n";

	std::cout << "Self assign stack8 into stack8...\n";
	stack8 = std::move(stack8);

	std::cout << "After self-assign...\n";

	retVal = stack8.top();
	if (!retVal.has_value())
		std::cout << "There is no top value for stack8!\n";
	else
		std::cout << "stack8 top value: " << retVal.value() << '\n';

	std::cout << "stack8 is empty: " << stack8.isEmpty() << '\n';
	std::cout << "Size of stack8:  " << stack8.size() << "\n\n";
}

void testStackOtherFunctions() {
	std::cout << std::boolalpha;

	// 1. Test an empty stack
	std::cout << "Create a stack using the default constructor test...\n";
	Stack<int> stack1;	// Create an empty stack

	std::cout << "Is stack1 empty: " << stack1.isEmpty() << '\n';
	std::cout << "Size of stack1:  " << stack1.size() << "\n\n";
	
	/*************************************************************************/

	// 2. Test one element constructor
	std::cout << "\n\nCreate a stack using the one arg constructor and test...\n";
	Stack<int> stack2(10);	// Create a stack
	std::optional<int> top_val;
	std::optional<int> pop_val;

	std::cout << "Is stack2 empty: " << stack2.isEmpty() << '\n';
	std::cout << "Size of stack2:  " << stack2.size() << "\n\n";

	top_val = stack2.top();
	if (!top_val.has_value())
		std::cout << "No top reference!\n";
	else
		std::cout << "elem (top):      " << top_val.value() << '\n';

	std::cout << "After call to top()...\n";
	std::cout << "Is stack2 empty: " << stack2.isEmpty() << '\n';
	std::cout << "Size of stack2:  " << stack2.size() << "\n\n";

	pop_val = stack2.pop();
	if (!pop_val.has_value())
		std::cout << "No elements left to pop!\n";
	else
		std::cout << "elem (pop):      " << pop_val.value() << '\n';

	std::cout << "After call to pop()...\n";
	std::cout << "Is stack2 empty: " << stack2.isEmpty() << '\n';
	std::cout << "Size of stack2:  " << stack2.size() << "\n\n";
	
	/*************************************************************************/

	// 3. Test a default stack and add to it
	std::cout << "\n\nCreate a stack using the default constructor and test...\n";
	Stack<int> stack3;	// Create an empty stack

	for (int i = 0; i < 11; i++)
		stack3.push(i);
	std::cout << "Is stack3 empty: " << stack3.isEmpty() << '\n';
	std::cout << "Size of stack3:  " << stack3.size() << '\n';

	try {
		for (int i = 1; i < 12; i++) {
			std::cout << "\n\nIteration " << i << ":\n";
			std::cout << "Is stack3 empty: " << stack3.isEmpty() << '\n';
			std::cout << "Size of stack3:  " << stack3.size() << "\n\n";

			top_val = stack3.top();
			if (!top_val.has_value())
				std::cout << "No top reference!\n";
			else
				std::cout << "elem (top):      " << top_val.value() << '\n';

			pop_val = stack3.pop();
			if (!pop_val.has_value())
				std::cout << "No elements left to pop!\n";
			else
				std::cout << "elem (pop):      " << pop_val.value() << '\n';
		}
	}
	catch (StackEmptyException& se) {
		std::cout << se.what() << '\n';
	}

	std::cout << "Is stack3 empty: " << stack3.isEmpty() << '\n';
	std::cout << "Size of stack3:  " << stack3.size() << '\n';
	
	/*************************************************************************/

	// 4. Test a one arg constructor stack and add to it
	std::cout << "\n\nCreate a stack using one arg constructor and test...\n";
	Stack<int> stack4(10);	// Create a empty stack

	for (int i = 20; i < 110; i += 10)
		stack4.push(i);
	std::cout << "Is stack4 empty: " << stack4.isEmpty() << '\n';
	std::cout << "Size of stack4:  " << stack4.size() << '\n';

	try {
		for (int i = 1; i < 12; i++) {
			std::cout << "\n\nIteration " << i << ":\n";
			std::cout << "Is stack4 empty: " << stack4.isEmpty() << '\n';
			std::cout << "Size of stack4:  " << stack4.size() << "\n\n";

			top_val = stack4.top();
			if (!top_val.has_value())
				std::cout << "No top reference!\n";
			else
				std::cout << "elem (top):      " << top_val.value() << '\n';

			pop_val = stack4.pop();
			if (!pop_val.has_value())
				std::cout << "No elements left to pop!\n";
			else
				std::cout << "elem (pop):      " << pop_val.value() << '\n';
		}
	}
	catch (StackEmptyException& se) {
		std::cout << se.what() << '\n';
	}

	std::cout << "\n\nAfter popping all elements...\n";
	std::cout << "Is stack4 empty: " << stack4.isEmpty() << '\n';
	std::cout << "Size of stack4:  " << stack4.size() << '\n';	
}

/***********************************************************************************/
/************************ REVERSE STRING WITH STACK ********************************/


// Time complexity  -- O(n)
// Space complexity -- O(n)
void reverseWithStack(std::string& s1) {
	Stack<char> stack1;
	std::optional<char> top_val;
	std::optional<char> pop_val;

	// Pushes (a copy of) each character of a string onto the stack 
	// in original order.
	// 
	// E.g. the string hello can be visualised on the stack as:
	// 
	// o -> top of stack
	// l
	// l
	// e
	// h -> bottom of stack
	for (char c : s1)						
		stack1.push(c);

	// The structure of the stack effectively has reversed the string
	// already, it is just a case now of copying that back to the string
	// object itself.
	// 
	// Pop off each character from top to bottom of stack
	// and successively add to first to last slot in the string.
	for (int i = 0; i < s1.length(); i++) {	// Pop off stack

		top_val = stack1.top();
		if (top_val.has_value())
			s1[i] = top_val.value();

		stack1.pop();
	}
}


// Time complexity  -- O(n)
// Space complexity -- O(1)
void reverseWithPointers(char* str, int len) {
	char* pStart = str;				// Set to location of first character in string
	char* pEnd = str + (len - 1);	// Set to location of last character in string

	// Start moves front to back and end moves back to front
	while (pStart < pEnd) {
		char temp = *pStart;
		*pStart++ = *pEnd;
		*pEnd-- = temp;
	}
}

void testReverseStringWithStack() {
	
	std::cout << "Use a stack to reverse a string...\n\n";
	std::string str = "No man is so tall as when he stoops to pet a plant.";
	
	std::cout << "str before reverse is:\n" << str << '\n';
	
	reverseWithStack(str);
	std::cout << "\nstr after reverse is:\n" << str << '\n';

	reverseWithStack(str);
	std::cout << "\nstr after another reverse is:\n" << str << '\n';

	/***********************************************************************/

	// Just compare, reverse a string with pointers...
	std::cout << "\n\nUse pointers to reverse a string...\n\n";
	char str2[] = "Who speaks for horticulture?";
	int len = strlen(str2);
	
	std::cout << "\nstr2 before reverse is:\n" << str2 << '\n';
	reverseWithPointers(str2, len);

	std::cout << "\nstr2 after reverse is:\n" << str2 << '\n';
	reverseWithPointers(str2, len);

	std::cout << "\nstr2 after another reverse is:\n" << str2 << '\n';
}

/****************************************************************************************/
/************************ REVERSE LINKED LIST WITH STACK ********************************/


void testReverseLinkedListWithStack() {
	std::cout << std::boolalpha;

	// 1. Create linked list
	DoublyLinkedList<int> dll;
	std::optional<int> ret_val;

	for (int i = 0; i < 11; i++)
		dll.insertAtTail(i * 10);

	std::cout << "\nContents of linked list before reverse:\n";
	dll.printList();

	// 2. Push list nodes onto stack
	Stack<int> stack1;
	int val;
	while (dll.peekFirst()) {
		val = dll.peekFirst().value();
		stack1.push(val);
		dll.removeFirst();
	}

	std::cout << "\nState of stack after pushing elements from stack and removing nodes from list:\n";
	std::cout << "Stack is empty: " << stack1.isEmpty() << '\n';
	std::cout << "\nState of list after pushing nodes onto stack:\n";
	dll.printList();
	std::cout << "List is empty: " << dll.isEmpty() << '\n';
	std::cout << "Size of list:  " << dll.getSize() << '\n';

	// 3. Pop nodes off stack and reinsert into list
	while (!stack1.isEmpty()) {
		ret_val = stack1.top();		// Get reference to top element on stack
		stack1.pop();				// Remove element from stack
		dll.insertAtTail(ret_val.value());		// Insert at end of list
	}

	std::cout << "\nState of stack after popping stack and inserting nodes back into list:\n";
	std::cout << "Stack is empty: " << stack1.isEmpty() << '\n';

	// 4. Check the state of our list now
	std::cout << "\nState of list after popping stack and inserting nodes back into list:\n";
	dll.printList();
	std::cout << "List is empty: " << dll.isEmpty() << '\n';
	std::cout << "Size of list:  " << dll.getSize() << '\n';	
}



/**********************************************************************************************/
/************************ CHECK BALANCED PARENTHESIS WITH STACK *******************************/

void testCheckBalancedParenthesisWithStack() {
	
	// 1. Test empty expression
	std::cout << "\nTest empty expression...\n";
	std::string expression = "";
	std::cout << "Expression is: " << expression << '\n';
	if (!parenthesisBalanced(expression))
		std::cout << "ERROR: parenthesis in expression found to be not balanced\n";
	else
		std::cout << "SUCCESS: parenthesis in expression found to be balanced\n";
	
	/***************************************************************************************/

	// 2. Test a one-char expression
	std::cout << "\n\nTest expression with one char...\n";
	expression = "[";
	std::cout << "Expression is: " << expression << '\n';
	if (!parenthesisBalanced(expression))
		std::cout << "SUCCESS: parenthesis in expression found to be not balanced\n";
	else
		std::cout << "ERROR: parenthesis in expression found to be balanced\n";
	
	/***************************************************************************************/

	// 3. Test a two-char expression - unbalanced
	std::cout << "\n\nTest an unbalanced expression with two chars...\n";
	expression = "[}";
	std::cout << "Expression is: " << expression << '\n';
	if (!parenthesisBalanced(expression))
		std::cout << "SUCCESS: parenthesis in expression found to be not balanced\n";
	else
		std::cout << "ERROR: parenthesis in expression found to be balanced\n";
	
	/***************************************************************************************/

	// 4. Test a two-char expression - balanced
	std::cout << "\n\nTest a balanced expression with two chars...\n";
	expression = "{}";
	std::cout << "Expression is: " << expression << '\n';
	if (!parenthesisBalanced(expression))
		std::cout << "ERROR: parenthesis in expression found to be not balanced\n";
	else
		std::cout << "SUCCESS: parenthesis in expression found to be balanced\n";
	
	/***************************************************************************************/

	// 5. Test a multi-char expression - balanced
	std::cout << "\n\nTest a balanced expression with multiple chars...\n";
	expression = "([]{})[adas{3454}]";
	std::cout << "Expression is: " << expression << '\n';
	if (!parenthesisBalanced(expression))
		std::cout << "ERROR: parenthesis in expression found to be not balanced\n";
	else
		std::cout << "SUCCESS: parenthesis in expression found to be balanced\n";
	
	/***************************************************************************************/

	// 6. Test a multi-char expression - unbalanced
	std::cout << "\n\nTest an unbalanced expression with multiple chars...\n";
	expression = "([]{}[adas{3454}]";
	std::cout << "Expression is: " << expression << '\n';
	if (!parenthesisBalanced(expression))
		std::cout << "SUCCESS: parenthesis in expression found to be not balanced\n";
	else
		std::cout << "ERROR: parenthesis in expression found to be balanced\n";
	
	/***************************************************************************************/

	// 7. Test another unbalanced multi-char expression
	std::cout << "\n\nTest another unbalanced expression with multiple chars...\n";
	expression = "([){}())";
	std::cout << "Expression is: " << expression << '\n';
	if (!parenthesisBalanced(expression))
		std::cout << "SUCCESS: parenthesis in expression found to be not balanced\n";
	else
		std::cout << "ERROR: parenthesis in expression found to be balanced\n";
	
	/***************************************************************************************/

	// 8. Test another unbalanced multi-char expression
	std::cout << "\n\nTest another unbalanced expression with multiple chars...\n";
	expression = "([{}])()(){}{}{])";
	std::cout << "Expression is: " << expression << '\n';
	if (!parenthesisBalanced(expression))
		std::cout << "SUCCESS: parenthesis in expression found to be not balanced\n";
	else
		std::cout << "ERROR: parenthesis in expression found to be balanced\n";	
}


// The property that must be preserved to make an expression valid is:
// Last parenthesis unclosed must be the first one closed.
//
// We can use a stack to check an expression for this property.
// 
// We create a stack and then process through each character of the expression.
// We place the opening parentheses on the stack as we find them.
// If we find a closing parenthesis, remove the last opening parenthesis on the stack.
// 
// Balance is achieved when:
// a) There is a closing parenthesis to match each opening parenthesis.
// b) There are no parentheses left on the stack at the end of the process.
//
// This function takes a reference to the expression and returns true if its parentheses
// are balanced, otherwise it returns false.
// An expression may be found invalid to be invalid before it is fully checked, in which 
// case the function will return early. Otherwise, the full expression will be checked
// before validity is confirmed.
bool parenthesisBalanced(std::string& expression) {
	// 1. Create stack
	Stack<char> stack;
	std::optional<char> openingChar;

	// 2. Process through loop
	for (char c : expression) {
		if (c == '(' || c == '{' || c == '[')
			stack.push(c);
		else if (c == ')' || c == '}' || c == ']') {
			// Stack empty or top element does not pair with c
			openingChar = stack.top();
			const char& oc = openingChar.value();
			if (stack.isEmpty() || !isPair(oc, c))
				return false;
			else
				stack.pop();
		}
	}

	// 3. Return is stack empty (are parenthesis balanced?)
	return stack.isEmpty();
}

// Checks if a closing brace character matches the 
// its appropriate opening brace character.
bool isPair(const char& openingChar, const char& closingChar) {
	switch (closingChar) {
	case ')':
		if (openingChar != '(')
			return false;
		break;
	case '}':
		if (openingChar != '{')
			return false;
		break;
	case ']':
		if (openingChar != '[')
			return false;
		break;
	default:
		return false;
	}
	return true;
}

void testStackDoubleSpecialisation() {
	std::cout << std::boolalpha;

	// 1. Test an empty double stack
	std::cout << "(1) Create a double stack using the default constructor test...\n";
	Stack<double> stack1;	// Create an empty stack
	std::optional<int> retVal;
	std::cout << "Is stack1 empty: " << stack1.isEmpty() << '\n';
	std::cout << "Size of stack1:  " << stack1.size() << "\n\n";

	retVal = stack1.top();
	if (!retVal.has_value())
		std::cout << "There is no top value on an empty stack!\n";

	retVal = stack1.pop();
	if (!retVal.has_value())
		std::cout << "There is no value to be popped on an empty stack!\n";

	/*************************************************************************/

	// 2. Test one element constructor
	std::cout << "\n\n(2) Create a stack using the one arg constructor and test...\n";
	Stack<double> stack2(10.23);	// Create a stack
	std::optional<double> top_val;
	std::optional<double> pop_val;

	std::cout << "Is stack2 empty: " << stack2.isEmpty() << '\n';
	std::cout << "Size of stack2:  " << stack2.size() << '\n';

	top_val = stack2.top();
	if (!top_val.has_value())
		std::cout << "No top reference!\n";
	else
		std::cout << "elem:            " << top_val.value() << '\n';

	std::cout << "Is stack2 empty: " << stack2.isEmpty() << '\n';
	std::cout << "Size of stack2:  " << stack2.size() << '\n';

	pop_val = stack2.pop();
	if (!pop_val.has_value())
		std::cout << "No elements left to pop!\n";
	else
		std::cout << "elem:            " << pop_val.value() << '\n';

	std::cout << "Is stack2 empty: " << stack2.isEmpty() << '\n';
	std::cout << "Size of stack2:  " << stack2.size() << '\n';
	
	/*************************************************************************/

	// 3. Test a default stack and add to it
	std::cout << "\n\n(3) Create a stack using the default constructor and test...\n";
	Stack<double> stack3;	// Create an empty stack

	for (int i = 0; i < 11; i++)
		stack3.push(i + 0.5);
	std::cout << "Is stack3 empty: " << stack3.isEmpty() << '\n';
	std::cout << "Size of stack3:  " << stack3.size() << '\n';

	try {
		for (int i = 1; i < 12; i++) {
			std::cout << "\n\nIteration " << i << ":\n";
			std::cout << "Is stack3 empty: " << stack3.isEmpty() << '\n';
			std::cout << "Size of stack3:  " << stack3.size() << "\n\n";

			top_val = stack3.top();
			if (!top_val.has_value())
				std::cout << "No top reference!\n";
			else
				std::cout << "elem:            " << top_val.value() << '\n';

			pop_val = stack3.pop();
			if (!pop_val.has_value())
				std::cout << "No elements left to pop!\n";
			else
				std::cout << "elem:            " << pop_val.value() << '\n';
		}
	}
	catch (StackEmptyException& se) {
		std::cout << se.what() << '\n';
	}

	std::cout << "Is stack3 empty: " << stack3.isEmpty() << '\n';
	std::cout << "Size of stack3:  " << stack3.size() << '\n';

	/*************************************************************************/

	// 4. Test a one arg constructor stack and add to it
	std::cout << "\n\n(4) Create a stack using one arg constructor and test...\n";
	Stack<double> stack4(10.60);	// Create a empty stack

	for (int i = 20; i < 110; i += 10)
		stack4.push(i + 0.6);
	std::cout << "Is stack4 empty: " << stack4.isEmpty() << '\n';
	std::cout << "Size of stack4:  " << stack4.size() << '\n';

	try {
		for (int i = 1; i < 12; i++) {
			std::cout << "\n\nIteration " << i << ":\n";
			std::cout << "Is stack4 empty: " << stack4.isEmpty() << '\n';
			std::cout << "Size of stack4:  " << stack4.size() << "\n\n";

			top_val = stack4.top();
			if (!top_val.has_value())
				std::cout << "No top reference!\n";
			else
				std::cout << "elem:            " << top_val.value() << '\n';

			pop_val = stack4.pop();
			if (!pop_val.has_value())
				std::cout << "No elements left to pop!\n";
			else
				std::cout << "elem:            " << pop_val.value() << '\n';
		}
	}
	catch (StackEmptyException& se) {
		std::cout << se.what() << '\n';
	}

	std::cout << "Is stack4 empty: " << stack4.isEmpty() << '\n';
	std::cout << "Size of stack4:  " << stack4.size() << '\n';	
}
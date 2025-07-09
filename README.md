# Data Structures

A collection of my implementations of various data structures in the C++ programming language. Initially, it contains the more commonly known and used data structures, such as linked lists and binary search trees, but I intend to add more in future.

## Objective 1 – Foundational Learning Exercise

A key aim of this exercise is to gain a deeper understanding of the core data structures, particularly those used in implementing the C++ standard library containers. Developing one’s own versions first-hand is the best way (in my experience) to consolidate what one learns about in computer science videos and articles on the subject.

A key resource has been William Fiset's YouTube video "Data Structures Easy to Advanced Course - Full Tutorial from a Google Engineer." His implementations are in Java, so needed to be "translated" into C++ code.

Notable challenges with this process have been documented in the comments of the specific data structure implementations, but as a general overview, this has involved sketching out the conceptual ideas and writing out the basic algorithmic logic of how these structures are created and amended during their operation, before actually writing the code. 

## Objective 2 – Resource for Revising & Enhancing Knowledge

Another key aim of the exercise is to have a repository to refer to for learning and revision purposes. 

In that vein, the comments in the code are liberally applied, and where appropriate, written in natural flowing English (i.e. a style similar to that in this document) in order to explain concepts in the clearest possible fashion. They are expansive in places – hopefully not too verbose, but certainly not the clipped, sparing style one might use in production code. 

This may not suit everyone’s preferences, but I find it far more helpful when refreshing my memory of how a data structure operation works being able to refer to a detailed explanation that captures the understanding gained while creating and testing it, rather than finding a curt comment that only describes what the operation does in simple terms (“removes specified node from tree”).

## Objective 3 – Portfolio

I would like to enhance existing structures in, and add new structures to, this repository as my experience and knowledge of data structures develops. Making this repository public highlights the work I have done in this area to date.

## Objective 4 – Contributions?

Fiset has a sophisticated process setup on his GitHub algorithms repo for other users to fix/enhance the code. This seems like another good idea for the future, but at this early stage the previous three objectives are the more pressing ones, so this last one is yet to be addressed.

## C++ Version

The code has been written and compiled with C++20 and uses C++20 features in various places, so this should be regarded as the minimum version required to be able to run and compile the code.

## Test Code

Files with test code are in .cpp files, with the structures in header files (since they are template classes). 

The approach is a little simplistic; there are various test functions covering a specific aspect or set of related aspects to be tested in the structure, which are called from the main function. Breaking them down into separate test functions allows the call to each to be commented out (or added back in) as desired, allowing the user to focus on particular aspects they wish to test on a particular program run.

Using a formal test framework would doubtless improve these tests considerably, so incorporating that is a future goal. 

Nonetheless, in the meantime, the existing tests are fairly comprehensive. They allow a user to quickly try running operations on the data structures, without having to go through the laborious process of setting up a lot of test data first. Ultimately, one can use or ignore the existing tests as one sees fit.


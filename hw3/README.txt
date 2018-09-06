HOMEWORK 3: MATRIX CLASS


NAME:  Gabriel Maayan


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

Piazza

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.


ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  10



ORDER NOTATION:
For each of the functions below, write the order notation O().
Write each answer in terms of m = the number of rows and n = the
number of columns.  You should assume that calling new [] or delete []
on an array will take time proportional to the number of elements in
the array.

get - O(1)

set - O(1)

num_rows - O(1)

get_column - O(m)

operator<< - O(m*n)

quarter - O(m*n)

operator== - O(m*n)

operator!= - O(m*n)

swap_rows - O(n)

rref (provided in matrix_main.cpp) - O(m^2*n + n^2*m)



TESTING & DEBUGGING STRATEGY: 
Discuss your strategy for testing & debugging your program.  
What tools did you use (gdb/lldb/Visual Studio debugger,
Valgrind/Dr. Memory, std::cout & print, etc.)?  How did you test the
"corner cases" of your Matrix class design & implementation?

I tested all of the functions in Matrix except for quarter because that had been 
tested in a previous test. I tested good and bad inputs for the functions to test 
corner cases and used assert to aid in debugging. I used g++, memg++, 
and Dr. Memory to debug the code.


EXTRA CREDIT: 
Indicate here if you implemented resize() for extra credit.  
Also document the order notation for your resize() function.



MISC. COMMENTS TO GRADER:  
(optional, please be concise!)


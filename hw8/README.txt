HOMEWORK 8: B+ TREES


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


TESTING & DEBUGGING STRATEGY: 
Discuss your strategy for testing & debugging your program.  
What tools did you use (gdb/lldb/Visual Studio debugger,
Valgrind/Dr. Memory, std::cout & print, etc.)?  How did you test the
"corner cases" of your implementation?

To test my program I used a little bit of gdb, but I couldn't figure 
out how to get it to test the things I wanted. I also used Dr. Memory
whenever I had a seg fault and just generally at the end. Finally I 
used a few print tree statements so I could see what was being tested 
and then follow along on that test case with my code the see what was 
going wrong.

I also wrote a few new test cases and added them to a new main function. 
There I tested some corner cases that weren't being tested in the 
provided test file, such as large filled trees with b>3.


MISC. COMMENTS TO GRADER:  
(optional, please be concise!)


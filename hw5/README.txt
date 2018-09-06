HOMEWORK 5: DSRADIO SONG GROUPS


NAME:  Gabriel Maayan


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

Piazza

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.


ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  20



ORDER NOTATION:
For each of the functions below, write the order notation O().
Write each answer in terms of s = the number of songs in the library,
g = the number of song groups, a = the average number of songs by the same 
artist, and l = the average length of song groups.

AddSongToLibrary - O(s+s) - O(s)

GroupExists - O(g)

AddToGroup - O(l+l+l*log(l)) - O(l*log(l))

MakeGroup - O(g)

PrintGroupRewind - O(l) - none of the options really give an average of 
rewind list lengths

PrintLongestGroupRewind - O(l*log(l))

RemoveGroup - O(g*g*l*l*l)

DeleteAllSongGroups - O(g*g*g*l*l*l)

RemoveFromGroup - O(g*l*l)

PrintGroupMarathon - O(a/l)



TESTING & DEBUGGING STRATEGY: 
Discuss your strategy for testing & debugging your program.  
What tools did you use (gdb/lldb/Visual Studio debugger,
Valgrind/Dr. Memory, std::cout & print, etc.)?  How did you test the
"corner cases" of your implementation?

I used a little gdb, mostly Dr. Memory, and, in a few cases where I 
really didn't understand what was going on, I used cout statements.
To test corner cases I wrote an extra input file that ran commands 
on empty libraries and groups as well as ones that had a single 
element in them.

MISC. COMMENTS TO GRADER:  
(optional, please be concise!)


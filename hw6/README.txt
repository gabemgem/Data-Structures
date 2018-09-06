HOMEWORK 6: INVERSE WORD SEARCH


NAME:  Gabriel Maayan


COLLABORATORS AND OTHER RESOURCES: 
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.



Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.

ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  40


ALGORITHM ANALYSIS:
What's the order notation of your algorithm?
It is about: O((s^2)+(r+f)*(w*h*s*l))

This is because deleting duplicates is s^2 and then placing words 
and deleting grids with bad words both depend on w*h*s*l, because they 
have to loop through every space of every board and for every letter in 
the word, and then either r or f respectively.


TEST CASE SUMMARY:
How did your program perform on the different test cases?  Summarize
the running times.  (It's ok if it didn't finish the harder examples.)
What new test cases did you create and how did it perform on those
tests?

Puzzle | Time(s) | Solutions
   1   |  .017   |    8
   2   |  .020   |    4
   3   |  .011   |    6
   4   |  .019   |    4
   5   |  .032   |  100
   6   |  .012   |  208
   7   |  .025   |    0
   8   |  .019   |    8

I made 4 test cases. The first had just a word that was too big and ran
 in .033 seconds. The second had an open spot to test the filling and
 removing duplicates, which ran in .019 seconds. The third had a positive
 and negative word that was the same, which ran in .02 seconds. Finally 
 the fourth one just had all of the letters negative except for z, which 
 ran in .019 seconds.




MISC. COMMENTS TO GRADER:  
Optional, please be concise!



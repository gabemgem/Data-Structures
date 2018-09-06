HOMEWORK 1: AIRLINE SEATING


NAME:  GABRIEL MAAYAN 


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
Piazza, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

Collaborators:
Resources:
Piazza
www.cplusplus.com/reference

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  16



EXPLANATION OF REMOVING PASSENGERS FROM UPGRADE LIST:
Describe the data structure you used to represent the upgrade lists,
and how you removed passengers from these lists.

I used two vectors, one for the Passenger I.D.'s and the other for the classes 
they were going to be upgraded to. This is what I did to remove passengers from
the upgrade lists: for loop to find index of passenger, another for loop that
adds each element from the passenger and class upgrade lists to two other temporary
vectors unless the index was equal to the index found in the first loop. Then I set
the passenger and class upgrade lists equal to their respective temp vector.


MISC. COMMENTS TO GRADER:  
All code commented out was used to test the rest of the code.



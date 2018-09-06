HOMEWORK 7: WORD FREQUENCY MAPS


NAME:  Gabriel Maayan


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

Piazza

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  7



ANALYSIS OF PERFORMANCE OF YOUR ALGORITHM:
(order notation & concise paragraph, < 200 words)

n = total number of words in the sample text file
m = number of unique words in the file
w = width of the sequencing window
p = average number of words observed to follow a particular word

How much memory will the map data structure require, in terms of n, m,
w, and p (order notation for memory use)?
O(w*m*p) - This is because for each 1 width of the window, you have a 
map with all of the unique words, and a map with p words for each 
unique word. This gives w*m*p.


What is the order notation for performance (running time) of each of
the commands?

LoadSampleText2/3 - O(n*log(n)) - Because it has to look at each 
word(n) and then do a lookup/insertion for each one, which is 
log(n) for maps.

printCom2/3 - O(log(p)) - Because it just has to do lookups for each 
word following a word.

genCom2/3 - O(p*log(p)) - Because for each word following the first 
word, it has to do lookups for a next word.


EXTRA CREDIT
Parsing & using punctuation data, implementation supports *any*
window size, new test cases (describe & summarize performance, but
don't include large datasets with submission).



MISC. COMMENTS TO GRADER:  
(optional, please be concise!)



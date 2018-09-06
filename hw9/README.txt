HOMEWORK 7: MINIBLAST


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


HASH FUNCTION DESCRIPTION
I used the hash function given to us in class. I believe originally it 
came from http://www.partow.net/programming/hashfunctions/. The function
manipulates an original number according to the ascii values of each 
character in the key.


HASH TABLE IMPLEMENTATION
The data structure behind my hash table is this:
vector< pair< string, pair< list<int>, bool > > >
I chose a vector so I wouldn't need to worry about memory leaks and it's
not really slower than an array if you are only accessing values. In the 
first pair, the string is the key. In the second pair, the list is a 
list of locations of the key in the input, and the bool is whether the
spot was occupied at some point.


ANALYSIS OF PERFORMANCE OF YOUR ALGORITHM:
(order notation & concise paragraph, < 200 words)

L = length of the genome sequence
q - query length
p - number of different locations where key is found
k - key size (k-mer size)

How much memory will the map data structure require (order notation for memory use)?
O((L-k)*p) - The amount of entries in the vector should be L-k because 
there is an entry for every spot except the last k-1 in the input. Each
entry also takes up p space.


What is the order notation for performance (running time) of each of
the commands?

make_table - O(L-k) - It has to loop over the input L-k times to 
insert all of the k-mers.

print_query - O(p*q) - For each location a key is found, it has to
loop as many times as the query length. I could reduce it to O(p*(q-k))
with a little optimization, but it doesn't really matter with our input.

insert, find, and erase are all O(1) because of the hashing

resize - O((L-k)*p) - It has to go through the whole data structure so 
its performance is the same as the data structure's size. See above.


EXTRA CREDIT
Add a new command to implement the database using one of the other
 data structures that we have covered so far in the course: 
vectors, lists, arrays etc. 

Compare the performance your alternative method to the homework method
by making a table of run times for each of the genomes and query 
sets provided with the homework  and compare the times to build
the index and the times to process the queries. 
Document any new commands you have added in your README file.



MISC. COMMENTS TO GRADER:  
(optional, please be concise!)



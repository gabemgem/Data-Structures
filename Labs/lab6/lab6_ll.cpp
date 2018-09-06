#include <iostream>
#include <list>
#include <string>

// ===========================================================================

// A SIMPLE LINKED LIST CLASS
// (note: it's ok that all the member variables are public for this tiny class)

class Node {
public:
  int value;
  Node* ptr;
};


// ===========================================================================

// a helper function to print the contents of a linked list of Nodes
void print_linked_list(const std::string &name, Node *my_linked_list) {
  // print the name of this list
  std::cout << name;
  // use a temporary pointer to walk down the list
  Node *tmp = my_linked_list;
  while (tmp != NULL) {
    // print out each element
    std::cout << " " << tmp->value;
    tmp = tmp->ptr;
  }
  std::cout << std::endl;
}


// YOU NEED TO WRITE THIS FUNCTION
Node* make_linked_list_from_STL_list(const std::list<int> &lst) {

	if(lst.size()>0) {
		std::list<int>::const_iterator it=lst.begin();
	  Node* ret;
	  Node* node1;
	  Node* node2;
	  ret=new Node();
	  ret->value=*it;
	  ret->ptr=NULL;
	  node1=ret;
	  for(unsigned int i=1; i<lst.size(); i++) {
		  it++;
		  node2=new Node();
		  node2->value=*it;
		  node2->ptr=NULL;
		  node1->ptr=node2;
		  node1=node2;
	  }
	  
	  return ret;
	}
	
	return NULL;

}


// YOU NEED TO WRITE THIS FUNCTION
Node* reverse_nodes_in_linked_list(Node *input) {
if(input!=NULL) {
  Node* node1;
  Node* node2;
  Node* node3;
  
  node1=input;
  if(node1->ptr!=NULL) {
	  node2=node1->ptr;
	  node1->ptr=NULL;
	  while(node2->ptr!=NULL) {
		  node3=node2->ptr;
		  node2->ptr=node1;
		  node1=node2;
		  node2=node3;
	  }
	  node2->ptr=node1;
	  
	  return node2;
  }
  
  return node1;
}
  
return NULL;
}


// ===========================================================================

int main() {

  // manually create a linked list of notes with 4 elements
  Node* a = new Node; 
  a->value = 6; 
  a->ptr = new Node;
  a->ptr->value = 7;
  a->ptr->ptr = new Node;
  a->ptr->ptr->value = 8;
  a->ptr->ptr->ptr = new Node;
  a->ptr->ptr->ptr->value = 9;
  a->ptr->ptr->ptr->ptr = NULL;
  // print out this list
  print_linked_list("a",a);

  // create an STL list with 4 elements
  std::list<int> b;
  b.push_back(10);
  b.push_back(11);
  b.push_back(12);
  b.push_back(13);

  // use the STL list as input to a creator function that creates
  // linked lists with the same data
  Node* c = make_linked_list_from_STL_list(b);
  // print that data
  print_linked_list("c",c);

  std::list<int> l1, l2, l3;
  l2.push_back(1);
  l3.push_back(1);
  l3.push_back(2);
  l3.push_back(3);
  l3.push_back(4);
  l3.push_back(5);
  
  Node* n1 = make_linked_list_from_STL_list(l1);
  print_linked_list("l1", n1);
  
  Node* n2 = make_linked_list_from_STL_list(l2);
  print_linked_list("l2", n2);
  
  Node* n3 = make_linked_list_from_STL_list(l3);
  print_linked_list("l3", n3);
  
  
  
  // reverse a linked list of nodes
  Node* d = reverse_nodes_in_linked_list(c);
  // print this data
  print_linked_list("d",d);

  Node* n4 = reverse_nodes_in_linked_list(n1);
  print_linked_list("n4",n4);
  
  Node* n5 = reverse_nodes_in_linked_list(n2);
  print_linked_list("n5",n5);
  
  Node* n6 = reverse_nodes_in_linked_list(n3);
  print_linked_list("n6",n6);


  // NOTE: We are not deleting any of the Nodes we created...  so this
  //       program has some memory leaks!  More on this in future
  //       lectures & labs :)

}

// ===========================================================================

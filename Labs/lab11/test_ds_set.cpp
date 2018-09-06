#include <iostream>
#include <string>
#include <utility>
#include <cassert>

#include "ds_set.h"

int main() {

  /*ds_set<std::string> set1;
  set1.insert("hello");
  set1.insert("good-bye");
  set1.insert("friend");
  set1.insert("abc");
  set1.insert("puppy");
  set1.insert("zebra");
  set1.insert("daddy");
  set1.insert("puppy");  // should recognize that this is a duplicate!

  assert(set1.sanity_check());
  assert (set1.size() == 7);

  ds_set<std::string>::iterator p = set1.begin();
  assert(p != set1.end() && *p == std::string("abc"));

  p = set1.find( "foo" );
  assert (p == set1.end());

  p = set1.find("puppy");
  assert (p != set1.end());
  assert (*p == "puppy");

  std::cout << "Here is the tree, printed sideways.\n"
	    << "The indentation is proportional to the depth of the node\n"
	    << "so that the value stored at the root is the only value printed\n"
	    << "without indentation.  Also, for each node, the right subtree\n"
	    << "can be found above where the node is printed and indented\n"
	    << "relative to it\n";
  set1.print_as_sideways_tree( std::cout );
  std::cout << std::endl;


  // copy the set
  ds_set<std::string> set2( set1 );
  assert(set1.sanity_check());
  assert(set2.sanity_check());
  assert(set1.size() == set2.size());
  

  //  Now add stuff to set2
  set2.insert( std::string("a") );
  set2.insert( std::string("b") );
  std::cout << "After inserting stuff:\n";
  set2.print_as_sideways_tree( std::cout );
  std::cout << std::endl;
  assert(set1.sanity_check());
  assert(set2.sanity_check());
  assert(set1.size() == set2.size() - 2);


  //  Now erase stuff from set2
  set2.erase("hello");
  set2.erase("a");
  set2.erase("hello"); // should recognize that it's not there anymore!
  set2.erase("abc");
  set2.erase("friend");
  std::cout << "After erasing stuff:\n";
  set2.print_as_sideways_tree( std::cout );
  std::cout << std::endl;
  assert(set1.sanity_check());
  assert(set2.sanity_check());
  assert(set1.size() == set2.size() + 2);*/


  // Test the iterators!
  ds_set<int> test1;
  test1.insert(8);
  test1.insert(4);
  test1.insert(12);
  test1.insert(2);
  test1.insert(6);
  test1.insert(10);
  test1.insert(14);
  test1.insert(1);
  test1.insert(3);
  test1.insert(5);
  test1.insert(7);
  test1.insert(9);
  test1.insert(11);
  test1.insert(13);
  test1.insert(15);

  std::cout<<"\n\n\n---------------------\nNew Tests:\n";
  test1.print_as_sideways_tree(std::cout);

  std::cout<<std::endl<<std::endl;
  tree_iterator<int> iter = test1.begin();
  while(iter!=test1.end()) {
    std::cout<<*iter<<std::endl;
    ++iter;
  }

  std::cout<<"\nNow backwards:\n";
  while(iter!=test1.begin()) {
    --iter;
    std::cout<<*iter<<std::endl;
  }

  test1.insert(16);
  test1.insert(17);
  test1.insert(18);

  std::cout<<"\n\n\n---------------------\nNew Tests:\n";
  test1.print_as_sideways_tree(std::cout);

  std::cout<<std::endl<<std::endl;
  tree_iterator<int> iter2 = test1.begin();
  while(iter2!=test1.end()) {
    std::cout<<*iter2<<std::endl;
    ++iter2;
  }

  std::cout<<"\nNow backwards:\n";
  while(iter2!=test1.begin()) {
    --iter2;
    std::cout<<*iter2<<std::endl;
  }


  std::cout<<"\nAccumulate(should be 171): "<<test1.accumulate(0)<<std::endl;

  ds_set<std::string> test2;
  test2.insert("mary ");
  test2.insert("had ");
  test2.insert("a ");
  test2.insert("little ");
  test2.insert("lamb ");



  std::cout<<"\n\n\n---------------------\nNew Tests:\n";
  test2.print_as_sideways_tree(std::cout);

  std::cout<<std::endl<<std::endl;
  tree_iterator<std::string> iter3 = test2.begin();
  while(iter3!=test2.end()) {
    std::cout<<*iter3<<std::endl;
    ++iter3;
  }

  std::cout<<"\nNow backwards:\n";
  while(iter3!=test2.begin()) {
    --iter3;
    std::cout<<*iter3<<std::endl;
  }


  std::cout<<"\nAccumulate(should include mary had a little lamb):\n"
           <<test2.accumulate("")<<std::endl;





  return 0;
}

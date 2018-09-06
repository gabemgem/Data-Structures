#include "Time.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <stdint.h>
#include <cstdio>
#include <cassert>
#include <iomanip>
#include <string>

using namespace std;


// GLOBAL VARIABLES used by print_stack, label_stack, and clear_stack
std::vector<uintptr_t*> GLOBAL_addresses;
std::vector<std::string> GLOBAL_labels;


// ==============================================================================
//
// This function does a limited print of the data stored on the stack
// in the range of the addresses currently "labeled" and stored in the
// global variables above.
//
// To make the output more readable, the function assumes that integer
// "values" will be between -1000 & 1000 and addresses will be within
// +/- 1000*4 (or *8) bytes from any of the labeled addresses.
// Anything else is assumed to be "garbage"
//
void print_stack() { 

  assert (GLOBAL_addresses.size() == GLOBAL_labels.size());
  if (GLOBAL_addresses.size() == 0) {
    std::cerr <<  "No labeled addresses to print" << std::endl;
    return;
  }

  // Identify the range of stack data to print
  uintptr_t* min_address = GLOBAL_addresses[0];
  uintptr_t* max_address = GLOBAL_addresses[0];
  int max_label_width = GLOBAL_labels[0].size();
  for (int i = 1; i < GLOBAL_addresses.size(); i++) {
    if (GLOBAL_addresses[i] > max_address) { max_address = GLOBAL_addresses[i]; }
    if (GLOBAL_addresses[i] < min_address) { min_address = GLOBAL_addresses[i]; }
    if (GLOBAL_labels[i].size() > max_label_width) { max_label_width = GLOBAL_labels[i].size(); }
  }

  // double check that my uintptr_t is actually the size of a pointer
  assert (sizeof(uintptr_t) == sizeof(void*));
  // double check that the start and end address are aligned 
  assert ((((uintptr_t)min_address) & (sizeof(uintptr_t)-1)) == 0);
  assert ((((uintptr_t)max_address) & (sizeof(uintptr_t)-1)) == 0);

  // double check that the range of address is reasonable 
  if (max_address-min_address > 1000) {
    std::cerr << "WARNING: trying to print too much" << std::endl;
    return;
  }

  // loop over all addresses in the range (plus some above & below)
  std::cout << "-----------------------------------------" << std::endl;
  for (uintptr_t* address = max_address+5; address >= min_address-5; address--) {
    std::string label = "";
    for (int i = 0; i < GLOBAL_addresses.size(); i++) {
      if (address == GLOBAL_addresses[i]) { label = GLOBAL_labels[i]; }
    }
    std::cout << std::setw(max_label_width) << label << " location: " << address;

    // this location might store a value (we assume all values are integers)
    int an_int = (int)(*address);
    // or it might store an address (so we cast it to a pointer)
    uintptr_t* an_address = (uintptr_t*)(*address);

    // if it's a value
    if (an_int > -1000 && an_int < 1000) {
      std::cout << "  VALUE:   " << an_int << std::endl;
    } 
    // if it's an address
    else if (an_address >= min_address-1000 && an_address <= max_address+1000) {
      std::cout << "  POINTER: " << an_address << std::endl;
    }
    // otherwise it's probably garbage
    else { 
      std::cout << "  garbage? " << std::endl;
    }
  }
  std::cout << "-----------------------------------------" << std::endl;
}


// add a label to a particular address in the stack
// NOTE: We use global variables for simplicity for this exercise
void label_stack(uintptr_t* address, const std::string& tag) {
  for (int i = 0; i < GLOBAL_addresses.size(); i++) {
    // check to see if that address is already labeled
    if (address == GLOBAL_addresses[i]) {
      // add additional labels
      GLOBAL_labels[i] += ", " + tag;      
      return;
    }
  }
  GLOBAL_addresses.push_back(address);
  GLOBAL_labels.push_back(tag);
}


// clear all previous labels
// NOTE: We use global variables for simplicity for this exercise
void clear_stack_labels() {
  GLOBAL_addresses.clear();
  GLOBAL_labels.clear();
}




void change_times(Time& t1, Time t2)
{
	t1.setHour(t1.getHour()+2);
	t1.setMinute(t1.getMin()+30);
	t1.setSecond(t1.getSec()+30);
	
	t2.setHour(t2.getHour()+2);
	t2.setMinute(t2.getMin()+30);
	t2.setSecond(t2.getSec()+30);
	
	label_stack((uintptr_t*)&t1, "t1");
	label_stack((uintptr_t*)&t2, "t2");
	
	print_stack();
}

int main()
{
	Time t1(5, 10, 10);
	Time t2(13, 15, 0);
	
	label_stack((uintptr_t*)&t1, "t1");
	label_stack((uintptr_t*)&t2, "t2");
	
	print_stack();
	
	cout<<endl<<endl<<endl;
	
	change_times(t1, t2);
	
	cout<<endl<<sizeof(Time)<<endl;
	
	/*std::cout<<t1.getHour()<<std::endl<<t1.getMin()<<std::endl<<t1.getSec()<<std::endl<<std::endl;
	
	std::cout<<t2.getHour()<<std::endl<<t2.getMin()<<std::endl<<t2.getSec()<<std::endl<<std::endl;
	
	t1.PrintAmPm();
	
	t2.setHour(12);
	t2.setMinute(5);
	t2.setSecond(1);
	
	std::cout<<t2.getHour()<<std::endl<<t2.getMin()<<std::endl<<t2.getSec()<<std::endl<<std::endl;
	
	t2.PrintAmPm();
	
	t1.setHour(23);
	
	t1.PrintAmPm();
	
	std::cout<<"\n\n\n";
	
	
	std::vector<Time> times;
	
	Time t3;
	Time t4(9,30,0);
	Time t5(9, 35, 0);
	Time t6(9, 35, 5);
	times.push_back(t4);
	times.push_back(t6);
	times.push_back(t3);
	times.push_back(t5);
	
	std::cout<<"\nUnsorted:\n";
	
	for(unsigned int i=0; i<times.size(); i++)
	{
		times[i].PrintAmPm();
	}
	
	std::cout<<"\n\nSorted:\n";
	
	sort(times.begin(), times.end(), IsEarlierThan);
	
	for(unsigned int i=0; i<times.size(); i++)
	{
		times[i].PrintAmPm();
	}*/
}
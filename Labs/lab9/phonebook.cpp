// A simple "caller ID" program

#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;

// add a number, name pair to the phonebook
void add(vector<string> &phonebook, int number, string const& name) {
  phonebook[number] = name;
}

void addM(map<unsigned int,string>& m, unsigned int number, string const& name) {
  m.insert(make_pair(number,name));
}

void identifyM(const map<unsigned int,string>& m, unsigned int num) {
  map<unsigned int,string>::const_iterator i = m.find(num);
  if(i==m.end())
    cout << "unknown caller!" << endl;
  else
    cout<<i->second<<" is calling!"<<endl;
}

// given a phone number, determine who is calling
void identify(const vector<string> & phonebook, int number) {
  if (phonebook[number] == "UNASSIGNED") 
    cout << "unknown caller!" << endl;
  else 
    cout << phonebook[number] << " is calling!" << endl;
}


int main() {
  // create the phonebook; initially all numbers are unassigned
  vector<string> phonebook(10000, "UNASSIGNED");
  map<unsigned int,string> m;

  // add several names to the phonebook
  add(phonebook, 1111, "fred");
  add(phonebook, 2222, "sally");
  add(phonebook, 3333, "george");

  addM(m, 1111, "fred");
  addM(m, 2222, "sally");
  addM(m, 3333, "george");
  addM(m, 3333333, "nancy");
  addM(m, 1, "clive");
  addM(m, 1000000000, "pappy");

  // test the phonebook
  identify(phonebook, 2222);
  identify(phonebook, 4444);

  identifyM(m, 2222);
  identifyM(m, 4444);
  identifyM(m, 0);
  identifyM(m, 3333333);
  identifyM(m, 1000000000);
}

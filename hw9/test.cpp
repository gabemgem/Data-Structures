#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <vector>
#include <utility>
#include <cstdlib>
#include "hash.h"

using namespace std;


//function to set up a hash table from a string of input
//input is the input from an input file, n is the starting size of the table
//f is the occupancy limit, and k is the k-mer size
hash_maayan make_table(const string& input, int n, float f, int k) {

	

	hash_maayan table(n, f);//make a new table
	unsigned int pos1=0, pos2=k-1;//keep track of two positions

	if(pos2>input.size()-1) {//make sure k is < the size of input
		cerr<<"k is too big: "<<k<<endl;
		exit(1);
	}

	while(pos2<input.size()) {//go to the end of the input
		table.insert(input.substr(pos1, k), pos1);//insert a k-mer starting at pos1 with
		++pos1; ++pos2;		//length of k from input. pos1 is the location of the k-mer
	}

	return table;//return the new hash table

}


//function to print a query command. table is the hash table to find positions in
//m is the # of allowed mismatches, k is the k-mer size, query is the query string
//input is all of the input from the input file
void print_query(hash_maayan& table, int m, int k, 
				 const string& query, const string& input) {

	unsigned int ksize=k;//used to compare against an unsigned int
	if(query.size()<ksize) {//make sure query is >= than the k-mers
		cout<<query.size()<<" : query size too small, k="<<k<<endl;
		exit(1);
	}

	bool found = false;//check to see if it has been found at the end

	cout<<"Query: "<<query<<endl;
	list<int> positions = table.find(query.substr(0, k));//get positions of k-mer
	if(positions.empty()) {//if there are no positions found
		cout<<"No Match\n";
		return;
	}

	list<int>::iterator it = positions.begin();//iterate through list of positions
	
	
	for(list<int>::iterator i=positions.begin(); i!=positions.end(); ++i) {
		int index = *i, mm=0;//mm is the current # of mismatches
		unsigned int l=1;//l is the length of the found string so far
		string s="";//s is the found string so far
		s+=input[index];//put the first letter in
		while(l<query.size() && mm<=m) {//while the found string is < query size
			++index;					  //and there aren't too many mismatches
			
			if(input[index]!=query[l]) {//increment mm if there is a mismatch
				++mm;
				if(mm>m)
					break;
			}
			s+=input[index];//add letters to the found string
			++l;
		}

		if(s.size()==query.size()) {//if find enough letters
			cout<<*i<<" "<<mm<<" "<<s<<endl;//output position, mismatches, and found string
			found=true;
		}
	}
	if(!found)//if didn't find a match, say so
		cout<<"No Match\n";
	

}




int main() {
	
	int n, k;//n is table size, k is k-mer size
	float f;//f is occupancy limit
	string com, filename;//com is the command, filename is the input file
	cin>>com;

	if(com!="genome") {//read in input setting variables as necessary
		cout<<com<<" : Invalid Input\n";
		return 1;
	}
	cin>>filename;
	cin>>com;
	if(com=="table_size") {
		cin>>n>>com;
	}
	else
		n=100;
	if(com=="occupancy") {
		cin>>f>>com;
		
	}
	else
		f=.5;
	if(com!="kmer") {
		cout<<com<<" : Invalid Input\n";
		return 1;
	}
	cin>>k;

	ifstream istr(filename.c_str());
	if (!istr) { 
		cerr << "ERROR cannot open file: " << filename << endl; 
		exit(1);
	}

	string input, temp;//read in all of the input file into input
	istr>>input;
	while(istr>>temp)
		input+=temp;

	hash_maayan table = make_table(input, n, f, k);//make the hash table


	while(cin>>com) {//process all of the query commands as well as quit
		if(com=="quit")
			return 0;
		else if(com!="query") {
			cout<<com<<" : Invalid Input\n";
			return 1;
		}
		int m;//max # of mismatches
		string query;
		cin>>m>>query;

		print_query(table, m, k, query, input);//call the query function
	}

	return 0;
}
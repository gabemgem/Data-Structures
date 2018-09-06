#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <vector>
#include <utility>
#include <cstdlib>

using namespace std;

class string_hash {
	public:
		unsigned int operator() (string const& key) const {
			// This implementation comes from
			// http://www.partow.net/programming/hashfunctions/
			unsigned int hash = 1315423911;
			for(unsigned int i = 0; i < key.length(); i++)
				hash ^= ((hash << 5) + key[i] + (hash >> 2));
			return hash;
		}
};

class hash_maayan {
	private:
		vector<pair<string, pair<list<int>, bool> > > table;
		//string is the key, list holds the locations, bool is whether the spot was occupied
		string_hash hashf;//hash functor
		unsigned int tsize;//filled size
		float occupancy;//occupancy limit



	public:

		hash_maayan(unsigned int isize=100, float ioccupancy=.5) {//default constructor
			tsize=0;//sets filled size
			occupancy=ioccupancy;//sets occupancy limit
			list<int> fill;
			table=vector<pair<string, pair<list<int>, bool> > >//sets up table with empty
					(isize, make_pair("",make_pair(fill, false)));//strings, lists, false
		}

		//copy constructor
		hash_maayan(const hash_maayan& old) : table(old.table), tsize(old.tsize) {}

		//no real need for destructor
		~hash_maayan() {}

		//not really needed but possibly helpful
		hash_maayan& operator=(const hash_maayan& old) {
			if(&old!=this)
				*this=old;
			return *this;
		}

		//return filled size
		unsigned int size() const {return tsize;}
		//return maximum size, for testing
		unsigned int fsize() const {return table.size();}

		//insert function, key is the k-mer, loc is the location
		bool insert(string const& key, int loc) {

			//if(key=="TATTACTGCC")
				//cout<<"found key\n\n";

			if(tsize/table.size()>=occupancy)//resize if over occupancy limit
				this->resize();

			unsigned int hval = hashf(key);//hash of key
			unsigned int index = hval%table.size();//index in bounds from hash

			if(table[index].first==key) {//if spot already has key
				table[index].second.first.push_back(loc);//add location to list
				table[index].second.second=true;//set spot as occupied
				return true;
			}
			else if(table[index].first=="") {//if spot is empty
				table[index].first=key;//set string as key
				table[index].second.first.push_back(loc);//add location to list
				table[index].second.second=true;//set spot as occupied
				++tsize;//increase filled size
				return true;
			}
			else {//otherwise find a different spot
				while(table[index].first!="") {//until there's an empty spot
					++index;
					if(index==table.size()) {//loop back to the front if no spots at back
						index=0;
					}
					if(table[index].first==key) {//if finds a spot with the key
						table[index].second.first.push_back(loc);//add location to list
						table[index].second.second=true;//set spot as occupied
						return true;
					}
				}
				table[index].first=key;//once you've found a spot insert key and location
				table[index].second.first.push_back(loc);
				table[index].second.second=true;
				++tsize;
				return true;
			}


		}

		
		//find function return list of locations for a key
		const list<int> find(const string& key) {
			int index=ifind(key);//get index of key

			if(index==-1) {//if couldn't find key, return an empty list
				return list<int>();
			}

			return table[index].second.first;//otherwise return that key's list of loc's

		}

		//erase function
		bool erase(const string& key) {
			int index=ifind(key);//get index of key
			if(index==-1)//if couldn't find key
				return false;//just return false

			table[index].first="";//otherwise clear out space
			table[index].second.first.clear();
			--tsize;//and decrease filled size

			//note: the space is left with a "true" bool showing it was once occupied
		}

		

		//print function return a string with an index's key and list of locations
		string printIndex(unsigned int index) {
			if(index<table.size()) {
				string ret = table[index].first;
				if(table[index].second.first.empty()) {
					ret+="  ---  but no found indicies";
					return ret;
				}
				list<int>::iterator i=table[index].second.first.begin();
				while(i!=table[index].second.first.end()) {
					ret+=" ";
					ret+=(*i);
					cout<<*i<<endl;
					++i;
				}
				return ret;
			}

			return "Invalid Index";
		}

	private:

		//find function return index of a key
		int ifind(const string& key) {
			unsigned int hval = hashf(key);//get where to start looking
			unsigned int index=hval%table.size();

			while(table[index].first!=key) {//loop to find key
				++index;
				if(!table[index].second.second)//if it finds an unoccupied space
					return -1;//return -1
				if(index==table.size()) {//if reach end of table, loop around to front
					index=0;
				}
			}

			return index;//return the index
		}
		
		//resize function doubles size of table
		void resize() {
			//store table in a temp vector
			vector<pair<string, pair<list<int>,bool> > > temp = table;

			list<int> fill;
			//make table a new empty vector of twice the old size
			table=vector<pair<string, pair<list<int>,bool> > >
							(temp.size()*2, make_pair("",make_pair(fill, false)));

			for(unsigned int i=0; i<temp.size(); ++i) {//for each old entry in table
				if(temp[i].first!="") {//if there is a key
					list<int>::iterator loc = temp[i].second.first.begin();
					while(loc!=temp[i].second.first.end()) {//for each location for the key
						this->insert(temp[i].first, *loc);//reinsert it into new table
						++loc;
					}//this will re-hash all of the entries so they can be found
				}
			}


		}

};

// pair<string, pair<list<int>, bool> >
// vector<pair<string, pair<list<int>, bool> > >
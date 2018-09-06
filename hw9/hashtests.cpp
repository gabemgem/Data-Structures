#include <iostream>
#include <string>


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


int main() {
	cout<<"Testing hash function:\n";

	string in, query;
	string_hash hashf;
	int tsize=10;
	int hash;
	while(cin>>in) {
		if(in=="q")
			return 0;
		if(in=="ts")
			cin>>tsize;
		else {
			cin>>query;
			hash=hashf(query);
			cout<<"Query: "<<query<<"\nts: "<<tsize<<"\nHash: "<<hash<<"\nIndex: "<<hash%tsize<<endl<<endl;
		}
	}
	return 0;
}
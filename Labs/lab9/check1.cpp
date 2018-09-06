#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <cstdlib>
#include <string>

using namespace std;

int main(int argc, char** argv) {
	if(argc!=2)
		return 1;

	ifstream istr(argv[1]);
  	if (!istr) { 
		cerr << "ERROR cannot open file: " << argv[1] << endl; 
		exit(1);
	}

	map<int, int> data;
	vector<int> modes;
	int max=0;
	int num;

	while(istr>>num) {
		++data[num];
	}

	for(map<int,int>::iterator i=data.begin(); i!=data.end(); i++) {
		if(i->second==max)
			modes.push_back(i->first);
		else if(i->second>max) {
			max=i->second;
			modes.clear();
			modes.push_back(i->first);
		}
	}

	cout<<"MODES:\n";
	for(unsigned int j=0; j<modes.size(); j++)
		cout<<"\t"<<modes[j]<<endl;

	return 0;

}
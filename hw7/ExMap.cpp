#include "ExMap.h"
#include <map>

using namespace std;

ExMap::ExMap() {
	value=0;
	extend=false;
}

ExMap::ExMap(bool ex) {
	extend=ex;
	if(extend) {
		value=-1;
	}
	else {
		value=0;
	}
}

ExMap::ExMap(int v) {
	extend=false;
	value=v;
}

ExMap::ExMap& operator[](string s) {
	return data[s];
}

bool ExMap::operator++() {
	if(extend)
		return false;
	++value;
	return true;
}

map<string, ExMap>::iterator ExMap::find(string s) {
	map<string, ExMap>::iterator i = data.begin();
	while(i!=data.end()) {
		if(i->first==s)
			break;
	}
	return i;
}

bool ExMap::isExt() {return extend;}
int ExMap::get() {return value;}
void ExMap::ext() {extend=true;}

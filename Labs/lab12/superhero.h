#ifndef SUPPY_ASASAS
#define SUPPY_ASASAS

#include <string>
#include <iostream>

using namespace std;

class Superhero {
private:
	string name, iden, power;
	bool good;

	string getTrueIdentity() const {return iden;}

public:
	Superhero(string n="", string i="", string p="") 
			  : name(n), iden(i), power(p), good(true) {}

	string getName() const {return name;}

	string getPower() const {return power;}

	bool isGood() const {return good;}

	bool operator==(const string& i) {return iden==i;}
	bool operator!=(const string& i) {return iden!=i;}

	 

	void operator-() {good=!good;}

	bool operator>(const Superhero& s2) {
		if(power=="Fire" && s2.power=="Wood")
			return true;
		if(power=="Wood" && s2.power=="Water")
			return true;
		if(power=="Water" && s2.power=="Fire")
			return true;
		int pnum1=0, pnum2=0;
		for(unsigned int i=0; i<power.size(); i++)
			pnum1+=power[i];
		for(unsigned int j=0; j<s2.power.size(); j++)
			pnum2+=s2.power[j];
		return pnum1>pnum2;
	}

	friend ostream& operator<<(ostream& os, const Superhero& s);
	friend class Team;
};

ostream& operator<<(ostream& os, const Superhero& s) ;

#endif
#include <string>
#include <iostream>
#include "superhero.h"

using namespace std;

ostream& operator<<(ostream& os, const Superhero& s)  
{
	if(s.isGood()) {
	    os << "Superhero "<<s.getName()<<" has power "<<s.getPower()<<endl;  
	    return os;  
	}
	else {
		os << "Supervillain "<<s.getName()<<" has power "<<s.getPower()<<endl;  
	    return os; 
	}
}

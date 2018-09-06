#include <map>
#include <vector>
#include <string>
#include <iostream>
#include "pokemon.h"

using namespace std;

bool Pokemon::SharesEggGroup(Pokemon* p) {
	for(unsigned int i=0; i<p->facts["eggGroups"].size(); ++i) {
		for(unsigned int j=0; j<this->facts["eggGroups"].size(); ++j) {
			if(p->facts["eggGroups"][i]==this->facts["eggGroups"][j])
				return true;
		}
	}
	return false;
}

Amorphous::Amorphous(const map<string, vector<string> >& f) : Pokemon(f) {
	bool found=false;
	for(unsigned int i=0; i<facts["eggGroups"].size(); ++i)
		if(facts["eggGroups"][i]=="Amorphous")
			found=true;
	if(!found)
		throw 1;
}

Bug::Bug(const map<string, vector<string> >& f) : Pokemon(f) {
	bool found=false;
	for(unsigned int i=0; i<facts["eggGroups"].size(); ++i)
		if(facts["eggGroups"][i]=="Bug")
			found=true;
	if(!found)
		throw 1;
}

Dragon::Dragon(const map<string, vector<string> >& f) : Pokemon(f) {
	bool found=false;
	for(unsigned int i=0; i<facts["eggGroups"].size(); ++i)
		if(facts["eggGroups"][i]=="Dragon")
			found=true;
	if(!found)
		throw 1;
}

Fairy::Fairy(const map<string, vector<string> >& f) : Pokemon(f) {
	bool found=false;
	for(unsigned int i=0; i<facts["eggGroups"].size(); ++i)
		if(facts["eggGroups"][i]=="Fairy")
			found=true;
	if(!found)
		throw 1;
}

Field::Field(const map<string, vector<string> >& f) : Pokemon(f) {
	bool found=false;
	for(unsigned int i=0; i<facts["eggGroups"].size(); ++i)
		if(facts["eggGroups"][i]=="Field")
			found=true;
	if(!found)
		throw 1;
}

Flying::Flying(const map<string, vector<string> >& f) : Pokemon(f) {
	bool found=false;
	for(unsigned int i=0; i<facts["eggGroups"].size(); ++i)
		if(facts["eggGroups"][i]=="Flying")
			found=true;
	if(!found)
		throw 1;
}

Grass::Grass(const map<string, vector<string> >& f) : Pokemon(f) {
	bool found=false;
	for(unsigned int i=0; i<facts["eggGroups"].size(); ++i)
		if(facts["eggGroups"][i]=="Grass")
			found=true;
	if(!found)
		throw 1;
}

HumanLike::HumanLike(const map<string, vector<string> >& f) : Pokemon(f) {
	bool found=false;
	for(unsigned int i=0; i<facts["eggGroups"].size(); ++i)
		if(facts["eggGroups"][i]=="HumanLike")
			found=true;
	if(!found)
		throw 1;
}

Mineral::Mineral(const map<string, vector<string> >& f) : Pokemon(f) {
	bool found=false;
	for(unsigned int i=0; i<facts["eggGroups"].size(); ++i)
		if(facts["eggGroups"][i]=="Mineral")
			found=true;
	if(!found)
		throw 1;
}

Monster::Monster(const map<string, vector<string> >& f) : Pokemon(f) {
	bool found=false;
	for(unsigned int i=0; i<facts["eggGroups"].size(); ++i)
		if(facts["eggGroups"][i]=="Monster")
			found=true;
	if(!found)
		throw 1;
}

Water1::Water1(const map<string, vector<string> >& f) : Pokemon(f) {
	bool found=false;
	for(unsigned int i=0; i<facts["eggGroups"].size(); ++i)
		if(facts["eggGroups"][i]=="Water1")
			found=true;
	if(!found)
		throw 1;
}

Water2::Water2(const map<string, vector<string> >& f) : Pokemon(f) {
	bool found=false;
	for(unsigned int i=0; i<facts["eggGroups"].size(); ++i)
		if(facts["eggGroups"][i]=="Water2")
			found=true;
	if(!found)
		throw 1;
}

Water3::Water3(const map<string, vector<string> >& f) : Pokemon(f) {
	bool found=false;
	for(unsigned int i=0; i<facts["eggGroups"].size(); ++i)
		if(facts["eggGroups"][i]=="Water3")
			found=true;
	if(!found)
		throw 1;
}

Ditto::Ditto(const map<string, vector<string> >& f) : Pokemon(f) {
	bool found=false;
	for(unsigned int i=0; i<facts["eggGroups"].size(); ++i)
		if(facts["eggGroups"][i]=="Ditto")
			found=true;
	if(!found)
		throw 1;
}

Undiscovered::Undiscovered(const map<string, vector<string> >& f) : Pokemon(f) {
	bool found=false;
	for(unsigned int i=0; i<facts["eggGroups"].size(); ++i)
		if(facts["eggGroups"][i]=="Undiscovered")
			found=true;
	if(!found)
		throw 1;
}

//----------------------------------------------//

Amaura::Amaura(const map<string, vector<string> >& f) : Monster(f) {
	for(unsigned int i=0; i<facts["abilities"].size(); ++i) {
		if(facts["abilities"][i]!="120" && facts["abilities"][i]!="0" && facts["abilities"][i]!="143")
			throw 1;
	}
}

Aurorus::Aurorus(const map<string, vector<string> >& f) : Amaura(f) {
	
	if(facts["height"][0]!="2.700000")
		throw 1;
	if(facts["weight"][0]!="225.000000")
		throw 1;
}

Sunkern::Sunkern(const map<string, vector<string> >& f) : Grass(f) {
	for(unsigned int i=0; i<facts["abilities"].size(); ++i) {
		if(facts["abilities"][i]!="17" && facts["abilities"][i]!="144" && facts["abilities"][i]!="34")
			throw 1;
	}
	
}

Sunflora::Sunflora(const map<string, vector<string> >& f) : Sunkern(f) {
	if(facts["height"][0]!="0.800000")
		throw 1;
	if(facts["weight"][0]!="8.500000")
		throw 1;
}

Chimchar::Chimchar(const map<string, vector<string> >& f) : Pokemon(f), Field(f), HumanLike(f) {
	
	for(unsigned int i=0; i<facts["abilities"].size(); ++i) {
		if(facts["abilities"][i]!="14" && facts["abilities"][i]!="0" && facts["abilities"][i]!="72")
			throw 1;
	}
}

Monferno::Monferno(const map<string, vector<string> >& f) : Pokemon(f), Chimchar(f) {
	bool fire=false, fighting=false;
	for(unsigned int i=0; i<facts["types"].size(); ++i) {
		if(facts["types"][i]=="Fire")
			fire=true;
		else if(facts["types"][i]=="Fighting")
			fighting=true;
	}
	if(!fire || !fighting)
		throw 1;
}

Infernape::Infernape(const map<string, vector<string> >& f) : Pokemon(f), Monferno(f) {
	if(facts["height"][0]!="1.200000")
		throw 1;
	if(facts["weight"][0]!="55.000000")
		throw 1;
}

Spheal::Spheal(const map<string, vector<string> >& f) : Pokemon(f), Water1(f), Field(f) {
	
	for(unsigned int i=0; i<facts["abilities"].size(); ++i) {
		if(facts["abilities"][i]!="168" && facts["abilities"][i]!="62" && facts["abilities"][i]!="100")
			throw 1;
	}
}

Sealeo::Sealeo(const map<string, vector<string> >& f) : Pokemon(f), Spheal(f) {
	if(facts["evYield"][0]!="2" && facts["evYield"][0]!="3")
		throw 1;
}

Walrein::Walrein(const map<string, vector<string> >& f) : Pokemon(f), Sealeo(f) {
	if(facts["height"][0]!="1.400000")
		throw 1;
	if(facts["weight"][0]!="150.600000")
		throw 1;
}

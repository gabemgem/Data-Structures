#include <map>
#include <vector>
#include <string>

using namespace std;

class Pokemon {
protected:
	map<string, vector<string> > facts;

public:
	Pokemon(const map<string, vector<string> >& f) : facts(f) {}
	virtual ~Pokemon() {}
	string getLabel() {return facts["label"][0];}
	bool SharesEggGroup(Pokemon* p);
};

class Amorphous : public Pokemon {
public:
	Amorphous(const map<string, vector<string> >& f);
};

class Bug : public Pokemon {
public:
	Bug(const map<string, vector<string> >& f);
};

class Dragon : public Pokemon {
public:
	Dragon(const map<string, vector<string> >& f);
};

class Fairy : public Pokemon {
public:
	Fairy(const map<string, vector<string> >& f);
};

class Field : virtual public Pokemon {
public:
	Field(const map<string, vector<string> >& f);
};

class Flying : public Pokemon {
public:
	Flying(const map<string, vector<string> >& f);
};

class Grass : public Pokemon {
public:
	Grass(const map<string, vector<string> >& f);
};

class HumanLike : virtual public Pokemon {
public:
	HumanLike(const map<string, vector<string> >& f);
};

class Mineral : public Pokemon {
public:
	Mineral(const map<string, vector<string> >& f);
};

class Monster : public Pokemon {
public:
	Monster(const map<string, vector<string> >& f);
};

class Water1 : virtual public Pokemon {
public:
	Water1(const map<string, vector<string> >& f);
};

class Water2 : public Pokemon {
public:
	Water2(const map<string, vector<string> >& f);
};

class Water3 : public Pokemon {
public:
	Water3(const map<string, vector<string> >& f);
};

class Ditto : public Pokemon {
public:
	Ditto(const map<string, vector<string> >& f);
};

class Undiscovered : public Pokemon {
public:
	Undiscovered(const map<string, vector<string> >& f);
};

//--------------------------------------------------------//

class Amaura : public Monster {
public:
	Amaura(const map<string, vector<string> >& f);
};

class Aurorus : public Amaura {
public:
	Aurorus(const map<string, vector<string> >& f);
};

class Sunkern : public Grass {
public:
	Sunkern(const map<string, vector<string> >& f);
};

class Sunflora : public Sunkern {
public:
	Sunflora(const map<string, vector<string> >& f);
};

class Chimchar : public Field, public HumanLike {
public:
	Chimchar(const map<string, vector<string> >& f);
};

class Monferno : public Chimchar {
public:
	Monferno(const map<string, vector<string> >& f);
};

class Infernape : public Monferno {
public:
	Infernape(const map<string, vector<string> >& f);
};

class Spheal : public Water1, public Field {
public:
	Spheal(const map<string, vector<string> >& f);
};

class Sealeo : public Spheal {
public:
	Sealeo(const map<string, vector<string> >& f);
};

class Walrein : public Sealeo {
public:
	Walrein(const map<string, vector<string> >& f);
};
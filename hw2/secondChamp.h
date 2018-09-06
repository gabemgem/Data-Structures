#include <string>

using namespace std;

class secondChamp {
	//the purpose of this class is to store just the base information
	//needed for the champions command. it stores information about
	//a champion, not about a player
	private:
		int wins, losses, mdeaths;
		string name;
		
	public:
		secondChamp(string n);
		
		//accessors
		int getWins() const;
		int getLoss() const;
		int getMDeaths() const;
		string getName() const;
		double getWinPer() const;
		
		//modifiers
		void setWins(int w);
		void setLoss(int l);
		void setMDeaths(int d);
		void setName(string n);
		
};

bool sortChampions(const secondChamp& c1, const secondChamp& c2);
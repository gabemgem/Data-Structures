#include <vector>
#include <string>

using namespace std;

class champ {
	//the purpose of this class is to store all of the information for 
	//each player. it can be used without anything else for the players
	//and custom commands
	
	private:
		int wins, losses, totKills;
		string summ_name;
		vector<string> champ_name;
		vector<string> match;
		vector<int> kills;
		vector<int> deaths;
		vector<int> mdeaths;
		vector<int> assists;
		
	public:
		champ();
		champ(int w, int l, string sname, string matchid, string cname);
		
		//accessors
		double killPart() const;
		int getWins() const;
		int getLoss() const;
		int getAssists() const;
		int getAssists(string matchid) const;
		string getSummName() const;
		vector<string> getChampNameV() const;
		string getChampName() const;
		string getChampName(string matchid) const;
		int getMatches() const;
		int getKills() const;
		int getKills(string matchid) const;
		int getDeaths() const;
		int getDeaths(string matchid) const;
		int getMinionDeaths() const;
		int getMinionDeaths(string matchid) const;
		double getKDR()	const;
		string getFirstMatch() const;
		
		//modifiers
		void setTotKills(int k);
		void setWins(int w);
		void setLoss(int l);
		void setSummName(string sname);
		void setChampName(string matchid, string cname);
		void addKill(string matchid);
		void addDeath(string matchid);
		void addMinionDeath(string matchid);
		void addAssist(string matchid);
	
};

bool sortPlayers(const champ& c1, const champ& c2);

bool sortCustom(const champ& c1, const champ& c2);
#include "champ.h"
#include <vector>
#include <string>

using namespace std;

champ::champ()//default constructor - never used
{
	wins=0;
	losses=0;
	summ_name="";
	
}

champ::champ(int w, int l, string sname, string matchid, string cname)
{	//constructor that sets wins, losses, name, match i.d., and the first champion used
	wins=w;
	losses=l;
	totKills=0;
	summ_name=sname;
	champ_name=vector<string> ();
	match=vector<string> ();
	kills=vector<int> ();
	deaths=vector<int> ();
	mdeaths=vector<int> ();
	assists=vector<int> ();
	setChampName(matchid, cname);
}

int champ::getWins() const//returns wins
{
	return wins;
}

int champ::getLoss() const//returns losses
{
	return losses;
}

int champ::getAssists() const//returns assists
{
	int a=0;
	if(!assists.empty())
		for(unsigned int i=0; i<assists.size(); i++)
			a+=assists[i];
		
	return a;
}

int champ::getAssists(string matchid) const//returns assists from a specific match
{
	int a=0;
	for(unsigned int i=0; i<match.size(); i++)
		if(match[i]==matchid)
			a=assists[i];
		
	return a;
}

int champ::getMatches() const//returns number of matches
{
	return match.size();
}

int champ::getKills() const//returns total kills
{
	int k=0;
	
	if(!kills.empty())
		for(unsigned int i=0; i<kills.size(); i++)
			k+=kills[i];
		
	return k;
}

int champ::getKills(string matchid) const//returns kills in a certain match
{
	int k=0;
	
	
	for(unsigned int i=0; i<match.size(); i++)
		if(match[i]==matchid)
			k=kills[i];
		
	return k;
}

int champ::getDeaths() const//returns total deaths
{
	int d=0;
	
	if(!deaths.empty())
		for(unsigned int i=0; i<deaths.size(); i++)
			d+=deaths[i];
		
	if(!mdeaths.empty())
		for(unsigned int i=0; i<mdeaths.size(); i++)
			d+=mdeaths[i];
		
	return d;
}

int champ::getDeaths(string matchid) const//returns deaths in a certain match
{
	int d=0;
	
	for(unsigned int i=0; i<match.size(); i++)
	{
		if(match[i]==matchid)
		{
			d=deaths[i];
			d+=mdeaths[i];
		}
	}
	return d;
}

int champ::getMinionDeaths() const//returns minion deaths
{
	int m=0;
	
	if(!mdeaths.empty())
		for(unsigned int i=0; i<mdeaths.size(); i++)
			m+=mdeaths[i];
		
	return m;
}

int champ::getMinionDeaths(string matchid) const//returns minion deaths in a certain match
{
	int m=0;
	
	for(unsigned int i=0; i<match.size(); i++)
		if(match[i]==matchid)
			m=mdeaths[i];
		
	return m;
}


double champ::getKDR()	const//use setprecision(3) in main
{
	if(getDeaths()==0)//returns kill-to-death ratio
	{
		return double(getKills());
	}
	
	return (double(getKills())/getDeaths());
}
	
string champ::getSummName() const//returns name
{
	return summ_name;
}

vector<string> champ::getChampNameV() const//returns vector of champions used
{
	return champ_name;
}

string champ::getChampName() const//returns first champion used
{
	return champ_name[0];
}

string champ::getChampName(string matchid) const//returns champion used in a certain match
{
	for(unsigned int i=0; i<match.size(); i++)
	{
		if(match[i]==matchid)
			return champ_name[i];
	}
	
	return champ_name[0];
}

string champ::getFirstMatch() const//returns the first match i.d.
{
	return match[0];
}

double champ::killPart() const//returns kill participation
{
	if(totKills==0)
		return 0.00;
	return (double(getKills()+getAssists())/totKills)*100.0;
}

void champ::setTotKills(int k)//sets the total kills
{
	totKills=k;
}

void champ::setWins(int w)//sets wins
{
	wins=w;
}

void champ::setLoss(int l)//sets losses
{
	losses=l;
}

void champ::setSummName(string sname)//sets name
{
	summ_name=sname;
}

void champ::setChampName(string matchid,string cname)//adds a champion and match to the respective vectors
{
	
	match.push_back(matchid);
	champ_name.push_back(cname);
	kills.push_back(0);
	deaths.push_back(0);
	mdeaths.push_back(0);
	assists.push_back(0);
}

void champ::addKill(string matchid)//adds a kill to a match
{
	
		for(unsigned int i=0; i<match.size(); i++)
		{
			if(match[i]==matchid)
			{
				kills[i]+=1;
				return;
			}
		}
		match.push_back(matchid);
		kills.push_back(1);
		deaths.push_back(0);
		mdeaths.push_back(0);
		assists.push_back(0);
}

void champ::addDeath(string matchid)//adds a death to a match
{
		for(unsigned int i=0; i<match.size(); i++)
		{
			if(match[i]==matchid)
			{
				deaths[i]+=1;
				return;
			}
		}
		match.push_back(matchid);
		kills.push_back(0);
		deaths.push_back(1);
		mdeaths.push_back(0);
		assists.push_back(0);
}

void champ::addMinionDeath(string matchid)//adds a minion death to a match
{
		for(unsigned int i=0; i<match.size(); i++)
		{
			if(match[i]==matchid)
			{
				mdeaths[i]+=1;
				return;
			}
		}
		match.push_back(matchid);
		kills.push_back(0);
		deaths.push_back(0);
		mdeaths.push_back(1);
		assists.push_back(0);
}

void champ::addAssist(string matchid)//adds an assist to a match
{
		for(unsigned int i=0; i<match.size(); i++)
		{
			if(match[i]==matchid)
			{
				assists[i]+=1;
				return;
			}
		}
		match.push_back(matchid);
		kills.push_back(0);
		deaths.push_back(0);
		mdeaths.push_back(0);
		assists.push_back(1);
}




bool sortPlayers(const champ& c1, const champ& c2)//sorts for the players command
{
	if(c1.getKDR()>c2.getKDR())//sorts by kdr
		return true;
	else if(c1.getKDR()==c2.getKDR())
	{
		if(c1.getKills()>c2.getKills())//sorts by kills
			return true;
		else if(c1.getKills()==c2.getKills())
		{
			if(c1.getDeaths()<c2.getDeaths())//sorts by deaths
				return true;
			else if(c1.getDeaths()==c2.getDeaths())
			{
				if(c1.getSummName()<c2.getSummName())//sorts by name
					return true;
			}
		}
	}
	
	return false;
}
	

bool sortCustom(const champ& c1, const champ& c2)//sorts for the custom command
{
	if(c1.getFirstMatch()<c2.getFirstMatch())//sorts by match
		return true;
	else if(c1.getFirstMatch()==c2.getFirstMatch())
	{
		if(c1.killPart()>c2.killPart())//sorts by kill participation
			return true;
		else if(c1.killPart()==c2.killPart())
			if(c1.getSummName()<c2.getSummName())//sorts by name
				return true;
	}	
	
	return false;
}	
			
			
			
			
			
			
			
			
			
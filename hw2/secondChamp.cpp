#include "secondChamp.h"
#include <string>

using namespace std;

secondChamp::secondChamp(string n)//constructor to just initialize everything and set the name
{
	wins=0;
	losses=0;
	mdeaths=0;
	name=n;
}

int secondChamp::getWins() const	{return wins;}//returns wins
int secondChamp::getLoss() const	{return losses;}//returns losses
int secondChamp::getMDeaths() const 	{return mdeaths;}//returns minion deaths
string secondChamp::getName() const		{return name;}//returns the champion name

double secondChamp::getWinPer() const//returns the win percent of the champion
{
	return double(wins)/(wins+losses);
}

void secondChamp::setWins(int w)	{wins=w;}//sets wins
void secondChamp::setLoss(int l)	{losses=l;}//sets losses
void secondChamp::setMDeaths(int d) {mdeaths=d;}//sets minion deaths
void secondChamp::setName(string n) {name=n;}//sets name - won't be called but included because it's good
											 //to have a way to champ all private variables

bool sortChampions(const secondChamp& c1, const secondChamp& c2)//sorts champions for champions command
{
	if(c1.getWinPer()>c2.getWinPer())//sorts by win percent
		return true;
	else if(c1.getWinPer()==c2.getWinPer())
	{
		if(c1.getWins()>c2.getWins())//sorts by wins
			return true;
		else if(c1.getWins()==c2.getWins())
		{
			if(c1.getLoss()<c2.getLoss())//sorts by losses
				return true;
			else if(c1.getLoss()==c2.getLoss())
			{
				if(c1.getName()<c2.getName())//sorts by name
					return true;
			}
		}
	}
	
	return false;
}





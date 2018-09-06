#include "champ.h"
#include "secondChamp.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

void condense(vector<champ>& players)//condenses duplicates in the player vector
{
	vector<champ> temp;//makes temp vector
	vector<unsigned int> skipIndex;//makes vector of indexes to skip
	bool skip=false;
	
	for(unsigned int f=0; f<players.size()-1; f++)//loops through all but the last player
	{
		for(unsigned int d=0; d<skipIndex.size(); d++)//skips the check if appropriate
		{
			if(f==skipIndex[d])
			{
				skip=true;
			}
		}
			
		if(skip==false)//checks all other players starting at the index after the first player
		{
			champ c=players[f];//makes a new temporary champ
			
			
			
			for(unsigned int s=f+1; s<players.size(); s++)
			{
				if(players[f].getSummName()==players[s].getSummName())//checks to see if player is the same as first player
				{
					c.setChampName(players[s].getFirstMatch(), 
						players[s].getChampName(players[s].getFirstMatch()));
						//adds champion name with the matchid to the temp champ
						
					c.setWins(c.getWins()+players[s].getWins());//combines wins of first and second champ in temp champ
					
					c.setLoss(c.getLoss()+players[s].getLoss());//same as above but with losses
					
					for(int i=0; i<players[s].getKills(); i++)//the following for loops do the same as above
						c.addKill(players[s].getFirstMatch());//but with kills, deaths, etc.
					
					for(int j=0; j<players[s].getDeaths(); j++)
						c.addDeath(players[s].getFirstMatch());
					
					for(int k=0; k<players[s].getMinionDeaths(); k++)
						c.addMinionDeath(players[s].getFirstMatch());
					
					for(int l=0; l<players[s].getAssists(); l++)
						c.addAssist(players[s].getFirstMatch());
					
					skipIndex.push_back(s);//adds the index of the player combined with the first one to the skip vector
				}
			}
		
			
			temp.push_back(c);//adds the temp champ to the temp vector
		}
		
		skip=false;
	}
	
	for(unsigned int x=0; x<skipIndex.size(); x++)//sets players to the temp champ vector
												 //if the last player was combined with an earlier player
	{
		if(skipIndex[x]==players.size()-1)
		{
			players=temp;
			return;
		}
	}
	
	temp.push_back(players[players.size()-1]);//adds the last player to temp if it was not combined
							//this is because the outer loop only goes to the second to last player
	players=temp;//sets players to the temp champ vector
}

bool playerComm(string ofName, vector<champ>& players)//makes the table for the players command
{
	std::ofstream output(ofName.c_str());//starts output to the output file
	if (!output.good()) 
	{
		std::cerr << "Can't open " << ofName << " to write.\n";
		exit(1);
	}
	
	condense(players);//condenses the player vector
	
	sort(players.begin(), players.end(), sortPlayers);//sorts the player vector according to the
													 //function in champ.cpp
	
	output<<"PLAYER NAME            KILLS  DEATHS     KDR   PLAYED WITH CHAMPION(S)\n";
	
	for(unsigned int i=0; i<players.size(); i++)//outputs the correct info for each player
	{
		output.width(23);
		output<<left<<players[i].getSummName();
		output.width(5);
		output<<right<<players[i].getKills();
		output.width(8);
		output<<right<<players[i].getDeaths();
		output.width(8);
		output<<right<<setprecision(2)<<fixed<<players[i].getKDR();
		output.width(3);
		output<<"   ";
		
		vector<string> cnames = players[i].getChampNameV();//gets a vector of all the champions each 
														  //player has played with
		vector<string> tempNames;
		
		sort(cnames.begin(), cnames.end());
		
		tempNames.push_back(cnames[0]);
		
		if(cnames.size()!=1)
		{
			for(unsigned int f=0; f<cnames.size(); f++)
			{
				unsigned int s=f+1;
				unsigned int skip=f;
				while(s!=cnames.size() && cnames[s]==cnames[f])
				{
					s++;
					skip++;
				}
				if(f!=0)
					tempNames.push_back(cnames[f]);
				if(skip!=f)
					f=skip;
				
				
			}
		}
		
		cnames=tempNames;
		
		
		for(unsigned int j=0; j<cnames.size(); j++)//prints out the champions
		{
			if(j==0)
			{
				output<<cnames[j];
			}
			else
			{
				output<<", "<<cnames[j];
			}
		}
		
		output<<endl;
			
		
		
	}
	
	
	return true;
}


bool championComm(string ofName, vector<champ>& players)//makes the table for the champions command
{
	std::ofstream output(ofName.c_str());//starts output to the output file
	if (!output.good()) 
	{
		std::cerr << "Can't open " << ofName << " to write.\n";
		exit(1);
	}
	
	output<<"CHAMPION NAME           WINS  LOSSES    WIN%   MINION DEATHS\n";
	
	vector<secondChamp> champions;//vector of champions
	
	
	
	for(unsigned int i=0; i<players.size(); i++)//put each player's data for a champion into the vector
	{
		
		if(champions.empty())//put the first player's champ in the vector
		{
			secondChamp c = secondChamp(players[i].getChampName());
			c.setWins(players[i].getWins());
			c.setLoss(players[i].getLoss());
			c.setMDeaths(players[i].getMinionDeaths());
			champions.push_back(c);
		}
		
		else
		{
		
			for(unsigned int j=0; j<champions.size(); j++)//check to see if champion is already in vector
			{
				if(champions[j].getName()==players[i].getChampName())//add appropriate data if champion is in vector	
				{
					champions[j].setWins(champions[j].getWins()+players[i].getWins());
					champions[j].setLoss(champions[j].getLoss()+players[i].getLoss());
					champions[j].setMDeaths(champions[j].getMDeaths()+players[i].getMinionDeaths());
					break;
				}
				
				else if(j==champions.size()-1 && champions[j].getName()!=players[i].getChampName())
										//create new champion and add to vector it isn't in vector
				{
					secondChamp c = secondChamp(players[i].getChampName());
					c.setWins(players[i].getWins());
					c.setLoss(players[i].getLoss());
					c.setMDeaths(players[i].getMinionDeaths());
					champions.push_back(c);
					break;
				}
				
			}
		}
		
	}
	
	sort(champions.begin(), champions.end(), sortChampions);//sort using function in secondChamp.cpp
	
	for(unsigned int k=0; k<champions.size(); k++)//output appropriate data in table
	{
		output.width(24);
		output<<left<<champions[k].getName();
		output.width(4);
		output<<right<<champions[k].getWins();
		output.width(8);
		output<<right<<champions[k].getLoss();
		output.width(8);
		output<<right<<setprecision(2)<<fixed<<champions[k].getWinPer();
		output.width(16);
		output<<right<<champions[k].getMDeaths()<<endl;
		
	}
	
	
	return true;
}


bool customComm(string ofName, vector<champ>& players)//makes the table for the custom command
{//the main parts of this are kill participation in a specific match for each player and a grade
	std::ofstream output(ofName.c_str());//starts output to the output file
	if (!output.good()) 
	{
		std::cerr << "Can't open " << ofName << " to write.\n";
		exit(1);
	}
	
	for(unsigned int i=0; i<players.size()/10; i++)//assign the total kills for each team in each match
	{											  //to the appropriate player
		int totKills=0;
		
		for(unsigned int j=i*10; j<(i*10)+5; j++)//team 1 in a match
		{
			totKills+=players[j].getKills();//add up the total kills
		}
		
		for(unsigned int k=i*10; k<(i*10)+5; k++)
		{
			players[k].setTotKills(totKills);//set the total kills
		}
		
		totKills=0;
		
		for(unsigned int l=(i*10)+5; l<(i*10)+10; l++)//team 2 in a match
		{
			totKills+=players[l].getKills();//same as above
		}
		
		for(unsigned int m=(i*10)+5; m<(i*10)+10; m++)
		{
			players[m].setTotKills(totKills);//same as above
		}
		
	}
	
	sort(players.begin(), players.end(), sortCustom);//sort according to sortCustom in champ.cpp
	
	output<<"MATCH ID            PLAYER NAME              KILL PART.     GRADE\n";
	
	for(unsigned int x=0; x<players.size(); x++)//print out the data for each player
	{
		output.width(20);
		output<<left<<players[x].getFirstMatch();
		output.width(25);
		output<<left<<players[x].getSummName();
		output.width(8);
		output<<right<<setprecision(1)<<fixed<<players[x].killPart();
		output<<" %";
		
		string grade;
		
		if(players[x].killPart()>=80)//assign and print grades according to each player's kill participation
			grade="S";
		else if(players[x].killPart()>=50)
			grade="A";
		else if(players[x].killPart()>=25)
			grade="B";
		else if(players[x].killPart()>=15)
			grade="C";
		else
			grade="D";
		
		output.width(10);
		output<<right<<grade<<endl;
		
		if(x!=players.size()-1 && players[x].getFirstMatch()!=players[x+1].getFirstMatch())
			output<<endl;//makes a new line if switching to a new match
		
		
	}	
	
	
	
	return true;
}



int main(int argc, char* args[])
{
	vector<champ> players;//vector of players to be filled from input file and then can be used to create output file
	
	string inFile, outFile, comm;
	
	inFile = args[1];
	outFile = args[2];
	comm = args[3];
	
	ifstream input(inFile.c_str());
	
	if (!input.good()) {
    std::cerr << "Can't open " << args[1] << " to read.\n";
    exit(1);
	}
	
	string x;//temp variable to hold the elements of the input file
	string matchid;
	
	while(input>>x)//loop through the whole input file
	{
		input>>x;//any repeated calls of input>>x are used to cycle through unwanted elements of the input file
		input>>x;
		matchid=x;//store match i.d.
		input>>x;
	
	
	
		if(x=="WINNING")//fill players vector if the first team listed is the winning team
		{
			input>>x;
			for(int i=0; i<5; i++)
			{
				string sname, cname;
				input>>sname;
				input>>cname;
				input>>cname;
				input>>cname;
				champ c = champ(1,0,sname,matchid,cname);//creates new champ variable with 1 win and the summoner and champion name
				players.push_back(c);//adds champ to vector
			}
			input>>x;
			input>>x;
			for(int i=0; i<5; i++)
			{
				string sname, cname;
				input>>sname;
				input>>cname;
				input>>cname;
				input>>cname;
				champ c = champ(0,1,sname,matchid,cname);//creates new champ variable with 1 loss and the summoner and champion name
				players.push_back(c);//adds champ to vector
			}
		}
		
		else//fill player vector if the first team listed is the losing team
		{//exactly the same as above except creates players with a loss before players with a win
			input>>x;
			for(int i=0; i<5; i++)
			{
				string sname, cname;
				input>>sname;
				input>>cname;
				input>>cname;
				input>>cname;
				champ c = champ(0,1,sname,matchid,cname);
				players.push_back(c);
			}
			input>>x;
			input>>x;
			for(int i=0; i<5; i++)
			{
				string sname, cname;
				input>>sname;
				input>>cname;
				input>>cname;
				input>>cname;
				champ c = champ(1,0,sname,matchid,cname);
				players.push_back(c);
			}
		}
		
		
		input>>x;
		input>>x;
		
		while(x!="END")//loop through events
		{
			
			input>>x;
			input>>x;
			if(x=="minion")//adds a minion death to champ if appropriate
			{
				input>>x;
				
					input>>x;
					for(unsigned int j=0; j<players.size(); j++)
					{
						if(players[j].getSummName()==x)
						{
							players[j].addMinionDeath(matchid);//adds the minion death
							//cout<<players[j].getSummName()<<" got killed by a minion.\n\n";
							break;
						}
					}
			}
			else//otherwise gives out the kill, death, and assists
			{
				
				
				
				for(unsigned int i=0; i<players.size(); i++)//finds player to give kill to
				{
					if(players[i].getSummName()==x)
					{
						players[i].addKill(matchid);//gives kill
						break;
					}
				}
				input>>x;
				if(x=="[")
				{
					input>>x;
					while(x!="]")//gives assists like above
					{
						
						
						for(unsigned int p=0; p<players.size(); p++)
						{
							if(players[p].getSummName()==x)
							{
								players[p].addAssist(matchid);
								break;
							}
						}
						
						input>>x;
					}
					
					input>>x;
				}
				
					
					input>>x;
					for(unsigned int j=0; j<players.size(); j++)
					{
						if(players[j].getSummName()==x)
						{
							players[j].addDeath(matchid);
							break;
						}
					}
				
				
			}
			
			input>>x;
			
		}
	}
	
	
	//makes the appropriate table according to the argument in the command line
	if(comm=="players")
	{
		playerComm(outFile, players);
	}
	
	else if(comm=="champions")
	{
		championComm(outFile, players);
	}
	
	else if(comm=="custom")
	{
		customComm(outFile, players);
	}
	
	return 0;
}
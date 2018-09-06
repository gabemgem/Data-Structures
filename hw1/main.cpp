// main.cpp - a very simple seating chart gnerator for a fictitious airline
//

#include <string>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;
// a constant for generating seat aisle labels
const string ALPHABET("ABCDEFGHIJKLMNOPQRSTUVWXYZ");

// return the row and column from a seat request
//
// Note: This code assumes that the seat chart is stored in a 2D vector or
//       array. If you are using a differnt structure for storing seat
//       information, it won't help.
//
// arguments:
// seat_request - a string of row and colummn, eg. 1A
// total_rows - the number of rows in the seating chart
// total_rows - the number of columns in the seating chart, including aisles
// seat_row, seat_col - the seat row and column. If the seat_request is
//                      formatted properly, on return these variables will
//                      contain the row and column of the seat (0-indexed)
//                      
//
// returns;
// true if the seat request contains a valid seat. false otherwise
//
// a seat is valid if its row number is >= 1 and <= the number of rows and
// its column falls in the alphabet in the range of columns.
bool GetSeatRowCol(const string& seat_request,
		   unsigned int total_rows,
		   unsigned int total_columns,
		   int& seat_row,  size_t& seat_col) {
  
   string row_str;
  string col_str;
  for (unsigned int i = 0; i < seat_request.size(); i++) {
    if (seat_request[i] >= '0' && seat_request[i] <= '9')
      row_str += seat_request[i];
    else
      col_str += seat_request[i];	
  }
    
  seat_row = atoi(row_str.c_str()) - 1;
  if (seat_row < 0 || seat_row > (int) total_rows - 1) {
    return false;
  }

  seat_col = ALPHABET.find(col_str);
  if (seat_col == string::npos || seat_col > total_columns - 1) {
    return false;
  }

  return true;
}








bool srn(string pid, string cl, string ff, vector<vector<string> >& plane, vector<string>& ulist,
		 vector<string>& ulist_class)
//try to seat passenger in requested class
//pid - passenger id, cl - requested class, plane - layout of the plane, ff - frequent flyer?, 
//ulist - upgrade list of passenger id's, ulist_class - upgrade list of classes to upgrade to							
{
	
	if(cl!="F" && cl!="B" && cl!="C")	{ //checks for valid class request
		cout << "Invalid seating class - " << cl << "." << endl;
		return false;
	}
	
	int start_class=0;
	int end_class=0;
	bool inClass=false;
	
	for(unsigned int i=0; i<plane.size(); i++)//find the starting row of the requested class
	{
		if(!inClass && plane[i][0]==cl)
		{
			start_class=i;
			//cout<<"\nStarting class: "<<start_class<<endl;
			inClass=true;
		}
		else if((inClass && plane[i][0]!=cl) || i==plane.size()-1)
		{
			if(i==plane.size()-1)
				end_class=i+1;
			else
				end_class=i;
			//cout<<"Ending class: "<<end_class<<endl<<endl;
			break;
		}
	}
	
	for(int r=start_class; r<end_class; r++)//try to give passenger a window or isle seat
	{
		for(unsigned int c=1; c<plane[0].size(); c++)
		{
			
			if(plane[r][c]==".")
			{
				if(c==1 || c==plane[0].size()-1)
				{
					plane[r][c]=pid;
					
					stringstream s;
					s << r+1;
					string row = s.str();
					string sid=row+ALPHABET[c-1];
					
					cout << "Passenger " << pid << " was given seat " << sid << "." << endl;
					return true;
				}
				else if(plane[r][c+1]=="!" || plane[r][c-1]=="!")
				{
					plane[r][c]=pid;
					
					stringstream s;
					s << r+1;
					string row = s.str();
					string sid=row+ALPHABET[c-1];
					
					cout << "Passenger " << pid << " was given seat " << sid << "." << endl;
					return true;
				}
			}
			
			
		}
	}
	
	for(int r=start_class; r<end_class; r++)//try to give passenger a seat
	{
		for(unsigned int c=1; c<plane[0].size(); c++)
		{
			stringstream s;
			s << r;
			string row = s.str();
			string sid=row+ALPHABET[c];
			if(plane[r][c]==".")
			{
				plane[r][c]=pid;
				cout << "Passenger " << pid << " was given seat " << sid << "." << endl;
				return true;
			}
			
		}
	}
	
	if(ff=="Y")//put on upgrade list if seat isn't found
	{
		
		if(cl=="C")	{
			ulist_class.push_back("B");
			ulist.push_back(pid);
			return true;
		}
		else if(cl=="B")	{
			ulist_class.push_back("F");
			ulist.push_back(pid);
			return true;
		}
		
	}
	
	cout << "Could not find a seat in the " << cl << " section for passenger " << pid << "." << endl;
	
	
	
	return false;
}

bool ssr(string pid, string sid, string ff, vector<vector<string> >& plane, vector<string>& ulist,
		 vector<string>& ulist_class)
//try to seat passenger in requested seat
//pid - passenger id, sid - seat id, plane - layout of the plane, ff - frequent flyer?,
//ulist - upgrade list of passenger id's, ulist_class - upgrade list of classes to upgrade to	
{
	int srow;
	size_t scol;
	
	if(!GetSeatRowCol(sid, plane.size(), plane[0].size()-1, srow, scol))//get the seat row and column and make sure it's a valid seat
	{
		cout << "Passenger " << pid << " requested an invalid seat " << sid << "." << endl;
		return false;
	}
	
	scol+=1;
	
	if(plane[srow][scol]==".")//put passenger in seat if available
	{
		plane[srow][scol]=pid;
		cout<< "Passenger " << pid << " was given seat " << sid << "." << endl;
		return true;
	}
	else//try to put passenger in same class or upgrade if seat taken
	{
		cout<< "Passenger " << pid << " requested an occupied seat " << sid << "." << endl;
		
		//cout<<endl<<plane[srow][0]<<endl;
		
		srn(pid, plane[srow][0], ff, plane, ulist, ulist_class);
	}
	return true;
}

bool cxl(string pid, vector<vector<string> >& plane, vector<string>& ulist,
		 vector<string>& ulist_class)
//free up passenger's seat/remove passenger from upgrade list
//pid - passenger id, plane - plane layout, ulist- upgrade list of passenger id's,
//upgrade list of classes to upgrade to
{
	
	for(unsigned int r=0; r<plane.size(); r++)//find passenger in plane if listed
	{
		for(unsigned int c=0; c<plane[0].size(); c++)
		{
			if(plane[r][c]==pid)
			{
				plane[r][c]=".";//remove passenger if found
				return true;
			}
		}
	}
	
	for(unsigned int i=0; i<ulist.size(); i++)//check for passenger in the upgrade list
	{
		if(ulist[i]==pid)
		{
			vector<string> temp1, temp2;
			for(unsigned int j=0; j<ulist.size(); j++)//add all passengers except for passenger to be
													//removed to a temp. vector
			{
				if(j!=i)
				{
					temp1.push_back(ulist[j]);
					temp2.push_back(ulist_class[j]);
				}
			}
			ulist=temp1;//replace upgrade lists with temp lists that don't contain specified passenger
			ulist_class=temp2;
			return true;
		}
	}
	
	cout << "Passenger " << pid << " could not be found." << endl;
	return false;
}

bool upl(const vector<string>& ulist, const vector<string>& ulist_class)
//print out the upgrade list
//ulist - upgrade list of passenger id's, ulist_class - upgrade list of classes to upgrade to
{
	cout << "The following passengers are scheduled to be upgraded to first class:" << endl;
	
	for(unsigned int f=0; f<ulist.size(); f++)//find and print passengers to be upgraded
											  //to first class
	{
		if(ulist_class[f]=="F")
		{
			cout << ulist[f] << endl;
		}
	}
	
	cout << "The following passengers are scheduled to be upgraded to business class:" << endl;
	
	for(unsigned int b=0; b<ulist.size(); b++)//find and print passengers to be upgraded
											  //to business class
	{
		if(ulist_class[b]=="B")
		{
			cout << ulist[b] << endl;
		}
	}
	return true;
}


bool upp(vector<string>& ulist, vector<string>& ulist_class, vector<vector<string> >& plane)
//try to upgrade all passengers in the upgrade list
//ulist - upgrade list of passenger id's, ulist_class - upgrade list of the classes to upgrade to,
//plane - plane layout
{
	for(unsigned int i=0; i<ulist.size(); i++)//loop through every passenger on the upgrade list
	{
		if(ulist_class[i]=="F")//upgrade first class upgrades first
		{
			if(srn(ulist[i], ulist_class[i], "N", plane, ulist, ulist_class))//try to seat the passenger
			{
				cout << "Passenger " << ulist[i] << " was upgraded to the first class section."<<endl; 
			}
			else//print out error message if could not seat passenger
			{
				cout << "Could not find a seat in the " << ulist_class[i] << " section for passenger "
					 << ulist[i] << "." << endl;
			}
		}
	}
	
	for(unsigned int i=0; i<ulist.size(); i++)//loop through every passenger on the upgrade list
	{
		if(ulist_class[i]=="B")//upgrade business class upgrades second
		{
			if(srn(ulist[i], ulist_class[i], "N", plane, ulist, ulist_class))//try to seat the passenger
			{
				cout << "Passenger " << ulist[i] << " was upgraded to the business class section."<<endl;
			}
			else//print out error message if could not seat passenger
			{
				cout << "Could not find a seat in the " << ulist_class[i] << " section for passenger "
					 << ulist[i] << "." << endl;
			}
		}
	}
	
	ulist.clear();
	ulist_class.clear();
	return true;
}


bool prt(string flnum, const vector<vector<string> >& plane)
//print out seating chart
//flnum - flight number, plane - plane layout
{
	cout << "Seating Chart for Flight " << flnum << endl;
	
	unsigned int total_rows = plane.size();//store length of plane
	unsigned int total_cols = plane[0].size();//store width of plane

	cout << "\t";//indent first line of layout

	for (unsigned int i = 0; i < total_cols-1; i++) {//print out first line
		cout << ALPHABET[i] << "    ";
	}
	cout << "Seating Class" << endl;//finish first line

	for (unsigned int r = 0; r < total_rows; r++) {//format and print each row

		cout << r + 1 << "\t";
		string cl = plane[r][0];//store row class

		for (unsigned int c = 1; c < total_cols; c++) {//format and print each column in a row
			if (plane[r][c] == ".")
				cout << ".... ";
			else if (plane[r][c] == "!")
				cout << "!!!! ";
			else
				cout << plane[r][c] << " ";
		}
		cout << cl << endl;
	}
	return true;
}



int main(int argc, char* argv[]) {

	string seat_file, pass_file;
	seat_file=argv[1];
	pass_file=argv[2];

	vector<vector<string> > plane;
	vector<string> row;
	string x;

	ifstream plfile(seat_file.c_str());//open file for plane layout

	plfile >> x;
	row.push_back(x);//add the first element of the layout file to the first row
	//cout<<x;

	while (plfile >> x) {//loop through the rest of the layout file adding elements to plane
		if (x == "." || x == "!") 
		{
			row.push_back(x);
			//cout<<x;
		}
		else//makes a new row when neccessary
		{
			plane.push_back(row);
			row.clear();
			row.push_back(x);
			//cout<<endl<<x;
		}
			

	}
	plane.push_back(row);
	

	


	vector<string> ulist, ulist_class;//creates upgrade list variables

	ifstream cmfile(pass_file.c_str());//opens command file

	string flnum;
	cmfile >> flnum;//sets the first element of command file as the flight number

	string comm;

	while (cmfile >> comm)//reads and executes each command in the command folder
	{
		if (comm == "SRN") {
			string pid, cl, ff;
			cmfile >> pid >> cl >> ff;
			//cout<<"\nSRN: "<<pid<<"  "<<cl<<"  "<<ff<<endl;
			srn(pid, cl, ff, plane, ulist, ulist_class);
		}

		else if (comm == "SSR") {
			string pid, sid, ff;
			cmfile >> pid >> sid >> ff;
			ssr(pid, sid, ff, plane, ulist, ulist_class);
		}

		else if (comm == "CXL") {
			string pid;
			cmfile >> pid;
			cxl(pid, plane, ulist, ulist_class);
		}

		else if (comm == "UPL")
			upl(ulist, ulist_class);

		else if (comm == "UPP")
			upp(ulist, ulist_class, plane);

		else if (comm == "PRT")
			prt(flnum, plane);
		
		else
			cout << "Invalid command: " << comm << "." << endl;
	}


  return 0;
}
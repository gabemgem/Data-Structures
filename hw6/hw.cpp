#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

class loc {//class to hold a location
public:
	loc(unsigned int r=0, unsigned int c=0) : row(r), col(c) {}
	unsigned int row, col;
};
bool operator== (const loc& lhs, const loc& rhs) { //be able to compare loc's
	return lhs.row == rhs.row && lhs.col == rhs.col;
}

void printBoards(const vector< vector< vector<char> > >& boards, ostream& ostr) {//output
	ostr<<boards.size()<<" solution(s)\n";
	for(unsigned int b=0; b<boards.size(); b++) {//print all the boards
		ostr<<"Board: \n";
		for(unsigned int i=0; i<boards[0].size(); i++) {
			ostr<<"  ";
			for(unsigned int j=0; j<boards[0][0].size(); j++)
				ostr<<boards[b][i][j];
			ostr<<endl;
		}
	}
	
}



bool placeFromLoc(loc pos, vector< vector<char> >& board, string& word,
				  unsigned int spos, unsigned int dir) {
	//places a word from a location, return true if possible

	//pos is a position to check and place
	//board is the board to use
	//word is the word to place
	//spos is the position in the word
	//dir is the direction to place in

	if(pos.row>=board.size() || pos.col>=board[0].size())//if it's out of bounds
		return false;
	
	if(board[pos.row][pos.col]!='0' && board[pos.row][pos.col]!=word[spos])
		return false;//if the char isn't the fill char and isn't the next letter of the word

	if(spos==word.size()-1) {//if it's gone through the whole word
		board[pos.row][pos.col]=word[spos];
		return true;
	}



	if(dir==1) {//right
		if(pos.col==board[0].size()-1)
			return false;//if word wouldn't fit

		loc nloc = loc(pos.row, pos.col+1);

		if(placeFromLoc(nloc, board, word, spos+1, 1)) {//try all the way through first
			board[pos.row][pos.col]=word[spos];//and then place the letter if the word 
			return true;					   //would fit
		}		
		return false;
	}
	if(dir==2) {//up
		if(pos.row==0)//same as above but in the upwards direction
			return false;

		loc nloc = loc(pos.row-1, pos.col);

		if(placeFromLoc(nloc, board, word, spos+1, 2)) {
			board[pos.row][pos.col]=word[spos];
			return true;
		}
		return false;
		
	}
	if(dir==3) {//down right
		if(pos.row==board.size()-1 || pos.col==board[0].size()-1)//see above
			return false;
		
			loc nloc = loc(pos.row+1, pos.col+1);

			if(placeFromLoc(nloc, board, word, spos+1, 3)) {
				board[pos.row][pos.col]=word[spos];
				return true;
			}
		
		return false;
		
	}
	if(dir==4) {//left
		if(pos.col==0)//see above
			return false;

		loc nloc = loc(pos.row, pos.col-1);

		if(placeFromLoc(nloc, board, word, spos+1, 4)) {
			board[pos.row][pos.col]=word[spos];
			return true;
		}		
		return false;
	}
	if(dir==5) {//down
		if(pos.row==board.size()-1)//see above
			return false;

		loc nloc = loc(pos.row+1, pos.col);

		if(placeFromLoc(nloc, board, word, spos+1, 5)) {
			board[pos.row][pos.col]=word[spos];
			return true;
		}		
		return false;
	}
	if(dir==6) {//down left
		if(pos.row==board.size()-1 || pos.col==0)//see above
			return false;

		
			loc nloc = loc(pos.row+1, pos.col-1);

			if(placeFromLoc(nloc, board, word, spos+1, 6)) {
				board[pos.row][pos.col]=word[spos];
				return true;
			}
		
		return false;
	}
	if(dir==7) {//up right
		if(pos.row==0 || pos.col==board[0].size()-1)//see above
			return false;

		
			loc nloc = loc(pos.row-1, pos.col+1);

			if(placeFromLoc(nloc, board, word, spos+1, 7)) {
				board[pos.row][pos.col]=word[spos];
				return true;
			}
		
		return false;
	}
	if(dir==8) {//up left
		if(pos.row==0 || pos.col==0)//see above
			return false;

		
			loc nloc = loc(pos.row-1, pos.col-1);

			if(placeFromLoc(nloc, board, word, spos+1, 8)) {
				board[pos.row][pos.col]=word[spos];
				return true;
			}
		
		return false;
	}

	else {//if just generically placing a word

		bool result = false;
		for(int i=1; i<=8 && !result; i++)//try placing in all directions
			result = placeFromLoc(pos, board, word, spos, i);
		return result;//and return true if any of them work
	}

}

bool contains0(vector< vector<char> > grid) {//checks if a grid contains the fill char
	for(unsigned int r=0; r<grid.size(); r++)
		for(unsigned int c=0; c<grid[0].size(); c++)
			if(grid[r][c]=='0')
				return true;
	return false;
}

void makeGrids(vector< vector<char> >& bGrid, vector<string>& gwords,
			   vector< vector< vector<char> > >& posGrids) {
	//bGrid is the base grid of the correct size with just fill char's
	//gwords is a vector of all the words to put in
	//posGrids is the collection of all possible grids

	posGrids.push_back(bGrid);//put the base grid in


	vector< vector< vector<char> > > tempGrids;//make a temporary vector of grids

	for(unsigned int j=0; j<gwords.size(); j++) {//for each word to put in
		
		for(unsigned int g=0; g<posGrids.size(); g++) {//for each possible grid

			for(unsigned int r=0; r<posGrids[0].size(); r++) {

				for(unsigned int c=0; c<posGrids[0][0].size(); c++) {

					loc pos = loc(r,c);//for each position in each grid

					for(int k=1; k<=8; k++) {//for each possible orientation

						vector< vector<char> > temp = posGrids[g];//temp grid to check
						if(placeFromLoc(pos,temp,gwords[j],0,k))//if can add the word
							tempGrids.push_back(temp);//put that grid into tempGrids
					}
				}
			}
		}
		posGrids=tempGrids;//replace posGrids with tempGrids
		tempGrids.clear();//and clear out the temp grid
	}
	tempGrids.clear();
	const string alphabet = "abcdefghijklmnopqrstuvwxyz";

	vector<unsigned int> eraseI;//indicies of grids to erase

	for(unsigned int iter=0; iter<posGrids.size(); iter++) {
		//for each grid
		
		vector< vector<char> > t=posGrids[iter];//copy the grid

			for(unsigned int r=0; r<t.size(); r++) {//for each space in the grid
				for(unsigned int c=0; c<t[0].size(); c++) {
					if(t[r][c]=='0') {//if the char in that space is the fill char
						

						eraseI.push_back(iter);//say to erase the original grid

						for(unsigned int letter=0; letter<alphabet.size(); letter++) {
							t[r][c]=alphabet[letter];//put all possible combinations of
							tempGrids.push_back(t);  // letters into the grid, add grid
													 // to tempGrids
						}
						
						
					}
				}
			
			}	
		
	}

	for(unsigned int i=0; i<eraseI.size(); i++) {//erase all of the grids that wer filled
		if(eraseI[i]<posGrids.size()) {
		vector< vector< vector<char> > >::iterator er = posGrids.begin()+eraseI[i];
		posGrids.erase(er); }
	}

	for(unsigned int k=0; k<tempGrids.size(); k++)
		posGrids.push_back(tempGrids[k]);

	

	if(!posGrids.empty()) {//erase any other grid with a fill char in it
		for(vector< vector< vector<char> > >::iterator i=posGrids.begin(); 
												    i!=posGrids.end(); i++) {
			if(contains0(*i)) {
				i=posGrids.erase(i);
				i--;
			}
		}
		
	}



}

bool findWord(loc pos, const vector< vector<char> >& board, const string& word, 
										   unsigned int spos, unsigned int dir) {
	//returns true if a word is found in the grid

	//pos is the position to check a letter
	//board is the board to check
	//word is the word being checked
	//spos is the position in the word
	//dir is the direction to check in
	
	
	//BASE CASES
	if( pos.row >=board.size() || pos.col >=board[0].size()){//if you go out of bounds
		return false;//since they're unsigned ints, you don't need to check <0
	}

	if(board[pos.row][pos.col]!=word[spos])//if the letter != next letter in word
		return false;

	if(spos==word.size()-1)//if you've reached the end of the word
		return board[pos.row][pos.col]==word[spos];
	
	

	

	if(dir==1) {//up left
		if(pos.row==0 || pos.col==0) {//if would go out of bounds in the next iteration
			return false;
		}
		loc npos(pos.row-1, pos.col-1);//make next position
		
		return findWord(npos, board, word, spos+1, 1);//recurse with new position
	}
	if(dir==2) {//up
		if(pos.row==0) {//see above
			return false;
		}
		loc npos(pos.row-1, pos.col);
		
		return findWord(npos, board, word, spos+1, 2);
	}
	if(dir==3) {//up right
		if(pos.row==0 || pos.col==board[0].size()-1) {//see above
			return false;
		}
		loc npos(pos.row-1, pos.col+1);
		
		return findWord(npos, board, word, spos+1, 3);
	}
	if(dir==4) {//left
		if(pos.col==0) {//see above
			return false;
		}
		loc npos(pos.row, pos.col-1);
		
		return findWord(npos, board, word, spos+1, 4);
	}
	if(dir==5) {//right
		if(pos.col==board[0].size()-1)//see above
			return false;
		loc npos(pos.row, pos.col+1);
		
		return findWord(npos, board, word, spos+1, 5);
	}
	if(dir==6) {//down left
		if(pos.row==board.size()-1 || pos.col==0) {//see above
			return false;
		}
		loc npos(pos.row+1, pos.col-1);
		
		return findWord(npos, board, word, spos+1, 6);
	}
	if(dir==7) {//down
		if(pos.row==board.size()-1)//see above
			return false;
		loc npos(pos.row+1, pos.col);
		
		return findWord(npos, board, word, spos+1, 7);
	}
	if(dir==8) {//down right
		if(pos.row==board.size()-1 || pos.col==board[0].size()-1)//see above
			return false;
		loc npos(pos.row+1, pos.col+1);
		
		return findWord(npos, board, word, spos+1, 8);
	}

	else{//if this is the first run of the code
		vector<loc> moveTo;//vector of possible next locations


		if(pos.row==0 && pos.col==0) {//if at origin
			for(int dr=0; dr<=1; dr++) {
				for(int dc=0; dc<=1; dc++) {
					if(dr!=0 || dc!=0){//don't add loc if there's no movement
						loc npos(pos.row+dr, pos.col+dc);
						moveTo.push_back(npos);//add possible loc to vector
					}
				}
			}

			// possible movement:
			// right - 5
			// down - 7
			// down right - 8

			return findWord(moveTo[0], board, word, spos+1, 5) ||
				   findWord(moveTo[1], board, word, spos+1, 7) ||
				   findWord(moveTo[2], board, word, spos+1, 8);
		}

		else if(pos.row==0) {//if on the top row
			for(int dr=0; dr<=1; dr++) {
				for(int dc=-1; dc<=1; dc++) {
					if(dr!=0 || dc!=0){//don't add loc if there's no movement
						loc npos(pos.row+dr, pos.col+dc);
						moveTo.push_back(npos);//add possible loc to vector
					}
				}
			}

			// possible movement:
			// left - 4
			// right - 5
			// down left - 6
			// down - 7
			// down right - 8

			return findWord(moveTo[0], board, word, spos+1, 4) ||
				   findWord(moveTo[1], board, word, spos+1, 5) ||
				   findWord(moveTo[2], board, word, spos+1, 6) ||
				   findWord(moveTo[3], board, word, spos+1, 7) ||
				   findWord(moveTo[4], board, word, spos+1, 8);
		}

		else if(pos.col==0) {//if in the left column
			for(int dr=-1; dr<=1; dr++) {
				for(int dc=0; dc<=1; dc++) {
					if(dr!=0 || dc!=0){//don't add loc if there's no movement
						loc npos(pos.row+dr, pos.col+dc);
						moveTo.push_back(npos);//add possible loc to vector
					}
				}
			}

			// possible movement:
			// up - 2
			// up right - 3
			// right - 5
			// down - 7
			// down right - 8

			return findWord(moveTo[0], board, word, spos+1, 2) ||
				   findWord(moveTo[1], board, word, spos+1, 3) ||
				   findWord(moveTo[2], board, word, spos+1, 5) ||
				   findWord(moveTo[3], board, word, spos+1, 7) ||
				   findWord(moveTo[4], board, word, spos+1, 8);
		}

		else {//otherwise
			for(int dr=-1; dr<=1; dr++) {
				for(int dc=-1; dc<=1; dc++) {
					if(dr!=0 || dc!=0){//don't add loc if there's no movement
						loc npos(pos.row+dr, pos.col+dc);
						moveTo.push_back(npos);//add possible loc to vector
					}
				}
			}

			for(unsigned int iter=1; iter<=moveTo.size(); iter++) {//recurse in all different directions
				if(findWord(moveTo[iter-1], board, word, spos+1, iter))
					return true;
			}
			return false;
		}

		

		
	}

	

}











void removeBWords(vector< vector< vector<char> > >& boards, vector<string>& bwords) {
	//removes all of the boards containing bad words

	//boards is the collection of all boards
	//bwords is a vector of words to be removed

	bool found = false;//bool to skip all of the checks for a board if a word is found
	unsigned int rows = boards[0].size();//size of the boards
	unsigned int cols = boards[0][0].size();
	vector< vector< vector<char> > >::iterator i=boards.begin();//iterator to go through

	while(i!=boards.end()) {
		//for every board
		found=false;
		for(unsigned int w=0; w<bwords.size() && !found; w++) {
			//for every word
			for(unsigned int r=0; r<rows && !found; r++) {
				
				for(unsigned int c=0; c<cols && !found; c++) {
					//for every space in every board
				
					if((*i)[r][c]==bwords[w][0]) {//if it finds the first letter
						loc pos(r,c);//mark the posistion

						if(findWord(pos, *i, bwords[w], 0, 0)) {//if finds the whole word
							i=boards.erase(i);//erase that board
							found=true;//skip the rest of the checks for that board
						}
					}
				}
			}
		}
		if(!found) {//if it didn't erase anything
			i++;	//move the iterator forward
		}
		
	}

}

void removeDuplicates(vector< vector< vector<char> > >& boards) {
	//removes all duplicate boards

	//boards is the collection of all boards

	if(boards.size()<=1)//if there are 0 or 1 boards do nothing
		return;



	for(unsigned int i=0; i<boards.size()-1; i++) {//for every board
		vector< vector<char> > temp1 = boards[i];
		for(unsigned int j=i+1; j<boards.size(); j++) {//for every other board
			vector< vector<char> > temp2 = boards[j];
			if(temp1==temp2) {//if they're equal, erase the second one

				vector< vector< vector<char> > >::iterator temp=boards.begin()+j;

				boards.erase(temp);
			}
		}
	}


}





int main(int argc, char* argv[])
{
	if(argc!=4) {//check input
		cout<<"Invalid arguments";
		return 1;
	}
	if(strcmp(argv[3], "one_solution") && strcmp(argv[3], "all_solutions")) {
		cout<<"Invalid arguments";
		return 1;
	}

	ifstream infile(argv[1]);//check input file
	if (!infile.good()) {
    	cerr << "Can't open " << argv[1] << " to read.\n";
    	exit(1);
  	}

  	std::ofstream outfile(argv[2]);//check output file
	if (!outfile.good()) {
		cerr << "Can't open " << argv[2] << " to write.\n";
		exit(1);
	}

	unsigned int w, h;//width and height
	infile>>w;//will become columns
	infile>>h;//will become rows


	string s, temp;//s is if good or bad, temp is the word
	vector<string> gwords;//vector to hold good words
	vector<string> bwords;//vector to hold bad words

	while(infile>>s) {//for all input
		if(s=="+") {//if good
			infile>>temp;

			gwords.push_back(temp);//add to gwords
		}
		else if(s=="-") {//if bad
			infile>>temp;

			bwords.push_back(temp);//add to bad words
		}
		
	}



	for(unsigned int i=0; i<gwords.size(); i++) {//if any of the good words dont fit
		if(gwords[i].length()>w && gwords[i].length()>h) {//in the specified size
			outfile<<"No solutions found";//output no solutions
			return 0;
		}
	}

	vector< vector<char> > board(h, vector<char>(w,'0'));//make base board with fill char

	
	


	vector< vector< vector<char> > > allBoards;//make collection of all boards


	makeGrids(board, gwords, allBoards);//make all possible boards

	removeDuplicates(allBoards);//remove the duplicate boards
	removeBWords(allBoards, bwords);//remove the boards with bad words


	if(allBoards.empty())	//OUTPUT FOR NO SOLUTIONS, ONE SOLUTION, OR ALL SOLUTIONS
		outfile<<"No solutions found";
	
	else if(!strcmp(argv[3], "one_solution")) {
		outfile<<"Board: \n";
		for(unsigned int r=0; r<allBoards[0].size(); r++) {
			outfile<<"  ";
			for(unsigned int c=0; c<allBoards[0][r].size(); c++)
				outfile<<allBoards[0][r][c];
			outfile<<endl;
		}
	}
	else
		printBoards(allBoards, outfile);




	

	return 0;
}
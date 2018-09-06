// -----------------------------------------------------------------
// HOMEWORK 7 WORD FREQUENCY MAPS
//
// You may use all of, some of, or none of the provided code below.
// You may edit it as you like (provided you follow the homework
// instructions).
// -----------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <cassert>
#include <cstdlib>
#include "mtrand.h"



using namespace std;

// ASSIGNMENT: FILL IN YOUR OWN MAP STRUCTURE
typedef  map<string, map<string, int> > MY_MAP1;
typedef  map<string, map<string, map<string, int> > > MY_MAP2;



// Custom helper function that reads the input stream looking for
// double quotes (a special case delimiter needed below), and white
// space.  Contiguous blocks of alphabetic characters are lowercased &
// packed into the word.
bool ReadNextWord(istream &istr, string &word) {
  char c;
  word.clear();
  while (istr) {
    // just "peek" at the next character in the stream
    c = istr.peek();
    if (isspace(c)) {
      // skip whitespace before a word starts
      istr.get(c);
      if (word != "") {
	// break words at whitespace
	      return true;
      }
    } else if (c == '"') {
      // double quotes are a delimiter and a special "word"
        if (word == "") {
	         istr.get(c);
	         word.push_back(c);
        }
        return true;
    } else if (isalpha(c)) {
      // this a an alphabetic word character
      istr.get(c);
      word.push_back(tolower(c));
    } else {
      // ignore this character (probably punctuation)
      istr.get(c);
    }
  }
  return false;
}


// Custom helper function that reads the input stream looking a
// sequence of words inside a pair of double quotes.  The words are
// separated by white space, but the double quotes might not have
// space between them and the neighboring word.  Punctuation is
// ignored and words are lowercased.
vector<string> ReadQuotedWords(istream &istr) {
  // returns a vector of strings of the different words
  vector<string> answer;
  string word;
  bool open_quote = false;
  while (ReadNextWord(istr,word)) {
    if (word == "\"") {
      if (open_quote == false) { open_quote=true; }
      else { break; }
    } 
    else {
      // add each word to the vector
      answer.push_back(word);
    }
  }
  return answer;
}



// Loads the sample text from the file, storing it in the map data
// structure Window specifies the width of the context (>= 2) of the
// sequencing stored in the map.  parse_method is a placeholder for
// optional extra credit extensions that use punctuation.
void LoadSampleText2(MY_MAP1 &data, const string &filename, int w, const string &parse_method) {
  // open the file stream
  ifstream istr(filename.c_str());
  if (!istr) { 
    cerr << "ERROR cannot open file: " << filename << endl; 
    exit(1);
  } 

  // verify that the parse method is appropriate
  /*bool ignore_punctuation = false;
  if (parse_method == "ignore_punctuation") {
    ignore_punctuation = true;
  } else {
    cerr << "ERROR unknown parse method: " << parse_method << endl;
    exit(1);
  }*/



  string word, lastWord;
  if(ReadNextWord(istr,word)) {//find the first word that isn't a "
    while(word=="\"")
      ReadNextWord(istr,word);
    data[word];//put the first word into the map
  }
  lastWord=word;//cycle variables

  while (ReadNextWord(istr,word)) {//read in all of the words
    // skip the quotation marks (not used for this part)
    if (word == "\"") continue;

    data[lastWord][word]++;//put the next word into the map after the first word
    lastWord=word;//make the next word the first word


  }

  data[lastWord]["-"]++;//count an occurrence of the last word with nothing after it

  cout<<"Loaded "<<filename<<" with window = "<<w<<" and parse method = "
      <<parse_method<<endl<<endl;

}


void LoadSampleText3(MY_MAP2 &data, const string &filename, int w,//same as above but for 
                     const string &parse_method) {                //window=3
  // open the file stream
  ifstream istr(filename.c_str());
  if (!istr) { 
    cerr << "ERROR cannot open file: " << filename << endl; 
    exit(1);
  } 

  // verify that the parse method is appropriate
  /*bool ignore_punctuation = false;
  if (parse_method == "ignore_punctuation") {
    ignore_punctuation = true;
  } else {
    cerr << "ERROR unknown parse method: " << parse_method << endl;
    exit(1);
  }*/



  string word1, word2, word3;
  if(ReadNextWord(istr,word1)) {//find first word that isn't "
    while(word1=="\"")
      ReadNextWord(istr,word1);
    data[word1];//put first word in
  }
  ReadNextWord(istr,word2);
  data[word1][word2];//put second word in after first word
  

  while (ReadNextWord(istr,word3)) {//read in all words
    // skip the quotation marks (not used for this part)
    if (word3 == "\"") continue;

    data[word1][word2][word3]++;//put third word in after first and second
    word1=word2;//cycle variables
    word2=word3;


  }

  data[word1][word2]["-"]++;//handle second to last word
  word1=word2;
  data[word1]["-"]["-"]++;//handle last word

  cout<<"Loaded "<<filename<<" with window = "<<w<<" and parse method = "
      <<parse_method<<endl<<endl;
}



void printCom2(MY_MAP1& data, vector<string>& s) {//print command for window=2
  string phrase=s[0];
  for(unsigned int i=1; i<s.size(); i++) {//not really necessary
    phrase+=" ";
    phrase+=s[i];
  }

  if(data.find(phrase)==data.end())//if the word isn't in the map
    cout<<phrase<<" (0)\n";
  else {
    map<string, int>::iterator iter=data[phrase].begin();//iterator to go through map
    int num=0;
    while(iter!=data[phrase].end()) {//count how many possibilities there are
      num+=iter->second;
      iter++;
    }
    cout<<phrase<<" ("<<num<<")\n";
    for(map<string, int>::iterator j=data[phrase].begin(); j!=data[phrase].end(); j++) {
                                          //output all of the possibilities
      if(j->first!="-")
        cout<<phrase<<" "<<j->first<<" ("<<j->second<<")\n";
    }
  }
  cout<<endl;
}


void printCom3(MY_MAP2& data,vector<string>& s) {//same as above for window=3
  string phrase=s[0];
  for(unsigned int i=1; i<s.size(); i++) {//combine s into 1 string
    phrase+=" ";
    phrase+=s[i];
  }

  if(data.find(s[0])==data.end()) {//if can't find the first word
    cout<<phrase<<" (0)\n";
    return;
  }

  if(s.size()==1) {//if there is only 1 word
    int num=0;
    map<string, map<string,int> >::iterator i=data[s[0]].begin();
    while(i!=data[s[0]].end()) {//count all of the possibilities
      map<string,int>::iterator j=i->second.begin();
      while(j!=i->second.end()) {
        num+=j->second;
        j++;
      }
      i++;
    }
    cout<<phrase<<" ("<<num<<")\n";
    i=data[s[0]].begin();
    num=0;

    while(i!=data[s[0]].end()) {//print all of the possibilities
      map<string,int>::iterator j=i->second.begin();
      while(j!=i->second.end()) {
        num+=j->second;
        j++;
      }
      cout<<phrase<<" "<<i->first<<" ("<<num<<")\n";
      i++;
      num=0;
    }
    cout<<endl;
    return;
  }


  if(data[s[0]].find(s[1])==data[s[0]].end()) {//if cant find the second word
    cout<<phrase<<" (0)\n";
    return;
  }
  else {
    map<string, int>::iterator iter=data[s[0]][s[1]].begin();
                      //do same as above with 2 known words
    int num=0;
    while(iter!=data[s[0]][s[1]].end()) {//count possibilities
      num+=iter->second;
      iter++;
    }
    cout<<phrase<<" ("<<num<<")\n";
    for(map<string, int>::iterator j=data[s[0]][s[1]].begin();//output possibilities
        j!=data[s[0]][s[1]].end(); j++) {

      if(j->first!="-") {
        cout<<phrase<<" "<<j->first<<" ("<<j->second<<")\n";
      }
    }
  }
  cout<<endl;
}



void genCom2(MY_MAP1& data, vector<string>& s, int l, bool r) {
                            //generate a sequence of words with window=2
  string phrase=s[0];
  for(unsigned int i=1; i<s.size(); i++) {//not really necessary
    phrase+=" ";
    phrase+=s[i];
  }

  if(data.find(phrase)==data.end())//if word isn't in the map
    return;
  cout<<phrase;
  string word=phrase, word2;
  static MTRand_int32 mtrand(time(NULL));

  for(int j=0; j<l; j++) {//for each additional word
    if(data[word].size()==0)//if there are no more words
      break;
    if(!r) {//if finding by most common
      map<string, int>::iterator iter=data[word].begin();
      int max=iter->second;//find word with most frequency
      word2=iter->first;
      while(iter!=data[word].end()) {//search through words
        if(iter->second>max) {
          max=iter->second;
          word2=iter->first;
        }
        iter++;
      }
      cout<<" "<<word2;
      word=word2;
    }

    else {//if doing by random
      vector<string> options;
      for(map<string, int>:: iterator iter=data[word].begin(); 
          iter!=data[word].end(); iter++) {//for each possibility

        for(int count=0; count<iter->second; count++) {//put in vector # of times its found
          options.push_back(iter->first);
        }
      }
      if(options.size()-1>0) {
        word=options[mtrand() % (options.size() - 1)];//pick a weighted random word
        cout<<" "<<word;
      }
      options.clear();
    }
  }
  cout<<endl<<endl;

}



//helper function to get the number of times a word is used in a secondary map
//when there are three layers of maps
int getNum(MY_MAP1& data, const string& word) {
  if(data.find(word)==data.end())//if can't find word
    return 0;
  map<string,int>::iterator i=data[word].begin();
  int num=0;
  while(i!=data[word].end()) {//count number of times word is found
    num+=i->second;
    i++;
  }

  return num;

}


void genCom3(MY_MAP2& data, vector<string>& s, int l, bool r) {
                                                 //same as above for window=3
  string phrase=s[0];
  int length=l;
  for(unsigned int i=1; i<s.size(); i++) {//combine words
    phrase+=" ";
    phrase+=s[i];
  }

  if(data.find(s[0])==data.end())//if can't find the first word
    return;

  
  string word1=s[0], word2, word3;//set up 3 strings
  static MTRand_int32 mtrand(time(NULL));


  if(s.size()==1) {//if there is only 1 provided word, find the second word

    length--;

    if(!r) {//if doing most common
      map<string, map<string,int> >::iterator iter=data[word1].begin();
      int max=getNum(data[word1],iter->first);
      word2=iter->first;
      while(iter!=data[word1].end()) {//find most frequent next word
        if(getNum(data[word1],iter->first)>max) {
          max=getNum(data[word1],iter->first);
          word2=iter->first;
        }
        iter++;
      }

      phrase+=" ";
      phrase+=word2;
    }


    else {//same as above, if using random
      vector<string> options;
      for(map<string, map<string,int> >::iterator iter=data[word1].begin(); 
          iter!=data[word1].end(); iter++) {

        int c=getNum(data[word1],iter->first);
        for(int count=0; count<c; count++) {
          options.push_back(iter->first);
        }
      }
      if(options.size()-1>0) {//find weighted random next word
        word2=options[mtrand() % (options.size() - 1)];
        phrase+=" ";
        phrase+=word2;
      }

    }
  }
    
  else {//if there are two words, just make the second word the next word
    if(data[s[0]].find(s[1])==data[s[0]].end())
      return;
    word2=s[1];
  }

  cout<<phrase;

  for(int j=0; j<length; j++) {//find a next word with 2 previous words
    if(data[word1][word2].size()==0)//if no more words
      break;
    if(!r) {//if doing most common
      map<string, int>::iterator iter=data[word1][word2].begin();
      int max=iter->second;
      word3=iter->first;
      while(iter!=data[word1][word2].end()) {//same as above
        if(iter->second>max) {
          max=iter->second;
          word3=iter->first;
        }
        iter++;
      }
      cout<<" "<<word3;
      word1=word2;
      word2=word3;
    }

    else {//if doing random, same as above
      vector<string> options;
      for(map<string, int>:: iterator iter=data[word1][word2].begin(); 
          iter!=data[word1][word2].end(); iter++) {

        for(int count=0; count<iter->second; count++) {
          options.push_back(iter->first);
        }
      }
      if(options.size()-1>0) {
        word3=options[mtrand() % (options.size() - 1)];
        cout<<" "<<word3;
        word1=word2;
        word2=word3;
      }
      options.clear();

    }
  }
  cout<<endl<<endl;

}




int main () {

  // ASSIGNMENT: THE MAIN DATA STRUCTURE
  MY_MAP1 data;//window=2 data structure
  MY_MAP2 data2;//window=3 data structure
  bool useData2=false;//says which structure to use

  // Parse each command
  string command;    
  while (cin >> command) {

    // load the sample text file
    if (command == "load") {//load command
      string filename;
      int window;
      string parse_method;
      cin >> filename >> window >> parse_method;      

      if(window==2)//do window=2 functions
      {
        LoadSampleText2(data,filename,window,parse_method);
        useData2=false;
      }
      else if(window==3)//do window=3 functions
      {
        LoadSampleText3(data2,filename,window,parse_method);
        useData2=true;
      }
      else
        cout<<"\nCurrently unable to process windows of size <2 || >3\n";

    } 

    // print the portion of the map structure with the choices for the
    // next word given a particular sequence.
    else if (command == "print") {//print command
      vector<string> sentence = ReadQuotedWords(cin);

      if(!useData2) {//window=2 function
        printCom2(data, sentence);
      }

      else {//window=3 function
        printCom3(data2, sentence);
      }
    }

    // generate the specified number of words 
    else if (command == "generate") {//generate command
      vector<string> sentence = ReadQuotedWords(cin);
      // how many additional words to generate
      int length;
      cin >> length;
      string selection_method;
      cin >> selection_method;
      bool random_flag;
      if (selection_method == "random") {
	random_flag = true;
      } else {
	assert (selection_method == "most_common");
	random_flag = false;
      }

      if(!useData2) {//window=2 function
        genCom2(data,sentence,length,random_flag);
      }

      else {//window=3 function
        genCom3(data2,sentence,length,random_flag);
      }


    } 
    else if (command == "quit") {
      break;
    } 
    else {
      cout << "WARNING: Unknown command: " << command << endl;
    }
  }
}

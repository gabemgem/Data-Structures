#include <cassert>
#include <list>
#include "superhero.h"
#include "team.h"

using namespace std;

bool isvowel(char c) {
  if (!isalpha(c)) return false;
  char c2 = tolower(c);
  return (c2 == 'a' || c2 == 'e' || c2 == 'i' || c2 == 'o' || c2 == 'u');
}

bool isconsonant(char c) {
  return (isalpha(c) && !isvowel(c));
}

string Team::getName() const {
  if (superheroes.size() == 0)
    return "";
  string answer;
  list<Superhero>::const_iterator itr;
  for (itr = superheroes.begin(); itr != superheroes.end(); itr++) {
    char first_consonant = ' ';
    char first_vowel = ' ';
    string true_identity = itr->getTrueIdentity();
    for (unsigned int j = 0; j < true_identity.size(); j++) {
      if (first_consonant == ' ' && isconsonant(true_identity[j]))
        first_consonant = tolower(true_identity[j]);
      if (first_vowel == ' ' && isvowel(true_identity[j]))
        first_vowel = tolower(true_identity[j]);
    }
    answer.push_back(first_consonant);
    answer.push_back(first_vowel);
  }

  answer[0] = toupper(answer[0]);
  return answer;
}

void Team::operator+=(const Superhero& a) {
    superheroes.push_back(a);
}

void Team::operator-=(const Superhero& a) {
  list<Superhero> nlist;
  for(list<Superhero>::iterator i=superheroes.begin(); i!=superheroes.end(); ++i) {
    if(i->getTrueIdentity()!=a.getTrueIdentity())
      nlist.push_back(*i);
  }

  superheroes=nlist;
}

Team operator+(const Team& a, const Team& b) {
  Team ret;
  list<Superhero>::const_iterator it1 = a.superheroes.begin();
  while(it1!=a.superheroes.end()) {
    ret+=*it1;
    ++it1;
  }

  list<Superhero>::const_iterator it2 = b.superheroes.begin();
  while(it2!=b.superheroes.end()) {
    ret+=*it2;
    ++it2;
  }

  return ret;
}

Team operator+(const Team& a, const Superhero& b) {
  Team ret;
  ret.superheroes=a.superheroes;

  ret+=b;

  return ret;
}

Team operator+(const Superhero& a, const Superhero& b) {
  Team ret;
  ret+=a;
  ret+=b;
  return ret;
}
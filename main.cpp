#include <iostream>
#include "verb.h"
#include <vector>
#include <stdlib.h>
#include <time.h>

using namespace std;

vector<Verb> verbList;
int numVerbs = 0;

void verbsFromFile();
void promptVerb();

string sanitizeInput(string input);

int main(){
  srand(time(NULL));
  verbsFromFile();
  promptVerb();
  return 0;
}

void verbsFromFile(){
  while(!Verb::fin.eof()){
    Verb b;
    b.inputVerb();
    verbList.push_back(b);
    numVerbs++;
  }
  verbList.pop_back();
  numVerbs--;
}

void promptVerb(){
  int verb = rand() % numVerbs;
  int person = rand() % 5;
  string answer = "";
  cout << "Enter the conjugation of " << verbList[verb].getInfinitive() << " for " << Verb::pronouns.spanish[person] << ": ";
  cin >> answer;
  answer = sanitizeInput(answer);
  while(answer != verbList[verb].getPresentConjugation(person)){
    cout << "That is not correct. Please try again: ";
    cin >> answer;
    answer = sanitizeInput(answer);
    if(answer == "help"){
      cout << "Enter the conjugation of " << verbList[verb].getInfinitive() << " for " << Verb::pronouns.spanish[person] << ": ";
      cin >> answer;
      answer = sanitizeInput(answer);
    }
  }
}

string sanitizeInput(string input){
  // sets all uppercase characters in a string to lowercase
  for(auto &c : input){
    if(isupper(c)){
      c = tolower(c);
    }
  }
  return input;
}

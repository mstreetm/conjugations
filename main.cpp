#include <iostream>// input/output
#include "verb.h"// Verb
#include <vector>//vectors
#include <stdlib.h>//rand, srand
#include <time.h>//time for random seeding
#include <cctype>//upper and lowercase things
#include <Windows.h>// SetConsoleOutputCP, SetConsoleInputCP

using namespace std;

vector<Verb> verbList;
int numVerbs = 0;

void verbsFromFile();
void promptVerb();
void newVerb();

string sanitizeInput(string input);

int main(){
  SetConsoleOutputCP(1252);
  SetConsoleCP(1252);
  srand(time(NULL));
  verbsFromFile();
  //newVerb();
  promptVerb();
  return 0;
}

void newVerb(){
  Verb nVerb;
  nVerb.setVerb();
  verbList.push_back(nVerb);
  numVerbs++;
}

void verbsFromFile(){
  while(!Verb::endOfFileInput()){
    Verb b;
    b.inputVerb();
    verbList.push_back(b);
    numVerbs++;
  }
  verbList.pop_back();
  numVerbs--;
}

void promptVerb(){
  int tense = rand() % Verb::numTenses;
  string tenseName = Verb::tenseList[tense];
  int verb = rand() % numVerbs;
  int person = rand() % 5;
  string personName = Verb::pronouns.spanish[person];
  string correctAnswer = verbList[verb].getConjugation(tenseName, person);
  string answer = "";
  cout << "Enter the conjugation of " << verbList[verb].getInfinitive() << " for " << personName << " in the " << tenseName << " tense: ";
  cin >> answer;
  answer = sanitizeInput(answer);
  int attempt = 1;
  while(attempt < 5 && (answer != correctAnswer)){
    cout << "That is not correct. Please try again: ";
    cin >> answer;
    answer = sanitizeInput(answer);
    if(answer == "help"){
      cout << "Enter the conjugation of " << verbList[verb].getInfinitive() << " for " << personName << " in the " << tenseName << " tense: ";
      cin >> answer;
      answer = sanitizeInput(answer);
    }
    attempt++;
  }
  if(answer == correctAnswer){
    cout << "Correct! Try again? (y/n): ";
  }else{
    cout << "That is not correct.  The correct answer was " << correctAnswer << ". Try again? (y/n): ";
  }
  char ans;
  cin >> ans;
  while((ans != 'y') && (ans != 'n')){
    cout << "Please enter y or n: ";
    cin >> ans;
  }
  if(ans == 'y'){
    promptVerb();
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

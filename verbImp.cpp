#include <iostream>
#include "verb.h"
#include <string>
#include <cctype>

using namespace std;

string Verb::validTypes[3] = {"ar", "er", "ir"};

void Verb::setVerb(){
  getInfinitive();
  determineVerbType();
}

void Verb::getVerb(){
  cout << "infinitive: " << infinitive << "\n";
  cout << "type: " << type << "\n";
}

Verb::Verb(string inf){
  infinitive = inf;
  determineVerbType();
}

Verb::Verb(){
  infinitive = "";
  type = "";
}

void Verb::determineVerbType(){
  type = "";
  type += infinitive[infinitive.length()-2];
  type += infinitive[infinitive.length()-1];
  for(auto vType : validTypes){
    if(type == vType){
      return;
    }
  }
  cout << infinitive << " is not a valid infinitive.  The infinitive must end in ";
  for(auto vType : validTypes){
    cout << vType << " ";
  }
  getInfinitive('f');
  determineVerbType();
}

string Verb::sanitizeInput(std::string &input){
  for(auto &c : input){
    if(isupper(c)){
      c = tolower(c);
    }
  }
  return input;
}

void Verb::getInfinitive(char tag, string inf){
  switch(tag){
    case ' ':
      if(infinitive == ""){
        cout << "Enter the verb infinitive: ";
        cin >> infinitive;
        infinitive = sanitizeInput(infinitive);
      } else{
        cout << "The verb is already set.\n";
      }
      break;
    case 'f':
      cout << "\nPlease enter a valid infinitive: ";
      cin >> infinitive;
      break;
    case 'i':
      infinitive = inf;
  }
  sanitizeInput(infinitive);
}

#include <iostream>
#include "verb.h"
#include <string>

using namespace std;

string Verb::validTypes[3] = {"ar", "er", "ir"};

void Verb::setVerb(){
  if(infinitive == ""){
    cout << "Enter the verb infinitive: ";
    cin >> infinitive;
  } else{
    cout << "The verb is already set.\n";
  }
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
  cout << "\nPlease enter a valid infinitive: ";
  cin >> infinitive;
  determineVerbType();
}

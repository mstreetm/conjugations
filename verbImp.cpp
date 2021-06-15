#include <iostream>
#include "verb.h"
#include <string>
#include <cctype>
#include <map>

using namespace std;

string Verb::validTypes[3] = {"ar", "er", "ir"};

map<string, string> Verb::standardText = {
  {"isPresentRegular", "Is the verb regular in the present tense: "},
  {"isYoGo", "Is the verb a yo-go verb: "},
  {"isPresentStemChanger", "Does the verb undergo a stem change in the present tense: "}
};

map<string, string> Verb::helpText = {
  {"isPresentRegular", "Is the verb conjugated regularly in the present tense?\n"},
  {"genericBool", "Please enter true, yes, false, no, or help.\n"},
  {"isYoGo", "Does the present tense yo form of the verb end in \"go\"?\n"},
  {"isPresentStemChanger", "Does the verb stem change for all of the present tense conjugations(other than nosotros)?\n: "}
};

string Verb::trueInputs[2] = {"true", "yes"};
string Verb::falseInputs[2] = {"false", "no"};

void Verb::setVerb(){
  getInfinitive();
  determineVerbType();
  setBooleans();
}

void Verb::getVerb(){
  cout << "infinitive: " << infinitive << "\n";
  cout << "type: " << type << "\n";
  cout << "isPresentRegular: " << isPresentRegular << "\n";
  cout << "isYoGo: " << isYoGo << "\n";
  cout << "isPresentStemChanger: " << isPresentStemChanger << "\n";
}

Verb::Verb(string inf){
  infinitive = inf;
  determineVerbType();
  isPresentRegular = true;
  isYoGo = false;
  isPresentStemChanger = false;
}

Verb::Verb(){
  infinitive = "";
  type = "";
  isPresentRegular = true;
  isYoGo = false;
  isPresentStemChanger = false;
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
      break;
  }
  sanitizeInput(infinitive);
}

void Verb::setBooleans(){
  isPresentRegular = booleanInput("isPresentRegular");
  if(!isPresentRegular){
    isYoGo = booleanInput("isYoGo");
    if(!isYoGo){
      isPresentStemChanger = booleanInput("isPresentStemChanger");
    }
  }
}

bool Verb::booleanInput(string key){
  cout << standardText[key];
  string input;
  cin >> input;
  input = sanitizeInput(input);
  for(auto a : falseInputs){
    if(a == input){
      return false;
    }
  }
  for(auto a : trueInputs){
    if(a == input){
      return true;
    }
  }
  if(input == "help"){
    cout << helpText[key];
  }else{
    cout << helpText["genericBool"];
  }
  return booleanInput(key);
}

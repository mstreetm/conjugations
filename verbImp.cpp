#include <iostream> //input, output
#include "verb.h" //class Verb
#include <string> //string functions
#include <cctype> //upper and lowercase things
#include <map> //maps

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

Verb::ConjRules Verb::endings = {
  .present = {
    .ar = {"o", "as", "a", "amos", "an"},
    .er = {"o", "es", "e", "emos", "en"},
    .ir = {"o", "es", "e", "imos", "en"}
  }
};

Verb::Pronouns Verb::pronouns = {
  .spanish = {"yo", "tu", "el/ella/usted", "nosotros", "ellos/ellas"},
  .english = {"i", "you", "he/she", "we", "they"}
};

void Verb::setVerb(){
  getInfinitive();
  determineVerbType();
  setBooleans();
  setInfinitiveWithoutEnding();
}

void Verb::getVerb(){
  cout << "infinitive: " << infinitive << "\n";
  cout << "type: " << type << "\n";
  cout << "isReflexive: " << isReflexive << "\n";
  cout << "isPresentRegular: " << isPresentRegular << "\n";
  cout << "isYoGo: " << isYoGo << "\n";
  cout << "isPresentStemChanger: " << isPresentStemChanger << "\n";
  cout << "presentStemChange: " << presentStemChange[0] << " " << presentStemChange[1] << "\n";
  cout << "infinitiveWithoutEnding: " << infinitiveWithoutEnding << "\n";
  cout << "presentStemChangeInfinitiveWithoutEnding: " << presentStemChangeInfinitiveWithoutEnding << "\n";
}

Verb::Verb(string inf){
  infinitive = inf;
  determineVerbType();
  verbSetup();
}

Verb::Verb(){
  infinitive = "";
  type = "";
  verbSetup();
}

void Verb::verbSetup(){
  isReflexive = false;
  isPresentRegular = true;
  isYoGo = false;
  isPresentStemChanger = false;
  presentStemChange[0] = "";
  presentStemChange[1] = "";
  infinitiveWithoutEnding = "";
  presentStemChangeInfinitiveWithoutEnding = "";
}

void Verb::determineVerbType(){
  type = "";
  type += infinitive[infinitive.length()-2];
  type += infinitive[infinitive.length()-1];
  if(type == "se"){
    isReflexive = true;
    type = "";
    type += infinitive[infinitive.length()-4];
    type += infinitive[infinitive.length()-3];
  }
  //if the verb type is valid, exit the function
  for(auto vType : validTypes){
    if(type == vType){
      return;
    }
  }
  //else, re-promt for the infinitive, and call self again
  isReflexive = false;
  getInfinitive('f');
  determineVerbType();
}

string Verb::sanitizeInput(std::string input){
  // sets all uppercase characters in a string to lowercase
  for(auto &c : input){
    if(isupper(c)){
      c = tolower(c);
    }
  }
  return input;
}

void Verb::getInfinitive(char tag, string inf){
  // tag defaults to " ", while inf defaults to ""
  switch(tag){
    case ' ':// normal use
      if(infinitive == ""){
        cout << "Enter the verb infinitive: ";
        cin >> infinitive;
        infinitive = sanitizeInput(infinitive);
      } else{
        cout << "The verb is already set.\n";
      }
      break;
    case 'f':// force(invalid type)
      cout << infinitive << " is not a valid infinitive.  The infinitive must end in ";
      for(auto vType : validTypes){
        cout << vType << " ";
      }
      cout << "\nPlease enter a valid infinitive: ";
      cin >> infinitive;
      break;
    case 'i'://initial
      infinitive = inf;
      break;
  }
  infinitive = sanitizeInput(infinitive);
}

void Verb::setBooleans(){
  isPresentRegular = booleanInput("isPresentRegular");
  if(!isPresentRegular){
    isYoGo = booleanInput("isYoGo");
    isPresentStemChanger = booleanInput("isPresentStemChanger");
    setPresentStemChange();
  }
}

void Verb::setPresentStemChange(){
  if(isPresentStemChanger){
    cout << "PLease enter the stem change in this form: \"e ie\": ";
    cin >> presentStemChange[0] >> presentStemChange[1];
  }
}

bool Verb::booleanInput(string key){
  cout << standardText[key];
  string input;
  cin >> input;
  input = sanitizeInput(input);
  for(auto a : falseInputs){//checks against false inputs
    if(a == input){
      return false;
    }
  }
  for(auto a : trueInputs){//checks against true inputs
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

void Verb::setInfinitiveWithoutEnding(){
  if(isPresentRegular || isYoGo || isPresentStemChanger){
    infinitiveWithoutEnding = infinitive;
    infinitiveWithoutEnding.pop_back();
    infinitiveWithoutEnding.pop_back();
    if(isReflexive){
      infinitiveWithoutEnding.pop_back();
      infinitiveWithoutEnding.pop_back();
    }
    setPresentStemChangeInfinitiveWithoutEnding();
  }
}

void Verb::setPresentStemChangeInfinitiveWithoutEnding(){
  if(isPresentStemChanger){
    int len = infinitiveWithoutEnding.length();
    for(int i = len-1; i >= 0; i--){//iterates back to front to find the last spot with the thing to change
      if(infinitiveWithoutEnding[i] == presentStemChange[0][0]){
        for(int j = 0; j < i; j++){
          presentStemChangeInfinitiveWithoutEnding += infinitiveWithoutEnding[j];//puts the first part of the PSCIWE in
        }
        presentStemChangeInfinitiveWithoutEnding += presentStemChange[1];//puts in the stem change
        for(int j = i+1; j < len; j++){
          presentStemChangeInfinitiveWithoutEnding += infinitiveWithoutEnding[j];//fills in the end of the PSCIWE
        }
        break;
      }
    }
  }
}

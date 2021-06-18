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
  {"isPresentStemChanger", "Does the verb undergo a stem change in the present tense: "},
  {"correctYoGo", "Is this the correct yo form of the verb: "}
};

map<string, string> Verb::helpText = {
  {"isPresentRegular", "Is the verb conjugated regularly in the present tense?\n"},
  {"genericBool", "Please enter true, yes, false, no, or help.\n"},
  {"isYoGo", "Does the present tense yo form of the verb end in \"go\"?\n"},
  {"isPresentStemChanger", "Does the verb stem change for all of the present tense conjugations(other than nosotros)?\n"},
  {"correctYoGo", "Should the yo form of this verb have the third-to-last letter removed?\n"}
};

string Verb::trueInputs[3] = {"true", "yes", "1"};
string Verb::falseInputs[3] = {"false", "no", "0"};

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
  setEnglishInfinitive();
  determineVerbType();
  setBooleans();
  setStem();
  setPresentConjugations();
}

void Verb::getVerb(){
  cout << "infinitive: " << infinitive << "\n";
  cout << "englishInfinitive: " << englishInfinitive << "\n";
  cout << "type: " << type << "\n";
  cout << "isReflexive: " << isReflexive << "\n";
  cout << "isPresentRegular: " << isPresentRegular << "\n";
  cout << "isYoGo: " << isYoGo << "\n";
  cout << "isPresentStemChanger: " << isPresentStemChanger << "\n";
  cout << "presentStemChange: " << presentStemChange[0] << " " << presentStemChange[1] << "\n";
  cout << "stem: " << stem << "\n";
  cout << "presentStemChangeStem: " << presentStemChangeStem << "\n";
  cout << "presentCongugations:";
  for(auto c : presentCongugations){
    cout << " " << c;
  }
  cout << "\n";
}

Verb::Verb(string inf){
  infinitive = inf;
  determineVerbType();
  verbSetup();
}

Verb::Verb(){
  infinitive = "";
  verbSetup();
}

void Verb::verbSetup(){
  englishInfinitive = "";
  isReflexive = false;
  isPresentRegular = true;
  isYoGo = false;
  isPresentStemChanger = false;
  presentStemChange[0] = "";
  presentStemChange[1] = "";
  stem = "";
  presentStemChangeStem = "";
  for(auto &c : presentCongugations){
    c = "";
  }
}

void Verb::determineVerbType(){
  string sType = "";
  sType += infinitive[infinitive.length()-2];
  sType += infinitive[infinitive.length()-1];
  if(sType == "se"){
    isReflexive = true;
    sType = "";
    sType += infinitive[infinitive.length()-4];
    sType += infinitive[infinitive.length()-3];
  }
  //if the verb type is valid, exit the function
  for(auto vType : validTypes){
    if(sType == vType){
      type = sType[0];
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

void Verb::setStem(){
  if(isPresentRegular || isYoGo || isPresentStemChanger){
    stem = infinitive;
    stem.pop_back();
    stem.pop_back();
    if(isReflexive){// actually remove the stem(first removed the "se")
      stem.pop_back();
      stem.pop_back();
    }
    setPresentStemChangeStem();
  }
}

void Verb::setPresentStemChangeStem(){
  if(isPresentStemChanger){
    int len = stem.length();
    for(int i = len-1; i >= 0; i--){//iterates back to front to find the last spot with the thing to change
      if(stem[i] == presentStemChange[0][0]){
        for(int j = 0; j < i; j++){
          presentStemChangeStem += stem[j];//puts the first part of the PSCS in
        }
        presentStemChangeStem += presentStemChange[1];//puts in the stem change
        for(int j = i+1; j < len; j++){
          presentStemChangeStem += stem[j];//fills in the end of the PSCS
        }
        break;
      }
    }
  }
}

void Verb::setEnglishInfinitive(){
  cout << "Enter the meaning of " << infinitive << ": ";
  cin >> englishInfinitive;
  englishInfinitive = sanitizeInput(englishInfinitive);
  if(englishInfinitive == "to"){// removes the "to" if it is included
    cin >> englishInfinitive;
  }
  englishInfinitive = sanitizeInput(englishInfinitive);
}

void Verb::setPresentConjugations(){
  if(!isPresentRegular && !isPresentStemChanger && !isYoGo){// if the verb is completley irregular
    for(int i = 0; i < 5; i++){
      cout << "enter the " << pronouns.spanish[i] << " conjugation of " << infinitive << ": ";
      cin >> presentCongugations[i];
    }
    return;
  }
  for(int i = 0; i < 5; i++){// if the verb is somewhat regular
    string currentConjugation = "";
    if(isPresentStemChanger && (i != 3)){// if the verb is a stem changer
      currentConjugation = presentStemChangeStem;
    }else{// if not
      currentConjugation = stem;
    }
    if(isYoGo && (i == 0)){// if the verb is a yo-go
      presentCongugations[i] = currentConjugation + "go";
      cout << presentCongugations[i] << ": ";
      bool correct = booleanInput("correctYoGo");
      if(!correct){
        presentCongugations[i] = currentConjugation;
        presentCongugations[i].pop_back();
        presentCongugations[i] += "go";
      }
      continue;
    }
    switch(type){//if not or a different form
      case 'a':
        currentConjugation += endings.present.ar[i];
        break;
      case 'e':
        currentConjugation += endings.present.er[i];
        break;
      case 'i':
        currentConjugation += endings.present.ir[i];
        break;
    }
    presentCongugations[i] = currentConjugation;
  }
}

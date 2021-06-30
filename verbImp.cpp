#include <iostream> //input, output
#include "verb.h" //class Verb
#include <string> //string functions
#include <cctype> //upper and lowercase things
#include <map> //maps
#include <iostream>// ifstream, ofstream

using namespace std;

string Verb::verbFile = "verbs.txt";

ifstream Verb::fin(verbFile);
ofstream Verb::fout(verbFile, ios::app);

string Verb::validTypes[4] = {"ar", "er", "ir", "ír"};

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
    .ir = {"o", "es", "e", "imos", "en"},
    .Ir = {"o", "es", "e", "ímos", "en"}//I think this one is correct, might not be though
  },
  .preterite = {
    .ar = {"é", "aste", "ó", "amos", "aron"},
    .erir = {"í", "iste", "ió", "imos", "ieron"},
    .Ir = {"í", "íste", "ió", "ímos", "ieron"},//also not 100% sure on this one
    .stemChange = {"e", "iste", "o", "imos", "ieron"},
    .endingChange = {"", "", "yó", "", "yeron"}// so only used on proper forms
  }
};

Verb::Pronouns Verb::pronouns = {
  .spanish = {"yo", "tu", "el/ella/usted", "nosotros", "ellos/ellas/ustedes"},
  .english = {"i", "you", "he/she", "we", "they"}
};

void Verb::setVerb(){
  setInfinitive();
  setEnglishInfinitive();
  setVerbType();
  setBooleans();
  setStem();
  setPresentConjugations();
  outputVerb();
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

void Verb::outputVerb(){
  fout << infinitive << " ";
  fout << englishInfinitive << " ";
  fout << type << " ";
  fout << isReflexive << " ";
  fout << isPresentRegular << " ";
  if(!isPresentRegular){
    fout << isYoGo << " ";
    fout << isPresentStemChanger << " ";
    if(isPresentStemChanger){
      fout << presentStemChange[0] << " ";
      fout << presentStemChange[1] << " ";
    }
  }
  if(isPresentRegular || isYoGo || isPresentStemChanger){
    fout << stem << " ";
  }
  if(isPresentStemChanger){
    fout << presentStemChangeStem << " ";
  }
  for(auto c : presentCongugations){
    fout << c << " ";
  }
  fout << "\n";
}

void Verb::inputVerb(){
  fin >> infinitive;
  fin >> englishInfinitive;
  fin >> type;
  fin >> isReflexive;
  fin >> isPresentRegular;
  if(!isPresentRegular){
    fin >> isYoGo;
    fin >> isPresentStemChanger;
    if(isPresentStemChanger){
      fin >> presentStemChange[0];
      fin >> presentStemChange[1];
    }
  }
  if(isPresentRegular || isYoGo || isPresentStemChanger){
    fin >> stem;
  }
  if(isPresentStemChanger){
    fin >> presentStemChangeStem;
  }
  for(auto &c : presentCongugations){
    fin >> c;
  }
}

Verb::Verb(string inf){
  infinitive = inf;
  setVerbType();
  verbSetup();
}

Verb::Verb(){
  infinitive = "";
  verbSetup();
}

Verb::Verb(const Verb& a){
  infinitive = a.infinitive;
  englishInfinitive = a.englishInfinitive;
  type = a.type;
  isReflexive = a.isReflexive;
  isPresentRegular = a.isPresentRegular;
  isYoGo = a.isYoGo;
  isPresentStemChanger = a.isPresentStemChanger;
  presentStemChange[0] = a.presentStemChange[0];
  presentStemChange[1] = a.presentStemChange[1];
  stem = a.stem;
  presentStemChangeStem = a.presentStemChangeStem;
  for(int i = 0; i < 5; i++){
    presentCongugations[i] = a.presentCongugations[i];
  }
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

void Verb::setVerbType(){
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
      if(vType == "ír"){
        type = 'I';
      }
      return;
    }
  }
  //else, re-promt for the infinitive, and call self again
  isReflexive = false;
  setInfinitive('f');
  setVerbType();
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

void Verb::setInfinitive(char tag, string inf){
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
  if(isPresentRegular || isYoGo || isPresentStemChanger){// else stem is not needed
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
      case 'I':
        currentConjugation += endings.present.Ir[i];
        break;
    }
    presentCongugations[i] = currentConjugation;
  }
}

string Verb::getInfinitive(){
  return infinitive;
};

string Verb::getPresentConjugation(int conNum){
  return presentCongugations[conNum];
}

void Verb::setPreteriteSpellChanges(){
  string ending3 = getEnding(3);
  if(type == 'a'){//for isPreteriteSpellChange
    switch(stem.back()){
      case 'c':
        preteriteSpellChangeStem = stem;
        preteriteSpellChangeStem.pop_back();
        preteriteSpellChangeStem += "qu";
        isPreteriteSpellChange = true;
        break;
      case 'g':
        preteriteSpellChangeStem = stem;
        preteriteSpellChangeStem += "u";
        isPreteriteSpellChange = true;
        break;
      case 'z':
        preteriteSpellChangeStem = stem;
        preteriteSpellChangeStem.pop_back();
        preteriteSpellChangeStem += "c";
        isPreteriteSpellChange = true;
        break;
    }
  }else if((ending3 == "eer") || (ending3 == "oer") || (ending3 == "oír") || (ending3 == "uir") || (getEnding(4) == "caer")){
      isPreteriteEndingChange = true;
  }
}

string Verb::getEnding(int n){
  string ending = "";
  for(int i = infinitive.length()-1; i >= infinitive.length()-n; i--){
    ending = infinitive[i] + ending;
  }
  return ending;
}

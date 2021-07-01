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

string Verb::validTypes[4] = {"ar", "er", "ir", "í­r"};

map<string, string> Verb::standardText = {
  {"isPresentRegular", "Is the verb regular in the present tense: "},
  {"isYoGo", "Is the verb a yo-go verb: "},
  {"isPresentStemChanger", "Does the verb undergo a stem change in the present tense: "},
  {"correctYoGo", "Is this the correct yo form of the verb: "},
  {"isPreteriteRegular", "Is the verb regular in the preterite tense: "},
  {"isPreteriteStemChanger", "Does the verb have a stem change in the preterite tense: "}
};

map<string, string> Verb::helpText = {
  {"isPresentRegular", "Is the verb conjugated regularly in the present tense? (answer no for stem change or yo-go)\n"},
  {"genericBool", "Please enter true, yes, false, no, or help.\n"},
  {"isYoGo", "Does the present tense yo form of the verb end in \"go\"?\n"},
  {"isPresentStemChanger", "Does the verb-stem change for all of the present tense conjugations(other than nosotros)?\n"},
  {"correctYoGo", "Should the yo form of this verb have the third-to-last letter removed?\n"},
  {"isPreteriteRegular", "Is the verb conjugated regularly in the preterite tense? (answer no for stem change)\n"},
  {"isPreteriteStemChanger", "Does the verb-stem change for all of the preterite tense conjugations?\n"}
};

string Verb::trueInputs[3] = {"true", "yes", "1"};
string Verb::falseInputs[3] = {"false", "no", "0"};

Verb::ConjRules Verb::endings = {
  .present = {
    .ar = {"o", "as", "a", "amos", "an"},
    .er = {"o", "es", "e", "emos", "en"},
    .ir = {"o", "es", "e", "imos", "en"},
    .Ir = {"o", "es", "e", "í­mos", "en"}//I think this one is correct, might not be though
  },
  .preterite = {
    .ar = {"é", "aste", "ó", "amos", "aron"},
    .erir = {"í­", "iste", "ió", "imos", "ieron"},
    .Ir = {"í­", "í­ste", "ió", "í­mos", "ieron"},//also not 100% sure on this one
    .stemChange = {"e", "iste", "o", "imos", "ieron"},
    .stemChangeJ = {"e", "iste", "o", "imos", "eron"},
    .endingChange = {"", "", "yó", "", "yeron"}// so only can be used on proper forms
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
  setPresentTense();
  setPreteriteTense();
  outputVerb();
}

void Verb::setPresentTense(){
  setPresentBooleans();
  setPresentStem();
  setPresentConjugations();
}

void Verb::setPreteriteTense(){
  setPreteriteBooleans();
  setPreteriteStem();
  setPreteriteConjugations();
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
  cout << "presentStem: " << presentStem << "\n";
  cout << "presentStemChangeStem: " << presentStemChangeStem << "\n";
  cout << "presentConjugations:";
  for(auto c : presentConjugations){
    cout << " " << c;
  }
  cout << "\n";
  cout << "isPreteriteRegular: " << isPreteriteRegular << "\n";
  cout << "isPreteriteStemChanger: " << isPreteriteStemChanger << "\n";
  cout << "preteriteStem: " << preteriteStem << "\n";
  cout << "isPreteriteSpellChanger: " << isPreteriteSpellChanger << "\n";
  cout << "isPreteriteEndingChanger: " << isPreteriteEndingChanger << "\n";
  cout << "isPreteriteSometimesStemChanger: " << isPreteriteSometimesStemChanger << "\n";
  cout << "preteriteSpellChangeStem: " << preteriteSpellChangeStem << "\n";
  cout << "preteriteCongugations:";
  for(int i = 0; i < 5; i++){
    cout << " " << preteriteConjugations[i];
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
    fout << presentStem << " ";
  }
  if(isPresentStemChanger){
    fout << presentStemChangeStem << " ";
  }
  for(auto c : presentConjugations){
    fout << c << " ";
  }
  fout << isPreteriteRegular << " ";
  fout << isPreteriteStemChanger << " ";
  if(isPreteriteRegular || isPreteriteStemChanger){
    fout << preteriteStem << " ";
  }
  fout << isPreteriteSpellChanger << " ";
  fout << isPreteriteEndingChanger << " ";
  fout << isPreteriteSometimesStemChanger << " ";
  if(isPreteriteSpellChanger){
    fout << preteriteSpellChangeStem << " ";
  }
  for(auto c : preteriteConjugations){
    fout << c << " ";
  }
  fout << "\n";
}

void Verb::inputVerb(){
  verbSetup();
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
    fin >> presentStem;
  }
  if(isPresentStemChanger){
    fin >> presentStemChangeStem;
  }
  for(auto &c : presentConjugations){
    fin >> c;
  }
  fin >> isPreteriteRegular;
  fin >> isPreteriteStemChanger;
  if(isPreteriteRegular || isPreteriteStemChanger){
    fin >> preteriteStem;
  }
  fin >> isPreteriteSpellChanger;
  fin >> isPreteriteEndingChanger;
  fin >> isPreteriteSometimesStemChanger;
  if(isPreteriteSpellChanger){
    fin >> preteriteSpellChangeStem;
  }
  for(auto &c : preteriteConjugations){
    fin >> c;
  }
}

Verb::Verb(string inf){
  verbSetup();
  setVerbType();
  setInfinitive('i', inf);
}

Verb::Verb(){
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
  presentStem = a.presentStem;
  presentStemChangeStem = a.presentStemChangeStem;
  for(int i = 0; i < 5; i++){
    presentConjugations[i] = a.presentConjugations[i];
  }
  isPreteriteRegular = a.isPresentRegular;
  isPreteriteStemChanger = a.isPreteriteStemChanger;
  preteriteStem = a.preteriteStem;
  isPreteriteSpellChanger = a.isPreteriteSpellChanger;
  isPreteriteEndingChanger = a.isPreteriteEndingChanger;
  isPreteriteSometimesStemChanger = a.isPreteriteSometimesStemChanger;
  preteriteSpellChangeStem = a.preteriteSpellChangeStem;
  for(int i = 0; i < 5; i++){
    preteriteConjugations[i] = a.preteriteConjugations[i];
  }
}

void Verb::verbSetup(){
  infinitive = "";
  englishInfinitive = "";
  type = ' ';
  isReflexive = false;
  isPresentRegular = true;
  isYoGo = false;
  isPresentStemChanger = false;
  presentStemChange[0] = "";
  presentStemChange[1] = "";
  presentStem = "";
  presentStemChangeStem = "";
  for(auto &c : presentConjugations){
    c = "";
  }
  isPreteriteRegular = true;
  isPreteriteStemChanger = false;
  preteriteStem = "";
  isPreteriteSpellChanger = false;
  isPreteriteEndingChanger = false;
  isPreteriteSometimesStemChanger = false;
  preteriteSpellChangeStem = "";
  for(auto &c : preteriteConjugations){
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
      if(vType == validTypes[3]){
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

void Verb::setPresentBooleans(){
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

void Verb::setPresentStem(){
  if(isPresentRegular || isYoGo || isPresentStemChanger){// else presentStem is not needed
    presentStem = infinitive;
    presentStem.pop_back();
    presentStem.pop_back();
    if(isReflexive){// actually remove the ending(first removed the "se")
      presentStem.pop_back();
      presentStem.pop_back();
    }
    setPresentStemChangeStem();
  }
}

void Verb::setPresentStemChangeStem(){
  if(isPresentStemChanger){
    int len = presentStem.length();
    for(int i = len-1; i >= 0; i--){//iterates back to front to find the last spot with the thing to change
      if(presentStem[i] == presentStemChange[0][0]){
        for(int j = 0; j < i; j++){
          presentStemChangeStem += presentStem[j];//puts the first part of the PSCS in
        }
        presentStemChangeStem += presentStemChange[1];//puts in the stem change
        for(int j = i+1; j < len; j++){
          presentStemChangeStem += presentStem[j];//fills in the end of the PSCS
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
      cout << "enter the present " << pronouns.spanish[i] << " conjugation of " << infinitive << ": ";
      cin >> presentConjugations[i];
      presentConjugations[i] = sanitizeInput(presentConjugations[i]);
    }
    return;
  }
  for(int i = 0; i < 5; i++){// if the verb is somewhat regular
    string currentConjugation = "";
    if(isPresentStemChanger && (i != 3)){// if the verb is a present stem changer and its not nosotros
      currentConjugation = presentStemChangeStem;
    }else{// if not
      currentConjugation = presentStem;
    }
    if(isYoGo && (i == 0)){// if the verb is a yo-go and its yo
      presentConjugations[i] = currentConjugation + "go";
      cout << presentConjugations[i] << ": ";
      bool correct = booleanInput("correctYoGo");
      if(!correct){
        presentConjugations[i] = currentConjugation;
        presentConjugations[i].pop_back();
        presentConjugations[i] += "go";
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
    presentConjugations[i] = currentConjugation;
  }
}

string Verb::getInfinitive(){
  return infinitive;
};

string Verb::getPresentConjugation(int conNum){
  return presentConjugations[conNum];
}

string Verb::getPreteriteConjugation(int conNum){
  return preteriteConjugations[conNum];
}

void Verb::setPreteriteSpellChanges(){
  string ending3 = getEnding(3);
  if(type == 'a'){//for isPreteriteSpellChanger
    switch(preteriteStem.back()){
      case 'c':
        preteriteSpellChangeStem = preteriteStem;
        preteriteSpellChangeStem.pop_back();
        preteriteSpellChangeStem += "qu";
        isPreteriteSpellChanger = true;
        break;
      case 'g':
        preteriteSpellChangeStem = preteriteStem;
        preteriteSpellChangeStem += "u";
        isPreteriteSpellChanger = true;
        break;
      case 'z':
        preteriteSpellChangeStem = preteriteStem;
        preteriteSpellChangeStem.pop_back();
        preteriteSpellChangeStem += "c";
        isPreteriteSpellChanger = true;
        break;
    }
  }else if((ending3 == "eer") || (ending3 == "oer") || (ending3 == "oí­r") || (ending3 == "uir") || (getEnding(4) == "caer")){
      isPreteriteEndingChanger = true;
  }
  if(isPresentStemChanger && (((presentStemChange[0] == "e") && (presentStemChange[1] == "i")) || ((presentStemChange[0] == "o") && (presentStemChange[1] == "u")))){
    //is a present stem changer of e->i or o->u
    isPreteriteSometimesStemChanger = true;
  }
}

string Verb::getEnding(int n){
  string ending = "";
  for(int i = infinitive.length()-1; i >= infinitive.length()-n; i--){
    ending = infinitive[i] + ending;
  }
  return ending;
}

void Verb::setPreteriteBooleans(){
  isPreteriteRegular = booleanInput("isPreteriteRegular");
  if(!isPreteriteRegular){
    isPreteriteStemChanger = booleanInput("isPreteriteStemChanger");
  }
}

void Verb::setPreteriteStem(){
  if(isPreteriteRegular){
    preteriteStem = presentStem;//ASSUMES that there are no verbs irr. in the present and reg. in the preterite! change if needed(stem generation or alwaus generate present stem)
  }else if(isPreteriteStemChanger){
    cout << "Enter the preterite stem change: ";
    cin >> preteriteStem;
    preteriteStem = sanitizeInput(preteriteStem);
  }else{
    return;
  }
  setPreteriteSpellChanges();
}

void Verb::setPreteriteConjugations(){
  if(!isPreteriteRegular && !isPreteriteStemChanger){// if the verb is completley irregular
    for(int i = 0; i < 5; i++){
      cout << "enter the preterite " << pronouns.spanish[i] << " conjugation of " << infinitive << ": ";
      cin >> preteriteConjugations[i];
      preteriteConjugations[i] = sanitizeInput(preteriteConjugations[i]);
    }
    return;
  }
  for(int i = 0; i < 5; i++){// if the verb is somewhat regular
    string currentConjugation = "";
    if(isPreteriteSpellChanger && (i == 0)){// if the verb is a preterite spell changer and its yo
      currentConjugation = preteriteSpellChangeStem;
    }else if(isPreteriteSometimesStemChanger && ((i == 2) || ( i == 4))){
      currentConjugation = presentStemChangeStem;//yes, present not preterite
    }else{// if not
      currentConjugation = preteriteStem;
    }
    if(isPreteriteStemChanger){
      if(preteriteStem.back() == 'j'){
        currentConjugation += endings.preterite.stemChangeJ[i];
        break;
      }else{
        currentConjugation += endings.preterite.stemChange[i];
      }
    }else if(isPreteriteEndingChanger && ((i == 2) || ( i == 4))){
      currentConjugation += endings.preterite.endingChange[i];
    }else{
      switch(type){//if not or a different form
        case 'a':
          currentConjugation += endings.preterite.ar[i];
          break;
        case 'e':
        case 'i':
          currentConjugation += endings.preterite.erir[i];
          break;
        case 'I':
          currentConjugation += endings.preterite.Ir[i];
          break;
      }
    }
    preteriteConjugations[i] = currentConjugation;
  }
}

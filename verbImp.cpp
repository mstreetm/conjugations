#include <iostream>
#include "verb.h"
#include <string>

using namespace std;

void Verb::setVerb(){
  if(infinitive == ""){
    cout << "Enter the verb infinitive: ";
    cin >> infinitive;
  } else{
    cout << "The verb is already set.\n";
  }
}

void Verb::getVerb(){
  cout << "The infinitive of the verb is: " << infinitive << "\n";
}

Verb::Verb(string inf){
  infinitive = inf;
}

Verb::Verb(){
  infinitive = "";
}

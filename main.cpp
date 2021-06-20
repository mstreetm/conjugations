#include <iostream>
#include "verb.h"
#include <vector>

using namespace std;

vector<Verb> verbList;
int numVerbs = 0;

void verbsFromFile();

int main(){
  verbsFromFile();
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

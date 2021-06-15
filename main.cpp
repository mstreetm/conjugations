#include <iostream>
#include "verb.h"

using namespace std;

int main(){
  Verb a;
  a.setVerb();
  a.getVerb();
  Verb b("correr");
  b.getVerb();
  b.setVerb();
}

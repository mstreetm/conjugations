#include <map>

class Verb{
  public:
    Verb(std::string inf);
    Verb();

    void setVerb();
    void getVerb();

  private:
    static std::string validTypes[3];
    static std::map<std::string, std::string> standardText;
    static std::map<std::string, std::string> helpText;
    static std::string trueInputs[2];
    static std::string falseInputs[2];


    std::string infinitive;
    std::string type;
    bool isPresentRegular;
    bool isYoGo;
    bool isPresentStemChanger;
    std::string infinitiveWithoutEnding;
    std::string englishMeanings[6];
    std::string englishInfinitive;
    std::string stemChange[2];
    std::string stemChangeInfinitiveWithoutEnding;
    std::string presentCongugations;

    void determineVerbType();
    void getInfinitive(char tag = ' ', std::string inf = "");
    void setBooleans();

    std::string sanitizeInput(std::string &input);
    bool booleanInput(std::string key);

};

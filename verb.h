#include <map>

class Verb{
  public:
    Verb(std::string inf);
    Verb();

    void setVerb();
    void getVerb();

  private:
    struct ConjRules{
      struct PresentTense{
        std::string ar[5];
        std::string er[5];
        std::string ir[5];
      };
      PresentTense present;
    };

    struct Pronouns{
      std::string spanish[5];
      std::string english[5];
    };

    static std::string validTypes[3];
    static std::map<std::string, std::string> standardText;
    static std::map<std::string, std::string> helpText;
    static std::string trueInputs[2];
    static std::string falseInputs[2];
    static ConjRules endings;
    static Pronouns pronouns;

    std::string infinitive;
    std::string type;
    bool isReflexive;
    bool isPresentRegular;
    bool isYoGo;
    bool isPresentStemChanger;
    std::string presentStemChange[2];
    std::string infinitiveWithoutEnding;
    std::string presentStemChangeInfinitiveWithoutEnding;
    std::string englishMeanings[6];
    std::string englishInfinitive;
    std::string presentCongugations;

    void determineVerbType();
    void getInfinitive(char tag = ' ', std::string inf = "");
    void setBooleans();
    void setPresentStemChange();
    void setInfinitiveWithoutEnding();
    void setPresentStemChangeInfinitiveWithoutEnding();

    void verbSetup();

    std::string sanitizeInput(std::string &input);
    bool booleanInput(std::string key);

};

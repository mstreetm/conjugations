class Verb{
  public:
    static std::string validTypes[3];

    Verb(std::string inf);
    Verb();

    void setVerb();
    void getVerb();

  private:
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

    std::string sanitizeInput(std::string &input);
};

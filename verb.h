class Verb{
  public:
    Verb(std::string inf);
    Verb();
    void setVerb();
    void getVerb();
  private:
    std::string infinitive;
    std::string infinitiveWithoutEnding;
    std::string type;
    std::string englishMeanings[6];
    std::string englishInfinitive;
    bool isPresentRegular;
    bool isYoGo;
    bool isPresentStemChanger;
    std::string stemChange[2];
    std::string stemChangeInfinitiveWithoutEnding;
    std::string presentCongugations;
};

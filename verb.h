#include <map>// std::maps
#include <fstream>//ifstream, ofstream

class Verb{
  public:
    // constructors, all call vrebSteup()
    Verb(std::string inf);// constructor including the verb infinitive
    Verb(); //default constructor

    void setVerb();// sets verb properties by user prompt for the most part
    void getVerb();// prints verb properties and labels
    void outputVerb();// outputs the verb to the text file

  private:
    // for verb endings
    struct ConjRules{
      struct PresentTense{
        std::string ar[5];
        std::string er[5];
        std::string ir[5];
      };
      PresentTense present;
    };

    //for pronouns ex. yo, I, etc.
    struct Pronouns{
      std::string spanish[5];
      std::string english[5];
    };

    static std::string outputFile;// the file to output the verbs to

    static std::ofstream fout;//the file output;

    static std::string validTypes[3];// valid types of verb ex. "ar"
    static std::map<std::string, std::string> standardText;// the standard prompt text for setVerb();
    static std::map<std::string, std::string> helpText;// the help text for setVerb();
    static std::string trueInputs[3];// strings that should evaluate as true (for booleans)
    static std::string falseInputs[3];// strings that should evaluate as false (for booleans)
    static ConjRules endings;// the verb endings
    static Pronouns pronouns;// the pronouns

    // verb properties
    std::string infinitive;// the verb infinitive
    std::string englishInfinitive;// "to ____" note: crops off the to if included in setup
    char type;// signifies the type of verb ex. "ar" but stores the first letter ex. 'a'
    bool isReflexive;// is the verb reflexive? (does it end in "se")
    bool isPresentRegular;// is the verb regular in the present tense
    bool isYoGo;// is teh verb a yo-go verb
    bool isPresentStemChanger;// is the verb a stem changer in the present tense
    std::string presentStemChange[2];// what is the change in the form "e ie"
    std::string stem;// the infinitive without the last 2(or 4 for reflexive) letters
    std::string presentStemChangeStem;// the above with the stem change
    std::string presentCongugations[5];// the spanish, present tense conjugations of the verb

    void determineVerbType();// determines the type ex "ar"(sets 'a') of the verb and sets isReflexive
    void getInfinitive(char tag = ' ', std::string inf = "");// prompts the user for the verb infinitive, validates it, and re-prompts if nesecary
    void setBooleans();// sets the boolean type properties by prompting the user
    void setPresentStemChange();// sets the presentStemChange if the verb is a present stem changer by prompting the user
    void setStem();// sets the stem
    void setPresentStemChangeStem();// sets the presentStemChangeStem if nesecary
    void setEnglishInfinitive();// sets the english meaning ex "eat" for comer not to eat, the to would be removed;
    void setPresentConjugations();// sets the present tense conjugations for the verb

    void verbSetup();// used for constructors, sets most properties to "" or false, while setting isPresentRegular to true;

    std::string sanitizeInput(std::string input);// takes in a string, and outputs it with all lowercase letters
    bool booleanInput(std::string key);//takes a map key and prompts the user for information about one of the boolean properties, gives help if needed.
};

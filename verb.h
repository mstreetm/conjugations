#include <map>// std::maps
#include <fstream>//ifstream, ofstream

class Verb{
  public:
    static std::ifstream fin;//the file input

    // constructors, all call vrebSteup()
    Verb(std::string inf);// constructor including the verb infinitive
    Verb(); //default constructor
    Verb(const Verb& a);// for copying

    void setVerb();// sets verb properties by user prompt for the most part, also calls outputVerb
    void getVerb();// prints verb properties and labels(only for present b/c not using. delete if not updated by 7/8)
    void outputVerb();// outputs the verb to the text file
    void inputVerb();//inputs a verb from the text file

    std::string getInfinitive();// returns the verb infinitive
    std::string getPresentConjugation(int conNum);// returns the specified present conjugation

    //for pronouns ex. yo, I, etc.
    struct Pronouns{
      std::string spanish[5];
      std::string english[5];
    };

    static Pronouns pronouns;// the pronouns

  private:
    // for verb endings
    struct ConjRules{
      struct PresentTense{
        std::string ar[5];
        std::string er[5];
        std::string ir[5];
        std::string Ir[5]; //for accent i(í)
      };
      struct PreteriteTense{
        std::string ar[5];
        std::string erir[5];
        std::string Ir[5];//for accent i(í)
        std::string stemChange[5];
        std::string stemChangeJ[5];//ends in j
        std::string endingChange[5];
      };
      PresentTense present;
      PreteriteTense preterite;
    };

    static std::string verbFile;// the file to input/output the verbs to

    static std::ofstream fout;//the file output;

    static std::string validTypes[4];// valid types of verb ex. "ar"
    static std::map<std::string, std::string> standardText;// the standard prompt text for setVerb();
    static std::map<std::string, std::string> helpText;// the help text for setVerb();
    static std::string trueInputs[3];// strings that should evaluate as true (for booleans)
    static std::string falseInputs[3];// strings that should evaluate as false (for booleans)
    static ConjRules endings;// the verb endings

    // verb properties
    std::string infinitive;// the verb infinitive
    std::string englishInfinitive;// "to ____" note: crops off the to if included in setup
    char type;// signifies the type of verb ex. "ar" but stores the first letter ex. 'a'
    bool isReflexive;// is the verb reflexive? (does it end in "se")

    //PRESENT
    bool isPresentRegular;// is the verb regular in the present tense
    bool isYoGo;// is the verb a yo-go verb
    bool isPresentStemChanger;// is the verb a stem changer in the present tense
    std::string presentStemChange[2];// what is the change in the form "e ie"
    std::string presentStem;// the infinitive without the last 2(or 4 for reflexive) letters
    std::string presentStemChangeStem;// the above with the stem change
    std::string presentCongugations[5];// the spanish, present tense conjugations of the verb

    //PRETERITE
    bool isPreteriteRegular;//is the verb regular in the preterite tense
    bool isPreteriteStemChange;//is the verb a stem changer in the preterite tense
    std::string preteriteStem;//the stem to use for preterite tense
    bool isPreteriteSpellChange;//-car, -gar, -zar
    bool isPreteriteEndingChange;//-caer, -eer, -oer, -oír, -uir
    std::string preteriteSpellChangeStem;//the stem to use for spelling changes
    std::string preteriteConjugations[5];//the spanish preterite tense conjugations of the verb

    void setVerbType();// sets the type ex "ar"(sets 'a') of the verb and sets isReflexive
    void setInfinitive(char tag = ' ', std::string inf = "");// prompts the user for the verb infinitive, validates it, and re-prompts if nesecary
    void setPresentBooleans();// sets the boolean type properties by prompting the user
    void setPresentStemChange();// sets the presentStemChange if the verb is a present stem changer by prompting the user
    void setPresentStem();// sets the present stem
    void setPresentStemChangeStem();// sets the presentStemChangeStem if nesecary
    void setEnglishInfinitive();// sets the english meaning ex "eat" for comer not to eat, the to would be removed;
    void setPresentConjugations();// sets the present tense conjugations for the verb
    void setPreteriteBooleans();//sets the top two preterite bools
    void setPreteriteSpellChanges();//sets the isPreteriteSpellChange and preteriteSpellChangeStem or isPreteriteEndingChange
    void setPreteriteStem();//sets the preteriteStem
    void setPreteriteConjugations();//sets the conjugations for the preterite tense

    void setPresentTense();//sets all the things for the present PresentTense
    void setPreteriteTense();//sets all the things for the preterite tense

    void verbSetup();// used for constructors, sets most properties to "" or false, while setting isPresentRegular to true;

    std::string sanitizeInput(std::string input);// takes in a string, and outputs it with all lowercase letters
    std::string getEnding(int n);//gets the last n letters of the infinitive
    bool booleanInput(std::string key);//takes a map key and prompts the user for information about one of the boolean properties, gives help if needed.
};

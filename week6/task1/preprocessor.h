#include <istream>
#include <ostream>
#include <stack>

class Preprocessor {
public:
    Preprocessor() = default;

    void process(std::istream &sin, std::ostream &sout);

private:
    void changeState(char c);

    void processSlash();

    void processStar();

    void processBackslash();

    void processQuote();

    void processDoubleQuote();

    void processNewline();

    void processRegularChars(char c);

    enum class State : int {
        Slash = 0,
        Star,
        Comment,
        MultilineComment,
        Code,
        Char,
        EscapeChar,
        String
    };

    std::stack<State> m_states;
    std::string m_buf;
};

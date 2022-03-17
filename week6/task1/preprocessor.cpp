#include "preprocessor.h"

void Preprocessor::process(std::istream &sin, std::ostream &sout) {
    m_states.push(State::Code);
    char c;
    sin.unsetf(std::ios_base::skipws);
    while (sin >> c) {
        changeState(c);
        auto state = m_states.top();
        if (static_cast<int>(state) & 4) {
            sout << m_buf;
            sout.flush();
            m_buf.clear();
        }
    }
    m_states.pop();
}

void Preprocessor::changeState(char c) {
    switch (c) {
        case '/':
            processSlash();
            break;
        case '*':
            processStar();
            break;
        case '\\':
            processBackslash();
            break;
        case '\'':
            processQuote();
            break;
        case '"':
            processDoubleQuote();
            break;
        case '\n':
            processNewline();
            break;
        default:
            processRegularChars(c);
            break;
    }
}

void Preprocessor::processSlash() {
    auto state = m_states.top();
    switch (state) {
        case State::Slash:
            m_buf.clear();
            m_states.top() = State::Comment;
            break;
        case State::Star:
            m_states.pop();
            m_states.pop();
            break;
        case State::Comment:
            [[fallthrough]];
        case State::MultilineComment:
            break;
        case State::Code:
            m_states.push(State::Slash);
            m_buf.push_back('/');
            break;
        case State::EscapeChar:
            m_states.pop();
            [[fallthrough]];
        default:
            m_buf.push_back('/');
            break;
    }
}

void Preprocessor::processStar() {
    auto state = m_states.top();
    switch (state) {
        case State::Slash:
            m_buf.clear();
            m_states.top() = State::MultilineComment;
            break;
        case State::Comment:
            break;
        case State::MultilineComment:
            m_states.push(State::Star);
            break;
        case State::EscapeChar:
            m_states.pop();
            [[fallthrough]];
        default:
            m_buf.push_back('*');
            break;
    }
}

void Preprocessor::processBackslash() {
    auto state = m_states.top();
    switch (state) {
        case State::Comment:
        case State::MultilineComment:
            break;
        case State::Char:
        case State::String:
            m_states.push(State::EscapeChar);
            m_buf.push_back('\\');
            break;
        case State::EscapeChar:
            m_states.pop();
            [[fallthrough]];
        default:
            m_buf.push_back('\\');
            break;
    }
}

void Preprocessor::processQuote() {
    auto state = m_states.top();
    switch (state) {
        case State::Slash:
        case State::Star:
            m_buf.push_back('\'');
            m_states.top() = State::Char;
            break;
        case State::Comment:
        case State::MultilineComment:
            break;
        case State::Code:
            m_states.push(State::Char);
            m_buf.push_back('\'');
            break;
        case State::Char:
            m_states.pop();
            m_buf.push_back('\'');
            break;
        case State::EscapeChar:
            m_states.pop();
            [[fallthrough]];
        default:
            m_buf.push_back('\'');
            break;
    }
}

void Preprocessor::processDoubleQuote() {
    auto state = m_states.top();
    switch (state) {
        case State::Slash:
        case State::Star:
            m_buf.push_back('"');
            m_states.top() = State::String;
            break;
        case State::Comment:
        case State::MultilineComment:
            break;
        case State::Code:
            m_states.push(State::String);
            m_buf.push_back('"');
            break;
        case State::String:
            m_states.pop();
            m_buf.push_back('"');
            break;
        case State::EscapeChar:
            m_states.pop();
            [[fallthrough]];
        default:
            m_buf.push_back('"');
            break;
    }
}

void Preprocessor::processNewline() {
    auto state = m_states.top();
    switch (state) {
        case State::MultilineComment:
            break;
        case State::Slash:
        case State::Star:
        case State::Comment:
        case State::EscapeChar:
            m_states.top() = State::Code;
            [[fallthrough]];
        default:
            m_buf.push_back('\n');
            break;
    }
}

void Preprocessor::processRegularChars(char c) {
    auto state = m_states.top();
    switch (state) {
        case State::Comment:
        case State::MultilineComment:
            break;
        case State::Slash:
        case State::Star:
        case State::EscapeChar:
            m_states.pop();
            [[fallthrough]];
        default:
            m_buf.push_back(c);
            break;
    }
}


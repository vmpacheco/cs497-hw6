#include <iostream>
#include <string>

enum class State {INIT, INT, DECIMAL_POINT, FRACTION, WORD, STRING, ERROR};

void tokenize(std::string& inputString) {
    State state = State::INIT;
    std::string lexeme = "";
    bool contin = true;
    int index = 0;
    while (contin) {
        char c;
        if (index < inputString.size()) {
            c = inputString[index];
        }
        else {
            c = -1;
        }
        std::cerr << "state = " << static_cast<int>(state)
            << ", index = " << index
            << ", c = " << c
            << ", lexeme = '" << lexeme
            << "'\n";
        switch (state) {
            case State::INIT:
                if (c >= '0' && c <= '9') {
                    state = State::INT;
                    index--;  // reuse this character in the next state
                } else if (c >= 'a' && c <= 'z') {
                    state = State::WORD;
                    index--;
                } else if (c == '"') {
                    state = State::STRING;
                } else if (c == ' ') {
                } else if (c == -1) {  // end of input, just let the while loop terminate
                } else {
                    std::cerr << "State::INIT going to ERROR\n";
                    state = State::ERROR;
                    index--;
                }
                break;
            case State::INT:
                if (c >= '0' && c <= '9') {
                    lexeme += c;
                } else if (c == '.') {
                    lexeme += c;
                    state = State::DECIMAL_POINT;
                } else {
                    std::cout << "Found integer '" << lexeme << "'\n";
                    lexeme = "";
                    state = State::INIT;
                    index--;
                }
                break;
            case State::DECIMAL_POINT:
                if (c >= '0' && c <= '9') {
                    state = State::FRACTION;
                    index--;
                } else {
                    std::cout << "Digit expected following decimal point\n";
                    state = State::ERROR;
                    index--;
                }
                break;
            case State::FRACTION:
                if (c >= '0' && c <= '9') {
                    lexeme += c;
                } else {
                    std::cout << "Found float '" << lexeme << "'\n";
                    lexeme = "";
                    state = State::INIT;
                    index--;
                }
                break;
            case State::WORD:
                if (c >= 'a' && c <= 'z') {
                    lexeme += c;
                } else {
                    std::cout << "Found word '" << lexeme << "'\n";
                    lexeme = "";
                    state = State::INIT;
                    index--;
                }
                break;
            case State::STRING:
                if (c == '"') {
                    std::cout << "Found string '" << lexeme << "'\n";
                    lexeme = "";
                    state = State::INIT;
                } else if (c == -1) {
                    std::cout << "Closing quote expected\n";
                    state = State::ERROR;
                    index--;
                } else {
                    lexeme += c;
                }
                break;
            case State::ERROR:
                std::cerr << "Error: character '" << c << "' found at index " << index << "\n";
                contin = false;
                break;
        }
        if (state == State::INIT && c == -1) {
            contin = false;
        }
        index++;
    }
}

int main() {
    std::string line;
    getline(std::cin, line);
    tokenize(line);
}

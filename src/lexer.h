#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>
#include <spdlog/spdlog.h>

// 1. Move Token outside the class so main.cpp can see it easily
enum TokenType {
    NUMBER, IDENTIFIER,
    LET, PRINT, // <--- Add your keywords here
    PLUS, EQUALS, SEMICOLON, UNKNOWN, END_OF_FILE
};

struct Token {
    TokenType type;
    std::string value;
};

class Lexer {
private:
    std::string source;
    int pos;
    char current;

    void advance(); // Moves the cursor

public:
    // 2. FIXED: This constructor takes the string input
    Lexer(std::string input);

    // 3. The logic that main.cpp calls
    std::vector<Token> tokenize();
};

#endif
//
//    Copyright 2025 grish-ka
//
//    Licensed under the Apache License, Version 2.0 (the "License");
//    you may not use this file except in compliance with the License.
//    You may obtain a copy of the License at
//
//        http://www.apache.org/licenses/LICENSE-2.0
//
//    Unless required by applicable law or agreed to in writing, software
//    distributed under the License is distributed on an "AS IS" BASIS,
//    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//    See the License for the specific language governing permissions and
//    limitations under the License.
//

#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>
#include <spdlog/spdlog.h>

#pragma once


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
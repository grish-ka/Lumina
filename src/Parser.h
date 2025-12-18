//
// Created by grishka on 18/12/2025.
//

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

#ifndef LUMINA_PARSER_H
#define LUMINA_PARSER_H
#include <vector>

#include "ast.h"
#include "lexer.h"


class Parser {
private:
    std::vector<Token> tokens;
    size_t pos = 0;

public:
    Parser(std::vector<Token> t);

    // Looks at the current token
    Token peek();

    // Moves the cursor forward
    Token advance();

    // Ensures the code follows the rules
    void expect(TokenType type, std::string msg);

    std::unique_ptr<ASTNode> parseStatement();

    std::unique_ptr<ASTNode> parseVarDeclaration();

    std::unique_ptr<ASTNode> parsePrimary();
};


#endif //LUMINA_PARSER_H
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

#include "Parser.h"

#include "ast.h"
std::vector<Token> tokens;
size_t pos = 0;


Parser::Parser(std::vector<Token> t) : tokens(std::move(t)) {}

// Looks at the current token
Token Parser::peek() { return tokens[pos]; }

// Moves the cursor forward
Token Parser::advance() { return tokens[pos++]; }

void Parser::expect(TokenType type, std::string msg) {
    if (peek().type != type) {
        spdlog::error("Syntax Error: {}", msg);
        exit(1);
    }
    advance(); // Move to next token
}
// 2. PARSING LOGIC (The Rules)

// This is the starting point for every line of code
std::unique_ptr<ASTNode> Parser::parseStatement() {
    if (peek().type == LET) {
        return parseVarDeclaration();
    }
    // In the future, you will add "if (peek().type == PRINT)" here
    return nullptr;
}

// Logic for: let <name> = <expression> ;
std::unique_ptr<ASTNode> Parser::parseVarDeclaration() {
    advance(); // Consume 'let'

    std::string varName = peek().value;
    expect(IDENTIFIER, "Expected variable name after 'let'");

    expect(EQUALS, "Expected '=' after variable name");

    // For now, we expect a single number.
    // Later, this will call parseExpression() for math like 50 + 10.
    auto valueNode = parsePrimary();

    expect(SEMICOLON, "Expected ';' at end of statement");

    spdlog::info("Parser: Successfully parsed variable declaration '{}'", varName);
    return std::make_unique<VarDeclStmt>(varName, std::move(valueNode));
}

// Logic for the smallest units of code (Numbers or Names)
std::unique_ptr<ASTNode> Parser::parsePrimary() {
    if (peek().type == NUMBER) {
        std::string val = advance().value;
        return std::make_unique<NumberExpr>(val);
    }

    spdlog::error("Parser: Expected an expression but found '{}'", peek().value);
    return nullptr;
}
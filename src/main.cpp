//
// Created by grishka on 17/12/2025.
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

#include "lexer.h"
#include "Parser.h"
#include "ast.h"
#include <spdlog/spdlog.h>
#include <iostream>

// Concept: Recursive function to print the tree so you can see if it worked
void printAST(ASTNode* node, int indent = 0) {
    if (!node) return;

    std::string space(indent, ' ');

    // Check if the node is a Variable Declaration
    if (auto v = dynamic_cast<VarDeclStmt*>(node)) {
        spdlog::info("{} [Variable Declaration] Name: {}", space, v->name);
        printAST(v->initializer.get(), indent + 4);
    }
    // Check if the node is a Number
    else if (auto n = dynamic_cast<NumberExpr*>(node)) {
        spdlog::info("{} [Number Literal] Value: {}", space, n->value);
    }
}

void runParserTest() {
    // 1. Your test string
    std::string input = "let x = 50 ;";
    spdlog::info("--- Starting Parser Test ---");
    spdlog::info("Input: \"{}\"", input);

    // 2. Lexical Analysis
    Lexer lexer(input);
    std::vector<Token> tokens = lexer.tokenize();

    // 3. Syntax Analysis (Parsing)
    Parser parser(tokens);
    std::unique_ptr<ASTNode> root = parser.parseStatement();

    // 4. Verify results
    if (root) {
        spdlog::info("SUCCESS: AST built successfully.");
        spdlog::info("Tree Structure:");
        printAST(root.get());
    } else {
        spdlog::error("FAILURE: Parser returned a null tree.");
    }
}

int main() {
    spdlog::set_level(spdlog::level::debug);
    runParserTest();
    return 0;
}
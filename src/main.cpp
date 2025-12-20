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
void printTree(ASTNode* node, std::string prefix = "", bool isLast = true) {
    if (!node) return;

    // 1. Draw the current branch
    // ├── for middle items, └── for the last item in a branch
    std::cout << prefix << (isLast ? "└── " : "├── ");

    // 2. Identify the Node and print its data
    if (auto v = dynamic_cast<VarDeclStmt*>(node)) {
        std::cout << "\033[1;32m[VarDecl]\033[0m name: " << v->name << std::endl;

        // Move to the initializer (the value)
        // We add to the prefix to draw the vertical line for the next level
        std::string newPrefix = prefix + (isLast ? "    " : "│   ");
        printTree(v->initializer.get(), newPrefix, true);
    }
    else if (auto n = dynamic_cast<NumberExpr*>(node)) {
        std::cout << "\033[1;34m[Literal]\033[0m value: " << n->value << std::endl;
    }
}

void runParserTest() {
    // 1. Your test string
    std::string input = "let x = 50 ;";
    spdlog::info("--- Starting Parser Test ---");
    spdlog::info("Input: \"{}\"", input);

    // 2. Lexical Analysis
    Lexer lexer(input);
    auto tokens = lexer.tokenize();

    // 3. Syntax Analysis (Parsing)
    Parser parser(tokens);
    auto root = parser.parseStatement();

    if (root) {
        std::cout << "\nAST Visualizer:" << std::endl;
        printTree(root.get()); // Trigger the 'tree' command style
        std::cout << std::endl;
    }
}

int main() {
    spdlog::set_level(spdlog::level::debug);
    runParserTest();
    return 0;
}
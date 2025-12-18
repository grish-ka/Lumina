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
#include <spdlog/spdlog.h>
#include <vector>
#include <map>

// Concept: Helper function to turn Enum IDs into readable text for the logs
std::string tokenTypeToString(TokenType type) {
    static std::map<TokenType, std::string> typeNames = {
        {NUMBER, "NUMBER"}, {IDENTIFIER, "IDENTIFIER"},
        {LET, "LET"}, {PRINT, "PRINT"},
        {PLUS, "PLUS"},
        {EQUALS, "EQUALS"}, {SEMICOLON, "SEMICOLON"}, {UNKNOWN, "UNKNOWN"},
        {END_OF_FILE, "EOF"}
    };
    return typeNames[type];
}

void runLexerTest() {
    std::string testInput = "let x = 50 + 10 ;";

    spdlog::info("--- Starting Lexer Test ---");
    spdlog::info("Input string: \"{}\"", testInput);

    Lexer testLexer(testInput);
    std::vector<Token> tokens = testLexer.tokenize();

    // Loop through and log each token found
    for (const auto& t : tokens) {
        spdlog::info("Token Found: [Type: {:<10} | Value: {:<5}]",
                     tokenTypeToString(t.type), t.value);
    }

    // A simple logic check using spdlog levels
    if (tokens.size() >= 6 && tokens[3].value == "50") {
        spdlog::info("RESULT: SUCCESS - Multi-digit number '50' captured correctly.");
    } else {
        spdlog::error("RESULT: FAILURE - Number capture failed or token count mismatch!");
    }
}

int main() {
    // Set global log level (can be debug, info, warn, error, etc.)
    // spdlog::set_level(spdlog::level::debug);

    spdlog::info("Lumina Compiler Pipeline Initialized");

    runLexerTest();

    spdlog::info("Lumina Shutdown Cleanly");
    return 0;
}
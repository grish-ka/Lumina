#include "lexer.h"
#include <spdlog/spdlog.h>
#include <cctype>
#include <unordered_map>

// Constructor: Sets up the source and initializes the 'cursor'
Lexer::Lexer(std::string input) : source(std::move(input)), pos(0) {
    if (!source.empty()) {
        current = source[0];
    } else {
        current = '\0';
    }
    spdlog::debug("Lexer: Initialized with source length {}", source.length());
}

// Moves the cursor to the next character in the string
void Lexer::advance() {
    pos++;
    if (pos < source.length()) {
        current = source[pos];
    } else {
        current = '\0'; // End of the string
    }
}

const std::unordered_map<std::string, TokenType> KEYWORDS = {
    {"let", LET},
    {"print", PRINT}
};

// The main loop that turns characters into a list of Tokens
std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens;
    spdlog::info("Lumina: Starting tokenization...");

    while (current != '\0') {
        // 1. SKIP WHITESPACE
        if (std::isspace(current)) {
            advance();
            continue;
        }

        // 2. NUMBERS
        if (std::isdigit(current)) {
            std::string num = "";
            while (current != '\0' && std::isdigit(current)) {
                num += current;
                advance();
            }
            tokens.push_back({NUMBER, num});
            spdlog::debug("Lexed Number: {}", num);
            continue;
        }

        // 3. IDENTIFIERS & KEYWORDS
        if (std::isalpha(current)) {
            std::string word = "";
            while (current != '\0' && std::isalnum(current)) {
                word += current;
                advance();
            }

            // Keyword Logic: Is it 'let'?
            if (word == "let") {
                tokens.push_back({LET, word});
                spdlog::debug("Lexed Keyword: LET");
            } else {
                tokens.push_back({IDENTIFIER, word});
                spdlog::debug("Lexed Identifier: {}", word);
            }
            continue;
        }

        // 4. SYMBOLS (Don't forget advance() here!)
        if (current == '=') {
            tokens.push_back({EQUALS, "="});
            spdlog::debug("Lexed Symbol: =");
            advance();
            continue;
        }
        if (current == '+') {
            tokens.push_back({PLUS, "+"});
            spdlog::debug("Lexed Symbol: +");
            advance();
            continue;
        }
        if (current == ';') {
            tokens.push_back({SEMICOLON, ";"});
            spdlog::debug("Lexed Symbol: ;");
            advance();
            continue;
        }

        // 5. FALLBACK (If it's something unknown)
        spdlog::warn("Lexer skipping unknown char: '{}'", current);
        advance();
    }

    tokens.push_back({END_OF_FILE, "EOF"});
    spdlog::info("Lumina: Tokenization complete. Found {} tokens.", tokens.size());
    return tokens;
}
#include "token.h"
#include <string>
// nicola you can change these here for the keywords
std::unordered_map<std::string, TokenType> language_keywords = {
    {"function", FUNCTION},
    {"auto", LET},
    {"true", TRUE},
    {"false", FALSE},
    {"if", IF},
    {"else", ELSE},
    {"return", RETURN},
    {"for", FOR},
    {"loop", LOOP}
};

// Define TokenType as a string alias
// Function to look up an identifier in language_keywords
TokenType LookupIdent(const std::string& ident) {
    if (language_keywords.find(ident) != language_keywords.end()) {
        return language_keywords[ident];
    }
    return IDENT;
}

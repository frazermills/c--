#include <iostream>
#include <string>
#include <map>
#include "token.h"

// Tokenize function
Token NextToken(const std::string& input) {
    static int position = 0;
    static int readPosition = 0;
    static char ch = ' ';

    // Helper function to read the next character
    auto readChar = [&]() {
        if (readPosition >= input.size()) {
            ch = 0;
        } else {
            ch = input[readPosition];
        }
        position = readPosition;
        readPosition++;
    };

    // Helper function to create a new token
    auto newToken = [](TokenType tokenType, char character) -> Token {
        return {tokenType, std::string(1, character)};
    };

    // Skip whitespace
    while (std::isspace(ch)) {
        readChar();
    }

    Token tok;

    switch (ch) {
    case '=':
        if (input[readPosition] == '=') {
            char character = ch;
            readChar();
            tok = {EQ, std::string(1, character) + ch};
        } else {
            tok = newToken(ASSIGN, ch);
        }
        break;
    case '+':
        tok = newToken(PLUS, ch);
        break;
    case '-':
        tok = newToken(MINUS, ch);
        break;
    case '!':
        if (input[readPosition] == '=') {
            char character = ch;
            readChar();
            tok = {NOT_EQ, std::string(1, character) + ch};
        } else {
            tok = newToken(BANG, ch);
        }
        break;
    case '/':
        tok = newToken(SLASH, ch);
        break;
    case '*':
        tok = newToken(ASTERISK, ch);
        break;
    case '<':
        tok = newToken(LT, ch);
        break;
    case '>':
        tok = newToken(GT, ch);
        break;
    case ';':
        tok = newToken(SEMICOLON, ch);
        break;
    case ',':
        tok = newToken(COMMA, ch);
        break;
    case '{':
        tok = newToken(LBRACE, ch);
        break;
    case '}':
        tok = newToken(RBRACE, ch);
        break;
    case '(':
        tok = newToken(LPAREN, ch);
        break;
    case ')':
        tok = newToken(RPAREN, ch);
        break;
    case 0:
        tok.Type = EOF_TOKEN;
        tok.Literal = "";
        break;
    default:
        if (std::isalpha(ch) || ch == '_') {
            std::string literal = std::string(1, ch);
            while (std::isalnum(input[readPosition]) || input[readPosition] == '_') {
                literal += input[readPosition];
                readPosition++;
            }
            tok.Literal = literal;
            TokenType keyword = "";
            if (literal == "function") {
                keyword = FUNCTION;
            } else if (literal == "auto") {
                keyword = LET;
            } else if (literal == "true") {
                keyword = TRUE;
            } else if (literal == "false") {
                keyword = FALSE;
            } else if (literal == "if") {
                keyword = IF;
            } else if (literal == "else") {
                keyword = ELSE;
            } else if (literal == "return") {
                keyword = RETURN;
            } else if (literal == "out") {
                keyword = OUT;
            } else if (literal == "for") {
                keyword = FOR;
            } else if (literal == "loop") {
                keyword = LOOP;
            } else if (literal == "and") {
                keyword = AND;
            } else if (literal == "or") {
                keyword = OR;
            } else if (literal == "not") {
                keyword = NOT;
            } else if (literal == "conintue") {
                keyword = CONTINUE;
            } else if (literal == "break") {
                keyword = BREAK;
            } else if (literal == "jumpto") {
                keyword = JUMP;
            } else if (literal == "\"") {
                keyword = STR_WRAP;
            } else if (literal == "\'") {
                keyword = CHAR_WRAP;
            } else if (literal == "int") {
                keyword = INT;
            } else if (literal == "string") {
                keyword = STRING;
            } else if (literal == "char") {
                keyword = CHAR;
            }
            if (keyword != "") {
                tok.Type = keyword;
            } else {
                tok.Type = IDENT;
            }
        } else if (std::isdigit(ch)) {
            std::string literal = std::string(1, ch);
            while (std::isdigit(input[readPosition])) {
                literal += input[readPosition];
                readPosition++;
            }
            tok.Type = INT;
            tok.Literal = literal;
        } else {
            tok = newToken(ILLEGAL, ch);
        }
    }

    readChar();
    return tok;
}

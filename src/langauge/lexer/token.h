#ifndef TOKEN_H_
#define TOKEN_H_

#include <string>
#include <unordered_map>

using TokenType = std::string;

// Define constants for token types
const TokenType ILLEGAL = "ILLEGAL";
const TokenType EOF_TOKEN = "EOF";
const TokenType IDENT = "IDENT";
const TokenType ASSIGN = "=";
const TokenType PLUS = "+";
const TokenType MINUS = "-";
const TokenType BANG = "!";
const TokenType ASTERISK = "*";
const TokenType SLASH = "/";
const TokenType LT = "<";
const TokenType GT = ">";
const TokenType EQ = "==";
const TokenType NOT_EQ = "!=";
const TokenType COMMA = ",";
const TokenType SEMICOLON = ";";
const TokenType LPAREN = "(";
const TokenType RPAREN = ")";
const TokenType LBRACE = "{";
const TokenType RBRACE = "}";
const TokenType FUNCTION = "FUNCTION";
const TokenType LET = "LET";
const TokenType TRUE = "TRUE";
const TokenType FALSE = "FALSE";
const TokenType IF = "IF";
const TokenType ELSE = "ELSE";
const TokenType RETURN = "RETURN";
const TokenType FOR = "FOR";
const TokenType LOOP = "LOOP";
const TokenType JUMP = "JUMP";
const TokenType BREAK = "BREAK";
const TokenType CONTINUE = "CONTINUE";
const TokenType AND = "AND";
const TokenType OR = "OR";
const TokenType NOT = "NOT";
const TokenType INT = "<DATATYPE>INT";
const TokenType STRING = "<DATATYPE>STRING";
const TokenType CHAR = "<DATATYPE>CHAR";
const TokenType BOOL = "<DATATYPE>BOOL";
const TokenType STR_WRAP = "STR_WRAP";
const TokenType CHAR_WRAP = "CHAR_WRAP";
const TokenType OUT = "<BUILTIN_FUNC_OUT>";

typedef std::string TokenType;

TokenType lookup_ident(std::string);

struct Token
{
    TokenType Type;
    std::string Literal;
};

#endif // TOKEN_H_

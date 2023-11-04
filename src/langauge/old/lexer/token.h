#ifndef TOKEN_H_
#define TOKEN_H_

#include <string>
#include <map>

typedef std::string TokenType;

TokenType lookup_ident(std::string);

struct Token
{
    TokenType Type;
    std::string Literal;
};

// these are all placeholder tokens, nicola you can change these
const std::string ILLEGAL = "ILLEGAL";
const std::string _EOF = "EOF";

const std::string IDENT = "IDENT";

// literals
const std::string INT = "INT";

// operators
const std::string ASSIGN = "=";
const std::string PLUS = "+";
const std::string MINUS = "-";
const std::string EXCLIMATION = "!";
const std::string ASTERISK = "*";
const std::string FWSLASH = "/";

const std::string LT = "<";
const std::string GT = ">";

const std::string EQ = "==";
const std::string NEQ = "==";

const std::string COMMA = ",";
const std::string SEMICOLON = ";";

const std::string LBRACK = "(";
const std::string RBRACK = ")";
const std::string LBRACE = "{";
const std::string RBRACE = "}";

// keywords
const std::string FUNCTION = "FUNCTION";
const std::string VAR = "VAR";
const std::string _TRUE = "TRUE";
const std::string _FALSE = "FALSE";
const std::string IF = "IF";
const std::string ELSE = "ELSE";
const std::string RETURN = "RETURN";


std::map<std::string, TokenType> keywords =
{
    {"function", FUNCTION},
    {"var", VAR},
	{"true", _TRUE},
	{"false", _FALSE},
	{"if", IF},
	{"else", ELSE},
	{"return", RETURN}
};

#endif // TOKEN_H_

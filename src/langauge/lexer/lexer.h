#include <string>

#ifndef LEXER_H_
#define LEXER_H_

struct
{
	std::string input;
	int cur_char_pos;
	int next_char_pos;
	char cur_char;
} Lexer;

const std::string ASSGIN = "=";
#endif // LEXER_H_

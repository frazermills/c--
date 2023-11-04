#include <string>

#ifndef LEXER_H_
#define LEXER_H_

struct Lexer
{
	std::string input;
	int cur_char_pos;
	int next_char_pos;
	char cur_char;
} ;

#endif // LEXER_H_

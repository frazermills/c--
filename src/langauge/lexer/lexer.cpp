#include "token.h"
#include "lexer.h"

// gives the next character and advances the position in the input string
void read_char(void)
{
	if (Lexer.next_char_pos >= Lexer.input.length())
		Lexer.cur_char = 0;
	else
		Lexer.cur_char = Lexer.input[Lexer.next_char_pos];

	// advances the position in input string
	Lexer.cur_char_pos = Lexer.next_char_pos;
	Lexer.next_char_pos++;
}

void new_token(void)
{
	Token tok;

	switch (Lexer.cur_char)
	{
		case '=':
			tok = new_token(ASSIGN);
	}
}

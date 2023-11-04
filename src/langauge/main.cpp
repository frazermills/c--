#include <iostream>
#include "lexer/token.h"
#include "lexer/lexer.h"

int main(int argc, char **argv) {
    std::string input = "fn test (int a, char c);";
    Token tok;

    do {
        tok = NextToken(input);
        std::cout << "Type: " << tok.Type << ", Literal: " << tok.Literal << std::endl;
    } while (tok.Type != EOF_TOKEN);

    return 0;
}

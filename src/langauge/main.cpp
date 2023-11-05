#include <iostream>
#include <fstream>
#include <string>
#include "lexer/token.h"
#include "lexer/lexer.h"
#include "parser/ast.h"

std::string read_file(std::string file_name)
{
    std::string file_string, std_string_line;

    std::fstream file(file_name);

    while(std::getline(file, std_string_line))
    {
        for(auto c : std_string_line){
            file_string.push_back(c);
        }
    }

    return file_string;
}

int main(int argc, char **argv) {
    std::string input = read_file(argv[1]);
  
    Token tok;
    std::ofstream File("token.txt", std::ios::out| std::ios::binary);

    do {
        tok = NextToken(input);
        File << "Type: " << tok.Type << ", Literal: " << tok.Literal << std::endl;
    } while (tok.Type != EOF_TOKEN);

    File.close();

    return 0;
}

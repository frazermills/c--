#include <iostream>
#include <sstream>
#include <vector>
#include <bits/stdc++.h>
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
    std::vector<TokenType>tokes;
    std::string input = read_file(argv[1]);
    std::string temp1;
    std::string active_line;

    Token tok;
    std::ofstream File("token.txt", std::ios::out| std::ios::binary);

    do {
        tok = NextToken(input);
        File << "Type: " << tok.Type << ", Literal: " << tok.Literal << std::endl;
    } while (tok.Type != EOF_TOKEN);

    File.close();

    temp1 = read_file("token.txt");
    std::stringstream ss(temp1);

    while (std::getline(ss, active_line))
    {
        tokes.push_back(active_line);
    }

    return 0;
}

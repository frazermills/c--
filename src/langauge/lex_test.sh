#!/usr/bin/env sh

g++ main.cpp lexer/lexer.cpp lexer/token.cpp parser/ast.cpp -o lex_test

./lex_test test.cmm

cat token.txt

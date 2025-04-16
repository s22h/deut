#pragma once

#include <cstddef>
#include <string>
#include <vector>

#include "token.h"

struct Lexer {
	size_t pos;
	size_t line;
	size_t column;
	std::string source;
	std::string file;
	std::vector<Token> tokens;
};

void run_lexer(Lexer& lex);
void identifier(Lexer& lex);
void number(Lexer& lex);
void unknown(Lexer& lex);
void whitespace(Lexer& lex);
void char_token(Lexer& lex, TokenType type);
char next(Lexer& lex);


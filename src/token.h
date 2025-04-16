#pragma once

#include <string>

enum TokenType {
	TOK_IDENTIFIER,
	TOK_NUMBER,
	TOK_WHITESPACE,
	TOK_EQUALS,
	TOK_ADD,
	TOK_SUB,
	TOK_MULT,
	TOK_DIV,
	TOK_COMMA,
	TOK_COLON,
	TOK_LBRACE,
	TOK_RBRACE,
	TOK_LPAREN,
	TOK_RPAREN,
	TOK_SEMICOLON,
	TOK_SINGLE_QUOTE,
	TOK_DOUBLE_QUOTE,
	TOK_EXCLAMATION_MARK,
	// keep TOK_UNKNOWN as last token type
	TOK_UNKNOWN
};

struct Token {
	TokenType type;
	std::string file;
	size_t line;
	size_t column;
	std::string data;
};

const char* token_type(TokenType type);

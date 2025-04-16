#include "lexer.h"

#include <cassert>
#include <cctype>
#include <cstdio>
#include <string>

char next(Lexer& lex)
{
	if (lex.source[lex.pos] == '\n') {
		++lex.line;
		lex.column = 0;
	} else {
		++lex.column;
	}

	++lex.pos;

	if (lex.source.size() <= lex.pos + 1) {
		return 0;
	}

	return lex.source[lex.pos];
}

bool ident_start(char ch) { return std::isalpha(ch) || ch == '_'; }

bool ident_part(char ch) { return std::isalnum(ch) || ch == '_'; }

void identifier(Lexer& lex)
{
	char ch = lex.source[lex.pos];
	assert(ident_start(ch));
	size_t line = lex.line;
	size_t col = lex.column;

	std::string ident = "";

	while (ident_part(ch)) {
		ident += ch;
		ch = next(lex);
	}

	lex.tokens.push_back(Token { .type = TOK_IDENTIFIER, .file = lex.file, .line = line, .column = col, .data = ident });
}

void number(Lexer& lex)
{
	char ch = lex.source[lex.pos];
	assert(std::isdigit(ch));

	std::string ident = "";

	size_t line = lex.line;
	size_t col = lex.column;

	// TODO: doubles/floats, other notations etc.
	while (std::isdigit(ch)) {
		ident += ch;
		ch = next(lex);
	}

	lex.tokens.push_back(Token { .type = TOK_NUMBER, .file = lex.file, .line = line, .column = col, .data = ident });
}

void run_lexer(Lexer& lex)
{
	char ch;

	while (lex.pos < lex.source.size()) {
		ch = lex.source[lex.pos];

		if (std::isspace(ch)) {
			whitespace(lex);
		} else if (ident_start(ch)) {
			identifier(lex);
		} else if (std::isdigit(ch)) {
			number(lex);
		} else if (ch == '{') {
			char_token(lex, TOK_LBRACE);
		} else if (ch == '}') {
			char_token(lex, TOK_RBRACE);
		} else if (ch == '(') {
			char_token(lex, TOK_LPAREN);
		} else if (ch == ')') {
			char_token(lex, TOK_RPAREN);
		} else if (ch == '=') {
			char_token(lex, TOK_EQUALS);
		} else if (ch == '+') {
			char_token(lex, TOK_ADD);
		} else if (ch == '-') {
			char_token(lex, TOK_SUB);
		} else if (ch == '*') {
			char_token(lex, TOK_MULT);
		} else if (ch == '/') {
			char_token(lex, TOK_DIV);
		} else if (ch == ',') {
			char_token(lex, TOK_COMMA);
		} else if (ch == ':') {
			char_token(lex, TOK_COLON);
		} else if (ch == ';') {
			char_token(lex, TOK_SEMICOLON);
		} else if (ch == '"') {
			char_token(lex, TOK_DOUBLE_QUOTE);
		} else if (ch == '\'') {
			char_token(lex, TOK_SINGLE_QUOTE);
		} else if (ch == '!') {
			char_token(lex, TOK_EXCLAMATION_MARK);
		} else {
			unknown(lex);
		}
	}
}

void unknown(Lexer& lex)
{
	char ch = lex.source[lex.pos];
	lex.tokens.push_back(Token {
		.type = TOK_UNKNOWN,
		.file = lex.file,
		.line = lex.line,
		.column = lex.column,
		.data = std::string(&ch, 1) });
	next(lex);
}

void whitespace(Lexer& lex)
{
	char ch = lex.source[lex.pos];

	assert(std::isspace(ch));

	std::string ws = "";

	size_t line = lex.line;
	size_t col = lex.column;

	while (std::isspace(ch)) {
		ws += ch;
		ch = next(lex);
	}

	lex.tokens.push_back(Token {
		.type = TOK_WHITESPACE,
		.file = lex.file,
		.line = line,
		.column = col,
		.data = ws });
}

void char_token(Lexer& lex, TokenType type)
{
	char ch = lex.source[lex.pos];
	lex.tokens.push_back(Token {
		.type = type,
		.file = lex.file,
		.line = lex.line,
		.column = lex.column,
		.data = std::string(&ch, 1) });
	next(lex);
}

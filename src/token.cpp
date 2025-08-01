#include "token.h"

#define TOKSTR(x) \
	case x:       \
		return #x

const char* token_type(TokenType type)
{
	switch (type) {
		TOKSTR(TOK_IDENTIFIER);
		TOKSTR(TOK_NUMBER);
		TOKSTR(TOK_WHITESPACE);
		TOKSTR(TOK_EQUALS);
		TOKSTR(TOK_ADD);
		TOKSTR(TOK_SUB);
		TOKSTR(TOK_MULT);
		TOKSTR(TOK_DIV);
		TOKSTR(TOK_COMMA);
		TOKSTR(TOK_COLON);
		TOKSTR(TOK_SEMICOLON);
		TOKSTR(TOK_LBRACE);
		TOKSTR(TOK_RBRACE);
		TOKSTR(TOK_LPAREN);
		TOKSTR(TOK_RPAREN);
		TOKSTR(TOK_DOUBLE_QUOTE);
		TOKSTR(TOK_SINGLE_QUOTE);
		TOKSTR(TOK_EXCLAMATION_MARK);
		TOKSTR(TOK_UNKNOWN);
	default:
		return "TOK_UNKNOWN";
	}
}

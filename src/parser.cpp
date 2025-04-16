#include "parser.h"

#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <string>

#include "token.h"

void run_parser(Parser& parser)
{
	statement(parser);

	if (parser.status != 0) {
		fprintf(stderr, "Error %u\n", parser.status);
	}
}

size_t find_nth(const std::string& str, const std::string& findee, int nth)
{
	size_t pos = 0;
	int cnt = 0;

	while (cnt != nth) {
		pos = str.find(findee, ++pos);

		if (pos == std::string::npos) {
			return -1;
		}

		++cnt;
	}

	return pos;
}

void print_error(Parser& parser, Token& token, std::string& err)
{
	fprintf(stderr, "Error in %s:%zu:%zu\n",
		token.file.c_str(),
		token.line,
		token.column);

	size_t line = find_nth(parser.source, "\n", token.line);
	size_t line_end = find_nth(parser.source, "\n", token.line + 1);

	fprintf(stderr, "%s\n", parser.source.substr(line, line_end - 1).c_str());
	fprintf(stderr, "%s%s %s\n",
		std::string(token.column, ' ').c_str(),
		std::string(token.data.size(), '^').c_str(),
		err.c_str());
}

void statement(Parser& parser)
{
	Token token = parser.tokens[parser.index];

	if (token.type == TOK_IDENTIFIER) {
		if (token.data.compare("proc") == 0) {
			token = parser.tokens[++parser.index];
			assert(token.type == TOK_WHITESPACE);
			token = parser.tokens[++parser.index];

			if (token.type != TOK_IDENTIFIER) {
				std::string err = std::string("expected TOK_IDENTIFIER, found ") + token_type(token.type);
				print_error(parser, token, err);
				parser.status = 1;
				return;
			}

			parser.ast.push_back(
				AstNode {
					.type = "PROCDECL",
					.procDecl = AstProcDecl { .name = token.data } });
		}
	}
}

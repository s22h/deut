#pragma once

#include <vector>

#include "token.h"

struct AstProcDecl {
	std::string name;
};

struct AstNode {
	// TODO: make enum out of this
	std::string type;
	AstProcDecl procDecl;
};

struct Parser {
	size_t index;
	unsigned short status;
	std::string source;
	std::vector<Token>& tokens;

	// TODO: make a proper AST
	std::vector<AstNode> ast;
};

void run_parser(Parser& parser);
void statement(Parser& parser);

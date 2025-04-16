#include <cstdio>
#include <fstream>
#include <string>

#include "lexer.h"
#include "parser.h"

std::string read_file(std::string file_path)
{
	std::ifstream infile(file_path);
	std::string buffer;
	std::string line;

	while (std::getline(infile, line)) {
		buffer.append(line);
		buffer.append("\n");
	}

	return buffer;
}

int main()
{
	std::string source = read_file("test.deu");

	Lexer lexer = Lexer { .pos = 0, .line = 0, .column = 0, .source = source, .file = "test.deu" };
	run_lexer(lexer);

	Parser parser = Parser { .index = 0, .status = 1, .source = source, .tokens = lexer.tokens };
	run_parser(parser);

	for (auto it : parser.ast) {
		printf("%s: %s\n", it.type.c_str(), it.procDecl.name.c_str());
	}

	return 0;
}

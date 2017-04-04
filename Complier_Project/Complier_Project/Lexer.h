#pragma once
#include <string>
#include "Token.h"

struct Lexer {
	std::string::iterator first;
	std::string::iterator last;

	Lexer(std::string::iterator first, std::string::iterator last) : first(first), last(last) {}
	bool eof() { return (first == last); }
	char look_ahead();
	void consume();
	Token* next();
	void print(Token* t);
};


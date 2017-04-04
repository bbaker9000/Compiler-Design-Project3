// Complier_Project.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <cassert>
#include "Lexer.h"
#include "Parser.h"
#include <string>
#include <vector>
#include "Eval.h"
#include <fstream>

int main(int argc, char *argv[])
{
	try {
		Context ctx;
		std::ifstream infile(argv[1]);
		while (!infile.eof()) {
			std::string test;
			std::getline(infile, test);
			Lexer* lex = new Lexer(test.begin(), test.end());
			std::vector<Token*> toks;
			while (!lex->eof()) {
				toks.push_back(lex->next());
			}
			Parser* p = new Parser(toks.begin(), toks.end() - 1, ctx);
			Expr* e = p->parse_Expr();
		}
		
	}
	catch(char* err){
		std::cout << err;
	}

    return 0;
}


#include "stdafx.h"
#include "Lexer.h"
#include <vector>
#include <iostream>
#include <cctype>
void printEnum(Token*);
char Lexer::look_ahead() {
	if (eof())
		return 0;
	else
		return *first;
}
void Lexer::consume() {
	if (eof())
		throw("Error in consume. Cannot consume past the end of the input");
	else
		++first;
}
Token* Lexer::next() {
	std::string::iterator itr = first;
	while (!eof())
	{
		switch (look_ahead()) {
		case '(': {
			consume();
			return new Punc_token(L_paren);
			break;
		}
		case ')': {
			consume();
			return new Punc_token(R_paren);	
			break;
		}
		case '&': {
			consume();
			if (look_ahead() == '&') {
				consume();
				return new Punc_token(Ampr);
				}
			break;
		}
		case '|': {
			consume();
			if (look_ahead() == '|') {
				consume();
				return new Punc_token(Vert_bar);
			}
			break;
		}
		case '!': {
			consume();
			if (look_ahead() == '=') {
				consume();
				return new Punc_token(Not_eq);
			}
			return new Punc_token(Excl);
			break;
		}
		case '+': {
			consume();
			return new Punc_token(Plus);
			break;
		}
		case '-': {
			consume();
			return new Punc_token(Minus);
			break;
		}
		case '*': {
			consume();
			return new Punc_token(Star);
			break;
		}
		case '/': {
			consume();
			return new Punc_token(F_slash);
			break;
		}
		case '\\': {
			consume();
			return new Punc_token(B_slash);
			break;
		}
		case '%': {
			consume();
			return new Punc_token(Percent);
			break;
		}
		case '<': {
			consume();
			if (look_ahead() == '='){
				consume();
				return new Punc_token(Less_Eq);
			}
			return new Punc_token(Less);
			break;
		}
		case '>': {
			consume();
			if (look_ahead() == '=') {
				consume();
				return new Punc_token(Greater_Eq);
			}
			return new Punc_token(Greater);
			break;
		}
		case '=': {
			consume();
			if (look_ahead() == '=') {
				consume();
				return new Punc_token(Equal);
			}

		}
		case '?': {
			consume();
			return new Punc_token(Question);
		}
		case ':': {
			consume();
			return new Punc_token(Colon);
		}
		case '0': {
			consume();
			if (!eof() && std::isdigit(look_ahead())) {
				continue;
			}
			else {
				std::string str(itr, first);
				int n = std::stoi(str);
				return new Int_token(Int, n);
			}
		}
		case '1': {
			consume();
			if (!eof() && std::isdigit(look_ahead())) {
				continue;
			}
			else {
				std::string str(itr, first);
				int n = std::stoi(str);
				return new Int_token(Int, n);
			}
		}
		case '2': {
			consume();
			if (!eof() && std::isdigit(look_ahead())) {
				continue;
			}
			else {
				std::string str(itr, first);
				int n = std::stoi(str);
				return new Int_token(Int, n);
			}
		}
		case '3': {
			consume();
			if (!eof() && std::isdigit(look_ahead())) {
				continue;
			}
			else {
				std::string str(itr, first);
				int n = std::stoi(str);
				return new Int_token(Int, n);
			}
		}
		case '4': {
			consume();
			if (!eof() && std::isdigit(look_ahead())) {
				continue;
			}
			else {
				std::string str(itr, first);
				int n = std::stoi(str);
				return new Int_token(Int, n);
			}
		}
		case '5': {
			consume();
			if (!eof() && std::isdigit(look_ahead())) {
				continue;
			}
			else {
				std::string str(itr, first);
				int n = std::stoi(str);
				return new Int_token(Int, n);
			}
		}
		case '6': {
			consume();
			if (!eof() && std::isdigit(look_ahead())) {
				continue;
			}
			else {
				std::string str(itr, first);
				int n = std::stoi(str);
				return new Int_token(Int, n);
			}
		}
		case '7': {
			consume();
			if (!eof() && std::isdigit(look_ahead())) {
				continue;
			}
			else {
				std::string str(itr, first);
				int n = std::stoi(str);
				return new Int_token(Int, n);
			}
		}
		case '8': {
			consume();
			if (!eof() && std::isdigit(look_ahead())) {
				continue;
			}
			else {
				std::string str(itr, first);
				int n = std::stoi(str);
				return new Int_token(Int, n);
			}
		}
		case '9': {
			consume();
			if (!eof() && std::isdigit(look_ahead())) {
				continue;
			}
			else {
				std::string str(itr, first);
				int n = std::stoi(str);
				return new Int_token(Int, n);
			}
		}
		case 't': {
			consume();
			if (!eof() && look_ahead() == 'r'){
				consume();
				if (!eof() && look_ahead() == 'u') {
					consume();
					if (!eof() && look_ahead() == 'e') {
						consume();
						return new Bool_token(Bool, true);
					}
				}
			}		
		}
		case 'f': {
			consume();
			if (!eof() && look_ahead() == 'a') {
				consume();
				if (!eof() && look_ahead() == 'l') {
					consume();
					if (!eof() && look_ahead() == 's') {
						consume();
						if (!eof() && look_ahead() == 'e') {
							consume();
							return new Bool_token(Bool, false);
						}
					}
				}
			}
		}
		case ' ':
		case '\n':
		case '\t':{
			consume();
			continue;
		}
		}
		return nullptr;
	}
}
void Lexer::print(Token* t) {
	struct V : Token::Visitor{
		void visit(Punc_token* t) { printEnum(t); std::cout << "\n"; }
		void visit(Bool_token* t) { printEnum(t); std::cout << " value:" << t->value << "\n"; }
		void visit(Int_token* t) { printEnum(t); std::cout << " value:" << t->value << "\n"; }
	};
	V vis;
	t->accept(vis);
	
}
void printEnum(Token* t){
	switch (t->kind) {
	case 0:{ std::cout << "EoF"; break; }
	case 1: { std::cout << "Left Paren"; break; }
	case 2: { std::cout << "Right Paren"; break; }
	case 3: { std::cout << "Ampresand"; break; }
	case 4: { std::cout << "Vertical Bar"; break; }
	case 5: { std::cout << "Exclemation"; break; }
	case 6: { std::cout << "Boolean"; break; }
	case 7: { std::cout << "Integer"; break; }
	case 8: { std::cout << "Plus"; break; }
	case 9: { std::cout << "Minus"; break; }
	case 10: { std::cout << "Star"; break; }
	case 11: { std::cout << "Forward Slash"; break; }
	case 12: { std::cout << "Back Slash"; break; }
	case 13: { std::cout << "Percent"; break; }
	case 14: { std::cout << "Less Than"; break; }
	case 15: { std::cout << "Greater Than"; break; }
	case 16: { std::cout << "Greater Equals"; break; }
	case 17: { std::cout << "Less Equals"; break; }
	case 18: { std::cout << "Equals"; break; }
	case 19: { std::cout << "Question"; break; }
	case 20: { std::cout << "Colon"; break; }
	}
}
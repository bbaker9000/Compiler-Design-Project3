#ifndef PARSER_HPP
#define PARSER_HPP



#include "Token.h"
#include <vector>
#include "Type.h"
#include "Eval.h"


struct Parser {
	std::vector<Token*>::iterator first;
	std::vector<Token*>::iterator last;
	Context& ctx;

	Parser(std::vector<Token*>::iterator first, std::vector<Token*>::iterator last, Context& ctx) : first(first), last(last), ctx(ctx) {}
	~Parser();
	bool eof();
	Kind look_ahead();
	Token* consume();
	Token* match(Kind k);
	Token* match_if(Kind k);
	Expr* factor();
	Expr* unary();
	Expr* term();
	Expr* math_expr();
	Expr* lt_gt_expr();
	Expr* equality_expr();
	Expr* and_or_expr();
	Expr* conditional_expr();
	Expr* parse_Expr();
};
#endif // !1

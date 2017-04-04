#include "stdafx.h"
#include "Parser.h"
#include <iostream>


Parser::~Parser()
{
}
bool Parser::eof() { 
	return first == last; 
}
Kind Parser::look_ahead() {
	Token* temp = *first;
	return temp->kind;
}
Token* Parser::consume() {
	if (!eof()) {
		Token* temp = *first;
		++first;
		return temp;
	}
	return *first;
}
Token* Parser::match(Kind k) {
	if (look_ahead() == k) {
		return consume();
	}
	else
		throw("Syntax error");
}
Token* Parser::match_if(Kind k) {
	if (look_ahead() == k)
		return consume();
	else
		return nullptr;
}
Expr* Parser::factor() {
	switch (look_ahead()) {
		case Bool: {
			Bool_token* temp = static_cast<Bool_token*>(consume());
			//std::cout << temp->value << " ";
			return new Bool_expr(temp->value);
		}
		case Int: {
			Int_token* temp = static_cast<Int_token*>(consume());
			//std::cout << temp->value << " ";
			return new Int_expr(temp->value);
		}
		case L_paren: {
			consume();
			Expr* e = conditional_expr();
			check(ctx, e);
			match(R_paren);
			return e;
		}
		default:
			return nullptr;
	}
}
Expr* Parser::unary() {
	if (match_if(Minus)) {
		Expr* e = unary();
		//std::cout << "before neg " << eval(e) << "\n";
		e = new Neg_expr(e);
		check(ctx, e);
		//std::cout << "after neg " << eval(e) << "\n";
		return e;
	}
    if (match_if(Excl)) {
		Expr* e = unary();
		e = new Not_expr(e);
		check(ctx, e);
		return e;
	}
	else
		return factor();
}

//term = term */% factor
Expr* Parser::term() {
	Expr* t1 = unary();
	check(ctx, t1);
	while (true) {
		if (match_if(Star)) {
			Expr* t2 = unary();
			check(ctx, t2);
			t1 = new Mult_expr(t1, t2);
			check(ctx, t1);
		}
		else if (match_if(F_slash)) {
			Expr* t2 = unary();
			check(ctx, t2);
			t1 = new Div_expr(t1, t2);
			check(ctx, t1);
		}
		else if (match_if(Percent)) {
			Expr* t2 = unary();
			check(ctx, t2);
			t1 = new Rem_expr(t1, t2);
			check(ctx, t1);
		}
		else
			break;
	}
	//std::cout << "out of term\n";
	return t1;
}

Expr* Parser::math_expr() {
	Expr* e1 = term();
	check(ctx, e1);
	while (true) {
		if (match_if(Plus)) {
			Expr* e2 = term();
			check(ctx, e2);
			e1 = new Add_expr(e1, e2);
			check(ctx, e1);
		}
		else if (match_if(Minus)) {
			Expr* e2 = term();
			check(ctx, e2);
			e1 = new Sub_expr(e1, e2);
			check(ctx, e1);
		}
		else
			break;
	}
	//std::cout << "out of math_expr\n";
	return e1;
}

Expr* Parser::lt_gt_expr() {
	Expr* e1 = math_expr();
	check(ctx, e1);
	while (true) {
		if (match_if(Less)) {
			Expr* e2 = math_expr();
			check(ctx, e2);
			e1 = new Less_expr(e1, e2);
			check(ctx, e1);
		}
		else if (match_if(Greater)) {
			Expr* e2 = math_expr();
			check(ctx, e2);
			e1 = new Greater_expr(e1, e2);
			check(ctx, e1);
		}
		else if (match_if(Less_Eq)) {
			Expr* e2 = math_expr();
			check(ctx, e2);
			e1 = new LessEq_expr(e1, e2);
			check(ctx, e1);
		}
		else if (match_if(Greater_Eq)) {
			Expr* e2 = math_expr();
			check(ctx, e2);
			e1 = new GreaterEq_expr(e1, e2);
			check(ctx, e1);
			//std::cout << "> ";
		}
		else
			break;
	}
	//std::cout << "out of ltGt_expr\n";
	return e1;
}
Expr* Parser::equality_expr() {
	Expr* e1 = lt_gt_expr();
	check(ctx, e1);
	while (true) {
		if (match_if(Equal)) {
			Expr* e2 = lt_gt_expr();
			check(ctx, e2);
			e1 = new Eq_expr(e1, e2);
			check(ctx, e1);
		}
		else if (match_if(Not_eq)) {
			Expr* e2 = lt_gt_expr();
			check(ctx, e2);
			e1 = new Noteq_expr(e1, e2);
			check(ctx, e1);
		}
		else
			break;
	}
	return e1;
}
Expr* Parser::and_or_expr() {
	Expr* e1 = equality_expr();
	check(ctx, e1);
	while (true) {
		if (match_if(Ampr)) {
			Expr* e2 = equality_expr();
			check(ctx, e2);
			e1 = new And_expr(e1, e2);
			check(ctx, e1);
		}
		else if (match_if(Vert_bar)) {
			Expr* e2 = equality_expr();
			check(ctx, e2);
			e1 = new Or_expr(e1, e2);
			check(ctx, e1);
		}
		else
			break;
	}
	return e1;
}
Expr* Parser::conditional_expr() {
	Expr* e1 = and_or_expr();
	check(ctx, e1);
	while (true) {
		if (match_if(Question)) {
			Expr* e2 = and_or_expr();
			check(ctx, e2);
			match(Colon);
			Expr* e3 = and_or_expr();
			check(ctx, e3);
			e1 = new Cond_expr(e1, e2, e3);
			check(ctx, e1);
		}
		else
			break;
	}
	return e1;
}
Expr* Parser::parse_Expr() {
	Expr* e = conditional_expr();
	std::cout  << eval(e) << "\n";
	return e;
}

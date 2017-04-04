#ifndef AST_HPP
#define AST_HPP

#include <cassert>

struct Bool_type;
struct Int_type;

struct Bool_expr;
struct And_expr;
struct Or_expr;
struct Not_expr;

struct Type {
	struct Visitor;
	virtual ~Type() = default;
	virtual void accept(Visitor&) { }
};

struct Bool_type : Type { };
struct Int_type : Type { };


struct Expr {
	struct Visitor;
	virtual ~Expr() = default;
	virtual void accept(Visitor&) = 0;
};

struct Expr::Visitor
{
	virtual void visit(Bool_expr*) = 0;
	virtual void visit(And_expr*) = 0;
	virtual void visit(Or_expr*) = 0;
	virtual void visit(Not_expr*) = 0;
};

struct Bool_expr : Expr {
	bool val;
	Bool_expr(bool b) : val(b) { }
	void accept(Visitor& v) { return v.visit(this); }
};

struct And_expr : Expr {
	Expr* e1;
	Expr* e2;
	And_expr(Expr* e1, Expr* e2) : e1(e1), e2(e2) { }
	void accept(Visitor& v) { return v.visit(this); }
};

struct Or_expr : Expr {
	Expr* e1;
	Expr* e2;
	Or_expr(Expr* e1, Expr* e2) : e1(e1), e2(e2) { }
	void accept(Visitor& v) { return v.visit(this); }
};

struct Not_expr : Expr {
	Expr* e1;
	Not_expr(Expr* e1) : e1(e1) { }
	void accept(Visitor& v) { return v.visit(this); }
};


struct Context
{
	Bool_type bool_type;
	Int_type int_type;
};


#endif


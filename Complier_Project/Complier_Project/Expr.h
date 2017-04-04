/*Expr class hierarchy
Expr is the base class that all expressions are derived from
all expressions: bool, and, or, xor, not, int, cond, ==, !=, >, <, >=, <=, +, -, *, /, %, neg
accept accepts a visitor of the most dreived class and returns teh value
*/
#ifndef EXPR_HPP
#define EXPR_HPP

#include <cassert>

struct Bool_type;
struct Int_type;

struct Bool_expr;
struct And_expr;
struct Or_expr;
struct Not_expr;
struct Xor_expr;
struct Int_expr;
struct Cond_expr;
struct Eq_expr;
struct Noteq_expr;
struct Greater_expr;
struct Less_expr;
struct GreaterEq_expr;
struct LessEq_expr;
struct Add_expr;
struct Sub_expr;
struct Mult_expr;
struct Div_expr;
struct Rem_expr;
struct Neg_expr;
struct AndThen_expr;
struct OrElse_expr;

//base class
struct Expr {
	struct Visitor;
	virtual ~Expr() = default;
	virtual void accept(Visitor&) = 0;
};
//visitor for Expr to keep the classes small
struct Expr::Visitor
{
	virtual void visit(Bool_expr*) = 0;
	virtual void visit(And_expr*) = 0;
	virtual void visit(Or_expr*) = 0;
	virtual void visit(Not_expr*) = 0;
	virtual void visit(Xor_expr*) = 0;
	virtual void visit(Int_expr*) = 0;
	virtual void visit(Cond_expr*) = 0;
	virtual void visit(Eq_expr*) = 0;
	virtual void visit(Noteq_expr*) = 0;
	virtual void visit(Greater_expr*) = 0;
	virtual void visit(Less_expr*) = 0;
	virtual void visit(GreaterEq_expr*) = 0;
	virtual void visit(LessEq_expr*) = 0;
	virtual void visit(Add_expr*) = 0;
	virtual void visit(Sub_expr*) = 0;
	virtual void visit(Mult_expr*) = 0;
	virtual void visit(Div_expr*) = 0;
	virtual void visit(Rem_expr*) = 0;
	virtual void visit(Neg_expr*) = 0;
	virtual void visit(AndThen_expr*) = 0;
	virtual void visit(OrElse_expr*) = 0;
};
//derived classes
//bool expr holds a boolean values: true or false
struct Bool_expr : Expr {
	bool value;
	Bool_expr(bool b) : value(b) { }
	void accept(Visitor& v) { return v.visit(this); }
};
//and expr is the logical and
//e1, e2 must be bools
struct And_expr : Expr {
	Expr* e1;
	Expr* e2;
	And_expr(Expr* e1, Expr* e2) : e1(e1), e2(e2) { }
	void accept(Visitor& v) { return v.visit(this); }
};
//or exper is inclusive or
//e1, e2 must be bools
struct Or_expr : Expr {
	Expr* e1;
	Expr* e2;
	Or_expr(Expr* e1, Expr* e2) : e1(e1), e2(e2) { }
	void accept(Visitor& v) { return v.visit(this); }
};
//xor is exclusive or
//e1, e2 must be bools
struct Xor_expr : Expr{
	Expr* e1;
	Expr* e2;
	Xor_expr(Expr* e1, Expr* e2) : e1(e1), e2(e2) { }
	void accept(Visitor& v) { return v.visit(this); }

};
//not expr is logical negation
//e must be bools
struct Not_expr : Expr {
	Expr* e;
	Not_expr(Expr* e) : e(e) { }
	void accept(Visitor& v) { return v.visit(this); }
};
//int exper holds an integer INT_MIN to INT_MAX
struct Int_expr : Expr{
	int value;
	Int_expr(int x) : value(x) { }
	void accept(Visitor& v) { return v.visit(this); }
};
//conditional expression if e1 then e2 else e3
//e1, e2, e3 must be bools
struct Cond_expr : Expr{
	Expr* e1;
	Expr* e2;
	Expr* e3;
	Cond_expr(Expr* e1, Expr* e2, Expr* e3) : e1(e1), e2(e2), e3(e3) { }
	void accept(Visitor& v) { return v.visit(this); }

};
//equal expression true if e1 == e2
//e1 and e2 must have same type
struct Eq_expr : Expr {
	Expr* e1;
	Expr* e2;
	Eq_expr(Expr* e1, Expr* e2) : e1(e1), e2(e2) {}
	void accept(Visitor& v) { return v.visit(this); }

};
//not equal expression true if e1 != e2
//e1 and e2 must have same type
struct Noteq_expr : Expr {
	Expr* e1;
	Expr* e2;
	Noteq_expr(Expr* e1, Expr* e2) : e1(e1), e2(e2) {}
	void accept(Visitor& v) { return v.visit(this); }

};
//greater than expression true if e1 > e2
//e1 and e2 must be ints
struct Greater_expr : Expr {
	Expr* e1;
	Expr* e2;
	Greater_expr(Expr* e1, Expr* e2) : e1(e1), e2(e2) {}
	void accept(Visitor& v) { return v.visit(this); }
};
//less than expression true if e1 < e2
//e1 and e2 must be ints
struct Less_expr : Expr {
	Expr* e1;
	Expr* e2;
	Less_expr(Expr* e1, Expr* e2) : e1(e1), e2(e2) {}
	void accept(Visitor& v) { return v.visit(this); }
};
//greater than expression true if e1 >= e2
//e1 and e2 must be ints
struct GreaterEq_expr : Expr {
	Expr* e1;
	Expr* e2;
	GreaterEq_expr(Expr* e1, Expr* e2) : e1(e1), e2(e2) {}
	void accept(Visitor& v) { return v.visit(this); }
};
//greater than expression true if e1 <= e2
//e1 and e2 must be ints
struct LessEq_expr : Expr {
	Expr* e1;
	Expr* e2;
	LessEq_expr(Expr* e1, Expr* e2) : e1(e1), e2(e2) {}
	void accept(Visitor& v) { return v.visit(this); }
};
//add expression returns e1 + e2
//e1 and e2 must be ints
struct Add_expr : Expr {
	Expr* e1;
	Expr* e2;
	Add_expr(Expr* e1, Expr* e2) : e1(e1), e2(e2) {}
	void accept(Visitor& v) { return v.visit(this); }
};
//add expression returns e1 - e2
//e1 and e2 must be ints
struct Sub_expr : Expr {
	Expr* e1;
	Expr* e2;
	Sub_expr(Expr* e1, Expr* e2) : e1(e1), e2(e2) {}
	void accept(Visitor& v) { return v.visit(this); }
};
//add expression returns e1 * e2
//e1 and e2 must be ints
struct Mult_expr : Expr {
	Expr* e1;
	Expr* e2;
	Mult_expr(Expr* e1, Expr* e2) : e1(e1), e2(e2) {}
	void accept(Visitor& v) { return v.visit(this); }
};
//add expression returns e1 / e2
//e1 and e2 must be ints
struct Div_expr : Expr {
	Expr* e1;
	Expr* e2;
	Div_expr(Expr* e1, Expr* e2) : e1(e1), e2(e2) {}
	void accept(Visitor& v) { return v.visit(this); }
};
//add expression returns e1 % e2
//e1 and e2 must be ints
struct Rem_expr : Expr {
	Expr* e1;
	Expr* e2;
	Rem_expr(Expr* e1, Expr* e2) : e1(e1), e2(e2) {}
	void accept(Visitor& v) { return v.visit(this); }
};
//add expression returns arithmetic negation of e
//e must be int
struct Neg_expr : Expr{
	Expr* e;
	Neg_expr(Expr* e) : e(e) {}
	void accept(Visitor& v) { return v.visit(this); }
};
//andThen expression returns e2 if e1 is true
//otherwise returns false
//e1, e2 must be bools
struct AndThen_expr : Expr{
	Expr* e1;
	Expr* e2;
	AndThen_expr(Expr* e1, Expr* e2) : e1(e1), e2(e2) {}
	void accept(Visitor& v) { return v.visit(this); }
};

struct OrElse_expr : Expr {
	Expr* e1;
	Expr* e2;
	OrElse_expr(Expr* e1, Expr* e2) : e1(e1), e2(e2) {}
	void accept(Visitor& v) { return v.visit(this); }
};
#endif



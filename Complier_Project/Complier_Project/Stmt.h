#pragma once
#include "Expr.h"
struct Stmt{
	Stmt();
	virtual ~Stmt() = default;
};
struct Expr_Stmt : Stmt{
	Expr* e;
	Expr_Stmt(Expr* e) : e(e) {}

};


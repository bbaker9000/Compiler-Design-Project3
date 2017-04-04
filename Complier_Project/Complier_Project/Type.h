#ifndef TYPE_HPP
#define TYPE_HPP
#include "Expr.h"
#include <typeinfo>
//type class hierarchy
//type is teh base and has two dereived classes: Bool_type and Int_type
//accpet returns true if the expression is well typed 
//throws and exception if not well typed 
struct Type
{
	struct Visitor;
	virtual ~Type() = default;
	virtual void accept(Visitor&) = 0;
};
struct Type::Visitor
{
	virtual void visit(Bool_type*) = 0;
	virtual void visit(Int_type*) = 0;
};
struct Bool_type : Type
{
	void accept(Visitor& v) { return v.visit(this); };
};
struct Int_type : Type
{
	void accept(Visitor& v) { return v.visit(this); };
};
struct Context 
{
	Int_type Int_typ;
	Bool_type Bool_typ;

};
Type* check(Context& cxt, Expr* e);

#endif
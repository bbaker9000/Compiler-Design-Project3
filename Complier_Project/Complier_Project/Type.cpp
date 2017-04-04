#include "stdafx.h"
#include "Type.h"
//check function checks if the expression is well typed
//if it is not it throws an exception and doesn't create
//the expression
Type* check(Context& cxt, Expr* e)

{
	struct V : Expr::Visitor {
		Context& cxt;
		Type* r;
		V(Context& c) : cxt(c) {}
		void visit(Bool_expr* e) {
			r = &cxt.Bool_typ;
		}
		void visit(And_expr* e)
		{
			if (check(cxt, e->e1) == &cxt.Bool_typ)
			{
				if (check(cxt, e->e2) == &cxt.Bool_typ)
					r = &cxt.Bool_typ;
				else
					throw("Typing error in and e2 is not bool");
			}
			else
				throw("Typing error in condition e1 is not bool");
		}
		void visit(Or_expr* e)
		{
			if (check(cxt, e->e1) == &cxt.Bool_typ)
			{
				if (check(cxt, e->e2) == &cxt.Bool_typ)
					r = &cxt.Bool_typ;
				else
					throw("Typing error in or e2 is not bool");
			}
			else
				throw("Typing error in or e1 is not bool");
		}

		void visit(Not_expr* e)
		{
			if (check(cxt, e->e) == &cxt.Bool_typ)
				r = &cxt.Bool_typ;
			else
				throw("Typing error in not e is not bool");
		}
		void visit(Xor_expr* e)
		{
			if (check(cxt, e->e1) == &cxt.Bool_typ)
			{
				if (check(cxt, e->e2) == &cxt.Bool_typ)
					r = &cxt.Bool_typ;
				else
					throw("Typing error in xor e2 is not bool");
			}
			else
				throw("Typing error in xor e1 is not bool");

		}
		void visit(Int_expr* e)
		{
			r = &cxt.Int_typ;

		}
		void visit(Cond_expr* e)
		{
			if (check(cxt, e->e1) == &cxt.Bool_typ)
			{
				if (check(cxt, e->e2) == &cxt.Bool_typ)
				{
					if (check(cxt, e->e3) == &cxt.Bool_typ)
						r = &cxt.Bool_typ;
					else
						throw("Typing error in condition e3 is not bool");
				}
				else
					throw("Typing error in condition e2 is not bool");
			}
			else
				throw("Typing error in condition e1 is not bool");
		}
		void visit(Eq_expr* e)
		{
			if (check(cxt, e->e1) == check(cxt, e->e2))
				r = &cxt.Bool_typ;
			else
				throw("Typing error in equality. The expressions must be same type");
		}
		void visit(Noteq_expr* e)
		{
			if (check(cxt, e->e1) == check(cxt, e->e2))
				r = &cxt.Bool_typ;
			else
				throw("Typing error in equality. The expressions must be same type");
		}
		void visit(Greater_expr* e)
		{
			if (check(cxt, e->e1) == &cxt.Int_typ)
			{
				if (check(cxt, e->e2) == &cxt.Int_typ)
					r = &cxt.Bool_typ;
				else
					throw("Typing error in greater than, e2 must be int");
			}
			else
				throw("Typing error in greater than, e1 must be int");
		}
		void visit(Less_expr* e)
		{
			if (check(cxt, e->e1) == &cxt.Int_typ)
			{
				if (check(cxt, e->e2) == &cxt.Int_typ)
					r = &cxt.Bool_typ;
				else
					throw("Typing error in less than, e2 must be int");
			}
			else
				throw("Typing error in less than, e1 must be int");
		}
		void visit(GreaterEq_expr* e)
		{
			if (check(cxt, e->e1) == &cxt.Int_typ)
			{
				if (check(cxt, e->e2) == &cxt.Int_typ)
					r = &cxt.Bool_typ;
				else
					throw("Typing error in greater than, e2 must be int");
			}
			else
				throw("Typing error in greater than, e1 must be int");
		}
		void visit(LessEq_expr* e)
		{
			if (check(cxt, e->e1) == &cxt.Int_typ)
			{
				if (check(cxt, e->e2) == &cxt.Int_typ)
					r = &cxt.Bool_typ;
				else
					throw("Typing error in less than, e2 must be int");
			}
			else
				throw("Typing error in less than, e1 must be int");
		}
		void visit(Add_expr* e)
		{
			if (check(cxt, e->e1) == &cxt.Int_typ)
			{
				if (check(cxt, e->e2) == &cxt.Int_typ)
					r = &cxt.Int_typ;
				else
					throw("Typing error in less than, e2 must be int");
			}
			else
				throw("Typing error in less than, e1 must be int");
		}
		void visit(Sub_expr* e)
		{
			if (check(cxt, e->e1) == &cxt.Int_typ)
			{
				if (check(cxt, e->e2) == &cxt.Int_typ)
					r = &cxt.Int_typ;
				else
					throw("Typing error in less than, e2 must be int");
			}
			else
				throw("Typing error in less than, e1 must be int");
		}
		void visit(Mult_expr* e)
		{
			if (check(cxt, e->e1) == &cxt.Int_typ)
			{
				if (check(cxt, e->e2) == &cxt.Int_typ)
					r = &cxt.Int_typ;
				else
					throw("Typing error in less than, e2 must be int");
			}
			else
				throw("Typing error in less than, e1 must be int");
		}
		void visit(Div_expr* e)
		{
			if (check(cxt, e->e1) == &cxt.Int_typ)
			{
				if (check(cxt, e->e2) == &cxt.Int_typ)
					r = &cxt.Int_typ;
				else
					throw("Typing error in less than, e2 must be int");
			}
			else
				throw("Typing error in less than, e1 must be int");
		}
		void visit(Rem_expr* e)
		{
			if (check(cxt, e->e1) == &cxt.Int_typ)
			{
				if (check(cxt, e->e2) == &cxt.Int_typ)
					r = &cxt.Int_typ;
				else
					throw("Typing error in less than, e2 must be int");
			}
			else
				throw("Typing error in less than, e1 must be int");
		}
		void visit(Neg_expr* e)
		{
			if (check(cxt, e->e) == &cxt.Int_typ)
				r = &cxt.Int_typ;
			else
				throw("Typing error in negation, e must be int");
		}
		void visit(AndThen_expr* e)
		{
			if (check(cxt, e->e1) == &cxt.Bool_typ)
			{
				if (check(cxt, e->e2) == &cxt.Bool_typ)
					r = &cxt.Bool_typ;
				else
					throw("Typing error in AndThen e2 is not bool");
			}
			else
				throw("Typing error in AndThen e1 is not bool");

		}
		void visit(OrElse_expr* e)
		{
			if (check(cxt, e->e1) == &cxt.Bool_typ)
			{
				if (check(cxt, e->e2) == &cxt.Bool_typ)
					r = &cxt.Bool_typ;
				else
					throw("Typing error in OrElse e2 is not bool");
			}
			else
				throw("Typing error in OrElse e1 is not bool");

		}

	};
	V vis(cxt);
	e->accept(vis);
	return vis.r;
}

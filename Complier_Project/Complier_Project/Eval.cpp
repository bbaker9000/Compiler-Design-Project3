#include "stdafx.h"
#include "Eval.h"
int eval(Expr* e)
{
	struct V : Expr::Visitor
	{
		int r;
		//overloads of visit
		void visit(Bool_expr* e) { r = e->value; }
		void visit(And_expr* e) { r = eval(e->e1) & eval(e->e2); }
		void visit(Or_expr* e) { r = eval(e->e1) | eval(e->e2); }
		void visit(Not_expr* e) { r = !eval(e->e); }
		void visit(Xor_expr* e) { r = !(eval(e->e1) == eval(e->e2)); }
		void visit(Int_expr* e) { r = e->value; }
		void visit(Cond_expr* e) { if (eval(e->e1)) r = eval(e->e2); else r = eval(e->e3); }
		void visit(Eq_expr* e) { r = eval(e->e1) == eval(e->e2); }
		void visit(Noteq_expr* e) { r = eval(e->e1) != eval(e->e2); }
		void visit(Greater_expr* e) { r = eval(e->e1) > eval(e->e2); }
		void visit(Less_expr* e) { r = eval(e->e1) < eval(e->e2); }
		void visit(GreaterEq_expr* e) { r = eval(e->e1) >= eval(e->e2); }
		void visit(LessEq_expr* e) { r = eval(e->e1) <= eval(e->e2); }
		void visit(Add_expr* e) {
			if (eval(e->e2) > 0 && eval(e->e1) > INT_MAX - eval(e->e2))
				throw("Overflow error in evaluation of addition. Max value is 2147483647");
			else if (eval(e->e2) < 0 && eval(e->e1) < INT_MIN - eval(e->e2))
				throw("Underflow error in evaluation of addition. Min value is –2147483648");
			else
				r = eval(e->e1) + eval(e->e2);
		}
		void visit(Sub_expr* e) {
			if (eval(e->e2) < 0 && eval(e->e1) > INT_MAX + eval(e->e2))
				throw("Overflow error in evaluation of subtraction. Max value is 2147483647");
			else if (eval(e->e2) > 0 && eval(e->e1) < INT_MIN + eval(e->e2))
				throw("Underflow error in evaluation of subtraction. Min value is –2147483648");
			else
				r = eval(e->e1) - eval(e->e2);
		}
		//in the visit overloads for arithmetic operations it throws and excpetion
		//if the value overflows/underflows
		void visit(Mult_expr* e) {/*
								  if (eval(e->e1) > INT_MAX / eval(e->e2))
								  throw("Overflow error in evaluation of multiplication. Max value is 2147483647");
								  else if (eval(e->e1) < INT_MIN / eval(e->e2))
								  throw("Underflow error in evaluation of multiplication. Min value is -2147483648");
								  else if (eval(e->e1) == -1 && eval(e->e2) == INT_MIN)
								  throw("Overflow error in evaluation of multiplication. Max value is 2147483647");
								  else if (eval(e->e2) == -1 && eval(e->e1) == INT_MIN)
								  throw("Overflow error in evaluation of multiplication. Max value is 2147483647");
								  else*/
			r = eval(e->e1) * eval(e->e2);
		}
		void visit(Div_expr* e) {
			if (eval(e->e2) == 0)
				throw("Error in evaluation of division. Cannot divide by zero");
			else if (eval(e->e1) == INT_MIN && eval(e->e2) == -1)
				throw("Underflow error in evaluation of division. Min value is -2147483648");
			else
				r = eval(e->e1) / eval(e->e2);
		}
		void visit(Rem_expr* e) {
			if (eval(e->e2) == 0)
				throw("Error in evaluation of remainder division. Cannot divide by zero");
			else if (eval(e->e1) == INT_MIN && eval(e->e2) == -1)
				throw("Underflow error in evaluation of remainder division. Min value is -2147483648");
			else
				r = eval(e->e1) % eval(e->e2);
		}
		void visit(Neg_expr* e)
		{
			if (eval(e->e) == INT_MIN)
				throw("Overflow error in evaluation of negation. Max value is 2147483647");
			else
				r = eval(e->e) * -1;
		}
		void visit(AndThen_expr* e) {
			if (eval(e->e1))
				r = eval(e->e2);
			else
				r = false;
		}
		void visit(OrElse_expr* e) {
			if (eval(e->e1))
				r = eval(e->e2);
			else
				r = eval(e->e2);
		}
	};
	V vis;
	e->accept(vis);
	return vis.r;
}
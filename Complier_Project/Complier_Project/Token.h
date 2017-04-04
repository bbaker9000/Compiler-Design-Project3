#pragma once
enum Kind {EoF, L_paren, R_paren, Ampr, Vert_bar, Excl, Bool, Int, Plus, Minus, Star, F_slash, B_slash, Percent, Less, Greater, Less_Eq, Greater_Eq, Equal, Question, Colon, Not_eq};

struct Punc_token;
struct Bool_token;
struct Int_token;

struct Token {
	virtual ~Token() = default;
	Token(Kind kind) : kind(kind) {}
	Kind kind;
	struct Visitor;
	virtual void accept(Visitor&) = 0;
};

struct Token::Visitor {
	virtual void visit(Punc_token* t) = 0;
	virtual void visit(Bool_token* t) = 0;
	virtual void visit(Int_token* t) = 0;

};

struct Punc_token : Token {
	Punc_token(Kind kind) : Token(kind) {}
	void accept(Visitor& v) { return v.visit(this); }
};

struct Bool_token : Token {
	bool value;
	Bool_token(Kind kind, bool value) : Token(kind), value(value) {}
	void accept(Visitor& v) { return v.visit(this); }
};

struct Int_token : Token {
	int value;
	Int_token(Kind kind, int value) : Token(kind), value(value) {}
	void accept(Visitor& v) { return v.visit(this); }
};
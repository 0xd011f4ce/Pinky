#ifndef __TOKEN_H
#define __TOKEN_H

#include <utils/buffer.h>

enum token_type
{
	// ********************************
	// single char tokens
	// ********************************
	TOK_LPAREN,		 // (
	TOK_RPAREN,		 // )
	TOK_LCURLY,		 // {
	TOK_RCURLY,		 // }
	TOK_LSQUAR,		 // [
	TOK_RSQUAR,		 // ]
	TOK_COMMA,		 // ,
	TOK_DOT,			 // .
	TOK_PLUS,			 // +
	TOK_MINUS,		 // -
	TOK_STAR,			 // *
	TOK_SLASH,		 // /
	TOK_CARET,		 // ^
	TOK_MOD,			 // %
	TOK_SEMICOLON, // ;
	TOK_QUESTION,	 // ?
	TOK_NOT,			 // ~
	TOK_GT,				 // >
	TOK_LT,				 // <

	// ********************************
	// two-char tokens
	// ********************************
	TOK_GE,			// >=
	TOK_LE,			// <=
	TOK_NE,			// ~=
	TOK_EQ,			// ==
	TOK_ASSIGN, // :=
	TOK_GTGT,		// >>
	TOK_LTLT,		// <<

	// ********************************
	// literals
	// ********************************
	TOK_IDENTIFIER,
	TOK_STRING,
	TOK_INTEGER,
	TOK_FLOAT,

	// ********************************
	// keywords
	// ********************************
	TOK_IF,
	TOK_THEN,
	TOK_ELSE,
	TOK_TRUE,
	TOK_FALSE,
	TOK_AND,
	TOK_OR,
	TOK_WHILE,
	TOK_DO,
	TOK_FOR,
	TOK_FUNC,
	TOK_NULL,
	TOK_END,
	TOK_PRINT,
	TOK_PRINTLN,
	TOK_RET
};

struct token
{
	enum token_type type;
	unsigned int line;
	struct buffer lexeme;
};

struct token *token_create (enum token_type type, const char *lexeme);
void token_print (struct token *t);
void token_free (struct token *t);

#endif

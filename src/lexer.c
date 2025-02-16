#include <lexer.h>

#include <token.h>

#include <stdio.h>

static void
add_token (enum token_type type, const char *lexeme, struct lexer *l)
{
	if (!l)
		return;

	vector_push (token_create (type, lexeme), &l->tokens);
}

void
lexer_init (const char *source, struct lexer *l)
{
	if (!l)
		return;

	vector_init (&l->tokens);
	buffer_init (&l->source);
	buffer_push (source, &l->source);

	l->line = 1;
}

void
lexer_tokenise (struct lexer *l)
{
	// TODO: This
	if (!l)
		return;

	char c = buffer_pop (&l->source);
	do
		{
			if (c == '+')
				add_token (TOK_PLUS, "+", l);

			if (c == '-')
				add_token (TOK_MINUS, "-", l);

			if (c == '*')
				add_token (TOK_STAR, "*", l);

			c = buffer_pop (&l->source);
		}
	while (c != '\0');
}

void
lexer_free (struct lexer *l)
{
	if (!l)
		return;

	for (int i = 0; i < l->tokens.size; i++)
		{
			struct token *t = vector_get (i, &l->tokens);
			token_free (t);
		}

	vector_free (&l->tokens);
	buffer_free (&l->source);
}

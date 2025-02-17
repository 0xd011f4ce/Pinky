#include <token.h>

#include <stdio.h>
#include <stdlib.h>

struct token *
token_create (enum token_type type, const char *lexeme)
{
	struct token *t = malloc (sizeof (struct token));
	t->type = type;
	t->line = 1;
	buffer_init (&t->lexeme);
	buffer_push (lexeme, &t->lexeme);
	return t;
}

void
token_print (struct token *t)
{
	if (!t)
		return;

	printf ("(TOK_TYPE: %d, LEXEME: %s, LINE: %d)\n", t->type,
					buffer_content (&t->lexeme), t->line);
}

void
token_free (struct token *t)
{
	if (!t)
		return;

	buffer_free (&t->lexeme);
	free (t);
}

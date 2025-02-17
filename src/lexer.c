#include <lexer.h>

#include <token.h>

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

static void
add_token (enum token_type type, struct lexer *l)
{
	if (!l)
		return;

	char *slice = buffer_slice (&l->source);
	struct token *tok = token_create (type, slice);
	free (slice);

	tok->line = l->line;
	vector_push (tok, &l->tokens);
}

static void
tokeniser_error (const char *err, struct lexer *l)
{
	fprintf (stderr, "[TOKENISER_ERROR: Line %d]: %s\n", l->line, err);
	abort ();
}

/* ================================ */
/* tokeniser functions */
/* ================================ */
void
handle_number (struct lexer *l)
{
	while (isdigit (buffer_peek (&l->source)))
		buffer_advance (&l->source);

	if (buffer_peek (&l->source) == '.'
			&& isdigit (buffer_lookahead (1, &l->source)))
		{
			buffer_advance (&l->source); // consume the '.'
			while (isdigit (buffer_peek (&l->source)))
				buffer_advance (&l->source);

			add_token (TOK_FLOAT, l);
		}
	else
		add_token (TOK_INTEGER, l);
}

void
handle_string (char quote, struct lexer *l)
{
	while (buffer_peek (&l->source) != quote)
		{
			buffer_advance (&l->source);

			if (buffer_peek (&l->source) == -1)
				tokeniser_error ("Unterminated string", l);
		}
	buffer_advance (&l->source); // consume the ending quote
	add_token (TOK_STRING, l);
}

void
handle_identifier (struct lexer *l)
{
	while (isalnum (buffer_peek (&l->source)) || buffer_peek (&l->source) == '_')
		buffer_advance (&l->source);
	add_token (TOK_IDENTIFIER, l);
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

	char c = 0;
	while (*buffer_curr (&l->source) != '\0')
		{
			l->source.start = buffer_curr (&l->source);
			c = buffer_advance (&l->source);

			if (c == '\n')
				{
					l->line++;
					continue;
				}
			else if (c == ' ' || c == '\t' || c == '\r')
				continue;
			else if (c == '#')
				{
					// let's assume single line comments start with #
					while (buffer_peek (&l->source) != '\n'
								 && buffer_in_bounds (&l->source))
						buffer_advance (&l->source);
				}

			/* single line comments */
			if (c == '+')
				add_token (TOK_PLUS, l);
			else if (c == '-')
				add_token (TOK_MINUS, l);
			else if (c == '*')
				add_token (TOK_STAR, l);
			else if (c == '(')
				add_token (TOK_LPAREN, l);
			else if (c == ')')
				add_token (TOK_RPAREN, l);
			else if (c == '{')
				add_token (TOK_LCURLY, l);
			else if (c == '}')
				add_token (TOK_RCURLY, l);
			else if (c == '[')
				add_token (TOK_LSQUAR, l);
			else if (c == ']')
				add_token (TOK_RSQUAR, l);
			else if (c == '.')
				add_token (TOK_DOT, l);
			else if (c == ',')
				add_token (TOK_COMMA, l);
			else if (c == '^')
				add_token (TOK_CARET, l);
			else if (c == '/')
				add_token (TOK_SLASH, l);
			else if (c == ';')
				add_token (TOK_SEMICOLON, l);
			else if (c == '?')
				add_token (TOK_QUESTION, l);
			else if (c == '%')
				add_token (TOK_MOD, l);
			/* more-than-one character tokens */
			else if (c == '=')
				{
					if (buffer_match ('=', &l->source))
						add_token (TOK_EQ, l);
				}
			else if (c == '~')
				{
					if (buffer_match ('=', &l->source))
						add_token (TOK_NE, l);
					else
						add_token (TOK_NOT, l);
				}
			else if (c == '<')
				{
					if (buffer_match ('=', &l->source))
						add_token (TOK_LE, l);
					else
						add_token (TOK_LT, l);
				}
			else if (c == '>')
				{
					if (buffer_match ('=', &l->source))
						add_token (TOK_GE, l);
					else
						add_token (TOK_GT, l);
				}
			else if (c == ':')
				{
					if (buffer_match ('=', &l->source))
						add_token (TOK_ASSIGN, l);
				}
			else if (isdigit (c))
				{
					handle_number (l);
				}
			else if (c == '\'' || c == '"')
				{
					handle_string (c, l);
				}
			else if (c == '_' || isalpha (c))
				{
					handle_identifier (l);
				}
			/* TODO: Check if it's "" or '' to read a string*/
			/* TODO: Check if it's an alpha or _, then handle identifiers */
		}
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

#include <lexer.h>

#include <token.h>

#include <stdio.h>

static void
add_token (enum token_type type, const char *lexeme, struct lexer *l)
{
	if (!l)
		return;

	struct token *tok = token_create (type, lexeme);
	tok->line = l->line;
	vector_push (tok, &l->tokens);
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
					while (buffer_peek (&l->source) != '\n')
						buffer_advance (&l->source);
				}

			/* single line comments */
			if (c == '+')
				add_token (TOK_PLUS, "+", l);
			else if (c == '-')
				add_token (TOK_MINUS, "-", l);
			else if (c == '*')
				add_token (TOK_STAR, "*", l);
			else if (c == '(')
				add_token (TOK_LPAREN, "(", l);
			else if (c == ')')
				add_token (TOK_RPAREN, ")", l);
			else if (c == '{')
				add_token (TOK_LCURLY, "{", l);
			else if (c == '}')
				add_token (TOK_RCURLY, "}", l);
			else if (c == '[')
				add_token (TOK_LSQUAR, "[", l);
			else if (c == ']')
				add_token (TOK_RSQUAR, "]", l);
			else if (c == '.')
				add_token (TOK_DOT, ".", l);
			else if (c == ',')
				add_token (TOK_COMMA, ",", l);
			else if (c == '^')
				add_token (TOK_CARET, "^", l);
			else if (c == '/')
				add_token (TOK_SLASH, "/", l);
			else if (c == ';')
				add_token (TOK_SEMICOLON, ";", l);
			else if (c == '?')
				add_token (TOK_QUESTION, "?", l);
			else if (c == '%')
				add_token (TOK_MOD, "%", l);
			/* more-than-one character tokens */
			else if (c == '=')
				{
					if (buffer_match ('=', &l->source))
						add_token (TOK_EQ, "==", l);
				}
			else if (c == '~')
				{
					if (buffer_match ('=', &l->source))
						add_token (TOK_NE, "~=", l);
					else
						add_token (TOK_NOT, "~", l);
				}
			else if (c == '<')
				{
					if (buffer_match ('=', &l->source))
						add_token (TOK_LE, "<=", l);
					else
						add_token (TOK_LT, "<", l);
				}
			else if (c == '>')
				{
					if (buffer_match ('=', &l->source))
						add_token (TOK_GE, ">=", l);
					else
						add_token (TOK_GT, ">", l);
				}
			else if (c == ':')
				{
					if (buffer_match ('=', &l->source))
						add_token (TOK_ASSIGN, ":=", l);
				}
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

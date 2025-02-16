#ifndef __LEXER_H
#define __LEXER_H

#include <utils/buffer.h>
#include <utils/vector.h>

struct lexer
{
	struct vector tokens;
	struct buffer source;

	unsigned int line;
};

void lexer_init (const char *source, struct lexer *l);
void lexer_tokenise (struct lexer *l);
void lexer_free (struct lexer *l);

#endif

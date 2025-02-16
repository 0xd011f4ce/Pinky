#ifndef __BUFFER_H
#define __BUFFER_H

#include <stddef.h>

struct buffer
{
	char *content;
	char *start;
	char *end;
	char *pp; // position pointer

	size_t length;
	size_t capacity;
};

void buffer_init (struct buffer *b);
void buffer_push (const char *str, struct buffer *b);
void buffer_seek (int offset, char type, struct buffer *b);
char buffer_peek (struct buffer *b);
char buffer_pop (struct buffer *b);
char *buffer_get (struct buffer *b);
char *buffer_get_at_position (struct buffer *b);
void buffer_free (struct buffer *b);

#endif

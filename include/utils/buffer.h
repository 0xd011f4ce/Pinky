#ifndef __BUFFER_H
#define __BUFFER_H

#include <stddef.h>

struct buffer
{
	char *content;
	char *start;
	char *curr;

	size_t length;
	size_t capacity;
};

void buffer_init (struct buffer *b);
void buffer_push (const char *str, struct buffer *b);

char buffer_advance (struct buffer *b);
char buffer_peek (struct buffer *b);
char buffer_lookahead (int n, struct buffer *b);
_Bool buffer_match (char c, struct buffer *b);

char *buffer_content (struct buffer *b);

size_t buffer_slice_len (struct buffer *b);
char *buffer_slice (struct buffer *b);

char *buffer_start (struct buffer *b);
char *buffer_curr (struct buffer *b);
_Bool buffer_in_bounds (struct buffer *b);

void buffer_free (struct buffer *b);

#endif

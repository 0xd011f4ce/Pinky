#include <utils/buffer.h>

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void
buffer_resize (size_t len, struct buffer *b)
{
	if (!b)
		return;

	unsigned long curr_offset = b->curr - b->content;
	unsigned long start_offset = b->start - b->content;
	b->capacity += len;
	b->content = realloc (b->content, sizeof (char) * b->capacity);
	if (!b->content)
		return;

	b->curr = b->content + curr_offset;
	b->start = b->content + start_offset;
}

void
buffer_init (struct buffer *b)
{
	if (!b)
		return;

	memset (b, 0, sizeof (struct buffer));
	b->capacity = 10;
	b->content = calloc (1, sizeof (char) * b->capacity);
	if (!b->content)
		return;

	b->start = b->content;
	b->curr = b->content;
}

void
buffer_push (const char *str, struct buffer *b)
{
	if (!b || !b->content || !str)
		return;

	size_t len = strlen (str);
	if ((b->length + len) >= b->capacity)
		buffer_resize (len, b);

	char *start = b->content + b->length;
	strncpy (start, str, len);
	b->length += len;
}

char
buffer_advance (struct buffer *b)
{
	if (!b || !buffer_in_bounds (b))
		return 0;
	return *b->curr++;
}

char
buffer_peek (struct buffer *b)
{
	if (!b || !buffer_in_bounds (b))
		return 0;

	return *b->curr;
}

char
buffer_lookahead (int n, struct buffer *b)
{
	if (!b || !buffer_in_bounds (b))
		return 0;
	return *(b->curr + n);
}

_Bool
buffer_match (char c, struct buffer *b)
{
	if (!b || !buffer_in_bounds (b) || *b->curr != c)
		return 0;
	b->curr++;
	return 1;
}

char *
buffer_content (struct buffer *b)
{
	if (!b)
		return NULL;

	return b->content;
}

char *
buffer_start (struct buffer *b)
{
	if (!b)
		return NULL;
	return b->start;
}

char *
buffer_curr (struct buffer *b)
{
	if (!b)
		return NULL;
	return b->curr;
}

_Bool
buffer_in_bounds (struct buffer *b)
{
	if (!b)
		return 0;
	return b->curr <= b->content + b->length;
}

void
buffer_free (struct buffer *b)
{
	if (!b)
		return;

	free (b->content);
	memset (b, 0, sizeof (struct buffer));
}

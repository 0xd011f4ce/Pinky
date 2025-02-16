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

	b->capacity += len + 1;
	size_t offset = b->pp - b->start;
	b->content = realloc (b->content, sizeof (char) * b->capacity);
	assert (b->content);

	b->start = b->content;
	b->end = b->content + (b->capacity - 1);
	b->pp = b->start + offset;
}

void
buffer_init (struct buffer *b)
{
	if (!b)
		return;

	b->capacity = 10;
	b->length = 0;
	b->content = calloc (b->capacity, sizeof (char));
	if (!b->content)
		return;
	b->start = b->content;
	b->end = b->content + (b->capacity - 1);
	b->pp = b->start;
}

void
buffer_push (const char *str, struct buffer *b)
{
	if (!str || !b || !b->content)
		return;

	size_t len = strlen (str);
	if (b->length + len >= b->capacity)
		buffer_resize (len, b);

	strncpy (b->content + b->length, str, len);
	b->length += len;
}

void
buffer_seek (int offset, char type, struct buffer *b)
{
	if (!b)
		return;

	switch (type)
		{
		case SEEK_SET:
			b->pp = b->start + offset;
			break;

		case SEEK_CUR:
			b->pp = b->pp + offset < b->end ? b->pp + offset : b->end;
			break;

		case SEEK_END:
			b->pp = b->end;
			break;
		}
}

char
buffer_peek (struct buffer *b)
{
	if (!b || !b->content || !b->pp)
		return 0;

	return *(b->pp + 1);
}

char
buffer_pop (struct buffer *b)
{
	if (!b || !b->content || !b->pp)
		return 0;

	return *b->pp++;
}

char *
buffer_get (struct buffer *b)
{
	if (!b)
		return NULL;

	return b->content;
}

char *
buffer_get_at_position (struct buffer *b)
{
	if (!b || !b->pp)
		return NULL;

	return b->pp < b->end ? b->pp : b->end;
}

void
buffer_free (struct buffer *b)
{
	if (!b)
		return;

	free (b->content);
	memset (b, 0, sizeof (struct buffer));
}

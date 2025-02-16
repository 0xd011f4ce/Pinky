#ifndef __VECTOR_H
#define __VECTOR_H

#include <stddef.h>

struct vector
{
	size_t size;
	size_t capacity;
	void **content;
};

void vector_init (struct vector *v);
void vector_push (void *elm, struct vector *v);
void *vector_pop (struct vector *v);
void vector_free (struct vector *v);

#endif

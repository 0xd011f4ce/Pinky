#include <utils/vector.h>

#include <assert.h>
#include <stdlib.h>

static void
vector_resize (struct vector *v)
{
	v->capacity *= 2;
	v->content = realloc (v->content, sizeof (void *) * v->capacity);
	assert (v->content);
}

void
vector_init (struct vector *v)
{
	if (!v)
		return;

	v->size = 0;
	v->capacity = 5;
	v->content = calloc (v->capacity, sizeof (void *));
}

void
vector_push (void *elm, struct vector *v)
{
	if (!elm || !v || !v->content)
		return;

	if (v->size >= v->capacity)
		vector_resize (v);

	v->content[v->size++] = elm;
}

void *
vector_pop (struct vector *v)
{
	if (!v || !v->content)
		return NULL;

	if (v->size == 0)
		return NULL;

	return v->content[--v->size];
}

void
vector_free (struct vector *v)
{
	if (!v)
		return;

	if (v->content)
		free (v->content);

	v->size = 0;
	v->capacity = 0;
}

#include <stdlib.h>
#include "vector.h"
#include "vector_internal.h"

Vector* vec_create(size_t size_element)
{
    if (size_element == 0) 
    {
        errno = EINVAL;
        return NULL;
    }
    struct Vector *vector = malloc(sizeof(Vector));
    if (vector == NULL)
        return NULL;
    
    vector->data = calloc(STARTCOUNT, size_element);
    if (vector->data == NULL)
    {
        free(vector);
        return NULL;
    }

    vector->capacity = STARTCOUNT;
    vector->elem_size = size_element;
    vector->length = 0;

    return vector;
}

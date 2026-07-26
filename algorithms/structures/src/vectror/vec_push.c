#include <stdlib.h>
#include <string.h>
#include "vector.h"
#include "vector_internal.h"

int vec_push(Vector* vector, const void *value)
{
    if (vector == NULL || value == NULL || vector->data == NULL)
    {
        errno = EINVAL;
        return 0;
    }

    if (vector->length >= vector->capacity)
    {
        size_t new_cap = vector->capacity * 2;
        void *tmp = realloc(vector->data, new_cap * vector->elem_size); 
        if (tmp == NULL)
            return 0;
        
        vector->data = tmp;
        vector->capacity = new_cap;
    }

    memcpy(vector->data + vector->length * vector->elem_size, value, vector->elem_size);
    vector->length++;

    return 1;
}

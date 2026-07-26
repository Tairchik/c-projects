#include <stdlib.h>
#include <string.h>
#include "vector.h"
#include "vector_internal.h"

int vec_insert(Vector* vector, size_t index, const void* value)
{
    if (vector == NULL || value == NULL || vector->data == NULL || index > vector->length)
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

    memmove(vector->data + (index + 1) * vector->elem_size, vector->data + index * vector->elem_size, vector->elem_size * (vector->length - index));
    memcpy(vector->data + index * vector->elem_size, value, vector->elem_size);
    vector->length++;
    return 1;
}

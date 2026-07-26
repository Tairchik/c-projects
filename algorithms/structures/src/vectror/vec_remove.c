#include <stdlib.h>
#include <string.h>
#include "vector.h"
#include "vector_internal.h"

int vec_remove(Vector* vector, size_t index)
{
    if (vector == NULL || vector->data == NULL || index >= vector->length)
    {
        errno = EINVAL;
        return 0;
    }

    vector->length--;
    memmove(vector->data + index * vector->elem_size, vector->data + (index + 1) * vector->elem_size, vector->elem_size * (vector->length - index));

    return 1;
}

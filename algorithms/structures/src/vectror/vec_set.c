#include <string.h>
#include "vector.h"
#include "vector_internal.h"

int vec_set(Vector* vector, size_t index, const void* value)
{
    if (vector == NULL || vector->data == NULL || value == NULL || vector->length <= index)
    {
        errno = EINVAL;
        return 0;
    }

    memcpy(vector->data + vector->elem_size * index, value, vector->elem_size);

    return 1;
}

#include "vector.h"
#include "vector_internal.h"

void vec_pop(Vector* vector)
{
    if (vector == NULL || vector->data == NULL)
    {
        errno = EINVAL;
        return;
    }

    vector->length -= vector->length == 0 ? 0 : 1;
}

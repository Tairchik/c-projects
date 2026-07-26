#include "vector.h"
#include "vector_internal.h"

void* vec_get(Vector* vector, size_t index)
{
    if (vector == NULL || vector->length <= index || vector->data == NULL)
    {
        errno = EINVAL;
        return NULL;
    }
    
    return vector->data + index * vector->elem_size; 
}

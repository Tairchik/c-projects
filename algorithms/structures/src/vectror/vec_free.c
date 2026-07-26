#include <stdlib.h>
#include "vector.h"
#include "vector_internal.h"

void vec_free(Vector *vector)
{
    if (vector == NULL) return;
    free(vector->data);
    free(vector);
}

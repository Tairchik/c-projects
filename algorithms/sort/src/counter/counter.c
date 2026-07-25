#include <stdlib.h>
#include "sort.h"

int sort(int *array, int size)
{
    int max_k = array[0], min_k = array[0];

    for (int i = 0; i < size; i++)
    {
        if (array[i] > max_k)
        {
            max_k = array[i];
        }
        if (array[i] < min_k)
        {
            min_k = array[i];
        }
    }

    int size_count = max_k - min_k + 1;
    int *array_count = calloc(sizeof(int), size_count), ptr = 0;
    if (!array_count) 
        return -1;

    for (int i = 0; i < size; i++)
    {
        array_count[array[i] - min_k]++;
    }

    for (int i = 0; i < size_count; i++)
    {
        for (int j = 0; j < array_count[i]; j++)
        {
            array[ptr] = min_k + i;
            ptr++;
        }
    }

    free(array_count);
    
    return 1;
}
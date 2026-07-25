#include <stdlib.h>
#include "sort.h"

// Для простоты приниамется, что диапазон элементолв есть size (от 1 до size)
int sort(int *array, int size)
{
    int *array_count = calloc(sizeof(int), size), ptr = 0;

    if (!array_count) 
        return -1;

    for (int i = 0; i < size; i++)
    {
        array_count[array[i] - 1]++;
    }

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < array_count[i]; j++)
        {
            array[ptr] = i + 1;
            ptr++;
        }
    }

    free(array_count);
    
    return 1;
}
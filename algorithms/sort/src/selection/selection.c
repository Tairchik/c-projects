#include "sort.h"

int sort(int *array, int size)
{
    int tmp, mi;

    for (int i = 0; i < size - 1; i++)
    {
        mi = i;

        // Ищем минимальный элемент
        for (int j = i + 1; j < size; j++)
        {
            if (array[j] < array[mi])
                mi = j;
        }

        tmp = array[i];
        array[i] = array[mi];
        array[mi] = tmp; 
    }

    return 1;
}
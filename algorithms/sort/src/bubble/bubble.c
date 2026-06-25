#include "sort.h"

int sort(int *array, int size)
{
    int tmp, swapped = 0;

    for (int i = 0; i < size - 1; i++)
    {
        swapped = 0;
        for (int j = size - 1; j >= i + 1; j--)
        {
            if (array[j] < array[j - 1])
            {
                tmp = array[j];
                array[j] = array[j - 1];
                array[j - 1] = tmp;
                swapped = 1;
            }
        }

        if (swapped == 0)
            return 1;
    }

    return 1;
}
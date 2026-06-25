#include "sort.h"

int sort(int *array, int size)
{
    int tmp, j = 0;

    for (int i = 1; i < size; i++)
    {
        j = i;
        while (j > 0 && array[j] < array[j - 1])
        {
            tmp = array[j];
            array[j] = array[j - 1];
            array[j - 1] = tmp;
            j -= 1;
        }
    }

    return 1;
}
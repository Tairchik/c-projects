#include "sort.h"

int sort(int *array, int size)
{
    int tmp, n = size;

    for (int i = 0; i < n - 2; i++)
    {
        for (int j = n - 1; j >= i + 1; j--)
        {
            if (array[j] < array[j - 1])
            {
                tmp = array[j];
                array[j] = array[j - 1];
                array[j - 1] = tmp;
            }
        }
    }

    return 1;
}
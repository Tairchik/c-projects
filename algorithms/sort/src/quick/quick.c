#include <stdlib.h>
#include "sort.h"

static void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

static int distributor(int *array, int start, int end)
{
int mid = start + (end - start) / 2;
    swap(&array[mid], &array[end]);

    int pivot = array[end];
    int i = start - 1;

    for (int j = start; j < end; j++)
    {
        if (array[j] <= pivot)
        {
            i++;
            swap(&array[i], &array[j]);
        }
    }

    swap(&array[i + 1], &array[end]);
    return i + 1;
}

static void quicksort(int *array, int start, int end)
{
    if (start < end)
    {
        int split = distributor(array, start, end);
        quicksort(array, start, split - 1);
        quicksort(array, split + 1, end);
    }
}

int sort(int *array, int size)
{
    quicksort(array, 0, size - 1);
    return 1;
}

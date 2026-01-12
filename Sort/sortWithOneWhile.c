#include <stdio.h>


void sort(int array[], int size)
{
    int i = 0, temp;
    while (i < size - 1)
    {   
        if (array[i] > array[i + 1])
        {
            temp = array[i];
            array[i] = array[i + 1];
            array[i + 1] = temp;
            i = 0;
            continue;
        }
        i++;
    }
}
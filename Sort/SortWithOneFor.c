#include <stdio.h>


void sort(int array[], int size)
{
    int temp;
    for (int i = 0; i < size - 1; i++)
    {
        if (array[i] > array[i + 1]) 
        {
            temp = array[i];
            array[i] = array[i + 1];
            array[i + 1] = temp;
            i = -1;
        }
    }
}
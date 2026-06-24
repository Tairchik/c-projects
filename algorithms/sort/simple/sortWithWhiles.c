#include <stdio.h>


void sort(int array[], int size)
{
    int i = 0, j = 0;

    while (i < size)
    {
        j = i;
        while (j < i)
        {
            if (array[i] > array[j])
            {
                int temp = array[i];
                array[i] = array[j];
                array[j] = temp;
            }
            ++j;
        }   
        ++i;     
    }
    
}
#include <stdio.h>


void sort (int array[], int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = i + 1; j < size; j++)
        {
            if (array[i] > array[j]) 
            {
                int temp = array[j];
                array[j] = array[i];
                array[i] = temp;
            }             
        }    
    }
}
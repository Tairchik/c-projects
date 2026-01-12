#include <stdio.h>
#include "interface.h"


void printArray(int array[], int size)
{
    int i = 0;
    while (i < size) 
    {
        printf("%d ", array[i]);
        ++i; 
    }
}


int main()
{
    int input_array[] = {1, 4, 3, 2, 4, -5};
    int size = sizeof(input_array) / sizeof(int);
    sort(input_array, size);
    printArray(input_array, size);
    return 0;    
}
#include <stdio.h>

void bubbleSort(int array[], int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - i - 1; j++)
        {
            if (array[j] > array[j + 1])
            {
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}

void printArray(int array[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}

int main()
{
    int array[] = {22, 10, 15, 3, 8, 2};
    int size = sizeof(array) / sizeof(array[0]);

    // printf("Array sebelum diurutkan:\n");
    // printArray(array, size);

    bubbleSort(array, size);

    printf("Array setelah diurutkan:\n");
    printArray(array, size);

    return 0;
}

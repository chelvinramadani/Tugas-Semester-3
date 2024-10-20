#include <stdio.h>

int main()
{
    int angka[] = {8, 10, 6, -2, 11, 7, 1, 100};
    int searchValue;
    int found = 0;

    printf("Masukkan angka yang ingin dicari: ");
    scanf("%d", &searchValue);

    for (int i = 0; i < 8; i++)
    {
        if (angka[i] == searchValue)
        {
            found = 1;
            printf("\nData ada\n");
            break;
        }
    }

    if (!found)
    {
        printf("\nData tidak ada.\n");
    }

    return 0;
}

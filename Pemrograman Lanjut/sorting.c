#include <stdio.h>
#include <string.h>

#define MAX_MAHASISWA 5

struct mahasiswa
{
    char npm[15];
    char nama[50];
    char prodi[50];
    float ipk;
};

void tampilkanMahasiswa(struct mahasiswa mhs[], int n)
{
    printf("data mahasiswa:\n");
    for (int i = 0; i < n; i++)
    {
        printf("NPM :%s, Nama :%s, Prodi :%s, IPK :%.2f\n", mhs[i].npm, mhs[i].nama, mhs[i].prodi, mhs[i].ipk);
    }
}

void bubbleSort(struct mahasiswa mhs[], int n, int ascending)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            int compare = strcmp(mhs[j].npm, mhs[j + 1].npm);
            if ((ascending && compare > 0) || (!ascending && compare < 0))
            {
                struct mahasiswa temp = mhs[j];
                mhs[j] = mhs[j + 1];
                mhs[j + 1] = temp;
            }
        }
    }
}

void selectionSort(struct mahasiswa mhs[], int n, int ascending)
{
    for (int i = 0; i < n - 1; i++)
    {
        int minOrMaxIndex = i;
        for (int j = i + 1; j < n; j++)
        {
            int compare = strcmp(mhs[j].npm, mhs[minOrMaxIndex].npm);
            if ((ascending && compare < 0) || (!ascending && compare > 0))
            {
                minOrMaxIndex = j;
            }
        }
        if (minOrMaxIndex != i)
        {
            struct mahasiswa temp = mhs[i];
            mhs[i] = mhs[minOrMaxIndex];
            mhs[minOrMaxIndex] = temp;
        }
    }
}

void insertionSort(struct mahasiswa mhs[], int n, int ascending)
{
    for (int i = 1; i < n; i++)
    {
        struct mahasiswa key = mhs[i];
        int j = i - 1;
        while (j >= 0 && ((ascending && strcmp(mhs[j].npm, key.npm) > 0) || (!ascending && strcmp(mhs[j].npm, key.npm) < 0)))
        {
            mhs[j + 1] = mhs[j];
            j--;
        }
        mhs[j + 1] = key;
    }
}

int main()
{
    struct mahasiswa mhs[MAX_MAHASISWA] = {
        {"23081010155", "Chelvin", "Informatika", 4.00},
        {"23081010100", "Eko", "Informatika", 3.80},
        {"21011010101", "Nadya", "Akuntansi", 3.95},
        {"24011010001", "Icha", "Ekonomi", 4.00},
        {"22082010200", "Yusuf", "Sistem Informasi", 3.65}};
    int choice, order;

    while (1)
    {
        printf("\nMenu Sorting:\n");
        printf("1. Bubble Sort\n");
        printf("2. Selection Sort\n");
        printf("3. Insertion Sort\n");
        printf("4. Keluar\n");
        printf("masukkan pilihan anda: ");
        scanf("%d", &choice);

        if (choice == 4)
        {
            printf("Keluar dari program.\n");
            break;
        }

        printf("Pilih urutan:\n1. Ascending\n2. Descending\n");
        printf("masukkan pilihan sorting:");
        scanf("%d", &order);
        int ascending = (order == 1);

        printf("\nData Sebelum sorting:\n");
        tampilkanMahasiswa(mhs, MAX_MAHASISWA);

        switch (choice)
        {
        case 1:
            bubbleSort(mhs, MAX_MAHASISWA, ascending);
            break;
        case 2:
            selectionSort(mhs, MAX_MAHASISWA, ascending);
            break;
        case 3:
            insertionSort(mhs, MAX_MAHASISWA, ascending);
            break;
        default:
            printf("Pilihan tidak valid\n");
            continue;
        }

        printf("Data setelah sorting:\n");
        tampilkanMahasiswa(mhs, MAX_MAHASISWA);
    }
    return 0;
}
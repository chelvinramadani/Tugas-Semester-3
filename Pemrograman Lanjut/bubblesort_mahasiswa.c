#include <stdio.h>
#include <string.h>

#define MAX_MAHASISWA 5

typedef struct
{
    char npm[15];
    char nama[50];
    char prodi[50];
    float ipk;
} Mahasiswa;

void tampilkanMahasiswa(Mahasiswa mhs[], int n)
{
    printf("Data Mahasiswa:\n");
    for (int i = 0; i < n; i++)
    {
        printf("NPM: %s, Nama: %s, Prodi: %s, IPK: %.2f\n",
               mhs[i].npm, mhs[i].nama, mhs[i].prodi, mhs[i].ipk);
    }
}

void bubbleSortNIM(Mahasiswa mhs[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (strcmp(mhs[j].npm, mhs[j + 1].npm) > 0)
            {
                Mahasiswa temp = mhs[j];
                mhs[j] = mhs[j + 1];
                mhs[j + 1] = temp;
            }
        }
    }
}

int main()
{
    Mahasiswa mhs[MAX_MAHASISWA] = {
        {"23081010155", "Chelvin", "Informatika", 3.9},
        {"23071010100", "Andi", "Sistem Informasi", 3.8},
        {"21081010101", "Yanto", "Informatika", 3.75},
        {"21011010110", "Fauzan", "Teknik Lingkungan", 3.9},
        {"23071010001", "Hana", "Hukum", 3.70}};

    printf("Data sebelum sorting:\n");
    tampilkanMahasiswa(mhs, MAX_MAHASISWA);

    bubbleSortNIM(mhs, MAX_MAHASISWA);

    printf("\nData setelah sorting berdasarkan NIM:\n");
    tampilkanMahasiswa(mhs, MAX_MAHASISWA);

    return 0;
}
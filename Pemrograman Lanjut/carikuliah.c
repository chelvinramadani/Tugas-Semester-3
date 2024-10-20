#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct kuliah
{
    int kodemk;
    char matakuliah[50];
    int sks;
    char jam[10];
    char ruang[20];
};

int main()
{
    struct kuliah *kelas;
    int jumlahData, cariKodeMK;
    int found = 0;

    printf("Masukkan jumlah mata kuliah : ");
    scanf("%d", &jumlahData);

    kelas = (struct kuliah *)malloc(jumlahData * sizeof(struct kuliah));

    if (kelas == NULL)
    {
        printf("Memori tidak cukup!\n");
        return 1;
    }

    for (int i = 0; i < jumlahData; i++)
    {
        printf("Masukkan kode MK untuk mata kuliah %d: ", i + 1);
        scanf("%d", &kelas[i].kodemk);

        printf("Masukkan nama mata kuliah: ");
        scanf(" %[^\n]s", kelas[i].matakuliah);

        printf("Masukkan jumlah SKS: ");
        scanf("%d", &kelas[i].sks);

        printf("Masukkan jam mata kuliah (format HH:MM AM/PM): ");
        scanf("%s", kelas[i].jam);

        printf("Masukkan ruang mata kuliah: ");
        scanf(" %[^\n]s", kelas[i].ruang);

        printf("\n");
    }

    printf("Data mata kuliah yang telah dimasukkan:\n");
    for (int i = 0; i < jumlahData; i++)
    {
        printf("Kode MK: %d\n", kelas[i].kodemk);
        printf("Mata Kuliah: %s\n", kelas[i].matakuliah);
        printf("SKS: %d\n", kelas[i].sks);
        printf("Jam: %s\n", kelas[i].jam);
        printf("Ruang: %s\n\n", kelas[i].ruang);
    }

    printf("Masukkan kode mata kuliah yang ingin dicari: ");
    scanf("%d", &cariKodeMK);

    for (int i = 0; i < jumlahData; i++)
    {
        if (cariKodeMK == kelas[i].kodemk)
        {
            found = 1;
            printf("\nData ditemukan:\n");
            printf("Kode MK: %d\n", kelas[i].kodemk);
            printf("Mata Kuliah: %s\n", kelas[i].matakuliah);
            printf("SKS: %d\n", kelas[i].sks);
            printf("Jam: %s\n", kelas[i].jam);
            printf("Ruang: %s\n", kelas[i].ruang);
            break;
        }
    }

    // Jika kode tidak ditemukan
    if (!found)
    {
        printf("\nData tidak ada.\n");
    }

    free(kelas);

    return 0;
}
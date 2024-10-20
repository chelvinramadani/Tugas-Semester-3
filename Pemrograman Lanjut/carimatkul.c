#include <stdio.h>
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
    struct kuliah kelas[5];
    int cariKodeMK;
    int found = 0;

    // Inisialisasi data kuliah
    kelas[0].kodemk = 1;
    strcpy(kelas[0].matakuliah, "Pemrograman Dasar");
    kelas[0].sks = 3;
    strcpy(kelas[0].jam, "07:00 AM");
    strcpy(kelas[0].ruang, "Gedung 1 101");

    kelas[1].kodemk = 2;
    strcpy(kelas[1].matakuliah, "Pemrograman Lanjut");
    kelas[1].sks = 3;
    strcpy(kelas[1].jam, "09:30 AM");
    strcpy(kelas[1].ruang, "Gedung 2 301");

    kelas[2].kodemk = 3;
    strcpy(kelas[2].matakuliah, "Pemrograman Website");
    kelas[2].sks = 3;
    strcpy(kelas[2].jam, "12:00 AM");
    strcpy(kelas[2].ruang, "Gedung 2 201");

    kelas[3].kodemk = 4;
    strcpy(kelas[3].matakuliah, "Pemrograman Framework");
    kelas[3].sks = 3;
    strcpy(kelas[3].jam, "07:00 AM");
    strcpy(kelas[3].ruang, "Gedung 2 201");

    kelas[4].kodemk = 5;
    strcpy(kelas[4].matakuliah, "Riset Informatika");
    kelas[4].sks = 3;
    strcpy(kelas[4].jam, "12:00 AM");
    strcpy(kelas[4].ruang, "Gedung 1 103");

    // Mencetak semua data kuliah
    for (int i = 0; i < 5; i++)
    {
        printf("Kode MK: %d\n", kelas[i].kodemk);
        printf("Mata Kuliah: %s\n", kelas[i].matakuliah);
        printf("SKS: %d\n", kelas[i].sks);
        printf("Jam: %s\n", kelas[i].jam);
        printf("Ruang: %s\n\n", kelas[i].ruang);
    }

    // Meminta input dari pengguna untuk kode mata kuliah yang dicari
    printf("Masukkan kode mata kuliah yang ingin dicari: ");
    scanf("%d", &cariKodeMK);

    // Pencarian kode mata kuliah menggunakan array
    for (int i = 0; i < 5; i++)
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

    return 0;
}
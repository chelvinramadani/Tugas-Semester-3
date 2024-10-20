#include <stdio.h>
#include <string.h>

#define MAX_RUTE 100

// Definisi struct untuk rute kereta api
struct RuteKereta
{
    int nomorPerjalanan;
    char nama[50];
    char tujuan[50];
    char keberangkatan[10];
};

// Deklarasi array of struct
struct RuteKereta ruteKereta[MAX_RUTE];
int jumlahRute = 0;

// Fungsi untuk menambah data rute
void tambahRute(int nomorPerjalanan, char nama[], char tujuan[], char keberangkatan[])
{
    if (jumlahRute < MAX_RUTE)
    {
        ruteKereta[jumlahRute].nomorPerjalanan = nomorPerjalanan;
        strcpy(ruteKereta[jumlahRute].nama, nama);
        strcpy(ruteKereta[jumlahRute].tujuan, tujuan);
        strcpy(ruteKereta[jumlahRute].keberangkatan, keberangkatan);
        jumlahRute++;
    }
    else
    {
        printf("Data penuh, tidak bisa menambah lebih banyak rute.\n");
    }
}

// Fungsi untuk menampilkan semua data rute
void tampilkanRute()
{
    printf("Data Rute Kereta Api:\n");
    for (int i = 0; i < jumlahRute; i++)
    {
        printf("Nomor Perjalanan: %d, Nama: %s, Tujuan: %s, Keberangkatan: %s\n",
               ruteKereta[i].nomorPerjalanan, ruteKereta[i].nama, ruteKereta[i].tujuan, ruteKereta[i].keberangkatan);
    }
}

// Fungsi untuk menampilkan menu
void tampilkanMenu()
{
    printf("\nMenu:\n");
    printf("1. Tambah Rute\n");
    printf("2. Tampilkan Semua Rute\n");
    printf("3. Keluar\n");
}

int main()
{
    int pilihan;
    int nomorPerjalanan;
    char nama[50], tujuan[50], keberangkatan[10];

    do
    {
        tampilkanMenu();
        printf("Masukkan pilihan: ");
        scanf("%d", &pilihan);

        switch (pilihan)
        {
        case 1:
            printf("Masukkan Nomor Perjalanan: ");
            scanf("%d", &nomorPerjalanan);
            printf("Masukkan Nama Kereta: ");
            scanf(" %[^\n]", nama); // Membaca input dengan spasi
            printf("Masukkan Stasiun Tujuan: ");
            scanf(" %[^\n]", tujuan);
            printf("Masukkan Jam Keberangkatan (format HH:MM): ");
            scanf(" %[^\n]", keberangkatan);
            tambahRute(nomorPerjalanan, nama, tujuan, keberangkatan);
            break;

        case 2:
            tampilkanRute();
            break;

        case 3:
            printf("Keluar dari program.\n");
            break;

        default:
            printf("Pilihan tidak valid.\n");
        }

    } while (pilihan != 3);

    return 0;
}
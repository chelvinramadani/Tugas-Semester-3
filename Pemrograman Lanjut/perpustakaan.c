#include <stdio.h>
#include <string.h>

// Definisi struct untuk buku
struct Buku
{
    char judul[100];
    char penulis[100];
    char genre[50];
};

// Deklarasi array untuk menyimpan data buku
struct Buku perpustakaan[100];
int jumlahBuku = 0;

// Function untuk menambah buku
void tambahBuku(char judul[], char penulis[], char genre[])
{
    strcpy(perpustakaan[jumlahBuku].judul, judul);
    strcpy(perpustakaan[jumlahBuku].penulis, penulis);
    strcpy(perpustakaan[jumlahBuku].genre, genre);
    jumlahBuku++;
    printf("Buku '%s' berhasil ditambahkan!\n", judul);
}

// Function untuk menampilkan semua buku
void tampilkanSemuaBuku()
{
    printf("\nDaftar Buku di Perpustakaan:\n");
    for (int i = 0; i < jumlahBuku; i++)
    {
        printf("Buku %d:\n", i + 1);
        printf("Judul  : %s, Penulis : %s, Genre : %s\n",
               perpustakaan[i].judul, perpustakaan[i].penulis, perpustakaan[i].genre);
    }
}

// Function untuk mencari buku berdasarkan judul
void cariBuku(char judul[])
{
    int ditemukan = 0;
    for (int i = 0; i < jumlahBuku; i++)
    {
        if (strcmp(perpustakaan[i].judul, judul) == 0)
        {
            printf("\nBuku ditemukan!\n");
            printf("Judul  : %s, Penulis : %s, Genre : %s\n",
                   perpustakaan[i].judul, perpustakaan[i].penulis, perpustakaan[i].genre);

            ditemukan = 1;
            break;
        }
    }
    if (!ditemukan)
    {
        printf("Buku dengan judul '%s' tidak ditemukan.\n", judul);
    }
}

// Function utama
int main()
{
    int pilihan;
    char judul[100], penulis[100], genre[50];

    do
    {
        printf("\nSistem Manajemen Buku Perpustakaan\n");
        printf("1. Tambah Buku\n");
        printf("2. Tampilkan Semua Buku\n");
        printf("3. Cari Buku\n");
        printf("4. Keluar\n");
        printf("Pilih opsi (1-4): ");
        scanf("%d", &pilihan);
        getchar(); // Untuk menangani newline setelah input angka

        switch (pilihan)
        {
        case 1:
            printf("Masukkan Judul Buku: ");
            fgets(judul, 100, stdin);
            judul[strcspn(judul, "\n")] = 0; // Menghilangkan newline di akhir input

            printf("Masukkan Nama Penulis: ");
            fgets(penulis, 100, stdin);
            penulis[strcspn(penulis, "\n")] = 0;

            printf("Masukkan Genre Buku: ");
            fgets(genre, 50, stdin);
            genre[strcspn(genre, "\n")] = 0;

            tambahBuku(judul, penulis, genre);
            break;

        case 2:
            tampilkanSemuaBuku();
            break;

        case 3:
            printf("Masukkan Judul Buku yang Ingin Dicari: ");
            fgets(judul, 100, stdin);
            judul[strcspn(judul, "\n")] = 0;

            cariBuku(judul);
            break;

        case 4:
            printf("Keluar dari program.\n");
            break;

        default:
            printf("Opsi tidak valid. Silakan coba lagi.\n");
        }
    } while (pilihan != 4);

    return 0;
}
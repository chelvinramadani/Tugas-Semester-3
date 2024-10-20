#include <stdio.h>
#include <string.h>

// Definisi struct untuk menyimpan data nasabah
struct Nasabah
{
    int nomorRekening;
    char nama[50];
    float saldo;
};

// Deklarasi array of struct untuk menyimpan data nasabah
struct Nasabah daftarNasabah[100];

// Variabel untuk menyimpan jumlah nasabah yang ada
int jumlahNasabah = 0;

// Deklarasi fungsi-fungsi
void tambahNasabah(int nomorRekening, char nama[], float saldoAwal);
void tampilkanNasabah();
struct Nasabah *cariNasabah(int nomorRekening);

int main()
{
    int pilihan, nomorRekening;
    char nama[50];
    float saldoAwal;

    do
    {
        printf("\nMenu:\n");
        printf("1. Tambah Nasabah\n");
        printf("2. Tampilkan Semua Nasabah\n");
        printf("3. Cari Nasabah berdasarkan Nomor Rekening\n");
        printf("4. Keluar\n");
        printf("Pilih menu: ");
        scanf("%d", &pilihan);

        switch (pilihan)
        {
        case 1:
            // Input data nasabah baru
            printf("Masukkan nomor rekening: ");
            scanf("%d", &nomorRekening);
            getchar(); // Menghilangkan newline

            printf("Masukkan nama nasabah: ");
            fgets(nama, sizeof(nama), stdin);
            nama[strcspn(nama, "\n")] = 0; // Menghilangkan newline dari fgets

            printf("Masukkan saldo awal: ");
            scanf("%f", &saldoAwal);

            // Tambahkan nasabah
            tambahNasabah(nomorRekening, nama, saldoAwal);
            break;

        case 2:
            // Tampilkan semua nasabah
            tampilkanNasabah();
            break;

        case 3:
            // Cari nasabah berdasarkan nomor rekening
            printf("Masukkan nomor rekening: ");
            scanf("%d", &nomorRekening);

            struct Nasabah *nasabah = cariNasabah(nomorRekening);
            if (nasabah != NULL)
            {
                printf("Nomor Rekening: %d\n", nasabah->nomorRekening);
                printf("Nama: %s\n", nasabah->nama);
                printf("Saldo: %.2f\n", nasabah->saldo);
            }
            else
            {
                printf("Nasabah dengan nomor rekening %d tidak ditemukan.\n", nomorRekening);
            }
            break;

        case 4:
            printf("Keluar dari program.\n");
            break;

        default:
            printf("Pilihan tidak valid. Coba lagi.\n");
        }

    } while (pilihan != 4);

    return 0;
}

// Fungsi untuk menambahkan nasabah
void tambahNasabah(int nomorRekening, char nama[], float saldoAwal)
{
    daftarNasabah[jumlahNasabah].nomorRekening = nomorRekening;
    strcpy(daftarNasabah[jumlahNasabah].nama, nama);
    daftarNasabah[jumlahNasabah].saldo = saldoAwal;
    jumlahNasabah++;
    printf("Nasabah berhasil ditambahkan!\n");
}

// Fungsi untuk menampilkan semua nasabah
void tampilkanNasabah()
{
    if (jumlahNasabah == 0)
    {
        printf("Belum ada nasabah yang terdaftar.\n");
    }
    else
    {
        printf("\nDaftar Nasabah:\n");
        for (int i = 0; i < jumlahNasabah; i++)
        {
            printf("Nomor Rekening: %d, Nama: %s, Saldo: %.2f\n",
                   daftarNasabah[i].nomorRekening,
                   daftarNasabah[i].nama,
                   daftarNasabah[i].saldo);
        }
    }
}

// Fungsi untuk mencari nasabah berdasarkan nomor rekening
struct Nasabah *cariNasabah(int nomorRekening)
{
    for (int i = 0; i < jumlahNasabah; i++)
    {
        if (daftarNasabah[i].nomorRekening == nomorRekening)
        {
            return &daftarNasabah[i];
        }
    }
    return NULL; // Jika nasabah tidak ditemukan
}

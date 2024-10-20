#include <stdio.h>
#include <string.h>

// Definisi struct untuk menyimpan data mahasiswa
struct Mahasiswa
{
    char nama[50];
    char NIM[15];
    float IPK;
};

// Deklarasi array of struct
struct Mahasiswa daftarMahasiswa[100];

// Variabel untuk menyimpan jumlah mahasiswa yang telah ditambahkan
int jumlahMahasiswa = 0;

// Deklarasi fungsi-fungsi
void tambahMahasiswa(char nama[], char NIM[], float IPK);
void tampilkanMahasiswa();
struct Mahasiswa *cariMahasiswa(char NIM[]);

// Fungsi untuk menambahkan mahasiswa ke dalam array
void tambahMahasiswa(char nama[], char NIM[], float IPK)
{
    if (jumlahMahasiswa < 100)
    {
        strcpy(daftarMahasiswa[jumlahMahasiswa].nama, nama);
        strcpy(daftarMahasiswa[jumlahMahasiswa].NIM, NIM);
        daftarMahasiswa[jumlahMahasiswa].IPK = IPK;
        jumlahMahasiswa++;
        printf("Mahasiswa berhasil ditambahkan!\n");
    }
    else
    {
        printf("Kapasitas mahasiswa penuh.\n");
    }
}

// Fungsi untuk menampilkan semua mahasiswa
void tampilkanMahasiswa()
{
    if (jumlahMahasiswa > 0)
    {
        printf("\nDaftar Mahasiswa:\n");
        for (int i = 0; i < jumlahMahasiswa; i++)
        {
            printf("Mahasiswa %d:\n", i + 1);
            printf("Nama: %s\n", daftarMahasiswa[i].nama);
            printf("NIM: %s\n", daftarMahasiswa[i].NIM);
            printf("IPK: %.2f\n", daftarMahasiswa[i].IPK);
        }
    }
    else
    {
        printf("Belum ada data mahasiswa.\n");
    }
}

// Fungsi untuk mencari mahasiswa berdasarkan NIM
struct Mahasiswa *cariMahasiswa(char NIM[])
{
    for (int i = 0; i < jumlahMahasiswa; i++)
    {
        if (strcmp(daftarMahasiswa[i].NIM, NIM) == 0)
        {
            return &daftarMahasiswa[i];
        }
    }
    return NULL; // Jika mahasiswa tidak ditemukan
}

int main()

{
    int pilihan;
    char nama[50], NIM[15];
    float IPK;

    do
    {
        printf("\nMenu:\n");
        printf("1. Tambah Mahasiswa\n");
        printf("2. Tampilkan Semua Mahasiswa\n");
        printf("3. Cari Mahasiswa berdasarkan NIM\n");
        printf("4. Keluar\n");
        printf("Pilih menu: ");
        scanf("%d", &pilihan);
        getchar(); // Menghilangkan karakter newline setelah input

        switch (pilihan)
        {
        case 1:
            // Input data mahasiswa baru
            printf("Masukkan nama mahasiswa: ");
            fgets(nama, sizeof(nama), stdin);
            nama[strcspn(nama, "\n")] = 0; // Menghilangkan newline dari fgets

            printf("Masukkan NIM mahasiswa: ");
            fgets(NIM, sizeof(NIM), stdin);
            NIM[strcspn(NIM, "\n")] = 0; // Menghilangkan newline dari fgets

            printf("Masukkan IPK mahasiswa: ");
            scanf("%f", &IPK);

            // Panggil fungsi untuk menambahkan mahasiswa
            tambahMahasiswa(nama, NIM, IPK);
            break;
        case 2:
            // Panggil fungsi untuk menampilkan semua mahasiswa
            tampilkanMahasiswa();
            break;
        case 3:
            // Input NIM mahasiswa yang ingin dicari
            printf("Masukkan NIM yang ingin dicari: ");
            fgets(NIM, sizeof(NIM), stdin);
            NIM[strcspn(NIM, "\n")] = 0; // Menghilangkan newline dari fgets

            // Panggil fungsi untuk mencari mahasiswa
            struct Mahasiswa *mhs = cariMahasiswa(NIM);
            if (mhs != NULL)
            {
                printf("Mahasiswa ditemukan\n");
                printf("Nama: %s\n", mhs->nama);
                printf("NIM: %s\n", mhs->NIM);
                printf("IPK: %.2f\n", mhs->IPK);
            }
            else
            {
                printf("Mahasiswa dengan NIM %s tidak ditemukan.\n", NIM);
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
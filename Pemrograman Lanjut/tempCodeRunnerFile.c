#include <stdio.h>
#include <string.h>

#define MAX_PASIEN 100

// Struktur data pasien
struct Pasien {
    char noRegistrasi[20];
    char nama[50];
    char alamat[100];
    int umur;
};

// Fungsi untuk menambahkan pasien baru
void tambahPasien(struct Pasien pasien[], int *jumlah) {
    struct Pasien pasienBaru;
    int unik = 0;
    
    // Memasukkan nomor registrasi dengan format NRP diikuti nomor unik
    while (!unik) {
        printf("Masukkan nomor registrasi (format: NRPXXXX): ");
        scanf("%s", pasienBaru.noRegistrasi);
        
        // Memeriksa apakah sudah ada nomor registrasi yang sama
        unik = 1;
        for (int i = 0; i < *jumlah; i++) {
            if (strcmp(pasien[i].noRegistrasi, pasienBaru.noRegistrasi) == 0) {
                printf("Nomor registrasi sudah ada. Masukkan nomor lain.\n");
                unik = 0;
                break;
            }
        }
        
        // Memeriksa apakah format nomor registrasi dimulai dengan NRP
        if (strncmp(pasienBaru.noRegistrasi, "NRP", 3) != 0) {
            printf("Nomor registrasi harus diawali dengan 'NRP'.\n");
            unik = 0;
        }
    }

    // Input data pasien
    printf("Masukkan nama pasien: ");
    scanf(" %[^\n]%*c", pasienBaru.nama); // Menggunakan %[^\n]%*c untuk menangkap spasi dalam input
    printf("Masukkan alamat pasien: ");
    scanf(" %[^\n]%*c", pasienBaru.alamat);
    printf("Masukkan umur pasien: ");
    scanf("%d", &pasienBaru.umur);
    
    // Menambahkan pasien ke dalam array
    pasien[*jumlah] = pasienBaru;
    (*jumlah)++;
    
    printf("Data pasien berhasil ditambahkan!\n");
}

// Fungsi untuk menampilkan semua data pasien
void tampilkanPasien(struct Pasien pasien[], int jumlah) {
    if (jumlah == 0) {
        printf("Belum ada data pasien.\n");
        return;
    }
    
    printf("Data semua pasien:\n");
    for (int i = 0; i < jumlah; i++) {
        printf("Nomor Registrasi: %s\n", pasien[i].noRegistrasi);
        printf("Nama: %s\n", pasien[i].nama);
        printf("Alamat: %s\n", pasien[i].alamat);
        printf("Umur: %d\n", pasien[i].umur);
        printf("-------------------------\n");
    }
}

// Fungsi untuk mencari pasien berdasarkan kriteria
void cariPasien(struct Pasien pasien[], int jumlah) {
    int pilihan;
    char kataKunci[100];
    int umurCari;
    
    printf("Pilih kriteria pencarian:\n");
    printf("1. Nomor Registrasi\n");
    printf("2. Nama\n");
    printf("3. Alamat\n");
    printf("4. Umur\n");
    printf("Masukkan pilihan: ");
    scanf("%d", &pilihan);
    
    switch (pilihan) {
        case 1:
            printf("Masukkan nomor registrasi: ");
            scanf("%s", kataKunci);
            for (int i = 0; i < jumlah; i++) {
                if (strcmp(pasien[i].noRegistrasi, kataKunci) == 0) {
                    printf("Data ditemukan:\n");
                    printf("Nomor Registrasi: %s\n", pasien[i].noRegistrasi);
                    printf("Nama: %s\n", pasien[i].nama);
                    printf("Alamat: %s\n", pasien[i].alamat);
                    printf("Umur: %d\n", pasien[i].umur);
					printf("-------------------------\n");
                    return;
                }
            }
            printf("Data dengan nomor registrasi tersebut tidak ditemukan.\n");
            break;
        case 2:
            printf("Masukkan nama pasien: ");
            scanf(" %[^\n]%*c", kataKunci);
            for (int i = 0; i < jumlah; i++) {
                if (strstr(pasien[i].nama, kataKunci) != NULL) {
                    printf("Data ditemukan:\n");
                    printf("Nomor Registrasi: %s\n", pasien[i].noRegistrasi);
                    printf("Nama: %s\n", pasien[i].nama);
                    printf("Alamat: %s\n", pasien[i].alamat);
                    printf("Umur: %d\n", pasien[i].umur);
					printf("-------------------------\n");
                }
            }
            break;
        case 3:
            printf("Masukkan alamat pasien: ");
            scanf(" %[^\n]%*c", kataKunci);
            for (int i = 0; i < jumlah; i++) {
                if (strstr(pasien[i].alamat, kataKunci) != NULL) {
                    printf("Data ditemukan:\n");
                    printf("Nomor Registrasi: %s\n", pasien[i].noRegistrasi);
                    printf("Nama: %s\n", pasien[i].nama);
                    printf("Alamat: %s\n", pasien[i].alamat);
                    printf("Umur: %d\n", pasien[i].umur);
					printf("-------------------------\n");
                }
            }
            break;
        case 4:
            printf("Masukkan umur pasien: ");
            scanf("%d", &umurCari);
            for (int i = 0; i < jumlah; i++) {
                if (pasien[i].umur == umurCari) {
                    printf("Data ditemukan:\n");
                    printf("Nomor Registrasi: %s\n", pasien[i].noRegistrasi);
                    printf("Nama: %s\n", pasien[i].nama);
                    printf("Alamat: %s\n", pasien[i].alamat);
                    printf("Umur: %d\n", pasien[i].umur);
					printf("-------------------------\n");
                }
            }
            break;
        default:
            printf("Pilihan tidak valid.\n");
    }
}

int main() {
    struct Pasien pasien[MAX_PASIEN];
    int jumlah = 0;
    int pilihan;
    
    do {
        printf("\nMenu Klinik:\n");
        printf("1. Tambah Data Pasien\n");
        printf("2. Tampilkan Semua Data Pasien\n");
        printf("3. Cari Data Pasien\n");
        printf("4. Keluar\n");
        printf("Masukkan pilihan: ");
        scanf("%d", &pilihan);
        
        switch (pilihan) {
            case 1:
                tambahPasien(pasien, &jumlah);
                break;
            case 2:
                tampilkanPasien(pasien, jumlah);
                break;
            case 3:
                cariPasien(pasien, jumlah);
                break;
            case 4:
                printf("Terima kasih telah menggunakan sistem pendataan klinik.\n");
                break;
            default:
                printf("Pilihan tidak valid. Silakan coba lagi.\n");
        }
    } while (pilihan != 4);
    
    return 0;
}
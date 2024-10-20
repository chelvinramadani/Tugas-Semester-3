#include <stdio.h>
#include <string.h>

struct RuteBis
{
    int nomorPerjalanan;
    char namaperusahaan[50];
    char Jurusan[50];
    char jamKeberangkatan[10];
};

int main()
{

    struct RuteBis bis1, bis2, bis3;

    bis1.nomorPerjalanan = 1;
    strcpy(bis1.namaperusahaan, "Sinar Jaya");
    strcpy(bis1.Jurusan, "Surabaya - Jakarta");
    strcpy(bis1.jamKeberangkatan, "08:00 AM");

    bis2.nomorPerjalanan = 2;
    strcpy(bis2.namaperusahaan, "Sugeng Rahayu");
    strcpy(bis2.Jurusan, "Surabaya - Solo");
    strcpy(bis2.jamKeberangkatan, "08:05 AM");

    printf("Rute Bis 1:\n");
    printf("Nomor Perjalanan: %d\n", bis1.nomorPerjalanan);
    printf("Jurusan: %s\n", bis1.namaperusahaan);
    printf("Jurusan: %s\n", bis1.Jurusan);
    printf("Jam Keberangkatan: %s\n\n", bis1.jamKeberangkatan);

    printf("Rute Bis 2:\n");
    printf("Nomor Perjalanan: %d\n", bis2.nomorPerjalanan);
    printf("Jurusan: %s\n", bis2.namaperusahaan);
    printf("Jurusan: %s\n", bis2.Jurusan);
    printf("Jam Keberangkatan: %s\n", bis2.jamKeberangkatan);

    return 0;
}

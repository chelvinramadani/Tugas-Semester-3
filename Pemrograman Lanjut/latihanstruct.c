#include <stdio.h>
#include <string.h>

struct RuteKA
{
    int nomerPerjalanan;
    char *nama;
    char *jurusan;
    char *keberangkatan;
} KA1;

int main()
{
    KA1.nomerPerjalanan = 1;
    KA1.nama = "Argo Bromo Anggrek";
    KA1.jurusan = "Surabaya - Jakarta";
    KA1.keberangkatan = "08:10 AM";

    printf("Rute KA 1:\n");
    printf("Nomer KA: %d\n", KA1.nomerPerjalanan);
    printf("Nama KA: %s\n", KA1.nama);
    printf("Jurusan: %s\n", KA1.jurusan);
    printf("Jam Keberangkatan: %s\n\n", KA1.keberangkatan);

    return 0;
}
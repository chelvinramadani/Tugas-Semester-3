#include <stdio.h>
#include <math.h>

int main()
{
    // Deklarasi variabel
    double b = 2600.0;              // rata-rata sampel
    double hipotesis_mean = 2500.0; // hipotesis mean
    double Sb = 150.0;              // simpangan baku sampel
    double variansi = 22500.0;      // variansi sampel
    int n = 15;                     // ukuran sampel
    double t_kritis = 2.145;        // nilai t kritis untuk α = 0.05 dan df = 14
    double t_hitung;

    // Menghitung nilai t-hitung
    t_hitung = (b - hipotesis_mean) / (sqrt(variansi) / sqrt(n));

    // Output hasil perhitungan
    printf("Data Uji:\n");
    printf("Rata-rata sampel (b)       : %.2f\n", b);
    printf("Hipotesis mean             : %.2f\n", hipotesis_mean);
    printf("Simpangan baku sampel (Sb) : %.2f\n", Sb);
    printf("Variansi sampel            : %.2f\n", variansi);
    printf("Ukuran sampel (n)          : %d\n", n);
    printf("Nilai t hitung             : %.2f\n", t_hitung);
    printf("Nilai t kritis             : %.3f\n\n", t_kritis);

    // Pengujian hipotesis
    if (fabs(t_hitung) > t_kritis)
    {
        printf("Kesimpulan: H0 ditolak, rata-rata konsumsi kalori harian berbeda dari 2500 kkal.\n");
    }
    else
    {
        printf("Kesimpulan: H0 diterima, rata-rata konsumsi kalori harian tidak berbeda dari 2500 kkal.\n");
    }

    return 0;
}
#include <stdio.h>
#include <math.h>

// Fungsi untuk menghitung rata-rata array
double calculateMean(double data[], int n)
{
    double sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += data[i];
    }
    return sum / n;
}

// Fungsi untuk menghitung koefisien regresi (slope dan intercept)
void linearRegression(double x1[], double x2[], double y[], int n, double *b0, double *b1, double *b2)
{
    double x1_mean = calculateMean(x1, n);
    double x2_mean = calculateMean(x2, n);
    double y_mean = calculateMean(y, n);

    double numerator_b1 = 0, numerator_b2 = 0, denominator = 0;

    for (int i = 0; i < n; i++)
    {
        numerator_b1 += (x1[i] - x1_mean) * (y[i] - y_mean);
        numerator_b2 += (x2[i] - x2_mean) * (y[i] - y_mean);
        denominator += (x1[i] - x1_mean) * (x1[i] - x1_mean) + (x2[i] - x2_mean) * (x2[i] - x2_mean);
    }

    *b1 = numerator_b1 / denominator;
    *b2 = numerator_b2 / denominator;
    *b0 = y_mean - (*b1 * x1_mean + *b2 * x2_mean);
}

// Fungsi untuk menghitung MAPE
double calculateMAPE(double actual[], double predicted[], int n)
{
    double mape = 0;
    for (int i = 0; i < n; i++)
    {
        mape += fabs((actual[i] - predicted[i]) / actual[i]);
    }
    return (mape / n) * 100;
}

// Fungsi untuk menampilkan data historis
void displayHistoricalData(int years[], double goldPrices[], double predictedPrices[], int n)
{
    printf("\nData Historis:\n");
    printf("Tahun\tHarga Aktual\tHarga Prediksi\tMAPE\n");
    printf("====================================================\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t%.2f\t%.2f\t%.2f%%\n", years[i], goldPrices[i], predictedPrices[i],
               fabs((goldPrices[i] - predictedPrices[i]) / goldPrices[i]) * 100);
    }
    printf("====================================================\n");
}

int main()
{
    // Data input historis
    int years[] = {2020, 2021, 2022, 2023, 2024};
    double goldPrices[] = {1065000, 981000, 1036000, 1145000, 1427000};
    double oilPrices[] = {41.67, 50.45, 123.64, 73.70, 81.92};
    double exchangeRates[] = {14844, 14069, 14407, 15510, 16170};
    int n = 5;

    // Variabel untuk koefisien regresi
    double b0, b1, b2;

    // Menghitung regresi linear
    linearRegression(oilPrices, exchangeRates, goldPrices, n, &b0, &b1, &b2);

    // Menampilkan hasil koefisien regresi
    printf("Hasil Perhitungan Regresi Linear:\n");
    printf("Intercept (b0): %.2f\n", b0);
    printf("Slope (b1 - Harga Minyak): %.2f\n", b1);
    printf("Slope (b2 - Kurs): %.2f\n", b2);

    // Menampilkan persamaan regresi linear
    printf("\nPersamaan Regresi Linear:\n");
    printf("Harga Emas (y) = %.2f + %.2f * (Harga Minyak) + %.2f * (Kurs USD/IDR)\n", b0, b1, b2);

    // Menghitung prediksi dan MAPE untuk data historis
    double predictedPrices[n];
    for (int i = 0; i < n; i++)
    {
        predictedPrices[i] = b0 + b1 * oilPrices[i] + b2 * exchangeRates[i];
    }
    double mape = calculateMAPE(goldPrices, predictedPrices, n);

    int choice;
    do
    {
        printf("\nMenu Prediksi Harga Emas\n");
        printf("1. Lihat Data Historis\n");
        printf("2. Prediksi Harga Emas Baru\n");
        printf("3. Keluar\n");
        printf("Pilihan Anda: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            displayHistoricalData(years, goldPrices, predictedPrices, n);
            printf("Total MAPE: %.2f%%\n", mape);
            break;

        case 2:
        {
            int tahun;
            double hargaMinyak, kurs;

            printf("\nMasukkan data baru:\n");
            printf("Tahun: ");
            scanf("%d", &tahun);
            printf("Harga Minyak (USD): ");
            scanf("%lf", &hargaMinyak);
            printf("Kurs USD/IDR: ");
            scanf("%lf", &kurs);

            double prediksi = b0 + b1 * hargaMinyak + b2 * kurs;

            printf("\nHasil Prediksi:\n");
            printf("====================================================\n");
            printf("Tahun: %d\n", tahun);
            printf("Harga Minyak: %.2f USD\n", hargaMinyak);
            printf("Kurs USD/IDR: %.2f\n", kurs);
            printf("Prediksi Harga Emas: Rp %.2f\n", prediksi);
            printf("====================================================\n");

            break;
        }

        case 3:
            printf("Terima kasih telah menggunakan program ini!\n");
            break;

        default:
            printf("Pilihan tidak valid. Silakan coba lagi.\n");
        }
    } while (choice != 3);

    return 0;
}

#include <stdio.h>
#include <math.h>

int main()
{
    // Data historis
    double x1[] = {71550, 76780, 75670, 51560, 61060};     // Harga crude oil
    double x2[] = {14920, 14665, 14990, 13872, 14133};     // Nilai tukar USD/IDR
    double y[] = {295027, 291746, 295107, 217010, 210561}; // Harga emas
    int n = 5;                                             // Jumlah data

    // Menghitung koefisien regresi b1, b2, dan b0
    double sumX1 = 0.0, sumX2 = 0.0, sumY = 0.0;
    double sumX1Y = 0.0, sumX2Y = 0.0, sumX1Squared = 0.0, sumX2Squared = 0.0;

    for (int i = 0; i < n; i++)
    {
        sumX1 += x1[i];
        sumX2 += x2[i];
        sumY += y[i];
        sumX1Y += x1[i] * y[i];
        sumX2Y += x2[i] * y[i];
        sumX1Squared += x1[i] * x1[i];
        sumX2Squared += x2[i] * x2[i];
    }

    double b1 = (n * sumX1Y - sumX1 * sumY) / (n * sumX1Squared - sumX1 * sumX1);
    double b2 = (n * sumX2Y - sumX2 * sumY) / (n * sumX2Squared - sumX2 * sumX2);
    double b0 = (sumY - b1 * sumX1 - b2 * sumX2) / n;

    // Menampilkan hasil koefisien
    printf("Koefisien regresi:\n");
    printf("b0 (intersep): %.2lf\n", b0);
    printf("b1 (koefisien X1): %.2lf\n", b1);
    printf("b2 (koefisien X2): %.2lf\n\n", b2);

    // Menampilkan persamaan regresi linear
    printf("Persamaan regresi linear:\n");
    printf("Y = %.2lf + %.2lf*X1 + %.2lf*X2\n\n", b0, b1, b2);

    // Prediksi harga emas berdasarkan input baru
    double newX1, newX2;
    printf("Masukkan harga crude oil baru (X1): ");
    scanf("%lf", &newX1);
    printf("Masukkan nilai tukar USD/IDR baru (X2): ");
    scanf("%lf", &newX2);

    double predictedY = b0 + b1 * newX1 + b2 * newX2;
    printf("Prediksi harga emas: %.2lf\n\n", predictedY);

    // Menghitung MAPE
    double totalError = 0.0;
    for (int i = 0; i < n; i++)
    {
        double predicted = b0 + b1 * x1[i] + b2 * x2[i];
        double error = fabs((y[i] - predicted) / y[i]) * 100; // Error dalam persen
        totalError += error;
    }

    double mape = totalError / n;
    printf("Mean Absolute Percentage Error (MAPE): %.2lf%%\n", mape);

    return 0;
}

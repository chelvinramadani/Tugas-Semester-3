#include <stdio.h>
#include <math.h>

int main()
{
    double mean = 170.0;
    double std_dev = 5.0;
    int n = 30;
    double z = 1.96;

    // Menghitung margin of error
    double margin_of_error = z * (std_dev / sqrt(n));

    // Menghitung batas bawah dan batas atas selang kepercayaan
    double lower_bound = mean - margin_of_error;
    double upper_bound = mean + margin_of_error;

    printf("Rata-rata sampel: %.2f\n", mean);
    printf("Simpangan baku sampel: %.2f\n", std_dev);
    printf("Selang kepercayaan 95%% untuk rata-rata: %.2f < µ < %.2f\n", lower_bound, upper_bound);

    return 0;
}
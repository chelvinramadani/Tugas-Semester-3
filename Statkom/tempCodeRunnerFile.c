#include <stdio.h>
#include <math.h>

// Struktur data untuk menyimpan informasi dataset
typedef struct {
    float gold_price;   // Harga emas (Y)
    float oil_price;    // Harga minyak bumi (X1)
    float usd_idr;      // Nilai tukar USD/IDR (X2)
} DataPoint;

// Fungsi untuk normalisasi data
void normalizeData(DataPoint data[], int n, float *min_gold, float *max_gold, float *min_oil, float *max_oil, float *min_usd, float *max_usd) {
    *min_gold = *max_gold = data[0].gold_price;
    *min_oil = *max_oil = data[0].oil_price;
    *min_usd = *max_usd = data[0].usd_idr;

    for (int i = 1; i < n; i++) {
        if (data[i].gold_price < *min_gold) *min_gold = data[i].gold_price;
        if (data[i].gold_price > *max_gold) *max_gold = data[i].gold_price;
        if (data[i].oil_price < *min_oil) *min_oil = data[i].oil_price;
        if (data[i].oil_price > *max_oil) *max_oil = data[i].oil_price;
        if (data[i].usd_idr < *min_usd) *min_usd = data[i].usd_idr;
        if (data[i].usd_idr > *max_usd) *max_usd = data[i].usd_idr;
    }

    for (int i = 0; i < n; i++) {
        data[i].gold_price = (data[i].gold_price - *min_gold) / (*max_gold - *min_gold);
        data[i].oil_price = (data[i].oil_price - *min_oil) / (*max_oil - *min_oil);
        data[i].usd_idr = (data[i].usd_idr - *min_usd) / (*max_usd - *min_usd);
    }
}

// Fungsi untuk denormalisasi hasil prediksi
float denormalizeGoldPrice(float normalized, float min_gold, float max_gold) {
    return normalized * (max_gold - min_gold) + min_gold;
}

// Fungsi untuk menghitung parameter regresi linear
void calculateLinearRegression(DataPoint data[], int n, float *a, float *b1, float *b2) {
    float sum_y = 0, sum_x1 = 0, sum_x2 = 0;
    float sum_x1x1 = 0, sum_x2x2 = 0, sum_x1x2 = 0;
    float sum_x1y = 0, sum_x2y = 0;

    for (int i = 0; i < n; i++) {
        sum_y += data[i].gold_price;
        sum_x1 += data[i].oil_price;
        sum_x2 += data[i].usd_idr;
        sum_x1x1 += data[i].oil_price * data[i].oil_price;
        sum_x2x2 += data[i].usd_idr * data[i].usd_idr;
        sum_x1x2 += data[i].oil_price * data[i].usd_idr;
        sum_x1y += data[i].oil_price * data[i].gold_price;
        sum_x2y += data[i].usd_idr * data[i].gold_price;
    }

    float denominator = n * sum_x1x1 * sum_x2x2 + 2 * sum_x1 * sum_x2 * sum_x1x2
                        - sum_x1 * sum_x1 * sum_x2x2 - sum_x2 * sum_x2 * sum_x1x1
                        - n * sum_x1x2 * sum_x1x2;

    if (denominator == 0) {
        printf("Error: Denominator is zero. Check your dataset.\n");
        *a = *b1 = *b2 = 0;
        return;
    }

    *a = (sum_y * sum_x1x1 * sum_x2x2 + sum_x1 * sum_x2 * sum_x2y
          + sum_x2 * sum_x1 * sum_x1y - sum_y * sum_x1x2 * sum_x1x2
          - sum_x1 * sum_x1 * sum_x2y - sum_x2 * sum_x2 * sum_x1y) / denominator;

    *b1 = (n * sum_x1y * sum_x2x2 + sum_x2 * sum_x2y * sum_x1
           + sum_x1x2 * sum_y * sum_x2 - n * sum_x1x2 * sum_x2y
           - sum_y * sum_x1x2 * sum_x2 - sum_x1 * sum_x2 * sum_x2y) / denominator;

    *b2 = (n * sum_x2y * sum_x1x1 + sum_x1 * sum_x1y * sum_x2
           + sum_x1x2 * sum_y * sum_x1 - n * sum_x1x2 * sum_x1y
           - sum_y * sum_x1x2 * sum_x1 - sum_x2 * sum_x1 * sum_x1y) / denominator;

    printf("Calculated Parameters:\n");
    printf("a (Intercept): %.2f\n", *a);
    printf("b1 (Oil Price Coefficient): %.2f\n", *b1);
    printf("b2 (USD/IDR Coefficient): %.2f\n", *b2);
}

// Fungsi untuk mengevaluasi model
void evaluateModel(DataPoint data[], int n, float a, float b1, float b2) {
    float mae = 0, rmse = 0;

    for (int i = 0; i < n; i++) {
        float predicted = a + b1 * data[i].oil_price + b2 * data[i].usd_idr;
        float error = data[i].gold_price - predicted;
        mae += fabs(error);
        rmse += error * error;
    }

    mae /= n;
    rmse = sqrt(rmse / n);

    printf("\nModel Evaluation:\n");
    printf("Mean Absolute Error (MAE): %.2f\n", mae);
    printf("Root Mean Square Error (RMSE): %.2f\n", rmse);
}

// Fungsi untuk membuat prediksi
float predict(float a, float b1, float b2, float oil_price, float usd_idr) {
    return a + b1 * oil_price + b2 * usd_idr;
}

int main() {
    DataPoint data[] = {
        {295027, 71.550, 14920},
        {291746, 76.780, 14665},
        {295107, 75.670, 14990},
        {217010, 51.560, 13650},
        {210561, 61.060, 13880}
    };

    int n = sizeof(data) / sizeof(data[0]);
    float min_gold, max_gold, min_oil, max_oil, min_usd, max_usd;

    // Normalisasi dataset
    normalizeData(data, n, &min_gold, &max_gold, &min_oil, &max_oil, &min_usd, &max_usd);

    // Hitung parameter regresi
    float a, b1, b2;
    calculateLinearRegression(data, n, &a, &b1, &b2);

    // Evaluasi model
    evaluateModel(data, n, a, b1, b2);

    // Prediksi harga emas baru
    float new_oil_price, new_usd_idr;
    printf("\nEnter new Oil Price: ");
    scanf("%f", &new_oil_price);
    printf("Enter new USD/IDR: ");
    scanf("%f", &new_usd_idr);

    // Normalisasi input
    new_oil_price = (new_oil_price - min_oil) / (max_oil - min_oil);
    new_usd_idr = (new_usd_idr - min_usd) / (max_usd - min_usd);

    // Prediksi dan denormalisasi hasil
    float predicted_price = predict(a, b1, b2, new_oil_price, new_usd_idr);
    predicted_price = denormalizeGoldPrice(predicted_price, min_gold, max_gold);

    printf("Predicted Gold Price: Rp %.2f\n", predicted_price);

    return 0;
}

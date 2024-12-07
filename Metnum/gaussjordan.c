#include <stdio.h>

#define ROWS 4
#define COLS 5

void gaussJordan(float matrix[ROWS][COLS])
{
    for (int i = 0; i < ROWS; i++)
    {
        // Membuat elemen diagonal menjadi 1
        if (matrix[i][i] != 0)
        {
            float divisor = matrix[i][i];
            for (int j = 0; j < COLS; j++)
            {
                matrix[i][j] /= divisor;
            }
        }

        // Mengeliminasi elemen di kolom i pada baris lainnya
        for (int k = 0; k < ROWS; k++)
        {
            if (k != i)
            {
                float factor = matrix[k][i];
                for (int j = 0; j < COLS; j++)
                {
                    matrix[k][j] -= factor * matrix[i][j];
                }
            }
        }
    }
}

void printMatrix(float matrix[ROWS][COLS])
{
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            printf("%8.0f ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    // Matriks augmented dari sistem persamaan
    float matrix[ROWS][COLS] = {
        {1, -1, 2, -1, -1},
        {2, 1, -2, -2, -2},
        {-1, 2, -4, 1, 1},
        {3, 0, 0, -3, -3}};

    printf("Matriks augmented awal:\n");
    printMatrix(matrix);

    // Menyelesaikan matriks menggunakan metode Gauss-Jordan
    gaussJordan(matrix);

    printf("\nMatriks setelah eliminasi Gauss-Jordan:\n");
    printMatrix(matrix);

    return 0;
}

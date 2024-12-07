#include <stdio.h>

int faktorial(int x)
{
    if (x == 1)
        return x;
    else
        return x * faktorial(x - 1);
}

int main()
{
    int N;
    printf("Masukkan Bilangan = ");
    scanf("%d", &N);
    printf("Hasil %d! = %d\n", N, faktorial(N));
    return 0;
}
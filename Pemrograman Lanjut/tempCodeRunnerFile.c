#include <stdio.h>

int main (){

    int angka;

    printf("Masukkan Angka :");
    scanf("%d", &angka);

    if(angka %2 == 0){
        printf("angka %d adalah genap.\n", angka);
    }
    else{
        printf("angka %d adalah ganjil\n", angka);
    }

    return 0;
};
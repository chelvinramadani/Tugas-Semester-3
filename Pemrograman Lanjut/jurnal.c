#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// validasi email
bool validateEmail(char *email){
    char *domain = strstr(email, "@");
    if (domain && strlen(domain)> 4){
        if (strstr(domain, "ac.id")){
            return true;
        }
    }
    return false;
}

void getInput(char *judul, char *namaPenulis, char *afiliasi, char *email, char *abstrak, char *kataKunci){
    printf("Masukkan Judul Jurnal : ");
    fgets(judul, 256, stdin);
    judul[strcspn(judul, "\n")] = '\0';

    printf("Masukkan Nama Penulis (Maksimal 3 penulis) : ");
    fgets(namaPenulis, 256, stdin);
    namaPenulis[strcspn(namaPenulis, "\n")] = '\0';

    printf("Masukkan Afiliasi : ");
    fgets(afiliasi, 256, stdin);
    afiliasi[strcspn(afiliasi, "\n")] = '\0';

    bool valid = false;
    while(!valid){
        printf("Masukkan email dengan domain ac.id : ");
        fgets(email, 256, stdin);
        email[strcspn(email, "\n")] = '\0';

        valid = validateEmail(email);
        if(!valid){
            printf("Email tidal valid, gunakan email berdomain ac.id : ");
        }
    }

    printf("Masukkan Abstrak (maksimal 200 kata) : ");
    fgets(abstrak, 1024, stdin);
    abstrak[strcspn(abstrak, "\n")] = '\0';

    printf("Masukkan kata kunci (3-5 kata kunci) : ");
    fgets(kataKunci, 256, stdin);
    kataKunci[strcspn(kataKunci, "\n")] = '\0';

}

void generateJournal(char *judul, char *namaPenulis, char *afiliasi, char *email, char *abstrak, char *kataKunci, char*result){
    sprintf(result, "Judul: %s\nNama Penulis: %s\nAfiliasi: %s\nEmail: %s\nAbstrak: %s\nKata Kunci: %s\n",
    judul, namaPenulis, afiliasi, email, abstrak, kataKunci);
}

int main(){
    char judul[256], namaPenulis[256], afiliasi[256], email[256], abstrak[1024], kataKunci[256], result[2048];
    
    getInput(judul, namaPenulis, afiliasi, email, abstrak, kataKunci);

    generateJournal(judul, namaPenulis, afiliasi, email, abstrak, kataKunci, result);

    printf("\n----- Hasil Jurnal -----\n");
    printf("%s\n", result);

    return 0;
}
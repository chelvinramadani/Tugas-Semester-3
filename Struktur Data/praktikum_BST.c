#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Mahasiswa
{
    int NIM;
    char nama[50];
    char Prodi[100];
    struct Mahasiswa *left;
    struct Mahasiswa *right;
};

// Membuat node Mahasiswa baru
struct Mahasiswa *createMahasiswa(int NIM, char nama[], char Prodi[])
{
    struct Mahasiswa *mahasiswabaru = (struct Mahasiswa *)malloc(sizeof(struct Mahasiswa));
    mahasiswabaru->NIM = NIM;
    strcpy(mahasiswabaru->nama, nama);
    strcpy(mahasiswabaru->Prodi, Prodi);
    mahasiswabaru->left = NULL;
    mahasiswabaru->right = NULL;
    return mahasiswabaru;
}

// Fungsi menambahkan Mahasiswa ke BST
struct Mahasiswa *insertBST(struct Mahasiswa *root, int NIM, char nama[], char Prodi[])
{
    if (root == NULL)
        return createMahasiswa(NIM, nama, Prodi);

    if (NIM < root->NIM)
        root->left = insertBST(root->left, NIM, nama, Prodi);
    else if (NIM > root->NIM)
        root->right = insertBST(root->right, NIM, nama, Prodi);

    return root;
}

// Fungsi untuk mencari node terkecil pada subtree
struct Mahasiswa *minValueNode(struct Mahasiswa *node)
{
    struct Mahasiswa *current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}

// Fungsi Mencari Mahasiswa berdasarkan NPM
struct Mahasiswa *searchMahasiswa(struct Mahasiswa *root, int NIM)
{
    if (root == NULL || root->NIM == NIM)
        return root;

    if (NIM < root->NIM)
        return searchMahasiswa(root->left, NIM);

    return searchMahasiswa(root->right, NIM);
}

// Fungsi menghapus Mahasiswa
struct Mahasiswa *deleteMahasiswa(struct Mahasiswa *root, int NIM)
{
    if (root == NULL)
        return root;

    if (NIM < root->NIM)
        root->left = deleteMahasiswa(root->left, NIM);
    else if (NIM > root->NIM)
        root->right = deleteMahasiswa(root->right, NIM);
    else
    {
        // Node satu atau tanpa anak
        if ((root->left == NULL) || (root->right == NULL))
        {
            struct Mahasiswa *temp = root->left ? root->left : root->right;

            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else
                *root = *temp;

            free(temp);
        }
        else
        {
            // Node dua anak
            struct Mahasiswa *temp = minValueNode(root->right);
            root->NIM = temp->NIM;
            strcpy(root->nama, temp->nama);
            strcpy(root->Prodi, temp->Prodi);
            root->right = deleteMahasiswa(root->right, temp->NIM);
        }
    }
    return root;
}

// Fungsi menampilkan data Mahasiswa
void displayMahasiswa(struct Mahasiswa *root)
{
    if (root != NULL)
    {
        displayMahasiswa(root->left);
        printf("| %-5d | %-22s | %-22s |\n", root->NIM, root->nama, root->Prodi);
        displayMahasiswa(root->right);
    }
}

// Fungsi utama
int main()
{
    struct Mahasiswa *root = NULL;

    int choice, NIM;
    char nama[50], Prodi[100];

    do
    {
        printf("\nMenu\n");
        printf("1. Tambah Mahasiswa\n");
        printf("2. Tampilkan Mahasiswa\n");
        printf("3. Cari Mahasiswa\n");
        printf("4. Hapus Mahasiswa\n");
        printf("5. Keluar\n");
        printf("Pilih: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Masukkan NIM: ");
            scanf("%d", &NIM);
            if (searchMahasiswa(root, NIM) != NULL)
            {
                printf("NIM %d sudah terdaftar\n", NIM);
                break;
            }

            getchar();
            printf("Masukkan Nama: ");
            fgets(nama, sizeof(nama), stdin);
            nama[strcspn(nama, "\n")] = 0;

            printf("Masukkan Prodi: ");
            fgets(Prodi, sizeof(Prodi), stdin);
            Prodi[strcspn(Prodi, "\n")] = 0;

            root = insertBST(root, NIM, nama, Prodi);
            printf("Mahasiswa berhasil ditambahkan.\n");
            break;
        case 2:
            printf("Data Mahasiswa:\n");
            printf("-----------------------------------------------------------\n");
            printf("|  NIM  |          Nama          |            Prodi       |\n");
            printf("-----------------------------------------------------------\n");
            displayMahasiswa(root);
            printf("-----------------------------------------------------------\n");
            break;
        case 3:
            printf("Masukkan NIM: ");
            scanf("%d", &NIM);
            struct Mahasiswa *found = searchMahasiswa(root, NIM);
            if (found == NULL)
                printf("Mahasiswa tidak ditemukan.\n");
            else
                printf("Mahasiswa ditemukan: NIM: %d, Nama: %s, Prodi: %s\n",
                       found->NIM, found->nama, found->Prodi);
            break;
        case 4:
            printf("Masukkan NIM yang akan dihapus: ");
            scanf("%d", &NIM);
            if (searchMahasiswa(root, NIM) == NULL)
            {
                printf("Mahasiswa dengan NIM %d tidak ditemukan.\n", NIM);
            }
            else
            {
                root = deleteMahasiswa(root, NIM);
                printf("Mahasiswa dengan NIM %d berhasil dihapus.\n", NIM);
            }
            break;
        case 5:
            printf("Keluar dari program..\n");
            break;
        default:
            printf("Pilihan tidak valid\n");
        }
    } while (choice != 5);

    return 0;
}
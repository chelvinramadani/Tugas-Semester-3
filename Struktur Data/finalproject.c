#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Pasien
{
    int NRM;
    char nama[50];
    int umur;
    char alamat[100];
    int height;
    struct Pasien *left;
    struct Pasien *right;
};

// Fungsi mendapatkan tinggi node
int getHeight(struct Pasien *node)
{
    if (node == NULL)
        return 0;
    return node->height;
}

// Fungsi menghitung nilai maksimum
int max(int a, int b)
{
    return (a > b) ? a : b;
}

// Membuat node pasien baru
struct Pasien *createPasien(int NRM, char nama[], int umur, char alamat[])
{
    struct Pasien *pasienbaru = (struct Pasien *)malloc(sizeof(struct Pasien));
    pasienbaru->NRM = NRM;
    strcpy(pasienbaru->nama, nama);
    pasienbaru->umur = umur;
    strcpy(pasienbaru->alamat, alamat);
    pasienbaru->height = 1;
    pasienbaru->left = NULL;
    pasienbaru->right = NULL;
    return pasienbaru;
}

// Fungsi rotasi kanan
struct Pasien *rotateRight(struct Pasien *y)
{
    struct Pasien *x = y->left;
    struct Pasien *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}

// Fungsi rotasi kiri
struct Pasien *rotateLeft(struct Pasien *x)
{
    struct Pasien *y = x->right;
    struct Pasien *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}

// Fungsi mendapatkan faktor keseimbangan
int getBalance(struct Pasien *node)
{
    if (node == NULL)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}

// Fungsi menambahkan pasien ke AVL
struct Pasien *insertPasien(struct Pasien *root, int NRM, char nama[], int umur, char alamat[])
{
    if (root == NULL)
        return createPasien(NRM, nama, umur, alamat);

    if (NRM < root->NRM)
        root->left = insertPasien(root->left, NRM, nama, umur, alamat);
    else if (NRM > root->NRM)
        root->right = insertPasien(root->right, NRM, nama, umur, alamat);
    else
        return root; // NRM sudah ada

    // Update tinggi node
    root->height = 1 + max(getHeight(root->left), getHeight(root->right));

    // Periksa keseimbangan
    int balance = getBalance(root);

    if (balance > 1 && NRM < root->left->NRM)
        return rotateRight(root);

    if (balance < -1 && NRM > root->right->NRM)
        return rotateLeft(root);

    if (balance > 1 && NRM > root->left->NRM)
    {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    if (balance < -1 && NRM > root->right->NRM)
    {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

// Fungsi Mencari pasien berdasarkan NRM
struct Pasien *searchPasien(struct Pasien *root, int NRM)
{
    if (root == NULL || root->NRM == NRM)
        return root;

    if (NRM < root->NRM)
        return searchPasien(root->left, NRM);

    return searchPasien(root->right, NRM);
}

// Fungsi untuk mencari node terkecil
struct Pasien *minValueNode(struct Pasien *node)
{
    struct Pasien *current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}

// Fungsi menghapus pasien
struct Pasien *deletePasien(struct Pasien *root, int NRM)
{
    if (root == NULL)
        return root;

    if (NRM < root->NRM)
        root->left = deletePasien(root->left, NRM);
    else if (NRM > root->NRM)
        root->right = deletePasien(root->right, NRM);
    else
    {
        // Node satu atau tanpa anak
        if ((root->left == NULL) || (root->right == NULL))
        {
            struct Pasien *temp = root->left ? root->left : root->right;

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
            struct Pasien *temp = minValueNode(root->right);

            root->NRM = temp->NRM;
            strcpy(root->nama, temp->nama);
            root->umur = temp->umur;
            strcpy(root->alamat, temp->alamat);

            root->right = deletePasien(root->right, temp->NRM);
        }
    }

    if (root == NULL)
        return root;

    // Update tinggi node
    root->height = 1 + max(getHeight(root->left), getHeight(root->right));

    // Periksa keseimbangan
    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0)
        return rotateRight(root);

    if (balance > 1 && getBalance(root->left) < 0)
    {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    if (balance < -1 && getBalance(root->right) <= 0)
        return rotateLeft(root);

    if (balance < -1 && getBalance(root->right) < 0)
    {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

// Fungsi menampilkan data pasien
void displayPasien(struct Pasien *root)
{
    if (root != NULL)
    {
        displayPasien(root->left);
        printf("NRM : %d, Nama : %s, Umur : %d, Alamat : %s\n",
               root->NRM, root->nama, root->umur, root->alamat);
        displayPasien(root->right);
    }
}

// Fungsi utama
int main()
{
    struct Pasien *root = NULL;
    int choice, NRM, umur;
    char nama[50], alamat[100];

    do
    {
        printf("\n=== Selamat Datang di Pelayanan Puskesmas===");
        printf("\n=== Menu===\n");
        printf("1. Tambah Pasien\n");
        printf("2. Tampilkan Pasien\n");
        printf("3. Cari Pasien\n");
        printf("4. Hapus Pasien\n");
        printf("5. Keluar\n");
        printf("Pilih: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Masukkan NRM : ");
            scanf("%d", &NRM);
            if (searchPasien(root, NRM) != NULL)
            {
                printf("NRM %d sudah terdaftar\n", NRM);
                break;
            }

            getchar();
            printf("Masukkan Nama : ");
            fgets(nama, sizeof(nama), stdin);
            nama[strcspn(nama, "\n")] = 0;
            printf("Masukkan Usia : ");
            scanf("%d", &umur);
            getchar();
            printf("Masukkan Alamat : ");
            fgets(alamat, sizeof(alamat), stdin);
            alamat[strcspn(alamat, "\n")] = 0;
            root = insertPasien(root, NRM, nama, umur, alamat);
            printf("Pasien berhasil ditambahkan.\n");
            break;
        case 2:
            printf("Data Pasien:\n");
            displayPasien(root);
            break;
        case 3:
            printf("Masukkan NRM: ");
            scanf("%d", &NRM);
            struct Pasien *found = searchPasien(root, NRM);
            if (found)
                printf("Pasen ditemukan: NRM: %d, Nama: %s, Umur: %d, Alamat: %s\n",
                       found->NRM, found->nama, found->umur, found->alamat);
            else
                printf("Pasien tidak ditemukan.\n");
            break;
        case 4:
            printf("Masukkan NRM: ");
            scanf("%d", &NRM);
            root = deletePasien(root, NRM);
            printf("Pasien berhasil dihapus.\n");
            break;
        case 5:
            printf("Keluar dari program\n");
            break;
        default:
            printf("Pilihan tidak valid\n");
        }
    } while (choice != 5);

    return 0;
}
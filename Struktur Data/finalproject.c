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
struct Pasien *insertAVL(struct Pasien *root, int NRM, char nama[], int umur, char alamat[])
{
    if (root == NULL)
        return createPasien(NRM, nama, umur, alamat);

    if (NRM < root->NRM)
        root->left = insertAVL(root->left, NRM, nama, umur, alamat);
    else if (NRM > root->NRM)
        root->right = insertAVL(root->right, NRM, nama, umur, alamat);
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

// Fungsi menambahkan pasien ke BST
struct Pasien *insertBST(struct Pasien *root, int NRM, char nama[], int umur, char alamat[])
{
    if (root == NULL)
        return createPasien(NRM, nama, umur, alamat);

    if (NRM < root->NRM)
        root->left = insertBST(root->left, NRM, nama, umur, alamat);
    else if (NRM > root->NRM)
        root->right = insertBST(root->right, NRM, nama, umur, alamat);

    return root;
}

// Fungsi untuk mencari node terkecil pada subtree
struct Pasien *minValueNode(struct Pasien *node)
{
    struct Pasien *current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
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

// Fungsi menghapus pasien
struct Pasien *deletePasien(struct Pasien *root, int NRM, int isAVL)
{
    if (root == NULL)
        return root;

    if (NRM < root->NRM)
        root->left = deletePasien(root->left, NRM, isAVL);
    else if (NRM > root->NRM)
        root->right = deletePasien(root->right, NRM, isAVL);
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
            root->right = deletePasien(root->right, temp->NRM, isAVL);
        }
    }

    if (root == NULL)
        return root;

    if (isAVL)
    {
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
    }

    return root;
}

// Fungsi menyimpan data ke file
void saveToFile(struct Pasien *root, FILE *file)
{
    if (root != NULL)
    {
        fwrite(root, sizeof(struct Pasien), 1, file);
        saveToFile(root->left, file);
        saveToFile(root->right, file);
    }
}

// Fungsi memuat data
struct Pasien *loadFromFile(FILE *file)
{
    struct Pasien temp, *root = NULL;
    while (fread(&temp, sizeof(struct Pasien), 1, file))
    {
        root = insertAVL(root, temp.NRM, temp.nama, temp.umur, temp.alamat);
    }
    return root;
}

// Fungsi menampilkan data pasien
void displayPasien(struct Pasien *root)
{
    if (root != NULL)
    {
        displayPasien(root->left);
        printf("| %-5d | %-22s | %-4d | %-30s |\n", root->NRM, root->nama, root->umur, root->alamat);
        displayPasien(root->right);
    }
}

// Fungsi utama
int main()
{
    struct Pasien *root = NULL;
    FILE *file;

    file = fopen("pasien.dat", "rb");
    if (file != NULL)
    {
        root = loadFromFile(file);
        fclose(file);
    }

    int choice, NRM, umur, treeChoice;
    char nama[50], alamat[100];

    printf("\nSelamat Datang di Pelayanan Puskesmas\n");
    printf("Masukkan Pilihan\n");
    printf("1. BST\n");
    printf("2. AVL Tree\n");
    printf("Pilihan :");
    scanf("%d", &treeChoice);

    do
    {

        printf("Menu\n");
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
            if (nama[strcspn(nama, "\n")] == '\n')
                nama[strcspn(nama, "\n")] = 0;

            printf("Masukkan Usia : ");
            while (scanf("%d", &umur) != 1)
            {
                printf("Input tidak valid. Masukkan angka: ");
                while (getchar() != '\n')
                    ;
            }
            getchar();

            printf("Masukkan Alamat : ");
            fgets(alamat, sizeof(alamat), stdin);
            if (alamat[strcspn(alamat, "\n")] == '\n')
                alamat[strcspn(alamat, "\n")] = 0;

            if (treeChoice == 1)
                root = insertBST(root, NRM, nama, umur, alamat);
            else
                root = insertAVL(root, NRM, nama, umur, alamat);
            printf("Pasien berhasil ditambahkan.\n");
            break;
        case 2:
            printf("Data Pasien:\n");
            printf("--------------------------------------------------------------------------\n");
            printf("|  NRM  |          Nama          | Umur |            Alamat              |\n");
            printf("--------------------------------------------------------------------------\n");
            displayPasien(root);
            printf("--------------------------------------------------------------------------\n");
            break;
        case 3:
            printf("Masukkan NRM: ");
            scanf("%d", &NRM);
            struct Pasien *found = searchPasien(root, NRM);
            if (found == NULL)
                printf("Pasien tidak ditemukan.\n");

            else
                printf("Pasien ditemukan: NRM: %d, Nama: %s, Umur: %d, Alamat: %s\n",
                       found->NRM, found->nama, found->umur, found->alamat);
            break;
        case 4:
            printf("Masukkan NRM yang akan dihapus: ");
            scanf("%d", &NRM);
            if (searchPasien(root, NRM) == NULL)
            {
                printf("Pasien dengan NRM %d tidak ditemukan.\n", NRM);
            }
            else
            {
                root = deletePasien(root, NRM, treeChoice == 2);
                printf("Pasien dengan NRM %d berhasil dihapus.\n", NRM);
            }
            break;
        case 5:
            printf("Menyimpan data & Keluar dari program..\n");
            file = fopen("pasien.dat", "wb");
            if (file != NULL)
            {
                saveToFile(root, file);
                fclose(file);
            }
            break;
        default:
            printf("Pilihan tidak valid\n");
        }
    } while (choice != 5);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struktur data pasien
struct Patient
{
    int nrm;               // Nomor Rekam Medis (unik)
    char name[50];         // Nama Pasien
    int age;               // Usia
    char address[100];     // Alamat
    int height;            // Tinggi node AVL
    struct Patient *left;  // Anak kiri
    struct Patient *right; // Anak kanan
};

// Fungsi untuk mendapatkan tinggi node
int getHeight(struct Patient *node)
{
    if (node == NULL)
        return 0;
    return node->height;
}

// Fungsi untuk menghitung nilai maksimum
int max(int a, int b)
{
    return (a > b) ? a : b;
}

// Fungsi untuk membuat node pasien baru
struct Patient *createPatient(int nrm, char name[], int age, char address[])
{
    struct Patient *newPatient = (struct Patient *)malloc(sizeof(struct Patient));
    newPatient->nrm = nrm;
    strcpy(newPatient->name, name);
    newPatient->age = age;
    strcpy(newPatient->address, address);
    newPatient->height = 1; // Tinggi node awal adalah 1
    newPatient->left = NULL;
    newPatient->right = NULL;
    return newPatient;
}

// Fungsi untuk rotasi ke kanan
struct Patient *rotateRight(struct Patient *y)
{
    struct Patient *x = y->left;
    struct Patient *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}

// Fungsi untuk rotasi ke kiri
struct Patient *rotateLeft(struct Patient *x)
{
    struct Patient *y = x->right;
    struct Patient *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}

// Fungsi untuk mendapatkan faktor keseimbangan
int getBalance(struct Patient *node)
{
    if (node == NULL)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}

// Fungsi untuk menambahkan pasien ke AVL Tree
struct Patient *insertPatient(struct Patient *root, int nrm, char name[], int age, char address[])
{
    // Penyisipan BST biasa
    if (root == NULL)
        return createPatient(nrm, name, age, address);

    if (nrm < root->nrm)
        root->left = insertPatient(root->left, nrm, name, age, address);
    else if (nrm > root->nrm)
        root->right = insertPatient(root->right, nrm, name, age, address);
    else
        return root; // NRM sudah ada

    // Update tinggi node
    root->height = 1 + max(getHeight(root->left), getHeight(root->right));

    // Periksa keseimbangan dan lakukan rotasi jika perlu
    int balance = getBalance(root);

    // Left Left Case
    if (balance > 1 && nrm < root->left->nrm)
        return rotateRight(root);

    // Right Right Case
    if (balance < -1 && nrm > root->right->nrm)
        return rotateLeft(root);

    // Left Right Case
    if (balance > 1 && nrm > root->left->nrm)
    {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    // Right Left Case
    if (balance < -1 && nrm < root->right->nrm)
    {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

// Fungsi untuk mencari pasien berdasarkan NRM
struct Patient *searchPatient(struct Patient *root, int nrm)
{
    if (root == NULL || root->nrm == nrm)
        return root;

    if (nrm < root->nrm)
        return searchPatient(root->left, nrm);

    return searchPatient(root->right, nrm);
}

// Fungsi untuk mencari node dengan nilai terkecil (suksesor)
struct Patient *minValueNode(struct Patient *node)
{
    struct Patient *current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}

// Fungsi untuk menghapus pasien dari AVL Tree
struct Patient *deletePatient(struct Patient *root, int nrm)
{
    if (root == NULL)
        return root;

    if (nrm < root->nrm)
        root->left = deletePatient(root->left, nrm);
    else if (nrm > root->nrm)
        root->right = deletePatient(root->right, nrm);
    else
    {
        // Node dengan satu atau tanpa anak
        if ((root->left == NULL) || (root->right == NULL))
        {
            struct Patient *temp = root->left ? root->left : root->right;

            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else
                *root = *temp; // Salin isi node anak

            free(temp);
        }
        else
        {
            // Node dengan dua anak
            struct Patient *temp = minValueNode(root->right);

            root->nrm = temp->nrm;
            strcpy(root->name, temp->name);
            root->age = temp->age;
            strcpy(root->address, temp->address);

            root->right = deletePatient(root->right, temp->nrm);
        }
    }

    if (root == NULL)
        return root;

    // Update tinggi node
    root->height = 1 + max(getHeight(root->left), getHeight(root->right));

    // Periksa keseimbangan dan lakukan rotasi jika perlu
    int balance = getBalance(root);

    // Left Left Case
    if (balance > 1 && getBalance(root->left) >= 0)
        return rotateRight(root);

    // Left Right Case
    if (balance > 1 && getBalance(root->left) < 0)
    {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    // Right Right Case
    if (balance < -1 && getBalance(root->right) <= 0)
        return rotateLeft(root);

    // Right Left Case
    if (balance < -1 && getBalance(root->right) > 0)
    {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

// Fungsi untuk menampilkan data pasien (Inorder Traversal)
void displayPatients(struct Patient *root)
{
    if (root != NULL)
    {
        displayPatients(root->left);
        printf("NRM: %d, Nama: %s, Usia: %d, Alamat: %s\n",
               root->nrm, root->name, root->age, root->address);
        displayPatients(root->right);
    }
}

// Fungsi utama
int main()
{
    struct Patient *root = NULL;
    int choice, nrm, age;
    char name[50], address[100];

    do
    {
        printf("\n=== Selamat Datang di pelayanan Puskesmas ===");
        printf("\n=== Menu ===\n");
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
            printf("Masukkan NRM: ");
            scanf("%d", &nrm);
            printf("Masukkan Nama: ");
            scanf(" %[^\n]", name);
            printf("Masukkan Usia: ");
            scanf("%d", &age);
            printf("Masukkan Alamat: ");
            scanf(" %[^\n]", address);
            root = insertPatient(root, nrm, name, age, address);
            printf("Pasien berhasil ditambahkan.\n");
            break;
        case 2:
            printf("Data Pasien:\n");
            displayPatients(root);
            break;
        case 3:
            printf("Masukkan NRM: ");
            scanf("%d", &nrm);
            struct Patient *found = searchPatient(root, nrm);
            if (found)
                printf("Pasien ditemukan: NRM: %d, Nama: %s, Usia: %d, Alamat: %s\n",
                       found->nrm, found->name, found->age, found->address);
            else
                printf("Pasien tidak ditemukan.\n");
            break;
        case 4:
            printf("Masukkan NRM: ");
            scanf("%d", &nrm);
            root = deletePatient(root, nrm);
            printf("Pasien berhasil dihapus.\n");
            break;
        case 5:
            printf("Keluar dari program.\n");
            break;
        default:
            printf("Pilihan tidak valid.\n");
        }
    } while (choice != 5);

    return 0;
}
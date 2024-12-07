#include <stdio.h>
#include <string.h>
#include <math.h>

#define MAX_MAHASISWA 5

typedef struct
{
    char npm[15];
    char nama[50];
    char prodi[50];
    float ipk;
} Mahasiswa;

void tampilkanMahasiswa(Mahasiswa mhs[], int n)
{
    printf("Data Mahasiswa:\n");
    for (int i = 0; i < n; i++)
    {
        printf("NPM: %s, Nama: %s, Prodi: %s, IPK: %.2f\n",
               mhs[i].npm, mhs[i].nama, mhs[i].prodi, mhs[i].ipk);
    }
}

void merge(Mahasiswa mhs[], int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    Mahasiswa L[n1], R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = mhs[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = mhs[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2)
    {
        if (strcmp(L[i].npm, R[j].npm) <= 0)
        {
            mhs[k] = L[i];
            i++;
        }
        else
        {
            mhs[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        mhs[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        mhs[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(Mahasiswa mhs[], int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;
        mergeSort(mhs, left, mid);
        mergeSort(mhs, mid + 1, right);

        merge(mhs, left, mid, right);
    }
}

int sequentialSearch(Mahasiswa mhs[], int n, const char *npm)
{
    for (int i = 0; i < n; i++)
    {
        if (strcmp(mhs[i].npm, npm) == 0)
        {
            return i;
        }
    }
    return -1;
}

int binarySearch(Mahasiswa mhs[], int n, const char *npm)
{
    int left = 0, right = n - 1;
    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        int cmp = strcmp(mhs[mid].npm, npm);
        if (cmp == 0)
            return mid;
        else if (cmp < 0)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1;
}

int interpolationSearch(Mahasiswa mhs[], int n, const char *npm)
{
    int low = 0, high = n - 1;
    while (low <= high && strcmp(npm, mhs[low].npm) >= 0 && strcmp(npm, mhs[high].npm) <= 0)
    {
        int pos = low + (strcmp(npm, mhs[low].npm) * (high - low)) /
                            (strcmp(mhs[high].npm, mhs[low].npm));

        if (pos < low || pos > high)
            break;

        int cmp = strcmp(mhs[pos].npm, npm);
        if (cmp == 0)
            return pos;
        else if (cmp < 0)
            low = pos + 1;
        else
            high = pos - 1;
    }
    return -1;
}

int jumpSearch(Mahasiswa mhs[], int n, const char *npm)
{
    int step = sqrt(n);
    int prev = 0;

    while (prev < n && strcmp(mhs[step - 1].npm, npm) < 0)
    {
        prev = step;
        step += sqrt(n);
        if (step > n)
            step = n;
    }

    while (prev < n && strcmp(mhs[prev].npm, npm) < 0)
        prev++;

    if (prev < n && strcmp(mhs[prev].npm, npm) == 0)
        return prev;

    return -1;
}

int main()
{
    Mahasiswa mhs[MAX_MAHASISWA] = {
        {"23081010155", "Chelvin", "Informatika", 3.9},
        {"23081010100", "Andi", "Informatika", 3.8},
        {"21081010101", "Yanto", "Informatika", 3.75},
        {"21011010110", "Hana", "Ekonomi", 4.0},
        {"23071010001", "Fauzan", "Hukum", 3.85}};

    printf("Data sebelum sorting: \n");
    tampilkanMahasiswa(mhs, MAX_MAHASISWA);

    mergeSort(mhs, 0, MAX_MAHASISWA - 1);

    printf("\nData setelah merge sort NPM :\n");
    tampilkanMahasiswa(mhs, MAX_MAHASISWA);

    char cariNPM[15];
    printf("\nMasukkan NPM yang dicari: ");
    scanf("%s", cariNPM);

    // sequential search
    int idx = sequentialSearch(mhs, MAX_MAHASISWA, cariNPM);
    if (idx != -1)
        printf("Sequential Search: NPM %s ditemukan di index %d (Nama: %s).\n", cariNPM, idx, mhs[idx].nama);
    else
        printf("Sequential Search: NPM %s tidak ditemukan.\n", cariNPM);

    // binary search
    idx = binarySearch(mhs, MAX_MAHASISWA, cariNPM);
    if (idx != -1)
        printf("Binary Search: NPM %s ditemukan di index %d (Nama: %s).\n", cariNPM, idx, mhs[idx].nama);
    else
        printf("Binary Search: NPM %s tidak ditemukan.\n", cariNPM);

    // interpolation search
    idx = interpolationSearch(mhs, MAX_MAHASISWA, cariNPM);
    if (idx != -1)
        printf("Interpolation Search: NPM %s ditemukan di index %d (Nama: %s).\n", cariNPM, idx, mhs[idx].nama);
    else
        printf("Interpolation Search: NPM %s tidak ditemukan.\n", cariNPM);

    // Jump search
    idx = jumpSearch(mhs, MAX_MAHASISWA, cariNPM);
    if (idx != -1)
        printf("Jump Search: NPM %s ditemukan di index %d (Nama: %s).\n", cariNPM, idx, mhs[idx].nama);
    else
        printf("Jump Search: NPM %s tidak ditemukan.\n", cariNPM);

    return 0;
}
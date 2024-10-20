#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 50 // Jumlah maksimal pelanggan dalam antrian

typedef struct {
    int id;
    char nama[30];
    char jenisPaket[50];
} Pelanggan;

typedef struct {
    int front, rear;
    Pelanggan pelanggan[MAX];
} Queue;

void initQueue(Queue *q) {
    q->front = -1;
    q->rear = -1;
}

int isFull(Queue *q) {
    return q->rear == MAX - 1;
}

int isEmpty(Queue *q) {
    return q->front == -1 || q->front > q->rear;
}

// Menambahkan pelanggan ke antrian
void enqueue(Queue *q, Pelanggan p) {
    if (isFull(q)) {
        printf("Antrian penuh. Tidak dapat menambah pelanggan.\n");
    } else {
        if (q->front == -1) q->front = 0;
        q->rear++;
        q->pelanggan[q->rear] = p;
        printf("Pelanggan %s telah ditambahkan ke antrian.\n", p.nama);
    }
}

// Menghapus pelanggan dari antrian
void dequeue(Queue *q) {
    if (isEmpty(q)) {
        printf("Antrian kosong. Tidak ada pelanggan untuk dilayani.\n");
    } else {
        printf("Pelanggan %s telah dilayani dan keluar dari antrian.\n", q->pelanggan[q->front].nama);
        q->front++;
        if (q->front > q->rear) {
            q->front = q->rear = -1;
        }
    }
}

// Menampilkan pelanggan yang sedang menunggu di antrian
void displayQueue(Queue *q) {
    if (isEmpty(q)) {
        printf("Antrian kosong.\n");
    } else {
        printf("Antrian pelanggan:\n");
        for (int i = q->front; i <= q->rear; i++) {
            printf("ID: %d, Nama: %s, Paket: %s\n", q->pelanggan[i].id, q->pelanggan[i].nama, q->pelanggan[i].jenisPaket);
        }
    }
}

int main() {
    Queue queue;
    initQueue(&queue);

    int pilihan;
    Pelanggan p;
    int idCounter = 1;

    do {
        printf("\nSistem Antrian Kantor Pos\n");
        printf("1. Tambah pelanggan ke antrian\n");
        printf("2. Layani pelanggan\n");
        printf("3. Tampilkan antrian\n");
        printf("4. Keluar\n");
        printf("Pilih opsi: ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:
                if (!isFull(&queue)) {
                    p.id = idCounter++;
                    printf("Masukkan nama pelanggan: ");
                    scanf("%s", p.nama);
                    printf("Masukkan jenis paket (Besar, sedang, kecil): ");
                    scanf("%s", p.jenisPaket);
                    enqueue(&queue, p);
                } else {
                    printf("Antrian penuh. Tidak bisa menambah pelanggan.\n");
                }
                break;
            case 2:
                dequeue(&queue);
                break;
            case 3:
                displayQueue(&queue);
                break;
            case 4:
                printf("Keluar dari program.\n");
                break;
            default:
                printf("Opsi tidak valid. Coba lagi.\n");
        }
    } while (pilihan != 4);

    return 0;
}
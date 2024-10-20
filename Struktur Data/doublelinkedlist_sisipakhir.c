#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *next;
    struct Node *prev;
};

// Menambahkan node di akhir linked list
void insertAtTail(struct Node **head_ref, int new_data)
{
    struct Node *baru = (struct Node *)malloc(sizeof(struct Node));
    baru->data = new_data;
    baru->next = NULL;

    if (*head_ref == NULL)
    {
        baru->prev = NULL;
        *head_ref = baru;
        return;
    }

    struct Node *last = *head_ref;
    while (last->next != NULL)
    {
        last = last->next;
    }

    // Buat node terakhir menunjuk node baru
    last->next = baru;
    baru->prev = last;
}

// Menampilkan linked list dari awal sampai akhir
void printList(struct Node *head)
{
    printf("Forward Traversal:\n");
    while (head != NULL)
    {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

int main()
{
    struct Node *head = NULL;
    struct Node *kedua = NULL;
    struct Node *ketiga = NULL;

    head = (struct Node *)malloc(sizeof(struct Node));
    kedua = (struct Node *)malloc(sizeof(struct Node));
    ketiga = (struct Node *)malloc(sizeof(struct Node));

    head->data = 20;
    head->next = kedua;
    head->prev = NULL;

    kedua->data = 30;
    kedua->next = ketiga;
    kedua->prev = head;

    ketiga->data = 40;
    ketiga->next = NULL;
    ketiga->prev = kedua;

    printf("List asli:\n");
    printList(head);

    insertAtTail(&head, 50);

    printf("List setelah sisip akhir:\n");
    printList(head);

    return 0;
}
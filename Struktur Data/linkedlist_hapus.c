#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *next;
};

struct Node *createNode(int data)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void appendNode(struct Node **head, int data)
{
    struct Node *newNode = createNode(data);
    if (*head == NULL)
    {
        *head = newNode;
        return;
    }

    struct Node *temp = *head;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = newNode;
}

void deleteBefore(struct Node **head, int key)
{
    if (*head == NULL || (*head)->next == NULL)
    {
        printf("Tidak ada node sebelum elemen yang diberikan.\n");
        return;
    }

    struct Node *prev = NULL;
    struct Node *curr = *head;
    struct Node *next = curr->next;

    if (curr->data == key)
    {
        printf("Tidak ada node sebelum node pertama.\n");
        return;
    }

    while (next != NULL && next->data != key)
    {
        prev = curr;
        curr = next;
        next = next->next;
    }

    if (next == NULL)
    {
        printf("Node dengan data %d tidak ditemukan dalam linked list.\n", key);
        return;
    }

    if (prev == NULL)
    {
        *head = next;
    }
    else
    {
        prev->next = next;
    }

    printf("Node sebelum %d berhasil dihapus.\n", key);
    free(curr);
}

void displayList(struct Node *head)
{
    if (head == NULL)
    {
        printf("Linked list kosong.\n");
        return;
    }

    struct Node *temp = head;
    while (temp != NULL)
    {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

int main()
{
    struct Node *head = NULL;
    appendNode(&head, 10);
    appendNode(&head, 20);
    appendNode(&head, 25);
    appendNode(&head, 30);
    appendNode(&head, 40);

    printf("Linked list awal:\n");
    displayList(head);

    deleteBefore(&head, 30);

    printf("Linked list setelah penghapusan:\n");
    displayList(head);

    return 0;
}
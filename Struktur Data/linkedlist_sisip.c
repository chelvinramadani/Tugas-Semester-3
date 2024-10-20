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

void insertBefore(struct Node **head, int target, int newData)
{
    struct Node *newNode = createNode(newData);
    if (*head == NULL)
    {
        printf("List kosong, tidak dapat menyisipkan sebelum node target.\n");
        return;
    }

    if ((*head)->data == target)
    {
        newNode->next = *head;
        *head = newNode;
        return;
    }

    struct Node *temp = *head;
    while (temp->next != NULL && temp->next->data != target)
    {
        temp = temp->next;
    }

    if (temp->next == NULL)
    {
        printf("Node dengan nilai %d tidak ditemukan dalam list.\n", target);
        free(newNode);
        return;
    }

    newNode->next = temp->next;
    temp->next = newNode;
}

void printList(struct Node *head)
{
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
    head = createNode(10);
    head->next = createNode(20);
    head->next->next = createNode(30);
    head->next->next->next = createNode(40);

    printf("Linked list sebelum penyisipan:\n");
    printList(head);

    int target = 30;
    int newData = 25;

    printf("\nMenyisipkan %d sebelum %d:\n", newData, target);
    insertBefore(&head, target, newData);

    printf("Linked list setelah penyisipan:\n");
    printList(head);

    return 0;
}
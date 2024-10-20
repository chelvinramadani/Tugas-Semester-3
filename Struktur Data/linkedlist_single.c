#include <stdio.h>

struct Node
{
    int data;
    struct Node *next;
};

void printList(struct Node *head)
{
    while (head != NULL)
    {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

int main()
{
    struct Node n1, n2, n3, n4;

    n1.data = 10;
    n1.next = &n2;

    n2.data = 20;
    n2.next = &n3;

    n3.data = 30;
    n3.next = &n4;

    n4.data = 40;
    n4.next = NULL;

    printList(&n1);

    return 0;
}

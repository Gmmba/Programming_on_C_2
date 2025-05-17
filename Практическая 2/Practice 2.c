#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *next;
} node;

void addNode(node **head, int value) {
    node *new_node = malloc(sizeof(node));
    new_node->data = value;
    new_node->next = NULL;
    
    if (*head == NULL) {
        *head = new_node;
    } else {
        node *temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new_node;
    }
    
}

int printList(node *head) {
    if (head == NULL) {
        printf("No data.\n");
        return 0;
    }
    while (1) {
        if (head->next == NULL) {
            printf("%d\n", head->data);
            return 0;
        }
        printf("%d -> ", head->data);
        head = head->next;
    } 
}

int main()
{
    node *head = NULL;
    printf("Введите элементы списка\n");
    int value;
    while (1) {
        scanf("%d", &value);
        if (value == 0) break;
        addNode(&head, value);
    }
    printList(head);
    
    node *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}

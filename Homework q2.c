#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* head = NULL;

struct Node* newNode(int data) {
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp->data = data;
    temp->next = NULL;
    return temp;
}

void addList(int data) {
    struct Node* new_node = newNode(data);
    new_node->next = head;
    head = new_node;
}

void printList() {
    struct Node* current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

void sortList() {
    struct Node* current;
    struct Node* temp = head;
    int swap;

    if (head == NULL) {
        return;
    } else {
        while (temp != NULL) {
            current = temp->next;

            while (current != NULL) {
                if (temp->data < current->data) {
                    swap = temp->data;
                    temp->data = current->data;
                    current->data = swap;
                }
                current = current->next;
            }
            temp = temp->next;
        }
    }
}

int main() {
    int i;

    // Rastgele 100 sayý ekleme
    for (i = 0; i < 100; i++) {
        int rand_num = rand() % 1000; // 0 ile 999 arasýnda rastgele sayý üret
        addList(rand_num);
    }

    printf("Random Number:\n");
    printList();

    sortList();

    printf("\nSorted Numbers: (from big to small):\n");
    printList();

    return 0;
}


#include <stdio.h>
#include <stdlib.h>

struct Ring {
    int num;
    struct Ring *next;
};

int main() {
    int i;
    struct Ring *head= (struct Ring *)malloc(sizeof(struct Ring));
    struct Ring *tail;
    struct Ring *front;
    head->num = 1;
    head->next = NULL;
    tail = head;
    for (i = 2; i <= 21; i++) {
        struct Ring *ring = (struct Ring *)malloc(sizeof(struct Ring));
        ring->num = i;
        ring->next = NULL;
        tail->next = ring;
        tail = ring;
    }
    tail->next = head;
    i = 0;
    front = tail;
    while (head->next != head) {
        i++;
        if (i >= 17) {
            front->next = head->next;
            free(head);
            head = front->next;
            i = 0;
        }
        else {
            front = front->next;
            head = head->next;
        }
    }
    printf("%d", head->num);
}
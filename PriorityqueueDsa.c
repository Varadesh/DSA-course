#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100

typedef struct {
    int data[MAX_SIZE];
    int priority[MAX_SIZE];
    int rear;
} PriorityQueue;

void initPriorityQueue(PriorityQueue* pq) {
    pq->rear = -1;
}

int isFull(PriorityQueue* pq) {
    return (pq->rear == MAX_SIZE - 1);
}

int isEmpty(PriorityQueue* pq) {
    return (pq->rear == -1);
}

void enqueue(PriorityQueue* pq, int item, int priority) {
    if (isFull(pq)) {
        printf("Priority queue is full. Cannot enqueue element.\n");
    } else {
        pq->rear++;
        int i = pq->rear;
        while (i > 0 && priority > pq->priority[i - 1]) {
            pq->data[i] = pq->data[i - 1];
            pq->priority[i] = pq->priority[i - 1];
            i--;
        }
        pq->data[i] = item;
        pq->priority[i] = priority;
        printf("Enqueued item: %d with priority: %d\n", item, priority);
    }
}

int dequeue(PriorityQueue* pq) {
    if (isEmpty(pq)) {
        printf("Priority queue is empty. Cannot dequeue element.\n");
        return -1;
    } else {
        int item = pq->data[pq->rear];
        pq->rear--;
        return item;
    }
}

void display(PriorityQueue* pq) {
    if (isEmpty(pq)) {
        printf("Priority queue is empty.\n");
    } else {
        printf("Priority Queue elements:\n");
        for (int i = pq->rear; i >= 0; i--) {
            printf("Item: %d, Priority: %d\n", pq->data[i], pq->priority[i]);
        }
    }
}

int main() {
    PriorityQueue pq;
    initPriorityQueue(&pq);
    int p, t, qVal, i, num, priority, count1 = 0, count2 = 0;
    FILE* fp1 = fopen("generate.txt", "w");
    printf("Enter the range: ");
    scanf("%d %d", &p, &qVal);
    printf("Enter the number of elements to generate: ");
    scanf("%d", &t);
    FILE* fp5 = fopen("operation.txt", "w");
    fprintf(fp5, "Generated elements are: ");
    for (i = 0; i < t; i++) {
        num = (rand() % (p - qVal + 1)) + p;
        printf("%d\n", num);
        fprintf(fp1, "%d ", num);
        fprintf(fp5, "%d ", num);
    }
    fprintf(fp5, "\n");
    fclose(fp1);
    fp1 = fopen("generate.txt", "r");
    FILE* fp2 = fopen("enqueue.txt", "w");
    FILE* fp3 = fopen("dequeue.txt", "w");
    initPriorityQueue(&pq);
    int e, ch;
    while (1) {
        printf("\n1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Display\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &ch);

        switch (ch) {
            case 1:
                if (isFull(&pq))
                    printf("Priority queue overflow\n");
                else {
                    printf("Enter the element: ");
                    fscanf(fp1, "%d", &e);
                    printf("%d\n", e);
                    printf("Enter the priority: ");
                    scanf("%d", &priority);
                    fprintf(fp2, "%d %d ", e, priority);
                    fprintf(fp5, "Enqueued element is %d with priority %d\n", e, priority);
                    count1++;
                    enqueue(&pq, e, priority);
                }
                break;
            case 2:
                if (isEmpty(&pq))
                    printf("Priority queue is empty\n");
                else {
                    e = dequeue(&pq);
                    fprintf(fp3, "%d ", e);
                    fprintf(fp5, "Dequeued element is %d\n", e);
                    count2++;
                }
                break;
            case 3:
                display(&pq);
                fprintf(fp5, "Number of enqueued elements: %d\n", count1);
                fprintf(fp5, "Number of dequeued elements: %d\n", count2);
                fprintf(fp5, "Number of elements left in the priority queue: %d\n", count1 - count2);
                break;
            case 4:
                exit(0);
        }
    }

    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    fclose(fp5);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100

typedef struct {
    int data[MAX_SIZE];
    int front;
    int rear;
} CircularQueue;

void initCircularQueue(CircularQueue* cq) {
    cq->front = -1;
    cq->rear = -1;
}

int isFull(CircularQueue* cq) {
    return ((cq->rear + 1) % MAX_SIZE == cq->front);
}

int isEmpty(CircularQueue* cq) {
    return (cq->front == -1);
}

void enqueue(CircularQueue* cq, int item) {
    if (isFull(cq)) {
        printf("Queue is full. Cannot enqueue element.\n");
    } else {
        if (isEmpty(cq)) {
            cq->front = 0;
        }
        cq->rear = (cq->rear + 1) % MAX_SIZE;
        cq->data[cq->rear] = item;
        printf("Enqueued item: %d\n", item);
    }
}

int dequeue(CircularQueue* cq) {
    if (isEmpty(cq)) {
        printf("Queue is empty. Cannot dequeue element.\n");
        return -1;
    } else {
        int item = cq->data[cq->front];
        if (cq->front == cq->rear) {
            // Reset the queue when it becomes empty
            initCircularQueue(cq);
        } else {
            cq->front = (cq->front + 1) % MAX_SIZE;
        }
        return item;
    }
}

void display(CircularQueue* cq) {
    if (isEmpty(cq)) {
        printf("Queue is empty.\n");
    } else {
        int i = cq->front;
        printf("Queue elements:\n");
        while (i != cq->rear) {
            printf("%d ", cq->data[i]);
            i = (i + 1) % MAX_SIZE;
        }
        printf("%d\n", cq->data[cq->rear]);
    }
}

int main() {
    CircularQueue cq;
    initCircularQueue(&cq);
    int p, t, qVal, i, num, count1 = 0, count2 = 0;
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
    initCircularQueue(&cq);
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
                if (isFull(&cq))
                    printf("Queue overflow\n");
                else {
                    printf("Enter the element: ");
                    fscanf(fp1, "%d", &e);
                    printf("%d", e);
                    fprintf(fp2, "%d ", e);
                    fprintf(fp5, "Enqueued element is %d\n", e);
                    count1++;
                    enqueue(&cq, e);
                }
                break;
            case 2:
                if (isEmpty(&cq))
                    printf("Queue is empty\n");
                else {
                    e = dequeue(&cq);
                    fprintf(fp3, "%d ", e);
                    fprintf(fp5, "Dequeued element is %d\n", e);
                    count2++;
                }
                break;
            case 3:
                display(&cq);
                fprintf(fp5, "Number of enqueued elements: %d\n", count1);
                fprintf(fp5, "Number of dequeued elements: %d\n", count2);
                fprintf(fp5, "Number of elements left in the queue: %d\n", count1 - count2);
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

#include <stdio.h>
#define MAX_SIZE 100

// Structure to represent a queue
typedef struct {
    int data[MAX_SIZE];
    int front;
    int rear;
} Queue;

// Function to initialize the queue
void initializeQueue(Queue *queue) {
    queue->front = -1;
    queue->rear = -1;
}

// Function to check if the queue is empty
int isEmpty(Queue *queue) {
    return (queue->front == -1 && queue->rear == -1);
}

// Function to check if the queue is full
int isFull(Queue *queue) {
    return (queue->rear + 1) % MAX_SIZE == queue->front;
}

// Function to add an element to the queue
void enqueue(Queue *queue, int element) {
    if (isFull(queue)) {
        printf("Queue is full. Cannot enqueue element.\n");
        return;
    }

    if (isEmpty(queue)) {
        queue->front = 0;
        queue->rear = 0;
    } else {
        queue->rear = (queue->rear + 1) % MAX_SIZE;
    }

    queue->data[queue->rear] = element;
    printf("Enqueued element: %d\n", element);
}

// Function to remove an element from the queue
int dequeue(Queue *queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty. Cannot dequeue element.\n");
        return -1;
    }

    int removedElement = queue->data[queue->front];

    if (queue->front == queue->rear) {
        // Only one element in the queue
        initializeQueue(queue);
    } else {
        queue->front = (queue->front + 1) % MAX_SIZE;
    }

    printf("Dequeued element: %d\n", removedElement);
    return removedElement;
}

// Function to display the elements in the queue
void displayQueue(Queue *queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty.\n");
        return;
    }

    printf("Elements in the queue: ");
    int i = queue->front;
    while (i != queue->rear) {
        printf("%d ", queue->data[i]);
        i = (i + 1) % MAX_SIZE;
    }
    printf("%d\n", queue->data[queue->rear]);
}

int main() {
    Queue queue;
    initializeQueue(&queue);

    enqueue(&queue, 10);
    enqueue(&queue, 20);
    enqueue(&queue, 30);

    displayQueue(&queue);

    dequeue(&queue);

    displayQueue(&queue);

    return 0;
}

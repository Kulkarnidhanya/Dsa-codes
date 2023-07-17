#include <stdio.h>
#include <stdbool.h>

#define MAX_VERTICES 100

// Queue data structure
struct Queue {
    int items[MAX_VERTICES];
    int front;
    int rear;
};

// Graph data structure
struct Graph {
    int adjMatrix[MAX_VERTICES][MAX_VERTICES];
    int numVertices;
};

// Initialize the graph
void initGraph(struct Graph* graph, int numVertices) {
    graph->numVertices = numVertices;

    int i, j;
    for (i = 0; i < numVertices; i++) {
        for (j = 0; j < numVertices; j++) {
            graph->adjMatrix[i][j] = 0;
        }
    }
}

// Add an edge to the graph
void addEdge(struct Graph* graph, int src, int dest) {
    graph->adjMatrix[src][dest] = 1;
    graph->adjMatrix[dest][src] = 1;
}

// Enqueue an item into the queue
void enqueue(struct Queue* queue, int item) {
    queue->rear++;
    queue->items[queue->rear] = item;
}

// Dequeue an item from the queue
int dequeue(struct Queue* queue) {
    int item = queue->items[queue->front];
    queue->front++;
    return item;
}

// Check if the queue is empty
bool isQueueEmpty(struct Queue* queue) {
    return queue->rear < queue->front;
}

// Breadth-First Search algorithm
void bfs(struct Graph* graph, int startVertex) {
    // Initialize visited array
    bool visited[MAX_VERTICES];
    int i;
    for (i = 0; i < graph->numVertices; i++) {
        visited[i] = false;
    }

    // Create a queue
    struct Queue queue;
    queue.front = 0;
    queue.rear = -1;

    // Mark the start vertex as visited and enqueue it
    visited[startVertex] = true;
    enqueue(&queue, startVertex);

    printf("BFS traversal: ");

    while (!isQueueEmpty(&queue)) {
        // Dequeue a vertex from the queue
        int currentVertex = dequeue(&queue);
        printf("%d ", currentVertex);

        // Visit all adjacent vertices of the dequeued vertex
        for (i = 0; i <= graph->numVertices; i++) {
            if (graph->adjMatrix[currentVertex][i] == 1 && !visited[i]) {
                // Mark the adjacent vertex as visited and enqueue it
                visited[i] = true;
                enqueue(&queue, i);
            }
        }
    }

    printf("\n");
}

// Display the graph visually
void displayGraph(struct Graph* graph) {
    printf("Graph:\n");
    for (int i = 0; i < graph->numVertices; i++) {
        printf("%d: ", i);
        for (int j = 0; j <= graph->numVertices; j++) {
            if (graph->adjMatrix[i][j] == 1) {
                printf("%d ", j);
            }
        }
        printf("\n");
    }
}

// Display the adjacency matrix of the graph
void displayAdjacencyMatrix(struct Graph* graph) {
    printf("Adjacency Matrix:\n");
    for (int i = 0; i < graph->numVertices; i++) {
        for (int j = 0; j < graph->numVertices; j++) {
            printf("%d ", graph->adjMatrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    struct Graph graph;
    int numVertices, i, j;

    printf("Enter the number of vertices: ");
    scanf("%d", &numVertices);

    initGraph(&graph, numVertices);

    // Add edges between vertices
    printf("Enter the edges (vertex pairs) (e.g., 0 1): (-2 -3 to stop)\n");
    while (true) {
        scanf("%d %d", &i, &j);
        if (i == -2 && j == -3)
            break;
        addEdge(&graph, i, j);
    }

    // Display the graph
    displayGraph(&graph);

    // Display the adjacency matrix
    displayAdjacencyMatrix(&graph);

    int startVertex;
    printf("Enter the starting vertex: ");
    scanf("%d", &startVertex);

    bfs(&graph, startVertex);

    return 0;
}

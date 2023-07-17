#include <stdio.h>
#include <stdbool.h>

#define MAX_VERTICES 100

// Stack implementation
struct Stack {
    int items[MAX_VERTICES];
    int top;
};

void initialize(struct Stack* stack) {
    stack->top = -1;
}

bool isEmpty(struct Stack* stack) {
    return stack->top == -1;
}

void push(struct Stack* stack, int item) {
    stack->items[++stack->top] = item;
}

int pop(struct Stack* stack) {
    return stack->items[stack->top--];
}

int peek(struct Stack* stack) {
    return stack->items[stack->top];
}

// DFS traversal
void dfs(int graph[MAX_VERTICES][MAX_VERTICES], int vertices, int start) {
    bool visited[MAX_VERTICES];
    struct Stack stack;

    for (int i = 0; i < vertices; i++) {
        visited[i] = false;
    }

    initialize(&stack);
    push(&stack, start);

    while (!isEmpty(&stack)) {
        int vertex = pop(&stack);

        if (!visited[vertex]) {
            visited[vertex] = true;
            printf("%d ", vertex);  // Process the visited vertex

            for (int i = vertices - 1; i >= 0; i--) {
                if (graph[vertex][i] && !visited[i]) {
                    push(&stack, i);
                }
            }
        }
    }
}

int main() {
    int vertices = 7;
    int graph[MAX_VERTICES][MAX_VERTICES] = {
        {0, 1, 1, 0, 0, 0, 0},
        {1, 0, 0, 1, 1, 0, 0},
        {1, 0, 0, 0, 0, 1, 0},
        {0, 1, 0, 0, 0, 1, 1},
        {0, 1, 0, 0, 0, 0, 0},
        {0, 0, 1, 1, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0}
    };

    int startVertex = 0;  // Starting vertex for DFS

    printf("DFS traversal: ");
    dfs(graph, vertices, startVertex);

    return 0;
}

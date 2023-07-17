#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 100

// Parking Lot structure
typedef struct {
    char parkingLot[MAX_SIZE][MAX_SIZE];
    int numRows;
    int numCols;
} ParkingLot;

// Initialize the parking lot
void initializeParkingLot(ParkingLot* parkingLot, int numRows, int numCols) {
    parkingLot->numRows = numRows;
    parkingLot->numCols = numCols;

    // Set all cells as unvisited
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            parkingLot->parkingLot[i][j] = '.';
        }
    }
}

// Add obstacles (occupied spaces) to the parking lot
void addObstacles(ParkingLot* parkingLot, int numObstacles) {
    int row, col;
    for (int i = 0; i < numObstacles; i++) {
        printf("Enter the row and column of obstacle %d (1-based indexing): ", i + 1);
        scanf("%d %d", &row, &col);
        parkingLot->parkingLot[row - 1][col - 1] = '#';
    }
}

// Breadth-First Search traversal to find the shortest distance
int findShortestDistance(ParkingLot* parkingLot, int startRow, int startCol, int destRow, int destCol) {
    int distance[MAX_SIZE][MAX_SIZE];
    bool visited[MAX_SIZE][MAX_SIZE];

    // Initialize distance and visited arrays
    for (int i = 0; i < parkingLot->numRows; i++) {
        for (int j = 0; j < parkingLot->numCols; j++) {
            distance[i][j] = -1;
            visited[i][j] = false;
        }
    }

    // Mark the starting position as visited and initialize its distance as 0
    visited[startRow][startCol] = true;
    distance[startRow][startCol] = 0;

    // Queue for BFS traversal
    int queue[MAX_SIZE * MAX_SIZE][2];
    int front = 0, rear = 0;

    // Enqueue the starting position
    queue[rear][0] = startRow;
    queue[rear][1] = startCol;
    rear++;

    // Perform BFS traversal
    while (front < rear) {
        int currentRow = queue[front][0];
        int currentCol = queue[front][1];
        front++;

        // Check if the destination is reached
        if (currentRow == destRow && currentCol == destCol) {
            return distance[currentRow][currentCol];
        }

        // Move in all four directions (up, right, down, left)
        int dr[] = {-1, 0, 1, 0};
        int dc[] = {0, 1, 0, -1};

        for (int i = 0; i < 4; i++) {
            int newRow = currentRow + dr[i];
            int newCol = currentCol + dc[i];

            // Check if the new position is within the parking lot boundaries
            if (newRow >= 0 && newRow < parkingLot->numRows && newCol >= 0 && newCol < parkingLot->numCols) {
                // Check if the new position is not an obstacle and is not visited
                if (parkingLot->parkingLot[newRow][newCol] != '#' && !visited[newRow][newCol]) {
                    visited[newRow][newCol] = true;
                    distance[newRow][newCol] = distance[currentRow][currentCol] + 1;

                    // Enqueue the new position
                    queue[rear][0] = newRow;
                    queue[rear][1] = newCol;
                    rear++;
                }
            }
        }
    }

    return -1;  // Destination is not reachable
}

int main() {
    int numRows, numCols;
    printf("Enter the number of rows in the parking lot: ");
    scanf("%d", &numRows);
    printf("Enter the number of columns in the parking lot: ");
    scanf("%d", &numCols);

    ParkingLot parkingLot;

    // Initialize the parking lot
    initializeParkingLot(&parkingLot, numRows, numCols);

    int numObstacles;
    printf("Enter the number of obstacles (occupied spaces) in the parking lot: ");
    scanf("%d", &numObstacles);

    // Add obstacles to the parking lot
    addObstacles(&parkingLot, numObstacles);

    int startRow, startCol, destRow, destCol;
    printf("\nEnter the starting position (row col): ");
    scanf("%d %d", &startRow, &startCol);
    printf("Enter the destination position (row col): ");
    scanf("%d %d", &destRow, &destCol);

    // Find the shortest distance
    int shortestDistance = findShortestDistance(&parkingLot, startRow - 1, startCol - 1, destRow - 1, destCol - 1);

    if (shortestDistance != -1) {
        printf("\nThe shortest distance from the starting position to the destination is: %d\n", shortestDistance);
    } else {
        printf("\nNo path exists from the starting position to the destination.\n");
    }

    return 0;
}



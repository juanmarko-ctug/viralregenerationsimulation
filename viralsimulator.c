#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define ROWS 15
#define COLS 15
#define DELAY 1000000 

void initializeGrid(int grid[ROWS][COLS]);
void printGrid(int grid[ROWS][COLS]);
void nextGeneration(int grid[ROWS][COLS], int newGrid[ROWS][COLS]);
int countNeighbors(int grid[ROWS][COLS], int x, int y);
void copyGrid(int source[ROWS][COLS], int destination[ROWS][COLS]);

int main() {
    int grid[ROWS][COLS];
    int newGrid[ROWS][COLS];

    srand(time(NULL));
    initializeGrid(grid);

    while (1) {
        system("clear"); 
        printGrid(grid);
        nextGeneration(grid, newGrid);
        copyGrid(newGrid, grid);
        usleep(DELAY);
    }

    return 0;
}

void initializeGrid(int grid[ROWS][COLS]) {
    
    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLS; j++)
            grid[i][j] = 0;

    
    int placed = 0;
    while (placed < 50) {
        int x = rand() % ROWS;
        int y = rand() % COLS;
        if (grid[x][y] == 0) {
            grid[x][y] = 1;
            placed++;
        }
    }
}

void printGrid(int grid[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%c ", grid[i][j] ? '0' : '.');
        }
        printf("\n");
    }
}

void nextGeneration(int grid[ROWS][COLS], int newGrid[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            int neighbors = countNeighbors(grid, i, j);

            if (grid[i][j] == 1) {
                newGrid[i][j] = (neighbors == 2 || neighbors == 3) ? 1 : 0;
            } else {
                newGrid[i][j] = (neighbors == 3) ? 1 : 0;
            }
        }
    }
}

int countNeighbors(int grid[ROWS][COLS], int x, int y) {
    int count = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue;

            int nx = x + i;
            int ny = y + j;

            if (nx >= 0 && nx < ROWS && ny >= 0 && ny < COLS) {
                count += grid[nx][ny];
            }
        }
    }
    return count;
}

void copyGrid(int source[ROWS][COLS], int destination[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLS; j++)
            destination[i][j] = source[i][j];
}
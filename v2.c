#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROWS 10
#define COLS 10
#define MINES 15

int board[ROWS][COLS];
int revealed[ROWS][COLS];
int lives = 3;
int mines_left = MINES;

void init_board() {
    int i, j, k;
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            board[i][j] = 0;
            revealed[i][j] = 0;
        }
    }
    for (k = 0; k < MINES; k++) {
        int i, j;
        do {
            i = rand() % ROWS;
            j = rand() % COLS;
        } while (board[i][j] == -1);
        board[i][j] = -1;
        for (int di = -1; di <= 1; di++) {
            for (int dj = -1; dj <= 1; dj++) {
                int ni = i + di;
                int nj = j + dj;
                if (ni >= 0 && ni < ROWS && nj >= 0 && nj < COLS && board[ni][nj] != -1) {
                    board[ni][nj]++;
                }
            }
        }
    }
}

void print_board() {
    int i, j;
    printf("Mines left: %d   Lives: %d\n", mines_left, lives);
    printf("  ");
    for (j = 0; j < COLS; j++) {
        printf("%d ", j);
    }
    printf("\n");
    printf("  ");
    for (j = 0; j < COLS; j++) {
        printf("--");
    }
    printf("\n");
    for (i = 0; i < ROWS; i++) {
        printf("%d|", i);
        for (j = 0; j < COLS; j++) {
            if (revealed[i][j]) {
                if (board[i][j] == -1) {
                    printf("* ");
                } else {
                    printf("%d ", board[i][j]);
                }
            } else {
                printf(". ");
            }
        }
        printf("\n");
    }
}

void reveal(int i, int j) {
    if (revealed[i][j]) {
        return;
    }
    revealed[i][j] = 1;
    if (board[i][j] == -1) {
        printf("Mine hit!\n");
        lives--;
        mines_left--;
        if (lives == 0) {
            printf("Game over!\n");
            exit(0);
        }
    } else if (board[i][j] == 0) {
        for (int di = -1; di <= 1; di++) {
            for (int dj = -1; dj <= 1; dj++) {
                int ni = i + di;
                int nj = j + dj;
                if (ni >= 0 && ni < ROWS && nj >= 0 && nj < COLS) {
                    reveal(ni, nj);
                }
            }
        }
    }
}

int main() {
    srand(time(NULL));
    init_board();
    int lives = 3;
    while (1) {
        system("cls"); // Clears the screen (for Windows)
        print_board();
        int x, y;
        printf("Enter x and y coordinates (separated by a space): ");
        scanf("%d %d", &x, &y);
        if (x < 0 || x >= ROWS || y < 0 || y >= COLS) {
            printf("Invalid coordinates. Try again.\n");
            continue;
        }
        if (revealed[x][y]) {
            printf("This tile has already been revealed. Try again.\n");
            continue;
        }
        reveal(x, y);
        if (board[x][y] == -1) {
            lives--;
            printf("You hit a mine! You have %d lives left.\n", lives);
            if (lives == 0) {
                printf("Game over!\n");
                exit(0);
            }
        }
        if (mines_left == 0) {
            printf("You win!\n");
            exit(0);
        }
    }
    return 0;
}

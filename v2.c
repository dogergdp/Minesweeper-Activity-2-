#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define ROWS 10
#define COLS 10
#define NUM_MINES 5

int board[ROWS][COLS];
int revealed[ROWS][COLS];
int lives = 3;
int mines_left = NUM_MINES;


void print_line(int LENGTH){
	int i;
	for (i=0; i<LENGTH; i++){
		printf("%c", 205);
	}
}


void init_board() {
    int i, j, k;
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            board[i][j] = 0;
            revealed[i][j] = 0;
        }
    }
    for (k = 0; k < NUM_MINES; k++) {
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
    printf("\n");
    printf("\t\t\t\t\t\t+");print_line(16);printf("+");print_line(13);printf("+");printf("\n");
    printf("\t\t\t\t\t\t| Mines left: %d  | %c  Lives: %d |\n", mines_left, 3, lives);
    printf("\t\t\t\t\t\t+");print_line(16);printf("+");print_line(13);printf("+");printf("\n");

    
    printf("\t\t\t\t\t");printf("+");print_line(3);printf("+");print_line(39);printf("+");printf("\n");
    printf("\t\t\t\t\t|   | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |\n");
    printf("\t\t\t\t\t");printf("+");print_line(3);printf("+");print_line(39);printf("+");printf("\n");
    
    for (i = 0; i < ROWS; i++) {
        printf("\t\t\t\t\t| %d ", i);
        for (j = 0; j < COLS; j++) {
            if (revealed[i][j]) {
                if (board[i][j] == -1) {
                    printf("| %c ", 149);
                } else {
                    switch (board[i][j]) {
                        case 1:
                            printf("| \033[1;34m%d\033[0m ", board[i][j]); // blue
                            break;
                        case 2:
                            printf("| \033[1;32m%d\033[0m ", board[i][j]); // green
                            break;
                        case 3:
                            printf("| \033[1;31m%d\033[0m ", board[i][j]); // red
                            break;
                        case 4:
                            printf("| \033[1;35m%d\033[0m ", board[i][j]); // magenta
                            break;
                        case 5:
                            printf("| \033[1;33m%d\033[0m ", board[i][j]); // yellow
                            break;
                        case 6:
                        case 7:
                        case 8:
                            printf("| \033[1;36m%d\033[0m ", board[i][j]); // cyan
                            break;
                        default:
                            printf("| \033[1m%d\033[0m ", board[i][j]); // bold
                            break;
                    }
                }
            } else {
                printf("| %c ", 219);
            }
        }
        printf("|\n");
        printf("\t\t\t\t\t");printf("+");print_line(3);printf("+");print_line(39);printf("+");printf("\n");
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
    int non_bombs_left = ROWS * COLS - NUM_MINES;
    while (1) {
        system("cls");
        int x, y;
        print_board();
        printf("\n\n");
        printf("\t\t\t\t  Enter x and y coordinates (separated by a space): ");
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
        } else {
            non_bombs_left--;
        }
        if (non_bombs_left == 0) {
            printf("You win!\n");
            exit(0);
        }
    }
    return 0;
}


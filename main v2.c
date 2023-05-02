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
                    printf("| \033[1;31m%c\033[0m ", 149);
                } else {
                    switch (board[i][j]) {
                        case 1:
                            printf("| \033[1;34m%d\033[0m ", board[i][j]); // blue
                            break;
                        case 2:
                            printf("| \033[1;32m%d\033[0m ", board[i][j]); // green
                            break;
                        case 3:
                            printf("| \033[1;38;5;208m%d\033[0m ", board[i][j]); // orange
                            break;
                        case 4:
                            printf("| \033[1;35m%d\033[0m ", board[i][j]); // magenta
                            break;
                        case 5:
                            printf("| \033[1;33m%d\033[0m ", board[i][j]); // yellow
                            break;
                        case 6: 
                      		printf("| \033[1;94m%d\033[0m ", board[i][j]); // light blue
                            break;
                        case 7:
                        	printf("| \033[1;32m%d\033[0m ", board[i][j]); // light green
                            break;
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
        lives--;
        mines_left--;
        if (lives == 0) {
            printf("\n\n\t\t\t\t\t\t\t   GAME OVER!\n");
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
    int game_over = 0;
    while (!game_over) {
        system("cls");
        print_board();
        int row, col;
        do {
            printf("\n\n\t\t\t\t\t Enter row and column (e.g. 3 4): ");
            if (scanf("%d %d", &row, &col) != 2) {
			    printf("\n\t\t\t\t\t Invalid input. Please enter two integers separated by a space.");
			    while(getchar() != '\n'); // consume the remaining characters in input buffer
			    continue;
			}
            if (row < 0 || row >= ROWS || col < 0 || col >= COLS) {
                printf("\n\t\t\t\t\t Invalid input. Please enter row and column values between 0 and 9.");
                continue;
            }
            if (revealed[row][col]) {
                printf("\n\t\t\t\t\t This cell has already been revealed. Please choose another cell.");
                continue;
            }
            if (board[row][col] == -1){
                reveal(row,col);
                system("cls");
                print_board();
                printf("\n\n\t\t\t\t\t\t\t   MINE HIT!\n");
            	continue;
			}
            break;
        } while (1);
        reveal(row, col);
        int revealed_count = 0;
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                if (revealed[i][j] || board[i][j] == -1) {
                    revealed_count++;
                }
            }
        }

        if (revealed_count == ROWS * COLS) {
        	system("cls");
        	print_board();
            printf("\n\n\t\t\t\t\t\t\t   YOU WON!\n");
            game_over = 1;
        }
    }
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define ROWS 10
#define COLS 10
#define NUM_MINES 10

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
    int i, j;
    board[0][8] = -1;
    board[0][2] = -1;
    board[2][1] = -1;
    board[3][3] = -1;
    board[3][6] = -1;
    board[5][5] = -1;
    board[6][4] = -1;
    board[7][2] = -1;
    board[8][7] = -1;
    board[9][1] = -1;
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            if (board[i][j] != -1) {
                board[i][j] = 0;
            }
            revealed[i][j] = 0;
        }
    }
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            if (board[i][j] == -1) {
                continue;
            }
            int count = 0;
            for (int di = -1; di <= 1; di++) {
                for (int dj = -1; dj <= 1; dj++) {
                    int ni = i + di;
                    int nj = j + dj;
                    if (ni >= 0 && ni < ROWS && nj >= 0 && nj < COLS && board[ni][nj] == -1) {
                        count++;
                    }
                }
            }
            board[i][j] = count;
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
        printf("Mine hit!\n");
        lives--;
        mines_left--;
        if (lives == 0) {
            printf("Game over!\n");
            exit(0);
        }
    } 
    else if (board[i][j] == 0) {
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
    // Number of moves entered by tester must be indicated manually in this format: int moves[number_of_moves][2]
    int moves[31][2] = {	{0, 7}, 
							{0, 8}, 
							{6, 1}, 
							{7, 3}, 
							{0, 6}, 
							{6, 8}, 
							{6, 9}, 
							{2, 7}, 
							{4, 7}, 
							{1, 1},
							{0, 4},
							{7, 5},
							{8, 6},
							{9, 6},
							{9, 7},
							{4, 0},
							{8, 5},
							{9, 5},
							{6, 5},
							{5, 4},
							{4, 5},
							{3, 5},
							{3, 3},
							{3, 4},
							{2, 2},
							{1, 2},
							{4, 4},
							{9, 0},
							{2, 0},
							{0, 9}
						}; 
    int move_index = 0;
    while (!game_over && move_index < 31) { 
        system("cls");
        print_board();
        int row = moves[move_index][0];
        int col = moves[move_index][1];
        move_index++;
        if (row < 0 || row >= ROWS || col < 0 || col >= COLS) {
            printf("Invalid input. Please enter row and column values between 0 and 9.\n");
            continue;
        }
        if (revealed[row][col]) {
            printf("This cell has already been revealed. Please choose another cell.\n");
            continue;
        }
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



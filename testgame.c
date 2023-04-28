#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

#define ROWS 25
#define COLUMNS 75

void gotoxy(int,int);
void print_line_vert(char,int);
void print_line_horiz(char, int);

int main(){

    int i,j;


    // Calculate the starting coordinates for the grid
    int x_start = (125 - COLUMNS) / 2;
    int y_start = (25 - ROWS) / 2;

    // Draw the grid
    for (i = 0; i < ROWS; i++) {
        // Move the cursor to the beginning of the row
        gotoxy(x_start, y_start + i);

        for (j = 0; j < COLUMNS; j++) {
            // Draw a blank space
            printf("*");

            // Move the cursor to the next column
            gotoxy(x_start + j + 1, y_start + i);
        }
    }
    print_line_horiz('#',20);

    return 0;

}



void gotoxy(int x, int y){
	COORD c;
	c.X = x;
	c.Y = y;
	SetConsoleCursorPosition(
        GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void print_line_vert(char CHAR, int LENGTH){
	int i;
	for (i=0; i<LENGTH; i++){
		printf("%c\n", CHAR);
	}
}

void print_line_horiz(char CHAR, int LENGTH){
	int i;
	for (i=0; i<LENGTH; i++){
		printf("%c", CHAR);
	}
	printf("\n");
}



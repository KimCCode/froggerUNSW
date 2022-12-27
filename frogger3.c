#include <stdio.h>
#include <stdlib.h>

#define SIZE 9
#define TRUE 1
#define FALSE 0

enum tile_type {LILLYPAD, BANK, WATER, TURTLE, LOG};

struct board_tile {
    enum tile_type type;
    int occupied; 
};

void print_board(struct board_tile board[SIZE][SIZE]);

int main() {
    struct board_tile game_board[SIZE][SIZE];
    char command;
    int i, a, a1, b, c, turtles, d, turtle_row, turtle_column, log_row, log_start, log_end, l, clear_row, h, remove_row, remove_column;
    
    // Set up mode
    for (i = 0; i < 9; i++) { 
        if (i == 0) { // Water + lily pads
            for (a = 0; a < 9; a+=2) {
                game_board[i][a].type = LILLYPAD;
                game_board[i][a].occupied = 0;
            }
            for (a1 = 1; a1 < 9; a1+=2) {
                game_board[i][a1].type = WATER;
                game_board[i][a1].occupied = 0;
            }
        }
        
        else if(i == 8){ // Bank
            for (b = 0; b < 9; b++) {
                if (b == 4) {
                    // game_board[i][b].type =
                    game_board[i][b].occupied = 1;
                }
                else {
                    game_board[i][b].type = BANK;
                    game_board[i][b].occupied = 0;
                }
            }
        }
        
        else { // Water
            for (c = 0; c < 9; c++) {
                game_board[i][c].type = WATER;
                game_board[i][c].occupied = 0;
            } 
        }
    }

    printf("\nWelcome to CSE Frogger!\nHow many turtles? ");
    scanf("%d", &turtles); // Ask user for turtles to be added
    
    printf("Enter pairs:\n");
    for (d = 0; d < turtles; d++){
        scanf("%d %d", &turtle_row, &turtle_column);
        if (turtle_row > 0 && turtle_row < 8 && turtle_column >= 0 && turtle_column <= 8) {
            game_board[turtle_row][turtle_column].type = TURTLE;
            game_board[turtle_row][turtle_column].occupied = 0;
        }   
        else {
            continue;
        }
    }

    printf("Game started\n");
    print_board(game_board);
    
    // Command mode
    while(1) {
        printf("\nEnter command: ");
        scanf(" %c", &command);
        switch (command) { 
            case 'l':
                scanf(" %d %d %d", &log_row, &log_start, &log_end); // ISSUE: Program only takes row of last turtle.
                if (log_row > 0 && log_row < 8 && log_start >= 0 &&
                log_start <= 8 && log_end >= 0 && log_end <= 8 && 
                log_start <= log_end && log_row != turtle_row) {
                    for (l = log_start; l <= log_end; l++) {
                        game_board[log_row][l].type = LOG;
                        game_board[log_row][l].occupied = 0;
                    }
                    print_board(game_board);
                } 
                else {
                    print_board(game_board);
                }       
                break;

            case 'c':
                scanf(" %d", &clear_row);
                if (clear_row > 0 && clear_row < 8) {
                    for (h = 0; h < 9; h++) {
                        game_board[clear_row][h].type = WATER;
                        game_board[clear_row][h].occupied = 0;
                    }
                    print_board(game_board);
                }
                else {
                    print_board(game_board);
                }
                break;

            case 'r':
                scanf(" %d %d", &remove_row, &remove_column);
        }
    }
    return 0;
}

void print_board(struct board_tile board[SIZE][SIZE]) {
    for (int row = 0; row < SIZE; row++) { 
        for (int col = 0; col < SIZE; col++) {
            char type_char;
            if (board[row][col].occupied) {
                type_char = 'F';
            }
            else {
                enum tile_type type = board[row][col].type;
                if (type == LILLYPAD) {
                    type_char = 'o';
                }
                else if (type == BANK) {
                    type_char = 'x';
                }
                else if (type == TURTLE) {
                    type_char = 'T';
                }
                else if (type == LOG) {
                    type_char = 'L';
                }
                else if (type == WATER) {
                    type_char = '~';
                }
            }
            printf("%c ", type_char);
        }
        printf("\n");
    }
}
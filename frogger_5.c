#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SIZE 9
#define TRUE 1
#define FALSE 0

enum tile_type {LILLYPAD, BANK, WATER, TURTLE, LOG};

struct board_tile {
    enum tile_type type;
    int occupied;
    int bug; 
    int bug_dir; // 1 = right, -1 = left
    int bug_left;
};

void print_board(struct board_tile board[SIZE][SIZE]);

int main() {
    struct board_tile game_board[SIZE][SIZE];
    char command;
    int i, j, a, a1, b, c, turtles, d, turtle_row, turtle_column,
    log_row, log_start, log_end, l, clear_row, h, remove_row,
    remove_column, z, turtle_check, frogger_check, f, y, v, 
    curr_row, curr_col, m, n, life = 3, bug_row, bug_col,
    left = 0, status, g, q, u, e;
    
        
                    // Set up mode //
    
    for (i = 0; i < 9; i++) { 
        if (i == 0) { // SETTING UP ROW 0
            for (a = 0; a < 9; a+=2) {
                game_board[i][a].type = LILLYPAD;
                game_board[i][a].occupied = 0;
                game_board[i][a].bug = 0;
                game_board[i][a].bug_dir = 1;
            }
            for (a1 = 1; a1 < 9; a1+=2) {
                game_board[i][a1].type = WATER;
                game_board[i][a1].occupied = 0;
                game_board[i][a1].bug = 0;
                game_board[i][a1].bug_dir = 1;                
            }
        }
        
        else if (i == 8){ // BANK
            for (b = 0; b < 9; b++) {
                if (b == 4) { // FROGGER
                    game_board[i][b].type = BANK;
                    game_board[i][b].occupied = 1;
                    game_board[i][b].bug = 0;
                    game_board[i][b].bug_dir = 1;
                }
                else {
                    game_board[i][b].type = BANK;
                    game_board[i][b].occupied = 0;
                    game_board[i][b].bug = 0;
                    game_board[i][b].bug_dir = 1;
                }
            }
        }
        
        else { // Water
            for (c = 0; c < 9; c++) {
                game_board[i][c].type = WATER;
                game_board[i][c].occupied = 0;
                game_board[i][c].bug = 0;
                game_board[i][c].bug_dir = 1;
            } 
        }
    }
    
                    // Adding turtles //

    printf("\nWelcome to CSE Frogger!\nHow many turtles? ");
    scanf("%d", &turtles); 
    if (turtles != 0) {
        printf("Enter pairs:\n");
        for (d = 0; d < turtles; d++) {
            scanf("%d %d", &turtle_row, &turtle_column);
            if (turtle_row > 0 && turtle_row < 8 && turtle_column >= 0 && turtle_column <= 8) {
                game_board[turtle_row][turtle_column].type = TURTLE;
                game_board[turtle_row][turtle_column].occupied = 0;
                game_board[turtle_row][turtle_column].bug = 0;
                game_board[turtle_row][turtle_column].bug_dir = 1;

            }  
        }
    }

    printf("Game started\n");
    print_board(game_board);

                    // Command mode //

    while(life > 0) { 
        printf("\nEnter command: ");
        scanf(" %c", &command); // Asks user for command
        for (m = 0; m < 9; m++) { // Keeps track of what tile frogger is on
            for (n = 0; n < 9; n++) {
                if (game_board[m][n].occupied == 1) {
                    curr_row = m;
                    curr_col = n;
                }
            }
        }       

                    // Adding bugs //

        if (command == 'b') {
            scanf(" %d %d", &bug_row, &bug_col);
            if ((game_board[bug_row][bug_col].type == TURTLE || game_board[bug_row][bug_col].type == LOG) && game_board[bug_row][bug_col].occupied == 0 && game_board[bug_row][bug_col].bug == 0) {
                game_board[bug_row][bug_col].bug = 1;
                game_board[bug_row][bug_col].bug_left = 1;
            }
        } 

                    // Moving frogger // 

        else if (command == 'w' || command == 'a' || command == 's' || command == 'd') { 
            switch (command) {
                case 'w':
                if (curr_row != 0) {
                    game_board[curr_row][curr_col].occupied = 0; // Clear Frogger's current position
                    curr_row--;                                        
                    game_board[curr_row][curr_col].occupied = 1;
                    printf("Frogger's current position %d %d\n", curr_row, curr_col);
                }
                break;
            
                case 'a':
                if (curr_col != 0) {
                    game_board[curr_row][curr_col].occupied = 0;
                    curr_col--;                    
                    game_board[curr_row][curr_col].occupied = 1;
                    printf("Frogger's current position %d %d\n", curr_row, curr_col);
                } 
                break;
            
                case 's':
                if (curr_row != 8) {
                    game_board[curr_row][curr_col].occupied = 0;
                    curr_row++;                    
                    game_board[curr_row][curr_col].occupied = 1;
                    printf("Frogger's current position %d %d\n", curr_row, curr_col);
                } 
                break;
            
                case 'd':
                if (curr_col != 8) {
                    game_board[curr_row][curr_col].occupied = 0;
                    curr_col++;
                    game_board[curr_row][curr_col].occupied = 1;
                    printf("Frogger's current position %d %d\n", curr_row, curr_col);
                }   
                break;
            } // End of switch statement
            
                   // Moving bugs //
            

            for (g = 0; g < 9; g++) {
                for (j = 0; j < 9; j++) {
                    if (game_board[g][j].bug_left == 0 && game_board[g][j].bug == 1) {
                        game_board[g][j].bug_dir = 1;
                        if (j + game_board[g][j].bug_dir > 0 && j + game_board[g][j].bug_dir < 8 && game_board[g][j+2].type == LOG) { // log to the right
                            game_board[g][j].bug = 0;
                            game_board[g][j + game_board[g][j].bug_dir].bug = 1;
                            game_board[g][j + game_board[g][j].bug_dir].bug_left = 0;
                            break;                                                                
                        }
                        else {
                            game_board[g][j].bug = 0;
                            game_board[g][j].bug_dir = 1;
                            game_board[g][j + game_board[g][j].bug_dir].bug = 1;  
                            game_board[g][j + game_board[g][j].bug_dir].bug_left = 1;
                            break;                                                                                           
                        }                          
                    }  
                    else if (game_board[g][j].bug_left == 1 && game_board[g][j].bug == 1) {
                        game_board[g][j].bug_dir = -1;
                        if (j + game_board[g][j].bug_dir > 0 && j + game_board[g][j].bug_dir < 8 && game_board[g][j-2].type == LOG) {                
                            game_board[g][j].bug = 0;
                            game_board[g][j + game_board[g][j].bug_dir].bug = 1; 
                            game_board[g][j + game_board[g][j].bug_dir].bug_left = 1;
                            break;                                                                                        
                        } 
                        else { 
                            game_board[g][j].bug = 0;
                            game_board[g][j].bug_dir = -1;
                            game_board[g][j + game_board[g][j].bug_dir].bug = 1;  
                            game_board[g][j + game_board[g][j].bug_dir].bug_left = 0;  
                            break;                                                                                         
                        }      
                    }                                      
                }
            }
        }   

                    // Adding logs //

        else if (command == 'l') {
            scanf(" %d %d %d", &log_row, &log_start, &log_end); 
            turtle_check = 1;
            for (z = 0; z < 9; z++) {
                if (game_board[log_row][z].type == TURTLE) { 
                    turtle_check = 0;
                }
            }
            if (log_row > 0 && log_row < 8 && log_start >= 0 &&
            log_start <= 8 && log_end >= 0 && log_end <= 8 && 
            log_start <= log_end && turtle_check == 1) {
                for (l = log_start; l <= log_end; l++) {
                    game_board[log_row][l].type = LOG;
                    game_board[log_row][l].occupied = 0;
                } 
            }       
        }

                    // Clearing rows //

        else if (command == 'c') {
            scanf(" %d", &clear_row);
            frogger_check = 1;
            for (f = 0; f < 9; f++) {
                if (game_board[clear_row][f].occupied) {
                    frogger_check = 0;
                }
            }

            if (clear_row > 0 && clear_row < 8 && frogger_check == 1) {
                for (h = 0; h < 9; h++) {
                    game_board[clear_row][h].type = WATER;
                    game_board[clear_row][h].occupied = 0;
                    game_board[clear_row][h].bug = 0;
                }
            }
        }
                    
                    // Removing specific logs //    

        else if (command == 'r') {
            scanf(" %d %d", &remove_row, &remove_column); // Asks the user which log they want to remove
            if (game_board[remove_row][remove_column].type == LOG) {
                for (v = 0; v < 9 - remove_column; v++) { // Checks adjacent logs to the right
                    if (game_board[remove_row][remove_column+v].type != WATER && game_board[remove_row][remove_column+v].occupied == 0) {
                        game_board[remove_row][remove_column+v].type = WATER;
                    }                    
                    else {
                        break; // exits for loop
                    }
                }
            
                for (y = 1; y <= remove_column; y++) { // Checks adjacent logs to the left
                    if (game_board[remove_row][remove_column-y].type != WATER && game_board[remove_row][remove_column-y].occupied == 0) {
                        game_board[remove_row][remove_column-y].type = WATER;
                    }   
                    else {
                        break;
                    }                                    
                }
            } // Issue: How to check for frogger?
        }
                
                // Moving the board //

        else if (command == 'g') {
            scanf(" %d", &status);
            if (status == 1) { // Game mode on
                printf("\n\n### GAME MODE ACTIVATED ###\n\n");
                print_board(game_board);
            }
        }
            
        else {
            break;   
        }
        
        print_board(game_board);

        if (game_board[curr_row][curr_col].occupied == 1 && game_board[curr_row][curr_col].type == LILLYPAD) {
            printf("\nWahoo!! You Won!\n\n");
            break; // exits while loop
        }
        else if (game_board[curr_row][curr_col].occupied == 1 && (game_board[curr_row][curr_col].type == WATER
        || game_board[curr_row][curr_col].bug == 1)) {
            life = life - 1;
            if (life == 0) {
                printf("\n\n!! GAME OVER !!");
                break; // exits while loop
            }
            else {
            printf("\n\n# LIVES LEFT: %d #\n\n", life);
            game_board[curr_row][curr_col].occupied = 0;
            game_board[8][4].occupied = 1;
            print_board(game_board);
            }
        }
    }
    printf("\n\nThank you for playing CSE Frogger!");
    return 0;
}

void print_board(struct board_tile board[SIZE][SIZE]) {
    for (int row = 0; row < SIZE; row++) { 
        for (int col = 0; col < SIZE; col++) {
            char type_char;
            if (board[row][col].occupied) {
                type_char = 'F';
            }
            else if (board[row][col].bug) {
                type_char = 'B';
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
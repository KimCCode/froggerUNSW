#include <stdlib.h>
#include <stdio.h>


int main() {
    char answer;
    int which_players_turn, pick, matches_remaining = 7;
    int picks_left = 7;

    int my_arr[7];

    printf("Do you want player 1 to go first (y/n): ");
    scanf("%c", &answer);
    if (answer == 'y') {
        which_players_turn = 0;
    } else if (answer == 'n') {
        which_players_turn = 1;
    } else {
        printf("You did not enter y/n");
    }

    printf("\n");

    for (int i = 1; i < 8; i++) {
        my_arr[i-1] = 1;
    }

    for (int j = 0; j < 7; j++) {
        printf("%d ", my_arr[j]);
    }

    printf("\n");

    while (picks_left > 0) {
        if (which_players_turn == 0) { // ask player 1 to pick the amount of matchsticks he wants to pick
            printf("\n");
            printf("Player 1 picks (1, 2 or 3) matchsticks: ");
            scanf("%i", &pick); // ask user for pick
            if (pick <= picks_left && pick > 0 && pick < 4){
                picks_left -= pick;
                which_players_turn = 1;
                printf("\n");
                for (int j = 0; j < picks_left; j++) {
                        printf("%d ", my_arr[j]);
                    }
            } else {
                printf("\n");
                printf("you can't pick that many matchsticks. Choose again.");
                printf("\n");
                printf("\n");
                for (int j = 0; j < picks_left; j++) {
                        printf("%d ", my_arr[j]);
                    }
            }
            printf("\n");

        }   
        else if (which_players_turn == 1) {
            printf("\n");
            printf("Player 2 picks (1, 2 or 3) matchsticks: ");
            scanf("%i", &pick); // ask user for pick
            if (pick <= picks_left && pick > 0 && pick < 4){
                picks_left -= pick;
                which_players_turn = 0;
                printf("\n");
            for (int j = 0; j < picks_left; j++) {
                    printf("%d ", my_arr[j]);
                }
            } else {
                printf("\n");
                printf("you can't pick that many matchsticks. Choose again.");
                printf("\n");
                printf("\n");
                for (int j = 0; j < picks_left; j++) {
                        printf("%d ", my_arr[j]);
                    }
            }
            printf("\n");
        }
    }

    if (which_players_turn == 0 && picks_left == 0) {
            printf("Player 2 wins!");
        } 
    else if (which_players_turn ==1 && picks_left == 0) {
            printf("Player 1 wins!");
        }

}
#include <stdlib.h>
#include <stdio.h>


int main() {
    char answer;
    int which_players_turn, pick, matches_remaining = 7;

    while (1) {
        printf("Do you want player 1 to go first (y/n): ");
        scanf("%c", answer);
        if (answer == 'y') {
            which_players_turn = 0;
            return which_players_turn;
        } else if (answer == 'n') {
            which_players_turn = 1;
            return which_players_turn;
        } else {
            printf("You did not enter y/n");
            }
        }

    while (matches_remaining > 1) {
        if (which_players_turn == 0) { // ask player 1 to pick the amount of matchsticks he wants to pick
            while (pick < 1  && pick > 3  && pick < matches_remaining) {
                printf("Player 1 picks: ");
                scanf("%i", &pick); // ask user for pick
            }
            matches_remaining -= pick; // updates matches remaining
            printf("There are %i matches remaining", matches_remaining);
            which_players_turn = 1; // allows player 2 to pick now -> confirm if this escapes the if statement
            return matches_remaining;
        } else if (which_players_turn == 1) {
            do {
                printf("Player 1 picks: ");
                scanf("%i", &pick); // ask user for pick
            } while (pick < 1 && pick > 3 && pick < matches_remaining);
            matches_remaining -= pick; // updates matches remaining
            printf("There are %i matches remaining", matches_remaining);
            which_players_turn = 0; // allows player 1 to pick now -> confirm if this escapes the if statement as well as stores updates which_player’s_turn
            return matches_remaining;
        }
    }

    if (which_players_turn == 0) {
        printf("Player 2 wins!");
    } else if (which_players_turn ==1) {
        printf("Player 1 wins!");
    }
}
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function prototypes
int Yahtzee(int Dice_array[]);
void random_num_gen(int *arr);
int Chance(int player_array[]);
int Ofa_kind(int arr[], int n);
int Upper_sec_combi(int arr[], int No);

int main() {
    srand(time(NULL)); // Seed the random number generator

    int game_category[13] = {0};
    int Dice_array[5], player_array[5];
    int com_plyr_sum[13] = {0}, plyr_sum[13] = {0};
    int move[1];

    printf("Welcome to Yahtzee!\n");

    for (int i = 0; i < 13; i++) { // Start of 13 rounds
        printf("\n--- Round %d ---\n", i + 1);

        // Computer's turn
        printf("Computer's Turn:\n");
        random_num_gen(Dice_array);
        com_plyr_sum[i] = Yahtzee(Dice_array); // Example move for Yahtzee

        // Player's turn
        printf("Your Turn:\n");
        random_num_gen(player_array);
        printf("Enter your move (1-12): ");
        scanf("%d", move);

        switch (move[0]) {
            case 1: plyr_sum[i] = Upper_sec_combi(player_array, 1); break; // Ones
            case 2: plyr_sum[i] = Upper_sec_combi(player_array, 2); break; // Twos
            case 3: plyr_sum[i] = Upper_sec_combi(player_array, 3); break; // Threes
            case 4: plyr_sum[i] = Upper_sec_combi(player_array, 4); break; // Fours
            case 5: plyr_sum[i] = Upper_sec_combi(player_array, 5); break; // Fives
            case 6: plyr_sum[i] = Upper_sec_combi(player_array, 6); break; // Sixes
            case 7: plyr_sum[i] = Ofa_kind(player_array, 3); break; // Three of a kind
            case 8: plyr_sum[i] = Ofa_kind(player_array, 4); break; // Four of a kind
            case 9: plyr_sum[i] = 25; break; // Full house
            case 10: plyr_sum[i] = 30; break; // Small straight
            case 11: plyr_sum[i] = 40; break; // Large straight
            case 12: plyr_sum[i] = Yahtzee(player_array); break; // Yahtzee
            case 13: plyr_sum[i] = Chance(player_array); break;
            default: printf("Invalid move. Try again.\n"); i--; break; // Retry
        }printf("%d",plyr_sum[i]);
    }

    // Calculate total scores
    int total_computer_score = 0, total_player_score = 0;
    for (int i = 0; i < 13; i++) {
        total_computer_score += com_plyr_sum[i];
        total_player_score += plyr_sum[i];
    }

    printf("\n--- Final Scores ---\n");
    printf("Computer: %d\n", total_computer_score);
    printf("Player: %d\n", total_player_score);

    return 0;
}

int Yahtzee(int Dice_array[]) {
    for (int i = 1; i < 5; i++) {
        if (Dice_array[i] != Dice_array[0]) {
            return 0; // No Yahtzee
        }
    }
    printf("Yahtzee!\n");
    return 50;
}

void random_num_gen(int *arr) {
    for (int i = 0; i < 5; i++) {
        arr[i] = (rand() % 6) + 1;
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int Chance(int player_array[]) {
    int sum = 0;
    for (int i = 0; i < 5; i++) {
        sum += player_array[i];
    }
    return sum;
}

int Ofa_kind(int arr[], int n) {
    int counts[7] = {0}, sum = 0;
    for (int i = 0; i < 5; i++) {
        counts[arr[i]]++;
        sum += arr[i];
    }
    for (int i = 1; i <= 6; i++) {
        if (counts[i] >= n) {
            return sum;
        }
    }
    return 0;
}

int Upper_sec_combi(int arr[], int No) {
    int sum = 0;
    for (int i = 0; i < 5; i++) {
        if (arr[i] == No) {
            sum += arr[i];
        }
    }
    return sum;
}
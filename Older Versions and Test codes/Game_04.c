#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

// Constants
#define NUM_DICE 5
#define NUM_CATEGORIES 13

// Define the Player structure
typedef struct {
    int dice[NUM_DICE];         // Array to store dice values
    int scores[NUM_CATEGORIES]; // Array to store scores for each category
    bool usedCategories[NUM_CATEGORIES]; // Tracks if a category is already used
} Player;

// Function prototypes
void initializePlayer(Player *player);
void rollDice(Player *player);
void printDice(Player *player);
int Yahtzee(Player *player);
int Chance(Player *player);
int Ofa_kind(Player *player, int n);
int Upper_sec_combi(Player *player, int No);
void displayScores(Player *player);


int main() {
    srand(time(NULL)); // Seed the random number generator

    Player human, computer; // Create two players
    initializePlayer(&human);
    initializePlayer(&computer);

    printf("Welcome to Yahtzee!\n");

    for (int round = 0; round < NUM_CATEGORIES; round++) {
        printf("\n--- Round %d ---\n", round + 1);

        // Computer's turn
        printf("Computer's Turn:\n");
        rollDice(&computer);
        printDice(&computer);
        
        

////////////////////////////////////////////////////////////////////////////////
        printf("Your Turn:\n");
        rollDice(&human);
        printDice(&human);

        int category;
        do {
            printf("Enter your move (1-13): ");
            scanf("%d", &category);
            category -= 1; // Convert to 0-based index
        } while (category < 0 || category >= NUM_CATEGORIES || human.usedCategories[category]);

        // Score calculation
        switch (category) {
            case 0: human.scores[category] = Upper_sec_combi(&human, 1); break; // Ones
            case 1: human.scores[category] = Upper_sec_combi(&human, 2); break; // Twos
            case 2: human.scores[category] = Upper_sec_combi(&human, 3); break; // Threes
            case 3: human.scores[category] = Upper_sec_combi(&human, 4); break; // Fours
            case 4: human.scores[category] = Upper_sec_combi(&human, 5); break; // Fives
            case 5: human.scores[category] = Upper_sec_combi(&human, 6); break; // Sixes
            case 6: human.scores[category] = Ofa_kind(&human, 3); break;        // Three of a kind
            case 7: human.scores[category] = Ofa_kind(&human, 4); break;        // Four of a kind
            case 8: human.scores[category] = 25; break;                        // Full house
            case 9: human.scores[category] = 30; break;                        // Small straight
            case 10: human.scores[category] = 40; break;                       // Large straight
            case 11: human.scores[category] = Yahtzee(&human); break;          // Yahtzee
            case 12: human.scores[category] = Chance(&human); break;           // Chance
        } printf("score: %d", human.scores[category]);
        human.usedCategories[category] = true; // Mark category as used
    }

    // Calculate and display final scores
    int total_computer_score = 0, total_player_score = 0;

    for (int i = 0; i < NUM_CATEGORIES; i++) {
        //total_computer_score += computer.scores[i];
        total_player_score += human.scores[i];
    }

    printf("\n--- Final Scores ---\n");
    //printf("Computer: %d\n", total_computer_score);
    printf("Player: %d\n", total_player_score);

    if (total_player_score > total_computer_score) {
        printf("Congratulations! You win!\n");
    } else if (total_player_score < total_computer_score) {
        printf("The computer wins. Better luck next time!\n");
    } else {
        printf("It's a tie!\n");
    }

    return 0;
}

// Initialize the player
void initializePlayer(Player *player) {
    for (int i = 0; i < NUM_CATEGORIES; i++) {
        player->scores[i] = 0;
        player->usedCategories[i] = false;
    }
}

// Roll dice for a player
void rollDice(Player *player) {
    for (int i = 0; i < NUM_DICE; i++) {
        player->dice[i] = (rand() % 6) + 1;
    }
}

// Print the dice values
void printDice(Player *player) {
    printf("Dice: ");
    for (int i = 0; i < NUM_DICE; i++) {
        printf("%d ", player->dice[i]);
    }
    printf("\n");
}

// Yahtzee scoring
int Yahtzee(Player *player) {
    for (int i = 1; i < NUM_DICE; i++) {
        if (player->dice[i] != player->dice[0]) {
            return 0; // No Yahtzee
        }
    }
    printf("Yahtzee!\n");
    return 50;
}

// Chance scoring
int Chance(Player *player) {
    int sum = 0;
    for (int i = 0; i < NUM_DICE; i++) {
        sum += player->dice[i];
    }
    return sum;
}

// Three/Four of a Kind scoring
int Ofa_kind(Player *player, int n) {
    int counts[7] = {0}, sum = 0;
    for (int i = 0; i < NUM_DICE; i++) {
        counts[player->dice[i]]++;
        sum += player->dice[i];
    }
    for (int i = 1; i <= 6; i++) {
        if (counts[i] >= n) {
            return sum;
        }
    }
    return 0;
}

// Upper section scoring
int Upper_sec_combi(Player *player, int No) {
    int sum = 0;
    for (int i = 0; i < NUM_DICE; i++) {
        if (player->dice[i] == No) {
            sum += player->dice[i];
        }
    }
    return sum;
}

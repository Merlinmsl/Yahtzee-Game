#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

// Constants
#define NUM_DICE 5
#define NUM_CATEGORIES 13
#define NUM_SIDES 6 // Dice have 6 sides (1–6)

// Define the Player structure
typedef struct {
    int dice[NUM_DICE];         // Array to store dice values
    int scores[NUM_CATEGORIES]; // Array to store scores for each category
    bool usedCategories[NUM_CATEGORIES]; // Tracks if a category is already used
} Player;

// Function declaration
void initializePlayer(Player *player);
void rollDice(Player *player);
void printDice(Player *player);
int Yahtzee(Player *player);
int Chance(Player *player);
int Ofa_kind(Player *player, int n);
int Upper_sec_combi(Player *player, int No);
void displayScores(Player *player);
void diceSort(Player *player);
void countOccurrences(Player *player, int frequencies[]);
void evaluateComputerMove(Player *player, int frequencies[]);


int main() {
    srand(time(NULL)); // Seed the random number generator

    Player human, computer; // Create two players
    initializePlayer(&human);
    initializePlayer(&computer);
    
    int frequencies[NUM_SIDES];          // Array to store frequencies

    printf("Welcome to Yahtzee!\n");

    for (int round = 0; round < NUM_CATEGORIES; round++) {
        printf("\n\n--- Round %d ---\n", round + 1);
/////////////////////////////////////////////////////////////////////////////////
        // Computer's turn
        printf("Computer's Turn:\n");
        rollDice(&computer);
        diceSort(&computer);
        printDice(&computer);
        countOccurrences(&computer, frequencies); // Update frequencies
        evaluateComputerMove(&computer, frequencies); // Evaluate and choose the best move
        

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
////////////////////////////////////////////////////////////////////////////
void diceSort(Player *player){
    for(int i = 0; i<NUM_DICE; i++){
        for(int j = i + 1; j<NUM_DICE; j++){
            if(player->dice[j] < player->dice[i]){
                int temp = player->dice[i];
                player->dice[i] = player->dice[j];
                player->dice[j] = temp;
            }
        }
    }
}

// Function to count occurrences of each dice number
void countOccurrences(Player *player, int frequencies[]) {
    // Initialize frequencies to 0
    for (int i = 0; i < NUM_SIDES; i++) {
        frequencies[i] = 0;
    }

    // Count occurrences
    for (int i = 0; i < NUM_DICE; i++) {
        frequencies[player->dice[i] - 1]++; // Map dice values (1–6) to indices (0–5)
    }
///////////////////////////////////////////////////////////////
   /* 
    printf("Frequencies: ");
    for (int i = 0; i < NUM_SIDES; i++) {
        printf("%d ", frequencies[i]);
    }
    printf("\n");*/
////////////////////////////////////////////////////////////////
    // Print the results
    /*printf("Number frequencies:\n");
    for (int i = 0; i < NUM_SIDES; i++) {
        if (frequencies[i] > 0) {
            printf("Number %d: %d times\n", i + 1, frequencies[i]);
        }
    }*/
}

void evaluateComputerMove(Player *player, int frequencies[]) {
    int bestScore = 0;    // Store the highest score found
    int bestCategory = -1; // Store the category index for the best score
    int score = 0;         // Use this for all scoring calculations

    printf("Computer evaluating categories...\n");

    // Debug: Print used categories
    printf("Used categories: ");
    for (int i = 0; i < NUM_CATEGORIES; i++) {
        printf("%d ", player->usedCategories[i]);
    }
    printf("\n");

    // Upper Section (Ones to Sixes)
    for (int i = 0; i < 6; i++) { // Categories 0–5 (Ones to Sixes)
        if (!player->usedCategories[i]) { // Check if category is unused
            score = frequencies[i] * (i + 1); // Dice value times its frequency
            printf("Category %d (Upper Section): Score = %d\n", i + 1, score);
            if (score > bestScore) {
                bestScore = score;
                bestCategory = i;
            }
        }
    }

    // Three of a Kind (Category 7)
    if (!player->usedCategories[6]) {
        score = Ofa_kind(player, 3);
        printf("Category 7 (Three of a Kind): Score = %d\n", score);
        if (score > bestScore) {
            bestScore = score;
            bestCategory = 6;
        }
    }

    // Four of a Kind (Category 8)
    if (!player->usedCategories[7]) {
        score = Ofa_kind(player, 4);
        printf("Category 8 (Four of a Kind): Score = %d\n", score);
        if (score > bestScore) {
            bestScore = score;
            bestCategory = 7;
        }
    }

    // Full House (Category 9)
    if (!player->usedCategories[8]) {
        bool hasThree = false, hasTwo = false;
        for (int i = 0; i < NUM_SIDES; i++) {
            if (frequencies[i] == 3) hasThree = true;
            if (frequencies[i] == 2) hasTwo = true;
        }
        if (hasThree && hasTwo) {
            score = 25;
            printf("Category 9 (Full House): Score = %d\n", score);
            if (score > bestScore) {
                bestScore = score;
                bestCategory = 8;
            }
        }
    }

    // Small Straight (Category 10)
    if (!player->usedCategories[9]) {
        if ((frequencies[0] > 0 && frequencies[1] > 0 && frequencies[2] > 0 && frequencies[3] > 0) ||
            (frequencies[1] > 0 && frequencies[2] > 0 && frequencies[3] > 0 && frequencies[4] > 0) ||
            (frequencies[2] > 0 && frequencies[3] > 0 && frequencies[4] > 0 && frequencies[5] > 0)) {
            score = 30;
            printf("Category 10 (Small Straight): Score = %d\n", score);
            if (score > bestScore) {
                bestScore = score;
                bestCategory = 9;
            }
        }
    }

    // Large Straight (Category 11)
    if (!player->usedCategories[10]) {
        if ((frequencies[0] == 1 && frequencies[1] == 1 && frequencies[2] == 1 && frequencies[3] == 1 && frequencies[4] == 1) ||
            (frequencies[1] == 1 && frequencies[2] == 1 && frequencies[3] == 1 && frequencies[4] == 1 && frequencies[5] == 1)) {
            score = 40;
            printf("Category 11 (Large Straight): Score = %d\n", score);
            if (score > bestScore) {
                bestScore = score;
                bestCategory = 10;
            }
        }
    }

    // Yahtzee (Category 12)
    if (!player->usedCategories[11]) {
        if (Yahtzee(player)) {
            score = 50;
            printf("Category 12 (Yahtzee): Score = %d\n", score);
            if (score > bestScore) {
                bestScore = score;
                bestCategory = 11;
            }
        }
    }

    // Chance (Category 13)
    if (!player->usedCategories[12]) {
        score = Chance(player);
        printf("Category 13 (Chance): Score = %d\n", score);
        if (score > bestScore) {
            bestScore = score;
            bestCategory = 12;
        }
    }

    // Assign the best category and score to the computer
    if (bestCategory != -1) {
        player->scores[bestCategory] = bestScore;
        player->usedCategories[bestCategory] = true;
        printf("Computer chose category %d with a score of %d\n", bestCategory + 1, bestScore);
    } else {
        printf("ERROR: Computer failed to select a valid category.\n");
    }
}

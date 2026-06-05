#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

// Constants
#define NUM_DICE 5  // No of dices
#define NUM_CATEGORIES 14 // 13 plus Bonus chance
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
int Large_straight (Player *player, int frequencies[]);
int Small_straight (Player *player, int frequencies[]);
int Full_house (Player *player, int frequencies[]);
int Ofa_kind(Player *player, int n);
int Upper_sec_combi(Player *player, int No);
void displayScores(Player *player);
void diceSort(Player *player);
void countOccurrences(Player *player, int frequencies[]);
void evaluateComputerMove(Player *player, int frequencies[], int recurs_n); 
void diceReroll_plyr(Player *player);
void frequency_up (Player *player, int frequencies[], int *recurs_n);  // Passing the address of the recurs_n value 

int main() {
    srand(time(NULL));// Seed the random number generator
    
    
    Player human, computer; // Create two players
    initializePlayer(&human);
    initializePlayer(&computer);
    
    int frequencies[NUM_SIDES]; // Array to store frequencies

    printf("Welcome to Yahtzee!\n\n");
    
    printf("--These are the Categories and their Indexes--\n *(Use these Indexes when chosing a category)*\n\n");
    printf("--Index-- | --Category--\n");
    printf("    1        Ones\n");
    printf("    2        Twos\n");
    printf("    3        Threes\n");
    printf("    4        Fours\n");
    printf("    5        Fivess\n");
    printf("    6        Sixes\n");
    printf("    7        Three of a kind\n");
    printf("    8        Four of a kind\n");
    printf("    9        Full house\n");
    printf("    10       Small straight\n");
    printf("    11       Large straight\n");
    printf("    12       Yahtzee\n");
    printf("    13       Chance\n");
    printf("    14       Bonus Yahtzee\n");
    printf("--------------------------------------------------------------------");

    for (int round = 0; round < NUM_CATEGORIES - 1; round++) {
        printf("\n\n--- Round %d ---\n", round + 1);
        

////////////////////////////////////////////////////////////////////////////////
        //Player's turn
        printf("\nYour Turn:\n");
        rollDice(&human);
        printDice(&human);
        // Print used categories
        printf("................ 1  2  3  4  5  6  7  8  9 10 11 12 13 14\n");
        printf("Used categories: ");
        for (int i = 0; i < NUM_CATEGORIES; i++) {
            printf("%d  ", human.usedCategories[i]);
        }
        printf("\n");
///////////////////////////////////////////////////////////////////////////////
        diceReroll_plyr(&human);
        countOccurrences(&human, frequencies);
///////////////////////////////////////////////////////////////////////////////
        
        int category;
        do {
            printf("Enter your move (1-13): ");
            scanf("%d", &category);
            category -= 1; // Convert to 0-based index
        } while (category < 0 || category >= (NUM_CATEGORIES) || human.usedCategories[category]);

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
            case 8: human.scores[category] = Full_house (&human, frequencies); break;   // Full house
            case 9: human.scores[category] = Small_straight (&human, frequencies); break; // Small straight
            case 10: human.scores[category] = Large_straight (&human, frequencies);; break; // Large straight
            case 11: human.scores[category] = Yahtzee(&human); break;          // Yahtzee
            case 12: human.scores[category] = Chance(&human); break;           // Chance
            case 13: human.scores[category] = 100; break;                // Bonus Yahtzee
            
        } printf("score: %d\n\n", human.scores[category]);
        human.usedCategories[category] = true; // Mark category as used
        
        /////////////////////////////////////////////////////////////////////////////////

        //Computer's turn
        int recurs_n = 0;  // Recursion times
        printf("Computer's Turn:\n");
        rollDice(&computer); // Roll computer player dices
        diceSort(&computer); // Sort dices in increasing oder
        printDice(&computer);
        countOccurrences(&computer, frequencies); // Update frequencies
        evaluateComputerMove(&computer, frequencies, recurs_n); // Evaluate and choose the best move
        

        
    }

    // Calculate and display final scores
    int total_computer_score = 0, total_player_score = 0;

    for (int i = 0; i < NUM_CATEGORIES; i++) {
        total_computer_score += computer.scores[i];
        total_player_score += human.scores[i];
    }

    printf("\n\n--- Final Scores ---\n");
    printf("Computer: %d\n", total_computer_score);
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

////////////////////////////////////////////////////////////////////////////////

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

// Reroll Human Player's selected dices
void diceReroll_plyr (Player *player) {
    for (int i = 0; i < 2;i++){
            int Y, reroll[5] = {0};
            printf("Reroll? (Enter 1 for YES and 0 for NO) : ");
            scanf("%d", &Y);
            if (Y == 1) {
                printf("Which dices do you want to roll? (Enter 1 for yes and 0 for no): ");
                for (int j = 0; j < 5; j++){
                    scanf("%d", &reroll[j]);
                }
                for (int k = 0; k < 5; k++) {
                    if (reroll[k] == 1) {
                        player->dice[k] = (rand() % 6) + 1;
                    }
                    else if (reroll[k] == 0) {
                        continue;
                    } 
                } printDice(player); 
            }
            else if (Y == 0) {
                //printDice(&human);
                break;
            }
            else {
                printf("Invalid Input!..\n");
                continue;
            } 
                
        }
        //printDice(&human);
}

// Yahtzee scoring
int Yahtzee(Player *player) {
    int n = 0;
    for (int i = 1; i < NUM_DICE; i++) {
        if (player->dice[0] == player->dice[i]) {
            n += 1;
        }
    }

    if(n == 4){
        return 50;
    } else {return 0;}
}

// Chance scoring
int Chance(Player *player) {
    int sum = 0;
    for (int i = 0; i < NUM_DICE; i++) {
        sum += player->dice[i];
    }
    return sum;
}

    // Full House
int Full_house (Player *player, int frequencies[]) {
    bool hasThree = false, hasTwo = false;
    for (int i = 0; i < NUM_SIDES; i++) {
        if (frequencies[i] == 3) hasThree = true;
        if (frequencies[i] == 2) hasTwo = true;
    }
    if (hasThree && hasTwo) {
        return 25; 
    }
    else {return 0;}
        
}

    // Small Straight 
int Small_straight(Player *player, int frequencies[]) {
    if ((frequencies[0] >= 1 && frequencies[1] >= 1 && frequencies[2] >= 1 && frequencies[3] >= 1) ||
            (frequencies[1] >= 1 && frequencies[2] >= 1 && frequencies[3] >= 1 && frequencies[4] >= 1) ||
            (frequencies[2] >= 1 && frequencies[3] >= 1 && frequencies[4] >= 1 && frequencies[5] >= 1)) {
        return 30; 
            
    }else {return 0;}
}

    // Large Straight
int Large_straight(Player *player, int frequencies[]) {
    if ((frequencies[0] >= 1 && frequencies[1] >= 1 && frequencies[2] >= 1 && frequencies[3] >= 1 && frequencies[4] >= 1) ||
            (frequencies[1] >= 1 && frequencies[2] >= 1 && frequencies[3] >= 1 && frequencies[4] >= 1 && frequencies[5] >= 1)) {
        return 40; 

    } else {return 0;}
}


// Three/Four of a Kind scoring
int Ofa_kind(Player *player, int n) {
    int counts[7] = {0}, sum = 0;  // count[7] because we can assign values from 1-6 insted of 0-5. So this avoids the need for subtracting 1 from the dice value to map it to the correct array index.
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
////////////////////////////////////////////////////////////////////////////////
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

////////////////////////////////////////////////////////////////////////////////
                    //    Computer AI     //
                    
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

}

// Increase the frequencies to match a Lower Section Category
void frequency_up (Player *player, int frequencies[], int *recurs_n){
    
    if (*recurs_n >= 2) {
    return; // Stop recursion when the depth limit is reached
    }

    // From 3-6
    for (int i = 2; i<6; i++){
        if (frequencies[i] >= 3 && *recurs_n < 2) {
            for (int k = 0; k<5; k++){
                if(player->dice[k] != i+1){
                    player->dice[k] = (rand() % 6) + 1;
                }
            }
            printf("Rerolling Dices...\n");
            diceSort(player);
            printDice(player);
            countOccurrences(player, frequencies);
            *recurs_n += 1;
            frequency_up (player, frequencies, recurs_n);
        }

    }

}



void evaluateComputerMove(Player *player, int frequencies[], int recurs_n) {
    int bestScore = 0;    // Store the highest score found
    int bestCategory = -1; // Store the category index for the best score
    int score = 0;
    int saveCategory[6] = {0}; // Store a fallback upper section category if needed
    int lastHopeChance = 0;  // If there's no category to select & chance score < 25

    printf("Computer evaluating categories...\n");

    countOccurrences(player, frequencies);  // Calculate frequencies
    
    frequency_up (player, frequencies, &recurs_n);  // Increase the frequencies


    // Print used categories
    printf("Used categories: ");
    for (int i = 0; i < NUM_CATEGORIES; i++) {
        printf("%d ", player->usedCategories[i]);
    }
    printf("\n");

    // Upper Section (Ones to Sixes)
    for (int i = 0; i < 6; i++) {
        // Select a dice pattern with frequency more than 2
        if (!player->usedCategories[i]){
            
                score = frequencies[i] * (i + 1); // Dice value times its frequency

                printf("Category %d (Upper Section): Score = %d\n", i + 1, score);


                if (score > bestScore && frequencies[i] >= 2) { 
                    /* chose an pattern with more than 1 frequency */
                    bestScore = score;
                    bestCategory = i ; // Align category numbering with 1-based index
                }
                
                else if (frequencies[i] < 2 && saveCategory[i] == 0) {
                    saveCategory[i] = i;
                }
            
        }
    }

    // Four of a Kind (Category 7)
    if (!player->usedCategories[7]) {
        score = Ofa_kind(player, 4);
        printf("Category 8 (Four of a Kind): Score = %d\n", score);
        if (score > bestScore) {
            bestScore = score;
            bestCategory = 7;
        } else { score = 0;}
    }

    // Three of a Kind (Category 6)
    if (!player->usedCategories[6]) {
        score = Ofa_kind(player, 3);
        printf("Category 7 (Three of a Kind): Score = %d\n", score);
        if (score > bestScore ) {
            bestScore = score;
            bestCategory = 6;
        } else { score = 0;}
    }

    // Full House (Category 8)
    if (!player->usedCategories[8]) {
        bool hasThree = false, hasTwo = false;
        for (int i = 0; i < NUM_SIDES; i++) {
            if (frequencies[i] == 3) hasThree = true;
            if (frequencies[i] == 2) hasTwo = true;
        }
        if (hasThree && hasTwo) {
            score = 25; 
            
            if (score > bestScore) {
                bestScore = score;
                bestCategory = 8;
            }
        }
        else {score = 0;}
        printf("Category 9 (Full House): Score = %d\n", score);
        
    }

    // Small Straight (Category 9)
    if (!player->usedCategories[9]) {
        if ((frequencies[0] >= 1 && frequencies[1] >= 1 && frequencies[2] >= 1 && frequencies[3] >= 1) ||
            (frequencies[1] >= 1 && frequencies[2] >= 1 && frequencies[3] >= 1 && frequencies[4] >= 1) ||
            (frequencies[2] >= 1 && frequencies[3] >= 1 && frequencies[4] >= 1 && frequencies[5] >= 1)) {
            score = 30; 
            
                
                if (score > bestScore) {
                    bestScore = score;
                    bestCategory = 9;
            }
        }else {score = 0;}
        printf("Category 10 (Small Straight): Score = %d\n", score);
    }

    // Large Straight (Category 10)
    if (!player->usedCategories[10]) {
        if ((frequencies[0] >= 1 && frequencies[1] >= 1 && frequencies[2] >= 1 && frequencies[3] >= 1 && frequencies[4] >= 1) ||
            (frequencies[1] >= 1 && frequencies[2] >= 1 && frequencies[3] >= 1 && frequencies[4] >= 1 && frequencies[5] >= 1)) {
            score = 40; 
            
                
                if (score > bestScore) {
                    bestScore = score;
                    bestCategory = 10;
            }
        } else {score = 0;}
        printf("Category 11 (Large Straight): Score = %d\n", score);
    }

    // Yahtzee (Category 11)
    if (!player->usedCategories[11]) {
        int x = Yahtzee(player);
        if (x == 50) {
            score = 50; 
        
            
            if (score > bestScore) {
                bestScore = score;
                bestCategory = 11;
            }
        } else {score = 0;}
        printf("Category 12 (Yahtzee): Score = %d\n", score);
    }

    // Chance (Category 12)
    if (!player->usedCategories[12]) {
        score = Chance(player);
        lastHopeChance = score; // store the value if needed as the last chance
        printf("Category 13 (Chance): Score = %d\n", score);
        if (score > bestScore && score >= 16) {
            bestScore = score;
            bestCategory = 12;
        } 
    }

    // Bonus Yahtzee (Category 14)
    if (player->usedCategories[11]) {
        int x = Yahtzee(player);
        if (x == 50) {
            score = 100; 
        
            
            if (score > bestScore) {
                bestScore = score;
                bestCategory = 13;
            }
        } else {score = 0;}
        printf("Bonus Yahtzee!: Score = %d\n", score);
    
    }

//////////////////////////////////////////////////////////////////////////////////////



    // If no valid lower section category was chosen, choose a remaining upper section category
    for (int j = 5; j>=0; j--) { // Chose from backword to find the highest value
        if (bestCategory == -1 && saveCategory[j] != 0 && !player->usedCategories[j]) {
            
            bestCategory = j; // (0-5)
            bestScore = j+1; // (1-6)
        }
    }

    // If didn't chose chance before & score < 25, chose chance category as the last chance
    if (bestCategory == -1 && !player->usedCategories[12]) {
        bestCategory = 12;
        bestScore = lastHopeChance;
        }
    





    // Assign the best category and score to the computer
    if (bestCategory != -1) {
        player->scores[bestCategory] = bestScore;
        player->usedCategories[bestCategory] = true;
        printf("Computer chose category %d with a score of %d\n\n", bestCategory + 1, bestScore);
    } else {
        printf("Failed to select a valid category from the remaining.\n\n");
    }


}
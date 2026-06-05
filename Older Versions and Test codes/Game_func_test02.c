#include <stdio.h>

#define NUM_DICE 5
#define NUM_SIDES 6 // Dice have 6 sides (1–6)

// Function to count occurrences of each dice number
void countOccurrences(int dice[], int frequencies[]) {
    // Initialize frequencies to 0
    for (int i = 0; i < NUM_SIDES; i++) {
        frequencies[i] = 0;
    }

    // Count occurrences
    for (int i = 0; i < NUM_DICE; i++) {
        frequencies[dice[i] - 1]++; // Map dice values (1–6) to indices (0–5)
    }

    // Print the results
    printf("Number frequencies:\n");
    for (int i = 0; i < NUM_SIDES; i++) {
        if (frequencies[i] > 0) {
            printf("Number %d: %d times\n", i + 1, frequencies[i]);
        }
    }
}
int main() {
    int dice[NUM_DICE] = {1, 4, 4, 6, 4}; // Example dice rolls
    int frequencies[NUM_SIDES];          // Array to store frequencies

    countOccurrences(dice, frequencies);

    return 0;
}

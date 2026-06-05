#include <stdio.h>

void Yahtzee(int Dice_array[], int size) {
    int isYahtzee = 1; // Assume all elements are the same
    for(int i = 1; i < size; i++) {
        if(Dice_array[i] != Dice_array[0]) {
            isYahtzee = 0; // Found a different element
            break;
        }
    }
    if(isYahtzee) {
        printf("Yahtzee!\n");
    } else {
        printf("No yahtzee\n");
    }
}

int main() {
    int Dice_array[] = {6, 6, 6, 6, 5}; // Example array
    int size = sizeof(Dice_array) / sizeof(Dice_array[0]);
    Yahtzee(Dice_array, size);
    return 0;
}

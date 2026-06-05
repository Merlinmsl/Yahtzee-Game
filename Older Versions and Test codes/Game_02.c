#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int Yahtzee(int Dice_array[]){
    int isYahtzee = 1; // Assume all elements are the same
    for(int i=1;i<6;i++){
        if(Dice_array[i] != Dice_array[0]){
            isYahtzee = 0;
        }
    }
    if(isYahtzee) {
        printf("Yahtzee!\n");
        return 50;
    } else {
        printf("No yahtzee\n");return 0;
    }
}

void random_num_gen(int *Dice_array){
    for (int i = 0; i < 5; i++) {  // Making random numbers
        int randomNumber = (rand() % 6 +1);
        Dice_array[i] = randomNumber;
        printf("%d ", randomNumber);
    }printf("\n");    
}

void Chance(int player_array){
    int sum = 0;
    for(int i=0;i<=5;i++){
        sum += player_array[i];
    }return sum;
}

int main() {
    srand(time(NULL)); // Seed the random number generator with the current time
    int game_category[13], Dice_array[5], player_array[5], com_plyr_sum[20], plyr_sum[20]; // Initialize the game point categories as an array
    char move;
    
    for(int i=0;i<13;i++){
        game_category[i] = 0; // Make all the array values are 0
    }
    
    for(int i=0;i<13;i++){ // Start of the 13 rounds
        printf("Random numbers with time seed:\n");

        random_num_gen(Dice_array); // Random number gene. function call for the computer player
        
    com_plyr_sum[i] = Yahtzee(Dice_array);
    //printf("%d\n",com_plyr_sum[i]); 
    ////////////////////////////////////////////////////////////////////////////////////////
    
    /*printf("Your turn:\n");
    random_num_gen(player_array); // Player dice random number call
    printf("Enter your move: "); // Taking the players desire move
    scanf("%d", &move);
    switch (move){
        case 1: ; break; 
        case 2: ; break;
        case 3: ; break;
        case 4: ; break;
        case 5: ; break;
        case 6: ; break;
        case 7: ; break;
        case 8: Chance(player_array); break;
        case 9: plyr_sum[i] = 25; break;
        case 10: plyr_sum[i] = 30; break;
        case 11: plyr_sum[i] = 40; 
    }*/
    }
    

    return 0;
}
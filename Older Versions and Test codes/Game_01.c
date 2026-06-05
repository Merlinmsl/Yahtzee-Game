#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void Yahtzee(){
    for(int i=0;i<4;i++){
        for(int j=i+1;j<3;j++){

        }
        
    }
}

int main() {
    srand(time(NULL));// Seed the random number generator with the current time
    int game_category[13], Dice_array[5]; //Initialize the game point categories as an array
    for(int i=0;i<13;i++){
        game_category[i] = 0; //make all the array values are 0
    }
    
    for(int i=0;i<13;i++){
        printf("Random numbers with time seed:\n");
        for (int i = 0; i < 5; i++) {
            int randomNumber = (rand() % 6 +1);
            Dice_array[i] = randomNumber;
            printf("%d ", randomNumber);
        }printf("\n");}

    return 0;
}
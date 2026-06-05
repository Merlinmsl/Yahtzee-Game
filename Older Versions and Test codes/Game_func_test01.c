// Online C compiler to run C program online
#include <stdio.h>
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

int abc(Player *player){
    int n[NUM_DICE] = {0}; // Array to store the count of each number
    int Value[NUM_DICE] = {0}; // Array to store the repeated numbers
    int No = 0; // Counter for the number of repeated numbers
    
    for(int i = 0; i<NUM_DICE; i++){
        for(int j = i + 1; j<NUM_DICE; j++){
            if(player->dice[j] == player->dice[i]){
                No += 1;
                //n[i] = No;
                Value[i] = player->dice[j];
            }
        }n[i] = No;
    }    
}

int main() {


    return 0;
}
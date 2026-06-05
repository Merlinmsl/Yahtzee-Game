// Online C compiler to run C program online
#include <stdio.h>

int main() {

    for (int i = 0; i < 2;i++){
        int Y, reroll[5] = {0};
        printf("Reroll? ");
        scanf("%d", &Y);
        if (Y == 1) {
            printf("Which dices do you want to roll? (Enter 1 for yes and 0 for no)");
            scanf("%d", reroll[i]);
            for (int i = 0; i < 5; i++) {
                if (reroll[i] == 1) {
                    human.dice[i] = (rand() % 6) + 1;
                }
                else if (reroll[i] == 0) {
                    break;
                }
            }
        }
        else if (Y == 0) {
            break;
        }
    }
    return 0;
}
#include <stdio.h>

int main() {
    int arr[5] =  {0};
    int i;

    printf("Enter 5 integers: ");
    for (i = 0; i < 5; i++) {
        scanf("%d", &arr[i]); 
    }

    printf("The array elements are: ");
    for (i = 0; i < 5; i++) {
        printf("%d ", arr[i]); 
    }

    return 0;
}

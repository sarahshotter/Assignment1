#include <stdio.h>

int encrypt(int *x, int *y, int shift);

int main() {
    int alpha[26]; //array with 26 elements
    int i;
    int alphaCopy[26];
    int n, k;
    
    for (i = 0; i < 26; i++) { //array with 26 elements
        alpha[i] = i + 65; //elements range from 65 to 90
        alphaCopy[i] = i + 65; //second array with elements ranging from 65 to 90
        /* there are two arrays with the same elements to allow us to edit one 
        from the other without changing the elements of the first one without the 
        need for temporary variables*/
        printf("%d      %d\n", alpha[i], alphaCopy[i]);
        /*print the first array next to the second to show similarity*/
    }
    
    encrypt(alpha, alphaCopy, k);
    
    return 0;
}

int encrypt(int *x, int *y, int shift) {
    printf("Enter a shift value:    ");
    scanf("%d", &shift);
    for (int i = 0; i < 26 - shift; i++) {
        y[i] = x[i + shift];
        printf("%d      %d\n", x[i], y[i]);
    }
}

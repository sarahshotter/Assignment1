#include <stdio.h>

int encrypt(int x[], int shift);

int main() {
    int alpha[26]; //array with 26 elements
    int i;
    int alphaCopy[26];
    int n, k = 3;
    
    for (i = 0; i < 26; i++) { //array with 26 elements
        alpha[i] = i + 65; //elements range from 65 to 90
        alphaCopy[i] = i + 65; //second array with elements ranging from 65 to 90
        /* there are two arrays with the same elements to allow us to edit one 
        from the other without changing the elements of the first one without the 
        need for temporary variables*/
        printf("%d      %d\n", alpha[i], alphaCopy[i]);
        /*print the first array next to the second to show similarity*/
    }
    
    for (n = 0; n < 26; n++) {
        alpha[n];
        if (n + k > 26) { //this is broken!
            alphaCopy[n] = alpha[n];
        }
        alphaCopy[n] = alphaCopy[n + k];
        
        printf("\n%d      %d", alpha[n], alphaCopy[n]); //displays old array next to new array
    }
    
    return 0;
}

int encrypt(int x[], int shift) {
    int index;
    printf("Enter a shift value:    ");
    scanf("%d", &shift);
    if (shift > 0) {
        shift = shift%25;
        x[index] = x[index + shift];
    } else if (shift < 0) {
        shift = shift%25;
        x[index] = x[index + shift];
    } else {
        return 0;
    }
}

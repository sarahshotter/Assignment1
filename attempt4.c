#include <stdio.h>
#include <math.h>

int encrypt(int *x, int *y, int shift);

int main() {
    int alpha[26]; //array with 26 elements
    int i;
    int alphaCopy[26];
    int k;
    
    for (i = 0; i < 26; i++) { //array with 26 elements
        alpha[i] = i + 65; //elements range from 65 to 90
        alphaCopy[i] = i + 65; //second array with elements ranging from 65 to 90
        /* there are two arrays with the same elements to allow us to edit one from the other without changing the elements of the first one without the need for temporary variables*/
    }
    
    encrypt(alpha, alphaCopy, k);
    
    return 0;
}

int encrypt(int *x, int *y, int shift) {
    printf("Enter a shift value:    ");
    scanf("%d", &shift);
    
    int indexT, index; //indexT represents a temporary index
    
    int tempShift = abs((26 + shift)%26); //Accommodating for negative values for shift
    
    for (index = 0; index < 26 - tempShift; index++) {
        y[index] = x[index + tempShift];
    }
    
    for (indexT = 0; indexT < tempShift; indexT++) {
        y[26 - tempShift + indexT] = x[indexT];
    }
    
    for (index = 0; index < 26; index++) {
        printf("%d      %d\n", x[index], y[index]);
    }
}

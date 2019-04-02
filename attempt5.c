#include <stdio.h>
#include <math.h>


/*Prototype sets up the function encrypt, which utilises two arrays and an integer shift, 
to transform a second array from the first using a shift factor*/
int encrypt(int *x, int *y, int shift);

int main() {
    int alpha[26], alphaCopy[26]; //Declaration of 2 arrays of length 26
    int i, k; 
    
    for (i = 0; i < 26; i++) { //array with 26 elements
        alpha[i] = i + 65; //elements range from 65 to 90
        alphaCopy[i] = i + 65; //second array with elements ranging from 65 to 90
        /* there are two arrays with the same elements to allow us to edit one from the 
        other without changing the elements of the first one without the need for temporary variables*/
    }
    
    /*passing the elements of both the alpha and alphaCopy array to the encrypt function*/
    encrypt(alpha, alphaCopy, k);
    
    return 0;
}

/*Definition of the encrypt function occurs after the int main() code block*/

int encrypt(int *x, int *y, int shift) {
    printf("Enter a shift value:    "); //printf encourages the user to input a value to shift the ASCII values by
    scanf("%d", &shift);    //scanf allocates the value input by the user to a memory address, in this case it is shift, 
                            //which will be used as the shift factor for the function 
    
    int indexT, index; //indexT represents a temporary index, and index that of the elements in the arrays
    
    /*% takes the remainder of the division and abs is the absolute function accommodating for negative values for shift. 
    As the Caesar ciper is a ring structure,  a positive shift of greater than 26 would result in a negative shift of the corresponding 
    number past 26, that is if the shift was 29, this would be equivalent to a shift of -3. This also applies in reverse for negative 
    shift being related to their positive counterparts*/
    int tempShift = abs((26 + shift)%26);   
    
    /*the for loop takes values of x[] i + some shift's value and assigns it to the array y[]'s ith element and then repeats this 
    process for all required values of index to suffice the conditions of the for loop thus encrypting the y[] array*/
    for (index = 0; index < 26 - tempShift; index++) {  
        y[index] = x[index + tempShift];
    }
    
    /*The for loop takes the values shift factor distance from the end of y[] + the indexT and assigns the value found in the indexT 
    positions of x[]. This allows us to circumnavigate the issue of accessing data from outside the array when having to rotate at the 
    end of the alphabet back to the start.*/
    for (indexT = 0; indexT < tempShift; indexT++) {
        y[26 - tempShift + indexT] = x[indexT];
    }
    
    /*This prints both arrays side by side to compare the non-encrypted (Left) and encrypted (Right)*/
    for (index = 0; index < 26; index++) {
        printf("%d      %d\n", x[index], y[index]);
    }
}

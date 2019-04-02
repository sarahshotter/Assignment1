#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>


/*Prototype sets up the function encrypt, which utilises two arrays and an integer shift, 
to transform a second array from the first using a shift factor   f*/
char encrypt(char *x, char *y, char shift);

char decrypt(char *x, char *y, char shiftBack);

int main() {
    char alpha[26], alphaCopy[26]; //Declaration of 2 arrays of length 26
    char k = 5, g = -5;
    int i; 
    
    for (i = 0; i < 26; i++) { //array with 26 elements
        alpha[i] = i + 65; //elements range from 65 to 90
        alphaCopy[i] = i + 65; //second array with elements ranging from 65 to 90
        /* there are two arrays with the same elements to allow us to edit one from the 
        other without changing the elements of the first one without the need for temporary variables*/
    }
    
    /*passing the elements of both the alpha and alphaCopy array to the encrypt function*/
    encrypt(alpha, alphaCopy, k);
    printf("%s\n", alphaCopy);
    
    decrypt(alpha, alphaCopy, g);
    printf("%s\n", alphaCopy);
    
    return 0;
}

/*Definition of the encrypt function occurs after the int main() code block*/

char encrypt(char *x, char *y, char shift) {
    printf("Enter a shift value:    ");
    scanf("%c", &shift);
    
    int indexT, index; //indexT represents a temporary index, and index that of the elements in the arrays
    
    /*% takes the remainder of the division and abs is the absolute function accommodating for negative values for shift. 
    As the Caesar ciper is a ring structure,  a positive shift of greater than 26 would result in a negative shift of the corresponding 
    number past 26, that is if the shift was 29, this would be equivalent to a shift of -3. This also applies in reverse for negative 
    shift being related to their positive counterparts*/
    char tempShift = abs((26 + shift)%26);   
    
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
    return 0;
}

char decrypt(char *x, char *y, char shiftBack) {
	
	int ind, tempIndex; //the indices for the arrays and the temporary indices
	
	char tempShiftBack = abs((26 + shiftBack)%26);
	
	for (tempIndex = 0; tempIndex < tempShiftBack; tempIndex++) {
		x[tempIndex] = y[26 - tempShiftBack + tempIndex];
	}
	
	for (ind = 0; ind < 26 - tempShiftBack; ind++) {
		x[ind + tempShiftBack] = y[ind];
	}
	return 0;
}

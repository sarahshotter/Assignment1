#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>


/*Prototype sets up the function encrypt, which utilises two arrays and an integer shift, 
to transform a second array from the first using a shift factor   f*/
char encrypt(char *x, char shift);

char decrypt(char *x, char shiftBack);

int main() {
    
    char k = 12;
    
    char sentenceO[] = "CAT";
    
    encrypt(sentenceO, k);
    printf("%s", sentenceO);
    
//    char sentenceOriginal[] = {THE QUICK BROWN FOX JUMPS OVER THE LAZY DOG}
//    char sentenceEnc[] = sentenceOriginal[];
//    encrypt(sentenceOriginal, sentenceEnc, k);
//    printf("%s", sentenceEnc);
    
    return 0;
}

/*Definition of the encrypt function occurs after the int main() code block*/

char encrypt(char *x, char shift) {
    
    char alpha[26], alphaCopy[26];
    int i;
    
    for (i = 0; i < 26; i++) { //array with 26 elements
        alpha[i] = i + 65; //elements range from 65 to 90
        alphaCopy[i] = i + 65; //second array with elements ranging from 65 to 90
        /* there are two arrays with the same elements to allow us to edit one from the 
        other without changing the elements of the first one without the need for temporary variables*/
    }
    
    int indexT, index; //indexT represents a temporary index, and index that of the elements in the arrays
    
    /*% takes the remainder of the division and abs is the absolute function accommodating for negative values for shift. 
    As the Caesar ciper is a ring structure,  a positive shift of greater than 26 would result in a negative shift of the corresponding 
    number past 26, that is if the shift was 29, this would be equivalent to a shift of -3. This also applies in reverse for negative 
    shift being related to their positive counterparts*/
    char tempShift = abs((26 + shift)%26);   
    
    /*the for loop takes values of x[] i + some shift's value and assigns it to the array y[]'s ith element and then repeats this 
    process for all required values of index to suffice the conditions of the for loop thus encrypting the y[] array*/
    for (index = 0; index < 26 - tempShift; index++) {  
        alphaCopy[index] = alpha[index + tempShift];
    }
    
    /*The for loop takes the values shift factor distance from the end of y[] + the indexT and assigns the value found in the indexT 
    positions of x[]. This allows us to circumnavigate the issue of accessing data from outside the array when having to rotate at the 
    end of the alphabet back to the start.*/
    for (indexT = 0; indexT < tempShift; indexT++) {
        alphaCopy[26 - tempShift + indexT] = alpha[indexT];
    }
    int N = sizeof(x), count = 0;
    
    for (count; count < N; count++) {
        if (count < 26 - tempShift) {
            count = count + tempShift;
        } else {
            count =+ 26 - tempShift;
        }
        x[count] = alphaCopy[count];
    }
    return 0;
    
}

char decrypt(char *x, char shiftBack) {
	
	char alpha[26], alphaCopy[26];
	int i;
	
	for (i = 0; i < 26; i++) { //array with 26 elements
        alpha[i] = i + 65; //elements range from 65 to 90
        alphaCopy[i] = i + 65; //second array with elements ranging from 65 to 90
        /* there are two arrays with the same elements to allow us to edit one from the 
        other without changing the elements of the first one without the need for temporary variables*/
    }
	
	int ind, tempIndex; //the indices for the arrays and the temporary indices
	
	char tempShiftBack = abs((26 + shiftBack)%26);
	for (ind = 0; ind < 26 - tempShiftBack; ind++) {
		alpha[ind + tempShiftBack] = alphaCopy[ind];
	}
	for (tempIndex = 0; tempIndex < tempShiftBack; tempIndex++) {
		alpha[tempIndex] = alphaCopy[26 - tempShiftBack + tempIndex];
	}
	return 0;
}

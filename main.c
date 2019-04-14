#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>


/*Prototype sets up the function encrypt, which utilises two arrays and an integer shift, 
transform a second array from the first using a shift factor*/

void encrypt(char *x, char *y, char shift);

void translate(char *message, int messageLength, char *key);

void decrypt(char *mixed, char *unmixed, int shiftFactor);

// void decode(char *scramble, int scrambleLength, char *code);

int main() {
    char alpha[26]; 
    char alphaCopy[26];
    int i;
    int m;
    
    for (i = 0; i < 26; i++) { //array with 26 elements
        alpha[i] = i + 65; //elements range from 65 to 90
        alphaCopy[i] = i + 65; //second array with elements ranging from 65 to 90
        /* there are two arrays with the same elements to allow us to edit one from the 
        other without changing the elements of the first one without the need for temporary variables*/
    }
    
    char k = 10;
    
    char sentenceO[] = "THE QUICK BROWN FOX JUMPS OVER THE LAZY DOG";
    char sentenceM[] = "DRO AESMU LBYGX PYH TEWZC YFOB DRO VKJI NYQ";
    
    encrypt(alpha, alphaCopy, k);
    printf("%s\n", alphaCopy);
    
    /*alphaCopy is now the encrypted alphabet. To ensure that the encryption key isn't lost, a second
    copy of alphaCopy is made, called the encryptKey*/
    
    char encryptKey[26];
    for (m = 0; m < 26; m++) {
        encryptKey[m] = alphaCopy[m];
    }
    printf("%s\n", encryptKey);
    
    translate(sentenceO, sizeof(sentenceO), alphaCopy);
    printf("%s\n", sentenceO);
    
    // decrypt(alphaCopy, alpha, k);
    // printf("%s\n", alpha);
    // printf("%s\n", alphaCopy);
    
    
    return 0;
}

/*Definition of the encrypt function occurs after the int main() code block*/

void encrypt(char *x, char *y, char shift) {
    
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
    
}


void decrypt(char *mixed, char *unmixed, int sFact) {
	char i, n, j;
		


void translate(char *message, int messageLength, char *key) {
    int i;
    for (i = 0; i < messageLength; i++) {
        if(message[i] != ' ') {
           message[i] = key[message[i] - 65];
        }
    }
}

// void decode(char *scramble, int scrambleLength, char *code) {
//     int l; 
//     for (l = 0; l < scrambleLength; l++) {
//         if (scramble[l] != ' ') {
//             scramble[l - 65] = code[l];
//         }
//     }
// }

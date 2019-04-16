#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

void shift(char *info); //this is the prototype of the encryption function

int main() {
    char message[1000]; //this sets the maximum number of characters in the message to be 1000 so as not to overload the computer
    
    FILE *input; //declares a variable of type "file"
    input = fopen("/Users/Sarebear/Desktop/Cipher/Message.txt", "r"); //reads the file from this location
    fgets(message, 1000, input); //takes the file up to 1000 characters and stores it in the array message which was declared earlier
    
    shift(message); //calls shift function to encrypt message
    printf("The altered message is: %s\n", message); //prints out the encrypted message
}

void shift(char *info) { //function shift takes an array and adds a shift factor to each of the individual elements
    int n, shiftFactor;
    printf("Enter a value to shift the message by:  \n");
    scanf("%d", &shiftFactor);
    if (shiftFactor < 0) { //if the shift factor is negative, the equivalent rotation can be achieved by taking the remainder of 26 + that shift factor
        shiftFactor = (shiftFactor + 26)%26;
        printf("To allow for the cyclic nature of the cipher, shift has been altered to:  %d\n", shiftFactor);
    }
    
    for (n = 0; info[n] != '\0'; n++){ //as long as the element is not a space or an empty element at the end of the array the function will add the shift factor onto the element's value even if it exceeds the value of Z (i.e. 90 in ASCII)
        if (info[n] != ' ') {
            info[n] = info[n] + shiftFactor;
        }
    }
    for (n = 0; info[n] != '\0'; n++) { //the function will then process each of the elements and those that are over the value of 'Z' (i.e. > 90) will have 26 subtracted from them to return them to the start of the alphabet and begin the cycle again thus retaining the cycling nature of a rotational cipher
        if (info[n] > 'Z') {
            info[n] = info[n] - 26;
        }
    }
}


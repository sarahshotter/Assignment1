#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

void shift(char *info); //this is the prototype of the encryption function

void reset(char *codedInfo);

int main() {
    char message[1000];
    FILE *fp;
    FILE *input;
    
    int choice;
    printf("Choose which function to perform:   \n"); //prints the options to the screen
    printf("1: Rotation Encryption\n");
    printf("2: Rotation Decryption\n");
    printf("3: Substitution Encryption\n");
    printf("4: Substitution Decryption\n");
    scanf("%d", &choice); //saves the choice of the user to the variable then continues to switch case to carry out the function
    
    switch (choice) { //case 1 carries out the shift function
        case 1: fp = fopen("/Users/Sarebear/Desktop/Cipher/Message.txt", "r"); //reads the file from this location
            fgets(message, 1000, fp); //takes the file up to 1000 characters and stores it in the array message which was declared earlier
            printf("The original message is:    %s\n", message);
            shift(message);
            printf("The altered message is: %s\n", message); //prints out the encrypted message
            break; //case 2 carries out the reset function
        case 2: input = fopen("/Users/Sarebear/Desktop/Cipher/shiftFour.txt", "r");
            fgets(message, 1000, input);
            printf("The original message is:    %s\n", message);
            reset(message);
            printf("The reset message is:   %s\n", message);
            break;
        case 3://calls on substitution encryption function (unwritten)
            break;
        case 4://calls on substitution decryption function (unwritten)
            break;
        default: printf("Try again, but this time choose an option that is actually there\n");
            break;
    }
    
    char alpha[26];
    char beta[26];
    char subsMessage[1000];
    FILE *fin;
    fin = fopen("/Users/Sarebear/Desktop/Cipher/SubstitutionEncryption.txt", "r");
    fgets(subsMessage, 1000, fin);
    printf("Original message is:    %s\n", subsMessage);
    
    for (int i = 0; i < 26; i++) {
        alpha[i] = i + 65;
    }
    
    for (int n = 0; n < 26; n++) {
        beta[n] = alpha[25 - n];
    }
    
    printf("Standard alphabet:                   %s\n", alpha);
    printf("Alphabet with letter substitution:   %s\n", beta);
    int k;
    for (k = 0; k < sizeof(subsMessage); k++) {
        if (subsMessage[k] != ' '){
            subsMessage[k] = beta[subsMessage[k] - 65];
        }
    }
    printf("Substituted message is: %s\n", subsMessage);
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

void reset(char *codedInfo) {
    int n, resetFactor;
    
    printf("Enter a value to reset code:    \n");
    scanf("%d", &resetFactor);
    
    if (resetFactor < 0) {
        resetFactor = (resetFactor + 26)%26;
        printf("Cipher is cyclic so factor has been reset to:   %d\n", resetFactor);
    }
    
    for (n = 0; codedInfo[n] != '\0'; n++) {
        if (codedInfo[n] != ' ') {
            codedInfo[n] = codedInfo[n] - resetFactor; //essentially doing the opposite of when we encrypted the message
        }
    }
    
    for (n = 0; codedInfo[n] != '\0'; n++) {
        if ((codedInfo[n] < 'A') && (codedInfo[n] != ' ')) { //as <space> has a lower value in ASCII need to ensure that the <space> elements aren't also shifted just because they have a value less than 'A' (i.e. < 65)
            codedInfo[n] = codedInfo[n] + 26; //increasing by 26 will return all values back into the alphabet
        }
    }
}

/* SUBSTITUTION
 create an array that contains 26 letters of the alphabet
 we want to make a second array that randomly calls upon the elements of the first array and distributes them into the second
 ok
 so
 
 let alphabet be an array with 26 elements from i = 0, to i = 25
 each element i, is equal to its element number + 65
 this makes it equal to its ASCII value
 
 This will give us an array alpha[26];
 
 let there be a second array beta[26] with elements ranging from n = 0, through to n = 25
 s.t. beta[n] = alpha[rand() % (25 - n)]
 
 char alpha[26];
 char beta[26];
 for (i = 0; i < 26; i++) {
 alpha[i] = i + 65;
 }
 
 created a new alphabet from the old one
 essentially a lookup table that the message will be drafted from
 
 if the message and message length is hardcoded into the programme it mostly works
 if the sizeof(subsMessage) is the max distance of k then it works brilliantly
 
 */

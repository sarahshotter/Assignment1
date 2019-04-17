#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

void shift(char *info); //this is the prototype of the encryption function

void reset(char *codedInfo);

void subs(char *content);

void subsDec(char *codedContent);

int main() {
    char message[1000];//a maximum message length of 1000 characters was set to ensure that the memory of the processor was not compromised by running the programme
    
    //the corresponding declarations for files for each of the functions lies below with the format being "f<function_number>"
    FILE *fone;
    FILE *ftwo;
    FILE *fthree;
    FILE *ffour;
    
    int choice;
    printf("Choose which function to perform:   \n"); //prints the options to the screen
    printf("1: Rotation Encryption\n");
    printf("2: Rotation Decryption\n");
    printf("3: Substitution Encryption\n");
    printf("4: Substitution Decryption\n");
    scanf("%d", &choice); //saves the choice of the user to the variable then continues to switch case to carry out the function
    
    switch (choice) {
            
            /*Case 1: carries out the shift function. It is a rotational cipher encryption. It reads from a file and allows the user to input the key, then printing the rotated message to the console*/
            
        case 1: fone = fopen("/Users/Sarebear/Desktop/Cipher/Message.txt", "r"); //reads the file from this location
            fgets(message, 1000, fone); //takes the file up to 1000 characters and stores it in the array message which was declared earlier
            printf("The original message is:    %s\n", message);
            shift(message);
            printf("The altered message is:     %s\n", message); //prints out the encrypted message
            break; //case 2 carries out the reset function
            
            /*Case 2: carries out the reset function. It is a rotational cipher decryption. It reads from a file and allows the user to input a key to decrypt by. At this point it can only decrypt by brute force attack. It prints the unencrypted message to the console*/
            
        case 2: ftwo = fopen("/Users/Sarebear/Desktop/Cipher/RotationDecrypt.txt", "r");
            fgets(message, 1000, ftwo);
            printf("The original message is:    %s\n", message);
            reset(message);
            printf("The reset message is:       %s\n", message);
            break;
            
            /*Case 3: carries out the subs function. It is a substitutional cipher encryption. It reads from a file based on the computers main frame. Prints the alphabet in order and then prints a substituted alphabet which is used as a lookup table. Prints the substituted message*/
            
        case 3: fthree = fopen("/Users/Sarebear/Desktop/Cipher/SubstitutionEncryption.txt", "r");
            fgets(message, 1000, fthree);
            printf("Original message is:    %s\n", message);
            subs(message);
            printf("Substituted message is: %s\n", message);
            break;
            
            /*Case 4: carries out subsDec function. It is a substitutional cipher decryption. */
            
        case 4: ffour = fopen("/Users/Sarebear/Desktop/Cipher/SubstitutionDecryption.txt", "r");
            fgets(message, 1000, ffour);
            printf("Original encrypted message is:  %s\n", message);
            //                    subsDec(message);
            printf("Decrypted message is:           %s\n", message);
            break;
            
        default: printf("Try again, but this time choose an option that is actually there\n"); //the user has input something other than 1, 2, 3, or 4 as they have either misunderstood the instructions or something has gone wrong. This allows them to try again.
            break;
    }
    
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
        
        if ((info[n] >= 65) && (info[n] <= 90)) { //the ASCII values of A and Z respectively
            info[n] = info[n] + shiftFactor;
            if (info[n] > 90) {         //the function will then process each of the elements and those that are over the value of 'Z' (i.e.                         > 90) will have 26 subtracted from them to return them to the start of the alphabet and begin the                            cycle again thus retaining the cycling nature of a rotational cipher
                info[n] = info[n] - 26;
            }
            
        } else if ((info[n] >= 97) && (info[n] <= 122)) { //these are the parameters for the lowercase alphabet
            info[n] = info[n] - 32 + shiftFactor; //this will shift the lower case values into the upper case ascii values
            if (info[n] > 90) {
                info[n] = info[n] - 26; //returns values of letters back A and starts reading through the alphabet again.
            }
            
        } else {
            info[n] = info[n]; //to accommodate for punctuation, it is dealt with separately and its ascii values lie outside of the aparmeters specified above. We don't want to shift it as it would make the message more difficult to read.
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
        
        if ((codedInfo[n] >= 65) && (codedInfo[n] <= 90)) { //values between 65 and 90 give the capitalised letters of the alphabet
            codedInfo[n] = codedInfo[n] - resetFactor; //essentially doing the opposite of when we encrypted the message
            if (codedInfo[n] < 'A') {
                codedInfo[n] = codedInfo[n] + 26;
            }
            
        } else if ((codedInfo[n] >= 97) && (codedInfo[n] <= 122)) { //these parameters for the lowercase alphabet set up the elseif statement to change all lowercase letters to their corresponding uppercase letters and then decrypt them
            codedInfo[n] = codedInfo[n] - 32 - resetFactor; //subtracting 32 will change their ASCII value to, e.g. a - 32 = A
            if (codedInfo[n] < 'A') {
                codedInfo[n] = codedInfo[n] + 26; //this will return it back into the domain of A to Z as the rotation cipher is cyclic
            }
            
        } else {
            codedInfo[n] = codedInfo[n]; //this accommodates for any other symbols used in the message, i.e. any punctuation, so that it will remain a constant through out and not be shifted with the other letters
        }
    }
    
}

void subs(char *content) {
    char alpha[26] = {0};
    char beta[26] = {0};
    int i, n, k;
    
    for (i = 0; i <= 25; i++) {
        alpha[i] = i + 65;
    }
    
    for (n = 0; n < 26; n++) {
        beta[n] = alpha[25 - n];
    }
    
    printf("Standard alphabet:      %s\n", alpha);
    printf("Substituted alphabet:   %s\n", beta);
    
    float contentLength; //need to find the message length to be able to perform a for loop later on
    contentLength = strlen(content); //function computes the length of the string but outputs a float
    printf("Length is:  %d\n", (int)contentLength);
    
    for (k = 0; k < contentLength; k++) {
        if (content[k] != ' '){
            content[k] = beta[content[k] - 65]; //value = the value - 65 to return it to its element value  then we want to find that element in the beta array. this is now the new value of the message array in that element.
        }
    }
}

//void subsDec(char *codedContent) {
//
//}

/* TODO
 rotation decryption
 sort through and pick out the most common letters in the message -  they are most likely t/e
 most common three letter word is the/and
 
 
 substitution decryption - unknown key
 
 int count = 0;
 char symbols[128] = {0};
 for (count = 0; message[count] != '\0'; count++) {
 ++symbols[message[count]];
 }
 
 int max, ind;
 max = symbols[0];
 ind = 0;
 for (count = 0; message[count] != '\0'; count++) {
 if ((message[count] >= 65) && (message[count] <= 90)) {
 if (symbols[count] > 0) {
 max = symbols[count];
 ind = count;
 }
 } else {
 break;
 }
 }
 printf("The most common letter is:  %c\n", message[ind]);
 
 download a dictionary - I have .txt file of a dictionary with 1000 words in it
 most common three letter words are the/and
 most common letters in English are t, e, a
 single letter words must be I or a
 
 idea to split into words:
 //    char words[1000];
 //    const char sp[] = " ";
 //    char *token;
 //
 //    token = strtok(message, sp); //this will give us the first token
 //    int q = 0;
 //    do {
 //        words[q] = *token;
 //        q = q + 1;
 //        token = strtok(NULL, sp);
 //    } while (token != '\0');
 //
 //    for(q = 0; q < 1000; q++) {
 //        printf("Array of words: %c\n", words[q]);
 //    }
 
 //    int n;
 //    for (n = 0; n != '\0'; n++) {
 //
 //        printf("%s\n", strtok(message, sp));
 //    }
 
 
 */

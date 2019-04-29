#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

void rotationEncryption(char *info, int shiftFactor); //this is the prototype of the encryption function

void rotationDecryption(char *codedInfo, char *decoded, int resetFactor);

void substitutionEncryption(char *content);

void substitutionDecryption(char *codedContent);

void substitutionDecryptNoKey(char *codedText);

int main() {
    char message[1000]; //a maximum message length of 1000 characters was set to ensure that the memory of the processor was not compromised by running the programme
    char key[3]; //string read from file cipherkey
    int keyValue; //integer obtained from string key[]
    char text[1000];//text is the output from the function. it is not called output as their is already a file called output
 

    FILE *input;//file where input is read from before the user decides what to do with the information
    FILE *cipherkey;//file where key is read from
    FILE *output;//file where output is printed to
    FILE *dictionary;//contains the most common words in the English language

    input = fopen("/Users/Sarebear/Desktop/Cipher/input.txt", "r"); //reads the file from this location
    fgets(message, 1000, input); //takes the file up to 1000 characters and stores it in the array message which was declared earlier
    
    printf("The input message is:   %s\n", message);

    int choice;
    do {
        printf("Choose which function to perform on the message:   \n"); //prints the options to the screen
        printf("1:  Rotation Encryption\n");
        printf("2:  Rotation Decryption\n");
        printf("3:  Substitution Encryption\n");
        printf("4:  Substitution Decryption with Key\n");
        printf("5:  Substitution Decryption without Key\n");
        printf("6:  Rotation Decryption without Key\n");
        scanf("%d", &choice); //saves the choice of the user to the variable then continues to switch case to carry out the function

        switch (choice) {

                /*Case 1: carries out the shift function. It is a rotational cipher encryption. It reads from a file and allows the user to input the key, then printing the rotated message to the console*/

            case 1: printf("The original message is:    %s\n", message);
                cipherkey = fopen("/Users/Sarebear/Desktop/Cipher/key.txt", "r");
                fgets(key, 3, cipherkey);
                keyValue = atoi(key);
                printf("The key is: %d\n", keyValue);
                rotationEncryption(message, keyValue);
                printf("The altered message is:     %s\n", message); //prints out the encrypted message
                output = fopen("/Users/Sarebear/Desktop/Cipher/output.txt", "w");
                fputs(message, output);
                break;

                /*Case 2: carries out the rotation Decryption function. It is a rotational cipher decryption. It reads from a file and allows the user to input a key to decrypt by. At this point it can only decrypt by brute force attack. It prints the unencrypted message to the console*/

            case 2: printf("The original message is:    %s\n", message);
                cipherkey = fopen("/Users/Sarebear/Desktop/Cipher/key.txt", "r");
                fgets(key, 3, cipherkey);
                keyValue = atoi(key);
                printf("The key from file is:   %d\n", keyValue);
                rotationDecryption(message, text, keyValue);
                printf("The reset message is:       %s\n", text);
                output = fopen("/Users/Sarebear/Desktop/Cipher/output.txt", "w");
                fputs(text, output);
                break;

                /*Case 3: carries out the subs function. It is a substitutional cipher encryption. It reads from a file based on the computers main frame. Prints the alphabet in order and then prints a substituted alphabet which is used as a lookup table. Prints the substituted message*/

            case 3: printf("Original message is:    %s\n", message);
                substitutionEncryption(message);
                printf("Substituted message is: %s\n", message);
                output = fopen("/Users/Sarebear/Desktop/Cipher/output.txt", "w");
                fputs(message, output);
                break;

                /*Case 4: carries out subsDec function. It is a substitutional cipher decryption. */

            case 4: printf("Original encrypted message is:  %s\n", message);
                substitutionDecryption(message);
                printf("Decrypted message is:           %s\n", message);
                output = fopen("/Users/Sarebear/Desktop/Cipher/output.txt", "w");
                fputs(message, output);
                break;

                /*Case 5: carries out <insert name> function. It's aim is to decode a message without being given the substitution key*/
            case 5: printf("Original encrypted message: %s\n", message);
                    substitutionDecryptNoKey(message);
                printf("Decrypted message is:       %s\n", message);
                output = fopen("/Users/Sarebear/Desktop/Cipher/output.txt", "w");
                fputs(message, output);
                break;

            case 6: //decryption by brute force
                printf("The original message is:    %s\n", message);
                for (keyValue = 0; keyValue < 27; keyValue++) {
                    rotationDecryption(message, text, keyValue);
                    printf("\nWhen the key is %d, message is: %s\n", keyValue, text);
                    }
                output = fopen("/Users/Sarebear/Desktop/Cipher/output.txt", "w");
                fputs(text, output);
                break;

            default: printf("Try again, but this time choose an option that is actually there\n"); //the user has input something other than 1, 2, 3, or 4 as they have either misunderstood the instructions or something has gone wrong. This allows them to try again.
                break;
        }
    } while (choice > 6);

    

}


void rotationEncryption(char *info, int shiftFactor) { //function shift takes an array and adds a shift factor to each of the individual elements
    int n;
    
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

void rotationDecryption(char *codedInfo,char *decoded, int resetFactor) {
    int n;
    
    if (resetFactor < 0) {
        resetFactor = (resetFactor + 26)%26;
        printf("Cipher is cyclic so factor has been reset to:   %d\n", resetFactor);
    }
    
    for (n = 0; codedInfo[n] != '\0'; n++) {
        
        if ((codedInfo[n] >= 65) && (codedInfo[n] <= 90)) { //values between 65 and 90 give the capitalised letters of the alphabet
           decoded[n] = codedInfo[n] - resetFactor; //essentially doing the opposite of when we encrypted the message
            if (decoded[n] < 'A') {
                decoded[n] = decoded[n] + 26;
            }
        
        } else if ((codedInfo[n] >= 97) && (codedInfo[n] <= 122)) { //these parameters for the lowercase alphabet set up the elseif statement to change all lowercase letters to their corresponding uppercase letters and then decrypt them
            decoded[n] = codedInfo[n] - 32 - resetFactor; //subtracting 32 will change their ASCII value to, e.g. a - 32 = A
            if (decoded[n] < 'A') {
                decoded[n] = decoded[n] + 26; //this will return it back into the domain of A to Z as the rotation cipher is cyclic
            }
        
        } else {
            decoded[n] = codedInfo[n]; //this accommodates for any other symbols used in the message, i.e. any punctuation, so that it will remain a constant through out and not be shifted with the other letters
        }
    }
    
}

void substitutionEncryption(char *content) {
    char alpha[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char beta[1000];
    int i;
    
    FILE *fSubEncKey;
    fSubEncKey = fopen("/Users/Sarebear/Desktop/Cipher/SubstitutionEncryptionKey.txt", "r");
    fgets(beta, 1000, fSubEncKey);
    
    printf("Standard alphabet:      %s\n", alpha);
    printf("Substituted alphabet:   %s\n", beta);
    
    float contentLength; //need to find the message length to be able to perform a for loop later on
    contentLength = strlen(content); //function computes the length of the string but outputs a float
    
    for (i = 0; i < contentLength; i++) {
        if (content[i] != ' ') {
            content[i] = beta[content[i] - 65]; //value = the value - 65 to return it to its element value  then we want to find that element in the beta array. this is now the new value of the message array in that element.
        }
    }
}

void substitutionDecryption(char *codedContent) {
    
    int i;
    char alpha[27] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    
    char beta[27];
    FILE *fSubDecKey;
    fSubDecKey = fopen("/Users/Sarebear/Desktop/Cipher/SubstitutionDecryptionKey.txt", "r");
    fgets(beta, 27, fSubDecKey);
    printf("The decryption key is:  %s\n", beta);
    printf("The alphabet is:        %s\n", alpha);
    
    float codedLength;
    codedLength = strlen(codedContent);
    
    /*when the message's character matches the key's character change the character in the message to the corresponding character in alphabet. This is essentially a look up table. It is a meticulous and slow way to work through code but when we have the key already it is a sure fire way to go about the problem*/
    int k;
    for (i = 0; i < codedLength; i++) {
        if (codedContent[i] != ' ') {
            for (k = 0; k < 26; k++) {
                if (codedContent[i] == beta[k]) {
                    codedContent[i] = alpha[k];
                    break;
                }
            }
        }
    }
    
    
    
    
}

void substitutionDecryptNoKey(char *passedMessage) {
    char englishLetters[26] = "ETAOINSRHLDCUMFPGWYBVKXJQZ"; //the most common letters in the English language in descending order
    char messageLetters[26]; //the most common letters in the message in descending order
    
    printf("Passed message is:  %s\n", passedMessage);
    int i, j, max;
    char maxLetter;
    float messageLength = strlen(passedMessage);
    printf("message length is:  %f\n", messageLength);

    char frequency[26] = {0}; //Frequency histogram for the letters in the message. Needs to initialise at 0 to start count correctly

    int temp;
    for (i = 0; i < messageLength; i++) {
        if ((passedMessage[i] >= 65) && (passedMessage[i] <= 90)) { //when the the message characters are within the constraints of uppercase letters so that the punctuation and other symbols e.g. ' ' don't get counted
            temp = passedMessage[i] - 65;
            frequency[temp] = frequency[temp] + 1;
        }
    }

    for (i = 0; i < 26; i++) {
        printf("Frequency of letter %c is %d\n", i + 'A', frequency[i]); //(i + 'A') is the same as i + 65 and is setting the char value to the ASCII value for each element of the for loop
    }

    for (i = 0; i < 26; i++) {
        max = 0;
        maxLetter = ' ';
        for (j = 0; j < 26; j++) {
            if (frequency[j] > max) {
                max = frequency[j]; //this sets the max value to the value that is at the first j value in the frequency histogram. then sorts through the rest of the data
                maxLetter = j + 65; //returns it to its ascii value
            }
        }
        messageLetters[i] = maxLetter;
        frequency[maxLetter - 65] = 0; //this replaces the value of the max valued element with zero. Otherwise the loop would continuously return only the one element as the max value
    }
    printf("Letters in decreasing frequency are:     %s\n", messageLetters); //Note: the letters that don't appear in the coded message won't appear in the array letters[]
    printf("Most frequently used letters in English: %s\n", englishLetters);

    int k;
    for (i = 0; i < messageLength; i++) {
        if (passedMessage[i] != ' ') {
            for (k = 0; k < 26; k++) {
                if (passedMessage[i] == messageLetters[k]) {
                    passedMessage[i] = englishLetters[k];
                    break;
                }
            }
        }
    }
    printf("\nThe new message reads:  %s\n", passedMessage);
    
    int wordCount = 0; //counts how many words in the message throughout the while loop
    char *array[1000]; //the array my tokens (words) are being saved to
    int x = 0;
    char *word; //my token is called word
    word = strtok(passedMessage, " ,.?-…"); //splits the string into words whenever one of the symbols in "" occurs
    while (word != NULL) { //whenever the word is not null
        array[x++] = word;
        word = strtok(NULL, " ,.?-…");
        wordCount++;
    }
    
    printf("There are %d words in the message\n", wordCount);
    
    for(x = 0; x < wordCount; x++) {
        printf("Word %d is:  %s\n", x, array[x]);
    }
    

}


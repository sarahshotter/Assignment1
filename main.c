#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <strings.h>

int main() {
    int n; //can call on n as many times as you want inside for loops
    int shift; //this is the value that is going to shift the alphabet by. It has not been initialised as the user is to enter the value
    char message[1000]; //this sets the maximum number of characters in the message to be 1000 so as not to overload the computer
    
    
    printf("Enter a value to shift alphabet by:    \n"); //prints to console
    scanf("%d", &shift); //this reads what is input by the user and assigns it to the variable shift
    
    FILE *input; //declares a variable of type "file"
    input = fopen("/Users/Sarebear/Desktop/Cipher/Message.txt", "r"); //reads the file from this location
    fgets(message, 1000, input); //takes the file up to 1000 characters and stores it in the array message which was declared earlier
    
    for (n = 0; message[n] != '\0'; n++) { //for each value between 0 and until there are no more characters in message, n will increment
        if (message[n] != ' ') { //whilever the character in the position of n is not a <space>
            message[n] = message[n] + shift; //the character in position n of message is now equal to its value + shift
        }
    }
    /*The above for loop is stable and shifts each character of the message, but not the spaces. howvere, it does not recirculate at Z back to A*/
    for (n = 0; message[n] != '\0'; n++) {
        if (message[n] > 'Z') { //whenever the value is greater than 'Z' (i.e. ASCII > 90) the program should restart back at A
            message[n] = message[n] - 26; //to restart at A simply subtract 26 from value returned
        }
    }
    printf("The altered message is: %s\n", message);
}

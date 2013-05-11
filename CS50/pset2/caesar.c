#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main(int argc, string argv[])  {
    if (argc != 2) {
        printf("you need to input one number");
        return 1;
    }
    string input = argv[1];
    int rot_num = atoi(input);

    string user_string = GetString();
    
    for (int i = 0; i < strlen(user_string); i++) {
        int letter = user_string[i];
        if (letter >= 65 && letter <= 90) {
            int upcase_cipher = (((letter - 65) + rot_num)%26) + 65;
            printf("%c", upcase_cipher); 
        }
        
        else if (letter >=97 && letter <= 122) {
            int lowcase_cipher = (((letter - 97) + rot_num)%26) + 97;
            printf("%c", lowcase_cipher);
        }
        
        else 
            printf("%c", letter);
     }
    printf("\n");
}

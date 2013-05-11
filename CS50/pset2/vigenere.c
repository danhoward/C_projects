#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

int main(int argc, string argv[])  {
if (argc != 2) {
        printf("you need to input one word, plz\n");
        return 1;
    }
  string check_input = argv[1];
for (int k = 0; check_input[k]; k++)     {
    if (!(isalpha(check_input[k]))) {
        printf("you need to enter a keyWORD\n");
        return 1; 
    }
       
 }
        
  string input = argv[1];
  for (int a = 0; input[a]; a++)
        input[a] = tolower(input[a]);
    
    
  int key_leng = strlen(input);
    
  string user_string = GetString();
  int j = 0;
    
  for (int i = 0; i < strlen(user_string); i++) {
      int letter = user_string[i];
      int key_index = (j)% key_leng;
      int crypt = input[key_index];
      
       if (letter >= 65 && letter <= 90) {
           int upcase_cipher = (((letter - 65) + (crypt - 97))%26) + 65;
           j++;
           printf("%c", upcase_cipher); 
       }
        
       else if (letter >=97 && letter <= 122) {
           int lowcase_cipher = (((letter - 97) + (crypt - 97))%26) + 97;
           j++;
           printf("%c", lowcase_cipher);
       }
        
       else 
           printf("%c", letter);
     }
    printf("\n"); 
    return 0;
}

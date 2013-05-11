#include <cs50.h>
#include <stdio.h>

int main(void) {
    int height;
    while(height < 0 || height > 23) {
        printf("Give me a number for the pyramid height (no more than 23): ");
        height = GetInt();
    }
    int input = height;
   for(int j = 1; j <= height; j++)  {
     for(int i = input; i > 1; i--)    {
       printf(" ");
            
        }
      int k = 0;
      while(k < j+1) {
        printf("#");
        k++;
        }
    printf("\n");    
    input--;
   }
}

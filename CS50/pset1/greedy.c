#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void) {
   float change = 0;
   //float cents_change;
   while(change <= 0) {
      printf("How much change should I return? ");
      change = GetFloat();
     } 
   //printf("%f\n", change);
   int change_given = (roundf(100* change));
   //printf("%f\n", cents_change);
   //int change_given = (int)cents_change;
   //printf("%d\n", change_given);
   int k = 0;
   while(change_given > 0)  {
   
    if (change_given >= 25)
        change_given = change_given - 25;
    else if (change_given >= 10 && change_given < 25)
        change_given = change_given - 10;
    else if (change_given >= 5 && change_given < 10)
        change_given = change_given - 5;
    else if (change_given < 5)
        change_given = change_given -1;
    k++;
    //printf("%d\n", change_given);
   } 
   printf("%d\n",k);
}

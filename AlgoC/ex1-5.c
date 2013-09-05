/* 
*
* Exercise to display binary representation of an input integer (non-neg)
*
*/


#include <stdio.h>
#include <cs50.h>


int main(void) {
	int input;

	do {
		printf("Enter a non-negative number please: ");
		input = GetInt();
	}

	while (input < 0);

	for (int i = sizeof(int) * 8 - 1; i >= 0; i--) {
		int mask = 1 << i;
		if (input & mask) {
			printf("1");
		}
		else {
			printf("0");
		}
	}
printf("\n");
return 0;
}
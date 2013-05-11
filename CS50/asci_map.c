#include <stdio.h>

int main(void) {
	printf("Uppercases\n");
	for (int i = 65; i < 65 + 26; i++)
		printf("%c : %d\n", (char) i, i);
		
	printf("\n");
	printf("Lowercases\n");
	for (int i = 97; i < 97 + 26; i++)
		printf("%c : %d\n", (char) i, i);
	
	return 0;
}
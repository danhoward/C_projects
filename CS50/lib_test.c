#include <cs50.h>
#include <stdio.h>

int GetInt(void);

int main(void) {
	printf("gimme a number\n");
	int x = GetInt();
	printf("%d\n", x);
}

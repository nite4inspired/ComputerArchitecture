#include <stdio.h>

int main(void)
{
	printf("Enter an amount: ");
	float a;
	scanf("%f", &a);
	printf("Wtih tax added: %.2f", 1.05 * a);
	return 0;
}

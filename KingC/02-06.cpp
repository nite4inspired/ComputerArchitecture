#include <stdio.h>

int main(void)
{
	printf("Enter a value for x: ");
	float a;
	scanf("%f", &a);
	printf("3x^5 + 2x^4 - 3x^2 + 5x - 1 = %.2f\n", (((3*a + 2)*a*a-3)*a+5)-1 );
	return 0;
}

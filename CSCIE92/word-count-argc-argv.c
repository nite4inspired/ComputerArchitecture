#include <stdio.h>

int main(int argc, char *argv[]) {
	for (int i = 0; i <= argc+1; i++) {
		printf("Argument %d: %s\n", i, argv[i]);
	}
	return 0;
}

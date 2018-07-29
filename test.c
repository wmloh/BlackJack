#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

struct Test {
	char *x;
};

int main () {
	int x = 3;
	goto B;
	
	struct Test test = {NULL};
	A: 
		x = 2;
	
	B:
		printf("%i\n", x);
}
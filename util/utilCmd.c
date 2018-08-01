#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

char *getInput(void) {
	char c;
	if(!scanf(" %c", &c)) return NULL;
	int maxLen = 1;
	int len = 1;
	char *str = malloc(maxLen * sizeof(char));
	str[0] = c;
	while(true) {
		if(!scanf("%c", &c) || c == '\n') break;
		if(len == maxLen) {
			maxLen *= 2;
			str = realloc(str, maxLen * sizeof(char));
		}
		len++;
		str[len - 1] = c;
	}
	str = realloc(str, (len + 1) * sizeof(char));
	str[len] = '\0';
	return str;
}
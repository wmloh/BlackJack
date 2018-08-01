#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

struct dArray {
	void **arr;
	int len;
	int maxLen;
};

struct dArray *initdArray(void) {
	struct dArray *arr = malloc(sizeof(struct dArray));
	arr->arr = malloc(sizeof(void *));
	arr->len = 0;
	arr->maxLen = 1;
	return arr;
}

void appendObj(struct dArray *arr, void *obj) {
	if(arr->len == arr->maxLen) {
		arr->maxLen *= 2;
		arr->arr = realloc(arr->arr, sizeof(void *) * arr->maxLen);
	}
	(arr->arr)[arr->len] = obj;
	(arr->len)++;
}

void *removeObj(struct dArray *arr) {
	void *obj = (arr->arr)[arr->len-1];
	(arr->len)--;
	if(arr->len < arr->maxLen / 2) {
		arr->maxLen /= 2;
		arr->arr = realloc(arr->arr, sizeof(void *) * arr->maxLen);
	}
	return obj;
}

void *getObj(struct dArray *arr, int index) {
	return (arr->arr)[index];
}

int getLen(struct dArray *arr) {
	return arr->len;
}

void freeArray(struct dArray *arr) {
	assert(!(arr->len));
	free(arr->arr);
	free(arr);
}


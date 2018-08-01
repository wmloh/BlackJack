
struct dArray;

// initdArray() returns a pointer to the struct dArray
struct dArray *initdArray(void);

// appendObj(arr, obj) appends obj to the end of the array in arr
void appendObj(struct dArray *arr, void *obj);

// removeObj(arr) removes the object at the end of the array in arr
void *removeObj(struct dArray *arr);

// getObj(arr, index) returns the object at index in the array in arr
void *getObj(struct dArray *arr, int index);

// getLen(arr) returns the number of objects in arr
int getLen(struct dArray *arr);

// freeArray(arr) frees all allocated memory associated to arr
void freeArray(struct dArray *arr);
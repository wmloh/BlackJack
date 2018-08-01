
struct dArray;

struct dArray *initdArray(void);

void appendObj(struct dArray *arr, void *obj);

void *removeObj(struct dArray *arr);

void *getObj(struct dArray *arr, int index);

int getLen(struct dArray *arr);

void freeArray(struct dArray *arr);
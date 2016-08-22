

void displayArray(int* arr, int arrSize);

//Tree operations
void displayTree(int* arr, int arrSize);
int treeHight(int nodeCount);

//Heap operations
void sortHeap(int* arr, int arrSize);
void buildHeap(int* arr, int arrSize);
void siftUp(int*arr, int i, int arrSize);
void siftDown(int*arr, int i, int arrSize);
int getParentId(int child);
int getLChildId(int parent);
int getRChildId(int parent);
void swap(int* arr, int aId, int bId);

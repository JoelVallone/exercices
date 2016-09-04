
#define _TYPE double

void displayArray(_TYPE* arr, int arrSize);

//Tree operations
void displayTree(_TYPE* arr, int arrSize);
int treeHight(int nodeCount);

//Heap operations
void sortHeap(_TYPE* arr, int arrSize);
void buildHeap(_TYPE* arr, int arrSize);
void siftUp(_TYPE*arr, int arrId, int arrSize);
void siftDown(_TYPE*arr, int arrId, int arrSize);
int getParentId(int childId);
int getLChildId(int parentId);
int  getRChildId(int parentId);
void swap(_TYPE* arr, int  aId, int bId);

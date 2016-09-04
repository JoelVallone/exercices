#include <stdio.h>
#include <math.h>
#include "heap.h"


// gcc -o heap heap.c -lm && ./heap

int main(void){
  
  int arraySize = 9;
  _TYPE arr[] = {2, 29, 83, 14,5,65,7, 33,-1}; // last entry is a buffer with min value
  displayArray(arr,arraySize);
  buildHeap(arr,arraySize);
  sortHeap(arr,arraySize);
  displayArray(arr,arraySize);
}

void sortHeap(_TYPE* arr, int arrSize){
  //printf("---> SORT HEAP <---\n");
  int i = 0;
  for(i = 1; i < arrSize;i++){
    swap(arr,0,arrSize-i);
    siftDown(arr,0,arrSize-i);
  }
  //displayTree(arr,arrSize);
}

void buildHeap(_TYPE* arr, int arrSize){
  //printf("---> BUILD HEAP <---\n");
  //displayTree(arr,arrSize);
  int i = -1;
  for(i = arrSize-1; i >= 0; i--){
    siftDown(arr, i, arrSize);
  }
  //displayTree(arr,arrSize);
}

void displayArray(_TYPE* arr, int arrSize){
  int i = 0;
  for(i = 0; i < arrSize; i++){
    printf("%.2f,",arr[i]);
  }
  printf("\n");
}

void displayTree(_TYPE* arr, int arrSize){
  int treeHeight = treeHight(arrSize);
  int cellId = 0;
  int maxNodeCnt = 0;
  int rowId = 0;
  int colId = 0;
  for(rowId = 0; rowId <= treeHeight; rowId++){
    maxNodeCnt = (1 << rowId);
    printf("\n");
    for(colId = 0; colId < maxNodeCnt && cellId < arrSize; colId++){
      printf("%.2f, ",arr[cellId]);
      cellId++;
    }
  }
  //printf("\n---------------------------\n");
}


int treeHight(int nodeCount){
  return (int) (log(nodeCount)/log(2));
}

void siftDown(_TYPE*arr, int i, int arrSize){
  char swapped = 1;
  _TYPE buffer = -1;
  int parentId = i;
  int lChildId = -1;
  int rChildId = -1;
  int maxChildId = -1;


  while(swapped && parentId < arrSize){
    swapped  = 0;

    //find max child
    lChildId = getLChildId(parentId);
    rChildId = getRChildId(parentId);
    if(lChildId >= arrSize){
       break;
    }else if (lChildId == arrSize -1){
	maxChildId = lChildId;
    } else {
      if (arr[lChildId] > arr[rChildId]) {
	maxChildId = lChildId;
      } else {
	maxChildId = rChildId;
      }
    }    
    //printf("parent [%d]=%d,  lChild [%d]=%d, rChild [%d]=%d, maxChildIdx=%d",
    //	   parentId,arr[parentId],lChildId,arr[lChildId],rChildId,arr[rChildId],maxChildId);
    //swap with child if he is greater than parent
    if(arr[maxChildId] > arr[parentId]){
      swap(arr, parentId, maxChildId);
      swapped = 1;
      parentId = maxChildId;
    }    
    //printf("\n");
  }

}

void siftUp(_TYPE*arr, int i, int arrSize){
  if(i >= arrSize)return;

  char swapped = 1;
  _TYPE buffer = -1;
  int current = i;
  int parent = 0;

  while(swapped && current > 0){
    parent = getParentId(current);
    swapped = 0;
    //printf("curent [%d]=%d,  parent [%d]=%d",current, arr[current],parent, arr[parent]);
    if(arr[parent] < arr[current]){
      swap(arr, parent, current);
      swapped = 1;
      current = parent;
      displayTree(arr,arrSize);
    }
    //printf("\n");
  }
}

void swap(_TYPE* arr,int aId,int bId){
  //printf("\t=> swap [%d] and [%d]\n",aId,bId);
      _TYPE buffer = arr[aId];
      arr[aId] = arr[bId];
      arr[bId] = buffer;
}

int getParentId(int child){
 return (child - 1)/2;
}

int getLChildId(int parent){
 return 2*parent + 1;
}

int getRChildId(int parent){
  return 2*parent + 2;
}

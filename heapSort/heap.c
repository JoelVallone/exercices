
#include <stdio.h>
#include "heap.h"
#include <math.h>

int main(void){

  int[] arr = {4,5,7,1,33,90,37,21};
  buildHeap(arr,8);
    
}


void displayTree(int*arr, int arrSize){
  int h = treeHight(arrSize);
  for(int row = 1; row <= arrSize; row++){
    for(int col = 1; col <=; col ++){
    }
  }
}


void treeHight(int nodeCount){
  return (int) log2(nodeCount);
}


void siftUp(int*arr, int i, int arrSize){
  if(i >= arrSize)return;

  boolean swapped = true;
  int buffer = -1;
  int current = i;
  int parent = 0;

  while(swapped && current > 0){
    parent = parent(current);
    swapped = false;
    if(arr[parent] < arr[current]){
      buffer = arr[parent];
      arr[parent] = arr[current];
      arr[current] = buffer;      
    }
  }
}
int parent(int child){
  (child - 1)/2
}

int lChild(int parent){
  2*parent + 1;
}

int rChild(int parent){
  2*parent + 2;
}

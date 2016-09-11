#include <stdlib.h>
#include <math.h>
#include "tree.h"


TreeNode* __treeBuildLayer(TreeNode* existingMe, int targetDepth, int myDepth, int* arr , int arrSize, int myLevelId);


TreeNode* getNode(TreeNode* root, int nodeVal){

  TreeNode* candidate = root;
  if(candidate == NULL)return NULL;
  if(*(candidate->val) == nodeVal) return root;
  
  candidate = getNode(root->left, nodeVal);
  if(candidate != NULL) return candidate;
  
  candidate = getNode(root->right, nodeVal);
  if(candidate != NULL) return candidate;

  return NULL;
}

int nodeDepth(TreeNode* root, TreeNode* node){
  return(treeHeight(root)-treeHeight(node));
}

//initialize tree with level order traversal input array
TreeNode*  treeBuild(int* arr,int idx, int arrSize){
  int treeHeight = floor(log2(arrSize));
  int targetDepth = 0;
  TreeNode* root = NULL;
  for(targetDepth=0; targetDepth <= treeHeight; targetDepth++){
      if(targetDepth == 0){
	root = __treeBuildLayer(root, targetDepth, 0, arr, arrSize, 0);
      }else{
	__treeBuildLayer(root, targetDepth, 0, arr, arrSize, 0);
      }
  }
  return root;
}

TreeNode*  __treeBuildLayer(TreeNode* existingMe, int targetDepth, int myDepth, int* arr , int arrSize, int myLevelId){  
  if(targetDepth == myDepth){
    int levelOffset = (1 << myDepth) -1;
    int idx =  levelOffset + myLevelId;
    if (idx >= arrSize){
      return NULL;
    }

    TreeNode* newMe = NULL;
    if(arr[idx] != -1){
      newMe = malloc(sizeof(TreeNode));
      newMe->val = malloc(sizeof(int));
      *(newMe->val) = arr[idx];
      printf("%d, ", arr[idx]);
    }else{
      printf("NULL, ");
    }
    return newMe;
  }else if (targetDepth > myDepth){
    existingMe->left = __treeBuildLayer(existingMe->left, targetDepth, myDepth+1, arr,  arrSize, (myLevelId << 1));
    existingMe->right = __treeBuildLayer(existingMe->right, targetDepth, myDepth+1, arr, arrSize, (myLevelId << 1)+1);
    return existingMe;
  }else{
    printf("Should not happen");
    return existingMe;
  }
}




//initialize tree with heap style array
TreeNode*  treeBuildHeapStyleinput(int* arr, int idx, int arrSize){
  if (idx >= arrSize || arr[idx] < 0) return NULL;
  TreeNode* root = malloc(sizeof(TreeNode));
  root->val = malloc(sizeof(int));
  *(root->val) = arr[idx];
  root->left = treeBuild(arr,(idx << 1) + 1, arrSize);
  root->right = treeBuild(arr,(idx << 1) + 2, arrSize);
  return root;
}

void treeDisplay(TreeNode* root, int myDepth, int myId, int* displayDepth, int treeDepth){
  if(root == NULL  || *displayDepth < myDepth) return;

  //display my value if I am the target depth otherwise ask children
  if(myDepth == *displayDepth){
    printf("(%d,%d)=", myId >> 1, myId);
    if(root->val != NULL){
      printf("%d, ", *(root->val));
    }else{
      printf("NULL, ");
    }
  }else{
    treeDisplay(root->left, myDepth+1, (myId << 1), displayDepth, treeDepth);
    treeDisplay(root->right, myDepth+1, (myId << 1) + 1, displayDepth, treeDepth);
  } 

  //the root iterates over all depths
  if(myId == 0 &&  myDepth == 0){
    int targetDepth;
    for(targetDepth = 1; targetDepth <= treeDepth; targetDepth++){
      *displayDepth +=1;
      printf("\n%d) ",*displayDepth);
      treeDisplay(root->left, 1, 0, displayDepth, treeDepth);
      treeDisplay(root->right, 1, 1, displayDepth, treeDepth);
    }
    printf("\n");
  } 
}

int treeHeight(TreeNode* root){
  if (root == NULL){
    return -1;
  } else {
    int l = treeHeight(root->left) + 1;
    int r = treeHeight(root->right) + 1;
    int height = (l > r)? l: r;
    return height;
  }
}

void  treeDestroy(TreeNode* root){
  if(root == NULL){
    return;
  }
  treeDestroy(root->left);
  treeDestroy(root->right);
  free(root->val);
  free(root);
}

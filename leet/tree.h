#ifndef HEADER_FILE_TREE
#define HEADER_FILE_TREE
#include <stdio.h>
typedef struct _treeNode TreeNode;
struct _treeNode {
  int* val;
  TreeNode* left;
  TreeNode* right;
};

TreeNode*  treeBuild(int* arr, int idx, int arrSize);
void treeDisplay(TreeNode* root, int myDepth, int myId, int* displayDepth, int treeDepth);
int treeHeight(TreeNode* root);

#endif

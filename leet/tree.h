#ifndef HEADER_FILE_TREE
#define HEADER_FILE_TREE
#include <stdio.h>
typedef struct _treeNode TreeNode;
struct _treeNode {
  int* val;
  TreeNode* left;
  TreeNode* right;
};

void BSTreeAdd(TreeNode* root, TreeNode* node);
TreeNode*  treeBuild(int* arr, int idx, int arrSize);
TreeNode*  treeNodeBuild(int val);
void treeNodeDestroy(TreeNode* node);
void treePrint(TreeNode *root);
void treeDisplay(TreeNode* root, int myDepth, int myId, int* displayDepth, int treeHeight);
int treeHeight(TreeNode* root);
int nodeDepth(TreeNode* root, TreeNode* node);
TreeNode* getNode(TreeNode* root,int nodeVal);
#endif

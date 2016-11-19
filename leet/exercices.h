#ifndef HEADER_FILE_EXERCICES
#define HEADER_FILE_EXERCICES
#include <stdio.h>
#include <stdbool.h>
#include "tree.h"
#include "linkedlist.h"

int climbStairs(int n);
void  testlowestCommonAncestor();
TreeNode* sortedListToBST(ListNode* head);
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q);
int maxProfit(int* prices, int pricesSize);
bool isPowerOfFour(int num);

#endif

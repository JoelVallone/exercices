
#include <stdio.h>
#include <stdbool.h>
#include "tree.h"
#include "exercices.h"

/* 
   gcc tree.c exercices.c -lm -o leet && ./leet
   https://leetcode.com/problemset/algorithms/
 */
#define ARR_SIZE 7

void main(){

  int arr[ARR_SIZE]  = {-2, 0, 1, 4, 65536, 4095, 4096};
  int i = 0;
  for(i = 0; i < ARR_SIZE; i++){
    printf("Is (%d) pow 4: %d\n",arr[i], isPowerOfFour(arr[i]));
  }
}

bool isPowerOfFour(int num) {
  return (num > 0) && ((num & (num-1)) == 0) && ((num & 0x55555555) != 0);
}

//121 - either max delta or maxminimum wins O (N)
int maxProfit(int* prices, int pricesSize) {
  if (prices == NULL || pricesSize <= 1) return 0;

  int delta = 0;
  int maxDelta  = 0;
  int bestMin = prices[0];
  int i = 0;
  for(i = 0; i < pricesSize; i++){
    bestMin = bestMin > prices[i] ? prices[i] : bestMin;
    delta = prices[i] - bestMin;
    maxDelta = maxDelta < delta ? delta : maxDelta;
  }
  return maxDelta;
}

//121 - exhaustive search = O(N^2);
int maxProfitSlow(int* prices, int pricesSize) {
  if (prices == NULL || pricesSize <= 1) return 0;
  //for each value select max next value -> maintaint the max positive delta pair
  int i = 0;
  int j = 0 ;
  int maxDelta = -1;
  int localDelta = -1;
  int maxSell = 0;
  int curentBuy = 0;
  for(i = 0; i < pricesSize; i++){
    localDelta = -2;
    curentBuy = prices[i];
    maxSell = curentBuy;
    for(j = i+1; j < pricesSize; j++){
      maxSell = maxSell < prices[j] ? prices[j] : maxSell;
      
    }
    localDelta = maxSell - prices[i];
    maxDelta = localDelta > maxDelta ? localDelta : maxDelta;
  }

  if(maxDelta < 0) return 0;
  return maxDelta;


  //One pass :
  //build delta array & find max pos delta (buy) & find max neg delta (sell)
}

void  testlowestCommonAncestor(){
  int arr[] = {6, 2,8 ,0,4,7,9, -1,-1,3,5,-1,-1,-1,-1};
  TreeNode* root = treeBuild(arr, 0, (1 << 4)-1);
  int initDisplayDepth = 0;
  int treeDepth = treeHeight(root);
  printf("Tree Height = %d\n", treeDepth);
  treeDisplay(root,0,0,&initDisplayDepth,treeDepth);
  printf("%d\n", *(getNode(root,5)->val));

  int testCnt = 3;
  int i = 0;
  int lcaTest[3][2] = {{2,8},{0,5},{2,5}};
  for(i = 0; i < testCnt; i++){
    TreeNode* p = getNode(root,lcaTest[i][0]);
    TreeNode* q = getNode(root,lcaTest[i][1]);
    TreeNode* lca = lowestCommonAncestor(root, p, q);
    int lcaVal = -1;
    if( lca != NULL){
      lcaVal = *(lca->val);
    }
    printf("LCA(tree, %d, %d) = %d\n", lcaTest[i][0], lcaTest[i][1], lcaVal);
  }

  treeDestroy(root);
}

//leet 235
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q){
  if( root == NULL | p == NULL || q == NULL){
    printf("LCA NULL\n");
    return NULL;
  }

  TreeNode* biggest = q;
  TreeNode* smallest = p;
  if( *(p->val) > *(q->val) ){
    biggest = p;
    smallest = q;
  }
  int biggestVal = *(biggest->val);
  int smallestVal = *(smallest->val);
  int rootVal = *(root->val);
  printf("LCA(%d, %d, %d)\n", *(root->val), *(smallest->val),*(biggest->val));


  if(rootVal > smallestVal && rootVal < biggestVal ){
    return root;
  }else if( rootVal == smallestVal || rootVal == biggestVal){
    return root;
  }else if(rootVal > biggestVal){
    if(root->left != NULL){
      return lowestCommonAncestor(root->left, smallest, biggest);
    }else{
      return NULL;
    }
  }else if(rootVal < smallestVal){
    if(root->right != NULL){
      return lowestCommonAncestor(root->right, smallest, biggest);
    }else{
      return NULL;
    }
  }
  return NULL;
  print("LCA UNKNOWN NULL ");
}




//TODO: 70
int climbStairs(int n){
  return climbStairs(n-2) + 1 + climbStairs(n-1) + 1;
}


// 1(1) = (1) => 1

// 2(2) = (1,1), (2) => 2

// 3(3) = (1,2) , (2,1), (1,1,1) => 3

// 4(5) = (1,3) => (1,1,2) (1,2,1) (1,1,1,1)
//     (3,1) => (1,2,1) (2,1,1) (1,1,1,1)
//     (2,2) => (1,1,2) (2,2)  (2,1,1) (2,2) ==> (1,1,2) (1,2,1) (1,1,1,1) (2,1,1) (2,2) == 5
//      
//     (1,3) -> (1,1,2) : 
//              (2,  2) :      + N(2)
//     (1,2,1)




//5(8) = (1,4) = (1,(1,1,2) (1,2,1) (1,1,1,1) (2,1,1) (2,2))
//    (4,1)  = ((1,1,2) (1,2,1) (1,1,1,1) (2,1,1) (2,2),1)
 
//    (3,2) = ((1,2) , (2,1), (1,1,1),2)
//    (2,3) = (2,(1,2) , (2,1), (1,1,1))

// ==> 1,1,1,2   1,1,2,1  1,1,1,1,1   1,2,1,1   1,2,2   

//     

// 5 =  (4,1) + (1,4)
//      (3,2) + (2,3)
//      (

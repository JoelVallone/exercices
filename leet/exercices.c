
#include <stdio.h>
#include "tree.h"
#include "exercices.h"

/* 
   gcc tree.c exercices.c -lm -o leet && ./leet
   https://leetcode.com/problemset/algorithms/
 */
void main(){
  int arr[] = {0, 1,2 ,3,4,5,6,-1};
  TreeNode* root = treeBuild(arr, 0, 8);
  int initDisplayDepth = 0;
  int treeDepth = treeHeight(root);
  printf("Tree Height = %d\n", treeDepth);
  treeDisplay(root,0,0,&initDisplayDepth,treeDepth);
  treeDestroy(root);
  // int input  = 4;
  //  printf("climbStairs(%d)=%d\n",input,climbStairs(input));
}

TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q){

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

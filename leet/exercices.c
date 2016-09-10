
#include <stdio.h>
#include "tree.h"
#include "exercices.h"

/* 
   gcc tree.c exercices.c -lm -o leet && ./leet
   https://leetcode.com/problemset/algorithms/
 */
void main(){
  testlowestCommonAncestor();
  // int input  = 4;
  //  printf("climbStairs(%d)=%d\n",input,climbStairs(input));
}

void  testlowestCommonAncestor(){
  int arr[] = {6, 2,8 ,0,4,7,9, -1,-1,3,5,-1,-1,-1,-1};
  TreeNode* root = treeBuild(arr, 0, (1 << 4)-1);
  int initDisplayDepth = 0;
  int treeDepth = treeHeight(root);
  printf("Tree Height = %d\n", treeDepth);
  printf("%d", *(getNode(root,5)->val)),
  /*
  int testCnt = 3;
  int lcaTest[][] = {{2,8},{0,5},{2,5}};
  for(int i = 0; i < testCnt; i++){
    TreeNode* p = getNode(lcaTest[i][0]);
    TreeNode* q = getNode(lcaTest[i][1]);
    printf("LCA(tree, %d, %d) = %d\n", lcaTest[i][0], lcaTest[i][1], lowestCommonAncestor(root, p, q);
  }
  */

  treeDisplay(root,0,0,&initDisplayDepth,treeDepth);
  treeDestroy(root);
}

//235
//V2: root descendent traversal with interval check O(log(n))
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q){
  if( root == NULL | p == NULL || q == NULL){
    printf("LCA NULL\n");
    return NULL;
  }

  TreeNode* biggest = q;
  TreeNode* smallest = p;
  if( p->val > q->val ){
    biggest = p;
    smallest = q;
  }

  printf("LCA(%d, %d, %d)\n", *(root->val), *(smallest->val),*(biggest->val));

  if(root->val > smallest->val &&root->val < biggest->val ){
    return root;
  }else if( root->val == smallest->val || root->val == biggest->val){
    return root;
  }else if(root->val > biggest->val){
    if(root->left != NULL){
      lowestCommonAncestor(root->left, smallest, biggest);
    }else{
      return NULL;
    }
  }else if(root->val < smallest->val){
    if(root->right != NULL){
      lowestCommonAncestor(root->right, smallest, biggest);
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

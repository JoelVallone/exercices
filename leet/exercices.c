
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

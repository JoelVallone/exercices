#ifndef HEADER_FILE_LINKEDLIST
#define HEADER_FILE_LINKEDLIST
#include <stdlib.h>
#include <stdio.h>
typedef struct _listnode ListNode;
struct _listNode {
  int val;
  struct ListNode* next;
};

ListNode* linkedlistBuild(int* arr, int arrSize);
void linkedlistDestroy(ListNode* head);
ListNode* linkedlistRevert(ListNode* head);
void linkedlistPrint(ListNode *head);

#endif


#ifndef HEADER_FILE_LINKEDLIST
#define HEADER_FILE_LINKEDLIST
#include <stdlib.h>
#include <stdio.h>

typedef struct _listNode ListNode;
struct _listNode {
  int val;
  ListNode* next;
};

ListNode* linkedlistBuild(int* arr, int arrSize);
void linkedlistDestroy(ListNode* head);
ListNode* linkedlistRevert(ListNode* head);
ListNode* linkedlistCutMiddle(ListNode* head);
void linkedlistPrint(ListNode *head);

#endif


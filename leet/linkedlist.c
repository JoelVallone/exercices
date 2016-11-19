#include "linkedlist.h"

ListNode* linkedlistBuild(int* arr, int arrSize) {
  if (arrSize <= 0) return NULL;

  int i = 0;
  ListNode* head;
  ListNode* currentNode;
  ListNode* nextNode;

  head = malloc(sizeof(ListNode));    
  head->val = arr[0];
  currentNode = head;

  for(i = 1; i < arrSize; i++) {
    nextNode = malloc(sizeof(ListNode));    
    nextNode->val = arr[i];
    currentNode->next = nextNode;
    currentNode = nextNode;
  }
  return head;
}

void linkedlistDestroy(ListNode* head) {
  if(head == NULL)return;

  ListNode* current = head;
  ListNode* next;
  do{
    next = current->next;
    free(current);    
    current = next;
  }while(next != NULL);
}

ListNode* linkedlistCutMiddle(ListNode* head){
  if(head == NULL || head->next == NULL)return head;

  int cnt = 0;
  ListNode* fast = head;
  ListNode* slow = head;
  ListNode* slowPrevious = head;
  while(fast-> next != NULL){
    fast = fast->next;

    if((cnt & 0x1) == 1) {
      slowPrevious = slow;
      slow = slow->next;
    }
    cnt++;
  }
  slowPrevious->next = NULL;
  return slow;
}

ListNode* linkedlistRevert(ListNode* head) {
  if(head == NULL || head->next == NULL) return head;

  ListNode* queue = head;
  ListNode* futureNext = head;
  ListNode* futurePrevious = head->next;
  ListNode* futurePreviousPrevious = head->next->next;

  while(futurePrevious->next != NULL) {
    //Swap references
    futurePrevious->next = futureNext;

    //Move pointers
    futureNext = futurePrevious;
    futurePrevious = futurePreviousPrevious;
    futurePreviousPrevious = futurePrevious->next;
    
  }
  futurePrevious->next = futureNext;
  head = futurePrevious;
  //Clear queue.next to avoid cicrular reference to new head
  queue->next = NULL;

  return head;
}

void linkedlistPrint(ListNode *head) {
  ListNode* current = head;
  while(current != NULL){
    printf("%d,", current->val);
    current = current->next;
  }
  printf("\n");
}

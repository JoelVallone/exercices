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
    currentNode.next = nextNode;
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

ListNode* linkedlistRevert(ListNode* head) {
  if(head == NULL || head->next == NULL) return;

  LinkedList* queue = head;
  LinkedList* futureNext = head;
  LinkedList* futurePrevious = head->next;
  LinkedList* futurePreviousPrevious = head->next->next;

  while(futurePrevious->next != NULL) {
    //Swap references
    futurePrevious->next = futureNext;

    //Move pointers
    FutureNext = FuturePrevious;
    FuturePrevious = FuturePreviousPrevious;
    FuturePreviousPrevious = FuturePrevious->next;
    
  }
  head = futurePrevious;
  //Clear queue.next to avoid cicrular reference to new head
  queue->next = NULL;

  return head;
}

void linkedlistPrint(ListNode *head) {
  LinkedList* current = head;
  while(current != NULL){
    printf("%d,", current->val);
    current = current->next;
  }
    printf("\n")
}

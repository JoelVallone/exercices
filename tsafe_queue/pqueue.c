#include <stdlib.h>
#include <stdio.h>
#include "pqueue.h"
#include <pthread.h>


int main(int argc, char *argv[]){
    int i = 0,rc_p = 0,rc_c = 0;
    p_queue* q = create(8);
    pthread_t producer[CNT_PRODUCER];
    pthread_t consumer[CNT_CONSUMER];
        
    for(i = 0; i < CNT_PRODUCER && i < CNT_CONSUMER; i++){
        if(i < CNT_PRODUCER )
            rc_p = pthread_create(&producer[i], NULL, producer, (void *)q);
        if(i < CNT_CONSUMER )
            rc_c = pthread_create(&consumer[i], NULL, consumer, (void *)q);
        if (rc_p || rc_c){
         printf("instantiation ERROR; return code from pthread_create() is"
                "%d\n for the producer(s) and %d for the consumer(s) \n", rc);
         exit(-1);
        }
    }
    
    int* retval = NULL;
    for(i = 0; i < CNT_CONSUMER; i++){
        pthread_join(consumer[i]; &retval) 
    }
    destroy(q);
}

p_queue* create(int arraySize){
    p_queue* q = calloc(1, sizeof(p_queue));
    q->array = calloc(arraySize, sizeof(element));
    q->size = arraySize;
    q->count = 0;
    q->nextIn = 0;
    q->nextOut = 0;
}

void destroy(p_queue* q){
    free(q->array);
    free(q);
}

void enqueue(p_queue* q, element e){
    if(q->count == q->size) return;
    q->array[q->nextIn] = e;
    q->count++;
    q->nextIn = (q->nextIn + 1) % q->size;
}

element dequeue(p_queue* q){
    element e = NULL;
    if(q->count == 0) return e;
    e = q->array[q->nextOut];
    q->count--;
    q->nextOut = (q->nextOut + 1) % q->size;
    return e;
}

void* producer(void* q){
    int i = 0;
    p_queue* shared_q = (p_queue* q) q;
    for(i = 0; i < 50; i++){
        printf("Producer Thread : writes %d",i);
        enqueue(shared_q ,i);
    }
}

void* consumer(void* q){
    int i = 0;
    p_queue* shared_q = (p_queue* q) q;
    for(i = 0; i < 50; i++){
        printf("Consumer Thread : reads %d", dequeue(shared_q));
    }
}























#include <stdlib.h>
#include <stdio.h>
#include "pqueue.h"
#include <pthread.h>


int main(int argc, char *argv[]){
    int i = 0,rc_p = 0,rc_c = 0;
    p_queue* q = create(SIZE_QUEUE);
    pthread_t producer[CNT_PRODUCER];
    pthread_t consumer[CNT_CONSUMER];
        
    for(i = 0; i < CNT_PRODUCER || i < CNT_CONSUMER; i++){
        if(i < CNT_PRODUCER ){
            rc_p = pthread_create(&producer[i], NULL, f_producer, (void *)q);
        }
        if(i < CNT_CONSUMER ){
            rc_c = pthread_create(&consumer[i], NULL, f_consumer, (void *)q);
        }
        if (rc_p || rc_c){
         printf("instantiation ERROR; return code from pthread_create() is"
                "%d\n for the producer(s) and %d for the consumer(s) \n"
                , rc_p,rc_c);
         exit(-1);
        }
    }
    
    int* retval = NULL;
    for(i = 0; i < CNT_CONSUMER; i++){
        rc_c = pthread_join(consumer[i], (void**) &retval);
      if (rc_c) {
         printf("ERROR; return code from pthread_join() is %d\n", rc_c);
         exit(-1);
         }
      printf("Main: completed join with consumer thread %d having a status"   
            " of %d\n",i,(int*)retval);
    }
    destroy(q);
    
    return 0;
}

p_queue* create(int arraySize){
    p_queue* q = calloc(1, sizeof(p_queue));
    q->array = calloc(arraySize, sizeof(element));
    q->size = arraySize;
    q->count = 0;
    q->nextIn = 0;
    q->nextOut = 0;
    q->cs = calloc(1,sizeof(pthread_mutex_t));
    q->is_not_full   = calloc(1,sizeof(pthread_cond_t));
    q->is_not_empty  = calloc(1,sizeof(pthread_cond_t));
    pthread_mutex_init(q->cs,NULL);
    pthread_cond_init(q->is_not_full,NULL);
    pthread_cond_init(q->is_not_empty,NULL);
    return q;
}

void destroy(p_queue* q){
    free(q->array);
    pthread_cond_destroy(q->is_not_empty);
    pthread_cond_destroy(q->is_not_full);
    pthread_mutex_destroy(q->cs);    
    free(q);
}

void enqueue(p_queue* q, element e){
    pthread_mutex_lock(q->cs);
        while(q->count == q->size)
            pthread_cond_wait(q->is_not_full, q->cs);
        q->array[q->nextIn] = e;
        q->count++;
        q->nextIn = (q->nextIn + 1) % q->size;
        pthread_cond_signal(q->is_not_empty);
    pthread_mutex_unlock(q->cs);
}

element dequeue(p_queue* q){
    pthread_mutex_lock(q->cs);
        element e = NULL;
        if(q->count == 0)
            pthread_cond_wait(q->is_not_empty, q->cs);
        e = q->array[q->nextOut];
        q->count--;
        q->nextOut = (q->nextOut + 1) % q->size;
        pthread_cond_signal(q->is_not_full);
    pthread_mutex_unlock(q->cs);
    return e;
}

void* f_producer(void* q){
    int i = 0;
    p_queue* shared_q = (p_queue*) q;
    for(i = 0; i < SIZE_QUEUE; i++){
        printf("Producer Thread %u: writes %d\n",pthread_self(),i);
        fflush(stdout);
        enqueue(shared_q ,i);
    }
    pthread_exit((void*)33);
}

void* f_consumer(void* q){
    int i = 0;
    element val = -1;
    p_queue* shared_q = (p_queue*) q;
    for(i = 0; i < SIZE_QUEUE; i++){
        val = dequeue(shared_q);
        printf("Consumer Thread %u: has read %d\n",pthread_self(), val);
        fflush(stdout);
        val = -1;
    }
    pthread_exit((void*)42);
}























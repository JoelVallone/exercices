#ifndef PQUEUE
#define PQUEUE

#define CNT_PRODUCER 2
#define CNT_CONSUMER 2
#define SIZE_QUEUE 2


typedef int element;

typedef struct {
    int nextIn;
    int nextOut;
    int count;
    element* array;
    int size;
    
    pthread_mutex_t* cs;
    pthread_cond_t* is_not_full;
    pthread_cond_t* is_not_empty;
} p_queue;

int main(int argc, char *argv[]);
void* f_producer(void* q);
void* f_consumer(void* q);

p_queue* create(int arraySize);
void destroy(p_queue* q);
void enqueue(p_queue* q, element e);
element dequeue(p_queue* q);

#endif


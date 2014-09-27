#ifndef PQUEUE
#define PQUEUE

#define CNT_PRODUCER 1
#define CNT_CONSUMER 1


typedef int element;

typedef struct {
    int nextIn;
    int nextOut;
    int count;
    element* array;
    int size;
} p_queue;

int main(int argc, char *argv[]);
void* producer(p_queue* q);
void* consumer(p_queue* q);

p_queue* create(int arraySize);
void destroy(p_queue* q);
void enqueue(p_queue* q, element e);
element dequeue(p_queue* q);

#endif

#include <math.h>
#include "queue.h"

// Checks if a number is prime
int isPrime(unsigned int num) {
    if(num == 1) return 0;
    for(int i = 2; i <= sqrt(num); i++) {
        if (num % i == 0) return 0;
    }
    return 1;
}

// Creates a new node
PNode newNode(void* data) {
    PNode node = (PNode)malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;
    return node;
}

// Initials queue
PQueue createQueue() {
    PQueue q = (PQueue)malloc(sizeof(Queue));
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    pthread_mutex_init(&q->lock, NULL); // Initialize mutex
    return q;
}

// Adds new element to the queue
void enqueue(PQueue queue, void* element) {
    if(queue == NULL) return;
    
    pthread_mutex_lock(&queue->lock); // Lock mutex
    
    PNode node = newNode(element);

    if(queue->head == NULL) { // Adds first element
        queue->head = node;
        queue->tail = node;
    } else { // Adds element to the end of the queue
        queue->tail->next = node;
        queue->tail = node;
    }
    queue->size++;
    pthread_mutex_unlock(&queue->lock); // Unlock mutex

}


void* dequeue(PQueue queue) {
    if(queue == NULL) return NULL;

    pthread_mutex_lock(&queue->lock); // Lock mutex

    if(queue->head == NULL) { // Queue is empty
        pthread_mutex_unlock(&queue->lock); // Unlock mutex
        return NULL;
    }

    PNode node = queue->head;
    
    if(queue->head == queue->tail) { // Queue has only one element
        queue->head = NULL;
        queue->tail = NULL;
    } else {
        queue->head = queue->head->next;
    }
    queue->size--;
    
    // Gets data from node and free it
    void* data = node->data;
    free(node);

    pthread_mutex_unlock(&queue->lock); // Unlock mutex

    return data;
}

// Free all memory allocated for the queue
void destroyQueue(PQueue q) {
    while(q->head != NULL) {
        PNode temp = q->head;
        q->head = q->head->next;
        free(temp);
    }
    pthread_mutex_destroy(&q->lock); // Destroy mutex
    free(q);
}
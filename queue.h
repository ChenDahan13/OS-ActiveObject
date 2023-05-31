#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct node {
    void* data;
    struct node* next;
} Node, *PNode;

typedef struct queue {
    PNode head;
    PNode tail;
    int size;
    pthread_mutex_t lock;
} Queue, *PQueue;


/* ----- Functions ----- */
PNode newNode(void*);
PQueue createQueue();
void destroyQueue(PQueue);
void enqueue(PQueue, void*);
void* dequeue(PQueue);

int isPrime(unsigned int);

#endif
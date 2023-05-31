#ifndef ACTIVE_OBJECT_H
#define ACTIVE_OBJECT_H
#include <pthread.h>
#include <time.h>
#include <stdio.h>
#include "queue.h"

typedef struct activeObject {
    int running;
    pthread_t thread;
    PQueue queue;
    int (*func)(int);
    struct activeObject* next;
} ActiveObject, *PActiveObject;

/* ----- Functions ----- */
PActiveObject createActiveObject(int (*func)(int));
PQueue GetQueue(PActiveObject);
void stop(PActiveObject);
void start(PActiveObject);
void *activeObjectThread(PActiveObject);


#endif
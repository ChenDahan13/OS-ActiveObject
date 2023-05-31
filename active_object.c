#include "active_object.h"

// Creates a new active object and starts its thread
PActiveObject createActiveObject(int (*func)(int)) {
    PActiveObject ao = (PActiveObject)malloc(sizeof(ActiveObject));
    ao->running = 1; // Set running to true
    ao->func = func;
    ao->queue = createQueue();
    ao->next = NULL;
    return ao;
}

void start(PActiveObject ao) {
    printf("Starting active object\n");
    pthread_create(&ao->thread, NULL, activeObjectThread, ao);
}

/* This function is called by the thread, 
   it will dequeue the queue and execute the function passed in the active object */
void *activeObjectThread(PActiveObject ao) {
    if(ao == NULL) return; // If active object is null, return
    
    while(ao->running) { // While the active object is running
        
        void* task = dequeue(ao->queue);
         
        if(task != NULL) { // While the queue is not empty
                
            if(task == -1) { // If the task is -1, stop the thread
                if(ao->next != NULL) { // If there is a next active object, enqueue the data
                    enqueue(ao->next->queue, task);
                }
                ao->running = 0;
                break;
            }

            int data = ao->func(task);

            if(ao->next != NULL) { // If there is a next active object, enqueue the data
                enqueue(ao->next->queue, data);
            }
            
        } else {
            sleep(1);
        }
    } 
}


PQueue GetQueue(PActiveObject ao) {
    return ao->queue;
}

void stop(PActiveObject ao) {
    pthread_exit(&ao->thread);
    destroyQueue(ao->queue);
    free(ao);
}
   
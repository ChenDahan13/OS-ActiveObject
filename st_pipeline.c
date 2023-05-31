#include "st_pipeline.h"


// Generates a random number between 100000 and 999999
int generateRandNum() {
    return rand() % 900000 + 100000;
}

// ao[0] function
int func1(int data) {
    return data;
}

// ao[1] function
int func2(int data) {
    printf("Received: %d\n", data);
    if(isPrime(data)) {
        printf("true\n");
    } else {
        printf("false\n");
    }
    data = data + 11;
    return data;
}

// ao[2] function
int func3(int data) {
    printf("Received: %d\n", data);
    if(isPrime(data)) {
        printf("true\n");
    } else {
        printf("false\n");
    }
    data = data - 13;
    return data;
}

// ao[3] function
int func4(int data) {
    printf("Received: %d\n", data);
    data = data + 2;
    printf("%d\n", data);
    return data;
}


int main(int argc, char* argv[]) {
    
    if(argc < 2 || argc > 3) { // Checks the number of arguments
        printf("Usage: %s <number> and <seed>\n", argv[0]);
        return 1;
    }
    
    if(argc == 2) { // Seed wasn't passed
        srand(time(NULL)); // Sets seed as current time
    } else if(argc == 3) {
        srand(atoi(argv[2])); // Sets seed as the passed argument
    }

    PActiveObject ao[4];

    // Creates the active objects
    ao[0] = createActiveObject(func1);
    ao[1] = createActiveObject(func2);
    ao[2] = createActiveObject(func3);
    ao[3] = createActiveObject(func4);
    
    ao[0]->next = ao[1];
    ao[1]->next = ao[2];
    ao[2]->next = ao[3];

    for(int i = 0; i < atoi(argv[1]); i++) {
        enqueue(ao[0]->queue, generateRandNum());
    }
    enqueue(ao[0]->queue, -1); // Adds the end of queue signal to stop the pipeline

    // Starts the active objects
    start(ao[0]);
    start(ao[1]);
    start(ao[2]);
    start(ao[3]);

    // Waits for the threads to finish
    pthread_join(ao[0]->thread, NULL);
    pthread_join(ao[1]->thread, NULL);
    pthread_join(ao[2]->thread, NULL);
    pthread_join(ao[3]->thread, NULL);

    // Destroys the active objects
    stop(ao[0]);
    stop(ao[1]);
    stop(ao[2]);
    stop(ao[3]);
    
    return 0;
}
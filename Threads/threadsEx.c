#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#define NUM_OF_THREADS 4

void* PrintFunc(void* tid)
{
    printf("Thread tid = %ld\n", *(unsigned long*)tid);
    
    pthread_exit(tid);
}

int main()
{
    size_t i, status;
    pthread_t threads[NUM_OF_THREADS];
    size_t buffer[NUM_OF_THREADS];

    for (i = 0; i < NUM_OF_THREADS; i++)
    {
        printf("Creating thread No.%ld\n", i);
        buffer[i] = i + 10;
        status = pthread_create(&threads[i], NULL, PrintFunc, &threads[i]);
        sleep(3);
        if(status)
        {
            printf("Error creating %ld thread\n", i);
        }
    }

    for (i = 0; i < NUM_OF_THREADS; i++)
    {
        /*pthread_join(threads[i], NULL);*/
    }
}
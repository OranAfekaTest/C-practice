#include <semaphore.h>
#include <pthread.h>
#define SHARED_BETWEEN_PROCESSES 1
#define SHARED_BETWEEN_THREADS 0

int main(void)
{
    sem_t* sem = NULL;
    int resources = 5;
    sem_init(sem, SHARED_BETWEEN_THREADS, resources);

    sem_post(sem);
    sem_wait(sem);
    
    
    return 0;
}
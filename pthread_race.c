#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
/**
 * THESE DEFINE VALUES CANNOT BE CHANGED.
 * DOING SO WILL CAUSE POINTS TO BE DEDUCTED
 * FROM YOUR GRADE (15 points)
 */
/** BEGIN VALUES THAT CANNOT BE CHANGED */
#define MAX_THREADS 16
#define MAX_ITERATIONS 40
/** END VALUES THAT CANNOT BE CHANGED */


/**
 * use this struct as a parameter for the function
 * nanosleep.
 * For exmaple : nanosleep(&ts, NULL);
 */
//struct timespec ts = {0, 123456};

int globalVar = 0;// shared variable.
void* addThread(void *tid)//ADDERTHREAD
{
    int threadId = *((int*)tid);
    int i;
    struct timespec ts, ts2;
    ts.tv_sec = 0;
    ts.tv_nsec = 500000;// change time accordingly. not given in question.
    for(i = 0; i < MAX_ITERATIONS; i++)
    {
        nanosleep(&ts, &ts2);
        int temp = globalVar;
        temp += 3;
        globalVar = temp;
        printf("Current Value written to Global Variables by ADDER thread : %d is %d\n",threadId, globalVar);
    }
    return NULL;
}

void* subThread(void *tid)
{
    int threadId = *((int*)tid);
    int i;
    struct timespec ts, ts2;
    ts.tv_sec = 0;
    ts.tv_nsec = 500;
    for(i = 0; i < MAX_ITERATIONS; i++)
    {
        nanosleep(&ts, &ts2);
        int temp = globalVar;
        temp -= 3;
        globalVar = temp;
        printf("Current Value written to Global Variables by SUBTRACTOR thread : %d is %d\n",threadId, globalVar);
    }
    return NULL;
}

int main()
{
    int i;
    int error;
    pthread_t threads[MAX_THREADS+1];// array for threads.
    for(i = 1; i <= MAX_THREADS; i++)//creates threads
    {
        if(i%2 == 0)
        {
            error = pthread_create(&threads[i], NULL, addThread, (void*)&i);
            if(error)
            {
                printf("ERROR creating THREADS %d\n",error);
                exit(-1);
            }
        }
        else
        {
            error = pthread_create(&threads[i], NULL, subThread, (void*)&i);
            if(error)
            {
                printf("ERROR creating THREADS %d\n",error);
                exit(-1);
            }
        }
    }
    for(i = 1; i <= MAX_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }
    printf("Final Value of Shared Variable : %d\n",globalVar);
    
    return 0;
}

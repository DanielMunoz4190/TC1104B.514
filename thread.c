#include <stdio.h>
#include <pthread.h>
#define NUM_THREADS 10

typedef struct thread_data
{
    int threadId;
    char name[20];
    //..
} ThreadData; //shortcut que será usado por ThreadData

void *holaMundo(void *arg)
{
    ThreadData *myData = (ThreadData *)arg;
    printf("Hola desde el hilo y mi id es %d \n", myData->threadId);
    pthread_exit(NULL); //avisar a main que el hilo terminó
}

int main()
{
    ThreadData ThreadData[NUM_THREADS];
    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_t threadId;
        ThreadData[i].threadId = i;
        pthread_create(&threadId, NULL, holaMundo, (void *) &ThreadData[i]);
    }
    pthread_exit(NULL); //acabar main si los hilos terminaron
    printf("Nunca llega aqui"); //el main ya habia terminado
}
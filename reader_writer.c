#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>


sem_t wrt;
pthread_mutex_t mutex;
int k = 1;
int numreader = 0;

void *writer(void *wno)
{   
  while(1)
  {
    printf("\nWriter %d wants to write ",(*((int *)wno)));
    sem_wait(&wrt);
    k = k+1;
    printf("\nWriter %d is writing, value of k to %d",(*((int *)wno)),k);
    sleep(rand()%4);
    sem_post(&wrt);
    printf("\nWriter %d has finished writing\n",(*((int *)wno)));
   sleep(1);
    
  }

}
void *reader(void *rno)
{   

   while(1)
   {
    printf("\nReader %d wants to read ",*((int *)rno));
    // Reader acquire the lock before modifying numreader
    pthread_mutex_lock(&mutex);
    numreader++;
    if(numreader == 1) {
        sem_wait(&wrt); // If this id the first reader, then it will block the writer
    }
    pthread_mutex_unlock(&mutex);
    // Reading Section
    printf("\nReader %d: read k as %d",*((int *)rno),k);
    sleep(rand()%4);
    
    // Reader acquire the lock before modifying numreader
    pthread_mutex_lock(&mutex);
    numreader--;
    if(numreader == 0) {
        sem_post(&wrt); // If this is the last reader, it will wake up the writer.
    }
    printf("\nReader %d has finished reading \n",*((int *)rno));
    pthread_mutex_unlock(&mutex);
    sleep(1);
   
    
  }
}

int main()
{   

    pthread_t read[10],write[5];
    pthread_mutex_init(&mutex, NULL);
    sem_init(&wrt,0,1);
    int pc,a[10];
  //input from user
    printf("HOW MANY READER AND WRITER ARE THERE? ");
    scanf("%d",&pc);
    printf("NAME THE READER AND WRITER :: ");
    for(int i=1;i<=pc;i++)
     {
    scanf("%d",&a[i]);
    }
   
    for(int i = 1; i <= pc-1; i++) {
        pthread_create(&write[i], NULL, (void *)writer, (void *)&a[i]);
        sleep(1);
    }


    for(int i = 1; i <= pc; i++) {
        pthread_create(&read[i], NULL, (void *)reader, (void *)&a[i]);
        sleep(1);
    }
    
    for(int i = 1; i <= pc; i++) {
        pthread_join(read[i], NULL);
    }
    for(int i = 1; i <= pc-1; i++) {
        pthread_join(write[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    sem_destroy(&wrt);

    return 0;
    
}


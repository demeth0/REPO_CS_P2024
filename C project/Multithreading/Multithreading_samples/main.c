/*
sources :
    http://manpagesfr.free.fr/man/man3/pthread_mutex_init.3.html
    https://www.thegeekstuff.com/2012/05/c-mutex-examples/
    https://man7.org/linux/man-pages/man3/pthread_join.3.html
    https://man7.org/linux/man-pages/man3/pthread_create.3.html
*/

#include <stdio.h>
#include <stdlib.h>
#include<pthread.h>

pthread_t thread1;
pthread_t thread2;

int counter=0; //global var

pthread_mutex_t lock; //for thread synchronisation (mutual exclusion)

void* Thread1(void *argt){
    pthread_mutex_lock(&lock);
    
    {
        printf("doing execution of thread1 (%d)\n", counter);
        counter+=122;
    }

    pthread_mutex_unlock(&lock);
}

void* Thread2(void *argt){
    pthread_mutex_lock(&lock);  //si lock pas verouiller le verouille/ si lock deja verouiller alors sleep jusqu'a deverouiller

    { //opérations du thread 
        printf("doing execution of thread2 (%d)\n", counter);
        counter+=250;
    }

    pthread_mutex_unlock(&lock); //debloque lock
}

int main(int argc, char const *argv[])
{
    if(pthread_mutex_init(&lock, NULL) != 0)               //initialisation du synchroiseur de thread
    {
        printf("échec de l'initialisation du mutex\n");
        return 1;
    }

    //creation et démarrage du thread1
    int status = pthread_create(&thread1, NULL, &Thread1, NULL); //thread object, initialisation function, run function , args
    if(status!=0){
        printf("failed to create thread 1\n");
        return 0;
    }

    //creation et démarrage du thread2
    status = pthread_create(&thread2, NULL, &Thread2, NULL); //thread object, initialisation function, run function , args
    if(status!=0){
        printf("failed to create thread 2\n");
        return 0;
    }

    pthread_join(thread1, NULL);  //waiting for thread1 to finish
    pthread_join(thread2, NULL);  //waiting for thread2 to finish
    printf("value: %d\n", counter);
    pthread_mutex_destroy(&lock); //destruction du mutex
    return 0;
}
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
#include <unistd.h>

pthread_t thread1;
pthread_t thread2;

int counter=0; //global var
unsigned short int stop  = 0; 
pthread_mutex_t lock; //for thread synchronisation (mutual exclusion)

unsigned short int getStopCode(){
    unsigned short int code=0;
   
    pthread_mutex_lock(&lock);
    
    code=stop;

    pthread_mutex_unlock(&lock);
    
    return code;
}

void setStopCode(unsigned short int ncode){
    pthread_mutex_lock(&lock);
    stop=ncode;
    pthread_mutex_unlock(&lock);
}

void* Thread1(void *argt){
    char word[6];
    while(stop==0){
        scanf("%5s",word);
        printf("%s\n", word);
        if(strcmp(word,"stop")==0){
            printf("stop request\n");
            setStopCode(1);
            printf("stopped\n");
        }
    }
}

void* Thread2(void *argt){
    unsigned short int playing=1;
    
    while(playing==1){
        if(getStopCode()==1){
            printf("end");
            return NULL;
        }
        printf("counting %d\n",counter);
        pthread_mutex_lock(&lock);
        counter++;
        
        sleep(1);
        pthread_mutex_unlock(&lock);
        
    }
    
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
    pthread_mutex_destroy(&lock); //destruction du mutex
    return 0;
}
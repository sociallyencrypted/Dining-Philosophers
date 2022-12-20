#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>
#include <signal.h>

sem_t forks[5];
sem_t soup[2]; // no tea :(
int fatness[5] = {0,0,0,0,0};

void eat(int phil)
{
	printf("\nPhilosopher %d is eating",phil);
    fatness[phil]++;
    sleep(0.1);
}

void think(int phil){
    printf("\nPhilosopher %d is thinking",phil);
    sleep(0.1); // the average philosopher; sleeps on their thinking
}

int get_forks_and_souppp(int phil){
    int sauce = -1; // we like the soup with the sauce
    while (sauce == -1){
        // printf("\nPhilosopher %d is waiting for soup",phil);
        if (sem_trywait(&soup[0]) == 0) {
            sauce = 0;
        }
        else if (sem_trywait(&soup[1]) == 0) {
            sauce = 1;
        }
    }
    if (phil==4){
        sem_wait(&forks[phil]);
        sem_wait(&forks[(phil+1)%5]);
    }
    else{
        sem_wait(&forks[(phil+1)%5]);
        sem_wait(&forks[phil]);
    }
    return sauce;
}

void release_forks(int phil, int sauce){
    sem_post(&forks[(phil+1)%5]);
    sem_post(&forks[phil]);
    sem_post(&soup[sauce]);
}

void * philosophise(int phil)
{
    while (1) {
        think(phil);

        int sauce = get_forks_and_souppp(phil);

        eat(phil);

        printf("\nPhilosopher %d has finished eating",phil);

        release_forks_and_souppp(phil, sauce);
    }
}

void print_stats(){
    for (int i = 0; i < 5; i++) {
        printf("\nPhilosopher %d has eaten %d times", i, fatness[i]);
    }
    exit(0);
}

int main()
{
    // call print_stats() when ctrl-c is pressed
    signal(SIGINT, print_stats);
    int philosopherIDs[5]; // the perils of the modern world, even the philosophers have been IDed
	pthread_t threadIDs[5]; //this is excusable
	
	for(int i=0;i<5;i++){
		sem_init(&forks[i],0,1);
        philosopherIDs[i] = i;
    }

    for (int i = 0; i < 2; i++) {
        sem_init(&soup[i],0,1);
    }
		
	for(int i=0;i<5;i++){
		pthread_create(&threadIDs[i],NULL,philosophise,philosopherIDs[i]);
	}

	for(int i=0;i<5;i++){
		pthread_join(threadIDs[i],NULL);
    }
}
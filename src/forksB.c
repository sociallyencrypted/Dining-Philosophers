//The dining philosophers problem contains five philosophers sitting on a round
//table can perform only one among two actions – eat and think. For eating, each
// of them requires two forks, one kept beside each person. Typically, allowing
// unrestricted access to the forks may result in a deadlock. Write a program
// to simulate the philosophers using threads, and the forks using global variables.
// Resolve the deadlock using semaphores.

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>
#include <signal.h>

sem_t forks[5];
int fatness[5] = {0,0,0,0,0};

void eat(int phil)
{
	printf("\nPhilosopher %d is eating",phil);
    fatness[phil]++;
}

void think(int phil){
    printf("\nPhilosopher %d is thinking",phil);
}

void get_forks(int phil){
    if (phil==4){
        sem_wait(&forks[phil]);
        sem_wait(&forks[(phil+1)%5]);
        sem_wait(&soup[phil % 2]);
    }
    else{
        sem_wait(&forks[(phil+1)%5]);
        sem_wait(&forks[phil]);
    }
}

void release_forks(int phil){
    sem_post(&forks[(phil+1)%5]);
    sem_post(&forks[phil]);
}

void * philosophise(int phil)
{
    while (1) {
        think(phil);

        get_forks(phil);

        eat(phil);

        printf("\nPhilosopher %d has finished eating",phil);

        release_forks(phil);
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
		
	for(int i=0;i<5;i++){
		pthread_create(&threadIDs[i],NULL,philosophise,philosopherIDs[i]);
	}

	for(int i=0;i<5;i++){
		pthread_join(threadIDs[i],NULL);
    }
}
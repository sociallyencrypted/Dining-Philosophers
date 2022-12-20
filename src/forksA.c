#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include <signal.h>

int forks[5];
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
    int left = phil;
    int right = (phil+1)%5;
    int acquired = 0;
    while (acquired == 0){
        if (phil%2==0){
            if (forks[left] == 1 && forks[right] == 1){
                forks[left] = 0;
                forks[right] = 0;
                acquired = 1;
            }
        }
        else{
            if (forks[right] == 1 && forks[left] == 1){
                forks[right] = 0;
                forks[left] = 0;
                acquired = 1;
            }
        }
    }
}

void release_forks(int phil){
    int left = phil;
    int right = (phil+1)%5;
    forks[left] = 1;
    forks[right] = 1;
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
        forks[i] = 1;
        philosopherIDs[i] = i;
    }
		
	for(int i=0;i<5;i++){
		pthread_create(&threadIDs[i],NULL,philosophise,philosopherIDs[i]);
	}

	for(int i=0;i<5;i++){
		pthread_join(threadIDs[i],NULL);
    }
}
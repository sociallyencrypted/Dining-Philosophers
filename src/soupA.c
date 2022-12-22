#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include <signal.h>


int forks[5];
int soup[2];
int fatness[5] = {0,0,0,0,0};

void eat(int phil)
{
	printf("\nPhilosopher %d is eating",phil);
    fatness[phil]++;
    sleep(0.1);
}

void think(int phil){
    printf("\nPhilosopher %d is thinking",phil);
    sleep(0.1);
}

int get_forks_and_souppp(int phil){

    int left = phil;
    int right = (phil+1)%5;
    int bowlAcquired = 0;
    while (!bowlAcquired){
        // try acquire bowl then forks otherwise yield all
        if (soup[0] == 1 || soup[1] == 1){
            if (soup[0]==1){
                soup[0] = 0;
            }
            else{
                soup[1] = 0;
            }
        }
        bowlAcquired = 1;
        // try acquire forks
        int acquired = 0;
        while (acquired == 0){
            if (forks[right] == 1 && forks[left] == 1){
                forks[right] = 0;
                forks[left] = 0;
                acquired = 1;
            }
            else {
                // release bowl
                if (soup[0] == 0){
                    soup[0] = 1;
                }
                else{
                    soup[1] = 1;
                }
                bowlAcquired = 0;
                break;
            }
        }
    }

}

void release_forks(int phils){
    int left = phils;
    int right = (phils+1)%5;
    forks[left] = 1;
    forks[right] = 1;
    int sauce = phils % 2;
    soup[sauce] = 1;
}

void * philosophise(int phil)
{
    while (1) {
        think(phil);

        get_forks_and_souppp(phil);

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
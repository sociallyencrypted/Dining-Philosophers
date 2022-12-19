//The dining philosophers problem contains five philosophers sitting on a round
//table can perform only one among two actions – eat and think. For eating, each
// of them requires two forks, one kept beside each person. Typically, allowing
// unrestricted access to the forks may result in a deadlock. Write a program
// to simulate the philosophers using threads, and the forks using global variables.
// Resolve the deadlock using strict ordering of resources

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void philosopher(int);
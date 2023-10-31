// \*
// compile with:
// 	g++ threadex2start.cpp -lpthread -o thread2

// run with:
// 	.\thread2
// */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

void *functionC(void *);

// initialize mutex
pthread_mutex_t mutex1 = PTHREAD_RECURSIVE_MUTEX_INITIALIZER_NP;
int counter = 0;
int temp;

int main()
{

	// declare the ids of thread 1 and thread 2
	pthread_t thread1, thread2;
	int rc1, rc2;

	// Create two independent threads each of which will execute functionC
	rc1 = pthread_create(&thread1, NULL, &functionC, NULL);
	rc2 = pthread_create(&thread2, NULL, &functionC, NULL);

	// Wait till threads are completed before main continues (notice however that threads do never return).
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);

	sleep(10);
	// This returns error when mutex is still busy.
	pthread_mutex_destroy( &mutex1);
}

void *functionC(void *)
{
	while (1)
	{
		// lock mutex (try to see how the behaviour changes if the mutex is present or absent)
		int ret = pthread_mutex_lock( &mutex1);
		/* For recursive mutex the operation will be still succesfull 
		   and function will be still executed, but the kernel 
		   incrementation */ 
		// printf("Mutex lock returns: %d\n", ret);


		temp = counter;
		temp = temp + 1;

		// introduce a delay of one second to increase the probability of a preemption to occur
		sleep(1);
		counter = temp;

		// print counter value
		printf("Counter value: %d \n",counter);

		// unlock mutex (try to see how the behaviour changes if the mutex is present or absent)
		// pthread_mutex_unlock( &mutex1);

	}
}

// OPTIONAL: try to define the mutex as a "recursive" (see the slides about the concept of a "recursive mutex"). Each
// thread must call the lock function and the unlock function twice to test the mechanism.g
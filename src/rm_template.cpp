//compile with: g++ -lpthread <sourcename> -o <executablename>

//This exercise shows how to schedule threads with Rate Monotonic

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <math.h>
#include <sys/types.h>

//code of periodic tasks
void task1_code( );
void task2_code( );
void task3_code( );

//code of aperiodic tasks (if any)

//characteristic function of the thread, only for timing and synchronization
//periodic tasks
void *task1( void *);
void *task2( void *);
void *task3( void *);

//aperiodic tasks (if any)

// initialization of mutexes and conditions (only for aperiodic scheduling)

#define INNERLOOP 1000
#define OUTERLOOP 2000

#define NPERIODICTASKS 3
#define NAPERIODICTASKS 0
#define NTASKS NPERIODICTASKS + NAPERIODICTASKS

long int periods[NTASKS];
struct timespec next_arrival_time[NTASKS];
double WCET[NTASKS];
pthread_attr_t attributes[NTASKS];
pthread_t thread_id[NTASKS];
struct sched_param parameters[NTASKS];
int missed_deadlines[NTASKS];

int
main()
{
  	// set task periods in nanoseconds
	//the first task has period 100 millisecond
	//the second task has period 200 millisecond
	//the third task has period 400 millisecond
	//you can already order them according to their priority; 
	//if not, you will need to sort them

  	//for aperiodic tasks we set the period equals to 0

	//this is not strictly necessary, but it is convenient to
	//assign a name to the maximum and the minimum priotity in the
	//system. We call them priomin and priomax.

  	struct sched_param priomax;
  	priomax.sched_priority=sched_get_priority_max(SCHED_FIFO);
  	struct sched_param priomin;
  	priomin.sched_priority=sched_get_priority_min(SCHED_FIFO);

	// set the maximum priority to the current thread (you are required to be
  	// superuser). Check that the main thread is executed with superuser privileges
	// before doing anything else.


  	// execute all tasks in standalone modality in order to measure execution times
  	// (use gettimeofday). Use the computed values to update the worst case execution
  	// time of each task.

 	int i;
  	for (i =0; i < NTASKS; i++)
    	{

		// initializa time_1 and time_2 required to read the clock
		struct timespec time_1, time_2;
		clock_gettime(CLOCK_REALTIME, &time_1);

		//we should execute each task more than one for computing the WCET
		//periodic tasks
      		
      		//aperiodic tasks

		clock_gettime(CLOCK_REALTIME, &time_2);

		// compute the Worst Case Execution Time (in a real case, we should repeat this many times under
		//different conditions, in order to have reliable values

      		printf("\nWorst Case Execution Time %d=%f \n", i, WCET[i]);
    	}

    	// compute U

    	// compute Ulub by considering the fact that we have harmonic relationships between periods
    	
	//if there are no harmonic relationships, use the following formula instead
	//double Ulub = NPERIODICTASKS*(pow(2.0,(1.0/NPERIODICTASKS)) -1);
	
	//check the sufficient conditions: if they are not satisfied, exit  

  	sleep(5);

  	// set the minimum priority to the current thread: this is now required because 
	//we will assign higher priorities to periodic threads to be soon created
	//pthread_setschedparam

  	if (getuid() == 0)
    		pthread_setschedparam(pthread_self(),SCHED_FIFO,&priomin);

  
  	// set the attributes of each task, including scheduling policy and priority
  	for (i =0; i < NPERIODICTASKS; i++)
    	{
		//initializa the attribute structure of task i

		//set the attributes to tell the kernel that the priorities and policies are explicitly chosen,
		//not inherited from the main thread (pthread_attr_setinheritsched) 
      
		// set the attributes to set the SCHED_FIFO policy (pthread_attr_setschedpolicy)

		//properly set the parameters to assign the priority inversely proportional 
		//to the period

		//set the attributes and the parameters of the current thread (pthread_attr_setschedparam)
    	}

 	// aperiodic tasks

	//delare the variable to contain the return values of pthread_create	
  	int iret[NTASKS];

	//declare variables to read the current time
	struct timespec time_1;
	clock_gettime(CLOCK_REALTIME, &time_1);

  	// set the next arrival time for each task. This is not the beginning of the first
	// period, but the end of the first period and beginning of the next one. 
  	for (i = 0; i < NPERIODICTASKS; i++)
    	{
		// first we encode the current time in nanoseconds and add the period 

		//then we compute the end of the first period and beginning of the next one

       		missed_deadlines[i] = 0;
    	}
	
	// create all threads(pthread_create)

  	// join all threads (pthread_join)

  	// set the next arrival time for each task. This is not the beginning of the first
	// period, but the end of the first period and beginning of the next one. 
  	for (i = 0; i < NTASKS; i++)
    	{
      		printf ("\nMissed Deadlines Task %d=%d", i, missed_deadlines[i]);
		fflush(stdout);
    	}
  	exit(0);
}

// application specific task_1 code
void task1_code()
{
	//print the id of the current task
  	printf(" 1[ "); fflush(stdout);

	//this double loop with random computation is only required to waste time
	int i,j;
	double uno;
  	for (i = 0; i < OUTERLOOP; i++)
    	{
      		for (j = 0; j < INNERLOOP; j++)
		{
			uno = rand()*rand()%10;
    		}
  	}

  	// when the random variable uno=0, then aperiodic task 5 must
  	// be executed
 
  	// when the random variable uno=1, then aperiodic task 5 must
  	// be executed
  
  	//print the id of the current task
  	printf(" ]1 "); fflush(stdout);
}

//thread code for task_1 (used only for temporization)
void *task1( void *ptr)
{
	// set thread affinity, that is the processor on which threads shall run
	cpu_set_t cset;
	CPU_ZERO (&cset);
	CPU_SET(0, &cset);
	pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t), &cset);

   	//execute the task one hundred times... it should be an infinite loop (too dangerous)
  	int i=0;
  	for (i=0; i < 100; i++)
    	{
      		// execute application specific code

		// it would be nice to check if we missed a deadline here... why don't
		// you try by yourself?

		// sleep until the end of the current period (which is also the start of the
		// new one

		// the thread is ready and can compute the end of the current period for
		// the next iteration
    	}
}

void task2_code()
{
	//print the id of the current task
  	printf(" 2[ "); fflush(stdout);
	int i,j;
	double uno;
  	for (i = 0; i < OUTERLOOP; i++)
    	{
      		for (j = 0; j < INNERLOOP; j++)
		{
			uno = rand()*rand()%10;
		}
    	}
	//print the id of the current task
  	printf(" ]2 "); fflush(stdout);
}


void *task2( void *ptr )
{
	// set thread affinity, that is the processor on which threads shall run
	cpu_set_t cset;
	CPU_ZERO (&cset);
	CPU_SET(0, &cset);
	pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t), &cset);

	int i=0;
  	for (i=0; i < 100; i++)
    	{
		//see task 1

    	}
}

void task3_code()
{
	//print the id of the current task
  	printf(" 3[ "); fflush(stdout);
	int i,j;
	double uno;
  	for (i = 0; i < OUTERLOOP; i++)
    	{
      		for (j = 0; j < INNERLOOP; j++);		
			double uno = rand()*rand()%10;
    	}
	//print the id of the current task
  	printf(" ]3 "); fflush(stdout);
}

void *task3( void *ptr)
{
	// set thread affinity, that is the processor on which threads shall run
	cpu_set_t cset;
	CPU_ZERO (&cset);
	CPU_SET(0, &cset);
	pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t), &cset);

	int i=0;
  	for (i=0; i < 100; i++)
    	{
		//see task 1
	
	}
}


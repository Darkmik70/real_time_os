/*
 * compile with: 	g++ threadex1start.cpp -lpthread -o thread1
 *
 * run with:
 *	.\thread1
 */

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *print_message_function(void *ptr);

int main()
{
     // Declare the ids of thread 1 and thread 2
     pthread_t thread1, thread2;

     // return status of threads
     void *ret1, *ret2; 

     const char *message1 = "1";
     const char *message2 = "2";
     int iret1, iret2;

     // Create two independent threads each of which will execute the function
     // print_message_function, by passing a different string as the fourth parameter.
     // That is, the first thread has message1 as the fourth parameter, the second thread has
     // message2 as the fourth parameter

     iret1 = pthread_create(&thread1, NULL, print_message_function, (void *)message1);
     iret2 = pthread_create(&thread2, NULL, print_message_function, (void *)message2);

     // Wait till threads are complete before main continues. Unless we
     // wait we run the risk of executing an exit which will terminate
     // the process and all threads before the threads have completed.

     pthread_join(thread1, &ret1);
     printf("thread 1 returned with state: %s\n", (char *) ret1); //  %ld\n", (long) ret1);
     pthread_join(thread2, &ret2);
     printf("thread 2 returned with state: %s\n", (char *) ret2);


     // OPTIONAL: try to get the return state of threads using the second parameter of pthread_join, and print it
     return 0;
}

void *print_message_function(void *ptr)
{
     char *message;
     message = (char *)ptr;
     int i;
     for (i = 0; i < 10000; i++)
     {
          printf("%s", message);
          usleep(15);
          // print the message and flush output on the screen
     }

     printf("\n");

     // OPTIONAL: when exiting from the thread,
     // use pthread_exit and properly set the error code,
     // such that this value can be retrieved in the main thread
     // when using the join function
     pthread_exit((void *) "SUCCES"); // Printing message as success exit code;
}
/*
//  intdate.c
//  Assignment 3
//
//  Parth Kejriwal, Section 2
//  Ritvik Upadhyaya, Section 2
*/
/* This program prints the current date and time every 3 seconds
 * and exits the program when Control+c is entered 5 times. 
 *
 */

#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
/*
 * global variables to declare and initialize the number of seconds for the
 * alarm to go off and number of times remaining to press Ctrl+C to exit.
 */
int count = 5;
int seconds = 3;

/* SIGALRM handler
 * handles the SIGALRM interrupt and prints the current time and date every 
 * 3 seconds.
 *
 */

void handler_SIGALRM() {
    time_t currentTime;
/* time() is void, no return value*/ 
    time(&currentTime);    
   /* ctime() returns the time in a CString*/ 
    printf("current time is %s", ctime(&currentTime));   

    if (alarm(seconds) != 0) {
	 /* alarm should return 0*/
	printf("Error when setting up alarm(%d). \n", seconds);

	}
    return;
}

/*
 * SIGINT handler
 * this function handles the SIGINT interrupt and prints the number of times
 * remaining for the program to exit it. The program exits when Ctrl+C is 
 * entered 5 times with a message.
 */

void handler_SIGINT(){
    count--;
    if (count >=1 ) {
        printf("\nControl-c caught. %d more before program ends.\n",count);
    }
    if (count == 0) {
         printf("\nFinal control-c caught. Exiting.\n");
        exit(0);
    }
    
}

/* main function of the program*/
int main() {
    
    /* Setting up the alarm*/
    if (alarm(seconds) != 0) {
	printf("Error when setting up alarm(%d). \n", seconds);
	}   /* alarm should return 0*/
    
    /* Setting up sigaction() for SIGALRM*/
    struct sigaction sa1;
    sa1.sa_handler = handler_SIGALRM;
    if (sigaction(SIGALRM, &sa1, NULL) != 0) {
	printf("Error when setting up sigaction() for SIGALRM. \n");
	}

    /* Setting up sigaction() for SIGINT*/
    struct sigaction sa2;
    sa2.sa_handler = handler_SIGINT;
    sa2.sa_flags =0;

    if (sigaction(SIGINT, &sa2, NULL) != 0) {
	/* should not happen */
	printf("Error when setting up sigaction() for SIGINT. \n");
	}
    
    printf("Date will be printed every %d seconds\n", seconds);
    printf("Enter ^C 5 times to end the program:\n");
    srandom(time(NULL)); 
    
    /* Infinite loop*/
    while (1) {
        }   
    
    return 0;
}

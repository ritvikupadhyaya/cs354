/*
  division.c

  CS 354 - Section 2
  Assignment 3
  Program 2

  Parth Kejriwal, 03/23/2015
  Ritvik Upadhyaya, 03/23/2015
*/
/*
 * This program prompts the user to input 2 integers and find the quotient
 * and remainder. This program then catches the interrupt when we try to 
 * divide it by 0 and gracefully exits the program. It also exits the program
 * when Control+c combination is entered by user. 
 * */
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

/* Global variable count for # of times the operation has been done*/

int count = 0; 
/* SIGFPE handler
 *
 * handler_SIGFPE handles the SIGFPE interrupt and exits the program
 * with an error message when a division by 0 is attempted.
 *
 * */

void handler_SIGFPE() {
  
    printf("Error: a division by 0 operation was attempted.\n");
    printf("Total number of operations completed: %d\n", count);
    printf("The program will be stopped.\n");
    exit(0);
}

/* SIGINT handler
 *  
 *  handles the SIGINT interrupt when a control+c combination is entered
 *  Exits the program with an error message and prints the number of 
 *  successful operations conducted.
 *
 * */

void handler_SIGINT() {
   /* "\n" is printed because ^C does not come with a newline*/
    printf("\nTotal number of operations successfully completed: %d\n", count); 
    printf("The program will be halted.\n");
    exit(0);
}

/* main function of the program
 *
 */
int main() {

    /* Setting up sigaction() for SIGFPE*/
    struct sigaction sa1;
    sa1.sa_handler = handler_SIGFPE;
   
    if (sigaction(SIGFPE, &sa1, NULL) != 0){
	printf("Error when setting up sigaction() for SIGFPE. \n");
	}
    
    /* Setting up sigaction() for SIGINT*/
    struct sigaction sa2;
    sa2.sa_handler = handler_SIGINT;
    
    if (sigaction(SIGINT, &sa2, NULL) != 0) {
	printf("Error when setting up sigaction() for SIGINT. \n");
	}
    
    /* Infinite loop*/
    while (1) {
	/*
 	* variable declarations for the 2 user inputs.	 	
 	*/
        int num1, num2;
	/*
 	* for user input 	
 	*/
        char input[100];

        printf("Enter first integer: ");
         /* max length is set to 100*/
	if (fgets(input, 100, stdin) != NULL) {    
         /* atoi() returns the int directly*/
   		num1 = atoi(input);          
	}
        
	printf("Enter second integer: ");
         /* max length is set to 100*/
	if (fgets(input, 100, stdin) != NULL) 
	{
         /* atoi() returns the int directly*/
		num2 = atoi(input);
        }
        
	printf("%d / %d is %d with a remainder of %d\n", num1, num2, num1/num2, num1%num2);
        count++;
    }
    
    return 0;
}

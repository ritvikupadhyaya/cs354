/*Assignment 1, stats.c
 * Authors: Ritvik Upadhyaya Section 2,
 * 		 : Parth Kejriwal Section 2
 *
 * This program reads the integers from a binary file and puts them
 * in an array and calculates the average of numbers
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>
#include <unistd.h>

/*This is the main function of the program. Carries all the functions
 * of this program like reading the integers from the file, putting into
 * the array and calculating the average.
 * Parameters:
 * argc: the number of arguments
 * argv[]: the actual command line arguments.
 *
 * Returns: integer.
 */
int main(int argc, char *argv[]){
    
    /* argc is the number of command line arguments*/
    /* argv gives the program name and the file name*/
    
    int file;
    char *inputfile;
    int sum;
    sum = 0;
    float average;
    average = 0;
    
    if(argc != 2){
        /*We print argv[0] for the program name */
        printf("usage: stats <file>\n");
        exit(1);
    }
    
    inputfile = argv[1];
    /* Assuming filename is containedin argv[1]*/
    
    file = open(inputfile, O_RDONLY);
    /*open returns 0 if file is unopened*/
    
    /*If the file cannot be opened or there was an*/
    /* error while opening	*/
    if(file == -1){
        printf("Could not open file\n");
        exit(1);
    }
    
    /* calculating the perfect size of the array using fstat*/
    struct stat inStat;
    fstat(file, &inStat);
    int size = inStat.st_size;
    int n = (int)(size / sizeof(int));
    
    /* pointer to the array */
    int *array = (int *)malloc(size);
    int i;
    
    /*reading individual integers from the input file*/
    for (i=0; i < n; i++) {
        int inputVal = (int)read(file, &array[i], sizeof(int));
    }
    /* closing the file*/
    
    if(close(file)==-1){
        printf("error closing file -- quitting\n");
        exit(1);
    }
    
    /*calculating the average*/
    /*the number of elements in the array */
    int elements;
    for (i=n-1; i>=0; i--) {
        sum += array[i];
        elements++;
    }
    
    /*calculating the average of the numbers*/
    average= sum/ elements;
    
    /*printing finally*/
    printf("Number of numbers averaged: %d\n Average of numbers: %d\n",
           elements, (int)average);
    
}
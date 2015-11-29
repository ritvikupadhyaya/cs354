/*
 * Assignment 1
 * game.c
 * Authors: Parth Kejriwal, Section 2
 *		 : Ritvik Upadhyaya, Section 2
 * This program reads the integers from a binary file and builds a singly linked
 * with them. Then, the program repetitively asks the user to guess an integer
 * that might be in the list. The user enters a guess, and the program searches
 * the linked list to either find the integer or not. It prints a message as to
 * whether it found the integer or not.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>
#include <unistd.h>

/* creating the node struct*/
typedef struct Node {
    int data;
    struct Node * next;
} Node;

Node * createlist(int fd);
Node * listadd(Node *head, int intforlist);

/*
 This function reads one integer at a time
 from that file, and for each integer, calls listadd,
 which will add the integer to the list.
 
 Parameters: int fd: the file descriptor.
 
 It returns the head of the list once the list has been made,
 returns the value NULL otherwise.
 */

Node * createlist(int fd){
    
    /* calculating the size of the file*/
    struct stat inStat;
    fstat(fd, &inStat);
    int size = inStat.st_size;
    int n = (int)(size / sizeof(int));
    
    Node * head;
    head = NULL;
    
    int i;
    /* reading individual integers from the file */
    for (i=0; i < n; i++) {
        
        int temp;
        read(fd, &temp, sizeof(int));
        /* adding them to the linked list*/
        
        head = listadd(head, temp);
        printf("%d\n", head->data);
    }
    /* closing the file now*/
    if(close(fd)==-1){
        printf("error closing file - aborting\n");
        exit(1);
    }
    return head;
}

/*
 This function creates a new Node structure, and hooks it
 into the list at the head.
 
 Parameters: head: pointer to the head of the linked list
 : intforlist: the integer to be added to the list
 
 Return: the (new) head of the linked list
 */

Node * listadd(Node *head, int intforlist){
    Node* newHead = malloc(sizeof(Node));
    newHead->data = intforlist;
    newHead->next = head;
    return newHead;
}

/*
 This function plays the game, taking care of printing out prompts,
 reading in the user input, converting the C string to an integer
 and printing the result of each user's guess.
 
 Parameter: listhead: pointer to the head of the linked list.
 */
void playgame(Node * listhead){
    /* value of user input*/
    int val;
    char userinput[12];
    /*prompting the user to play the game*/
    printf("This game has you guess which integers are in the list.\n");
    printf("Enter an integer (followed by the newline)\n");
    printf("or q (followed by the newline) to quit.\n");
    printf("Integer guess: ");
    
    /* getting the value of user's input*/
    if(fgets(userinput,sizeof userinput, stdin)!=NULL){
        
        /* if the input doesn't start with the letter q, the program runs*/
        /* quits otherwise */
        while(userinput[0] != 'q'){
            
            /* string to integer*/
            val=atoi(userinput);
            
            /* calling the inlist function to check if the list contains*/
            /* the integer or not*/
            /* printing the required prompt and asking user to enter again*/
            if(inlist(listhead, val)==1){
                printf("%d is on the list.\n", val);
                printf("Integer guess: ");
                fgets(userinput, sizeof userinput, stdin);
            }
            
            /* if the integer is not present in the list*/
            else{
                printf("%d is not on the list.\n", val);
                
                printf("Integer guess: ");
                fgets(userinput, sizeof userinput, stdin);
                
            }
            
        }
        /* if the user input starts with q, the program is exitted*/
        if(userinput[0]=='q'){
            exit(1);
        }
    }
}


/*
 * This function iterates through the list, comparing the value in a node to
 * intvalue. If it finds intvalue in the list, the function stops looking at
 * further values and returns the value 1, otherwise 0.
 *
 * Parameters:
 * head: pointer to the head of the list of integers
 * intvalue: value to be searched.
 *
 * Return: 1 if the list has the value
 *		  0 if it doesnt
 */

int inlist(Node *head, int intvalue){
    
    /* comparing till the end of the list*/
    while(head!= NULL){
        
        /* checking if the value in node equals the value we are looking for*/
        /* if yes, then 1 is returned*/
        /* continues forward in the list otherwise and repeats*/
        if(head->data==intvalue){
            return 1;
            break;
        }
        
        head= head->next;
    }
    /* if the value is not in the list, 0 is returned.*/
    return 0;
}


/*This is the main function of the program. Carries all the functions
 * of this program like reading the integers from the file, putting into
 * the array and calculating the average.
 * Parameters:
 * argc: the number of arguments
 * argv[]: the actual command line arguments.
 *
 * Returns: integer.
 */

int main(int argc, const char * argv[])
{
    Node * createlist(int fd);
    Node * listadd(Node *head, int intforlist);
    int file;
    char *inputfile;
    
    if(argc != 2){
        /*We print argv[0] for the program name */
        printf("usage: game <file>\n");
        exit(1);
    }
    
    inputfile = argv[1];
    /* Assuming filename is containedin argv[1]*/
    
    file = open(inputfile, O_RDONLY);
    /*open returns 0 if file is unopened*/
    
    if(file == -1){
        printf("Could not open file\n");
        exit(1);
    }
    playgame(createlist(file));
}

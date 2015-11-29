/*
 * Assignment 1
 * game2.c
 * Authors: Parth Kejriwal, Section 2
 *		  : Ritvik Upadhyaya, Section 2
 * This program reads the integers from an ASCII file and builds a singly linked
 * with them. Then, the program repetitively asks the user to guess an integer
 * that might be in the list. The user enters a guess, and the program searches
 * the linked list to either find the integer or not. It prints a message as to
 * whether it found the integer or not.
 *
 */
/*Defining all the header files required for this program*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>
#include <unistd.h>

/*Defining the node struct*/
typedef struct Node {
    int data;
    struct Node * next;
} Node;

Node * createlist(FILE * file);
Node * listadd(Node *head, int intforlist);

/*
 * This function receives the file descriptor of an already opened file.
 * It then reads one integer at a time from file and calls listadd for each
 * integer, which will add the integer to the list.
 *
 * Parameters: int fd: file descriptor.
 *
 * Return: head of the list once the list has been made.
 *	  : NULL if something goes wrong.
 */

Node * createlist(FILE * fd){
    /* getting the stats of the file to be opened*/
    /* calculating the size of the file*/
    
    Node * head;
    head = NULL;
    char temp[12];
    /*loop for the individual raeding of the integers from the file*/
    
    while (fgets(temp, sizeof(temp), fd)) {
        int temp1 = atoi(temp);
        head = listadd(head, temp1);
    }
    
    /*closing the file*/
    /* returns EOF if there is an error, in which case the program is exitted*/
    if(fclose(fd)==EOF){
        printf("error closing file - aborting\n");
        exit(1);
    }
    
    /*the head node is returned*/
    /* it is null if there was an error during adding into the linked list*/
    return head;
}

/*This function creates a new Node structure, and hooks it into the list
 * at the front (head) of the list to improve efficiency.
 *
 * Parameters:
 * head: pointer to the head of the nodes
 * intforlist: integer to be added to the list.
 *
 * Return:
 *  returns the (new) head of the linked list
 */

Node * listadd(Node *head, int intforlist){
    
    /*adding the node to the head of the list*/
    Node* newHead = malloc(sizeof(Node));
    newHead->data = intforlist;
    newHead->next = head;
    
    /* returning the head of the list*/
    return newHead;
}

/*It plays the game, taking care of printing out prompts,
 * reading in the user input, converting the C string to an integer, and
 * printing the result of the user's guess each time.
 *
 * Parameters:
 * listhead: pointer to the head of the list of integers
 */

void playgame(Node * listhead){
    
    /* value of the user input after parsing*/
    int val;
    char userinput[12];
    /*printing the prompt for the beginning of the game*/
    
    printf("This game has you guess which integers are in the list.\n");
    printf("Enter an integer (followed by the newline)\n");
    printf("or q (followed by the newline) to quit.\n");
    printf("Integer guess: ");
    
    /* getting the user input*/
    if(fgets(userinput,sizeof(userinput), stdin)!=NULL){
        /* if the input doesn't start with the letter q, the program runs*/
        /* quits otherwise */
        
        while(userinput[0] != 'q'){
            /* string to integer*/
            val=atoi(userinput);
            
            /* calling the inlist function to check if the list contains*/
            /* the integer or not*/
            /* printing the required prompt and asking user to enter again*/
            if(inlist(listhead, val) == 1){
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


/*
 * This is the main function of the program. Reads the file name and opens it.
 * Calls the play game function to start the game.
 *
 * Parameters: argc- number of arguments
 *			 : argv[]- the actual user input.
 */

int main(int argc, const char * argv[])
{
    FILE * file;
    const char *inputfile;
    
    if(argc != 2){
        /*We print argv[0] for the program name */
        printf("usage: game2 <file>\n");
        exit(1);
    }
    
    inputfile = argv[1];
    /* Assuming filename is containedin argv[1]*/
    file = fopen(inputfile, "r");
    /*open returns 0 if file is unopened*/
    
    if(file == -1){
        printf("Could not open file\n");
        exit(1);
    }
    playgame(createlist(file));
}
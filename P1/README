#Assignment 1

##CS/ECE 354

#Collaboration Policy

For this assignment, you may work in pairs (2 people). All students (whether working in a pair or not) must individually turn in the assignment. Therefore, 2 copies of the assignment will be turned in for those working as a pair. The grader will choose to grade only one copy of a pair's work, and assign the same score to both students.

If one member of a pair does something unexpected with respect to turning in the assignment (for example: bad copy of the source code, late, or perhaps not turning in portions of the assignment), then both of the pair get the same penalty and the same score.

If working in a pair, the names and sections of both students must appear as comments at the top of all files of the turned in assignment.

In addition, students who work in a pair must turn in an extra file that identifies the pair. Details are given in the section on Handing In the Programs.

#Purpose

The purpose of this assignment is to quickly become good at writing C programs, gaining the experience of working in a non-object oriented language. Arrays, command-line arguments, file I/O, pointers, and structures are used.

#Statement

In this assignment, you will write three C programs. To begin with, you will be given the program generate, which generates a set of integers.

The representation of an integer is a key point of understanding in this assignment. If we have 8-bit two's complement integers, then the representation for the value 12 is (given in binary) 00001100. If we use a C string, then there are three 8-bit ASCII characters to represent the C string "12" (given in binary):

00110001 00110010 00000000
The generate program writes two's complement integer representations to a file. This representation is often called binary output. It also prints out the ASCII version of the integers to stdout (the terminal display), placing each value on its own line.

For this assignment, you will be writing programs that work with two types of files: binary and ASCII. It is important to know which type of input or output you are working with.

#Use the Tools

To familiarize yourself with the generate program and create input files for the assignment, do the following:

Create an a1 folder in the /private/354 directory that you made in assignment 0.
Copy the generate.c file into your a1 directory. The file is located in the directory /p/course/cs354-common/public/html/homeworks.
Compile the program.
Run the program using the following command:
./generate ints-file
The program should have created a file named ints-file, which contains a set of 32-bit two's complement integers. Each integer written to the file was also printed to stdout (display). The output to the display are ASCII characters.
Alter the shell command such that the output sent to stdout is instead captured in a file. This is called a shell redirect.
./generate ints2-file > ascii2-file
To try to see the results, you might try the shell command:
cat ints2-file
Also try running cat with the ascii2-file
The cat program is a standard Unix tool for displaying text (ASCII) files. The goal is to understand why you see something different than what you would expect. Before you move on, study the source code for generate. You should understand why the output of cat is different for ints2-file vs ascii2-file.

Notes:
All sample files that you generated have names that distinguish their contents. Names prefixed with ints have binary contents and names prefixed with ascii have ASCII contents.
You can use these sample files to test your programs. Pay attention to the contents of the file. For example, if my program expects a binary file of integers, I would use ints-file to test it.
To show you some variety in programming style, the generate program uses the assert library function to verify the return values from functions. Doing this likely requires less code to handle program errors, but you also have less control over what happens when the program asserts on an error. Users of the program will likely not understand the displayed error messages without also knowing and understanding your source code. You can accomplish the same task without the extra library inclusion by using if statements to make sure that return values are what they should be.
#Program 1: Averaging Integers

This simple program is intended to give you some programming practice and to expose you to some concepts. Please follow the instructions closely, as alternative implementations will receive score deductions.

#Description:

Write a program called stats.c that reads integers from a binary file and computes the integer average of those integers.

#Specification:

Read integers one at a time from a file. The file name is given as a command line argument.
Place each integer in an array of integers. An array of exactly the right size should be allocated dynamically by using the malloc() function. malloc()'s first parameter is the number of bytes to allocate. You can use fstat() to figure out the size of the file.
After reading and placing the integers into the array, close the file.
Finally, compute the integer average of the values in the array. Print the number of integers read and their calculated average.
#Error Handling:

If the user invokes the stats program incorrectly (for example, without an argument, or with two or more arguments), the program should print an error message and call exit(1)
Be sure to always check the return value of library functions (see notes). For example, if a file cannot be opened, then the program should not read input. If the read fails, then the program should detect the failure and do something relevant. Points will be deducted for forgetting to check return values.
These points will apply to program 2 and 3 as well! Be sure to continue to do error handling when you write programs 2 and 3.
#Notes/Hints:

Using library functions is something you will do a lot when writing programs. Each library function is fully specified in a manual page. To read the manual page to learn about the function, issue the command man. For example, to view the manual page for open, you would issue the command man open. If you are having trouble using man, manual pages are also available online. You will use these library functions to write this program:
open() to open the file
fstat() to get statistics about the file
malloc() to allocate the array of integers
read() to read each individual integer. To view the manual page, use man 2 read on a galapagos machine.
close() to close the file when done
printf() to display results to the screen. To view the manual page, use man 3 printf on a galapagos machine.
When opening a file for reading, it only needs a O_RDONLY flag. See the manual page for read to see how to open, read, and close a file correctly.
#Program 2: Guessing Game

This program is intended to give you practice with building and using linked lists as well as give you experience with structures and using pointers. These skills will come in handy in future projects for this class and in your career as a computer scientist. Follow the instructions closely as alternate implementations will receive score deductions.

#Description:

Write a program called game.c that reads the integers from a binary file and builds a singly linked list with them. The program will then prompt the user for a number and then print a message that tells the user whether or not the number is in the list. The program will keep prompting for a number until the user decides to quit.

#Step 1: Build the Linked List

You will be building a linked list in this first part. Get this part of the program fully tested and completely working before moving on to the next step. For the stats program, you already wrote code that opens a file and reads integers from a file one at a time. Reuse that code! The difference with this program is that we are adding each integer to a singly linked list, not to an array.

Some details about linked lists:

A pointer to the first node in the list identifies where the list is. It is called the head of the list. If the head has the value NULL, then the list is empty.
Since we do not care about the ordering of the list, add each new node (integer) to the front of the list. This is the easiest and most efficient way to write the code. You should be able to explain why this is more efficient than adding a new node to the tail end of the list.
To start, declare a structure called Node to represent each node in the linked list. Then for this part of the program, implement the following functions:

Node * createlist(int fd);
This function receives the file descriptor of an already successfully opened file. It then reads one integer at a time from the file and calls listadd for each integer. This will add each integer to the list. It returns the head of the list once the list has been made. If something goes wrong, or if the list is empty, it returns the value NULL.

Node * listadd(Node *head, int intforlist);
This function creates a new Node structure and hooks it into the list. It is not required, but it is highly recommended to add the new node to the front (head) of the list. This function returns the (new) head of the linked list.

void printlist(Node *head);
This function is not required, though it will be good experience to write and will help you test your program. It should iterate through the linked list and print out each value on its own line.
Before you continue, your program should successfully read integers from a binary file and place them into a singly linked list. Use the functions above to create the linked list and for testing.

#Step 2: Implement the Guessing Game

Now it is time to implement the guessing game. Follow the instructions closely as alternate implementations will receive score deductions.

Note that the game requires reading a user-entered C-string. Use the fgets function to help prevent buffer overflow. Use a static declaration of a single buffer (an array of characters). The file being read from is stdin, which does not need to be opened or closed. An issue you will need to consider is the size of the buffer.

Also notice that an integer must be added to the linked list, but the program reads in a set of characters as a C string. So, the C string must be converted to an integer. Use the atoi function to do the conversion and do not worry about bad input.

For this part of the program, implement and use the following functions:

void playgame(Node * listhead);
This function receives a pointer to the head of the list of integers. It takes care of playing the guessing game. The game must read a line of user input, convert that C string to an integer, and call inlist to search the linked list for the integer that the user entered. It then prints an appropriate result, based on the results of inlist. Finally, the game should continuously prompt for the user's guess until the user enters the character q as the first character in a guess.

int inlist(Node *head, int intvalue);
This function receives a pointer to the head of the list and the integer to search for (intvalue). It iterates through the list, comparing the value in a node to intvalue. If it finds intvalue in the list, the function stops looking at further values and returns the value 1. If the entire list has been searched and intvalue has not been found, the function returns the value 0.
Sample gameplay:

        ./game ints-file
        This game has you guess which integers are in the list.
        Enter an integer (followed by the newline)
        or q (followed by the newline) to quit.
        Integer guess: 25
        25 is not in the list.
        Integer guess: 0
        0 is in the list.
        Integer guess: abq
        0 is in the list.
        Integer guess: -12
        -12 is not in the list.
        Integer guess: -1
        -1 is in the list.
        Integer guess: q
        Quitting.
#Program 3: A Modified Game

This program is a slightly modified version of the game.c program. Call this program game2.c. The only difference between the two programs is the file format of the command line argument that specifies the input file. In other words, to get integers for the linked list, game.c read integers from a binary file. However, game2.c will build the linked list using integers that are read from a file of ASCII characters (commonly called a text file). The program will still read user input from stdin when playing the game.

You created a file of ASCII characters (ascii2-file) when you redirected the output of generate. That file is what is read by this program. The file format has each integer on its own line of the file.

Start by copying game.c to game2.c. The amount of code that you change in game2.c will be rather small. The user playing the game will see no difference, other than that the command line argument that specifies the input file will be different.

Differences:

game2.c must use fopen, instead of open. Read the man page to understand the parameters and return value. This file only needs to be read, so the second parameter will be the C string literal "r".
game2.c must use fclose, instead of close.
game2.c must use fgets, instead of read. Note that you have already used this function to read the user input in game.c. Again for this program, you will need to make a quality choice for the size of the buffer. Also note that the value that gets added to the list is still an integer, so after reading a C string, use atoi to convert the C string to an integer.
#Requirements

Your program must follow style guidelines as given in Style Guidelines.
Include a comment at the top of each source code file with your name and section.
See Guidelines for Programs to see an indication of point allocation for program grading.

Your programs are to operate as any examples given above show.
Use a Linux machine for this assignment! A penalty will be imposed for any program that was obviously edited on a Windows machine and transferred to the Unix machines for turning in. Part of this assignment is learning about and becoming proficient at using some Unix tools.
We will compile each of your programs with
  gcc -Wall -m32 -O -std=gnu99
on a galapagos Linux machine. So, your programs must compile there, and without warnings or errors.
The stats program must use an array to hold the integers. The game programs must use a singly linked list of structures to hold the integers.
Remember to do error handling in all three programs. See the instructions for program 1 for more details.
#Handing in the Assignment

Copy stats.c, game.c, game2.c into your handin directory: /p/course/cs354-common/public/fall15.handin/<yourloginID>/p1/

<yourloginID> is the username of your CS account.

If you are working as part of a pair, you must turn in an extra file. This file will contain the names and sections of both students in the pair. As an example, if Kevin worked with Urmish on this assignment, the contents of the extra file for both Kevin and Urmish would be

Kevin Zhang     section 1
Urmish Thakker  section 2
The name of this file is specialized to help the 354 automated grading tools identify who worked together. This file name is composed of the CS logins of the partners separated by a period. The file name is of the form <login1>.<login2>. Kevin's login is kzhang, and Urmish's login is uthakker. The file name that both use will be kzhang.uthakker. Please have both partners use the same file name. It does not matter which partner's name is first within this file name.

#About Copying Code and Academic Misconduct

Don't cheat. Read this link carefully.

Do not post your assignment solutions (or drafts) on any publicly accessible web sites. This specifically includes GitHub. It is academic misconduct to post your solution.

For almost any C program that does something useful, someone has already written this program and further, has posted it for others to use. These programs do not do much that is useful, and are not likely posted anywhere. Still, it is academic misconduct for you to copy or use some or all of a program that has been written by someone else.

The penalty for academic misconduct on this assignment (and all CS/ECE 354 assignments) will be a failing grade in the course. This penalty is significantly more harsh than if you simply do not do the assignment. You will gain much more by doing the assignment than by copying, possibly modifying, and turning in someone else's effort.

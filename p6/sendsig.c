////////////////////////////////////////////////////////////////////////////////
// Main File:        sendsig.c
// This File:        sendsig.c
// Other Files:      n/a
// Semester:         CS 354 Fall 2020
//
// Author:           Ishaan Backliwal
// Email:            backliwal@wisc.edu
// CS Login:         ishaan
//
/////////////////////////// OTHER SOURCES OF HELP //////////////////////////////
//                   Fully acknowledge and credit all sources of help,
//                   other than Instructors and TAs.
//
// Persons:          Identify persons by name, relationship to you, and email.
//                   Describe in detail the the ideas and help they provided.
//
// Online sources:   Avoid web searches to solve your problems, but if you do
//                   search, be sure to include Web URLs and description of
//                   of any information you find.
////////////////////////////////////////////////////////////////////////////////

/**
 * sendsig.c:
 * Prorgam to send two types of signals to specified process...
 *     1. SIGUSR1
 *     2. SIGINT
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

/**
 * send_SIGUSR1:
 * Sends SIGUSR1 signal to specified process
 * and handles errors
 */
void send_SIGUSR1(int pid){
    if(kill(pid, SIGUSR1) != 0){
        printf("ERROR: Not able to send SIGUSR1");
	exit(1);
    }
}

/**
 * send_SIGINT:
 * Sends SIGINT signal to specified process
 * and handles errors
 */
void send_SIGINT(int pid){
    if(kill(pid, SIGINT) != 0){
        printf("ERROR: Not able to send SIGINT");
	exit(1);
    }
}

/**
 * isNum:
 * Helper function to determine whether every character
 * of the given string is an integer or not
 */
int isNum(char* string){
    int count = 0; // position in string
    char character; // current e character in string
    
    // check if each character in the string is a digit 
    do{
        character = string[count];
	// return false if any char in string isn't a num
	if(!isdigit(character)){
	    return 0;
	}
	count++;
    } while(string[count + 1] != '\0');

    // if reached here, every char in string was a num
    return 1;
}

/**
 * main:
 * Makes sure user input is valid and then uses it to
 * send the requested signal to the specified process
 */
int main(int argc, char *argv[]){
    // check input arguements
    if(argc != 3){
        printf("Usage: <signal type> <pid>\n");
	exit(1);
    }

    // extract sig type and pid
    char* sig_type = argv[1];
    char* pid_RAW = argv[2];

    // check signal type
    if(sig_type[1] != 'i' && sig_type[1] != 'u'){
        printf("Usage: <signal type> <pid>\n");
        exit(1);
    }

    // check pid
    if(!isNum(pid_RAW)){
        printf("Usage: <signal type> <pid>\n");
        exit(1);
    }

    // convert pid to int
    int pid = atoi(pid_RAW);

    // run appropriate method to send requested signal
    if(sig_type[1] == 'i'){
        send_SIGINT(pid);
    }
    if(sig_type[1] == 'u'){
        send_SIGUSR1(pid);
    }
}


// end sendsig.c

////////////////////////////////////////////////////////////////////////////////
// Main File:        division.c
// This File:        division.c
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
 * division.c:
 * A program that allows you to calulate integer quotient
 * of any two integers and handles division by 0 and ^C
 * using signals
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

int successes = 0; // global var indicating num of successful divisions

/**
 * handle_SIGFPE:
 * signal handler function to catch when division by 0
 * is attempted and exit program after displaying final
 * statistics
 */
void handle_SIGFPE(){
    printf("Error: a division by 0 operation was attempted.\n");
    printf("Total number of operations completed successfully: %i\n", successes);
    printf("The program will be terminated.\n");
    exit(0);
}

/**
 * handle_SIGINT:
 * signal handler function to catch when the
 * keyboard interrupt signal (^C) is entered
 * and exit program after displaying final statistics
 */
void handle_SIGINT(){
    printf("\nTotal number of operations completed successfully: %i\n", successes);
    printf("The program will be terminated.\n");
    exit(0);
}

/**
 * main:
 * registers both signal handlers, runs an infinite loop
 * that asks user for two integers and displays quotient
 * with remainder, and calls signal handler functions when
 * needed
 */
int main(){
    
    // register sig handler for SIGFPE
    struct sigaction sigfpe;
    memset(&sigfpe, 0, sizeof(sigfpe));
    sigfpe.sa_handler = &handle_SIGFPE;
    if(sigaction(SIGFPE, &sigfpe, NULL) != 0){
        printf("ERROR binding SIGFPE handler\n");
        exit(1);
    }

    // register sig handler for SIGINT
    struct sigaction sigint;
    memset(&sigint, 0, sizeof(sigint));
    sigint.sa_handler = &handle_SIGINT;
    if(sigaction(SIGINT, &sigint, NULL) != 0){
        printf("ERROR binding SIGINT handler\n");
        exit(1);
    }
	
    // infinite loop
    while(1){
        // prompt for and get user input
        int first_int;
        int second_int;
        char buffer[100];
        // get first int
        printf("Enter first integer: ");
        fgets(buffer, 100, stdin);
        first_int = atoi(buffer);
        // get second int
        printf("Enter second integer: ");
        fgets(buffer, 100, stdin);
        second_int = atoi(buffer);

        // calculate quotient and remainder
        // of first_int / second_int
        int quotient = first_int / second_int;
        int remainder = first_int % second_int;

        // print out results
        printf("%i / %i is %i with a remainder of %i\n", first_int, second_int, quotient, remainder);
        
	// increment number of successful divisions
	successes++;
    }
    
}


// end division.c

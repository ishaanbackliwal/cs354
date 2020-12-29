////////////////////////////////////////////////////////////////////////////////
// Main File:        mySigHandler.c
// This File:        mySigHandler.c
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
 * mySigHandler.c:
 * Program that sets off an alarm every 3 seconds
 * in an infinite loop and handles three signals...
 *     1. SIGALRM
 *     2. SIGUSR1
 *     3. SIGINT
 */

#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <sys/types.h>

int seconds = 3; // alarm delay in seconds
int count_SIGUSR1 = 0; // number of times SIGUSR1 is caught and dealt with

/**
 * handle_SIGALRM:
 * signal handler function for SIGARLM that 
 * prints PID and current time every time the 
 * alarm is set off
 */
void handle_SIGALRM(){
    // get pid
    pid_t pid = getpid();

    // get and check time
    time_t curr_time;
    if(time(&curr_time) == -1){
        printf("ERROR time() failed");
	exit(1);
    }
    if(ctime(&curr_time) == NULL){
        printf("ERROR ctime() failed");
        exit(1);
    }

    // print pid and time
    printf("PID: %i CURRENT TIME: %s", pid, ctime(&curr_time));

    // re-arm the alarm
    alarm(seconds);
}

/**
 * handle_SIGUSR1:
 * signal handler function for SIGUSR1 that
 * counts number of times SIGUSR1 is caught
 */
void handle_SIGUSR1(){
    // increment SIGUSR1 counter 
    count_SIGUSR1++;

    // inform user of signal handle
    printf("SIGUSR1 handled and counted!\n");
}

/**
 * handle_SIGINT:
 * signal handler function to catch when the
 * keyboard interrupt signal (^C) is entered
 * and exit program after displaying final statistics
 */
void handle_SIGINT(){
    printf("\nSIGINT handled.\nSIGUSR1 was handled %i times. Exiting now.\n", count_SIGUSR1);
    exit(0);
}

/**
 * main:
 * sets an alarm, registers signal handlers, and runs
 * an infinite loop
 */
int main(){
    // user instructions
    printf("Pid and time print every 3 seconds.\n");
    printf("Enter Ctrl-C to end the program.\n");

    // set alarm
    alarm(seconds);
    
    // register sig handler for SIGALRM
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = &handle_SIGALRM;
    if(sigaction(SIGALRM, &sa, NULL) != 0){
        printf("ERROR binding SIGALRM handler\n");
	exit(1);
    }
    
    // register sig handler for SIGUSR1
    struct sigaction sigusr1;
    memset(&sigusr1, 0, sizeof(sigusr1));
    sigusr1.sa_handler = &handle_SIGUSR1;
    if(sigaction(SIGUSR1, &sigusr1, NULL) != 0){
        printf("ERROR binding SIGUSR1 handler\n");
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
    }
}


// end mySigHandler.c

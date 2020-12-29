///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2020 Jim Skrentny
// Posting or sharing this file is prohibited, including any changes/additions.
// Used by permission for CS 354 Fall 2020, Deb Deppeler
//
////////////////////////////////////////////////////////////////////////////////
// Main File:        n_in_a_row.c
// This File:        n_in_a_row.c
// Other Files:      N/A
// Semester:         CS 354 Fall 2020
//
// Author:           Ishaan Backliwal
// Email:            backliwal@wisc.edu)
// CS Login:         ishaan)
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
   
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
     
char *DELIM = ",";  // commas ',' are a common delimiter character for data strings
     
/* COMPLETED:       
 * Retrieves from the first line of the input file,
 * the size of the board (number of rows and columns).
 * 
 * fp: file pointer for input file
 * size: pointer to size
 */
void get_dimensions(FILE *fp, int *size) {      
    char *line = NULL;
    size_t len = 0;
    if (getline(&line, &len, fp) == -1) {
        printf("Error in reading the file.\n");
        exit(1);
    }

    char *token = NULL;
    token = strtok(line, DELIM);
    *size = atoi(token);
}       
 
   
  
/* 
 * Returns 1 if and only if the board is in a valid state.
 * Otherwise returns 0.
 * 
 * board: heap allocated 2D board
 * size: number of rows and columns
 */
int n_in_a_row(int **board, int size) {
    // if size is not odd, board is invalid
    if(size % 2 == 0){
        return 0;
    }	

    // declare variables
    int x_count = 0; // tracks number of x's
    int o_count = 0; // tracks number of o's
    int x_row_wins = 0; // tracks number of x row wins
    int o_row_wins = 0; // tracks number of o row wins
    int x_col_wins = 0; // tracks number of x column wins
    int o_col_wins = 0; // tracks number of o column wins
    int x_seq_count = 0; // tracks x values in a sequence
    int o_seq_count = 0; // tracks o values in a sequence
    int x_diag_wins = 0; // track diagonal x wins
    int o_diag_wins = 0; // tracks diagonal o wins
    
    // check rows
    for(int i = 0; i < size; i++){
        x_seq_count = 0;
        o_seq_count = 0;
        for(int j = 0; j < size; j++){
            if((*(*(board+i)+j)) == 1){
                x_seq_count++;
            }
            else if((*(*(board+i)+j)) == 2){
                o_seq_count++;
            }
        }
        if(x_seq_count == size){
            x_row_wins++;
        }
        else if (o_seq_count == size){
            o_row_wins++;
        }
    }

    // check columns
    for(int i = 0; i < size; i++){
        x_seq_count = 0;
        o_seq_count = 0;
        for(int j = 0; j < size; j++){
            if((*(*(board+j)+i)) == 1){
                x_seq_count++;
		x_count++;
            }
            else if((*(*(board+j)+i)) == 2){
                o_seq_count++;
		o_count++;
            }
        }
        if(x_seq_count == size){
            x_col_wins++;
        }
        else if (o_seq_count == size){
            o_col_wins++;
        }
    }   
    
    // check diagonal: left-right
    x_seq_count = 0;
    o_seq_count = 0;
    for(int i = 0; i < size; i++){
        if((*(*(board+i)+i)) == 1){
            x_seq_count++;
        }
        else if((*(*board+i)+i) == 2){
            o_seq_count++;
        }
    }
    if(x_seq_count == size){
        x_diag_wins++;	
    }
    else if(o_seq_count == size){
	o_diag_wins++;
    }
    
    // check diagonal: right-left
    x_seq_count = 0;
    o_seq_count = 0;
    for(int i = 0; i < size; i++){
        if((*(*(board+i)+(size-i))) == 1){
            x_seq_count++;
        }
        else if((*(*board+i)+(size-i)) == 2){
            o_seq_count++;
        }
    }
    if(x_seq_count == size){
	x_diag_wins++;
    }
    else if(o_seq_count == size){
	o_diag_wins++;
    }   
    
    // validate wins
    // valid if two diagonals of the same type are present
    if(x_diag_wins == 2 || o_diag_wins == 2){
	// if both x and o have two diagonal wins, board is invalid
        if(x_diag_wins == 2 && o_diag_wins != 0){
            return 0;
        }
	if(o_diag_wins == 2 && x_diag_wins != 0){
            return 0;
        }
    }
    // invalid if two parallel columns or rows are wining
    int total_col_wins = x_col_wins + o_col_wins;
    int total_row_wins = x_row_wins + o_row_wins;
    if(total_col_wins > 1 || total_row_wins > 1){
        return 0;
    }

    // validate number of x's and o's
    // x has to equal o or be one greater
    int difference = x_count - o_count;
    if(difference < 0 || difference > 1){
        return 0;
    }
   
    // if program has run up to here, board is valid
    return 1;
}    
  
 
   
/* 
 * This program prints Valid if the input file contains
 * a game board with either 1 or no winners; and where
 * there is at most 1 more X than O.
 * 
 * argc: CLA count
 * argv: CLA value
 */
int main(int argc, char *argv[]) {              
     
    //Check if number of command-line arguments is correct.
    if(argc != 2){
        printf("Usage: ./n_in_a_row <input_filename>\n");
        exit(1);
    }

    //Open the file and check if it opened successfully.
    FILE *fp = fopen(*(argv + 1), "r");
    if (fp == NULL) {
        printf("Can't open file for reading.\n");
        exit(1);
    }

    //Declare local variables.
    int size;
    int **board;
    int validity;

    //Call get_dimensions to retrieve the board size.
    get_dimensions(fp, &size);

    //Dynamically allocate a 2D array of dimensions retrieved above.
    board = malloc(sizeof(int*) * size);
    for(int i = 0; i < size; i++){
        *(board+i) = malloc(sizeof(int) * size);
    }

    //Read the file line by line.
    //Tokenize each line wrt the delimiter character to store the values in your 2D array.
    char *line = NULL;
    size_t len = 0;
    char *token = NULL;
    for (int i = 0; i < size; i++) {

        if (getline(&line, &len, fp) == -1) {
            printf("Error while reading the file.\n");
            exit(1);
        }

        token = strtok(line, DELIM);
        for (int j = 0; j < size; j++) {
            //Complete the line of code below
            //to initialize your 2D array.
            *(*(board+i)+j) = atoi(token);
            token = strtok(NULL, DELIM);
        }
    }

    //Call the function n_in_a_row and print the appropriate
    //output depending on the function's return value.
    validity = n_in_a_row(board, size);
    if(validity == 1){
        printf("valid\n");
    }
    else if(validity == 0){
        printf("invalid\n");
    }

    //Free all dynamically allocated memory.
    for(int i = 0; i < size; i++){
        free(*(board+i));
	*(board+i) = NULL;
    }
    free(board);
    board = NULL;

    //Close the file.
    if (fclose(fp) != 0) {
        printf("Error while closing the file.\n");
        exit(1);
    } 
     
    return 0;       
}       




// FIN

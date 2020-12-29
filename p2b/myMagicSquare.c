///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2020 Jim Skrentny
// Posting or sharing this file is prohibited, including any changes/additions.
// Used by permission, CS 354 Fall 2020, Deb Deppeler
//
////////////////////////////////////////////////////////////////////////////////
// Main File:        myMagicSquare.c
// This File:        myMagicSquare.c
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
   
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure that represents a magic square
typedef struct {
    int size;      // dimension of the square
    int **magic_square; // pointer to heap allocated magic square
} MagicSquare;

/* 
 * Prompts the user for the magic square's size, reads it,
 * checks if it's an odd number >= 3 (if not display the required
 * error message and exit), and returns the valid number.
 */
int getSize() {
    int matrix_size = 0;
    printf("Enter magic square's size (odd integer >=3): ");	
    scanf("%i", &matrix_size);
    if(matrix_size < 3){
        printf("Size must be >= 3.\n");
        exit(1);
    }
    else if(matrix_size % 2 == 0){
        printf("Size must be odd.\n");
	exit(1);
    }
    else{
        return matrix_size;
    }
} 
   
/*
 * Makes a magic square of size n using the alternate 
 * Siamese magic square algorithm from assignment and 
 * returns a pointer to the completed MagicSquare struct.
 *
 * n the number of rows and columns
 */
MagicSquare *generateMagicSquare(int n) {
    // declare and allocate heap memory to matrix
    MagicSquare matrix;
    matrix.size = n;
    matrix.magic_square = malloc(sizeof(int*) * matrix.size);
    for(int i = 0; i < matrix.size; i++){
        *((matrix.magic_square)+i) = malloc(sizeof(int) * matrix.size);
    }

    // fill each position in matrix with 0
    for(int i = 0; i < matrix.size; i++){
        for( int j = 0; j < matrix.size; j++){
            *(*(matrix.magic_square + i) + j) = 0;
        }
    }

    // fill matrix with values
    // fill ( (n/2), (n-1) ) with the value 1
    int row = matrix.size / 2;
    int col = matrix.size - 1;
    *(*(matrix.magic_square + row) + col) = 1;
    // fill rest of the positions
    // if current position is (s,t) then
    // move to ( ((s+1)%n), ((t+1)%n) ) next
    // if that position is filled
    // move to ( s, ((t-1)%n) ) and continue
    int count = (matrix.size * matrix.size) + 1;
    for(int i = 2; i < count; i++){
        int tempr = (row + 1) % matrix.size; // temporary row peeker
        int tempc = (col + 1) % matrix.size; // temporary column peeker
        int value = *(*(matrix.magic_square + tempr) + tempc);
        // if position is empty, fill with next number
	if(value == 0){
	    row = tempr;
	    col = tempc;
            *(*(matrix.magic_square + row) + col) = i;
        }
	// else, move back one column and continue process
        else{
            col = (col - 1) % matrix.size;
	    *(*(matrix.magic_square + row) + col) = i;
        }
    }

    // pointer to matrix   
    MagicSquare *ptr = malloc(sizeof(MagicSquare));
    ptr->size = n;
    ptr->magic_square = matrix.magic_square;

    return ptr;    
} 

/*  
 * Opens a new file (or overwrites the existing file)
 * and writes the square in the specified format.
 *
 * magic_square the magic square to write to a file
 * filename the name of the output file
 */
void fileOutputMagicSquare(MagicSquare *magic_square, char *filename) {
    // open output file
    FILE *ofp = fopen(filename, "w");
    if(ofp == NULL){
        printf("%s", "ERROR: Cannot open output file");
        exit(1);
    }

    // write the matrix to the output file
    int num = 0;
    int matrix_size = magic_square->size;
    fprintf(ofp, "%d\n", matrix_size); 
    for(int i = 0; i < matrix_size; i++){
	for(int j = 0; j < matrix_size - 1; j++){
	    num = *(*(magic_square->magic_square + i) + j);
	    fprintf(ofp, "%d,", num);
	}
	// write last value of row without a succeeding comma
	num = *(*(magic_square->magic_square + i) + (matrix_size-1));
	fprintf(ofp, "%d\n", num);
    }

    // close output file
    fclose(ofp);    
}

/*
 * Generates a magic square of the user specified size and
 * output the quare to the output filename
 */
int main(int argc, char *argv[]) {
    // Check input arguments to get output filename
    if(argc != 2){
        printf("Usage: ./myMagicSquare <input_filename>\n");
        exit(1);
    }
    char filename[50];
    strcpy (filename, argv[1]);

    // Get magic square's size from user
    int square_size = getSize();

    // Generate the magic square
    MagicSquare *ptr = generateMagicSquare(square_size);

    // Output the magic square
    fileOutputMagicSquare(ptr, filename);
    
    // Free memory
    for(int i = square_size-1; i <= 0; i--){
        free(*(ptr->magic_square + i));
	*(ptr->magic_square + i) = NULL;
    }
    free(ptr->magic_square);
    ptr->magic_square = NULL;

    return 0;
} 
                                                         
//				myMagicSquare.c      

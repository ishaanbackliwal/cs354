///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2020 Jim Skrentny
// Posting or sharing this file is prohibited, including any changes/additions.
// Used by permission, CS 354 Fall 2020, Deb Deppeler
//
////////////////////////////////////////////////////////////////////////////////
// Main File:        cache2Dclash.c
// This File:        cache2Dclash.c
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

int arr2D[128][8];

int main(){
    for(int iteration = 0; iteration < 100; iteration++){
        for(int row = 0; row < 128; row += 64){
	    for(int col = 0; col < 8; col++){
	        arr2D[row][col] = iteration + row + col;
	    }
	}
    }

    return 0;
}

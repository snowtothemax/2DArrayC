///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2020 Jim Skrentny
// Posting or sharing this file is prohibited, including any changes/additions.
// Used by permission for CS 354 Fall 2020, Deb Deppeler
//
////////////////////////////////////////////////////////////////////////////////
// Main File:        n_in_a_row.c
// This File:        n_in_a_row.c
// Other Files:      (name of all other files if any)
// Semester:         CS 354 Fall 2020
//
// Author:           Max Johnson
// Email:            mkjohnson9@wisc.edu
// CS Login:         maxwellj
//
/////////////////////////// OTHER SOURCES OF HELP //////////////////////////////
//                   Fully acknowledge and credit all sources of help,
//                   other than Instructors and TAs.
//
// Persons:          NONE
//
// Online sources:   NONE
//
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *DELIM = ","; // commas ',' are a common delimiter character for data strings

/* COMPLETED:       
 * Retrieves from the first line of the input file,
 * the size of the board (number of rows and columns).
 * 
 * fp: file pointer for input file
 * size: pointer to size
 */
void get_dimensions(FILE *fp, int *size)
{
	char *line = NULL;
	size_t len = 0;
	if (getline(&line, &len, fp) == -1)
	{
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
int n_in_a_row(int **board, int size)
{
	//checks if the board is an even number, returns 0 if true
	if ((size % 2 == 0) || size < 3)
	{
		return 0;
	}

	//local variables
	int countX = 0; // amount of X's
	int countO = 0; // amount of O's

	//Traverse 2D array for the amount of X's and O's
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (*(*(board + i) + j) > 2 || *(*(board + i) + j) < 0)
			{
				printf("ERROR: Illegal number found on the board. You can only enter a 0, 1 or 2.\n");
				exit(1);
			}
			if (*(*(board + i) + j) == 1)
			{
				countX++;
			}
			if (*(*(board + i) + j) == 2)
			{
				countO++;
			}
		}
	}

	//Check and compare counts of X's and O's to make sure
	//board is valid
	if (countX == countO || (countX - 1) == countO)
	{
		//There are a valid count of X's and O's,
		//continue:

		//Variables to keep track of horizontal
		//winning lines for x's and o's
		int xWinsHorz = 0;
		int oWinsHorz = 0;

		//Traverse 2D array row by row and keeps track of
		//winning lines
		for (int l = 0; l < size; l++)
		{
			//Vars that keep track of columns for both
			//X's and O's
			int incX = 0;
			int incO = 0;

			//Check for X having a winning line
			while (incX < size && (*(*(board + l) + incX) == 1))
			{
				incX++;
			}
			if (incX == size)
			{
				xWinsHorz++;
			}

			//Check for O having a winning line now
			while (incX < size && (*(*(board + l) + incO) == 2))
			{
				incO++;
			}
			if (incO == size)
			{
				oWinsHorz++;
			}
		}

		//If there are parallel wins, invalid because there is no cross section
		if (xWinsHorz > 1 || oWinsHorz > 1)
		{
			return 0;
		}

		// Checks if both X and O have winning lines which is invalid
		if (xWinsHorz > 0 && oWinsHorz > 0)
		{
			return 0;
		}

		//Variables to keep track of vertical winning lines
		int xWinsVert = 0;
		int oWinsVert = 0;

		//Check for vertical wins
		for (int k = 0; k < size; k++)
		{
			//vars that keep track of which row for x and o
			int incX = 0;
			int incO = 0;

			//check for winning column for x
			while (incX < size && (*(*(board + incX) + k) == 1))
			{
				incX++;
			}
			if (incX == size)
			{
				xWinsVert++;
			}
			//check for O winning column
			while (incO < size && (*(*(board + incO) + k) == 2))
			{
				incO++;
			}
			if (incO == size)
			{
				oWinsVert++;
			}
		}

		//Checks if there are more than one winning vertical lines for x and o
		//which is invalid
		if (xWinsVert > 1 || oWinsVert > 1)
		{
			return 0;
		}

		//Checks if both X and O have a vertical winning line which
		//is invalid
		if (xWinsVert > 0 && oWinsVert > 0)
		{
			return 0;
		}

		//now we check for diagonal wins
		int xWinsDiag = 0;
		int oWinsDiag = 0;

		//trackers for how many x's or o's are present in the diagonal line (left to right first)
		int xDiagTrack = 0;
		int oDiagTrack = 0;

		//For loop that goes in a diagonal line starting at m[0][0] and counts number
		//of X's and O's. If the number of X's or O's equals the size after the last
		//increment, then there is a winning diagonal line for an X or O.
		for (int p = 0; p < size; p++)
		{
			//Check for X
			if (*(*(board + p) + p) == 1)
			{
				xDiagTrack++;
			}
			//Check for O
			if (*(*(board + p) + p) == 2)
			{
				oDiagTrack++;
			}
		}

		//If the number of X's in a line is equal to the size, winning line
		if (xDiagTrack == size)
		{
			xWinsDiag++;
		}
		//if the number of O's in a line is equal to the size, winning line
		if (oDiagTrack == size)
		{
			oWinsDiag++;
		}

		//Reset the trackers to 0 to check for a diagonal win in the other direction
		xDiagTrack = 0;
		oDiagTrack = 0;

		//For loop that goes in a diagonal line starting at m[size-1][0] and counts
		//the number of X's and O's in that diagonal line, the last elementing being located at
		//m[0][size-1].
		for (int f = 0; f < size; f++)
		{
			//Check if the element equals X
			if (*(*(board + size - 1 - f) + f) == 1)
			{
				xDiagTrack++;
			}
			//Check if the element equals O
			if (*(*(board + size - 1 - f) + f) == 2)
			{
				oDiagTrack++;
			}
		}

		//checks if there is a winning line for X
		if (xDiagTrack == size)
		{
			xWinsDiag++;
		}
		//checks if there is a winning line for O
		if (oDiagTrack == size)
		{
			oWinsDiag++;
		}

		//check if both x and O have a diagonal win
		//this is invalid and impossible (maybe).
		if (xWinsDiag > 0 && oWinsDiag > 0)
		{
			return 0;
		}

		//Now we use our win data to determine the validity of the board

		//first add the total amount of wins of the X's and O's
		int totXWin = xWinsDiag + xWinsVert + xWinsHorz;
		int totOWin = oWinsDiag + oWinsVert + oWinsHorz;

		//now since we already checked for parallell wins, we just check to make sure there are only less than 2 winning lines for the winner
		if ((totXWin <= 2 && totOWin == 0) || (totOWin <= 2 && totXWin == 0))
		{
			return 1;
		}
	}

	return 0;
}

/* PARTIALLY COMPLETED:
 * This program prints Valid if the input file contains
 * a game board with either 1 or no winners; and where
 * there is at most 1 more X than O.
 * 
 * argc: CLA count
 * argv: CLA value
 */
int main(int argc, char *argv[])
{

	//Checks if there are 2 and only 2 command line arguments.
	if (argc != 2)
	{
		printf("Invalid number of command line arguments.\n");
		exit(1);
	}

	//Open the file and check if it opened successfully.
	FILE *fp = fopen(*(argv + 1), "r");
	if (fp == NULL)
	{
		printf("Can't open file for reading.\n");
		exit(1);
	}

	//Declare local variables.
	int size;					   //size variable
	int *sizePtr;				   // Pointer to a size variable
	sizePtr = malloc(sizeof(int)); // allocate mem for int
	if (sizePtr == NULL)
	{
		printf("ERROR: Mem for sizePtr could not be allocated.\n");
		exit(1);
	}
	int **m; //2D array on the heap to be allocated

	//Call get_dimensions to retrieve the board size.
	get_dimensions(fp, sizePtr);
	size = *sizePtr; //set the size local variable to the sizePtr value.

	//Dynamically allocate a 2D array of dimensions retrieved above.
	m = malloc(sizeof(int *) * size);
	if (m == NULL)
	{
		printf("ERROR: Memory for the 2D Array m could not be allocated. \n");
		exit(1);
	}

	//Allocate each row in the dynamic 2D array of characters.
	for (int i = 0; i < size; i++)
	{
		*(m + i) = malloc(sizeof(int) * size);
		if (*(m + i) == NULL)
		{
			printf("ERROR: rows of 2D array could not have memory allocated. \n");
			exit(1);
		}
	}

	//Read the file line by line.
	//Tokenize each line wrt the delimiter character to store the values in your 2D array.
	char *line = NULL;
	size_t len = 0;
	char *token = NULL;
	for (int i = 0; i < size; i++)
	{

		if (getline(&line, &len, fp) == -1)
		{
			printf("Error while reading the file.\n");
			exit(1);
		}

		token = strtok(line, DELIM);
		for (int j = 0; j < size; j++)
		{
			//Initialize the 2D array.
			*(*(m + i) + j) = atoi(token);
			token = strtok(NULL, DELIM);
		}
	}

	//Call the function n_in_a_row and print the appropriate
	//output depending on the function's return value
	int response = n_in_a_row(m, size);

	if (response == 1)
	{
		printf("valid\n");
	}
	else
	{
		printf("invalid\n");
	}

	// Free all dynamically allocated memory.
	for (int k = 0; k < size; k++)
	{
		free(*(m + k));
		*(m + k) = NULL;
	}
	free(m);
	m = NULL;
	free(sizePtr);
	sizePtr = NULL;

	//Close the file.
	if (fclose(fp) != 0)
	{
		printf("Error while closing the file.\n");
		exit(1);
	}

	return 0;
}

// FIN

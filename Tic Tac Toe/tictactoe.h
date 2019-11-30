#ifndef TIC_TAC_TOE_MAIN_H
#define TIC_TAC_TOE_MAIN_H
/* ^^ these are the include guards */

/* Prototypes for the functions */

// Verifyes if someone won and return an array[3]
//if someone won, returns {1, W, C}, being:
//	W the win type:
//		0, if horizontal
//		1, if vertical
//		2, if diagonal 1 (\)
//		3, if diagonal 2 (/)
//	C the coordinate, being:
//		row for horizontal win
//		column for the rest
int* winVerifyer(int grid[3][3]);

// Verifyes if exists 3 or less free cells
// and return the coordinate of these cells
extern int** freeCells(int grid[3][3]);

// gets the tied grid to pass it to main
int** gridTiedReturner(int gridCopy[3][3], int mod);

// Verifyes if the game will tie in 3, 2 or 1 plays
// if it ties, returns 1
// if not, returns 0
int tieVerifyer(int grid[3][3], int player, int insertionPreference);

// Converts the position to coordinates
int* convertToCoordinate(int position);

// converts the grid coordinates to supergrid coordinates
int* coordinatesToSupergrid(int coordinates[2]);

// Modifies the supergrid, putting X or O on the place they are
void superGridModifier(char supergrid[31][51], int grid[3][3]);

// prints the supergrid
void gridPrinter(int grid[3][3], int mod);

// prints the thanks
void thanks();

#endif
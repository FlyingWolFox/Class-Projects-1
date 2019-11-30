#define _CRT_SECURE_NO_WARNINGS
#include "tictactoe.h"
#include "ai.h"
#include "minimax.h"
#include "ansi_escapes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern void setupConsole(void);
extern void restoreConsoleMode(void);
extern void restoreConsole(void);

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
int* winVerifyer(int grid[3][3])
{
	static int returnValue[3];
	int i, j;

	// looks for X horizontal wins
	for (i = 0; i < 3; i++)
	{
		if (grid[i][0] == 1)
		{
			if (grid[i][1] == 1 && grid[i][2] == 1)
			{
				returnValue[0] = 1;
				returnValue[1] = 0;
				returnValue[2] = i;
				return returnValue;
			}
		}
	}

	// looks for X vertical wins
	for (j = 0; j < 3; j++)
	{
		if (grid[0][j] == 1)
		{
			if (grid[1][j] == 1 && grid[2][j] == 1)
			{
				returnValue[0] = 1;
				returnValue[1] = 1;
				returnValue[2] = j;
				return returnValue;
			}
		}
	}

	// look for X \ diagonal wins
	i = 0;
	j = 0;
	if (grid[i][j] == 1 && grid[i + 1][j + 1] == 1 && grid[i + 2][j + 2] == 1)
	{
		returnValue[0] = 1;
		returnValue[1] = 2;
		returnValue[2] = j;
		return returnValue;
	}

	// look for X / diagonal wins
	i = 0;
	j = 2;
	if (grid[i][j] == 1 && grid[i + 1][j - 1] == 1 && grid[i + 2][j - 2] == 1)
	{
		returnValue[0] = 1;
		returnValue[1] = 3;
		returnValue[2] = j;
		return returnValue;
	}

	//looks for O horizontal wins
	for (i = 0; i < 3; i++)
	{
		if (grid[i][0] == -1)
		{
			if (grid[i][1] == -1 && grid[i][2] == -1)
			{
				returnValue[0] = 1;
				returnValue[1] = 0;
				returnValue[2] = i;
				return returnValue;
			}
		}
	}


	// looks for O vertical wins
	for (j = 0; j < 3; j++)
	{
		if (grid[0][j] == -1)
		{
			if (grid[1][j] == -1 && grid[2][j] == -1)
			{
				returnValue[0] = 1;
				returnValue[1] = 1;
				returnValue[2] = j;
				return returnValue;
			}
		}
	}

	// look for O \ diagonal wins
	i = 0;
	j = 0;
	if (grid[i][j] == -1 && grid[i + 1][j + 1] == -1 && grid[i + 2][j + 2] == -1)
	{
		returnValue[0] = 1;
		returnValue[1] = 2;
		returnValue[2] = j;
		return returnValue;
	}
	
	// look for O / diagonal wins
	i = 0;
	j = 2;
	if (grid[i][j] == -1 && grid[i + 1][j - 1] == -1 && grid[i + 2][j - 2] == -1)
	{
		returnValue[0] = 1;
		returnValue[1] = 3;
		returnValue[2] = j;
		return returnValue;
	}

	// if no one won returns everything -1
	returnValue[0] = -1;
	returnValue[1] = -1;
	returnValue[2] = -1;
	return returnValue;
}

// Verifyes if exists 3 or less free cells
// and return the coordinate of these cells
int** freeCells(int grid[3][3])
{
	static int freePositions[4][2] = { 0 };
	int count1;

	count1 = 0;

	// looks for free cells
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			// if more than 3 free cells are found return all -1
			if (count1 > 3)
			{
				freePositions[2][0] = -1;
				freePositions[2][1] = -1;
				freePositions[1][0] = -1;
				freePositions[1][1] = -1;
				freePositions[0][0] = -1;
				freePositions[0][1] = -1;
				return freePositions;
			}
			if (grid[i][j] == 0)
			{
				freePositions[count1][0] = i;
				freePositions[count1][1] = j;
				count1++;
			}
		}
	}
	// no free position was found, set everything to 3
	if (freePositions[2][0] == 0 && freePositions[2][1] == 0 && freePositions[1][0] == 0 && freePositions[1][1] == 0 && freePositions[0][0] == 0 && freePositions[0][1] == 0)
	{
		freePositions[3][0] = 3;
		freePositions[3][1] = 3;
		freePositions[2][0] = 3;
		freePositions[2][1] = 3;
		freePositions[1][0] = 3;
		freePositions[1][1] = 3;
		freePositions[0][0] = 3;
		freePositions[0][1] = 3;
	}
	return freePositions;
}

// gets the tied grid to pass it to main
int** gridTiedReturner(int gridCopy[3][3], int mod)
{
	static int gridCopyToReturn[3][3];

	// gets the tied grid
	if (mod == 0)
		memcpy(gridCopyToReturn, gridCopy, sizeof(gridCopyToReturn));
	// returns the pereviously got tied grid
	if (mod == 1)
		return gridCopyToReturn;
	return 0;
}

// Verifyes if the game will tie in 3, 2 or 1 plays
// if it ties, returns 1
// if not, returns 0
int tieVerifyer(int grid[3][3], int player, int insertionPreference)
{
	static int gridCopy[3][3];
	int symbol = 0, winVerifyerReturn[4], freeCellsReturn[4][2];
	
	// gives the gridTieReturn the tied grid, so, if the game ties before the end
	// the board won't be empty
	gridTiedReturner(gridCopy, 0);

	memcpy(gridCopy, grid, sizeof(gridCopy));

	// get the free cells
	memcpy(freeCellsReturn, freeCells(grid), sizeof(freeCellsReturn));

	// loops to player 3
	if (player == 3)
	{
		player = 1;
		symbol = insertionPreference;
	}

	if (player == 2)
		symbol = -insertionPreference;

	// if no free cell exists
	if (freeCellsReturn[0][0] == 3 && freeCellsReturn[0][1] == 3 && freeCellsReturn[1][0] == 3 && freeCellsReturn[1][1] == 3)
	{
		// stores the tied grid
		gridTiedReturner(gridCopy, 0);
		return 1;
	}

	// if 1 free cell exists
	if (freeCellsReturn[1][0] == -1 && freeCellsReturn[1][1] == -1 && freeCellsReturn[2][0] == -1 && freeCellsReturn[2][1] == -1)
	{
		// try to do a play in that cell
		gridCopy[freeCellsReturn[0][0]][freeCellsReturn[0][1]] = symbol;
		memcpy(winVerifyerReturn, winVerifyer(gridCopy), sizeof(winVerifyerReturn));

		// if there was a win the game flow continues
		if (winVerifyerReturn[0] == 1)
			return 0;

		// else it stores the tied grid and
		// return 1 (tie)
		gridTiedReturner(gridCopy, 0);
		return 1;
	}

	// if 2 free cells exist
	if (freeCellsReturn[1][0] != -1 && freeCellsReturn[1][1] != -1  && freeCellsReturn[2][0] == -1 && freeCellsReturn[2][1] == -1)
	{
		// try to play every possible combination
		// and see if there's a win
		// if yes, the game continues
		// else it stores the tied grid and returns a tie
		gridCopy[freeCellsReturn[0][0]][freeCellsReturn[0][1]] = symbol;
		gridCopy[freeCellsReturn[1][0]][freeCellsReturn[1][1]] = -symbol;
		memcpy(winVerifyerReturn, winVerifyer(gridCopy), sizeof(winVerifyerReturn));

		if (winVerifyerReturn[0] == 1)
			return 0;
		gridCopy[freeCellsReturn[0][0]][freeCellsReturn[0][1]] = -symbol;
		gridCopy[freeCellsReturn[1][0]][freeCellsReturn[1][1]] = symbol;
		memcpy(winVerifyerReturn, winVerifyer(gridCopy), sizeof(winVerifyerReturn));
		if (winVerifyerReturn[0] == 1)
			return 0;
		gridTiedReturner(gridCopy, 0);
		return 1;
	}

	// if 3 free cells exits
	if (freeCellsReturn[1][0] != -1 && freeCellsReturn[1][1] != -1 && freeCellsReturn[2][0] != -1 && freeCellsReturn[2][1] != -1)
	{
		// try to play every possible combination
		// and see if there's a win
		// if yes, the game continues
		// else it stores the tied grid and returns a tie
		gridCopy[freeCellsReturn[0][0]][freeCellsReturn[0][1]] = symbol;
		gridCopy[freeCellsReturn[1][0]][freeCellsReturn[1][1]] = -symbol;
		gridCopy[freeCellsReturn[2][0]][freeCellsReturn[2][1]] = symbol;
		memcpy(winVerifyerReturn, winVerifyer(gridCopy), sizeof(winVerifyerReturn));

		if (winVerifyerReturn[0] == 1)
			return 0;

		gridCopy[freeCellsReturn[0][0]][freeCellsReturn[0][1]] = symbol;
		gridCopy[freeCellsReturn[1][0]][freeCellsReturn[1][1]] = symbol;
		gridCopy[freeCellsReturn[2][0]][freeCellsReturn[2][1]] = -symbol;
		memcpy(winVerifyerReturn, winVerifyer(gridCopy), sizeof(winVerifyerReturn));

		if (winVerifyerReturn[0] == 1)
			return 0;

		gridTiedReturner(gridCopy, 0);
		return 1;
	}
	
	//safety guard, stores the received grid (ot tied grid)
	gridTiedReturner(gridCopy, 0);

	// will return tie, for safety
	return 1;
}

// Converts the position to coordinates
int* convertToCoordinate(int position)
{
	static int coordinate[2];

	// receives the positions played and
	// converts it to arrat coordinates
	if (position == 1)
	{
		coordinate[0] = 0;
		coordinate[1] = 0;
	}
	if (position == 2)
	{
		coordinate[0] = 0;
		coordinate[1] = 1;
	}
	if (position == 3)
	{
		coordinate[0] = 0;
		coordinate[1] = 2;
	}
	if (position == 4)
	{
		coordinate[0] = 1;
		coordinate[1] = 0;
	}
	if (position == 5)
	{
		coordinate[0] = 1;
		coordinate[1] = 1;
	}
	if (position == 6)
	{
		coordinate[0] = 1;
		coordinate[1] = 2;
	}
	if (position == 7)
	{
		coordinate[0] = 2;
		coordinate[1] = 0;
	}
	if (position == 8)
	{
		coordinate[0] = 2;
		coordinate[1] = 1;
	}
	if (position == 9)
	{
		coordinate[0] = 2;
		coordinate[1] = 2;
	}

	return coordinate;
}

// converts the grid coordinates to supergrid coordinates
int* coordinatesToSupergrid(int coordinates[2])
{
	static int supergridCoordinates[2];
	// receives array coordinates and
	// converts to array coordinates of the supergrid
	if (coordinates[0] == 0)
	{
		supergridCoordinates[0] = 1;
		if (coordinates[1] == 0)
			supergridCoordinates[1] = 0;
		if (coordinates[1] == 1)
			supergridCoordinates[1] = 18;
		if (coordinates[1] == 2)
			supergridCoordinates[1] = 36;
	}

	if (coordinates[0] == 1)
	{
		supergridCoordinates[0] = 12;
		if (coordinates[1] == 0)
			supergridCoordinates[1] = 0;
		if (coordinates[1] == 1)
			supergridCoordinates[1] = 18;
		if (coordinates[1] == 2)
			supergridCoordinates[1] = 36;
	}

	if (coordinates[0] == 2)
	{
		supergridCoordinates[0] = 23;
		if (coordinates[1] == 0)
			supergridCoordinates[1] = 0;
		if (coordinates[1] == 1)
			supergridCoordinates[1] = 18;
		if (coordinates[1] == 2)
			supergridCoordinates[1] = 36;
	}
	return supergridCoordinates;
}

// Modifies the supergrid, putting X or O on the place they are
void superGridModifier(char supergrid[31][51], int grid[3][3])
{
	int supergridCoordinates[2], gridCoordinates[2];
	int symbolI = 0, symbolJ = 0; // to track the symbol array coordinates
	int supergridI, supergridJ; // to keep the start coordinates

	// X symbol in ascii in an 2d array
	char x[8][14] = { {' ','8', 'b', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'd', '8', ' '},
					  {' ',' ', 'Y', '8', ',', ' ', ' ', ' ', ' ', ',', '8', 'P', ' ', ' '},
					  {' ',' ', ' ', '`', '8', 'b', ' ', ' ', 'd', '8', '\'', ' ', ' ', ' '},
					  {' ',' ', ' ', ' ', ' ', 'Y', '8', '8', 'P', ' ', ' ', ' ', ' ', ' '},
					  {' ',' ', ' ', ' ', ' ', 'd', '8', '8', 'b', ' ', ' ', ' ', ' ', ' '},
					  {' ',' ', ' ', ',', '8', 'P', ' ', ' ', 'Y', '8', ',', ' ', ' ', ' '},
					  {' ',' ', 'd', '8', '\'', ' ', ' ', ' ', ' ', '`', '8', 'b', ' ', ' '},
					  {' ','8', 'P', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'Y', '8', ' '} };

	// O symbol in ascii in an 2d array
	char o[8][14] = { {' ', ' ', ',', 'a', 'd', '8', '8', '8', '8', 'b', 'a', ',', ' ', ' ' },
					  {' ', 'd', '8', '"', '\'', ' ', ' ', ' ', ' ', '`', '"', '8', 'b', ' ' },
					  {'d', '8', '\'', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '`', '8', 'b'},
					  {'8', '8', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '8', '8'},
					  {'8', '8', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '8', '8' },
					  {'Y', '8', ',', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ',', '8', 'P'},
					  {' ', 'Y', '8', 'a', '.', ' ', ' ', ' ', ' ', '.', 'a', '8', 'P', ' '},
					  {' ', ' ', '`', '"', 'Y', '8', '8', '8', '8', 'Y', '"', '\'', ' ', ' '} };

	// the loop will search for X's (1) or O's (-1) in the board
	// if it finds it'll place the X or O in the supergrid
	for (gridCoordinates[0] = 0; gridCoordinates[0] < 3; gridCoordinates[0]++)
	{
		for (gridCoordinates[1] = 0; gridCoordinates[1] < 3; gridCoordinates[1]++)
		{
			memcpy(supergridCoordinates, coordinatesToSupergrid(gridCoordinates), sizeof(supergridCoordinates)); // gets the supergrid coordinates
			// store the initial values
			supergridI = supergridCoordinates[0];
			supergridJ = supergridCoordinates[1];
			symbolI = 0;

			// this puts the ascii X or O in the supergrid
			for (supergridCoordinates[0] = supergridI; supergridCoordinates[0] < supergridI + 8; supergridCoordinates[0]++)
			{
				symbolJ = 0;
				for (supergridCoordinates[1] = supergridJ; supergridCoordinates[1] < supergridJ + 14; supergridCoordinates[1]++)
				{
					if (grid[gridCoordinates[0]][gridCoordinates[1]] == 1)
						supergrid[supergridCoordinates[0]][supergridCoordinates[1]] = x[symbolI][symbolJ];
					if (grid[gridCoordinates[0]][gridCoordinates[1]] == -1)
						supergrid[supergridCoordinates[0]][supergridCoordinates[1]] = o[symbolI][symbolJ];
					symbolJ++;
				}
				symbolI++;
			}
		}
	}

}

// prints the supergrid
void gridPrinter(int grid[3][3], int mod)
{
	static char superGrid[31][51];
	int i, j;
	// creates (visualy) the supergrid
	// putting the character to create an empty board
	if (mod == 0)
	{
		for (i = 0; i < 31; i++)
		{
			for (j = 0; j < 51; j++)
			{
				if (j == 15 || j == 16 || j == 33 || j == 34 || i == 10 || i == 21)
				{
					superGrid[i][j] = '#';
				}
				else if (j == 50)
				{
					superGrid[i][j] = '\n';
				}
				else
					superGrid[i][j] = ' ';
			}
		}
		for (i = 0; i < 31; i++)
		{
			superGrid[i][50] = '\n';
		}
	}
	// just prints the supergrid
	if (mod == 1)
	{
		for (int i = 0; i < 31; i++)
		{
			printf(" ");
			for (int j = 0; j < 51; j++)
			{
				printf("%c", superGrid[i][j]);
			}
		}
	}
	// calls the supergridModifyer then prints the supergrid
	if (mod == 2)
	{
		superGridModifier(superGrid, grid);
		for (int i = 0; i < 31; i++)
		{
			printf(" ");
			for (int j = 0; j < 51; j++)
			{
				printf("%c", superGrid[i][j]);
			}
		}
	}
	// prints the supergrid witn the numbers from 1 to 9 in it
	// it's printed when the game launches
	if (mod == 3)
	{
		printf("\n                ##               ##              \n         88     ##   ad888888b,  ##   ad888888b,  \n       ,d88     ##  d8\"     \"88  ##  d8\"     \"88  \n     888888     ##          a8P  ##          a8P  \n         88     ##       ,d8P\"   ##       aad8\"   \n         88     ##     a8P\"      ##       \"\"Y8,   \n         88     ##   a8P\'        ##          \"8b  \n         88     ##  d8\"          ##  Y8,     a88  \n         88     ##  88888888888  ##   \"Y888888P\' \n                ##               ##               \n ################################################\n                ##               ##                 \n          ,d8   ##  8888888888   ##    ad8888ba,  \n        ,d888   ##  88           ##   8P\'    \"Y8  \n      ,d8\" 88   ##  88  ____     ##  d8           \n    ,d8\"   88   ##  88a8PPPP8b,  ##  88,dd888bb,  \n  ,d8\"     88   ##  PP\"     `8b  ##  88P\'    `8b  \n  8888888888888 ##           d8  ##  88       d8  \n           88   ##  Y8a     a8P  ##  88a     a8P  \n           88   ##   \"Y88888P\"   ##   \"Y88888P\"   \n                ##               ##               \n ################################################\n                ##               ##                  \n  888888888888  ##   ad88888ba   ##   ad88888ba   \n           8P\'  ##  d8\"     \"8b  ##  d8\"     \"88  \n         d8\"    ##  Y8a     a8P  ##  8P       88  \n       ,8P\'     ##    \"Y8aaa8P\"  ##  Y8,    ,d88  \n      d8\"       ##   ,d8\"\"\"8b,   ##   \"PPPPPP\"88  \n    ,8P\'        ##  d8\"     \"8b  ##           8P \n   d8\"          ##  Y8a     a8P  ##  8b,    a8P   \n  8P\'           ##   \"Y88888P\"   ##  `\"Y8888P\'    \n");
	}
	// prints the supergrid with the coordinates from (1, 1) to (3, 3)
	// unused in the final version, because the option to use coordinates has been removed
	if (mod == 4)
	{
		printf("\n                ##               ##              \n                ##               ##              \n   /         \\  ##  /      __ \\  ##  /      __ \\ \n  ( /|    /|  ) ## ( /|     _) ) ## ( /|    __) )\n   \\ |  /  | /  ##  \\ |  / /__/  ##  \\ |  / __)/ \n                ##               ##              \n                ##               ##              \n                ##               ##              \n ##############################################\n                ##               ##              \n                ##               ##              \n   /__       \\  ##  /__    __ \\  ##  /__    __ \\ \n  (  _)   /|  ) ## (  _)    _) ) ## (  _)   __) )\n   \\/__ /  | /  ##  \\/__ / /__/  ##  \\/__ / __)/ \n                ##               ##              \n                ##               ##              \n                ##               ##              \n ##############################################\n                ##               ##              \n                ##               ##              \n   /__       \\  ##  /__    __ \\  ##  /__    __ \\ \n  ( __)   /|  ) ## ( __)    _) ) ## ( __)   __) )\n   \\__) /  | /  ##  \\__) / /__/  ##  \\__) / __)/ \n                ##               ##              \n                ##               ##              \n                ##               ##              \n");
	}

	// prinnts the supergrid with the victory line in it
	if (mod == 5)
	{
		// updates the supergrid to the last move
		superGridModifier(superGrid, grid);

		int winVerifyerReturn[4];

		// gets the winVerifyer return array know which victory line to print
		memcpy(winVerifyerReturn, winVerifyer(grid), sizeof(winVerifyerReturn));
		printf(" ");

		// if the win is horizontal
		// it'll print ':' in sequence on a horizontal line
		if (winVerifyerReturn[1] == 0)
		{
			if (winVerifyerReturn[2] == 0)
			{
				for (j = 0; j < 50; j++)
				{
					superGrid[3][j] = ':';
					superGrid[4][j] = ':';
				}
			}

			if (winVerifyerReturn[2] == 1)
			{
				for (j = 0; j < 50; j++)
				{
					superGrid[14][j] = ':';
					superGrid[15][j] = ':';
				}
			}

			if (winVerifyerReturn[2] == 2)
			{
				for (j = 0; j < 50; j++)
				{
					superGrid[25][j] = ':';
					superGrid[26][j] = ':';
				}
			}
		}

		// if the win is vertical
		// it'll print ':' in sequence on a vertical line
		if (winVerifyerReturn[1] == 1)
		{
			if (winVerifyerReturn[2] == 0)
			{
				for (i = 0; i < 31; i++)
				{
					superGrid[i][7] = ':';
					superGrid[i][8] = ':';
				}
			}

			if (winVerifyerReturn[2] == 1)
			{
				for (i = 0; i < 31; i++)
				{
					superGrid[i][25] = ':';
					superGrid[i][26] = ':';
				}
			}

			if (winVerifyerReturn[2] == 2)
			{
				for (i = 0; i < 31; i++)
				{
					superGrid[i][43] = ':';
					superGrid[i][44] = ':';
				}
			}
		}

		//if the win is a diagonal 1 (comes from top left to botton right)
		// it'll print '\' in a diagonal line
		// this print isn't exactly a sequence
		// but will print more than one '\' per line until it goes to the next
		if (winVerifyerReturn[1] == 2)
		{
			j = 0;
			int jCopy = -1;
			for (i = 0; i < 31; i++)
			{

				for (jCopy = j; j < jCopy + 3; j++)
				{
					superGrid[i][j] = '\\';
				}
				i++;
				j = jCopy + 1;
				for (jCopy = j; j < jCopy + 3; j++)
				{
					superGrid[i][j] = '\\';
				}
				i++;
				j = jCopy + 1;
				for (jCopy = j; j < jCopy + 3; j++)
				{
					superGrid[i][j] = '\\';
				}
				if (i == 26)
				{
					for (i = 27; i < 31; i++)
					{
						j = jCopy + 1;
						for (jCopy = j; j < jCopy + 3; j++)
						{
							superGrid[i][j] = '\\';
						}
					}

				}
			}
		}

		//if the win is a diagonal 2 (comes from top right to botton left)
		// it'll print '/' in a diagonal line
		// this print isn't exactly a sequence
		// but will print more than one '/' per line until it goes to the next
		if (winVerifyerReturn[1] == 3)
		{
			j = 49;
			int jCopy;
			for (i = 0; i < 31; i++)
			{

				for (jCopy = j; j > jCopy - 3; j--)
				{
					superGrid[i][j] = '/';
				}
				i++;
				j = jCopy - 1;
				for (jCopy = j; j > jCopy - 3; j--)
				{
					superGrid[i][j] = '/';
				}
				i++;
				j = jCopy - 1;
				for (jCopy = j; j > jCopy - 3; j--)
				{
					superGrid[i][j] = '/';
				}
				if (i == 26)
				{
					for (i = 27; i < 31; i++)
					{
						j = jCopy - 1;
						for (jCopy = j; j > jCopy - 3; j--)
						{
							superGrid[i][j] = '/';
						}
					}

				}
			}
		}
		
		// prints the supergrid
		for (i = 0; i < 31; i++)
		{
			for (j = 0; j < 51; j++)
			{
				printf("%c", superGrid[i][j]);
			}
			printf(" ");
		}
	
	}
}

// prints the thanks
void thanks()
{
	printf("\nThank you for playing!\n");
	printf("pecial thanks to::\n");
	printf("My mom, that, while not knowing anything about code, listened to me and helped clarify as ideas,\n");
	printf("Patrick Gillespie (twiiter @patorjk) and his Text to ASCII Art Generator (http://patorjk.com/software/taag)\n");
	printf("\n");
	printf("This projecct is possible due to Notepad++ and Visaul Studio Community 2019\n");
	printf("\n");
	printf("Author: Lucas Isaac (@LIPSilva5)\n");
	system("pause");
}

int main(int argc, char* argv[])
{
	static int grid[3][3] = { 0 }; //grid creation
	int playCoordinates[2] = { 0 }, playPosition, player; // creates the player interaction
	int  symbolPreference; // this will be used to determine if the player 1 wants X or O
	int win = 0, tie = 0; // win and tie flags
	int freeCellsReturn[4][2]; // this will hold the return array of the free cells verifyer function
	char keepPlaying; // keep playing flag
	char trashcan[10]; //used to freeze the program
	keepPlaying = 'x';

	printf("Starting Tic Tac Toe\n");
	printf("To select a position you use:\n");
	gridPrinter(grid, 3);
	fgets(trashcan, 5, stdin); // freezes the execution so the player can see how the game handles the play
	printf("Would you like to play which mode: 1- Singleplyer or 2- Multiplayer\n");
	if (scanf("%i", &player) == 1); // gets the player mode
	printf("Which you'll play with? 1- X ou 2- O\n");
	if (scanf("%i", &symbolPreference) == 2); // gets the symbol preference for player 1
	if (symbolPreference == 2) // if the player selected O (2) it'll use -1 as representation of O
		symbolPreference = -1;

	// multiplayer mode
	if (player == 2)
	{
		// this loops will keep the game running if the player selects keep playing
		while (keepPlaying != 'n' && keepPlaying != 'N')
		{
			// put zeros in the grid
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					grid[i][j] = 0;
				}
			}
			player = 1; // set to player 1
			gridPrinter(grid, 0); // prints the supergrid
			
			// set win and tie flags to zero
			win = 0;
			tie = 0;

			// play loop
			while (win == 0 && tie == 0)
			{
				// uses ANSI escape codes to clear the screen
				{
					setupConsole();
					clearScreenToTop();
					moveTo(0, 0);
					restoreConsole();
				}

				// prints the updated grid
				gridPrinter(grid, 2);

				// sets to player 1 if player 2 already played
				if (player == 3)
					player = 1;
				printf("Play, Player %i\n", player);

				if(scanf("%i", &playPosition) == 1); // gets play position
				memcpy(playCoordinates, convertToCoordinate(playPosition), sizeof(playCoordinates)); // converts the play position to array coordinates

				// if play coordinates come negarive this stops the game (not inted to be done)
				if (playCoordinates[0] < 0 || playCoordinates[1] < 0)
					break;

				// looks if the cell isn't empty, if it is, warns the player and loops early
				if (grid[playCoordinates[0]][playCoordinates[1]] != 0)
				{
					printf("\nThis cell is already marked!\n");
					fgets(trashcan, 5, stdin);
					continue;
				}

				// makes the payer move
				if (player == 1)
					grid[playCoordinates[0]][playCoordinates[1]] = symbolPreference;
				if (player == 2)
					grid[playCoordinates[0]][playCoordinates[1]] = -symbolPreference;

				// calls the winVerifyer function, if it returns a win
				// it will print the board with the victory line and the message of who won
				if ((winVerifyer(grid))[0] == 1)
				{
					setupConsole();
					clearScreenToTop();
					moveTo(0, 0);
					restoreConsole();
					gridPrinter(grid, 5);
					printf("\nPlayer %i wins!", player);
					win = 1;
					break;
				}

				player++; // next player

				memcpy(freeCellsReturn, freeCells(grid), sizeof(freeCellsReturn)); // looks for free cells

				// if the freeCells function retuned something different of -1 (more than 3 free cells)
				// it'll look for tie
				if (freeCellsReturn[0][0] != -1)
				{
					// if there aren't free cells
					// prits the tied board and the tie message
					if (freeCellsReturn[0][0] == 3)
					{
						gridPrinter(gridTiedReturner(grid, 1), 2);
						printf("\nTie...\n");
						tie = 1;
						break;
					}

					// calls the tieVerifyer function
					// if it returns 1 (tie)
					// prits the tied board and the tie message
					if (tieVerifyer(grid, player, symbolPreference) == 1)
					{
						memcpy(grid, gridTiedReturner(grid, 1), sizeof(grid));
						gridPrinter(gridTiedReturner(grid, 1), 2);
						printf("\nTie...\n");
						tie = 1;
						break;
					}
				}
			}
			// prompts if the player wants to continue playing
			printf("\nContinue playing?\n y- yes  n- no\n");
			if(getchar() == '\n');
			if (scanf("%c", &keepPlaying) == 1);
			player = 0;
		}
	}
	
	// single player mode
	// instead of the player 2 play, the AI plays
	// what happens here that also happens in two player mode won't be commented
	// just things that are for single player only
	if (player == 1)
	{
		int difficulty;
		printf("Select your difficulty: 1- Easy, 2- Normal, 3- Impossible\n");
		if (scanf(" %i", &difficulty) == 1);
		difficulty--;

		// starts the AI
		aiStart(grid, -symbolPreference);
		while (keepPlaying != 'n' && keepPlaying != 'N')
		{
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					grid[i][j] = 0;
				}
			}
			player = 1;
			gridPrinter(grid, 0);
			win = 0;
			tie = 0;
			while (win == 0 && tie == 0)
			{
				setupConsole();
				clearScreenToTop();
				moveTo(0, 0);
				restoreConsole();
				if (player == 3)
					player = 1;
				if (player == 1)
				{
					gridPrinter(grid, 2);
					printf("Play, Player!\n");
				
					if (scanf("%i", &playPosition) == 1);
					memcpy(playCoordinates, convertToCoordinate(playPosition), sizeof(playCoordinates));

					if (playCoordinates[0] < 0 || playCoordinates[1] < 0)
						break;
					if (grid[playCoordinates[0]][playCoordinates[1]] != 0)
					{
						printf("\nThis cell is already marked!\n");
						if (getchar() != NULL);
						continue;
					}
				}
				if (player == 1)
					grid[playCoordinates[0]][playCoordinates[1]] = symbolPreference;
				if (freeCellsReturn[0][0] == 3)
				{
					gridPrinter(grid, 2);
					printf("\nTie...\n");
					tie = 1;
					break;
				}
				if (player == 2)
				{
					memcpy(playCoordinates, aiPlay(grid, difficulty), sizeof(playCoordinates)); // gets the AI play
					grid[playCoordinates[0]][playCoordinates[1]] = -symbolPreference; // puts the AI play inthe board
				}
					
				if ((winVerifyer(grid))[0] == 1)
				{
					gridPrinter(grid, 5);
					if (player == 1)
						printf("\nYou win!");
					if (player == 2)
						printf("\nYou lose!\n");
					win = 1;
					break;
				}
				player++;
				memcpy(freeCellsReturn, freeCells(grid), sizeof(freeCellsReturn));
				if (freeCellsReturn[0][0] != -1)
				{
					if (freeCellsReturn[0][0] == 3)
					{
						gridPrinter(grid, 2);
						printf("\nTie...\n");
						tie = 1;
						break;
					}

					if (tieVerifyer(grid, player, symbolPreference) == 1)
					{
						memcpy(grid, gridTiedReturner(grid, 1), sizeof(grid));
						gridPrinter(gridTiedReturner(grid, 1), 2);
						printf("\nTie...\n");
						tie = 1;
						break;
					}
				}
			}
			printf("\nContine playing?\n y- yes  n- no\n");
			if (getchar() == '\n');
			if (scanf("%c", &keepPlaying) == 1);
		}
	}
	
	// prints the thanks after playing
	thanks();
}
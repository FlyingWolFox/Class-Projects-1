#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "ansi_escapes.h"

// handles mouse interaction
#include "windowsConsoleInteraction.h"
#include <conio.h>

// coordinate system
typedef struct Coordinates {
	short i, j;
}coord;

// converts the mouse click to board coordinates
coord clickToCoordinates(COORD click)
{
	coord retValue;
	
	click.X--;
	retValue.i = -1;
	retValue.j = -1;

	for (int count = 0; count < 37; count += 4)
	{
		if (click.Y > count&& click.Y < count + 4)
		{
			retValue.i = count / 4;
			break;
		}
	}
	for (int count = 0; count < 109; count += 9)
	{
		if (click.X > count&& click.X < count + 9)
		{
			retValue.j = count / 9;
			break;
		}
	}
	return retValue;
}

// creates the display board
// putting the character to create an empty board
void createDisplayeGrid(char displayGrid[61][145])
{
	for (int i = 0; i < 61; i++)
	{
		for (int j = 0; j < 145; j++)
		{
			if (j % 9 == 0 || i % 4 == 0)
			{
				if (i % 4 == 0)
					displayGrid[i][j] = ':';

				if (j % 9 == 0)
					displayGrid[i][j] = '|';
			}
			else
				displayGrid[i][j] = ' ';
		}		
	}
}

// modifyes the display grid putting
// a ship part, submarine or miss in the squares
void modifyDisplayGrid(char displayGrid[61][145], coord coordinates, char symbol)
{
	char horizontalBow[3][8] = { {' ', ' ', ' ', ' ', ' ', ' ', ' ', '_'} ,
								 {' ', ' ', ' ', ' ', '_', '_', '/', ' '} ,
								 {' ', ' ', ' ', ' ', '\\', '_', '_', '_'} };

	char horizontalMiddle[3][8] = { {'_', '_', '_', '_', '_', '_', '_', '_'} ,
									{' ', ' ', '|', '_', 'o', '_', '|', ' '} ,
									{'_', '_', '_', '_', '_', '_', '_', '_'} };

	char horizontalStern[3][8] = { {'_', '_', '_', ' ', ' ', ' ', ' ', ' '} ,
								   {' ', ' ', ' ', '|', ' ', ' ', ' ', ' '} ,
								   {'_', '_', '/', ' ', ' ', ' ', ' ', ' '} };

	char verticalBow[3][8] = { {' ', ' ', ' ', '/', '\\', ' ', ' ', ' '} ,
							   {' ', ' ', '/', '_', '_', '\\', ' ', ' '} ,
							   {' ', '|', ' ', ' ', ' ', ' ', '|', ' '} };

	char verticalMiddle[3][8] = { {' ', '|', ' ', ' ', ' ', ' ', '|', ' '} ,
								  {' ', '|', ' ', ' ', ' ', ' ', '|', ' '} ,
								  {' ', '|', ' ', ' ', ' ', ' ', '|', ' '} };

	char verticalStern[3][8] = { {' ', '|', ' ', '_', '_', ' ', '|', ' '} ,
								 {' ', '|', '_', '_', '_', '_', '|', ' '} ,
								 {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '} };

	char nope[3][8] = { {' ', ' ', '\\', '_', '_', '/', ' ', ' '} ,
						{' ', '-', '|', '_', '_', '|', '-', ' '} ,
						{' ', ' ', '/', ' ', ' ', '\\', ' ', ' '} };

	char submarine[3][8] = { {' ', ' ', ' ', ' ', '_', ' ', ' ', ' '} ,
							 {' ', '_', '_', '/', 'o', '\\', '_', ' '} ,
							 {'|', '_', '_', '_', '_', '_', '_', '|'} };

	coord start;

	for (int count = 0; count < 9; count++)
	{
		if (coordinates.i == count)
		{
			start.i = (count * 4) + 1;
			break;
		}
	}
	for (int count = 0; count < 11; count++)
	{
		if (coordinates.j == count)
		{
			start.j = (count * 9) + 1;
			break;
		}
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (symbol == '<')
			{
				displayGrid[start.i + i][start.j + j] = horizontalBow[i][j];
				continue;
			}
			if (symbol == '=')
			{
				displayGrid[start.i + i][start.j + j] = horizontalMiddle[i][j];
				continue;
			}
			if (symbol == '>')
			{
				displayGrid[start.i + i][start.j + j] = horizontalStern[i][j];
				continue;
			}
			if (symbol == '^')
			{
				displayGrid[start.i + i][start.j + j] = verticalBow[i][j];
				continue;
			}
			if (symbol == '|')
			{
				displayGrid[start.i + i][start.j + j] = verticalMiddle[i][j];
				continue;
			}
			if (symbol == '~')
			{
				displayGrid[start.i + i][start.j + j] = verticalStern[i][j];
			}
			if (symbol == ' ')
			{
				displayGrid[start.i + i][start.j + j] = nope[i][j];
				continue;
			}
			if (symbol == 'o')
			{
				displayGrid[start.i + i][start.j + j] = submarine[i][j];
				continue;
			}
		}
	}

}

// prints the display
void printDisplayGrid(char displayGrid[61][145])
{
	for (int i = 0; i < 61; i++)
	{
		moveRight(1);
		for (int j = 0; j < 145; j++)
			printf("%c", displayGrid[i][j]);
		printf("\n");
	}
}

// sees if the game ended
// if yes, is because all ships have been found
bool isEnd(char grid[15][15], char playerGrid[15][15])
{
	bool isEnd = true;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 11; j++)
			if (grid[i][j] != playerGrid[i][j])
				isEnd = false;
	}
	return isEnd;
}

// prints the thanks
void thanks(void)
{
	puts("Thanks for playing!");
	puts("");
	puts("Shoutouts for the people on Stack Overflow!");
	puts("This project was made using Visual Studio Comuity 2019, Excel and Notepad++");
	puts("");
}

int main(int argc, char** argv)
{
	// if there's no argument, shows the usage
	if (argc < 3)
	{
		printf("\tusage: battleship <file> <map mode>\n");
		return -1;
	}
	// try to open the file
	FILE* textFile;
	textFile = fopen(argv[1], "r");
	if (textFile == NULL)
	{
		puts("Couldn't open file");
		return -2;
	}

	char displayGrid[61][145];
	char grid[15][15]; // grid with the complete board
	char playGrid[15][15]; // the grid that the player sees
	coord play; // play coordinates
	EVENT retEvent; // console window events
	COORD mouseCoord; // mouse click coordinates
	char trashcan[10]; // used to get inputs or freeze execution

	// looks if the file is valid and
	// formatted correctly, and 
	// gets the map from the file
	{
		char getGrid[15][33] = { 0 };
		bool pass = true;
		for (int count = 0; count < 15; count++)
			fgets(getGrid[count], 33, textFile);

		for (int count = 0; count < 15; count++)
		{
			if (getGrid[count][32] != '\0' && getGrid[count][32] != '\n')
			{
				pass = false;
				break;
			}
		}

		if (pass == false)
		{
			puts("the file isn't formatted correctly, please try again");
			return 1;
		}

		for (int i = 0; i < 15; i++)
		{
			for (int j = 1; j < 31; j += 2)
				grid[i][j - (j/2 + 1)] = getGrid[i][j];
		}

		for (int i = 0; i < 15; i++)
		{
			for (int j = 0; j < 15; j++)
				playGrid[i][j] = ' ';
		}

	}
	
	// verifies the windows size
	// if it's too small it'll prompt to maximaze it
	{
		int windowSize[2];
		setupConsole();
		moveTo(999, 999);
		getCursorPosition(&windowSize[0], &windowSize[1]);
		moveTo(0, 0);

		while (windowSize[0] < 40)
		{
			puts("Please, expand the console window!");
			moveTo(999, 999);
			getCursorPosition(&windowSize[0], &windowSize[1]);
			moveTo(0, 0);
		}
		clearScreenToBottom();
		restoreConsoleMode();
	}

	createDisplayeGrid(displayGrid);
	printDisplayGrid(displayGrid);

	// play loop
	for (bool playing = true; playing == true;)
	{
		// gets the mouse click coordinates
		while (true)
		{
			retEvent.event.mouseEvent = 0xc00;
			retEvent = eventMain();
			mouseCoord = retEvent.event.mouseCoord;
			if (retEvent.event.mouseEvent == FROM_LEFT_1ST_BUTTON_PRESSED) 
				break;
		}

		// if the mouse click coordinates weren't captured
		// (for some reason) it'll loop to get it again
		play = clickToCoordinates(mouseCoord);
		if (play.i == -1 || play.j == -1)
			continue;

		// modifies the grid and prints it
		modifyDisplayGrid(displayGrid, play, grid[play.i][play.j]);
		playGrid[play.i][play.j] = grid[play.i][play.j];
		clearScreenToTop;
		moveTo(0, 0);
		printDisplayGrid(displayGrid);

		// verifies if the game ended
		if (isEnd(grid, playGrid))
		{
			puts("Game Over!");
			playing = false;
			break;
		}
	}

	// prints the thanks
	thanks();
	puts("---Press any key to exit---");
	fgets(trashcan, 5, stdin);
	return 0;
}
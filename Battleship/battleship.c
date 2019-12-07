#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <inttypes.h>
#include "ansi_escapes.h"

// handles mouse interaction
#include "windowsConsoleInteraction.h"
#include <conio.h>

// coordinate system
typedef struct Coordinates {
	short i, j;
}coord;

int mapMode;

// the _x inthe function names express in which mode they're used
// I done this because the grid array can have variable lenght
// I tried getting the size by argument, just avilable in c99, bit it didn't work


// converts the mouse click to board coordinates
coord clickToCoordinates(COORD click)
{
	coord retValue;
	
	click.X--;
	retValue.i = -1;
	retValue.j = -1;

	for (int count = 0; count < 40; count += 4)
	{
		if (click.Y > count&& click.Y < count + 4)
		{
			retValue.i = count / 4;
			break;
		}
	}
	for (int count = 0; count < 135; count += 9)
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
void createDisplayeGrid_0(char displayGrid[61][136])
{
	for (int i = 0; i < 61; i++)
	{
		for (int j = 0; j < 136; j++)
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
void modifyDisplayGrid_0(char displayGrid[61][136], coord coordinates, char symbol)
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

	for (int count = 0; count < 15; count++)
	{
		if (coordinates.i == count)
		{
			start.i = (count * 4) + 1;
			break;
		}
	}
	for (int count = 0; count < 15; count++)
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
void printDisplayGrid_0(char displayGrid[61][136])
{
	for (int i = 0; i < 61; i++)
	{
		moveRight(1);
		for (int j = 0; j < 136; j++)
			printf("%c", displayGrid[i][j]);
		printf("\n");
	}
}

// sees if the game ended
// if yes, is because all ships have been found
bool isEnd_0(char grid[15][15], char playerGrid[15][15])
{
	bool isEnd = true;
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
			if (grid[i][j] != playerGrid[i][j])
				isEnd = false;
	}
	return isEnd;
}

// creates the display board
// putting the character to create an empty board
void createDisplayeGrid_1(char displayGrid[41][136])
{
	for (int i = 0; i < 41; i++)
	{
		for (int j = 0; j < 136; j++)
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
void modifyDisplayGrid_1(char displayGrid[41][136], coord coordinates, char symbol)
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

	for (int count = 0; count < 10; count++)
	{
		if (coordinates.i == count)
		{
			start.i = (count * 4) + 1;
			break;
		}
	}
	for (int count = 0; count < 15; count++)
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
void printDisplayGrid_1(char displayGrid[41][136])
{
	for (int i = 0; i < 41; i++)
	{
		moveRight(1);
		for (int j = 0; j < 136; j++)
			printf("%c", displayGrid[i][j]);
		printf("\n");
	}
}

// sees if the game ended
// if yes, is because all ships have been found
bool isEnd_1(char grid[10][15], char playerGrid[10][15])
{
	bool isEnd = true;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 15; j++)
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

// default: battleship.exe "C:\textFile" 1
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

	if (argv[2][0] != '0' && argv[2][0] != '1')
	{
		printf("\tinvalid map mode");
		return -3;
	}

	mapMode = argv[2][0] - '0';

	char trashcan[10]; // used to get inputs or freeze execution

	if (mapMode == 0)
	{
		char displayGrid[61][136];
		char grid[15][15]; // grid with the complete board
		char playGrid[15][15]; // the grid that the player sees
		coord play; // play coordinates		

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
					grid[i][j - (j / 2 + 1)] = getGrid[i][j];
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

		createDisplayeGrid_0(displayGrid);
		printDisplayGrid_0(displayGrid);

		// play loop
		for (bool playing = true; playing == true;)
		{
			// initialization. withou it won't compile
			play.i = 0;
			play.j = 0;

			// gets the player move coordinates and converts to int
			puts("What cordinates to attack? (Type the X coordinate and enter, then type the Y coordinate)");
			fgets(trashcan, 10, stdin);
			play.i = (strtoimax(trashcan, NULL, 10)) - 1;

			fgets(trashcan, 10, stdin);
			play.j = (strtoimax(trashcan, NULL, 10)) - 1;


			if ( (play.i == UINTMAX_MAX && errno == ERANGE) || (play.j == UINTMAX_MAX && errno == ERANGE) )
			{
				puts("Invalid input. Just numbers are allowed");
				fgets(trashcan, 10, stdin);
				continue;
			}

			if (play.i > 15 || play.i < 1 || play.j > 15 || play.j < 1)
			{
				puts("Out of the range!");
				fgets(trashcan, 10, stdin);
				continue;
			}

			play.i--;
			play.j--;

			// modifies the grid and prints it
			modifyDisplayGrid_0(displayGrid, play, grid[play.i][play.j]);
			playGrid[play.i][play.j] = grid[play.i][play.j];
			printDisplayGrid_0(displayGrid);

			// verifies if the game ended
			if (isEnd_0(grid, playGrid))
			{
				puts("Game Over!");
				playing = false;
				break;
			}
		}

	}

	if (mapMode == 1)
	{
		char displayGrid[41][136];
		char grid[10][15]; // grid with the complete board
		char playGrid[10][15]; // the grid that the player sees
		EVENT retEvent; // console window events
		COORD mouseCoord; // mouse click coordinates
		coord play; // play coordinates

		// looks if the file is valid and
		// formatted correctly, and 
		// gets the map from the file
		{
			char getGrid[10][33] = { 0 };
			bool pass = true;
			for (int count = 0; count < 10; count++)
				fgets(getGrid[count], 33, textFile);

			for (int count = 0; count < 10; count++)
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
				return -1;
			}

			for (int i = 0; i < 10; i++)
			{
				for (int j = 1; j < 30; j += 2)
					grid[i][j - (j / 2 + 1)] = getGrid[i][j];
			}

			for (int i = 0; i < 10; i++)
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


		createDisplayeGrid_1(displayGrid);
		printDisplayGrid_1(displayGrid);

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
			modifyDisplayGrid_1(displayGrid, play, grid[play.i][play.j]);
			playGrid[play.i][play.j] = grid[play.i][play.j];
			clearScreenToTop();
			moveTo(0, 0);
			printDisplayGrid_1(displayGrid);

			// verifies if the game ended
			if (isEnd_1(grid, playGrid))
			{
				puts("Game Over!");
				playing = false;
				break;
			}
		}
	}

	// prints the thanks
	thanks();
	puts("---Press any key to exit---");
	fgets(trashcan, 5, stdin);
	return 0;
}